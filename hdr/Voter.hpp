/**
 * @file    Voter.hpp
 * @brief   Voter for the Triple Modular Redundance Controller header
 *
 * @author  Tiago Pereira Vidigal
 * @version 3.1
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/09/23  TVIDIGAL     File created and base created
 * 2.0      2016/09/24  TVIDIGAL     Voter checks which PID is with error and
 *                                   store it.
 * 3.0      2016/10/02  TVIDIGAL     Voter only checks the PIDs, don't choose
 *                                   the ouput of the top level PID. There is
 *                                   no chance that a PID marked with error be
 *                                   dismarked aftewards (no-recovery faults)
 * 3.1      2016/11/21  TVIDIGAL     Changed SystemC class macro for Doxygen
 *
 *----------------------------------------------------------------------------*/

#ifndef VOTER_H_
#define VOTER_H_

#include <systemc.h>
#include "PID_constants.hpp"

///Voter of TMR implementations
class Voter : public sc_module {

	public:

	/* Ports *****************************************************************/

		///Gain of the PID 0
		sc_in<float_pid> gain_0;

		///Gain of the PID 1
		sc_in<float_pid> gain_1;

		///Gain of the PID 2
		sc_in<float_pid> gain_2;

		///Event that indicates voter must act
		sc_event voter_start;

		///Event that indicates end of the voter
		sc_event voter_ends;


	/* Methods ***************************************************************/

		///Default constructor
		SC_CTOR(Voter);

		///Check if PID 0 had an error identified
		bool isPID0WithError();

		///Check if PID 1 had an error identified
		bool isPID1WithError();

		///Check if PID 2 had an error identified
		bool isPID2WithError();


	private:

	/* Properties ************************************************************/

		bool errorInPID0;
		bool errorInPID1;
		bool errorInPID2;


	/* Methods ***************************************************************/

		///Execute Voter
		void doVoter();
		
};

#endif /* VOTER_H_ */
