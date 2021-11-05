#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "Graph.h"

GraphNode* Graph::AddNode(char key, int data){
	//create an instance of struct
	// check whether that node already exists? -> make sure each node is unique (same key, different data)?
	GraphNode *gn = new GraphNode;
	gn->key = key;
	gn->data = data;
	
	AllNodes.push_back(gn);
	AllEdges.resize(AllEdges.size()+1);
	
	return gn;
}

GraphEdge* Graph::AddEdge(GraphNode *gn1, GraphNode *gn2, unsigned int weight){
	
	//check whether gn1 and gn2 actually exists in AllNodes, already in AllEdges
	GraphEdge *ge = new GraphEdge;
	ge->from = gn1;
	ge->to = gn2;
	ge->weight = weight;
	
	for (unsigned int i = 0; i < AllNodes.size(); i++){
		if (gn1->key == AllNodes.at(i)->key){
			AllEdges.at(i).push_back(ge);
		}
	}
	return ge;
}


const vector<GraphNode*>& Graph::GetNodes() const{
	return AllNodes;
}


const vector<GraphEdge*>& Graph::GetEdges(const GraphNode *gn) const{
	int idx = -1;
	
	for (unsigned int i = 0; i < AllNodes.size(); i++){
		if (gn->key == AllNodes.at(i)->key){
			idx = i;
		}
	}
	
	return AllEdges.at(idx);
}

string Graph::GraphNodeToString(const GraphNode *gn){
	string s = "(";
	s.push_back(gn->key);
	s += ":";
	s += to_string(gn->data); 
	s += ")";
	
	return s;
}


string Graph::GraphEdgeToString(const GraphEdge *ge){
	// [(a:15)->(c:9) w:2], [(a:15)->(b:12) w:8]
	string s = "[";
	s += GraphNodeToString(ge->from);
	s += "->";
	s += GraphNodeToString(ge->to);
	s += " w:" + to_string(ge->weight) + "]";
	
	return s;
}

string Graph::NodesToString() const{
	string s = "[";
	
	for (unsigned int i = 0; i < AllNodes.size(); i++){
		if (i > 0) { s += ", ";}
		s += GraphNodeToString(AllNodes.at(i));
	}

	s += "]";
	return s;
} 


string Graph::ToString() const{
	string s;
	
	for (unsigned int i = 0; i < AllNodes.size(); i++){
		s.push_back(AllNodes.at(i)->key);
		s += " | ";
		
		for (unsigned int j = 0; j < AllEdges.at(i).size(); j++){
			if (j > 0) { s+= ", "; }
			s += GraphEdgeToString(AllEdges.at(i).at(j));
		}
		s += "\n";
	}
	return s;
}


const GraphNode* Graph::NodeAt(unsigned int idx) const{
	return AllNodes.at(idx);
}

size_t Graph::Size() const{
	size_t count = 0;
	
	for (unsigned int i = 0; i < AllEdges.size(); i++){
		count += AllEdges.at(i).size();
	}
	return count;
}
 
 
size_t Graph::Order() const{
	return AllNodes.size();
}


Graph::~Graph(){
	// delete all the nodes and edges
	for (unsigned int i = 0; i < AllNodes.size(); i++){
		delete AllNodes.at(i);
		for (unsigned int j = 0; j < AllEdges.at(i).size(); j++){
			delete AllEdges.at(i).at(j);
		}
	}
}
