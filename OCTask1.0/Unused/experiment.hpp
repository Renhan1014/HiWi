

#ifndef __EXPERIMENT__
#define __EXPERIMENT__
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

class experiment
{

public:
	
	string class_name() const { return string("experiment"); };
	string tag_name() const { return string("experiment"); };
	experiment();

	void perform(vector<double>& input, vector<double>& weight);
	void create_inputs(vector<double>& input);
	void create_target(vector<double>& input);
	bool finished() const;
	double get_reward();
	void print();
	void reset();


private:
	int input_size;
	double min_input;
	double max_input;
	double reward;
	double target;
	double res;
	

};
#endif
