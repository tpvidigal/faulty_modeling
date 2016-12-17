/**
 * @file    main.cpp
 * @brief   Main method of the Fault Analysis testbench
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.0
 * 
 * This testbench generates faults and times to inject them. An analysis of
 * the time to fail is performed and stored in a file.
 * 
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/11/11  TVIDIGAL     Document created based on tb_PID_Matlab
 *
 *----------------------------------------------------------------------------*/

#include <systemc.h>
#include <cstdio>
#include "tb_Fault_Analysis.hpp"


/* Main **********************************************************************/

///Start simulation
int sc_main(int argc, char* argv[]) {

	tb_Fault_Analysis tb("Fault_Analysis");
	tb.fault_loops    = 1000;

	sc_start();

	return 0;
}
