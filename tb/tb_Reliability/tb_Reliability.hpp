/**
 * @file    tb_Reliability.hpp
 * @brief   Testbench to validate reliability of PIDs header
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

#ifndef TB_RELIABILITY_H_
#define TB_RELIABILITY_H_

#include <systemc.h>
#include "Stimulus.hpp"
#include "Monitor.hpp"
#include "../../hdr/PID_TLM.hpp"
#include "../../hdr/PIDSimplex.hpp"
#include "../../hdr/PIDTMR.hpp"
#include "../../hdr/PIDTMRSimplex.hpp"
#include "../../hdr/FaultManager.hpp"

SC_MODULE(tb_Reliability) {

	public:


	/* Methods ************************************************************/

		///Default constructor
		SC_CTOR(tb_Reliability);


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

#endif /* TB_RELIABILITY_H_ */
