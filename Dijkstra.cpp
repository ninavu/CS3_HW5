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
	BetterPriorityQueue path; 
	vector<const GraphNode*> list;		
	int result = 0;
	
	
	DNode org;			// create an original node to start
	org.node = start;
	org.pri = 0;
	path.push(org);
	
	// what if the end is not connected?
	
	//while 
	while (!(path.empty())){
		DNode min = path.top();
		min.visited = true; 
		list.push_back(min.node);
		
		for (unsigned int i = 0; i < g->GetEdges(min.node).size(); i++){
			DNode edge;
			edge.node = g->GetEdges(min.node).at(i)->to;
			edge.pri = min.pri + g->GetEdges(min.node).at(i)->weight;
			cout << "dnode tmp: " << path.DnodeToString(edge) << endl;
			
			if (!(count(list.begin(), list.end(), edge.node)) && !(path.Contains(edge))){
				path.push(edge);
				cout << "sth queue: " << path.ToString() << endl;
				
				
			} else {
				path.Update(edge);
				cout << "updated queue: " << path.ToString() << endl;
			}
			
			//cout << "alledges size: " << g->GetEdges(min.node).size() << endl;
		
		}
		
		path.pop();
		result = min.pri;
		
		cout << "min: " << result << endl;
		cout << "new queue: " << path.ToString() << endl;
		
	}
	
	return result;
}


int DijkstraTest(){
	// Note, when grading I will replace this with
	// other / more tests.  I recommend you do the same!
	
	Graph *g = new Graph();
	
	GraphNode *a = g->AddNode('1');
	GraphNode *b = g->AddNode('2');
	GraphNode *c = g->AddNode('3');
	GraphNode *d = g->AddNode('4');
	GraphNode *e = g->AddNode('5');
	GraphNode *f = g->AddNode('6');
	
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
	
	
	cout << g->ToString() << endl;
	
	unsigned int ans = dijkstra(g->NodeAt(0), e, g);
	assert(ans == 20);

	delete g;
		
	return ans;
}


int main(){
	
	int ans = DijkstraTest();
	cout << "ans: "  << ans << endl;
	
	return 0;
}
