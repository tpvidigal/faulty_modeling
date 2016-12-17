/**
 * @file    tb_PID_Matlab.hpp
 * @brief   TLM Testbench of the PID using Matlab data source
 *
 * @author  Tiago Pereira Vidigal
 * @version 2.0
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/09/02  TVIDIGAL     Document created.
 * 2.0      2016/10/17  TVIDIGAL     Adapted to correct PID
 *
 *----------------------------------------------------------------------------*/

#include "tb_PID_Matlab.hpp"
 
SC_HAS_PROCESS(tb_PID_Matlab);


/* Public ********************************************************************/

//Constructor
tb_PID_Matlab::tb_PID_Matlab(sc_module_name inst) : sc_module(inst),

	stim("Stimulus"),
	mon("Monitor"),
	fi_manager("FaultManager")

{
	enable_faults = true;

	cout << "Constructing PID TB\t" << name();
	if(enable_faults) cout << " (Faults enabled)";
	cout << endl;

	pid = new PIDTMR("PIDCoreTMR");
	dut = new PID_TLM("DUT", pid);
	stim.initError.bind( dut->trgtError );
	dut->initGain.bind( mon.trgtGain );

	SC_THREAD(doTestbench);
}

void tb_PID_Matlab::doTestbench() {

	cout << "\n######################## START ########################\n\n" << flush;
	while(true) {

		//Inject faults (if enabled)
		if(enable_faults)
			fi_manager.inject_faults.notify(SC_ZERO_TIME);

		//Send stimulus
		stim.send_event.notify(SC_ZERO_TIME);
		wait(CLK_PERIOD*1000, SC_MS);
	}
}
