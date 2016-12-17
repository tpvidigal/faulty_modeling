/**
 * @file    tb_System_Matlab.hpp
 * @brief   TLM Testbench of the System using Matlab data source
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.1
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/09/21  TVIDIGAL     Document adapted from tb_PID_Matlab.cpp
 * 1.1      2016/09/22  TVIDIGAL     Adapted the doTestbench to send and wait
 *                                   signals
 *
 *----------------------------------------------------------------------------*/

#include "tb_System_Matlab.hpp"
 
SC_HAS_PROCESS(tb_System_Matlab);


/* Public ********************************************************************/

//Constructor
tb_System_Matlab::tb_System_Matlab(sc_module_name inst) : sc_module(inst),

	stim("Stimulus"),
	mon("Monitor")

{
	cout << "Constructing TB Sys\t" << name() << endl;

	pid = new PIDTMR("PIDCoreTMR");
	dut = new Control_System("DUT", pid, true);
	stim.initSetpoint.bind( dut->trgtSetpoint );
	dut->initOutput.bind( mon.trgtOutput );

	SC_THREAD(doTestbench);
}

void tb_System_Matlab::doTestbench() {

	cout << "\n######################## START ########################\n\n" << flush;
	while(true) {
		stim.send_event.notify(SC_ZERO_TIME);
		wait(CLK_PERIOD*1000, SC_MS);
	}
}
