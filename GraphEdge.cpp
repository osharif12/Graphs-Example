// CS 532; Project 4; Sharif, Omar

#include "GraphEdge.h"

Edge::Edge() {
	v1 = 0;
	v2 = 0;
	weight = 0;
}

Edge::Edge(int vertex1, int vertex2, double eWeight)
{
	v1 = vertex1;
	v2 = vertex2;
	weight = eWeight;
}

Edge::Edge(int vertex1, int vertex2, double eWeight, bool directed, bool weighted)
{
	v1 = vertex1;
	v2 = vertex2;
	weight = eWeight;
	isEdgeD = directed;
	isEdgeW = weighted;
}

int Edge::getv1() {
	return v1;
}

int Edge::getv2() {
	return v2;
}

void Edge::setv1(int value) {
	v1 = value;
}

void Edge::setv2(int value) {
	v2 = value;
}

// ***********************************************************************

Graph::Graph() {
	numVertices = 0;
	directed1 = false;
	weighted1 = false;
}

Graph::Graph(int n, bool directed, bool weighted)
{
	array.resize(n + 1);
	directed1 = directed;
	weighted1 = weighted;
	numVertices = n;
	visited = new bool[n];
}

void Graph::addEdge(Edge e)
{
	if (!isDirected()) {
		array[e.getv1()].push_back(e);

		int temp1 = e.getv1();
		int temp2 = e.getv2();
		e.setv1(temp2);
		e.setv2(temp1);
		array[e.getv1()].push_back(e);
	}
	else {
		array[e.getv1()].push_back(e);
	}
	numEdges++;
}

list<Edge> Graph::getAdjacentList(int v)
{
	/*
	list<Edge> copy = array[v];
	while (copy.size() > 0) {
		cout << "( " << copy.front().getv1() << ", " << copy.front().getv2() << ") ";
		copy.pop_front();
	}
	cout << endl;
	*/
	return array[v];
}

Edge Graph::getEdge(int v1, int v2)
{
	list<Edge> second; // list<Edge> = Array[i]
	second.resize(array[v1].size() + 1);
	second = array[v1];

	while (second.front().getv2() != v2) {
		second.pop_front();
	}

	return second.front();
}

int Graph::getNumVertices()
{
	return numVertices;
}

int Graph::getNumEdges()
{
	return numEdges;
}

bool Graph::isDirected()
{
	return directed1;
}

bool Graph::isWeighted()
{
	return weighted1;
}

void Graph::setVertices(int n)
{
	numVertices = n;
}

void Graph::setDirected(bool d)
{
	directed1 = d;
}

void Graph::setWeighted(bool w)
{
	weighted1 = w;
}
