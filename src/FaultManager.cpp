/**
 * @file    FaultManager.hpp
 * @brief   Manager of Fault Injections source
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.0
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/10/31  TVIDIGAL     File created.
 *
 *----------------------------------------------------------------------------*/

#include "../hdr/FaultManager.hpp"
SC_HAS_PROCESS(FaultManager);


/* Public *********************************************************************/

FaultManager::FaultManager(sc_module_name inst) : sc_module(inst) {
			
	cout << "Constructing Manager\t" << name() << endl << flush;

	SC_METHOD(checkAndInjectFaults);
	sensitive << inject_faults;
	dont_initialize();
}


/* Private ********************************************************************/

///Inject pending faults
void FaultManager::checkAndInjectFaults() {

	list<BufferFault>::iterator it;
	list<BufferFault> *faults;
	bool first_injection = true;
	bool faults_injected = false;

	faults = FaultDatabase::getInstance()->getBufferFaults();
	
	//Separate faults to be injected
	for(it = faults->begin(); it != faults->end(); it++) {
		if(it->isPending()) {

			//Format first injection output
			if(first_injection) {
				cout << endl;
				first_injection = false;
				faults_injected = true;
			}

			//Inject fault infos
			cout << "\n  ** Fault Injected at " << it->getModule()->name();
			cout << " (" << it->getTimeToInject() << "ms)";

			//Inject fault and erase it from the list
			it->getModule()->injectFault(*it);
			it = faults->erase(it);
		}
	}

	if(faults_injected)
		cout << endl << flush;
}
