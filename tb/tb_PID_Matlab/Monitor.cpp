/**
 * @file    Monitor.cpp
 * @brief   System Monitor source
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
 * 1.0      2016/09/21  TVIDIGAL     Document adapted from PID TB's Monitor
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
	mean = max = min = 0;
	error_count = 0;

	fout.open("tb/tb_PID_Matlab/gain.txt");
	fresult.open("tb/tb_PID_Matlab/result.txt");	
	fmean.open("tb/tb_PID_Matlab/mean.txt");	
	trgtGain.register_b_transport(this, &Monitor::doMonitor);

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

	#ifdef BINARY_FILE
		char exp_bin[65];
	#endif
	float_pid exp_output;
	float_pid aux;
	int index = 0;

	cout << "-> Receiving gain (";
	printf("%f", gain);
	cout << ") -> " << flush;

	if(fout.is_open()) {

		#ifdef BINARY_FILE
			fout.getline(exp_bin, sizeof(exp_bin));
			if (fout.good()) {
				exp_output = (float_pid) bin2double(exp_bin);

		#else
			if (fout >> exp_output) {

				if(fresult.is_open()) {
					fresult << gain << "\n";
					aux = gain - exp_output;
					mean += aux;
					index++;
					if(max<aux) max = aux;
					if(min>aux) min = aux;
					if(fmean.is_open())
						fmean << "Mean: " << mean/index << "\tMin: " << min << "\tMax: " << max << "\n" << flush;
				}

		#endif
	    	if( (gain-exp_output)>ERROR_PID || (gain-exp_output)<(-1*ERROR_PID) ) {
	    	//if(gain != exp_output) {
	    		cout << "Should be ";
	    		printf("%f", exp_output);
	    		error_count++;
	    	}
			else 
				cout << "Value OK!";
			
			cout << "\t(Errors: " << error_count << ")" << flush;
		}

	    else {
    		cout << " << File ended >> ";
    		sc_stop();
	    }
	}
}
