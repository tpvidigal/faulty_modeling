/**
 * @file    FaultyBuffer.hpp
 * @brief   Derived class from sc_buffer to enable fault injection header
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
 * 1.0      2016/10/31  TVIDIGAL     File created.
 * 1.1      2016/11/05  TVIDIGAL     Removing template, fixing for float_pid
 * 1.2      2016/11/09  TVIDIGAL     General fixes
 *
 *----------------------------------------------------------------------------*/

#ifndef FAULTY_BUFFER_H_
#define FAULTY_BUFFER_H_

#include <systemc.h>
#include <random>
#include "PID_constants.hpp"
#include "FaultDatabase.hpp"
#include "BufferFault.hpp"


///Buffers that enable fault injection
class FaultyBuffer: public sc_buffer<float_pid> {

	public:

		/* Fields ****************************************************************/

		///Random number generator
  		default_random_engine generator;

  		///Distribution of random number
  		exponential_distribution<double> distribution;


		/* Methods ***************************************************************/

		///Default constructor
		FaultyBuffer();

		///Selective write method
		void write( const float_pid& a );

		///Set a fault to be injected
		void setFault(FAULT_TYPE fault_type);

		///Inject a fault
		void injectFault(BufferFault fault);


	protected:

		/* Fields ****************************************************************/

		///Fault injected at the module
		BufferFault *fault;


		/* Methods ***************************************************************/

		///Stuck output with the value zero
		void faultStuckAtZero();

};

#endif /* FAULTY_BUFFER_H_ */

