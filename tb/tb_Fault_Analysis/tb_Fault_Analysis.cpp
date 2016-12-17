/**
 * @file    tb_Fault_Analysis.cpp
 * @brief   Testbench to check time to fail of PID implementations source
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

#include "tb_Fault_Analysis.hpp"
 
SC_HAS_PROCESS(tb_Fault_Analysis);


/* Public ********************************************************************/

//Constructor
tb_Fault_Analysis::tb_Fault_Analysis(sc_module_name inst) : sc_module(inst) {

	cout << "Constructing Fault TB\t" << name() << endl;

	SC_THREAD(doTestbench);
}

void tb_Fault_Analysis::doTestbench() {

	// Variables to fault analysis
	ofstream fsimplex;
	ofstream ftmr;
	ofstream ftmrsimplex;
	double   time_to_fail;
	double   min, aux;

	// Iterate all types of PID
	fsimplex.open   ("tb/tb_Fault_Analysis/time_to_fail_Simplex.txt"    );
	ftmr.open       ("tb/tb_Fault_Analysis/time_to_fail_TMR.txt"        );
	ftmrsimplex.open("tb/tb_Fault_Analysis/time_to_fail_TMRSimplex.txt" );

	// Create N time to fail values, N being fault_loops
	for(unsigned long i=0; i<fault_loops; i++) {

		/* Simplex case *****************************************/

		//time to fail = time to inject
		time_to_fail = getTimeToInject();
		fsimplex << time_to_fail << "\n";


		/* TMR case *********************************************/

		//: time to fail = second minimum time to inject
		min = getTimeToInject();
		time_to_fail = min;
		//Define who is second minimum
		aux = getTimeToInject();
		if(aux < min) min = aux;
		else time_to_fail = aux;
		//Define if there's new second minimum
		aux = getTimeToInject();
		if(aux < min) time_to_fail = min;
		else if(aux < time_to_fail) time_to_fail = aux;
		ftmr << time_to_fail << "\n";


		/* TMRSimplex case **************************************/

		//time to fail = random time to inject after minimum
		min = getTimeToInject();
		time_to_fail = min;
		//Define who is second minimum
		aux = getTimeToInject();
		if(aux > min) time_to_fail = aux;
		ftmrsimplex << time_to_fail << "\n";
		wait(SC_ZERO_TIME);
	}

	fsimplex.close();
	ftmr.close();
	ftmrsimplex.close();
	sc_stop();
}

double tb_Fault_Analysis::getTimeToInject() {
	return ((5 + distribution(generator))*1000);
}
