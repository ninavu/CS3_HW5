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
	
	for (unsigned int i = 0; i < this->c.size(); i++){
		if (dn.node == this->c.at(i).node && !(dn > this->c.at(i))){
			//this->c.at(i).pri = dn.pri;
			this->push(dn);
			
			return true;	
		} 
	}
	// if DNode doesn’t match any existing in the queue or doesn’t have a lower priority than the matching DNode in the queue
	return false;
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



