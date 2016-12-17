/**
 * @file    Plant.hpp
 * @brief   Plant of the control system header
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
 * 1.0      2016/09/07  TVIDIGAL     Document created.
 * 1.1      2016/09/16  TVIDIGAL     Added matrixes and transports
 * 1.2      2016/09/24  TVIDIGAL     Correcting methodSendOutput name(to thread)
 * 1.3      2016/10/02  TVIDIGAL     Using state matrix as a pointer
 * 1.4      2016/11/21  TVIDIGAL     Changed SystemC class macro for Doxygen
 *
 *----------------------------------------------------------------------------*/

#ifndef PLANT_H_
#define PLANT_H_

#include <systemc.h>
#include "PID_constants.hpp"
#include "Matrix.hpp"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

using namespace tlm;
using namespace tlm_utils;
using namespace std;

///Plant of the PID System
class Plant : public sc_module {

	public:

		/* Ports **************************************************************/

		///Socket: Output computed
		simple_initiator_socket<Plant> initOut;

		///Socket: Output for feedback
		simple_initiator_socket<Plant> initFeedback;

		///Target: Gain to compute output
		simple_target_socket<Plant> trgtGain;


		/* Methods ************************************************************/

		///Default constructor
		SC_CTOR(Plant);


		/* Tables *************************************************************/

		static const float_pid MATRIX_A[][3];

		static const float_pid MATRIX_B[][1];

		static const float_pid MATRIX_C[][3];


	private:

		/* Signals ************************************************************/

		///State variables matrix
		Matrix *state;

		///State-Space's A Matrix
		Matrix m_A;

		///State-Space's B Matrix
		Matrix m_B;

		///State-Space's C Matrix
		Matrix m_C;

		///Event that triggers the send output method
		sc_event send_output;

		///Gain received from PID
		float_pid gain;


		/* Methods ************************************************************/

		/**
          * @brief Transport method of the trgtGain
          * @param trans Transport payload pointer
          * @param delay Delay of the transport
          */
		void doPlant(tlm_generic_payload& trans, sc_time& delay);

		///Transport method for initOut
		void threadSendOutput();

		/**
		 * @brief  Compute the output of the plant
		 * @param  gain Gain received by the plant
		 * @return Return output
		 */
		float_pid plantFunction(float_pid gain);

};

#endif /* PLANT_H_ */