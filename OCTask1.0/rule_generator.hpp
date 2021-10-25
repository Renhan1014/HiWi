#ifndef __RULE_GENERATOR__
#define __RULE_GENERATOR__

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>

// STL libraries
#include <algorithm>
#include <vector>

#include "rl_definitions.hpp"
#include "xcs_random.hpp"
#include "xcs_classifier.hpp"
class xcs_classifier_system;

using namespace std;

class rule_generator
{
public:
        //! name of the class that implements XCS
	string class_name() const {return string("rule_generator");};

	//! tag used to access the configuration file
	string tag_name() const {return string("rule_generator");};

	//! class constructor
	rule_generator(xcs_classifier_system *xcs);
        
    ~rule_generator() {};
        
	//void setXCS(t_classifier_system *XCS_out){xcs = XCS_out;};


public:
	//! pointer to a classifier
	typedef xcs_classifier* t_classifier_ptr;

	typedef vector<xcs_classifier*> t_classifier_set;

	//! index in set of classifiers
	/*!
	 * \type t_set_iterator
	 * \brief represent an iterator over a set of classifiers
	*/ 
	typedef vector<xcs_classifier*>::iterator	t_set_iterator;
	typedef vector<xcs_classifier*>::const_iterator	t_set_const_iterator;

private:
        xcs_classifier_system *xcs;
	t_set_iterator 	parent1;
	t_set_iterator	parent2;
	t_classifier	offspring1;
	t_classifier	offspring2;
	unsigned long total_step;
	bool flag_ga_tournament_selection;
	double prob_crossover;
	double prob_mutation;
	bool flag_ga_average_init;
	bool flag_ga_subsumption;
	bool flag_gaa_subsumption;

public:
    void genetic_algorithm(t_classifier_set &action_set, const t_state& detectors, const bool flag_condensation);
	void run_ge_algo(t_classifier_set& action_set, const t_state& detectors, const bool flag_condensation);
};
#endif
