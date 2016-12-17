/**
 * @file    tb_Reliability.cpp
 * @brief   Testbench to validate reliability of PIDs source
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
 * 1.0      2016/11/12  TVIDIGAL     Document created.
 *
 *----------------------------------------------------------------------------*/

#include "tb_Reliability.hpp"
 
SC_HAS_PROCESS(tb_Reliability);


/* Public ********************************************************************/

//Constructor
tb_Reliability::tb_Reliability(sc_module_name inst) : sc_module(inst),

	stim("Stimulus"),
	mon("Monitor"),
	fi_manager("FaultManager")

{
	cout << "Constructing Reliab\t" << name() << endl;

	pid = new PIDSimplex("PIDCoreSimplex");
	mon.setPIDImplementationName("Simplex");

	dut = new PID_TLM("DUT", pid);
	stim.initError.bind( dut->trgtError );
	dut->initGain.bind( mon.trgtGain );

	SC_THREAD(doTestbench);
}

void tb_Reliability::doTestbench() {

	cout << "\n######################## START ########################\n\n" << flush;
	while(true) {

		fi_manager.inject_faults.notify(SC_ZERO_TIME);

		//Send stimulus
		stim.send_event.notify(SC_ZERO_TIME);
		wait(CLK_PERIOD*1000, SC_MS);
	}
}
