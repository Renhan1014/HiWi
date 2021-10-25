#include <fstream>
#include <iostream>
#include <sstream>
#include "read_Inp.hpp"
#include <stdlib.h>
read_Inp::read_Inp(){

}

void 
read_Inp::get_Inp_From_File(string file_name){
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
read_Inp::get_Inp_To_Vec(){
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

    /*
    cout<< "tem is :" << endl;
    for(int i = 0; i < tem.size(); i++){
       cout<< tem[i] << endl;
    }
    */

    for(int i = 0; i < tem.size(); i++){
       char *p=(char*)tem[i].c_str(); 
       double res = strtod(p, NULL);
       input.push_back(res);
    }

}

void 
read_Inp::get_Reward_To_Value(){
    char *p=(char*)read_reward.c_str(); 
    reward = strtod(p, NULL);
    //cout << "reward is: " << reward << endl;
}
void 
read_Inp::put_Output_To_String(vector<double>& weight){
    for(int i = 0; i < weight.size(); i++){
       std::string weig = read_Inp::fromDoubleToString(weight[i]);
       get_output.push_back(weig);
    }
}

string 
read_Inp::fromDoubleToString(double val){
    std::string ele;
    std::stringstream ss;
    ss << val;
    ss >> ele;
    return ele;
}
void 
read_Inp::put_Output_To_File(string file_name){
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
read_Inp::get_Input(){
    return input;
}

double
read_Inp::get_reward(){
    return reward;
}


