/*
 * The XCS Library 
 * A C++ framework to apply and develop learning classifier systems
 * Copyright (C) 2002-2009 Pier Luca Lanzi
 * 
 * Pier Luca Lanzi 
 * Dipartimento di Elettronica e Informazione
 * Politecnico di Milano
 * Piazza Leonardo da Vinci 32
 * I-20133 MILANO - ITALY
 * pierluca.lanzi@polimi.it/lanzi@elet.polimi.it
 *
 * This file is part of the XCSLIB library.
 *
 * xcslib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * xcslib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * A copy of the license is available at http://www.gnu.org/licenses/gpl.html
 * 
 * If you use this code, please cite the following technical report:
 *
 * P.L. Lanzi and D. Loiacono (2009), "XCSLib: The XCS Classifier System Library", 
 * Technical Report No. 2009005, Illinois Genetic Algorithms Laboratory
 * University of Illinois at Urbana-Champaign, 117 Transportation Building
 * 104 S. Mathews Avenue Urbana, IL 61801
 * 
 * Available at http://www.illigal.uiuc.edu/pub/papers/IlliGALs/2009005.pdf
 *
 * For updates please visit: http://xcslib.sf.net 
 *                           http://www.pierlucalanzi.net
 */



//-------------------------------------------------------------------------
// Filename      : main.cc
//
// Purpose       : main
//                 
// Special Notes : 
//                 
//
// Creator       : Pier Luca Lanzi
//
// Creation Date : 2002/05/28
//
// Current Owner : Pier Luca Lanzi
//-------------------------------------------------------------------------
// Modifications
// 20050429	added the verbose flag
// 20030807	general.hh becomes xcs_definitions.hh
//-------------------------------------------------------------------------

/*!
 * \file main.cc
 *
 * \brief implements the main code to exploit the 
 *
 */

#include "xcs_definitions.hpp" 
//#include "experiment_mgr.hpp"
#include "in_output.hpp"
//#include <typeinfo>
/*!
//	global variables
*/

/*!
 * \var t_environment* Environment
 * the environment
 */

/*!
 * \var xcs_classifier_system* XCS
 * the XCS classifier system
 */

/*!
 * \var experiment_mgr* Session
 * the experiment session
 *
 */

t_environment		*Environment;
t_classifier_system	*XCS;

//experiment_mgr* Session;
bool flag_verbose = false;		//! if true verbose output is printed

/*! 
 * \fn int main(int Argc, char *Argv[])
 * \param argc number of arguments
 * \param argv list of arguments
 * 
 * main code to exploit the XCS implementation
 */
int
main(int argc, char *argv[])
{
	string	str_suffix = "weight"; 		//! configuration file suffix
	//int		o;							//! current option
	
	/*
	if (argc==1)
	{
		cerr << "USAGE:\t\t" << argv[0] << "\t" << "-f <suffix> [-v] [-s <set>] " << endl;
		cerr << "      \t\t\t\t" << "<suffix>     suffix for the configuration file" << endl;
		cerr << "      \t\t\t\t" << "-v           verbose output" << endl;
		cerr << "      \t\t\t\t" << "-h           print version" << endl;
		return 0;
	}		


	while ( (o = getopt(argc, argv, "hvf:")) != -1 )
	{
		switch (o)
		{
			case 'v':
				flag_verbose = true;
			
			case 'f':
				str_suffix = string(optarg);
				break;
			case 'h':
				//! print version
				cerr << "XCSLIB\tVERSION " << __XCSLIB_VERSION__ << endl;
				cerr << "      \tBUILT   " << __DATE__ << endl;
				cerr << "      \tTIME    " << __TIME__ << endl;
				cerr << endl;
				cerr << "      \tSTATE       " << __INPUTS_VERSION__ << endl;
				cerr << "      \tACTION      " << __ACTION_VERSION__ << endl;
				cerr << "      \tCONDITIIONS " << __CONDITION_VERSION__ << endl;
				cerr << endl << endl;
				return 0;
				break;	
			default:
				string msg = "unrecognized option" + string(optarg);
				xcs_utility::error("main","main",msg,0);
		}
	}
	*/

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
	t_action		integer_action(xcs_config2);
	if (flag_verbose) 
		cout << "Actions                \t\tok." << endl;

	//! init the environment
	Environment = new t_environment(xcs_config2);
        
	if (flag_verbose) 
		cout << "Environment            \t\tok." << endl;
    
    Environment->weight_init();
    
        
	//! init the condition class
	t_condition		real_interval_condition(xcs_config2);
	if (flag_verbose) 
		cout << "Conditions             \t\tok." << endl;

	//! init the XCS classifier system
	XCS = new t_classifier_system(xcs_config2);
	if (flag_verbose) 
		cout << "Classifier System      \t\tok." << endl;

    //prepare for input&reward&weight
    
	double get_weight[3];
    vector<long long> get_input;
    int get_reward;
	unsigned long get_action;
    
    //simulate input &reward &weight
	struct dls_system_snapshot sys1;  
    memset(&sys1,0,sizeof(sys1));
    sys1.n_tasks = 1;
    sys1.longest_path = 3;
    sys1.max_width = 5;
    sys1.max_cpu_temp = 7;
    sys1.gpu_temp = 9;
    sys1.avg_pu_waiting_time = 11;
    
	int received_reward = 10;
	vector<double> weight_xcs;
    unsigned long action_xcs;
    
    //Prepare for performing experiment
	bool flag_condensation = false;
	bool flag_exploration = true;
    XCS->begin_experiment();
	XCS->begin_problem();
	Environment->begin_problem(flag_exploration);
	in_output in_out;
    
	//perform one step
	//First, get the input
	in_out.receiveInput(sys1);
	in_out.get_Input(get_input);
	//transfer Input type from long long to double
	vector<double> input1;
	for (int i =0; i<get_input.size();i++) {
		double val = static_cast<double>(get_input[i]);
        input1.push_back(val);
	}
    //send input to xcs
	Environment->setInput(input1);
	
	// xcs perform step_part_1 and select a action
	XCS->step_part_1(flag_exploration,flag_condensation);
	
	//get action form xcs
	Environment->getWeightAndAction(weight_xcs, action_xcs);
	
	//action from xcs to in_output
	in_out.get_Action_from_XCS(weight_xcs,action_xcs);
	//send action to outside from in_output
	
	in_out.sendAction(get_weight,get_action);
	

	
	//in_output receive reward from outside
    in_out.receiveReward(received_reward);
	
    //get the reward form in_output
	in_out.get_Reward(get_reward);
	
	//send reward to xcs
    Environment->setRewardFromOut(static_cast<double>(get_reward));
	
	//xcs perform step part 2 and update
	XCS->step_part_2(flag_exploration,flag_condensation);
	
   
    //print result
    cout << "selected_action is: " << get_action <<endl;
	cout << "final_weight is: " << endl;
	for(int i = 0; i < 3;i++){
		cout << get_weight[i]<< endl;
	}


    /*
	//! init the experiment manager
	Session = new experiment_mgr(xcs_config2);
	if (flag_verbose) 
	{
		cout << "Session Manager        \t\tok." << endl;
		cout << endl;
	}

	//! the experiment session begins
	if (flag_verbose) 
		cout << "Begin Experiments...\n" << endl;
	Session->perform_experiments();
	if (flag_verbose) 
		cout << "End Experiments...\n" << endl;
	*/
	
}
