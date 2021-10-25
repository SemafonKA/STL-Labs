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

template <typename T> inline void printvec(vector < T > vec) {
	 for (int i = 0; i < (int)vec.size(); ++i) {
		  cout << vec[i] << ' ';
	 }
}

void task1()
{
	 cout << "Задание 1:\nВведите последовательность целых чисел, оканчивающуюся нулём:\n";

	 int x;

	 cin >> x;

	 stack <int> st;

	 while (x) {
		  st.push(x);
		  cin >> x;
	 }

	 cout << "Последовательность в обратном порядке:\n";

	 while (!st.empty()) {
		  cout << st.top() << " ";
		  st.pop();
	 }
	 cout << "\n\n";
}

void task2() {
	 cout << "Задание 2:\nВведите последовательность целых чисел, содержащую повторения и оканчивающуюся нулём:\n";
	 int x;

	 cin >> x;

	 unordered_set <int> u_s;

	 while (x) {
		  u_s.insert(x);
		  cin >> x;
	 }

	 vector <int> v(all(u_s));

	 sort(all(v));

	 cout << "Последовательность из которой удалены повторения и упорядоченная по возрастанию:\n";

	 printvec(v);

	 cout << "\n\n";
}


void task3() {

	 cout << "Задание 3:\nВведите последовательность пар чисел: номер массива и число, добавляемое в этот массив. Признаком конца ввода служит пара, состоящая из двух нулей:\n";
	 
	 int x, y;
	 
	 cin >> x >> y;

	 const int maxn_task3  = 20;
	 
	 vector < int > g[maxn_task3];
	 
	 while (!(!x && !y)) {
		  g[x].pb(y);
		  cin >> x >> y;
	 }

	 cout << "Отсортированные динамические массивы по возрастанию выведены в out.txt";
	 
	 Fout("out.txt");

	 for (int i = 0; i < 20; ++i) {
		  sort(all(g[i]));
		  cout << "g[" << i << "]: ";
		  if (g[i].empty()) 
				cout << "empty";
		  else
				printvec(g[i]);
		  cout << "\n";
	 }
}

int main() {

	 setlocale(LC_ALL, "rus");
	 
	 task1();
	 task2();
	 task3();

	 return 0;
}