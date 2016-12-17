/**
 * @file    PIDTMRSimplexSimplex.cpp
 * @brief   PID in TMR/Simplex Controller source
 *
 * @author  Tiago Pereira Vidigal
 * @version 2.1
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/09/24  TVIDIGAL     File created and base created
 * 2.0      2016/10/03  TVIDIGAL     The change of sc_in to sc_buffer made me
 *                                   change doPID to write at internal PIDs, so
 *                                   they receive the error. This class now
 *                                   derives from PIDTMR
 * 2.1      2016/11/12  TVIDIGAL     Corrected output treatment and added delta
 *                                   delay in the notifies of sendGainsToVoter
 *
 *----------------------------------------------------------------------------*/

#include "../hdr/PIDTMRSimplex.hpp"
SC_HAS_PROCESS(PIDTMRSimplex);


/* Public ********************************************************************/

PIDTMRSimplex::PIDTMRSimplex(sc_module_name inst) : PIDTMR(inst) {
	this->use_voter = true;
}


/* Private *******************************************************************/

void PIDTMRSimplex::sendGainsToVoter() {
	s_gain_0.write(pid_0.gain.read());
	s_gain_1.write(pid_1.gain.read());
	s_gain_2.write(pid_2.gain.read());

	if(use_voter)
		voter.voter_start.notify(SC_ZERO_TIME);
	else
		voter.voter_ends.notify(SC_ZERO_TIME);
}

void PIDTMRSimplex::sendOutputGain() {

	static int first_PID_to_fail = -1;

	//Check if the first PID had an error
	if(first_PID_to_fail == -1) {
		if     (voter.isPID0WithError()) first_PID_to_fail =  0;
		else if(voter.isPID1WithError()) first_PID_to_fail =  1;
		else if(voter.isPID2WithError()) first_PID_to_fail =  2;
		else                             first_PID_to_fail = -1;
	}

	//With the first PID failed, the failed and one of the working PIDs "removed"
	//That way, only one working PID will be used after the first fails
	switch(first_PID_to_fail) {
	case -1: 
		this->gain.write(s_gain_0.read());
		break;
	case  0: this->gain.write(s_gain_1.read()); break;
	case  1: this->gain.write(s_gain_0.read()); break;
	case  2: this->gain.write(s_gain_0.read()); break;
	}
}