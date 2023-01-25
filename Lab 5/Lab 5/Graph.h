#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <vector>
#include "Rule.h"
#include "Node.h"

using namespace std;

class Graph : public map<int, Node> {
private:
	int currentNum;
public:
	Graph() { currentNum = 0; }
	Graph makeGraphs(vector<Rule> rulesVector);
	void dfsForest();
	void dfs(int i);
	vector<int> topoSort();
	vector<vector<int>> scc(vector<int> topoVector);
	void toString();
};

#endif