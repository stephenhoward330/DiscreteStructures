#include "Interpreter.h"

void Interpreter::interpretSchemes() {
	vector<Predicate> schemesVector = datalogProgram.getSchemes();
	string name;
	Scheme scheme;
	vector<Parameter> paramVector;
	for (unsigned int i = 0; i < schemesVector.size(); i++) {
		name = schemesVector.at(i).getID();
		paramVector = schemesVector.at(i).getParamVector();
		scheme.clear();
		for (unsigned int j = 0; j < paramVector.size(); j++) {
			scheme.push_back(paramVector.at(j).getIDstring());
		}
		//Scheme scheme = stringVector;
		Relation newRelation(name, scheme);
		pair<string, Relation> relationPair = { name, newRelation };
		database.addRelationPair(relationPair);
	}
}

void Interpreter::interpretFacts() {
	vector<Predicate> factsVector = datalogProgram.getFacts();
	string name;
	Tuple newTuple;
	vector<Parameter> paramVector;
	for (unsigned int i = 0; i < factsVector.size(); i++) {
		name = factsVector.at(i).getID();
		//cout << name;
		paramVector = factsVector.at(i).getParamVector();
		newTuple.clear();
		for (unsigned int j = 0; j < paramVector.size(); j++) {
			newTuple.push_back(paramVector.at(j).getIDstring());
			//cout << " " << paramVector.at(j).getIDstring();
		}
		database.addNewTuple(name, newTuple);
		//cout << endl;
	}
	
}

void Interpreter::evaluateQueries() {
	string idCheck;
	vector<Predicate> queriesVector = datalogProgram.getQueries();
	string name;
	vector<Parameter> paramVector;
	vector<int> projectVector;
	Scheme renameVector;
	bool derek;
	for (unsigned int i = 0; i < queriesVector.size(); i++) {
		name = queriesVector.at(i).getID();
		Relation newRelation = database.getRelation(name);
		queriesVector.at(i).toString();
		cout << "? ";
		paramVector = queriesVector.at(i).getParamVector();
		projectVector.clear();
		renameVector.clear();
		for (unsigned int j = 0; j < paramVector.size(); j++) {
			derek = false;
			idCheck = paramVector.at(j).getIDstring().substr(0, 1);
			if (idCheck == "'") {
				newRelation = database.SELECT(newRelation, j, paramVector.at(j).getIDstring());
			}
			else if (j < paramVector.size() - 1) {
				for (unsigned int l = 0; l < renameVector.size(); l++) {
					if (renameVector.at(l) == paramVector.at(j).getIDstring()) derek = true;
				}
				if (derek == false) {
					renameVector.push_back(paramVector.at(j).getIDstring());
					projectVector.push_back(j);
				}
				for (unsigned int k = j + 1; k < paramVector.size(); k++) {
					if (paramVector.at(j).getIDstring() == paramVector.at(k).getIDstring()) {
						newRelation = database.SELECT(newRelation, j, k);
					}
				}
			}
			else {
				for (unsigned int l = 0; l < renameVector.size(); l++) {
					if (renameVector.at(l) == paramVector.at(j).getIDstring()) derek = true;
				}
				if (derek == false) {
					renameVector.push_back(paramVector.at(j).getIDstring());
					projectVector.push_back(j);
				}
			}
		}
		newRelation = database.PROJECT(newRelation, projectVector);
		newRelation = database.RENAME(newRelation, renameVector);
		database.toString(newRelation);
	}
}
