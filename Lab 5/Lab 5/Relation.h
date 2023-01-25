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
	Relation UNION(Relation relationTwo);
	Relation JOIN(Relation relationTwo);

	Scheme joinSchemes(Scheme schemeOne, Scheme schemeTwo);
	bool joinable(Tuple tupleOne, Tuple tupleTwo, Scheme schemeOne, Scheme schemeTwo);
	Tuple joinTuples(Tuple tupleOne, Tuple tupleTwo, Scheme schemeOne, Scheme schemeTwo);

	void addTuple(Tuple newTuple) {
		tupleSet.insert(newTuple);
	}

	int getTupleSetSize() { return tupleSet.size(); }
	Scheme getScheme() { return scheme; }

	void toString();
};

#endif