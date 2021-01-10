#include <iostream>
#include "integer_action.hpp"
int main(int argc, char *argv[]){

	const unsigned long no_actions = 4;
        integer_action act(no_actions);
	cout<<"action is "<<act.class_name()<<endl;
	cout<<"action numbert is "<<act.actions()<<endl;
	return 0;




}
