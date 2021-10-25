
cxx=g++
opt= -I. -lm
TARGET=main
OBJECTS= *.o
ZIP= *.gz
REPORT = *.mp6-10

main:main.o real_inputs.o integer_action.o experiment_mgr.o generic.o weight_env.o real_interval_condition.o xcs_classifier.o xcs_classifier_system.o xcs_config_mgr2.o xcs_random.o xcs_utility.o read_Inp.o rule_generator.o

	$(cxx) -g main.o real_inputs.o integer_action.o experiment_mgr.o generic.o weight_env.o real_interval_condition.o xcs_classifier.o xcs_classifier_system.o xcs_config_mgr2.o xcs_random.o xcs_utility.o read_Inp.o rule_generator.o -o main

main.o: xcs_main.cpp experiment_mgr.hpp xcs_definitions.hpp read_Inp.hpp
	$(cxx) $(opt) -c  xcs_main.cpp -o main.o

real_inputs.o: real_inputs.cpp real_inputs.hpp inputs_base.hpp xcs_utility.hpp
	$(cxx) $(opt) -c real_inputs.cpp -o real_inputs.o

integer_action.o: integer_action.cpp integer_action.hpp xcs_random.hpp action_base.hpp rl_definitions.hpp xcs_config_mgr2.hpp
	$(cxx) $(opt) -c integer_action.cpp -o integer_action.o

experiment_mgr.o: experiment_mgr.cpp experiment_mgr.hpp xcs_utility.hpp xcs_definitions.hpp xcs_random.hpp xcs_config_mgr2.hpp
	$(cxx) $(opt) -c experiment_mgr.cpp -o experiment_mgr.o

generic.o: generic.cpp generic.hpp
	$(cxx) $(opt) -c generic.cpp -o generic.o

weight_env.o: weight_env.cpp weight_env.hpp xcs_random.hpp xcs_utility.hpp rl_definitions.hpp environment_base.hpp xcs_config_mgr2.hpp
	$(cxx) $(opt) -c weight_env.cpp -o weight_env.o

real_interval_condition.o: real_interval_condition.cpp xcs_definitions.hpp xcs_random.hpp xcs_config_mgr2.hpp condition_base.hpp real_interval_condition.hpp rl_definitions.hpp real_inputs.hpp interval.hpp
	$(cxx) $(opt) -c real_interval_condition.cpp -o real_interval_condition.o

xcs_classifier.o: xcs_classifier.cpp xcs_classifier.hpp xcs_definitions.hpp
	$(cxx) $(opt) -c xcs_classifier.cpp -o xcs_classifier.o

xcs_classifier_system.o: xcs_classifier_system.cpp xcs_classifier_system.hpp xcs_definitions.hpp xcs_random.hpp xcs_config_mgr2.hpp rule_generator.hpp
	$(cxx) $(opt) -c xcs_classifier_system.cpp -o xcs_classifier_system.o

xcs_config_mgr2.o: xcs_config_mgr2.cpp xcs_config_mgr2.hpp generic.hpp xcs_utility.hpp
	$(cxx) $(opt) -c xcs_config_mgr2.cpp -o xcs_config_mgr2.o

xcs_random.o: xcs_random.cpp xcs_random.hpp xcs_config_mgr2.hpp
	$(cxx) $(opt) -c xcs_random.cpp -o xcs_random.o

xcs_utility.o: xcs_utility.cpp xcs_utility.hpp
	$(cxx) $(opt) -c xcs_utility.cpp -o xcs_utility.o

read_Inp.o: read_Inp.cpp read_Inp.hpp
	$(cxx) $(opt) -c read_Inp.cpp -o read_Inp.o

rule_generator.o: rule_generator.cpp rule_generator.hpp xcs_random.hpp xcs_classifier.hpp
	$(cxx) $(opt) -c rule_generator.cpp -o rule_generator.o

clean:
	@\rm -f $(OBJECTS) $(ZIP) $(REPORT) main report.add-*

