// CS 532; Project 4; Sharif, Omar

#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H
#include <list>
#include <iostream>
#include <vector>
using namespace std;

class Edge {
public:
	Edge();
	Edge(int vertex1, int vertex2, double eWeight);
	Edge(int vertex1, int vertex2, double eWeight, bool directed, bool weighted);
	int getv1();
	int getv2();
	void setv1(int value);
	void setv2(int value);
private:
	int v1 = 0, v2 = 0;
	double weight;
	bool isEdgeD;
	bool isEdgeW;
};

class Graph {
public:
	Graph();
	Graph(int n, bool directed, bool weighted);
	void addEdge(Edge e);
	std::list<Edge> getAdjacentList(int v); // returns a list of the Edge objects for vertices adjacent to v, if list is empty returns empty list
	Edge getEdge(int v1, int v2);
	int getNumVertices();
	int getNumEdges();
	bool isDirected();
	bool isWeighted();
	void setVertices(int n);
	void setDirected(bool d);
	void setWeighted(bool w);
	bool* visited;
	vector<list<Edge>> array; // This is adjacency list, vector holding lists of edge objects adjacent to assigned index
private:
	bool directed1;
	bool weighted1;
	int numVertices = 0;
	int numEdges = 0;
};

#endif GRAPHEDGE_H

