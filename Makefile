all:
	g++ --std=c++14 -Wall Graph.cpp GraphTests.cpp -o gra
	g++ --std=c++14 -Wall Graph.cpp BetterPriorityQueue.cpp BPQTests.cpp -o bpq
	g++ --std=c++14 -Wall Graph.cpp BetterPriorityQueue.cpp Dijkstra.cpp -o dijkstra 
