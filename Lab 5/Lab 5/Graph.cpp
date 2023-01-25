#include "Graph.h"

Graph Graph::makeGraphs(vector<Rule> rulesVector) {
	Graph reverseGraph;
	for (unsigned int i = 0; i < rulesVector.size(); i++) {
		pair<int, Node> newPair;
		Node newNode;
		newPair = make_pair(i, newNode);
		this->insert(newPair);
		reverseGraph.insert(newPair);
	}
	
	for (unsigned int i = 0; i < rulesVector.size(); i++) {
		vector<Predicate> predVector = rulesVector.at(i).getPredicateVector();
		for (unsigned int j = 0; j < predVector.size(); j++) {
			for (unsigned int k = 0; k < rulesVector.size(); k++) {
				Predicate headPred = rulesVector.at(k).getHeadPredicate();
				if (headPred.getID() == predVector.at(j).getID()) {
					this->at(i).addEdge(k);
					reverseGraph.at(k).addEdge(i);
				}
			}
		}
	}
	return reverseGraph;
}

void Graph::dfsForest() {
	for (unsigned int i = 0; i < this->size(); i++) {
		//if (this->at(i).getVisitFlag() == false) dfs(this->at(i));
		if (this->at(i).getVisitFlag() == false) dfs(i);
	}
	for (unsigned int i = 0; i < this->size(); i++) {
		this->at(i).setFlag(false);
	}
}

void Graph::dfs(int i) {
	this->at(i).setFlag(true);
	set<int> adjaNodes = this->at(i).getAdjNodes();
	for (set<int>::iterator iter = adjaNodes.begin(); iter != adjaNodes.end(); iter++) {
		if (this->at(*iter).getVisitFlag() == false) {
			dfs(*iter);
		}
	}
	currentNum++;
	this->at(i).setPostNum(currentNum);
}

vector<int> Graph::topoSort() {
	dfsForest();
	vector<int> indexVector;
	for (unsigned int i = 0; i < this->size(); i++) {
		indexVector.push_back(this->at(i).getPostNum());
	}
	return indexVector;
}

vector<vector<int>> Graph::scc(vector<int> topoVector) {
	vector<vector<int>> mainVector;
	vector<int> sccVector;
	for (unsigned int i = this->size(); i > 0; i--) {
		sccVector.clear();
		for (unsigned int j = 0; j < topoVector.size(); j++) {
			if (i == topoVector.at(j)) {
				dfs(j);
				for (unsigned int k = 0; k < this->size(); k++) {
					if (this->at(k).getVisitFlag() == true && this->at(k).getUsedFlag() == false) {
						sccVector.push_back(k);
						this->at(k).setUFlag(true);
					}
				}
			}
		}
		if (sccVector.size() > 0) mainVector.push_back(sccVector);
	}
	return mainVector;
}


void Graph::toString() {
	cout << "Dependency Graph" << endl;
	for (unsigned int i = 0; i < this->size(); i++) {
		cout << "R" << i << ":";
		this->at(i).toString();
		cout << endl;
	}
}