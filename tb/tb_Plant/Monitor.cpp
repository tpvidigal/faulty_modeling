/**
 * @file    Monitor.cpp
 * @brief   Plant Monitor source
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
 * 1.0      2016/10/17  TVIDIGAL     Document adapted from Control System TB's
 *
 *----------------------------------------------------------------------------*/

 
#include "Monitor.hpp"
SC_HAS_PROCESS(Monitor);


/* Public ********************************************************************/

//Constructor
Monitor::Monitor(sc_module_name inst) : sc_module(inst),

	trgtOutput("TrgtOutput"),
	trgtFeedback("TrgtFeedback")

{
	cout << "Constructing Monitor\t" << name() << endl;
	mean = max = min = 0;
	error_count = 0;

	fout.open("tb/tb_Plant/output.txt");
	fresult.open("tb/tb_Plant/result.txt");	
	fmean.open("tb/tb_Plant/mean.txt");	
	trgtOutput.register_b_transport(this, &Monitor::doMonitor);
	trgtFeedback.register_b_transport(this, &Monitor::dummy);

}


/* Private ********************************************************************/

void Monitor::doMonitor(tlm::tlm_generic_payload& trans, sc_time& delay) {

	tlm::tlm_command cmd = trans.get_command();
	unsigned char*   ptr = trans.get_data_ptr();
	unsigned int     len = trans.get_data_length();
	unsigned int     wid = trans.get_streaming_width();
	float_pid        output;

	// Validate payload
	if ( wid != len || len != sizeof(float_pid) )
		SC_REPORT_ERROR("TLM-2", "Invalid payload transaction");

	// Commands
	if ( cmd == tlm::TLM_WRITE_COMMAND ) {
		memcpy(&(output), ptr, len);
		checkOutput(output);
	}
	else
		SC_REPORT_ERROR("TLM-2", "Invalid command");

	// Response status
	trans.set_response_status( tlm::TLM_OK_RESPONSE );
	check_done.notify(100, SC_MS);
}

void Monitor::checkOutput(float_pid output) {

	float_pid exp_output;
	float_pid aux;
	int index = 0;

	cout << "-> Receiving output (";
	printf("%f", output);
	cout << ") -> " << flush;

	if(fout.is_open()) {

		if (fout >> exp_output) {

			if(fresult.is_open()) {
				fresult << output << "\n";
				aux = output - exp_output;
				mean += aux;
				index++;
				if(max<aux) max = aux;
				if(min>aux) min = aux;
				if(fmean.is_open())
					fmean << "Mean: " << mean/index << "\tMin: " << min << "\tMax: " << max << "\n" << flush;
			}

	    	if( (output-exp_output)>ERROR_PLANT || (output-exp_output)<(-1*ERROR_PLANT) ) {
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

void Monitor::dummy(tlm::tlm_generic_payload& trans, sc_time& delay) {
	trans.set_response_status( tlm::TLM_OK_RESPONSE );
}