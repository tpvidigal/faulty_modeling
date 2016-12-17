/**
 * @file    PIDTMR.hpp
 * @brief   PID in Triple Modular Redundance Controller header
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.2
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/09/23  TVIDIGAL     File created and base created
 * 1.1      2016/10/03  TVIDIGAL     Adapting changes of the voter and of the 
 *                                   PIDSimplex ports (now they are buffers).
 *                                   Making some methods virtual so
 *                                   PIDTMRSimplex can derivate from PIDTMR
 * 1.2      2016/11/21  TVIDIGAL     Changed SystemC class macro for Doxygen
 *
 *----------------------------------------------------------------------------*/

#ifndef PIDTMR_H_
#define PIDTMR_H_

#include "PID.hpp"
#include "PIDSimplex.hpp"
#include "Voter.hpp"

///TMR implementation of PID
class PIDTMR: public PID {

	public:

	/* Methods ***************************************************************/

		///Default constructor
		SC_CTOR(PIDTMR);

    	///Set the coefficients the three PID controllers
        void setCoeffs(float_pid kp, float_pid ki, float_pid kd);

	protected:

	/* Modules ***************************************************************/

		///PID 0 of triple redundancy
		PIDSimplex pid_0;

		///PID 1 of triple redundancy
		PIDSimplex pid_1;

		///PID 2 of triple redundancy
		PIDSimplex pid_2;

		///Voter to check error in PIDs
		Voter voter;


	/* Signals ***************************************************************/

		///Signal to read the PID 0's gain output and send to voter
		sc_signal<float_pid> s_gain_0;

		///Signal to read the PID 1's gain output and send to voter
		sc_signal<float_pid> s_gain_1;
		
		///Signal to read the PID 2's gain output and send to voter
		sc_signal<float_pid> s_gain_2;


	/* Methods ***************************************************************/

		///Execute PID in TMR mode
		void doPID();

		///Send gains to the voter
		virtual void sendGainsToVoter();

		///Send output gain
		virtual void sendOutputGain();
		
};

#endif /* PIDTMR_H_ */
