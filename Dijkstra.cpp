#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <iostream>
#include <climits>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

// This file is not used for part 1

/* Time Complexity of this algorithm: O(n^2)
 * 
 */


int dijkstra(const GraphNode *start, const GraphNode *end, Graph *g){
	BetterPriorityQueue path; 			// the queue contains all the edges connected to the nodes
	vector<const GraphNode*> list;	
	vector<DNode> visits;
	int result = 0;
	
	DNode min;			// create an original node to start
	min.node = start;
	min.pri = 0;
	path.push(min);
	

	while (!(path.empty())){
			
		if (count(g->GetNodes().begin(), g->GetNodes().end(), min.node)){
			for (unsigned int i = 0; i < g->GetEdges(min.node).size(); i++){
				DNode edge;
				edge.node = g->GetEdges(min.node).at(i)->to;
				edge.pri = min.pri + g->GetEdges(min.node).at(i)->weight;
				//cout << "dnode edge: " << path.DnodeToString(edge) << endl;
				
				if (!(count(list.begin(), list.end(), edge.node)) && !(path.Contains(edge))){
					path.push(edge);
					//cout << "newnode queue: " << path.ToString() << endl;	
					
				} else {
					path.Update(edge);
					//cout << "updated queue: " << path.ToString() << endl;
				}
			}
		
		min.visited = true; 
		list.push_back(min.node);
		visits.push_back(min);
		
		}	
		
		path.pop();
		min = path.top();
		
		//cout << "new queue: " << path.ToString() << endl;
	}
	
	if (visits.size() == 0){
		throw invalid_argument("Start node is not in the graph!");
			
	} else {
		for (unsigned int i = 0; i < visits.size(); i++){
			//cout << path.DnodeToString(visits.at(i)) << endl;
			if (visits.at(i).node == end){
				result = visits.at(i).pri;
			} else if (!(count(list.begin(), list.end(), end))){
				result = INT_MAX;
			}
		}
	}

	return result;
}


int DijkstraTest(){
	// Note, when grading I will replace this with
	// other / more tests.  I recommend you do the same!
	
	Graph *g = new Graph();
	Graph *t = new Graph();		// create another graph
	
	GraphNode *a = g->AddNode('1');
	GraphNode *b = g->AddNode('2');
	GraphNode *c = g->AddNode('3');
	GraphNode *d = g->AddNode('4');
	GraphNode *e = g->AddNode('5');
	GraphNode *f = g->AddNode('6');
	GraphNode *h = g->AddNode('7');		// a node that doesn't have any edges
	
	GraphNode *z = t->AddNode('9');		// a node belongs to a different graph
	
	g->AddEdge(a, b, 7);
	g->AddEdge(b, a, 7);
	g->AddEdge(a, c, 9);
	g->AddEdge(c, a, 9);
	g->AddEdge(a, f, 14);
	g->AddEdge(f, a, 14);
	
	g->AddEdge(b, c, 10);
	g->AddEdge(c, b, 10);
	g->AddEdge(b, d, 15);
	g->AddEdge(d, b, 15);
	
	g->AddEdge(c, f, 2);
	g->AddEdge(f, c, 2);
	g->AddEdge(c, d, 11);
	g->AddEdge(d, c, 11);
	
	g->AddEdge(f, e, 9);
	g->AddEdge(e, f, 9);
	
	g->AddEdge(d, e, 6);
	g->AddEdge(e, d, 6);
	
	
	cout << g->ToString() << endl << endl;
	//cout << t->ToString() << endl;
	
	unsigned int ans = dijkstra(g->NodeAt(0), e, g);
	assert(ans == 20);
	
	// random test cases
	unsigned int ans1 = dijkstra(g->NodeAt(0), f, g);
	assert(ans1 == 11);
	
	unsigned int ans2 = dijkstra(g->NodeAt(1), d, g);
	assert(ans2 == 15);
	
	// test: start node == end node
	unsigned int ans3 = dijkstra(g->NodeAt(2), c, g);
	assert(ans3 == 0);
	
	// test: the end node doesn't connect to any nodes in the graph
	unsigned int ans4 = dijkstra(g->NodeAt(2), h, g);
	//cout << ans4 << endl;
	assert(ans4 == INT_MAX);
	
	// test: the end node belongs to another graph
	unsigned int ans5 = dijkstra(g->NodeAt(1), z, g);
	//cout << ans5 << endl;
	assert(ans5 == INT_MAX);
	
	// test: the start node doesn't connect to any nodes in the graph
	unsigned int ans6 = dijkstra(t->NodeAt(0), h, t);
	assert(ans6 == INT_MAX);
	
	// test: the start node belongs to another graph
	try{
		unsigned int ans7 = dijkstra(t->NodeAt(0), h, g);
		assert(ans7 == false);
		
	} catch(const invalid_argument& e){
		
	}	

	delete g;
	delete t;
		
	return ans;
}


int main(){
	
	int ans = DijkstraTest();
	cout << "ans: "  << ans << endl;
	
	return 0;
}
