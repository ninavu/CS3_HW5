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
	BetterPriorityQueue q_copy = *this;		// copy existing priority queue
	BetterPriorityQueue* q = &q_copy;
	
	if (dn.node == nullptr || !(this->Contains(dn))){
		return false;
	}
	
	tmp = q->top();
	while (!(tmp.node == dn.node) && !(q->empty())){
		list.push_back(tmp);
		q->pop();
		tmp = q->top();
	}
		
	if (!(dn > tmp)){
		q->pop();
		
		for (unsigned int i = 0; i < list.size(); i++){
			q->push(list.at(i));
		}
		q->push(dn);
		//cout << "q: " << q.ToString() << endl;
		*this = *q;			// update the priority queue by copying q
			
	} else {
		return false;
	}
	
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



