/**
 * @file    tb_PID_Matlab.hpp
 * @brief   TLM Testbench of the PID using Matlab data
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
 * 2.0      2016/11/09  TVIDIGAL     Adding Fault Injection model
 *
 *----------------------------------------------------------------------------*/

#ifndef TB_PID_MATLAB_H_
#define TB_PID_MATLAB_H_

#include <systemc.h>
#include "Stimulus.hpp"
#include "Monitor.hpp"
#include "../../hdr/PID_TLM.hpp"
#include "../../hdr/PIDSimplex.hpp"
#include "../../hdr/PIDTMR.hpp"
#include "../../hdr/PIDTMRSimplex.hpp"
#include "../../hdr/FaultManager.hpp"

SC_MODULE(tb_PID_Matlab) {

	public:


	/* Methods ************************************************************/

		///Default constructor
		SC_CTOR(tb_PID_Matlab);


	private:

	/* Fields *************************************************************/

		Stimulus stim;
		PID *pid;
		PID_TLM *dut;
		Monitor mon;

		sc_event start_tb;

		FaultManager fi_manager;
		bool enable_faults;


	/* Methods ************************************************************/

		void doTestbench();

};

#endif /* TB_PID_MATLAB_H_ */
