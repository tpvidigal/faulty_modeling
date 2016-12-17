/**
 * @file    Monitor.hpp
 * @brief   System Monitor header
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


#ifndef MONITOR_H_
#define MONITOR_H_

#include <systemc.h>
#include <iostream>
#include <fstream>
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "../../hdr/PID_constants.hpp"

using namespace tlm_utils;
using namespace std;


SC_MODULE(Monitor) {

	public:

		/* Ports **************************************************************/

		///Socket: Receive output
		simple_target_socket<Monitor> trgtOutput;


		/* Fields *************************************************************/

		sc_event check_done;


		/* Methods ************************************************************/

		///Default constructor
		SC_CTOR(Monitor);


	private:

		/* Fields *************************************************************/

		ifstream fout;
		ofstream fresult;
		ofstream fmean;

		float_pid mean;
		float_pid max;
		float_pid min;
		
		unsigned int error_count;


		/* Methods ************************************************************/

		void doMonitor(tlm::tlm_generic_payload& trans, sc_time& delay);
		void checkOutput(float_pid output);
};

#endif /* MONITOR_H_ */