// CS 532; Project 4; Sharif, Omar

#include <queue>
#include <fstream>
#include <functional>
#include "GraphEdge.h"
#include "UnionFind.h"
using namespace std;

struct data1 {
	int n1 = 0;
	int n2 = 0;
	string coord;
	string wallStat;
	bool connect = false;
};
vector<data1> generateWalls(int N);

struct data2
{
	int v1, v2, weight;
	bool operator<(const data2& rhs) const
	{
		return weight > rhs.weight; // change the greater than sign to change priority queue prioritization
	}
};

int getEdgev2(Edge a);
void RDS(Graph g, int start);
void RDFS(Graph g, int v, std::vector<int> *path);
bool isPath = false;

int main()
{
	cout << "Part 1: " << endl;
	vector<data1> b;
	Graph a(9, false, false);

	cout << "Value of N = 3: " << endl;
	b = generateWalls(3);

	for (int i = 0; i < b.size(); i++) {
		if (b.at(i).connect) {
			Edge temp(b.at(i).n1, b.at(i).n2, 0, false, false);
			a.addEdge(temp);
		}
	}
	RDS(a, 0);
	cout << endl;

	vector<data1> f;
	Graph e(16, false, false);

	cout << "Value of N = 4: " << endl;
	f = generateWalls(4);

	for (int i = 0; i < f.size(); i++) {
		if (f.at(i).connect) {
			Edge temp(f.at(i).n1, f.at(i).n2, 0, false, false);
			e.addEdge(temp);
		}
	}
	RDS(e, 0);
	cout << endl;

	vector<data1> g;
	Graph h(25, false, false);

	cout << "Value of N = 5: " << endl;
	g = generateWalls(5);

	for (int i = 0; i < g.size(); i++) {
		if (g.at(i).connect) {
			Edge temp(g.at(i).n1, g.at(i).n2, 0, false, false);
			h.addEdge(temp);
		}
	}
	RDS(h, 0);

	cout << endl;
	// ********************************************************************************
	cout << "Part 2: " << endl << endl;
	cout << "Edges in Kruskall's MST algorithm " << endl;

	int vertices, v1, v2, weight, sumW = 0;
	priority_queue<data2> q;
	fstream fin("Input1.txt");

	fin >> vertices;
	Graph c(vertices, false, true);
	UnionFind d(vertices);

	while (fin >> v1) {
		fin >> v2;
		fin >> weight;
		data2 temp = { v1, v2, weight };
		q.push(temp);
	}

	while (!q.empty()) {
		data2 temp1 = q.top();
		if (d.pcFind(temp1.v1) != d.pcFind(temp1.v2)) {
			d.wUnion(temp1.v1, temp1.v2);
			Edge temp2(temp1.v1, temp1.v2, temp1.weight, false, true);
			c.addEdge(temp2);
			cout << "(" << temp1.v1 << ", " << temp1.v2 << ") " << endl;
			sumW += temp1.weight;
		}
		q.pop();
	}
	cout << "The total weight of MST is: " << sumW << endl;

	return 0;
}

vector<data1> generateWalls(int N) {
	srand(time(0));
	vector<data1> a;
	data1 temp;
	cout << "List of Internal Walls: ";

	for (int c1 = 0; c1 < N*N - 1; c1++) // All possible internal walls will be printed out in order
	{
		int c2 = c1 + 1;
		if (c2 % N != 0) {
			cout << "( " << c1 << ", " << c2 << "), ";
			temp.n1 = c1;
			temp.n2 = c2;

			string str1 = "( )";
			string str2 = to_string(c1);
			string str3 = to_string(c2);
			str1.insert(1, str2);
			str1.insert(3, ", ");
			str1.insert(5, str3);
			temp.coord = str1;
			a.push_back(temp);
		}

		c2 = c1 + N;
		if (c2 < N*N) {
			cout << "( " << c1 << ", " << c2 << "), ";
			temp.n1 = c1;
			temp.n2 = c2;

			string str1 = "( )";
			string str2 = to_string(c1);
			string str3 = to_string(c2);
			str1.insert(1, str2);
			str1.insert(3, ", ");
			str1.insert(5, str3);
			temp.coord = str1;
			a.push_back(temp);
		}
	}
	cout << endl << endl;

	int r;
	for (unsigned i = 0; i < a.size(); i++) // Randomly permutes order of inner walls in vector
	{
		r = rand() % (i + 1);

		data1 temp = a.at(i);
		a.at(i) = a.at(r);
		a.at(r) = temp;
	}

	UnionFind b(N*N); // New array of elements, all of which are -1, indices representing numbers in their own set
	cout << "List of connected vertices: " << endl;
	for (int i = 0; i < a.size(); i++) // Determine if walls go up or down, then print final permuted order of walls with proper description
	{
		if (b.pcFind(a.at(i).n1) == b.pcFind(a.at(i).n2)) {
			a.at(i).connect = false;
			a.at(i).wallStat = "Wall Up";
		}
		else
		{
			a.at(i).connect = true;
			a.at(i).wallStat = "Wall Down";
			b.wUnion(a.at(i).n1, a.at(i).n2);
		}
		cout << a.at(i).coord << "- ";
		cout << a.at(i).wallStat << endl;
	}

	return a;
}

int getEdgev2(Edge b) {
	return b.getv2();
}

void RDS(Graph g, int start) {
	for (unsigned i = 0; i < g.array.size(); i++)
		g.visited[i] = false;
	vector<int> *path = new vector<int>;
	RDFS(g, start, path);
}
void RDFS(Graph g, int v, vector<int> *path) {
	g.visited[v] = true;
	//pre
	path->push_back(v);
	bool deleteVertex = true;
	list<Edge>::iterator i;
	std::list<Edge> vec = g.getAdjacentList(v);
	for (i = vec.begin(); i != vec.end(); i++)  //Traverse any vertex adjacent to v
	{
		int val = getEdgev2(*i);
		if (g.visited[val])
			continue;
		RDFS(g, val, path);
	}

	//post
	//if no ajdacent vectors and not n^2-1 - remove from path vector
	int size = g.getNumVertices();
	if (v != (size - 1)) {//If vertex is not the exit(last one)
		list<Edge> adjs = g.getAdjacentList(v);
		for (i = adjs.begin(); i != adjs.end(); i++) {
			if (!g.visited[getEdgev2(*i)])  //if there are still unvisited adjacent vectors - do not remove from path yet
				deleteVertex = false;  //Prevent function from deleting the vertex from the path
		}
		if (deleteVertex) {
			vector<int>::iterator j = path->begin();
			path->erase(std::remove(path->begin(), path->end(), v), path->end());  //Remove the vertex from path vector since all its adjacents have been visited
		}
	}
	else { //print path
		vector<int>::iterator i;
		cout << "The solution for this maze is as follows: ";
		for (i = path->begin(); i != path->end(); i++) {
			cout << *i << " ";
		}
		cout << "\n";
	}
}