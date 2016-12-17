/**
 * @file    Actuator.hpp
 * @brief   Actuator of the control system header
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.1
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/10/17  TVIDIGAL     Document created.
 * 1.1      2016/11/21  TVIDIGAL     Changed SystemC class macro for Doxygen
 *
 *----------------------------------------------------------------------------*/

#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <systemc.h>
#include "PID_constants.hpp"
#include "Matrix.hpp"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

using namespace tlm;
using namespace tlm_utils;
using namespace std;

///Actuator of the system's Plant
class Actuator: public sc_module {

	public:

		/* Ports **************************************************************/

		///Socket: PID's gain
		simple_initiator_socket<Actuator> initGain;

		///Target: Gain to compute output
		simple_target_socket<Actuator> trgtGain;


		/* Methods ************************************************************/

		///Default constructor
		SC_CTOR(Actuator);


	private:

		/* Fields *************************************************************/

		// Gain received from PID
		float_pid gain;

		// Gain sent/to send to Plant
		float_pid output_gain;

		///Event that triggers the send output method
		sc_event send_output;


		/* Methods ************************************************************/

		/**
          * @brief Transport method of the trgtGain
          * @param trans Transport payload pointer
          * @param delay Delay of the transport
          */
		void doActuator(tlm_generic_payload& trans, sc_time& delay);

		///Transport method for initGain
		void threadSendGain();

		/**
		 * @brief  Compute the gain after actuator losses
		 * @return The output gain
		 */
		float_pid computeGain();
};

#endif /* ACTUATOR_H_ */