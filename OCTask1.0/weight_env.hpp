#ifndef __WEIGHT_ENV__
#define __WEIGHT_ENV__

#include <cassert>
#include "rl_definitions.hpp"
#include "environment_base.hpp"
#include "xcs_config_mgr2.hpp"
#include <sstream>
//#include "experiment.hpp"

using namespace std;

class weight_env : public virtual environment_base
{
public:
	string class_name() const { return string("weight_env"); };
	string tag_name() const { return string("environment::weight"); };
	weight_env(xcs_config_mgr2&);
	weight_env();
	void begin_experiment() {};
	void end_experiment() {};

	void begin_problem(const bool explore);
	void end_problem() {};

	bool stop() const;

    //void perform();
	void perform(const t_action& action);
	void get_action_from_xcs(const t_action& action);

	void trace(ostream& output) const;

	void reset_input();
	bool next_input();

	void reset_problem();
	bool next_problem();

	void save_state(ostream& output) const;
	void restore_state(istream& input);

	virtual double reward() const { assert(current_reward == weight_env::current_reward); return current_reward; };

	virtual t_state state() const { return inputs; };
    t_state get_state() {return inputs;};
	bool allow_test() const { return true; };
	virtual bool single_step() const { return false; };

	void setInput(vector<double>& inp);
	void weight_init();
	bool finished() const;
	void setRewardFromOut(double re);
	void getWeightAndAction(vector<double>& weight, unsigned long& action);
	unsigned long getAction() {return selected_action; };

private:
	static bool			init;
	t_state			inputs;
	//bool				first_problem;
	double				current_reward;
	//bool				solved;
	//vector<double>      init_weight;
	vector<vector <double> > weights;
	vector<double>      final_weight;
	vector<double>      input;
	unsigned long  input_dim;
	unsigned long weight_dim;
	double step;
	unsigned long number_of_actions;
	ostringstream	action_weight;
	//double reward_from_outside;
	unsigned long selected_action;
	//experiment exp;
};
#endif
