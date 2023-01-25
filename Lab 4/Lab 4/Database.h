#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include "Relation.h"

using namespace std;

class Database {
private:
	map<string, Relation> relationMap;
public:
	void addRelationPair(pair<string, Relation> newRelationPair) {
		relationMap.insert(newRelationPair);
	}
	void addNewTuple(string name, Tuple tuple) {
		relationMap.at(name).addTuple(tuple);
	}
	Relation getRelation(string name) {
		return relationMap.at(name);
	}

	Relation SELECT(Relation relation, int IDX1, int IDX2) {
		Relation newRelation = relation.SELECT(IDX1, IDX2);
		return newRelation;
	}
	Relation SELECT(Relation relation, int IDX, string val) {
		Relation newRelation = relation.SELECT(IDX, val);
		return newRelation;
	}
	Relation PROJECT(Relation relation, vector<int> IDXVector) {
		Relation newRelation = relation.PROJECT(IDXVector);
		return newRelation;
	}
	Relation RENAME(Relation relation, Scheme nameVector) {
		Relation newRelation = relation.RENAME(nameVector);
		return newRelation;
	}
	bool UNION(Relation relation, string relationName) {
		bool change = false;
		int sizePrior = relationMap.at(relationName).getTupleSetSize();
		relationMap.at(relationName) = relationMap.at(relationName).UNION(relation);
		int sizeAfter = relationMap.at(relationName).getTupleSetSize();
		if (sizeAfter > sizePrior) change = true;
		return change;
	}
	Relation JOIN(Relation relationOne, Relation relationTwo) {
		Relation newRelation = relationOne.JOIN(relationTwo);
		return newRelation;
	}

	void toString(Relation newRelation) {
		newRelation.toString();
	}
};

#endif