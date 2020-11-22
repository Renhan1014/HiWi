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
// Filename      : multiplexer_env.cpp
//
// Purpose       : implementation of the multiplexer class 
//                 
// Special Notes : 
//                 
// Creator       : Pier Luca Lanzi
//
// Creation Date : 2002/05/31
//
// Current Owner : Pier Luca Lanzi
//
//-------------------------------------------------------------------------

/*!
 * \file multiplexer_env.cpp
 *
 * \brief implements the Boolean multiplexer
 *
 * \author Pier Luca Lanzi
 *
 * \version 0.01
 *
 * \date 2002/05/14
 *
 */

#include <cmath>
#include "xcs_utility.hpp"
#include "xcs_random.hpp"
#include <OCtask.hpp>

#include "task_env.hpp"

using namespace std;

bool	task_env::init=false;	//!< set the init flag to false so that the use of the config manager becomes mandatory
//#define __DEBUG__
task_env::task_env(xcs_config_mgr2& xcs_config)
{
	//! string used to read layered payoff settings; forced off in this version
	string		str_layered_reward;
	
	if (!task_env::init)
	{
		task_env::init = true;

		if (!xcs_config.exist(tag_name()))
		{
			xcs_utility::error(class_name(), "constructor", "section <" + tag_name() + "> not found", 1);	
		}
		
		try {
			//address_size = xcs_config.Value(tag_name(), "address size");
			//str_layered_reward = (string) xcs_config.Value(tag_name(), "layered reward", "off");
		} catch (const char *attribute) {
			string msg = "attribute \'" + string(attribute) + "\' not found in <" + tag_name() + ">";
			xcs_utility::error(class_name(), "constructor", msg, 1);
		}

		//TODO(Renhan): environment must be implemented.
		//unsigned long BitStringSize = 1;
		//BitStringSize <<= address_size;
		//state_size = address_size + BitStringSize;
		//no_configurations = 1;
		//no_configurations <<= state_size;

		//state_size = address_size + long(pow(double(2),int(address_size)));

		//xcs_utility::set_flag(string(str_layered_reward), flag_layered_reward);

		//assert(!flag_layered_reward);
/*#ifdef __DEBUG__
		clog << "ADDRESS SIZE    " << address_size << endl;
		clog << "CONFIGURATIONS  " << no_configurations << endl;
		clog << "INPUT SIZE      " << state_size << endl;

		if (flag_layered_reward)
			clog << "LAYERED REWARD  ON";
		else 
			clog << "LAYERED REWARD  OFF";
#endif
*/
	}

	task_env::init = true;
}

/*!
 * \fn void multiplexer_env::begin_problem(const bool explore)
 * \param explore true if the problem is solved in exploration
 *
 * \brief generates a new input configuration for the Boolean multiplexer
 */
void	
task_env::begin_problem(const bool explore)
{
	current_reward = 0;

	string	str;

	string::size_type	bit;

	str = "";

	for(bit = 0; bit<state_size; bit++)
	{
		str += '0' + xcs_random::dice(2);
	}

	inputs.set_string_value(str);
	current_reward = 0;
	first_problem = false;
}

bool	
task_env::stop()
const
{
	return(true); 
}


void	
task_env::perform(const binary_action& action)
{
	unsigned long		address;
	unsigned long		index;		//! index of the output bit
	string			str_inputs;

	str_inputs = inputs.string_value();

	index = xcs_utility::binary2long(str_inputs.substr(0,address_size));
	address = address_size + index;

	if (!flag_layered_reward)
	{
		if ((str_inputs[address]-'0')==action.value())
		{
			current_reward = 1000;
			solved = true;
		} else {
			current_reward = 0;
			solved = false;
		}
	} else {
		if ((str_inputs[address]-'0')==action.value())
		{
			current_reward = 300 + index*200 + double(100*(unsigned long)(str_inputs[address]-'0'));
			solved = true;
		} else {
			current_reward = index*200 + double(100*(unsigned long)(str_inputs[address]-'0'));
			solved = false;
		}
	}
#ifdef __DEBUG__
	cout << "INPUT " << inputs << " BIT " << str_inputs[address] << " ACTION " << action.value() << " REWARD " << current_reward << endl;
#endif
}
/*
      reward= 300.+(double)(((place-NRBITS)*200)+100*(int)(state[place]-'0'));
      reward= 0.+(double)(((place-NRBITS)*200)+100*(int)(state[place]-'0'));
 *
 */

//! only the current reward is traced
void
task_env::trace(ostream& output) const
{
	if (solved)
		output << 1;
	else
		output << 0;
}

void 
task_env::reset_input()
{
	current_state = 0;
	inputs.set_string_value(xcs_utility::long2binary(current_state,state_size));
}

bool 
task_env::next_input()
{
	string	binary;
	bool	valid = false;

	current_state++; 
	if (current_state<no_configurations)
	{
		inputs.set_string_value(xcs_utility::long2binary(current_state,state_size));
		valid = true;
	} else {
		current_state = 0;
		inputs.set_string_value(xcs_utility::long2binary(current_state,state_size));
		valid = false;
	}
	return valid;
}

void
task_env::save_state(ostream& output) const
{
	output << endl;
	output << current_state << endl;
}

void
task_env::restore_state(istream& input)
{
	input >> current_state; 
	begin_problem(true);
}

task_env::task_env()
{
	if (!multiplexer_env::init)
	{
		xcs_utility::error(class_name(),"class constructor", "not inited", 1);
	} else {
		// nothing to init
	}
}

