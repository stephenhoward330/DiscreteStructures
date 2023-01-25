#ifndef RULE_H
#define RULE_H

#include "Predicate.h"
#include <vector>

using namespace std;

class Rule {
private:
	Predicate headPredicate;
	vector<Predicate> predicateVector;
public:
	Rule(Predicate newHeadPredicate, vector<Predicate> newPredicateVector) {
		headPredicate = newHeadPredicate;
		predicateVector = newPredicateVector;
	}
	void toString() {
		headPredicate.toString();
		cout << " :- ";
		for (unsigned int i = 0; i < predicateVector.size(); i++) {
			predicateVector.at(i).toString();
			if (i < (predicateVector.size() - 1)) cout << ",";
		}
	}
};

#endif