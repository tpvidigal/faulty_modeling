/**
 * @file    FaultDatabase.hpp
 * @brief   Database of the faults of the system header
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
 * 1.0      2016/11/02  TVIDIGAL     File created.
 * 1.1      2016/11/09  TVIDIGAL     General fixes
 *
 *----------------------------------------------------------------------------*/

#ifndef FAULT_DATABASE_H_
#define FAULT_DATABASE_H_

#include <systemc.h>
#include <list>
#include "PID_constants.hpp"
#include "BufferFault.hpp"

using namespace std;


///Database to organize faults
class FaultDatabase {

	public:


		/* Methods ***************************************************************/

		///Return instance of Singleton
		static FaultDatabase* getInstance();

		/**
		 * @brief  Register a fault of a faulty component in the database
		 * @param  fault  Fault to be registered
		 */
		void registerPossibleFault(const BufferFault fault);

		///Gets the buffer faults
		list<BufferFault>* getBufferFaults();

		///Delete copy constructor
        FaultDatabase(FaultDatabase const&)  = delete;

        ///Delete copy operator
        void operator=(FaultDatabase const&) = delete;


	protected:

		/* Fields ****************************************************************/

		///Singleton instance
		static FaultDatabase *singleton;

		///Method that models this fault 
		list<BufferFault> faults;


		/* Methods ***************************************************************/

		///Default constructor
		FaultDatabase();

};

#endif /* FAULT_DATABASE_H_ */

