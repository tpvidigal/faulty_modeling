/**
 * @file    tb_Plant.hpp
 * @brief   TLM Testbench of the Plant using Matlab data source
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
 * 1.0      2016/10/17  TVIDIGAL     Document adapted from tb_Control_System.cpp
 *
 *----------------------------------------------------------------------------*/

#include "tb_Plant.hpp"
 
SC_HAS_PROCESS(tb_Plant);


/* Public ********************************************************************/

//Constructor
tb_Plant::tb_Plant(sc_module_name inst) : sc_module(inst),

	stim("Stimulus"),
	dut("Plant"),
	mon("Monitor")

{
	cout << "Constructing TB Pla\t" << name() << endl;

	stim.initGain.bind( dut.trgtGain );
	dut.initOut.bind( mon.trgtOutput );
	dut.initFeedback.bind( mon.trgtFeedback );

	SC_THREAD(doTestbench);
}

void tb_Plant::doTestbench() {

	cout << "\n######################## START ########################\n\n" << flush;
	while(true) {
		stim.send_event.notify(SC_ZERO_TIME);
		wait(CLK_PERIOD*1000, SC_MS);
	}
}
