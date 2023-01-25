#ifndef RELATION_H
#define RELATION_H

#include "Tuple.h"
#include "Scheme.h"
#include <set>
#include <string>

using namespace std;

class Relation {
private:
	string name;
	Scheme scheme;
	set<Tuple> tupleSet;
public:
	Relation() {}
	Relation(string newName, Scheme newScheme) {
		name = newName;
		scheme = newScheme;
	}
	
	Relation SELECT(int IDX1, int IDX2);
	Relation SELECT(int IDX, string val);
	Relation PROJECT(vector<int> IDXVector);
	Relation RENAME(Scheme nameVector);

	void addTuple(Tuple newTuple) {
		tupleSet.insert(newTuple);
	}

	void toString();
};

#endif