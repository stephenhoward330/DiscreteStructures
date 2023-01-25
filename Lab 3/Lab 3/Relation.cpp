#include "Relation.h"
#include <iostream>

Relation Relation::SELECT(int IDX1, int IDX2) {
	Relation newRelation(name, scheme);

	for (set<Tuple>::iterator iter = tupleSet.begin(); iter != tupleSet.end(); iter++) {
		Tuple newTuple = *iter;
		if (newTuple.at(IDX1) == newTuple.at(IDX2)) {
			newRelation.addTuple(newTuple);
		}
	}

	return newRelation;
}

Relation Relation::SELECT(int IDX, string val) {
	Relation newRelation(name, scheme);

	for (set<Tuple>::iterator iter = tupleSet.begin(); iter != tupleSet.end(); iter++) {
		Tuple newTuple = *iter;
		if (newTuple.at(IDX) == val) {
			newRelation.addTuple(newTuple);
		}
	}

	return newRelation;
}

Relation Relation::PROJECT(vector<int> IDXVector) {
	Scheme newScheme;
	
	for (unsigned int i = 0; i < IDXVector.size(); i++) {
		newScheme.push_back(scheme.at(IDXVector.at(i)));
	}

	Relation newRelation(name, newScheme);

	Tuple newTuple;

	for (set<Tuple>::iterator iter = tupleSet.begin(); iter != tupleSet.end(); iter++) {
		Tuple currTuple = *iter;
		newTuple.clear();
		for (unsigned int j = 0; j < IDXVector.size(); j++) {
			newTuple.push_back(currTuple.at(IDXVector.at(j)));
		}
		newRelation.addTuple(newTuple);
	}

	return newRelation;
}

Relation Relation::RENAME(Scheme nameVector) {
	Relation newRelation(name, nameVector);

	for (set<Tuple>::iterator iter = tupleSet.begin(); iter != tupleSet.end(); iter++) {
		newRelation.addTuple(*iter);
	}

	return newRelation;
}

void Relation::toString() {
	if (tupleSet.empty()) cout << "No" << endl;
	else if (scheme.empty()) cout << "Yes(1)" << endl;
	else {
		cout << "Yes(" << tupleSet.size() << ")" << endl;
		for (set<Tuple>::iterator iter = tupleSet.begin(); iter != tupleSet.end(); iter++) {
			Tuple newTuple = *iter;
			for (unsigned int i = 0; i < scheme.size(); i++) {
				if (i == 0) cout << "  ";
				else if (i > 0) cout << ", ";
				cout << scheme.at(i) << "=" << newTuple.at(i);
			}
			cout << endl;
		}
	}
}
