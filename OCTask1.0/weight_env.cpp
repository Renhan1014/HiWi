#include <cmath>
#include "xcs_utility.hpp"
#include "xcs_random.hpp"

#include "weight_env.hpp"

using namespace std;

bool	weight_env::init = false;

//constructor, read the number of weight from the configuration file and set it 
weight_env::weight_env(xcs_config_mgr2& xcs_config) {
	if (!weight_env::init) {
		weight_env::init = true;
		if (!xcs_config.exist(tag_name()))
		{
			xcs_utility::error(class_name(), "constructor", "section <" + tag_name() + "> not found", 1);
		}
		try {
			num = xcs_config.Value(tag_name(), "num");
			
		}
		catch (const char* attribute) {
			string msg = "attribute \'" + string(attribute) + "\' not found in <" + tag_name() + ">";
			xcs_utility::error(class_name(), "constructor", msg, 1);
		}	
	}
	weight_env::init = true;
}

//Settings before starting a problem 
void weight_env::begin_problem(const bool explore){
	current_reward = 0;

    //Set input
	real_inputs tmp(num);
	for (int i = 0; i < num; i++)
		tmp.set_input(i, input[i]);
	inputs = tmp;

    //Initialize weight 
	init_weight.clear();
	final_weight.clear();
	init_env();
}

// If the problem is solved, you can stop.
bool weight_env::stop() const
{
	bool res =  this->finished();
        return res;
}


void weight_env::perform(const t_action& action) {
	//TODO: Don’t know what the specific action is, so only assume that the current action is to choose a weight.
	unsigned long	act;
	act = action.value();
	double selected = final_weight[act];

	//TODO: Perform the selected action.
	//...
	//...
	
	if (finished()) {
		current_reward = reward_from_file;
	}
	else {
		current_reward = 0;
	}
	action_weight << act << ",";
}

void weight_env::trace(ostream& output) const {
	string information = action_weight.str();
	output << information;
}

void weight_env::reset_input() {
	reset_problem();
}

bool weight_env::next_input() {
	return next_problem();
}

void weight_env::reset_problem() {
	init_weight.clear();
	final_weight.clear();
	weight_init();
	current_reward = 0;
}

bool weight_env::next_problem() {
	if (finished()) {
		reset_problem();
		return true;
	}
	else {
		return false;
	}
}

void weight_env::save_state(ostream& output) const {
	output << endl;
	for (int i = 0; i < num; i++)
	{
		output << final_weight[i] << endl;
	}
	//current configuration or state?

}

void weight_env::restore_state(istream& input) {
	double x;
	for (int i = 0; i < num; i++)
	{
		input >> x;
		final_weight[i] = x;
	}
	//current configuration or state?
}

void weight_env::setInput(vector<double>& inp) {
	weight_env::input = inp;
}

void weight_env::setRewardFromFile(double re){
	weight_env::reward_from_file = re;
}

void weight_env::weight_init() {
	//Initialize the vector of weight
	double sum = 1;
	double weight = sum / num;
	for (int i = 0; i < num; i++) {
		init_weight.push_back(weight);
	}
	for (int i = 0; i < num; i++) {
		final_weight.push_back(weight);
	}
}

bool weight_env::finished() const {
	//TODO: Determine whether the problem is solved.
	return true;
}

// Pass the result of weight to the main function.
void weight_env::getWeight(vector<double>& weight){
    weight.assign(final_weight.begin(),final_weight.end());
}