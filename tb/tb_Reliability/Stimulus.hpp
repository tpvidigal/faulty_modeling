/**
 * @file    Stimulus.hpp
 * @brief   System Stimulus header
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
 * 1.0      2016/09/21  TVIDIGAL     Document adapted from PID TB's Stimulus
 * 1.1      2016/09/22  TVIDIGAL     Removed input_ended event and adding
 *                                   sc_stop when file has finished
 *
 *----------------------------------------------------------------------------*/

#ifndef STIMULUS_H_
#define STIMULUS_H_

#include <systemc.h>
#include <iostream>
#include <fstream>
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "../../hdr/PID_constants.hpp"

using namespace tlm_utils;


SC_MODULE(Stimulus) {

	public:

		/* Ports **************************************************************/

		///Socket: Transport an error
		simple_initiator_socket<Stimulus> initError;


		/* Fields *************************************************************/

		sc_event send_event;


		/* Methods ************************************************************/

		///Default constructor
		SC_CTOR(Stimulus);


	private:

		/* Fields *************************************************************/

		ifstream fset;


		/* Methods ************************************************************/

		void doStimulus();
};

#endif /* STIMULUS_H_ */