#include "Graph.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <string>

using namespace std;


void TestAddNode(){
	cout << "Testing AddNode..." << endl;
	Graph g = Graph();
	g.AddNode('a', 15);
	
	//cout << "nodes: "  << g.NodesToString() << endl;
	//cout << "graph: " << g.ToString() << endl;
	
	assert(g.NodesToString() == "[(a:15)]");
	assert(g.ToString() == "a | \n");
	
	g.AddNode('b', 12);
	//cout << "nodes: "  << g.NodesToString() << endl;
	//cout << "graph: " << endl << g.ToString() << endl;

	assert(g.NodesToString() == "[(a:15), (b:12)]");
	assert(g.ToString() == "a | \nb | \n");
	
	g.AddNode('c', 20);
	
	assert(g.NodesToString() == "[(a:15), (b:12), (c:20)]");
	assert(g.ToString() == "a | \nb | \nc | \n");
	
	try{
		g.AddNode('a', 17); 
		assert(false);
		
		g.AddNode('b', 12); 
		assert(false);
		
	} catch(const invalid_argument& e){
		
	}
	
	cout << "PASSED!" << endl << endl;
}


void TestAddEdge(){
	cout << "Testing AddEdge..." << endl;
	Graph g = Graph();
	GraphNode *gn1 = g.AddNode('a', 15);
	
	assert(g.NodesToString() == "[(a:15)]");
	assert(g.ToString() == "a | \n");
	
	GraphNode *gn2 = g.AddNode('b', 12);

	assert(g.NodesToString() == "[(a:15), (b:12)]");
	assert(g.ToString() == "a | \nb | \n");
	
	GraphNode *gn3 = g.AddNode('c', 9);
	assert(g.NodesToString() == "[(a:15), (b:12), (c:9)]");
	assert(g.ToString() == "a | \nb | \nc | \n");
	
	g.AddEdge(gn1, gn3, 2);
	//cout << "nodes: "  << g.NodesToString() << endl;
	//cout << "graph: " << endl << g.ToString() << endl;
	assert(g.NodesToString() == "[(a:15), (b:12), (c:9)]");
	assert(g.ToString() == "a | [(a:15)->(c:9) w:2]\nb | \nc | \n");
	
	g.AddEdge(gn3, gn2);
	g.AddEdge(gn1, gn2, 8);
	//cout << "nodes: "  << g.NodesToString() << endl;
	//cout << "graph: " << endl << g.ToString() << endl;
	
	assert(g.NodesToString() == "[(a:15), (b:12), (c:9)]");
	assert(g.ToString() == "a | [(a:15)->(c:9) w:2], [(a:15)->(b:12) w:8]\nb | \nc | [(c:9)->(b:12) w:0]\n");
	
	try{
		GraphNode *gn4 = new GraphNode;
		gn4->key = 'd';
		gn4->data = 3;
		g.AddEdge(gn2, gn4, 9); // gn4 is not in the graph
		assert(false);
		
	} catch(const invalid_argument& e){
		
	}	
	
	GraphNode *gn4 = g.AddNode('d', 3);
	g.AddEdge(gn2, gn4, 5);
	//cout << "graph: " << endl << g.ToString() << endl;
	assert(g.NodesToString() == "[(a:15), (b:12), (c:9), (d:3)]");
	assert(g.ToString() == "a | [(a:15)->(c:9) w:2], [(a:15)->(b:12) w:8]\nb | [(b:12)->(d:3) w:5]\nc | [(c:9)->(b:12) w:0]\nd | \n");
	
	
	cout << "PASSED!" << endl << endl;
}

void TestGetNodes(){
	cout << "Testing GetNodes..." << endl;
	Graph g = Graph();
	
	g.AddNode('a', 15);
	assert(g.GraphNodeToString(g.GetNodes().at(0)) == "(a:15)");
	
	g.AddNode('b', 12);
	assert(g.GraphNodeToString(g.GetNodes().at(1)) == "(b:12)");
	
	g.AddNode('c', 20);
	assert(g.GraphNodeToString(g.GetNodes().at(2)) == "(c:20)");
	
	cout << "PASSED!" << endl << endl;
}

void TestGetEdges(){
	cout << "Testing GetEdges..." << endl;
	Graph g = Graph();
	GraphNode *gn1 = g.AddNode('a', 15);
	GraphNode *gn2 = g.AddNode('b', 12);
	GraphNode *gn3 = g.AddNode('c', 9);
	g.AddEdge(gn1, gn3, 2);
	g.AddEdge(gn3, gn2);
	g.AddEdge(gn1, gn2, 8);
	
	//cout << "nodes: "  << g.GraphEdgeToString(g.GetEdges(g.NodeAt(0)).at(0)) << endl;
	
	assert(g.GraphEdgeToString(g.GetEdges(g.NodeAt(0)).at(0)) == "[(a:15)->(c:9) w:2]");
	assert(g.GraphEdgeToString(g.GetEdges(g.NodeAt(0)).at(1)) == "[(a:15)->(b:12) w:8]");
	assert(g.GraphEdgeToString(g.GetEdges(g.NodeAt(2)).at(0)) == "[(c:9)->(b:12) w:0]");
	
	cout << "PASSED!" << endl << endl;
}

void TestNodeAt(){
	cout << "Testing NodeAt..." << endl;
	Graph g = Graph();
	g.AddNode('a', 15);
	assert(g.GraphNodeToString(g.NodeAt(0)) == "(a:15)");
	
	g.AddNode('b', 12);
	assert(g.GraphNodeToString(g.NodeAt(1)) == "(b:12)");
	
	g.AddNode('c', 20);
	assert(g.GraphNodeToString(g.NodeAt(2)) == "(c:20)");
	
	try{
		string s = g.GraphNodeToString(g.NodeAt(3));
		assert(false);
		
	} catch(const invalid_argument& e){
		
	}	
	
	cout << "PASSED!" << endl << endl;
}

void TestOrder(){
	cout << "Testing Order..." << endl;
	Graph g = Graph();
	assert(g.Order() == 0);
	
	g.AddNode('a', 15);
	assert(g.Order() == 1);
	
	g.AddNode('b', 12);
	assert(g.Order() == 2);
	
	g.AddNode('c', 20);
	assert(g.Order() == 3);
	
	cout << "PASSED!" << endl << endl;
}

void TestSize(){
	cout << "Testing Size..." << endl;
	Graph g = Graph();
	GraphNode *gn1 = g.AddNode('a', 15);
	GraphNode *gn2 = g.AddNode('b', 12);
	GraphNode *gn3 = g.AddNode('c', 9);
	
	g.AddEdge(gn1, gn3, 2);
	(assert(g.Size() == 1));
	
	g.AddEdge(gn3, gn2);
	assert(g.Size() == 2);
	
	g.AddEdge(gn1, gn2, 8);
	assert(g.Size() == 3);
	
	cout << "PASSED!" << endl << endl;
}

void TestDestructor(){
	cout << "Testing Destructor..." << endl;
	Graph *g = new Graph();
	
	GraphNode *a = g->AddNode('a', 3);
	GraphNode *b = g->AddNode('b', 5);
	g->AddEdge(b, a, 15);
	
	delete g;
	
	
	Graph g2 = Graph();
	GraphNode *c = g2.AddNode('c', 12);
	g2.AddNode('d', 11);
	assert(c->key == 'c' && c->data == 12);
	
	cout << "NO ERRORS.  Use valgrind to check!" << endl << endl;
}


int main(){
	
	TestAddNode();
	TestAddEdge();
	TestGetNodes();
	TestGetEdges();
	TestSize();
	TestOrder();
	TestNodeAt();
	TestDestructor();
	
	cout << "ALL TESTS PASSED!" << endl;
	return 0;
}
