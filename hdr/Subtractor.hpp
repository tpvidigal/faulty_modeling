/**
 * @file    Subtractor.hpp
 * @brief   Subtractor of the control system header
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.4
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/08/17  TVIDIGAL     Document created.
 * 1.1      2016/08/24  TVIDIGAL     Adding setpoint and output signals.
 * 1.2      2016/09/24  TVIDIGAL     Correcting methodSendError name (to thread)
 * 1.3      2016/10/01  TVIDIGAL     Setpoint transport defines iteration of
 *                                   subtractor (output only changes variable)
 * 1.4      2016/11/21  TVIDIGAL     Changed SystemC class macro for Doxygen
 *
 *----------------------------------------------------------------------------*/

#ifndef SUBTRACTOR_H_
#define SUBTRACTOR_H_

#include <systemc.h>
#include "PID_constants.hpp"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

using namespace tlm;
using namespace tlm_utils;


///Class that models the subtractor of a control system
class Subtractor : public sc_module {

	public:

		/* Ports *****************************************************************/

		///Socket: Error of the system
		simple_initiator_socket<Subtractor> initError;

		///Target: Setpoint of the system
		simple_target_socket<Subtractor> trgtSetpoint;

		///Target: Output of the system
		simple_target_socket<Subtractor> trgtOutput;


		/* Methods ************************************************************/

		///Default constructor
		SC_CTOR(Subtractor);

	private:

		/* Signals ************************************************************/

		///Indicates that gain was computed
		sc_event ev_error;

		///Setpoint of the system
		float_pid s_setpoint;

		///Output of the plant
		float_pid s_output;


		/* Methods ************************************************************/

		/**
          * @brief Transport method of the trgtSetpoint
          * @param trans Transport payload pointer
          * @param delay Delay of the transport
          */
		void b_trans_setvalue(tlm_generic_payload& trans, sc_time& delay);

		/**
          * @brief Transport method of the trgtOutput
          * @param trans Transport payload pointer
          * @param delay Delay of the transport
          */
		void b_trans_output(tlm_generic_payload& trans, sc_time& delay);

		///Transport method for initError
		void threadSendError();
};

#endif /* SUBTRACTOR_H_ */