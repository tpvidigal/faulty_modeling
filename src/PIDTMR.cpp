/**
 * @file    PIDTMR.cpp
 * @brief   PID in Triple Modular Redundance Controller source
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
 * 1.0      2016/09/23  TVIDIGAL     File created and base created
 * 1.1      2016/10/03  TVIDIGAL     Adapting changes of the voter and of the 
 *                                   PIDSimplex ports (now they are buffers)
 * 2.0      2016/11/11  TVIDIGAL     Correct failed PIDs treatment
 * 2.1      2016/11/12  TVIDIGAL     Fixing bitwise operation with double
 *
 *----------------------------------------------------------------------------*/

#include "../hdr/PIDTMR.hpp"
SC_HAS_PROCESS(PIDTMR);


/* Public ********************************************************************/

PIDTMR::PIDTMR(sc_module_name inst) : PID(inst),

	pid_0("PID_0"),
	pid_1("PID_1"),
	pid_2("PID_2"),
	voter("Voter")

{ 
	setCoeffs(KP_DEFAULT, KI_DEFAULT, KD_DEFAULT);

	SC_METHOD(sendGainsToVoter);
	sensitive << pid_2.gain;
	dont_initialize();

	SC_METHOD(sendOutputGain);
	sensitive << voter.voter_ends;
	dont_initialize();

	voter.gain_0(s_gain_0);
	voter.gain_1(s_gain_1);
	voter.gain_2(s_gain_2);
}

void PIDTMR::setCoeffs(float_pid kp, float_pid ki, float_pid kd) {

	this->kp = kp;
	this->ki = ki;
	this->kd = kd;

	this->pid_0.setCoeffs(kp, ki, kd);
	this->pid_1.setCoeffs(kp, ki, kd);
	this->pid_2.setCoeffs(kp, ki, kd);
}


/* Private *******************************************************************/

void PIDTMR::doPID() {
	float_pid error;

	error = this->error.read();
	pid_0.error.write(error);
	pid_1.error.write(error);
	pid_2.error.write(error);
}

void PIDTMR::sendGainsToVoter() {
	s_gain_0.write(pid_0.gain.read());
	s_gain_1.write(pid_1.gain.read());
	s_gain_2.write(pid_2.gain.read());
	voter.voter_start.notify(SC_ZERO_TIME);
}

void PIDTMR::sendOutputGain() {

	static int first_PID_to_fail = -1;
	float_pid gain0, gain1, gain2;
	unsigned long bits0, bits1, bits2;

	//Check if the first PID had an error
	if(first_PID_to_fail == -1) {
		if     (voter.isPID0WithError()) first_PID_to_fail =  0;
		else if(voter.isPID1WithError()) first_PID_to_fail =  1;
		else if(voter.isPID2WithError()) first_PID_to_fail =  2;
		else                             first_PID_to_fail = -1;
	}

	//If no PID has failed
	if(first_PID_to_fail==-1)
		this->gain.write(s_gain_0.read());
	

	//With the first PID failed, the others are ANDed to the output
	//If another one fails, the AND operation will generate strange output
	else {

		//Read double values
		gain0 = s_gain_0.read();
		gain1 = s_gain_1.read();
		gain2 = s_gain_2.read();

		//And prepare bits to bitwise operation
		memcpy(&bits0, &gain0, sizeof(bits0));
		memcpy(&bits1, &gain1, sizeof(bits1));
		memcpy(&bits2, &gain2, sizeof(bits2));

		//Case the first PID to fail was...
		switch(first_PID_to_fail) {
		case  0: 
			bits1 &= bits2;
			memcpy(&gain1, &bits1, sizeof(gain1));  
			this->gain.write( gain1 );
			break;

		case  1: 
			bits0 &= bits2;
			memcpy(&gain0, &bits0, sizeof(gain0));  
			this->gain.write( gain0 );
			break;

		case  2: 
			bits0 &= bits1;
			memcpy(&gain0, &bits0, sizeof(gain0));  
			this->gain.write( gain0 );
			break;
		}
	}
}
