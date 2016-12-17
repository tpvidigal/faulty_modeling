/**
 * @file    tb_Actuator.hpp
 * @brief   TLM Testbench of the Actuator using Matlab data source
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
 * 1.0      2016/10/17  TVIDIGAL     Document adapted from tb_Plant.cpp
 *
 *----------------------------------------------------------------------------*/

#include "tb_Actuator.hpp"
 
SC_HAS_PROCESS(tb_Actuator);


/* Public ********************************************************************/

//Constructor
tb_Actuator::tb_Actuator(sc_module_name inst) : sc_module(inst),

	stim("Stimulus"),
	dut("Actuator"),
	mon("Monitor")

{
	cout << "Constructing TB Act\t" << name() << endl;

	stim.initGain.bind( dut.trgtGain );
	dut.initGain.bind( mon.trgtGain );

	SC_THREAD(doTestbench);
}

void tb_Actuator::doTestbench() {

	cout << "\n######################## START ########################\n\n" << flush;
	while(true) {
		stim.send_event.notify(SC_ZERO_TIME);
		wait(CLK_PERIOD*1000, SC_MS);
	}
}
