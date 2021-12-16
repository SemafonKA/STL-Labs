#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <queue>
#include <sstream>
#include <chrono>

#pragma region Defines

//#define DEBUG

#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(x) (x).begin(),(x).end()

using pii = std::pair<int, int>;

#pragma endregion

using namespace std;

const string outputPath = "outputs/";

class Timer
{
private:
   // Псевдонимы типов используются для удобного доступа к вложенным типам
   using clock_t = std::chrono::high_resolution_clock;
   using second_t = std::chrono::duration<double, std::ratio<1> >;

   std::chrono::time_point<clock_t> m_beg;

public:
   Timer() : m_beg(clock_t::now())
   {
   }

   void reset()
   {
      m_beg = clock_t::now();
   }

   double elapsed() const
   {
      return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
   }
};

inline pair < vector < int >, vector < int > > dijkstra(const vector < vector < pii > >& g, int f)
{
   priority_queue < pii > q;           // [first]: weight, [second]: vertexTo

   vector < int > distance((int)g.size(), INT_MAX);
   vector < int > parent((int)g.size());

   distance[f] = 0;
   q.push(mp(distance[f], f));

   while (!q.empty())
   {
      int v = q.top().S;
      int w = -q.top().F;
      q.pop();
      if (w > distance[v])
         continue;
      for (int i = 0; i < (int)g[v].size(); ++i)
      {
         int to = g[v][i].F;
         int weight = g[v][i].S;
         if (distance[v] + weight < distance[to])
         {
            distance[to] = distance[v] + weight;
            q.push(mp(-distance[to], to));
            parent[to] = v;
         }
      }
   }

   return mp(distance, parent);
}

inline string getPath(const vector < int >& distance, const vector < int >& parent, const int f, const int s)
{
   string str;

   if (distance[s] != INT_MAX)
   {
      str = "Vertex to: " + to_string(s) + ", distance: " + to_string(distance[s]) + ", path: ";

      //vector < int > path;
      //for (int x = s; x != f; x = parent[x])
      //   path.pb(x);
      //path.pb(f);
      //reverse(all(path));

      //for (auto x : path)
      //   str += to_string(x) + " ";
      str += "\n";
   }
   //else
   //{
   //   str = "There is no path from " + to_string(f) + " to " + to_string(s) + "\n";
   //}
   return str;
}

void getAllRoutesBy(int startVertex, const vector < vector < pii > >& graph)
{
   ofstream out(outputPath + to_string(startVertex) + ".txt");
   if (!out.is_open()) throw exception("Output file is not open!");

   pair < vector < int >, vector < int > >&& babah = dijkstra(graph, startVertex);

   vector < int >& d = babah.F;
   vector < int >& p = babah.S;

   for (int i = 1; i < (int)graph.size(); ++i)
   {
      if (i == startVertex)
         continue;

      out << getPath(d, p, startVertex, i);
   }
   out.close();
}

int main()
{
   setlocale(LC_ALL, "rus");

   ifstream in; in.open("input.txt");
   if (!in.is_open()) throw exception("Input file is not open!");

   int n, m;
   in >> n >> m;

   filesystem::remove_all(filesystem::path(outputPath));
   filesystem::create_directory(filesystem::path(outputPath));

   vector < vector < pii > > g(n + 1);  // [first]: vertexTo, [second]: weight 

   for (int i = 1; i <= m; ++i)
   {
      int u, v, w;
      in >> u >> v >> w;
      g[u].pb(mp(v, w));
      g[v].pb(mp(u, w));
   }

   in.close();

   Timer timer;
   //for (int i = 1; i < g.size(); ++i)
   //{
   //   #ifdef DEBUG
   //   static stringstream ss; ss.str("");
   //   ss << "Getting routes to vertex " << i << endl;
   //   cerr << ss.str();
   //   #endif // ifdef DEBUG

   //   getAllRoutesBy(i, g);

   //   #ifdef DEBUG
   //   ss.str("");
   //   ss << "All routes to vertex " << i << " is already printed" << endl;
   //   cerr << ss.str();
   //   #endif // ifdef DEBUG
   //}

   //cerr << "Linear program is over by " << timer.elapsed() << " second" << endl;

   timer.reset();
   #pragma omp parallel for num_threads(12) schedule(guided, 10)        // more threads == faster
   for (int i = 1; i < g.size(); ++i)
   {
      #ifdef DEBUG
      static stringstream ss;
      ss << "Getting routes to vertex " << i << endl;
      cerr << ss.str();
      #endif // ifdef DEBUG

      getAllRoutesBy(i, g);

      #ifdef DEBUG
      ss.str("");
      ss << "All routes to vertex " << i << " is already printed" << endl;
      cerr << ss.str();
      #endif // ifdef DEBUG
   }

   cerr << "Parallel program is over by " << timer.elapsed() << " second" << endl;

   return 0;
}

//#include<vector>
//#include <string>
//#include<fstream>
//#include<queue>
//#include<omp.h>
//#include<locale.h>
//
//using namespace std;
//
//typedef pair<int, int> myPair;
//
//class graph
//{
//
//private:
//   int vertexs;
//   int edges;
//   int weight;
//   int v1;
//   int v2;
//
//   vector < pair<int, int>>* g;
//
//public:
//
//   graph() //
//   {
//      ifstream in("input.txt");
//      if (!in.is_open()) throw exception();
//
//      in >> vertexs >> edges;
//      this->vertexs = vertexs + 1;
//      this->edges = edges;
//      g = new vector<myPair>[vertexs];
//
//      for (int i = 0; i < edges; ++i)
//      {
//         in >> v1 >> v2 >> weight;
//         g[v1].push_back(make_pair(v2, weight));
//         g[v2].push_back(make_pair(v1, weight));
//      }
//   }
//
//   int get_vertexs()
//   {
//      return vertexs;
//   }
//
//   void short_ways()
//   {
//      int j; ofstream out("out.txt");
//      out << "Пары вершин и миниальное растояние до них: " << endl;
//
//#pragma omp parallel for
//      for (int j = 1; j < vertexs; j++)
//      {
//         vector<int> way(vertexs, INT_MAX);
//         vector<bool> visit(vertexs, false);
//         vector<int> connect(vertexs, -1);
//         priority_queue < myPair, vector<myPair>, greater < myPair>> queue;
//         queue.push(make_pair(0, j));
//         way[j] = 0;
//         while (!queue.empty())
//         {
//            int l = queue.top().second;
//            visit[l] = true;
//            queue.pop();
//            for (vector<myPair>::iterator it = g[l].begin(); it != g[l].end(); ++it)
//            {
//               int v = (*it).first;
//               int w = (*it).second;
//               if ((way[v] > way[l] + w) && !visit[v])
//               {
//                  way[v] = way[l] + w;
//                  connect[v] = v;
//                  queue.push(make_pair(way[v], v));
//               }
//            }
//         }
//
//         string str;
//         for (int i = 1; i < vertexs; i++)
//         {
//            if (connect[i] != -1)
//            {
//               //out « j « " " « connect[i] « " " « way[i] « endl;
//               str = to_string(j) + " " + to_string(connect[i]) + " " + to_string(way[i]) + "\n";
//               out << str;
//            }
//         }
//      }
//
//      out.close();
//   }
//};
//
//int main()
//{
//   setlocale(LC_ALL, "");
//   graph g;
//   g.short_ways();
//
//   return 0;
//}