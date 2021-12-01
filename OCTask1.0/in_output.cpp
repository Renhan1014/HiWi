
#include <iostream>
#include "in_output.hpp"
#include <stdlib.h>

in_output::in_output(){
    input_sys.clear();
	weight.clear();
	reward_sys = -1;
    selected_action = -1;
}


void 
in_output::receiveInput(struct dls_system_snapshot sys_snap){
    input_sys.clear();
    input_sys.push_back(sys_snap.n_tasks);
    input_sys.push_back(sys_snap.longest_path);
    input_sys.push_back(sys_snap.max_width);
    input_sys.push_back(sys_snap.max_cpu_temp);
    input_sys.push_back(sys_snap.gpu_temp);
    input_sys.push_back(sys_snap.avg_pu_waiting_time);
}

void 
in_output::receiveReward(int reward){
    reward_sys = reward;
}

void 
in_output::sendAction(double action[], unsigned long& action_num){
    for(int i = 0; i < weight.size();i++){
        action[i] = weight[i];
    }
    
    action_num = selected_action;

}
	
void 
in_output::get_Input(vector<long long>& input){
    input.assign(input_sys.begin(),input_sys.end());
}

void 
in_output::get_Reward(int& re){
    re = reward_sys;
}

void 
in_output::get_Action_from_XCS(vector<double>& weight_xcs, unsigned long action_xcs){
    weight.assign(weight_xcs.begin(), weight_xcs.end());
    
    selected_action = action_xcs;
   
}


void
in_output::print_in_out(){
    cout<< "in_out is: "<<endl;
    cout<< "the reward is: "<< reward_sys <<endl;

    cout<< "the input is: "<< endl;
    for(int i = 0; i<input_sys.size(); i++){
        cout<< "the input["<<i<<"] is: " << input_sys[i] << endl;
    }

    cout<< "the output is: "<< endl;
    for(int i = 0; i<weight.size(); i++){
        cout<< "the weight["<<i<<"] is: " << weight[i] << endl;
    }
    cout<<endl;
	
}
























/*
void 
In_Output::get_Inp_From_File(string file_name){
    std::string name = file_name;
    std::fstream in;

    in.open(name.c_str());
    std::getline(in, read_input);
    std::getline(in, read_reward);
    in.close();

    //cout<< read_input <<endl;
    //cout<< read_reward <<endl;
}

void 
In_Output::get_Inp_To_Vec(){
    size_t begin = read_input.find('(');
    begin = begin +1;
    size_t end = read_input.find(')');
    //size_t length = read_input.length();
   
    vector<string> tem;
    size_t last = begin;
    size_t index = read_input.find_first_of(',', last);

    while (index!= std::string::npos){
        tem.push_back(read_input.substr(last, index-last));
        last = index +1;
        index = read_input.find_first_of(',', last);
    }

    if(index - last >0){
        //cout << "now the last is " << last << endl;
        tem.push_back(read_input.substr(last,end-last));
    }

    
    cout<< "tem is :" << endl;
    for(int i = 0; i < tem.size(); i++){
       cout<< tem[i] << endl;
    }
    

    for(int i = 0; i < tem.size(); i++){
       char *p=(char*)tem[i].c_str(); 
       double res = strtod(p, NULL);
       input.push_back(res);
    }

}

void 
In_Output::get_Reward_To_Value(){
    char *p=(char*)read_reward.c_str(); 
    reward = strtod(p, NULL);
    //cout << "reward is: " << reward << endl;
}
void 
In_Output::put_Output_To_String(vector<double>& weight){
    for(int i = 0; i < weight.size(); i++){
       std::string weig = read_Inp::fromDoubleToString(weight[i]);
       get_output.push_back(weig);
    }
}

string 
In_Output::fromDoubleToString(double val){
    std::string ele;
    std::stringstream ss;
    ss << val;
    ss >> ele;
    return ele;
}
void 
In_Output::put_Output_To_File(string file_name){
    output = "(";
    for(int i = 0; i < get_output.size(); i++){
        output = output + get_output[i]+ "," + " ";
    }
    size_t end = output.length() -2;
    output.replace(end,1,")");
    cout << "output is: " << output << endl;

    std::string name = file_name.c_str();
    std::fstream out;

    out.open(name.c_str(),ios_base::out);
    if (!out.is_open()) {
        cout << "failed to open " << name << '\n';
    } else {
        out << output << endl;
    }
    out.close();
}

vector<double>
In_Output::get_Input(){
    return input;
}

double
In_Output::get_reward(){
    return reward;
}

*/
