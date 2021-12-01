#include <string>
#include <fstream>
#include <algorithm>
#include "rule_generator.hpp"
//#include "xcs_classifier_system.hpp"


rule_generator::rule_generator(xcs_classifier_system *out){
        xcs = out;
	xcs->get_total_steps(&total_step);
        //cout<< "init rule :total step is "<< total_step<<endl;
	xcs->get_flag_ga_tournament_selection(flag_ga_tournament_selection);
	xcs->get_prob_crossover(&prob_crossover);
	xcs->get_prob_mutation(&prob_mutation);
	xcs->get_flag_ga_average_init(flag_ga_average_init);
	xcs->get_flag_ga_subsumption(flag_ga_subsumption);
	xcs->get_flag_gaa_subsumption(flag_gaa_subsumption);
}

/*
rule_generator::rule_generator(xcs_config_mgr2& xcs_config)
{
    string str_ga_ts; //! string for reading GA tournament selection settings
    string str_ga_sub;	
    string str_gaa_sub;
    if (!xcs_config.exist(tag_name()))
	{
		xcs_utility::error(class_name(), "constructor", "section <" + tag_name() + "> not found", 1);	
	}
	
	try {
             str_ga_ts = (string) xcs_config.Value(tag_name(), "GA tournament selection");
             tournament_size = xcs_config.Value(tag_name(), "tournament size");
             prob_crossover = xcs_config.Value(tag_name(), "crossover probability");
             str_ga_sub = (string) xcs_config.Value(tag_name(), "GA subsumption");
             str_gaa_sub = (string) xcs_config.Value(tag_name(), "GAA subsumption", "off");
             prob_mutation = xcs_config.Value(tag_name(), "mutation probability");

	} catch (const char *attribute) {
		string msg = "attribute \'" + string(attribute) + "\' not found in <" + tag_name() + ">";
		xcs_utility::error(class_name(), "constructor", msg, 1);
	}

        xcs_utility::set_flag(string(str_ga_ts), flag_ga_tournament_selection);
        xcs_utility::set_flag(string(str_ga_sub),flag_ga_subsumption);
        xcs_utility::set_flag(string(str_gaa_sub),flag_gaa_subsumption);
        flag_ga_average_init = false;
}
*/
//rule_generator::rule_generator() {
//
//}



/*

void    
rule_generator::do_cover_GA(const t_state& current_input) {
	// how to get parent classifier?
	t_classifier& parent1;
	t_classifier& parent2;
	genetic_algorithm(current_input, parent1, parent2);
}
*/

/*
void
rule_generator::do_covering(const t_classifier& cls, const t_state& current_input) {
	cls.cover(current_input);
	//cls_cover = &cls;
}
*/

/*
void
rule_generator::do_GA(const t_classifier& parent1, const t_classifier& parent2, const t_classifier& offspring1, const t_classifier& offspring2, const t_state& current_input) {
	// how to get parent classifier?
	parent1.cover(current_input);
	parent2.cover(current_input);
	genetic_algorithm(current_input, parent1, parent2, offspring1, offspring2);
}
/*

/*
void
rule_generator::genetic_algorithm(const t_state& detectors, const t_classifier& pa1, const t_classifier& pa2, const t_classifier& offspring1, const t_classifier& offspring2)
{

	//t_classifier	offspring1;
	//t_classifier	offspring2;
	//t_classifier    parent1 = pa1;
	//t_classifier    parent2 = pa2;

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


void    
rule_generator::do_simulator(t_classifier_ptr cl) {
	//ToDo: What is the task of simulation?
	t_classifier cl1;
	cl1 = *cl;
	cl = &cl1;
}
*/


void
rule_generator::genetic_algorithm(t_classifier_set &action_set, const t_state& detectors, const bool flag_condensation)
{
	
         
        //cout<<"enter rule_ga."<<endl;
        //cout<<"xcs address is "<<xcs<<endl;
        //cout<<"XCS.total_steps is"<< thisXCStotal_steps <<endl;
       // cout<<"tournament_size is"<< tournament_size <<endl;
        //cout<<"prob_mutation is"<< prob_mutation <<endl;
        
	t_set_iterator	as;

	//! set the time stamp of classifiers in [A]
        
        //cout<<"XCS.total_steps is"<<  total_step <<endl;
	for(as=action_set.begin(); as!=action_set.end(); as++)
	{
                (**as).time_stamp = total_step;
		//(**as).time_stamp = total_step;
	}
	//! select offspring classifiers
	if (!flag_ga_tournament_selection)
	{
		xcs->select_offspring1(action_set, parent1, parent2);
	} else {
		xcs->select_offspring_ts1(action_set, parent1);
		xcs->select_offspring_ts1(action_set, parent2);
	}

	//! the GA is activated only if condensation is off
	if (!flag_condensation)
	{	
		offspring1 = (**parent1);
		offspring2 = (**parent2);

		offspring1.numerosity = offspring2.numerosity = 1;
		offspring1.experience = offspring2.experience = 1;

		if (xcs_random::random()<prob_crossover)
		{
			offspring1.recombine(offspring2);

			//! classifier parameters are inited from parents' averages
			if (flag_ga_average_init)
			{
				xcs->init_classifier1(offspring1,true);
				xcs->init_classifier1(offspring2,true);
				offspring1.prediction = offspring2.prediction = ((**parent1).prediction+(**parent2).prediction)/2;
			} else {
				offspring1.prediction = offspring2.prediction = ((**parent1).prediction+(**parent2).prediction)/2;
				offspring1.error = offspring2.error = ((**parent1).error+(**parent2).error)/2;
				offspring1.fitness = offspring2.fitness = ((**parent1).fitness+(**parent2).fitness)/2;
				offspring1.time_stamp = offspring2.time_stamp = total_step;
				offspring1.actionset_size = offspring2.actionset_size = ((**parent2).actionset_size + (**parent2).actionset_size)/2;
				//offspring1.actionset_size = offspring2.actionset_size = init_set_size;
			}
		}

		offspring1.mutate(prob_mutation,detectors);
		offspring2.mutate(prob_mutation,detectors);

		//! offsprings are penalized through the reduction of fitness
		offspring1.fitness = offspring1.fitness * 0.1;
		offspring2.fitness = offspring2.fitness * 0.1;

		t_condition	cond;
	
		if (cond.allow_ga_subsumption() && flag_ga_subsumption)
		{
			if (xcs->subsume1(**parent1, offspring1))
			{	//! parent1 subsumes offspring1
				(**parent1).numerosity++;
				//population_size++;
				unsigned long size;
				xcs->get_population_size(&size);
				size++;
				xcs->set_population_size(&size);
				 
			} else if (xcs->subsume1(**parent2, offspring1))
			{	//! parent2 subsumes offspring1
				(**parent2).numerosity++;
				//population_size++;
				unsigned long size;
				xcs->get_population_size(&size);
				size++;
				xcs->set_population_size(&size);
			} else {
				//! neither of the parent subsumes offspring1
				if (flag_gaa_subsumption)
				{
					//! if the usual GA subsumption is used, offspring classifier is inserted
					xcs->insert_classifier1(offspring1);
				} else {
					//! if Martin's GA subsumption is used, offspring classifier is compared to the classifiers in [A]
					t_set_iterator 	par;

					xcs->ga_a_subsume(action_set,offspring1,par);
					if (par!=action_set.end())
					{				
						(**par).numerosity++;
						//population_size++;
						unsigned long size;
						xcs->get_population_size(&size);
						size++;
						xcs->set_population_size(&size);
					} else {
						xcs->insert_classifier1(offspring1);
					}
				}
			}
	
			if (xcs->subsume1(**parent1, offspring2))
			{	//! parent1 subsumes offspring2
				(**parent1).numerosity++;
				//population_size++;
				unsigned long size;
				xcs->get_population_size(&size);
				size++;
				xcs->set_population_size(&size);
			}
			else if (xcs->subsume1(**parent2, offspring2))
			{	//! parent2 subsumes offspring2
				(**parent2).numerosity++;
				//population_size++;
				unsigned long size;
				xcs->get_population_size(&size);
				size++;
				xcs->set_population_size(&size);
			} else {
				//! neither of the parent subsumes offspring1
				if (!flag_gaa_subsumption)
				{
					//! if the usual GA subsumption is used, offspring classifier is inserted
					xcs->insert_classifier1(offspring2);
				} else {
					//! if Martin's GA subsumption is used, offspring classifier is compared to the classifiers in [A]
					t_set_iterator 	par;

					xcs->ga_a_subsume(action_set,offspring2,par);
					if (par!=action_set.end())
					{				
						(**par).numerosity++;
						//population_size++;
						unsigned long size;
						xcs->get_population_size(&size);
						size++;
						xcs->set_population_size(&size);
					} else {
						xcs->insert_classifier1(offspring2);
					}
				}
			}
			xcs->delete_classifier1();
			xcs->delete_classifier1();
		} else {	
			// insert offspring classifiers without subsumption
			xcs->insert_classifier1(offspring1);
			xcs->insert_classifier1(offspring2);

			xcs->delete_classifier1();
			xcs->delete_classifier1();
		}

	} else {
		// when in condensation
		(**parent1).numerosity++;
		//population_size++;
		unsigned long size;
		xcs->get_population_size(&size);
		size++;
		xcs->set_population_size(&size);
		xcs->delete_classifier1();

		(**parent2).numerosity++;
		//population_size++;
		xcs->get_population_size(&size);
		size++;
		xcs->set_population_size(&size);
		xcs->delete_classifier1();
	}
}


void
rule_generator::run_ge_algo(t_classifier_set& action_set, const t_state& detectors, const bool flag_condensation) {
	xcs->genetic_algorithm1(action_set, detectors, flag_condensation);
}

/*
void run(bool flag_condensation)
{
       // cout<<"enter rule_ga."<<endl;
        //cout<<"XCS.total_steps is"<< xcs.total_steps <<endl;
       // cout<<"tournament_size is"<< xcs.tournament_size <<endl;
        //cout<<"prob_mutation is"<< xcs.prob_mutation <<endl;

        vector<t_classifier*> action_set = rule_generator::xcs->action_set;
        t_state detectors = xcs->previous_input;
  
        vector<xcs_classifier*>::iterator 	parent1;
	vector<xcs_classifier*>::iterator	parent2;

	t_classifier	offspring1;
	t_classifier	offspring2;

	t_set_iterator	as;

	//! set the time stamp of classifiers in [A]
	for(as=action_set.begin(); as!=action_set.end(); as++)
	{
		(**as).time_stamp = xcs->total_steps;
	}
        cout<<"XCS.total_steps is"<< xcs->total_steps <<endl;
	//! select offspring classifiers
	if (!xcs->flag_ga_tournament_selection)
	{
		xcs->select_offspring(action_set, parent1, parent2);
	} else {
		xcs->select_offspring_ts(action_set, parent1);
		xcs->select_offspring_ts(action_set, parent2);
	}

	//! the GA is activated only if condensation is off
	if (!flag_condensation)
	{	
		offspring1 = (**parent1);
		offspring2 = (**parent2);

		offspring1.numerosity = offspring2.numerosity = 1;
		offspring1.experience = offspring2.experience = 1;

		if (xcs_random::random()<xcs->prob_crossover)
		{
			offspring1.recombine(offspring2);

			//! classifier parameters are inited from parents' averages
			if (xcs->flag_ga_average_init)
			{
				xcs->init_classifier(offspring1,true);
				xcs->init_classifier(offspring2,true);
				offspring1.prediction = offspring2.prediction = ((**parent1).prediction+(**parent2).prediction)/2;
			} else {
				offspring1.prediction = offspring2.prediction = ((**parent1).prediction+(**parent2).prediction)/2;
				offspring1.error = offspring2.error = ((**parent1).error+(**parent2).error)/2;
				offspring1.fitness = offspring2.fitness = ((**parent1).fitness+(**parent2).fitness)/2;
				offspring1.time_stamp = offspring2.time_stamp = xcs->total_steps;
				offspring1.actionset_size = offspring2.actionset_size = ((**parent2).actionset_size + (**parent2).actionset_size)/2;
				//offspring1.actionset_size = offspring2.actionset_size = init_set_size;
			}
		}

		offspring1.mutate(prob_mutation,detectors);
		offspring2.mutate(prob_mutation,detectors);

		//! offsprings are penalized through the reduction of fitness
		offspring1.fitness = offspring1.fitness * 0.1;
		offspring2.fitness = offspring2.fitness * 0.1;

		t_condition	cond;
	
		if (cond.allow_ga_subsumption() && xcs->flag_ga_subsumption)
		{
			if (xcs->subsume(**parent1, offspring1))
			{	//! parent1 subsumes offspring1
				(**parent1).numerosity++;
				xcs->population_size++;
			} else if (xcs->subsume(**parent2, offspring1))
			{	//! parent2 subsumes offspring1
				(**parent2).numerosity++;
				xcs->population_size++;
			} else {
				//! neither of the parent subsumes offspring1
				if (!xcs->flag_gaa_subsumption)
				{
					//! if the usual GA subsumption is used, offspring classifier is inserted
					xcs->insert_classifier(offspring1);
				} else {
					//! if Martin's GA subsumption is used, offspring classifier is compared to the classifiers in [A]
					t_set_iterator 	par;

					xcs->ga_a_subsume(action_set,offspring1,par);
					if (par!=action_set.end())
					{				
						(**par).numerosity++;
						xcs->population_size++;
					} else {
						xcs->insert_classifier(offspring1);
					}
				}
			}
	
			if (xcs->subsume(**parent1, offspring2))
			{	//! parent1 subsumes offspring2
				(**parent1).numerosity++;
				xcs->population_size++;
			}
			else if (xcs->subsume(**parent2, offspring2))
			{	//! parent2 subsumes offspring2
				(**parent2).numerosity++;
				xcs->population_size++;
			} else {
				//! neither of the parent subsumes offspring1
				if (!xcs->flag_gaa_subsumption)
				{
					//! if the usual GA subsumption is used, offspring classifier is inserted
					xcs->insert_classifier(offspring2);
				} else {
					//! if Martin's GA subsumption is used, offspring classifier is compared to the classifiers in [A]
					t_set_iterator 	par;

					xcs->ga_a_subsume(action_set,offspring2,par);
					if (par!=action_set.end())
					{				
						(**par).numerosity++;
						xcs->population_size++;
					} else {
						xcs->insert_classifier(offspring2);
					}
				}
			}
			xcs->delete_classifier();
			xcs->delete_classifier();
		} else {	
			// insert offspring classifiers without subsumption
			xcs->insert_classifier(offspring1);
			xcs->insert_classifier(offspring2);

			xcs->delete_classifier();
			xcs->delete_classifier();
		}

	} else {
		// when in condensation
		(**parent1).numerosity++;
		xcs->population_size++;
		xcs->delete_classifier();

		(**parent2).numerosity++;
		xcs->population_size++;
		xcs->delete_classifier();
	}
   

}
/*
/*
void
rule_generator::select_offspring(t_classifier_set &action_set, t_set_iterator &clp1, t_set_iterator &clp2)
{
	t_set_iterator	as;		//! iterator in [A]
	vector<double>	select;		//! vector used to implement the roulette wheel
	unsigned long	sel;		//! counter

	double		fitness_sum;
	double		random1;
	double		random2;

	select.clear();

	fitness_sum = 0;
	for(as=action_set.begin(); as!=action_set.end(); as++)
	{
		fitness_sum += (**as).fitness;
		select.push_back( fitness_sum );
	}

	random1 = (xcs_random::random())*fitness_sum;
	random2 = (xcs_random::random())*fitness_sum;

	if (random1>random2)
		swap(random1,random2);

	for(sel = 0; (sel<select.size()) && (random1>=select[sel]); sel++);
	clp1 = action_set.begin()+sel;	// to be changed if list containers are used
	assert(sel<select.size());

	for(; (sel<select.size()) && (random2>=select[sel]); sel++);
	clp2 = action_set.begin()+sel;	// to be changed if list containers are used
	assert(sel<select.size());
}


void
rule_generator::select_offspring_ts(t_classifier_set& set, t_set_iterator& clp)
{
	t_set_iterator	as;				//! iterator in set
	t_set_iterator	winner = set.end();

	while (winner==set.end())
	{
		for(as=set.begin(); as!=set.end(); as++)
		{
			bool selected = false;

			for(unsigned long num=0; (!selected && (num<(**as).numerosity)); num++)
			{
				if (xcs_random::random()<tournament_size)
				{
					if ((winner==set.end()) ||
					    (((**winner).fitness/(**winner).numerosity)<((**as).fitness/(**as).numerosity)))
					{
						winner = as;
						selected = true;
					}
				}
			}
		}
	}

	clp = winner;

}
*/

