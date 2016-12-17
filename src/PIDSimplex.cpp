/**
 * @file    PIDSimplex.cpp
 * @brief   PID Simplex Controller source
 *
 * @author  Tiago Pereira Vidigal
 * @version 3.0
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/04/21  TVIDIGAL     File created and base constructed
 * 1.1      2016/04/26  TVIDIGAL     Using PID_constants, b_transport created
 *                                   and validated calculateGain
 * 1.2      2016/05/03  TVIDIGAL     Minor fixes
 * 1.3      2016/07/13  TVIDIGAL     Adapted to RTL model style and using
 *                                   float_pid instead of bit precise types
 * 1.4      2016/07/14  TVIDIGAL     Transformed into derived class PID Simplex
 * 2.0      2016/08/13  TVIDIGAL     doPID -> calcPID (change at base class)
 * 2.1      2016/08/24  TVIDIGAL     Using same PID equation as Prof. Muñoz
 *                                   and implementing everything of the PID
 *                                   in the doPID() method and making
 *                                   improvements using brettbeauregard.com's
 *                                   "Improving The Beginner's PID" articles
 * 3.0      2016/11/02  TVIDIGAL     Setting stuck-at 0 fault
 *
 *----------------------------------------------------------------------------*/

#include "../hdr/PIDSimplex.hpp"
SC_HAS_PROCESS(PIDSimplex);


/* Public ********************************************************************/

PIDSimplex::PIDSimplex(sc_module_name inst) : PID(inst) { 

	setCoeffs(KP_DEFAULT, KI_DEFAULT, KD_DEFAULT);
	gain.setFault(STUCK_AT_0);
}

void PIDSimplex::setCoeffs(float_pid kp, float_pid ki, float_pid kd) {

	this->kp = kp;
	this->ki = ki;
	this->kd = kd;
}


/* Private *******************************************************************/

void PIDSimplex::doPID() {

	float_pid v_gain;
	float_pid kp_error, ki_error, kd_error;
	
	//Read error and prepare for calculation
	kp_error = this->error.read();

	//ki_error = this->error_int += kp_error;
	ki_error = kp_error + this->error_old;
	kd_error = kp_error - this->error_old;

	//Calculate gain
	v_gain  = kp_error * this->kp;
	v_gain += ki_error * this->ki;
	v_gain += kd_error * this->kd;

	//Update old error and send gain
	this->error_old = kp_error;
	gain.write(v_gain);
}