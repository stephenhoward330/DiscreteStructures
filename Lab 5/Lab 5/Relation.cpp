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

Relation Relation::UNION(Relation relationTwo) { //assuming the two relations have the same scheme
	Relation newRelation(name, scheme);
	for (set<Tuple>::iterator iter = tupleSet.begin(); iter != tupleSet.end(); iter++) {
		Tuple newTuple = *iter;
		newRelation.addTuple(newTuple);
	}
	int sizePrior;
	int sizeAfter;
	for (set<Tuple>::iterator iter = relationTwo.tupleSet.begin(); iter != relationTwo.tupleSet.end(); iter++) {
		sizePrior = newRelation.getTupleSetSize();
		Tuple newTuple = *iter;
		newRelation.addTuple(newTuple);
		sizeAfter = newRelation.getTupleSetSize();
		if (sizeAfter > sizePrior) {
			for (unsigned int i = 0; i < scheme.size(); i++) {
				if (i == 0) cout << "  ";
				else if (i > 0) cout << ", ";
				cout << scheme.at(i) << "=" << newTuple.at(i);
			}
			cout << endl;
		}
	}
	return newRelation;
}

Relation Relation::JOIN(Relation relationTwo) {
	Scheme schemeTwo = relationTwo.getScheme();
	Scheme newScheme = joinSchemes(scheme, schemeTwo);
	Relation newRelation(name, newScheme);

	for (set<Tuple>::iterator iter1 = tupleSet.begin(); iter1 != tupleSet.end(); iter1++) {
		for (set<Tuple>::iterator iter2 = relationTwo.tupleSet.begin(); iter2 != relationTwo.tupleSet.end(); iter2++) {
			Tuple tupleOne = *iter1;
			Tuple tupleTwo = *iter2;
			if (joinable(tupleOne, tupleTwo, scheme, relationTwo.scheme)) {
				Tuple newTuple = joinTuples(tupleOne, tupleTwo, scheme, relationTwo.scheme);
				newRelation.addTuple(newTuple);
			}
		}
	}

	return newRelation;
}

Scheme Relation::joinSchemes(Scheme schemeOne, Scheme schemeTwo) {
	bool isNew = false;
	Scheme finalScheme = schemeOne;
	for (unsigned int i = 0; i < schemeTwo.size(); i++) {
		isNew = true;
		for (unsigned int j = 0; j < schemeOne.size(); j++) {
			if (schemeTwo.at(i) == schemeOne.at(j)) {
				isNew = false;
			}
		}
		if (isNew) finalScheme.push_back(schemeTwo.at(i));
	}
	return finalScheme;
}

bool Relation::joinable(Tuple tupleOne, Tuple tupleTwo, Scheme schemeOne, Scheme schemeTwo) {
	bool joinable = true;
	for (unsigned int i = 0; i < schemeOne.size(); i++) {
		for (unsigned int j = 0; j < schemeTwo.size(); j++) {
			if ((schemeOne.at(i) == schemeTwo.at(j)) && (tupleOne.at(i) != tupleTwo.at(j))) joinable = false;
		}
	}

	return joinable;
}

Tuple Relation::joinTuples(Tuple tupleOne, Tuple tupleTwo, Scheme schemeOne, Scheme schemeTwo) {
	bool isNew = false;
	Tuple newTuple = tupleOne;
	for (unsigned int i = 0; i < schemeTwo.size(); i++) {
		isNew = true;
		for (unsigned int j = 0; j < schemeOne.size(); j++) {
			if (schemeTwo.at(i) == schemeOne.at(j)) {
				isNew = false;
			}
		}
		if (isNew) newTuple.push_back(tupleTwo.at(i));
	}

	return newTuple;
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
