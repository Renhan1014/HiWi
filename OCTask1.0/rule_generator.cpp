#include <string>
#include <fstream>
#include <algorithm>
#include "rule_generator.hpp"
extern t_classifier_system* XCS;


rule_generator::rule_generator() {

}

void    
rule_generator::do_cover_GA(const t_state& current_input) {
	// how to get parent classifier?
	t_classifier& parent1;
	t_classifier& parent2;
	genetic_algorithm(current_input, parent1, parent2);
}

void
rule_generator::genetic_algorithm(const t_state& detectors, t_classifier& pa1, t_classifier& pa2)
{

	t_classifier	offspring1;
	t_classifier	offspring2;
	t_classifier    parent1 = pa1;
	t_classifier    parent2 = pa2;

	parent1.time_stamp = XCS->time();
	parent2.time_stamp = XCS->time();

	offspring1.numerosity = offspring2.numerosity = 1;
	offspring1.experience = offspring2.experience = 1;

	if (xcs_random::random() < prob_crossover)
	{
		//crossover
		offspring1.recombine(offspring2);

		//! classifier parameters are inited from parents' averages
		if (flag_ga_average_init)
		{
			XCS->init_classifier_1(offspring1, true);
			XCS->init_classifier_1(offspring2, true);
			offspring1.prediction = offspring2.prediction = (parent1.prediction + parent2.prediction) / 2;
		}
		else {
			offspring1.prediction = offspring2.prediction = (parent1.prediction + parent2.prediction) / 2;
			offspring1.error = offspring2.error = (parent1.error + parent2.error) / 2;
			offspring1.fitness = offspring2.fitness = (parent1.fitness + parent2.fitness) / 2;
			offspring1.time_stamp = offspring2.time_stamp = XCS->time();
			offspring1.actionset_size = offspring2.actionset_size = (parent2.actionset_size + parent2.actionset_size) / 2;
				//offspring1.actionset_size = offspring2.actionset_size = init_set_size;
		}
	}

	//mutate
	offspring1.mutate(prob_mutation, detectors);
	offspring2.mutate(prob_mutation, detectors);

	//! offsprings are penalized through the reduction of fitness
	offspring1.fitness = offspring1.fitness * 0.1;
	offspring2.fitness = offspring2.fitness * 0.1;

	//simulation
	do_simulator(&offspring1);
	do_simulator(&offspring2);
	
	//insert new classifier into XCS
	XCS->insert_classifier_1(offspring1);
	XCS->insert_classifier_1(offspring2);

	XCS->delete_classifier_1();
	XCS->delete_classifier_1();
}



//For Covering

//! perform covering on [M], only if needed
bool
rule_generator::perform_covering(const t_state& detectors)
{
	switch (covering_strategy)
	{
		//! perform covering according to Wilson 1995
	case COVERING_STANDARD:
		return perform_standard_covering(match_set, detectors);
		break;

		//! covering strategy as in Butz and Wilson 2001
	case COVERING_ACTION_BASED:
		return perform_nma_covering(match_set, detectors);
		break;
	default:
		xcs_utility::error(class_name(), "perform_covering", "covering strategy not allowed", 1);
		exit(-1);
	}
}


void    
rule_generator::do_simulator(t_classifier_ptr cl) {
	//ToDo: What is the task of simulation?
	t_classifier cl1;
	cl1 = *cl;
	cl = &cl1;
}
