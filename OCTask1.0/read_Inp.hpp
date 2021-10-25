#ifndef __READ_INP__
#define __READ_INP__

#include <vector>
#include <string>

using namespace std;
class read_Inp {
	public:	
	string class_name() const { return string("read_Input"); };
	read_Inp();
	~read_Inp(){};

    void get_Inp_From_File(string file_name);
	
	void get_Inp_To_Vec();
	void get_Reward_To_Value();

	vector<double> get_Input();
	double get_reward();

	void put_Output_To_String(vector<double>& weight);
	void put_Output_To_File(string file_name);


	private:
    string read_input;
	vector<double> input;

	string read_reward;
	double reward;

	vector<string> get_output;
	string output;
	
	string fromDoubleToString(double val);




};

#endif
