/**
 * @file    tb_Plant.hpp
 * @brief   TLM Testbench of the Plant using Matlab data header
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
 * 1.0      2016/10/17  TVIDIGAL     Document adapted from tb_Control_System.hpp
 *
 *----------------------------------------------------------------------------*/

#ifndef TB_PLANT_H_
#define TB_PLANT_H_

#include <systemc.h>
#include "Stimulus.hpp"
#include "Monitor.hpp"
#include "../../hdr/Plant.hpp"

SC_MODULE(tb_Plant) {

	public:


	/* Methods ************************************************************/

		///Default constructor
		SC_CTOR(tb_Plant);


	private:

	/* Fields *************************************************************/

		Stimulus stim;
		Plant    dut;
		Monitor  mon;

		sc_event start_tb;

	/* Methods ************************************************************/

		void doTestbench();

};

#endif /* TB_PLANT_H_ */
