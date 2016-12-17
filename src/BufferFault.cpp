/**
 * @file    BufferFault.cpp
 * @brief   Fault of a FaultyBuffer source
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

#include "../hdr/BufferFault.hpp"


/* Public *********************************************************************/

BufferFault::BufferFault(FaultyBuffer *module, FI_METHOD fault_method, double time_to_inject) {

	this->module         = module;
	this->fault_method   = fault_method;
	this->time_to_inject = time_to_inject;
	cout << "\t '-> Fault: Method " << fault_method;
	cout << ", Inject at " << time_to_inject  << "ms" << endl << flush;
}

bool BufferFault::isPending() {
	if(time_to_inject <= sc_time_stamp().to_seconds()*1000)
		return true;
	else return false;
}

FaultyBuffer* BufferFault::getModule() {
	return module;
}

FIMethod BufferFault::getFaultMethod() {
	return fault_method;
}

double BufferFault::getTimeToInject() {
	return time_to_inject;
}