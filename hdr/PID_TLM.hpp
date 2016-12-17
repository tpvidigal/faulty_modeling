/**
 * @file    PID_TLM.hpp
 * @brief   TLM wrapper of the PID header
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
 * 1.0      2016/08/14  TVIDIGAL     Document created.
 * 1.1      2016/08/24  TVIDIGAL     Using float_pid as the type of signals
 * 1.2      2016/09/21  TVIDIGAL     Correcting template method comment and
 *                                   name of the sendGain (threadSendGain).
 * 1.3      2016/10/02  TVIDIGAL     Forcing PID type choose at the constructor
 * 1.4      2016/11/21  TVIDIGAL     Changed SystemC class macro for Doxygen
 *
 *----------------------------------------------------------------------------*/

#ifndef PID_TLM_H_
#define PID_TLM_H_

#include <systemc.h>
#include "PID_constants.hpp"
#include "PID.hpp"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

using namespace tlm;
using namespace tlm_utils;
using namespace std;

///TLM Wrapper for PID
class PID_TLM : public sc_module {

	public:

		/* Ports **************************************************************/

		///Socket: Gain computated by the PID
		simple_initiator_socket<PID_TLM> initGain;

		///Target: Error to compute gain
		simple_target_socket<PID_TLM> trgtError;


		/* Methods ************************************************************/

		/**
		 * @brief      Default constructor
		 * @param[in]  inst  The instance name
		 * @param      pid   The PID to be wrapped
		 */
		PID_TLM(sc_module_name inst, PID* pid);


	private:

		/* Fields *************************************************************/

		///PID being wrapped
		PID *pid;


		/* Methods ************************************************************/

		/**
          * @brief Transport method of the trgtError
          * @param trans Transport payload pointer
          * @param delay Delay of the transport
          */
		virtual void b_transport(tlm_generic_payload& trans, sc_time& delay);

		///Transport thread for initGain
		void threadSendGain();
		
};

#endif /* PID_TLM_H_ */

