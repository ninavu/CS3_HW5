#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <iostream>
#include <cassert>
#include <queue>

using namespace std;

void ContainsTest() {
	cout << "Testing Contains Helper Method..." << endl;
	
	Graph g = Graph();
	BetterPriorityQueue q;
	
	GraphNode *a = g.AddNode('a');
	DNode n;
	n.node = a;
	q.push(n);

	assert(q.Contains(n) == true);
	
	DNode m;
	assert(q.Contains(m) == false);
	
	GraphNode *b = g.AddNode('b');
	DNode k;
	k.node = b;
	q.push(k);
	
	assert(q.Contains(k) == true);
	
	cout << "PASSED!" << endl;
}



void UpdateTest() {
	cout << "Testing Update Helper Method..." << endl;
	
	Graph g = Graph();
	BetterPriorityQueue q;
	
	g.AddNode('a');
	g.AddNode('b');
	g.AddNode('c');
	g.AddNode('d');
	GraphNode *e = g.AddNode('e');
	GraphNode *f = g.AddNode('f');
	vector<GraphNode*> nodes = g.GetNodes();
	for(size_t i = 0; i < nodes.size(); i++){
		DNode cur;
		cur.pri = i;
		cur.node = nodes.at(i);
		//cout << "inserting cur.pri: " << cur.pri << "  node: " << cur.node->key << endl;
		q.push(cur);
		//cout << "size: " << q.size() << endl;
	}

	DNode positive;
	positive.node = f;
	positive.pri = 0;
	//cout << "q before: " << q.ToString() << endl;
	assert(q.Update(positive) == true);
	//cout << "q after: " << q.ToString() << endl;


	// Either one of these solutions is correct depending on
	// how you implement the priority queue
	string soln1 = "[(a: 0), (b: 1), (f: 0), (d: 3), (e: 4), (c: 2)]";
	string soln2 = "[(f: 0), (b: 1), (a: 0), (d: 3), (e: 4), (c: 2)]";
	//string soln3 = "[(f: 0), (a: 0), (b: 1), (c: 2), (d: 3), (e: 4)]";
	assert(q.ToString() == soln1 || q.ToString() == soln2);
	
	
	DNode neg1;
	neg1.node = e;
	neg1.pri = 5;
	assert(q.Update(neg1) == false);
	
	GraphNode *h = new GraphNode;
	h->key = 'h';
	h->data = 3;
	DNode neg2;
	neg2.node = e;
	neg2.pri = 5;
	assert(q.Update(neg2) == false);
	
	
	cout << "PASSED!" << endl;
}

int main(){
	
	ContainsTest();
	UpdateTest();
	
	cout << "ALL TESTS PASSED!!" << endl;
	
	return 0;
	
}
