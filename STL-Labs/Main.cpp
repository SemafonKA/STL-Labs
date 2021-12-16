#include<vector>
#include<fstream>
#include<queue>
#include<omp.h>
#include<locale.h>

using namespace std;

typedef pair<int, int> myPair;

class graph
{

private:
   int vertexs;
   int edges;
   int weight;
   int v1;
   int v2;

   vector<pair<int, int>>* g;

public:

   graph() //конструктор графа
   {
      ifstream in("input.txt");
      in >> vertexs >> edges;
      this->vertexs = vertexs + 1;
      this->edges = edges;
      g = new vector<myPair>[vertexs];

      for (int i = 0; i < edges; ++i)
      {
         in >> v1 >> v2 >> weight;
         g[v1].push_back(make_pair(v2, weight));
         g[v2].push_back(make_pair(v1, weight));
      }
   }

   int get_vertexs()
   {
      return vertexs;
   }

   void short_ways()
   {
      int j; ofstream out("out.txt");
      out << "Пары вершин и миниальное растояние до них: " << endl;

#pragma omp parallel for
      for (int j = 1; j < vertexs; j++)
      {
         vector<int> way(vertexs, INT_MAX);
         vector<bool> visit(vertexs, false);
         vector<int> connect(vertexs, -1);
         priority_queue < myPair, vector<myPair>, greater<myPair>> queue;
         queue.push(make_pair(0, j));
         way[j] = 0;
         while (!queue.empty())
         {
            int l = queue.top().second;
            visit[l] = true;
            queue.pop();
            for (vector<myPair>::iterator it = g[l].begin(); it != g[l].end(); ++it)
            {
               int v = (*it).first;
               int w = (*it).second;
               if ((way[v] > way[l] + w) && !visit[v])
               {
                  way[v] = way[l] + w;
                  connect[v] = v;
                  queue.push(make_pair(way[v], v));
               }
            }
         }

#pragma omp critical
         for (int i = 1; i < vertexs; i++)
         {
            if (connect[i] != -1)
               out << j << " " << connect[i] << " " << way[i] << endl;
         }
      }

      out.close();
   }
};

int main()
{
   setlocale(LC_ALL, "");
   graph g;
   g.short_ways();

   return 0;
}