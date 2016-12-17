/**
 * @file    PIDSimplex.hpp
 * @brief   PID Simplex Controller header
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
 * 1.0      2016/04/21  TVIDIGAL     File created and base constructed
 * 1.1      2016/04/26  TVIDIGAL     Using PID_constants and b_transport created
 * 1.2      2016/05/03  TVIDIGAL     Minor fixes
 * 1.3      2016/07/12  TVIDIGAL     Adapted to RTL model style
 * 1.4      2016/07/13  TVIDIGAL     Using float_pid instead of bit precise types
 * 1.5      2016/07/14  TVIDIGAL     Transformed into derived class PID Simplex
 * 2.0      2016/08/13  TVIDIGAL     doPID -> calcPID (change at base class)
 * 2.1      2016/08/24  TVIDIGAL     Removing method for extern "C" call because
 *                                   UVM Connect appears to be better than the
 *                                   technique at the Cadence's RAK and making
 *                                   improvements using brettbeauregard.com's
 *                                   "Improving The Beginner's PID" articles
 *
 *----------------------------------------------------------------------------*/

#ifndef PIDSIMPLEX_H_
#define PIDSIMPLEX_H_

#include "PID.hpp"

///Simplex implementation of PID
class PIDSimplex: public PID {

	public:

	/* Methods ***************************************************************/

		///Default constructor
		SC_CTOR(PIDSimplex);

    	///Set the coefficients of the single PID controller
        void setCoeffs(float_pid kp, float_pid ki, float_pid kd);

	private:

	/* Methods ***************************************************************/

		///Execute PID in simplex mode
		void doPID();
		
};

#endif /* PIDSIMPLEX_H_ */
