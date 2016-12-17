/**
 * @file    FaultManager.hpp
 * @brief   Manager of Fault Injections header
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
 * 1.0      2016/10/31  TVIDIGAL     File created.
 * 1.1      2016/11/21  TVIDIGAL     Changed SystemC class macro for Doxygen
 *
 *----------------------------------------------------------------------------*/

#ifndef FAULT_MANAGER_H_
#define FAULT_MANAGER_H_

#include <systemc.h>
#include <list>
#include "PID_constants.hpp"
#include "FaultDatabase.hpp"
#include "FaultyBuffer.hpp"
#include "BufferFault.hpp"

using namespace std;


///Manager of Fault Injections
class FaultManager : public sc_module {

	public:

		/* Fields ****************************************************************/

		///Event to trigger fault injection iteration
		sc_event inject_faults;


		/* Methods ***************************************************************/

		///Default constructor
		SC_CTOR(FaultManager);


	private:

		/* Methods ***************************************************************/

		///Check if there's pending faults and inject them
		void checkAndInjectFaults();

};

#endif /* FAULT_MANAGER_H_ */

