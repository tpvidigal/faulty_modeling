/**
 * @file    Control_System.hpp
 * @brief   Control System of a Control Surface of an Aircraft header
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
 * 1.0      2016/09/19  TVIDIGAL     Document created.
 * 1.1      2016/09/21  TVIDIGAL     Copying and sending transaction and
 *                                   adding PID type configuration method.
 * 2.0      2016/10/17  TVIDIGAL     Adding actuator
 * 3.0      2016/11/07  TVIDIGAL     Adding Fault Injection model
 * 3.1      2016/11/21  TVIDIGAL     Changed SystemC class macro for Doxygen
 *
 *----------------------------------------------------------------------------*/

#ifndef CONTROL_SYSTEM_H_
#define CONTROL_SYSTEM_H_

#include <systemc.h>
#include "Subtractor.hpp"
#include "Actuator.hpp"
#include "Plant.hpp"
#include "PID_TLM.hpp"
#include "FaultManager.hpp"

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

using namespace tlm;
using namespace tlm_utils;

///Control System using a PID controller
class Control_System : public sc_module {

	public:

	/* Ports **************************************************************/

		///Initiator: Output of the Control System
		simple_initiator_socket<Control_System> initOutput;

		///Initiator: Setpoint to the PID
		simple_initiator_socket<Control_System> initSetpoint;

		///Target: Output from the PID
		simple_target_socket<Control_System> trgtOutput;

		///Target: Setpoint that Control System must reach
		simple_target_socket<Control_System> trgtSetpoint;


	/* Methods ************************************************************/

		/**
		 * @brief      Default constructor
		 * @param[in]  inst           The instance name
		 * @param      pid            The PID to be used in the system
		 * @param[in]  enable_faults  Enable faults of not
		 */
		Control_System(sc_module_name inst, PID* pid, bool enable_faults);


	private:

	/* Fields *************************************************************/

		///Subtractor to compute error of the system
		Subtractor subtractor;

		///TLM wrapper to be used
		PID_TLM    *pid;

		///Actuator of the Plant
		Actuator   actuator;

		///Plant of the system
		Plant      plant;

		///Fault injection manager of the system
		FaultManager fi_manager;

		///Enable flag for fault injection
		bool enable_faults;


	/* Methods ************************************************************/

		/**
          * @brief Transport method of the trgtSetpoint
          * @param trans Transport payload pointer
          * @param delay Delay of the transport
          */
		void receiveSetpoint(tlm_generic_payload& trans, sc_time& delay);

		/**
          * @brief Transport method of the trgtOutput
          * @param trans Transport payload pointer
          * @param delay Delay of the transport
          */
		void receiveOutput(tlm_generic_payload& trans, sc_time& delay);

};

#endif /* CONTROL_SYSTEM_H_ */
