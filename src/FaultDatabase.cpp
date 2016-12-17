/**
 * @file    FaultDatabase.cpp
 * @brief   Database of the faults of the system source
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

#include "../hdr/FaultDatabase.hpp"


/* Public *********************************************************************/

FaultDatabase* FaultDatabase::getInstance() {
	if(singleton==NULL)
		singleton = new FaultDatabase();
	return singleton;
}

void FaultDatabase::registerPossibleFault(const BufferFault fault) {

	faults.push_back(fault);
}

list<BufferFault>* FaultDatabase::getBufferFaults() {

	return &faults;
}


/* Protected ******************************************************************/

FaultDatabase* FaultDatabase::singleton = NULL;

FaultDatabase::FaultDatabase() { }
