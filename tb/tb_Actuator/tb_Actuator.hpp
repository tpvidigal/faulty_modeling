/**
 * @file    tb_Actuator.hpp
 * @brief   TLM Testbench of the Actuator using Matlab data header
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
 * 1.0      2016/10/17  TVIDIGAL     Document adapted from tb_Plant.hpp
 *
 *----------------------------------------------------------------------------*/

#ifndef TB_ACTUATOR_H_
#define TB_ACTUATOR_H_

#include <systemc.h>
#include "Stimulus.hpp"
#include "Monitor.hpp"
#include "../../hdr/Actuator.hpp"

SC_MODULE(tb_Actuator) {

	public:


	/* Methods ************************************************************/

		///Default constructor
		SC_CTOR(tb_Actuator);


	private:

	/* Fields *************************************************************/

		Stimulus stim;
		Actuator dut;
		Monitor  mon;

		sc_event start_tb;

	/* Methods ************************************************************/

		void doTestbench();

};

#endif /* TB_ACTUATOR_H_ */
