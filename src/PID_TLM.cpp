/**
 * @file    PID_TLM_TLM.cpp
 * @brief   TLM wrapper of the PID source
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.3
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/08/15  TVIDIGAL     Document created.
 * 1.1      2016/08/24  TVIDIGAL     Using float_pid as the type of signals and
 *                                   making gain send with SC_ZERO_TIME delay
 * 1.2      2016/09/21  TVIDIGAL     Correcting name sendGain (threadSendGain).
 * 1.3      2016/10/02  TVIDIGAL     Forcing PID type choose at the constructor
 *
 *----------------------------------------------------------------------------*/

#include "../hdr/PID_TLM.hpp"

SC_HAS_PROCESS(PID_TLM);


/* Public ********************************************************************/

//Constructor
PID_TLM::PID_TLM(sc_module_name inst, PID* pid) : sc_module(inst),

	initGain("InitGain"),
	trgtError("TrgtError")

{
	cout << "Constructing PIDTLM\t" << name() << endl;
	
	this->pid = pid;
	trgtError.register_b_transport(this, &PID_TLM::b_transport);
	SC_THREAD(threadSendGain);
	sensitive << pid->gain;
}


/* Private *******************************************************************/

void PID_TLM::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {

	tlm::tlm_command cmd = trans.get_command();
	unsigned char*   ptr = trans.get_data_ptr();
	unsigned int     len = trans.get_data_length();
	unsigned int     wid = trans.get_streaming_width();
	float_pid        error;

	// Validate payload
	if ( wid != len || len != sizeof(float_pid) )
		SC_REPORT_ERROR("TLM-2", "Invalid payload transaction");

	// Commands
	if ( cmd == tlm::TLM_WRITE_COMMAND ) {
		memcpy(&(error), ptr, len);
		pid->error.write(error);
	}
	else
		SC_REPORT_ERROR("TLM-2", "Invalid command");

	// Response status
	trans.set_response_status( tlm::TLM_OK_RESPONSE );
}

void PID_TLM::threadSendGain() {

	float_pid gain;

	while(true) {
		wait();

		gain = pid->gain.read();
	    sc_time delay = sc_time(SC_ZERO_TIME);
	    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;

		trans->set_command( tlm::TLM_WRITE_COMMAND );
		trans->set_data_ptr( reinterpret_cast<unsigned char*>(&gain) );
		trans->set_data_length( sizeof(float_pid) );
		trans->set_streaming_width( sizeof(float_pid) );
		trans->set_dmi_allowed( false );
		trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

		// Transport call
		initGain->b_transport( *trans, delay );

		// Check response status and delay
		if ( trans->is_response_error() )
			SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
		wait(delay);
	}
}
