#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define pb push_back

using namespace std;

void Task1()
{
   constexpr char inputFilePath[] = "Task1/input.txt";
   constexpr char outputFilePath[] = "Task1/output.txt";

   int size_n, size_v;

   ifstream in; in.open(inputFilePath);
   if (!in.is_open()) throw exception("Can't open input file.");

   in >> size_n >> size_v;
   vector<vector<int>> graph(size_n);

   int n_first, n_second;
   for (size_t i = 0; i < size_v; ++i)
   {
      in >> n_first >> n_second;
      graph[n_first - 1].pb(n_second - 1);
      graph[n_second - 1].pb(n_first - 1);
   }
   in.close();

   ofstream out; out.open(outputFilePath);
   for (size_t i = 0; i < graph.size(); ++i)
   {
      out << "[" << i + 1 << "] :";
      for (auto k : graph[i])
      {
         out << " " << k + 1;
      }
      out << endl;
   }
}

void Task2()
{
   constexpr char inputFilePath[] = "Task2/n.txt";
   ifstream in; in.open(inputFilePath);

   int N;
   in >> N;
   in.close();
   vector<vector<int>> g(1);
   int mx_sz = 1;
   for (int id = 1; id <= N; ++id)
   {
      string path = "Task2/" + to_string(id) + ".txt";
      in.open(path);
      if (!in.is_open()) throw exception("Can't open input file.");
      int cnt;
      in >> cnt;
      vector < int > nm;

      for (int i = 0; i < cnt; ++i)
      {
         int x;
         in >> x;
         mx_sz = max(mx_sz, x);
         nm.pb(x - 1);
      }
      in.close();
      g.resize(mx_sz);
      for (int i = 0; i < cnt; ++i)
      {
         for (int j = i + 1; j < cnt; ++j)
         {
            g[nm[i]].pb(nm[j]);
            g[nm[j]].pb(nm[i]);
         }
      }
   }
   constexpr char outputFilePath[] = "Task2/output.txt";
   ofstream out; out.open(outputFilePath);
   for (size_t i = 0; i < g.size(); ++i)
   {
      out << "[" << i + 1 << "] :";
      vector < bool > was(mx_sz, false);
      for (auto k : g[i])
      {
         if (!was[k])
         {
            out << " " << k + 1;
            was[k] = true;
         }
      }
      out << endl;
   }
}

double Sum(int n, double* a)
{
   double s = 0;
   for (int i = 0; i < n; i++)
   {
      s += a[i];
   }
   return s;
}

double SumVectorVector(vector< vector<double> >& a)
{
   double s = 0;
   int sz1 = a.size();
   for (int i = 0; i < sz1; i++)
   {
      int sz2 = a[i].size();
      for (int j = 0; j < sz2; j++)
      {
         s += a[i][j];
      }
   }
   return s;
}

void TestSumMatrix(int n, int m)
{
   vector< vector<double> > a;
   a.resize(n, vector<double>(m, 1));
   cout << SumVectorVector(a) << '\t' << Sum(n * m, &a[0][0]) << endl;
}

void Task3(void)
{
   cout << "N = 1, M = 1 : ";
   TestSumMatrix(1, 1);
   cout << endl << "N = 1, M = 10 : ";
   TestSumMatrix(1, 10);
   cout << endl << "N = 2, M = 1 : ";
   TestSumMatrix(2, 1);
   cout << endl << "N = 2, M = 10 : ";
   TestSumMatrix(2, 10);
   cout << endl << "N = 10, M = 10 : ";
   TestSumMatrix(10, 10);
}

int main(void)
{
  /* Task1();
   Task2();*/
   Task3();
}