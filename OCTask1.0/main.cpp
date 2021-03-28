#include "xcs_definitions.hpp" 
#include "controller.hpp"
#include <vector> 

t_environment* Environment;
t_classifier_system* XCS;

controller* Session;
bool flag_verbose = false;		//! if true verbose output is printed
int main(int argc, char *argv[]){

	vector<double> input;
	vector<double> output;

	//direct write
	string	str_suffix = "maze"; 		//! configuration file suffix
	flag_verbose = true;

	//! system configuration begins
	if (flag_verbose)
		cout << "\nSystem Start ..." << endl;

	string			suffix(str_suffix);

	//! init the configuration manager
	xcs_config_mgr2	xcs_config2(suffix);
	if (flag_verbose)
		cout << "Configuration Manager\t\tok." << endl;


	//! init random the number generator
	xcs_random::set_seed(xcs_config2);
	if (flag_verbose)
		cout << "Random numbers         \t\tok." << endl;

	//! init the action class
	t_action		dummy_action(xcs_config2);
	if (flag_verbose)
		cout << "Actions                \t\tok." << endl;

	//! init the environment
	Environment = new t_environment(xcs_config2);
	if (flag_verbose)
		cout << "Environment            \t\tok." << endl;

	//set Input & Output
	Environment->setInput(input);
	Environment->setOutput(output);

	//! init the condition class
	t_condition		dummy_condition(xcs_config2);
	if (flag_verbose)
		cout << "Conditions             \t\tok." << endl;


	//! init the XCS classifier system
	XCS = new t_classifier_system(xcs_config2);
	if (flag_verbose)
		cout << "Classifier System      \t\tok." << endl;

	//! init the experiment manager
	Session = new controller(xcs_config2);
	if (flag_verbose)
	{
		cout << "Session Manager        \t\tok." << endl;
		cout << endl;
	}

	//Session->setInput(input);
	//Session->setOutput(output);


	//! the experiment session begins
	if (flag_verbose)
		cout << "Begin Experiments...\n" << endl;
	Session->perform_experiments();
	if (flag_verbose)
		cout << "End Experiments...\n" << endl;


	




}
