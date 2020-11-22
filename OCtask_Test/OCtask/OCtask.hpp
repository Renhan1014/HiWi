#ifndef _OCTASK_
#define _OCTASK_

//++++++++++++++++
//from rl_definition.hpp
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>

//! STL libraries
#include <algorithm>
#include <vector>

//! maximum number of char available for error messages

//++++++++++++++++

#include "xcs_config_mgr2.hpp"
#include "xcs_random.hpp"
#include "binary_action.hpp"
#include "task_env.hpp"
#include "ternary_condition.hpp"
#include "xcs_classifier_system.hpp"
#include "experiment_mgr.hpp"

class OCtask {

public:
	OCtask();
	~OCtask();
	void performTask(string str_suffix);
	xcs_random* getRandom();
	binary_action* getAction();
	task_env* getEnvironment();
	ternary_condition* getCondition();
	xcs_classifier_system* getXCS();
	experiment_mgr* getSession();
	unsigned long getMSGSTR();
	

private:
	xcs_config_mgr2* xcs_config2;
	xcs_random* random;
	binary_action* t_action;
	task_env* Environment;
	ternary_condition* t_condition;
	xcs_classifier_system* XCS;
	experiment_mgr* Session;
	bool flag_verbose;
	const unsigned long MSGSTR;

private:
	void setConfig(string suffix);
	void setRandom();
	void setAction();
	void setEnvironment();
	void setCondition();
	void setXCS();
	void setSession();
	void setMSGSTR();
	
};
#endif _OCTASK_