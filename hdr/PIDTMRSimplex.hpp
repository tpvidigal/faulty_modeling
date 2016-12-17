/**
 * @file    PIDTMRSimplex.hpp
 * @brief   PID in TMR/Simplex Controller header
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
 * 1.0      2016/09/24  TVIDIGAL     File created and base created
 * 2.0      2016/10/02  TVIDIGAL     The change of sc_in to sc_buffer made me
 *                                   change doPID to write at internal PIDs, so
 *                                   they receive the error. This class now
 *                                   derives from PIDTMR
 *
 *----------------------------------------------------------------------------*/

#ifndef PIDTMRSIMPLEX_H_
#define PIDTMRSIMPLEX_H_

#include "PID.hpp"
#include "PIDSimplex.hpp"
#include "PIDTMR.hpp"
#include "Voter.hpp"

///TMR/Simplex implementation of PID
class PIDTMRSimplex: public PIDTMR {

	public:

	/* Methods ***************************************************************/

		///Default constructor
		SC_CTOR(PIDTMRSimplex);

	private:

	/* Signals ***************************************************************/

		///Indicates that voter should be used
		bool use_voter;

	/* Methods ***************************************************************/

		///Send gains to the voter
		void sendGainsToVoter();

		///Send output gain
		void sendOutputGain();

};

#endif /* PIDTMRSIMPLEX_H_ */
