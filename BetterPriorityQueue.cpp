#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

#include "Graph.h"
#include "BetterPriorityQueue.h"

bool BetterPriorityQueue::Contains(DNode dn){
	
	for (unsigned int i = 0; i < this->c.size(); i++){
		if (dn == this->c.at(i)){
			return true;
		}
	}
	return false;
}

bool BetterPriorityQueue::Update(DNode dn){
	DNode tmp;
	vector<DNode> list;
	
	tmp = this->top();
	while (!(tmp.node == dn.node)){
		list.push_back(tmp);
		this->pop();
		tmp = this->top();
	}
		
	if (!(dn > tmp)){
		this->pop();
		this->push(dn); 
	} else {
		return false;
	}
	
	for (unsigned int i = 0; i < list.size(); i++){
		this->push(list.at(i));
	}
	// if DNode doesn’t match any existing in the queue or doesn’t have a lower priority than the matching DNode in the queue
	return true;
}

string BetterPriorityQueue::DnodeToString(DNode dn){
	string s = "(";
	s.push_back(dn.node->key);
	s += ": " + to_string(dn.pri) + ")";
	return s;
}
		
string BetterPriorityQueue::ToString() const{
	string s = "[";
	
	for (unsigned int i = 0; i < this->c.size(); i++){
		if (i > 0) { s += ", "; }
		s += DnodeToString(this->c.at(i));
	}
	
	s += "]";
	return s;
}



