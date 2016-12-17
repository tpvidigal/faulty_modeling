/**
 * @file    Actuator.cpp
 * @brief   Actuator of the control system source
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.0
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/10/17  TVIDIGAL     Document created.
 *
 *----------------------------------------------------------------------------*/

#include "../hdr/Actuator.hpp"
SC_HAS_PROCESS(Actuator);


/* Public ********************************************************************/

//Constructor
Actuator::Actuator(sc_module_name inst) : sc_module(inst),

	initGain("ActuatorInitGain"),
	trgtGain("ActuatorTrgtGain")

{
	cout << "Constructing Actuat\t" << name() << endl;

	//Transports and methods
	trgtGain.register_b_transport(this, &Actuator::doActuator);
	SC_THREAD(threadSendGain);
	sensitive << send_output;
}


/* Private ********************************************************************/

//Methods

void Actuator::doActuator(tlm::tlm_generic_payload& trans, sc_time& delay) {
	tlm::tlm_command cmd = trans.get_command();
	unsigned char*   ptr = trans.get_data_ptr();
	unsigned int     len = trans.get_data_length();
	unsigned int     wid = trans.get_streaming_width();

	// Validate payload
	if ( wid != len || len != sizeof(float_pid) )
		SC_REPORT_ERROR("TLM-2", "Invalid payload transaction");

	// Commands
	if ( cmd == tlm::TLM_WRITE_COMMAND )
		memcpy(&(gain), ptr, len);

	else
		SC_REPORT_ERROR("TLM-2", "Invalid command");

	// Response status
	trans.set_response_status( tlm::TLM_OK_RESPONSE );
	send_output.notify(SC_ZERO_TIME);
}

void Actuator::threadSendGain() {

	while(true) {

		wait();

		// Initializations
		output_gain = computeGain();
	    sc_time delay = sc_time(SC_ZERO_TIME);
	    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;

		trans->set_command( tlm::TLM_WRITE_COMMAND );
		trans->set_data_ptr( reinterpret_cast<unsigned char*>(&output_gain) );
		trans->set_data_length( sizeof(float_pid) );
		trans->set_streaming_width( sizeof(float_pid) );
		trans->set_dmi_allowed( false );
		trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

		// Transport call
		initGain->b_transport( *trans, delay );
		if ( trans->is_response_error() )
			SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
		wait(delay);

	}
}

float_pid Actuator::computeGain() {

		static float_pid rate = 0.8 * CLK_PERIOD;
		float_pid plant_gain;

		// Saturation
		// Min = -2
		// Max =  2
		if     (gain <= -2) plant_gain =   -2;
		else if(gain >=  2) plant_gain =    2;
		else                plant_gain = gain;

		// Rate Limiter
		// Rate: 0.8
		if(plant_gain > output_gain) {
			if(plant_gain - output_gain > rate)
				output_gain += rate;
			else
				output_gain = plant_gain;
		}
		else {
			if(output_gain - plant_gain > rate)
				output_gain -= rate;
			else
				output_gain = plant_gain;
		}

		return output_gain;
}
