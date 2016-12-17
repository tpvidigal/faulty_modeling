/**
 * @file    tb_Fault_Analysis.hpp
 * @brief   Testbench to check time to fail of PID implementations header
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
 * 1.0      2016/11/11  TVIDIGAL     Creating fault analysis to check time to
 *                                   fail of the PID implementations
 *
 *----------------------------------------------------------------------------*/

#ifndef TB_FAULT_ANALYSIS_H_
#define TB_FAULT_ANALYSIS_H_

#include <systemc.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <random>
#include "../../hdr/PID.hpp"
#include "../../hdr/PIDSimplex.hpp"
#include "../../hdr/PIDTMR.hpp"
#include "../../hdr/PIDTMRSimplex.hpp"
#include "../../hdr/FaultDatabase.hpp"

using namespace std;


SC_MODULE(tb_Fault_Analysis) {

	public:

	/* Fields *************************************************************/

		unsigned long fault_loops;


	/* Methods ************************************************************/

		///Default constructor
		SC_CTOR(tb_Fault_Analysis);


	private:

	/* Fields *************************************************************/

  		default_random_engine generator;

  		exponential_distribution<double> distribution;


	/* Methods ************************************************************/

		void doTestbench();
		double getTimeToInject();

};

#endif /* TB_FAULT_ANALYSIS_H_ */
