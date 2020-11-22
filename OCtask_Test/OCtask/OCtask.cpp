#include "OCtask.hpp"


OCtask::OCtask() {
	this->flag_verbose = true;
	this->MSGSTR = = 256;
}

OCtask::~OCtask() {

}

void OCtask::performTask(string str_suffix){
	
	if (flag_verbose)
		cout << "\nSystem Start ..." << endl;


	//! init the configuration manager
	this->setConfig(str_suffix);

	//! init random the number generator
	this->setRandom();

	//! init the action class
	this->setAction();

	//! init the environment
	this->setEnvironment();

	//! init the condition class
	this->setCondition();


	//! init the XCS classifier system
	this->setXCS();


	//! init the experiment manager
	this->setSession();


	//! the experiment session begins
	if (flag_verbose)
		cout << "Begin Experiments...\n" << endl;
	Session->perform_experiments();
	if (flag_verbose)
		cout << "End Experiments...\n" << endl;
}



OCtask::setConfig(string str_suffix) {
	string suffix(str_suffix);

	this->xcs_config2 = new xcs_config_mgr2(suffix);
	if (flag_verbose)
		cout << "Configuration Manager\t\tok." << endl;
}

OCtask::setRandom() {
	this->random = new xcs_random();
	random->set_seed(*(this->xcs_config2));
	if (flag_verbose)
		cout << "Random numbers         \t\tok." << endl;
}

OCtask::setAction() {
	this->t_action = new binary_action(*(this->xcs_config2));
	if (flag_verbose)
		cout << "Actions                \t\tok." << endl;

}

OCtask::setEnvironment() {
	this->Environment = new task_env(*(this->xcs_config2));
	if (flag_verbose)
		cout << "Environment            \t\tok." << endl;

}

OCtask::setCondition() {
	this->t_condition = new ternary_condition(*(this->xcs_config2));
	if (flag_verbose)
		cout << "Conditions             \t\tok." << endl;
}
OCtask::setXCS() {
	this->XCS = new xcs_classifier_system(*(this->xcs_config2));
		if (flag_verbose)
			cout << "Classifier System      \t\tok." << endl;

}

OCtask::setSession() {
	this->Session = new experiment_mgr(*(this->xcs_config2));
	if (flag_verbose)
	{
		cout << "Session Manager        \t\tok." << endl;
		cout << endl;
	}
}
OCtask::setMSGSTR() {

}





xcs_random* OCtask::getRandom() {
	return this->random;
}
binary_action* OCtask::getAction() {
	return this->t_action;
}

task_env* OCtask::getEnvironment() {
	return this->Environment;
}

ternary_condition* OCtask::getCondition() {
	return this->t_condition;
}

xcs_classifier_system* OCtask::getXCS() {
	return this->XCS;

}
experiment_mgr* OCtask::getSession() {
	return this->Session;

}

unsigned long OCtask::getMSGSTR() {
	return this->MSGSTR;
}

