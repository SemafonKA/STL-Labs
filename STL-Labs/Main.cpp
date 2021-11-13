#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void Task1()
{
   constexpr char g_inputFilePath[] = "Task1/input.txt";
   constexpr char g_outputFilePath[] = "Task1/output.txt";

   int size_n, size_v;

   ifstream in; in.open(g_inputFilePath);
   if (!in.is_open()) throw exception("Can't open input file.");

   in >> size_n >> size_v;
   vector<vector<int>> graph(size_n);

   int n_first, n_second;
   for (size_t i = 0; i < size_v; ++i)
   {
      in >> n_first >> n_second;
      graph[n_first - 1].push_back(n_second - 1);
      graph[n_second - 1].push_back(n_first - 1);
   }
   in.close();

   ofstream out; out.open(g_outputFilePath);
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

int main(void)
{
   Task1();
}