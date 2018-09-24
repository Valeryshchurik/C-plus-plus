#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <list>
#include <iostream>
#include <stdio.h>
using namespace std;
void Doubling(int &a);

class comparatorX {
public:
	bool operator()(const pair<int, int> & mc1, const pair<int, int> mc2) {
		return mc1.first < mc2.first;
	}
};
class comparatorY {
public:
	bool operator()(const pair<int, int> & mc1, const pair<int, int> mc2) {
		return mc1.second < mc2.second;
	}
};
int main() {
	comparatorX a;
	comparatorY b;
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int	N, X, Y;
	int counter = 0;
	int X0, Y0;
	fin >> N >> X >> Y;
	X--;
	Y--;
	pair<int, int>* trees = new pair<int, int>[N];
	int *mas;
	bool anytree = false;
	vector <short> stb(X + 1, 0);
	while (counter<N+1)
	{
		fin >> X0, fin >> Y0;
		counter++;
		X0--;
		Y0--;
		if ((X0 == -1) || (X0 == X) || (Y0 == -1) || (Y0 == Y))
		{
			N--;
			continue;
		}
	}
	fin.clear();
	fin.seekg(0, ios::beg);
	int musor;
	fin >> musor >> musor >> musor;
	counter = 0;
	while (counter<N)
	{
		anytree = true;
		fin >> X0, fin >> Y0;
		X0--;
		Y0--;
		if ((X0 == -1) || (X0 == X) || (Y0 == -1) || (Y0 == Y))
			continue;
		stb[X0] = -1;
		trees[counter] = make_pair(X0, Y0);
		counter++;
	}
	fin.close();
	if (!anytree)
	{
		fout << (X + 1)*(Y + 1);
		fout.close();
		return 0;
	}
	counter = 0;
	sort(trees, trees + N, a);
	int ans = X > Y ? X : Y, squ = 0;
	ans++;
	vector <short>::iterator it1, it2;
	it1 = stb.begin();
	it2 = it1;
	while (it1 != stb.end())
	{
		counter = 0;
		while (*it1 != -1 && it1 != stb.end() - 1)
		{
			counter++;
			it1++;
		}
		it1 = stb.erase(it2, it1);
		*it1 = counter;
		it1++;
		it2 = it1;
	}
	int stb_size = stb.size();
	int mas_size = stb_size - 1;
	mas = new int[mas_size];
	for (int i = 0;i < mas_size;i++)
		mas[i] = -1;
	short idx = 0;
	for (int i = 0; i < N; i++)
		cout << trees[i].first << "," << trees[i].second << endl;
	int buffer = trees[0].first;
	trees[0].first = 0;
	for (int i = 1; i < N; i++)
	{
		if (trees[i].first != buffer)
			idx++;
		buffer = trees[i].first;
		trees[i].first = idx;
	}
	for (int i = 0; i < N; i++)
		cout << trees[i].first << "," << trees[i].second << endl;
	sort(trees, trees + N, b);
	for (int i = 0; i < N; i++)
		cout << trees[i].first << "," << trees[i].second << endl;
	stack<int> st;
	int sq = 0, h = 0, limited = 2;
	int l = 1, r = 1;
	int bstb = 0;
	bool niz = false;
	for (int i = 0;i < stb.size();i++)
		if((Y+1)*(stb[i]+1)>ans)
			ans = (Y+1)*(stb[i]+1);
niz:
	for (int i = 0;i < N;i++)
	{
		limited = mas[trees[i].first];
		h = trees[i].second - limited - 1;
		while (h > 0)
		{
			l = 1;
			bstb = stb[trees[i].first] + stb[trees[i].first + 1];
			while ((mas[trees[i].first - l]) <= limited)
			{
				if (trees[i].first - l < 0)
				{
					l--;
					break;
				}
				bstb++;
				bstb += stb[trees[i].first - l];
				l++;
				if (trees[i].first - l < 0)
				{
					l--;
					break;
				}
			}
			r = 1;
			while ((mas[trees[i].first + r]) <= limited)
			{
				if (trees[i].first + r > mas_size - 1)
				{
					r--;
					break;
				}
				bstb++;
				bstb += stb[trees[i].first + r + 1];
				r++;
				if (trees[i].first + r > mas_size - 1)
				{
					r--;
					break;
				}
			}
			sq = (h + 1)*(bstb + 2);
			ans = ans > sq ? ans : sq;
			if (limited >= max(mas[trees[i].first + r], (mas[trees[i].first - l])))
			{
				if ((l == 0) || (r == 0))
					limited++;
				else break;
				if (limited >= trees[i].second)
					break;
			}
			else
				if (limited >= min(mas[trees[i].first + r], (mas[trees[i].first - l])))
					limited = max(mas[trees[i].first + r], (mas[trees[i].first - l]));
				else limited = min(mas[trees[i].first + r], (mas[trees[i].first - l]));
				h = trees[i].second - limited - 1;
		}
		mas[trees[i].first] = trees[i].second;
	}
	delete[] trees;
	trees = new pair<int, int>[stb.size()];
	N = stb.size()-1;
	for (int i = 0;i <N;i++)
		trees[i] = (make_pair(i, Y));
	if (!niz)
	{
		niz = true;
		goto niz;
	}
	fout << ans;
	fout.close();
	return 0;
}
void Doubling(int &a)
{
	a = a << 1;
}