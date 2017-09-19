// CS 532; Project 4; Sharif, Omar

#include "UnionFind.h"

UnionFind::UnionFind(int n)
{
	size = n;
	parent = new int[n];

	for (int i = 0; i < size; i++)
		parent[i] = -1;
}

void UnionFind::wUnion(int e1, int e2)
{
	int root1 = pcFind(e1);
	int root2 = pcFind(e2);

	if (parent[root1] == parent[root2]) { // if both trees are the same size
		parent[root1] = parent[root1] + parent[root2];
		parent[root2] = root1;
	}
	else if (parent[root2] < parent[root1]) { // if right tree is bigger than left tree, you join left tree to the right tree(join small tree to big tree)
		parent[root2] = parent[root2] + parent[root1];
		parent[root1] = root2;
	}
	else { // if left tree is bigger than right tree
		parent[root1] = parent[root1] + parent[root2];
		parent[root2] = root1;
	}
}

int UnionFind::pcFind(int e)
{
	if (parent[e] < 0) // parent of the root will be a negative number for sure
		return e; // returns root of tree right before negative parent pointer
	else
		return parent[e] = pcFind(parent[e]); // recursion to collapse nodes on way to root
}

void UnionFind::printArray()
{
	for (int i = 0; i < size; i++) {
		if (i != size - 1)
			cout << parent[i] << ", ";
		else
			cout << parent[i] << " ";
	}
	cout << endl;
}

void Wall::addWalls(int N)
{
	for (int c1 = 0; c1 < N*N - 1; c1++) // All possible internal walls will be printed out in order
	{
		int c2 = c1 + 1;
		if (c2 % N != 0) {
			cout << "( " << c1 << ", " << c2 << ") ";
		}

		c2 = c1 + N;
		if (c2 < N*N) {
			cout << "( " << c1 << ", " << c2 << ") ";
		}
	}
	cout << endl;
}

void Wall::randPerm(int N)
{
	srand(time(0));
	dataItem z;
	a.reserve(N*N * 2);

	for (int c1 = 0; c1 < N*N - 1; c1++) // Creates vector of inner walls, each with unique description
	{
		int c2 = c1 + 1;

		if (c2 % N != 0) {
			z.r1 = c1;
			z.r2 = c2;

			string str1 = "( , )";
			string str2 = to_string(c1);
			string str3 = to_string(c2);
			str1.insert(1, str2);
			str1.insert(5, str3);
			z.wall = str1;
			a.push_back(z);
		}

		c2 = c1 + N;
		if (c2 < N*N) {
			z.r1 = c1;
			z.r2 = c2;

			string str1 = "( , )";
			string str2 = to_string(c1);
			string str3 = to_string(c2);
			str1.insert(1, str2);
			str1.insert(5, str3);
			z.wall = str1;
			a.push_back(z);
		}
	}

	int r;
	for (unsigned i = 0; i < a.size(); i++) // Randomly permutes order of inner walls in vector
	{
		r = rand() % (i + 1);

		dataItem temp = a.at(i);
		a.at(i) = a.at(r);
		a.at(r) = temp;
	}

	UnionFind b(N*N); // New array of elements, all of which are -1, indices representing numbers in their own set
	for (int i = 0; i < a.size(); i++) // Determine if walls go up or down, then print final permuted order of walls with proper description
	{
		if (b.pcFind(a.at(i).r1) == b.pcFind(a.at(i).r2))
			a.at(i).wallStat = "Wall up";
		else
		{
			a.at(i).wallStat = "Wall down";
			b.wUnion(a.at(i).r1, a.at(i).r2);
		}
		cout << a.at(i).wall << "- ";
		cout << a.at(i).wallStat << endl;
	}
}