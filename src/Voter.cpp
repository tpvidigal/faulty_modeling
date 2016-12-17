/**
 * @file    Voter.cpp
 * @brief   Voter for the Triple Modular Redundance Controller source
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
 * 3.1      2016/11/12  TVIDIGAL     Added "If no error in any PID" block at
 *                                   doVoter method
 *
 *----------------------------------------------------------------------------*/

#include "../hdr/Voter.hpp"

/* Public *********************************************************************/

Voter::Voter(sc_module_name inst) : sc_module(inst) {
	cout << "Constructing Voter \t" << name() << endl;
	
	errorInPID0 = false;
	errorInPID1 = false;
	errorInPID2 = false;

	SC_METHOD(doVoter);
	sensitive << voter_start;
	dont_initialize();
}

bool Voter::isPID0WithError() {
	return errorInPID0;
}

bool Voter::isPID1WithError() {
	return errorInPID1;
}

bool Voter::isPID2WithError() {
	return errorInPID2;
}


/* Private ********************************************************************/

void Voter::doVoter() {

	float_pid gain_0, gain_1, gain_2;
	bool eq_01, eq_02, eq_12;

	// Gains read
	gain_0 = this->gain_0.read();
	gain_1 = this->gain_1.read();
	gain_2 = this->gain_2.read();

	// Gains equality analysis
	eq_01 = eq_02 = eq_12 = true;

	// If PID0 already had an error
	if(this->errorInPID0) {
		eq_01 = eq_02 = false;
		if(gain_1 != gain_2)
			eq_12 = false;
	}

	// If PID1 already had an error
	if(this->errorInPID1) {
		eq_01 = eq_12 = false;
		if(gain_0 != gain_2)
			eq_02 = false;
	}

	// If PID2 already had an error
	if(this->errorInPID2) {
		eq_02 = eq_12 = false;
		if(gain_0 != gain_1)
			eq_01 = false;
	}

	//No error in any PID
	if(!errorInPID0 && !errorInPID1 && !errorInPID2) {
		if(gain_0 != gain_1) eq_01 = false;
		if(gain_0 != gain_2) eq_02 = false;
		if(gain_1 != gain_2) eq_12 = false;
	}

	//Errors check
	if(eq_01) {
		if(!eq_02)
			this->errorInPID2 = true;
	}

	else if(eq_02) {
		this->errorInPID1 = true;
	}

	else if(eq_12) {
		this->errorInPID0 = true;
	}

	else {
		this->errorInPID0 = true;
		this->errorInPID1 = true;
		this->errorInPID2 = true;
	}

	voter_ends.notify(SC_ZERO_TIME);
}
