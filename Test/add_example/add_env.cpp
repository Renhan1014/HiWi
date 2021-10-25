#include <cmath>
#include "xcs_utility.hpp"
#include "xcs_random.hpp"

#include "add_env.hpp"

using namespace std;

bool	add_env::init = false;

add_env::add_env(xcs_config_mgr2& xcs_config) {
	if (!add_env::init) {
		add_env::init = true;
		if (!xcs_config.exist(tag_name()))
		{
			xcs_utility::error(class_name(), "constructor", "section <" + tag_name() + "> not found", 1);
		}
		try {
			percent = xcs_config.Value(tag_name(), "percent");
			num = xcs_config.Value(tag_name(), "num");
			step = xcs_config.Value(tag_name(), "step");
		}
		catch (const char* attribute) {
			string msg = "attribute \'" + string(attribute) + "\' not found in <" + tag_name() + ">";
			xcs_utility::error(class_name(), "constructor", msg, 1);
		}


		
	}
	add_env::init = true;
}
void add_env::begin_problem(const bool explore){
	current_reward = 0;
	real_inputs tmp(num);

	for (int i = 0; i < num; i++)
		tmp.set_input(i, input[i]);
	inputs = tmp;
	init_weight.clear();
	final_weight.clear();
	init_env();
}

bool add_env::stop() const
{
	bool res =  this->greaterThanTarget();
        return res;
}
void add_env::perform(const t_action& action) {
	unsigned long	act;
	act = action.value();
	double selected = final_weight[act];
	selected = selected + step;
	double others = (1 - selected) / (num - 1);
	for (int i = 0; i < num; i++) {
		final_weight[i] = others;
	}
	final_weight[act] = selected;
	if (greaterThanTarget()) {
		current_reward = reward_from_file;
	}
	else {
		current_reward = 0;
	}
	action_weight << act << ",";
}

void add_env::trace(ostream& output) const {
	string information = action_weight.str();
	output << information;
}

void add_env::reset_input() {
	reset_problem();
}

bool add_env::next_input() {
	return next_problem();
}

void add_env::reset_problem() {
	init_weight.clear();
	final_weight.clear();
	init_env();
	current_reward = 0;
}
bool add_env::next_problem() {
	if (greaterThanTarget()) {
		reset_problem();
		return true;
	}
	else {
		return false;
	}
}

void add_env::save_state(ostream& output) const {
	output << endl;
	for (int i = 0; i < num; i++)
	{
		output << final_weight[i] << endl;
	}
	//current configuration or state?

}
void add_env::restore_state(istream& input) {
	double x;
	for (int i = 0; i < num; i++)
	{
		input >> x;
		final_weight[i] = x;
	}
	//current configuration or state?
}

void add_env::setInput(vector<double>& inp) {
	add_env::input = inp;
}

void add_env::setRewardFromFile(double re){
	add_env::reward_from_file = re;
}

void add_env::init_env() {
	double max = *max_element(input.begin(), input.end());
	target = percent * max;
        double sum = 1;
	double weight = sum / num;
       // cout<<"weight is " << weight<<endl;
	for (int i = 0; i < num; i++) {
		init_weight.push_back(weight);
	}
	for (int i = 0; i < num; i++) {
		final_weight.push_back(weight);
	}
}

bool add_env::greaterThanTarget() const {
	double res = 0;
	for (int i = 0; i < num; i++) {
		res = res + final_weight[i] * input[i];
	}
//        cout<<"now the res is "<< res <<endl;
	if (res >= target) {
        //        trace(cout);
          //      cout <<"."<<endl;
		return true;
	}
	else {
		return false;
	}
}

void 
add_env::getWeight(vector<double>& weight){
    weight.assign(final_weight.begin(),final_weight.end());
}