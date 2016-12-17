/**
 * @file    BufferFault.hpp
 * @brief   Fault of a FaultyBuffer header
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.2
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/11/02  TVIDIGAL     File created.
 * 1.1      2016/11/09  TVIDIGAL     General fixes
 * 1.2      2016/11/11  TVIDIGAL     Adding getter for time to inject
 *
 *----------------------------------------------------------------------------*/

#ifndef BUFFER_FAULT_H_
#define BUFFER_FAULT_H_

#include <systemc.h>
#include "PID_constants.hpp"

///Fault of a FaultyBuffer
class BufferFault {

	public:

		/* Methods ***************************************************************/

		/**
		 * @brief  Default constructor
		 *
		 * @param  module          The module of the fault
		 * @param  fault_method    Fault method
		 * @param  time_to_inject  The time to inject in milliseconds
		 */
		BufferFault(FaultyBuffer *module, FI_METHOD fault_method, double time_to_inject);

		/**
		 * @brief   Check if it's time to be injected
		 * @result  Indicates if injection is pending
		 */
		bool isPending();

		///Get module pointer
		FaultyBuffer* getModule();

		///Get fault method pointer
		FIMethod getFaultMethod();

		///Get time to inject
		double getTimeToInject();


	protected:

		/* Fields ****************************************************************/

		///Module related to this fault
		FaultyBuffer *module;

		///Method that models this fault 
		FI_METHOD fault_method;

		///Time-To-Inject this fault
		double time_to_inject;

};

#endif /* BUFFER_FAULT_H_ */

