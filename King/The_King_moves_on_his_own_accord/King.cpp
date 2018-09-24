#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <list>
#include <queue>
#include <iostream>
#include <stdio.h>
using namespace std;
vector < vector<int> > g, gr, relations;
vector<char> used;
vector<int> order, component;
queue<int> wifes;
void dfs1(int v);
void dfs2(int v);
int main() {
	ifstream fin("king.in");
	ofstream fout("king.out");
	int N, X;
	fin >> N;
	stack <pair<int, int>> marriages;
	int counter = 0, Ni = 0;
	vector<int> mas(N);
	vector<int> mas2(N);
	int* mascomp = new int[N];
	int* mascount = new int[N];
	while (counter<N)
	{
		vector<int> a, b, c;
		fin >> Ni;
		mascount[counter] = Ni;
		relations.push_back(a);
		g.push_back(b);
		gr.push_back(c);
		for (int i = 0; i < Ni; i++)
		{
			fin >> X;
			X--;
			relations[counter].push_back(X);
			marriages.push(make_pair(counter, X));
		}
		counter++;
	}
	vector<int> b, c;
	for (int i = 0; i < N; i++)
	{
		fin >> mas[i];
		mas[i]--;
		mas2[mas[i]] = i;
	}
	for (; marriages.size()>0;) {
		int a, b;
		a = marriages.top().first;
		b = marriages.top().second;
		b = mas2[b];
		g[a].push_back(b);
		gr[b].push_back(a);
		marriages.pop();
	}
	used.assign(N, false);
	for (int i = 0; i<N; ++i)
		if (!used[i])
			dfs1(i);
	used.assign(N, false);
	int comp = 0;
	for (int i = 0; i<N; ++i) {
		int v = order[N - 1 - i];
		if (!used[v]) {
			dfs2(v);
			comp++;
			for (int j = 0; j < component.size(); j++)
			{
				mascomp[component[j]] = comp;
				cout << component[j] << "ty " << comp << endl;
			}
			component.clear();
		}
	}
	vector < vector<int> >::iterator it;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < relations[i].size(); j++)
			if (mascomp[i] != mascomp[mas2[relations[i][j]]])
			{
				mascount[i]--;
				relations[i].erase(relations[i].begin() + j);
				j--;
			}
	for (int i = 0; i < N; i++)
	{
		fout << mascount[i] << " ";
		for (int j = 0; j < relations[i].size(); j++)
			fout << relations[i][j] + 1 << " ";
		fout << endl;
	}
	system("pause");
}

void dfs1(int v) {
	used[v] = true;
	for (size_t i = 0; i<g[v].size(); ++i)
		if (!used[g[v][i]])
			dfs1(g[v][i]);
	order.push_back(v);
}

void dfs2(int v) {
	used[v] = true;
	component.push_back(v);
	for (size_t i = 0; i<gr[v].size(); ++i)
		if (!used[gr[v][i]])
			dfs2(gr[v][i]);
}