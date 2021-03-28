#include "xcs_definitions.hpp"
#include "xcs_random.hpp"
#include "xcs_config_mgr2.hpp"

using namespace std;

#ifndef __RULE_GENERATOR__
#define __RULE_GENERATOR__


class rule_generator
{
public:
	//! pointer to a classifier
	typedef t_classifier* t_classifier_ptr;

	typedef vector<t_classifier*>			t_classifier_set;

	//! index in set of classifiers
	/*!
	 * \type t_set_iterator
	 * \brief represent an iterator over a set of classifiers
	 */
	typedef vector<t_classifier*>::iterator	t_set_iterator;
	typedef vector<t_classifier*>::const_iterator	t_set_const_iterator;

public:
	unsigned long	match(const t_state& detectors);
	void    do_cover_GA(const t_state& current_input);
	void    do_simulator(t_classifier_ptr cl);
	t_classifier_ptr get_classifier();
};
