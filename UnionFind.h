// CS 532; Project 4; Sharif, Omar

#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class UnionFind
{
public:
	UnionFind(int n);
	void wUnion(int e1, int e2);
	int pcFind(int e);
	void printArray();
private:
	int* parent;
	int size;
};

class Wall
{
public:
	void addWalls(int N);
	void randPerm(int N);
private:
	struct dataItem {
		string wall = "";
		string wallStat = "";
		int r1 = 0;
		int r2 = 0;
	};
	vector<dataItem> a;
};

#endif UNIONFIND_H
