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

void Interpreter::evaluateRules() {
	vector<Rule> rulesVector = datalogProgram.getRules();
	Graph forwardGraph;
	Graph reverseGraph;
	reverseGraph = forwardGraph.makeGraphs(rulesVector);
	forwardGraph.toString();
	//cout << "Reverse ";
	//reverseGraph.toString();
	cout << endl << "Rule Evaluation" << endl;
	vector<int> topoVector = reverseGraph.topoSort();
	vector<vector<int>> sccVector = forwardGraph.scc(topoVector);
	for (unsigned int i = 0; i < sccVector.size(); i++) {
		vector<int> miniVector = sccVector.at(i);
		if (miniVector.size() == 1) {
			cout << "SCC: R" << miniVector.at(0) << endl;
			if (forwardGraph.at(miniVector.at(0)).hasLoop(miniVector.at(0))) {
				evalRules(miniVector);
			}
			else evalRule(miniVector.at(0));
			cout << "R" << miniVector.at(0) << endl;
		}
		else {
			cout << "SCC: ";
			for (unsigned int j = 0; j < miniVector.size(); j++) {
				if (j > 0) cout << ",";
				cout << "R" << miniVector.at(j);
			}
			cout << endl;
			evalRules(miniVector);
			for (unsigned int j = 0; j < miniVector.size(); j++) {
				if (j > 0) cout << ",";
				cout << "R" << miniVector.at(j);
			}
			cout << endl;
		}
	}
}

void Interpreter::evalRule(int ruleNum) {
	vector<Rule> rulesVector = datalogProgram.getRules();
	vector<Relation> relationVector;
	vector<int> intVector;
	rulesVector.at(ruleNum).toString();
	cout << "." << endl;
	vector<Predicate> predicateVector = rulesVector.at(ruleNum).getPredicateVector();
	for (unsigned int j = 0; j < predicateVector.size(); j++) {
		Relation newRelation = evaluatePredicate(predicateVector.at(j));
		relationVector.push_back(newRelation);
	}
	while (relationVector.size() > 1) {
		Relation relationTwo = relationVector.back();
		relationVector.pop_back();
		Relation relationOne = relationVector.back();
		relationVector.pop_back();
		Relation relationThree = database.JOIN(relationOne, relationTwo);
		relationVector.push_back(relationThree);
	}
	Relation finalRelation = relationVector.front();
	Predicate headPredicate = rulesVector.at(ruleNum).getHeadPredicate();
	vector<Parameter> paramVector = headPredicate.getParamVector();
	Scheme finalScheme = finalRelation.getScheme();
	for (unsigned int k = 0; k < paramVector.size(); k++) {
		for (unsigned int j = 0; j < finalScheme.size(); j++) {
			if (finalScheme.at(j) == paramVector.at(k).getIDstring()) {
				intVector.push_back(j);
			}
		}
	}
	finalRelation = database.PROJECT(finalRelation, intVector);
	Scheme newScheme;
	for (unsigned int j = 0; j < paramVector.size(); j++) {
		newScheme.push_back(paramVector.at(j).getIDstring());
	}
	finalRelation = database.RENAME(finalRelation, newScheme);
	string head = headPredicate.getID();
	bool change = database.UNION(finalRelation, head);

	cout << "1 passes: ";
}

void Interpreter::evalRules(vector<int> ruleNumVector) {
	vector<Rule> rulesVector = datalogProgram.getRules();
	int numPasses = 0;
	bool changes = true;
	vector<Relation> relationVector;
	vector<int> intVector;
	while (changes) {
		changes = false;
		numPasses++;
		for (unsigned int i = 0; i < ruleNumVector.size(); i++) {
			intVector.clear();
			relationVector.clear();
			rulesVector.at(ruleNumVector.at(i)).toString();
			cout << "." << endl;
			vector<Predicate> predicateVector = rulesVector.at(ruleNumVector.at(i)).getPredicateVector();
			for (unsigned int j = 0; j < predicateVector.size(); j++) {
				Relation newRelation = evaluatePredicate(predicateVector.at(j));
				relationVector.push_back(newRelation);
			}
			while (relationVector.size() > 1) {
				Relation relationTwo = relationVector.back();
				relationVector.pop_back();
				Relation relationOne = relationVector.back();
				relationVector.pop_back();
				Relation relationThree = database.JOIN(relationOne, relationTwo);
				relationVector.push_back(relationThree);
			}
			Relation finalRelation = relationVector.front();
			Predicate headPredicate = rulesVector.at(ruleNumVector.at(i)).getHeadPredicate();
			vector<Parameter> paramVector = headPredicate.getParamVector();
			Scheme finalScheme = finalRelation.getScheme();
			for (unsigned int k = 0; k < paramVector.size(); k++) {
				for (unsigned int j = 0; j < finalScheme.size(); j++) {
					if (finalScheme.at(j) == paramVector.at(k).getIDstring()) {
						intVector.push_back(j);
					}
				}
			}
			finalRelation = database.PROJECT(finalRelation, intVector);
			Scheme newScheme;
			for (unsigned int j = 0; j < paramVector.size(); j++) {
				newScheme.push_back(paramVector.at(j).getIDstring());
			}
			finalRelation = database.RENAME(finalRelation, newScheme);
			string head = headPredicate.getID();
			bool change = database.UNION(finalRelation, head);
			if (change) changes = true;
		}
	}

	cout << numPasses << " passes: ";
}


void Interpreter::evaluateQueries() {
	vector<Predicate> queriesVector = datalogProgram.getQueries();
	cout << endl << "Query Evaluation" << endl;
	for (unsigned int i = 0; i < queriesVector.size(); i++) {
		queriesVector.at(i).toString();
		cout << "? ";
		Relation newRelation = evaluatePredicate(queriesVector.at(i));
		database.toString(newRelation);
	}
}

Relation Interpreter::evaluatePredicate(Predicate predicate) {
	string idCheck;
	string name = predicate.getID();
	Relation newRelation = database.getRelation(name);
	vector<Parameter> paramVector = predicate.getParamVector();
	vector<int> projectVector;
	Scheme renameVector;
	bool derek;
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

	return newRelation;
}