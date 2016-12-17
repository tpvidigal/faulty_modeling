/**
 * @file    tb_System_Matlab.hpp
 * @brief   TLM Testbench of the System using Matlab data header
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
 * 1.0      2016/09/21  TVIDIGAL     Document adapted from tb_PID_Matlab.hpp
 *
 *----------------------------------------------------------------------------*/

#ifndef TB_SYSTEM_MATLAB_H_
#define TB_SYSTEM_MATLAB_H_

#include <systemc.h>
#include "Stimulus.hpp"
#include "Monitor.hpp"
#include "../../hdr/Control_System.hpp"
#include "../../hdr/PIDSimplex.hpp"
#include "../../hdr/PIDTMR.hpp"
#include "../../hdr/PIDTMRSimplex.hpp"

SC_MODULE(tb_System_Matlab) {

	public:


	/* Methods ************************************************************/

		///Default constructor
		SC_CTOR(tb_System_Matlab);


	private:

	/* Fields *************************************************************/

		Stimulus stim;
		PID *pid;
		Control_System *dut;
		Monitor mon;

		sc_event start_tb;

	/* Methods ************************************************************/

		void doTestbench();

};

#endif /* TB_SYSTEM_MATLAB_H_ */
