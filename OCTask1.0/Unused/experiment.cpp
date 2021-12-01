#include "experiment.hpp"
//using namespace std;

experiment::experiment()
{
	input_size = 3;
	min_input = 1.0;
	max_input = 15.0;
	reward = -1.0;
	res = 0;
	target = -1.0;
	srand(time(0));
}

void experiment::create_inputs(vector<double>& input) {
	//srand(time(0));
	for (int i = 0; i < input_size; i++) {
		double ele = rand()* ((max_input - min_input) / RAND_MAX) + min_input;
		input.push_back(ele);
	}
	
	cout << "the created input is: " << endl;
	for (int i = 0; i < input_size; i++) {
		cout << input[i] <<endl;
	}
}

void experiment::create_target(vector<double>& input) {
	double max = 0;
	for (int i = 0; i<input.size();i++) {
		if (max < input[i]) max = input[i];
	}
	target = max * 0.8;
}
void experiment::perform(vector<double>& input, vector<double>& weight) {
	res = 0;
	for (int i = 0; i < input_size; i++) {
		res = res + input[i] * weight[i];
	}
	
	if (res >= target) {
		reward = 100;
	} else {
		reward = 0;
	}
}

bool experiment::finished() const{
         bool finished = false;
	if (res >= target) {
		finished = true;
	}
	else {
		finished = false;
	}
      return finished;
}

double experiment::get_reward() {
	return reward;
}
void  experiment::print() {
	cout<<"the input size is " << input_size << endl;
	cout << "the min input is " << min_input << endl;
	cout << "the max input is " << max_input << endl;
	cout << "the reward is " << reward << endl;
	cout << "the target is " << target << endl;
	cout << "the res is " << res << endl;
}

void  experiment::reset(){
	reward = -1.0;
	res = 0;
}
