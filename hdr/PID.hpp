/**
 * @file    PID.hpp
 * @brief   Proportional-Integral-Derivative (PID) Controller header
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
 * 1.0      2016/07/14  TVIDIGAL     Super class created for the PIDs.
 * 2.0      2016/08/11  TVIDIGAL     Added methods for SystemVerilog wrapper
 * 2.1      2016/08/12  TVIDIGAL     All methods for SV wrapper implemented
 * 2.2      2016/08/13  TVIDIGAL     doPID now calls calcPID (change was made
 *                                   so and extern "C" call can get the gain)
 *                                   and divided DPI and PID things
 * 2.3      2016/08/24  TVIDIGAL     Correcting PID about time informations
 *                                   and removing method for extern "C" call
 *                                   because UVM Connect appears to be better
 *                                   than the technique at the Cadence's RAK
 * 2.4      2016/10/02  TVIDIGAL     Changing ports to sc_buffer, once sc_in
 *                                   only notify an event at value changes
 * 3.0      2016/11/02  TVIDIGAL     Changing buffers to faulty buffers
 * 3.1      2016/11/21  TVIDIGAL     Changed SystemC class macro for Doxygen
 *
 *----------------------------------------------------------------------------*/

#ifndef PID_H_
#define PID_H_

#include <systemc.h>
#include "PID_constants.hpp"
#include "FaultyBuffer.hpp"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

///Base class for PID implementations
class PID : public sc_module {

	public:

		/* Ports *****************************************************************/

		///Input: Error of the plant
		sc_buffer<float_pid> error;

		///Output: Gain of the PID
		FaultyBuffer gain;


		/* Methods ***************************************************************/

		///Default constructor
		SC_CTOR(PID);

        /**
         * @brief Set coefficients
         * @param kp Proportional coefficient
         * @param ki Integral coefficient
         * @param kd Derivative coefficient 
         */
        virtual void setCoeffs(float_pid kp, float_pid ki, float_pid kd) = 0;


	protected:

		/* Attributes ************************************************************/

		///Proporcional coefficient
		float_pid kp;

		///Integral coefficient
		float_pid ki;

		///Derivative coefficient
		float_pid kd;

		///Old error of the controller
		float_pid error_old;


		/* Methods ***************************************************************/

		///Calculate and send gain of the PID
		virtual void doPID() = 0;
		
};

#endif /* PID_H_ */

