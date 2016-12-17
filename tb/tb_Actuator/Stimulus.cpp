/**
 * @file    Stimulus.hpp
 * @brief   Actuator Stimulus source
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
 * 1.0      2016/10/17  TVIDIGAL     Document adapted from Plant TB
 *
 *----------------------------------------------------------------------------*/

#include "Stimulus.hpp"
SC_HAS_PROCESS(Stimulus);


/* Public ********************************************************************/

//Constructor
Stimulus::Stimulus(sc_module_name inst) : sc_module(inst),

	initGain("InitSetpoint")

{
	cout << "Constructing Stimul\t" << name() << endl;

	fset.open("tb/tb_Actuator/gain.txt");

	SC_THREAD(doStimulus);
	sensitive << send_event;
}


/* Private ********************************************************************/

void Stimulus::doStimulus() {

	float_pid gain;

	// Initializations
    sc_time delay = sc_time(SC_ZERO_TIME);

	while(true) {

		wait();

		//Read + Stop conditions
		if(fset.is_open()) {
			if(!(fset >> gain))
				break;
		}
		
		else break;

		// Create transport
    	tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
		trans->set_command( tlm::TLM_WRITE_COMMAND );
		trans->set_data_ptr( reinterpret_cast<unsigned char*>(&gain) );
		trans->set_data_length( sizeof(float_pid) );
		trans->set_streaming_width( sizeof(float_pid) );
		trans->set_dmi_allowed( false );
		trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

		// Transport call
		cout << endl << "[" << sc_time_stamp() << "]   \t" << flush;
		cout << "Sending gain (" << gain << ")\t" << flush;
		initGain->b_transport( *trans, delay );

		// Check response status and delay
		if ( trans->is_response_error() )
			SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
		wait(delay);
	}

    sc_stop();
}
