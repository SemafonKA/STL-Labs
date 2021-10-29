#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <cstdio>

#define all(x) (x).begin(), (x).end()
#define pb push_back

#define Fin(x) freopen((x), "r", stdin)
#define Fout(x) freopen((x), "w", stdout)

using namespace std;

template <typename T> inline void printvec(vector < T > vec) 
{
	 for (int i = 0; i < (int)vec.size(); ++i) 
	 {
		  cout << vec[i] << ' ';
	 }
}

void task1()
{
	 cout << "������� 1:\n������� ������������������ ����� �����, �������������� ����:\n";
	 int x;
	 cin >> x;
	 stack <int> st;

	 while (x) 
	 {
		  st.push(x);
		  cin >> x;
	 }

	 cout << "������������������ � �������� �������:\n";
	 while (!st.empty()) 
	 {
		  cout << st.top() << " ";
		  st.pop();
	 }
	 cout << "\n\n";
}

void task2() 
{
	 cout << "������� 2:\n������� ������������������ ����� �����, ���������� ���������� � �������������� ����:\n";
	 int x;
	 cin >> x;
	 vector <int> v;

	 while (x) 
	 {
		 if (find(all(v), x) == v.end())
			 v.pb(x);
		 cin >> x;
	 }
	 sort(all(v));

	 cout << "������������������ ��� ������������� ��������� � ������������� �� �����������:\n";
	 printvec(v);
	 cout << "\n\n";
}

template<typename Iterator, typename T>
Iterator findKeyInMap(Iterator begin, Iterator end, const T& v)
{
	for (; begin != end; ++begin)
		if (begin->first == v)
			return begin;

	return end;
}

bool comp(pair <int, vector <int> > x1, pair <int, vector <int> > x2) 
{
	return ((x1.first) < (x2.first));
}

void task3() 
{

	 cout << "������� 3:\n������� ������������������ ��� �����: ����� ������� � �����, ����������� � ���� ������. ��������� ����� ����� ������ ����, ��������� �� ���� �����:\n";
	 int x, y;
	 cin >> x >> y;
	 vector <pair <int, vector<int> > > g;

	 while (x || y) // !(!x && !y)
	 {
		 auto it = findKeyInMap(all(g), x);
		 if (it != g.end()) 
		 {
			 (it->second).pb(y);
		 }
		 else 
		 {
			 pair <int, vector <int> > cur;
			 cur.first = x;
			 cur.second.pb(y);
			 g.pb(cur);
		 }

		 cin >> x >> y;
	 }
	 sort(all(g), comp);

	 cout << "��������������� ������������ ������� �� ����������� �������� � out.txt";

	 Fout("out.txt");
	 for (auto q : g) 
	 {
		 sort(all(q.second));
		 cout << "g[" << q.first << "]: ";
		 printvec(q.second);
		 cout << "\n";
	 }
}

int main() 
{
	 setlocale(LC_ALL, "rus");
	 
	 task1();
	 task2();
	 task3();

	 return 0;
}