#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>

#define all(x) (x).begin(), (x).end()
#define pb push_back

#define Fin(x) freopen((x), "r", stdin)
#define Fout(x) freopen((x), "w", stdout)

using namespace std;

template <typename T> inline void printvec(vector < T > vec)
{
   for (int i = 0; i < (int)vec.size(); ++i)
   {
      cout << vec [ i ] << ' ';
   }
}

void task1()
{
   cout << "Задание 1:\nВведите последовательность целых чисел, оканчивающуюся нулём:\n";
   int x;
   cin >> x;
   stack <int> st;

   while (x)
   {
      st.push(x);
      cin >> x;
   }

   cout << "Последовательность в обратном порядке:\n";
   while (!st.empty())
   {
      cout << st.top() << " ";
      st.pop();
   }
   cout << "\n\n";
}

void task2()
{
   cout << "Задание 2:\nВведите последовательность целых чисел, содержащую повторения и оканчивающуюся нулём:\n";
   int x;
   cin >> x;
   vector <int> v;

   while (x)
   {
      v.push_back(x);
      cin >> x;
   }
   sort(all(v));
   auto last = unique(all(v));
   v.erase(last, v.end());

   cout << "Последовательность без повторяющихся элементов и упорядоченная по возрастанию:\n";
   printvec(v);
   cout << "\n\n";
}

void task3()
{
   cout << "Задание 3:\nВведите последовательность пар чисел: номер массива и число, добавляемое в этот массив. Признаком конца ввода служит пара, состоящая из двух нулей:\n";
   int x, y;
   cin >> x >> y;
   vector <vector <int> > g;

   while (x || y)
   {
      if (g.size() <= x)
      {
         g.resize(x + 1);
      }
      g[x].push_back(y);
      cin >> x >> y;
   }

   for (auto& i : g)
   {
      sort(all(i));
   }

   cout << "Отсортированные динамические массивы по возрастанию выведены в out.txt";
   Fout("out.txt");
   for (const auto& k : g)
   {
      static size_t i = 0;
      cout << "[" << i << "] :   ";
      printvec(k);
      cout << endl;
      ++i;
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