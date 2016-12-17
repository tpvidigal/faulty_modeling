/**
 * @file    FaultyBuffer.cpp
 * @brief   Derived class from sc_buffer to enable fault injection source
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

#include "../hdr/FaultyBuffer.hpp"


/* Public *********************************************************************/

FaultyBuffer::FaultyBuffer() :

	generator(std::random_device{}()),
	distribution(EXP_DIST_LAMBDA)

{
	cout << "Constructing Faulty\t" << name() << endl;
	fault = NULL;
}

void FaultyBuffer::write( const float_pid& a ) {

	if(fault == NULL)
		sc_buffer::write(a);
	else
		(this->*fault->getFaultMethod())();
}

void FaultyBuffer::setFault(FAULT_TYPE fault_type) {

	BufferFault *fault;
	double time_to_inject;

	time_to_inject = (STEP_RISE_TIME + distribution(generator))*1000;

	switch(fault_type) {
		case STUCK_AT_0: 
			fault = new BufferFault(this, &FaultyBuffer::faultStuckAtZero, time_to_inject);
			FaultDatabase::getInstance()->registerPossibleFault(*fault);
			break;
		default:
			break;
	}
}

void FaultyBuffer::injectFault(BufferFault fault) {
	this->fault = new BufferFault(fault);
}


/* Protected ******************************************************************/

void FaultyBuffer::faultStuckAtZero() {
	//cout << "\n\t\tExecuting STUCK_AT_0 at " << name() << "\n\t\t\t\t\t" << flush;
	sc_buffer::write(0);
}
