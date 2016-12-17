/**
 * @file    Monitor.cpp
 * @brief   System Monitor for Reliability source
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
 * 1.0      2016/11/12  TVIDIGAL     Document created
 *
 *----------------------------------------------------------------------------*/

 
#include "Monitor.hpp"
SC_HAS_PROCESS(Monitor);


/* Public ********************************************************************/

//Constructor
Monitor::Monitor(sc_module_name inst) : sc_module(inst),

	trgtGain("TrgtGain")

{
	cout << "Constructing Monitor\t" << name() << endl;

	fout.open("tb/tb_Reliability/gain.txt");
	trgtGain.register_b_transport(this, &Monitor::doMonitor);

}

void Monitor::setPIDImplementationName(string name) {
	output_file_name  = "tb/tb_Reliability/time_to_fail_";
	output_file_name += name;
	output_file_name += ".txt";
}


/* Private ********************************************************************/

void Monitor::doMonitor(tlm::tlm_generic_payload& trans, sc_time& delay) {

	tlm::tlm_command cmd = trans.get_command();
	unsigned char*   ptr = trans.get_data_ptr();
	unsigned int     len = trans.get_data_length();
	unsigned int     wid = trans.get_streaming_width();
	float_pid        gain;

	// Validate payload
	if ( wid != len || len != sizeof(float_pid) )
		SC_REPORT_ERROR("TLM-2", "Invalid payload transaction");

	// Commands
	if ( cmd == tlm::TLM_WRITE_COMMAND ) {
		memcpy(&(gain), ptr, len);
		checkOutput(gain);
	}
	else
		SC_REPORT_ERROR("TLM-2", "Invalid command");

	// Response status
	trans.set_response_status( tlm::TLM_OK_RESPONSE );
	check_done.notify(100, SC_MS);
}

void Monitor::checkOutput(float_pid gain) {

	float_pid exp_output;

	cout << "-> Receiving gain (";
	printf("%f", gain);
	cout << ") -> " << flush;

	if(fout.is_open()) {

		if (fout >> exp_output) {

			//If error occurred, PID failed
	    	if( (gain-exp_output)>ERROR_PID || (gain-exp_output)<(-1*ERROR_PID) ) {
	    		cout << "Should be ";
	    		printf("%f", exp_output);

	    		//Record time to fail and exit
				fresult.open(output_file_name, ofstream::app);	
	    		if(fresult.is_open()) fresult << (sc_time_stamp().to_seconds()*1000) << "\n";
    			sc_stop();
	    	}
			else 
				cout << "Value OK!";
		}

	    else {
    		cout << " << File ended >> ";
    		sc_stop();
	    }
	}
}
