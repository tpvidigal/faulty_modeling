/**
 * @file    Monitor.hpp
 * @brief   System Monitor for Reliability header
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

		///Socket: Receive gain
		simple_target_socket<Monitor> trgtGain;


		/* Fields *************************************************************/

		sc_event check_done;


		/* Methods ************************************************************/

		///Default constructor
		SC_CTOR(Monitor);
		void setPIDImplementationName(string name);


	private:

		/* Fields *************************************************************/

		ifstream fout;
		ofstream fresult;

		string output_file_name;


		/* Methods ************************************************************/

		void doMonitor(tlm::tlm_generic_payload& trans, sc_time& delay);
		void checkOutput(float_pid output);
};

#endif /* MONITOR_H_ */