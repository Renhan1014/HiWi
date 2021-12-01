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
			input_dim = xcs_config.Value(tag_name(), "input dim");
			weight_dim = xcs_config.Value(tag_name(), "weight dim");
			step = xcs_config.Value(tag_name(), "step");
			number_of_actions = xcs_config.Value(tag_name(), "number of actions");
		}
		catch (const char* attribute) {
			string msg = "attribute \'" + string(attribute) + "\' not found in <" + tag_name() + ">";
			xcs_utility::error(class_name(), "constructor", msg, 1);
		}	
	}
	//exp.create_inputs(input);
	//exp.create_target(input);
	//exp.print();
	inputs.set_dim(input_dim);
	weight_env::init = true;
	//cout<<"inputs is: "<<inputs<<endl;
}

//Settings before starting a problem 
void weight_env::begin_problem(const bool explore){
	current_reward = 0;
	selected_action = 0;
    action_weight.str("");
    final_weight.clear();
	input.clear();

    //exp.reset();
    //Initialize weight 
	//init_weight.clear();
	//final_weight.clear();
	//init_env();
}

// If the problem is solved, you can stop.
bool weight_env::stop() const
{
	//
    return false;
}

void weight_env::get_action_from_xcs(const t_action& action){
	unsigned long	act;
	act = action.value();
	selected_action = act;

	final_weight = weights[selected_action];
	
	//cout<<"in env: final weight: "<<endl;
	//for(int i = 0; i<final_weight.size();i++){
	//	cout << final_weight[i]<<endl;
	//}
	action_weight << act << ",";
}

/*
void weight_env::perform(){
	//exp.perform(input, final_weight);
	//current_reward = exp.get_reward();
}
*/

void weight_env::perform(const t_action& action) {
	// we do not need this function any more
	//because the action is performed outside the system
}

/*
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
*/

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
	//weight_init();
	current_reward = 0;
	selected_action = 0;
	action_weight.str("");
	final_weight.clear();
	input.clear();
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
	for (int i = 0; i < weight_dim; i++)
	{
		output << final_weight[i] << endl;
	}
	//current configuration or state?

}

void weight_env::restore_state(istream& input) {
	double x;
	for (int i = 0; i < weight_dim; i++)
	{
		input >> x;
		final_weight[i] = x;
	}
	//current configuration or state?
}

void weight_env::setInput(vector<double>& inp) {
	input = inp;
	//cout<<"inputs is: "<<inputs<<endl;
	for (int i = 0; i < input_dim; i++)
		inputs.set_input(i, inp[i]);
	//cout <<"input: "<<inputs.string_value()<<endl;
	//cout<<"inputs is: "<<inputs<<endl;
	//cout<<"in envir, the input address: "<<&inputs<<endl;
}

void weight_env::setRewardFromOut(double re){
	current_reward = re;
}

void weight_env::weight_init() {
	//Initialize the vector of weight /action
    weights.resize(number_of_actions);
    for(int a=0;a<number_of_actions;a++){
        weights[a].resize(weight_dim); 
    }

    vector <double> all_weights;
    double i, j , k;
    int index;
    index = 0;
    for (i = 0.0; (1.1 - i) > 0.001; i+=0.1) {
        for (j = 1.0 - i; (0.1 + j) > 0.001; j-=0.1) {
            k = 1.0 - i - j;
            all_weights.push_back(fabs(i));
            all_weights.push_back(fabs(j));
            all_weights.push_back(fabs(k));
            //printf("Weights for index %i: %f %f %f\n", index, fabs(i), fabs(j), fabs(k));
            index++;
        }
    }
    weights[0][0]= 1.0/3;
    weights[0][1]= 1.0/3;
    weights[0][2]= 1.0/3;
    for(int i = 1; i<weights.size();i++){
        for(int j = 0; j<weights[0].size();j++){
            weights[i][j] = all_weights[(i-1)*weight_dim+j];
        }
    }
    
	
    /*
    for(int i = 0; i<weights.size();i++){
        printf("Weights for index %i: %f %f %f\n", i, weights[i][0], weights[i][1], weights[i][2]);
    }
	*/
	
}

bool weight_env::finished() const {
	return false;
}

// Pass the result of weight to the main function.
void weight_env::getWeightAndAction(vector<double>& weight, unsigned long& action){
    weight.assign(final_weight.begin(),final_weight.end());
	action = selected_action;
}


t_state weight_env::get_state(){
	//cout<<"in get_state(),the input is: "<<inputs<<endl;
	return this->inputs;
}
