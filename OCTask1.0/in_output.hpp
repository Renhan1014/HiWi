#ifndef __IN_OUTPUT__
#define __IN_OUTPUT__

#include <vector>
#include <string>

using namespace std;
class in_output {
	public:	
	string class_name() const { return string("read_Input"); };
	in_output();
	//~in_output(){};

    //void get_Inp_From_File(string file_name);
    

	void receiveInput(struct dls_system_snapshot sys_snap);
	void receiveReward(int reward);
	void sendAction(double action[], unsigned long &action_num);
	
	void get_Input(vector<long long>& input);
    void get_Reward(int& re);
    void get_Action_from_XCS(vector<double>& weight_xcs, unsigned long action_xcs);

	//void put_Output_To_String(vector<double>& weight);
	//void put_Output_To_File(string file_name);
    void print_in_out();

	private:
    //string read_input;
	vector<long long> input_sys;
	//string read_reward;
	vector<double> weight;
	int reward_sys;
	unsigned long selected_action;



};

struct dls_system_snapshot {
    int n_tasks ;
    long long longest_path ;
    long long max_width;
    
    long long max_cpu_temp;
    long long gpu_temp;
    long long avg_pu_waiting_time;
    
};

#endif
