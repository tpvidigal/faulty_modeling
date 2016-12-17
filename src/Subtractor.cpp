/**
 * @file    Subtractor.cpp
 * @brief   Subtractor of the control system source
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.2
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/08/24  TVIDIGAL     Document created.
 * 1.1      2016/09/24  TVIDIGAL     Correcting thread (making it loop)
 * 1.2      2016/10/01  TVIDIGAL     Setpoint transport defines iteration of
 *                                   subtractor (output only changes variable)
 *
 *----------------------------------------------------------------------------*/

#include "../hdr/Subtractor.hpp"
SC_HAS_PROCESS(Subtractor);


/* Public ********************************************************************/

/**
 * @brief      Default constructor
 * @note       trgtOutput don't have it's b_transport registered because
 *             setpoint must be defined before (b_trans_setvalue must
 *             occur before)
 */
Subtractor::Subtractor(sc_module_name inst) : sc_module(inst),

	initError("SubInitError"),
	trgtSetpoint("SubTrgtSetpoint"),
	trgtOutput("SubTrgtOutput")

{
	cout << "Constructing Subtra\t" << name() << endl;

	trgtSetpoint.register_b_transport(this, &Subtractor::b_trans_setvalue);
	trgtOutput.register_b_transport(this, &Subtractor::b_trans_output);
	SC_THREAD(threadSendError);
	sensitive << ev_error;
}


/* Private *******************************************************************/

/**
 * @brief      b_transport of trgtSetpoint
 * @param      trans  The transaction
 * @param      delay  The delay
 * @note       Registers b_transport of trgtOutput 
 */
void Subtractor::b_trans_setvalue(tlm::tlm_generic_payload& trans, sc_time& delay) {

	tlm::tlm_command cmd = trans.get_command();
	unsigned char*   ptr = trans.get_data_ptr();
	unsigned int     len = trans.get_data_length();
	unsigned int     wid = trans.get_streaming_width();

	// Validate payload
	if ( wid != len || len != sizeof(float_pid) )
		SC_REPORT_ERROR("TLM-2", "Invalid payload transaction");

	// Commands
	if ( cmd == tlm::TLM_WRITE_COMMAND )
		memcpy(&(s_setpoint), ptr, len);

	else
		SC_REPORT_ERROR("TLM-2", "Invalid command");

	// Response status
	trans.set_response_status( tlm::TLM_OK_RESPONSE );
	ev_error.notify(SC_ZERO_TIME);
}

/**
 * @brief      b_transport of trgtOutput
 * @param      trans  The transaction
 * @param      delay  The delay
 */
void Subtractor::b_trans_output(tlm::tlm_generic_payload& trans, sc_time& delay) {

	tlm::tlm_command cmd = trans.get_command();
	unsigned char*   ptr = trans.get_data_ptr();
	unsigned int     len = trans.get_data_length();
	unsigned int     wid = trans.get_streaming_width();

	// Validate payload
	if ( wid != len || len != sizeof(float_pid) )
		SC_REPORT_ERROR("TLM-2", "Invalid payload transaction");

	// Commands
	if ( cmd == tlm::TLM_WRITE_COMMAND ) 
		memcpy(&(s_output), ptr, len);

	else
		SC_REPORT_ERROR("TLM-2", "Invalid command");

	// Response status
	trans.set_response_status( tlm::TLM_OK_RESPONSE );
}

void Subtractor::threadSendError() {

	float_pid error;

	while(true) {

		wait();

		error = s_setpoint - s_output;
	    sc_time delay = sc_time(SC_ZERO_TIME);
	    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;

		trans->set_command( tlm::TLM_WRITE_COMMAND );
		trans->set_data_ptr( reinterpret_cast<unsigned char*>(&error) );
		trans->set_data_length( sizeof(float_pid) );
		trans->set_streaming_width( sizeof(float_pid) );
		trans->set_dmi_allowed( false );
		trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

		// Transport call
		initError->b_transport( *trans, delay );

		// Check response status and delay
		if ( trans->is_response_error() )
			SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
		wait(delay);
	}

}
