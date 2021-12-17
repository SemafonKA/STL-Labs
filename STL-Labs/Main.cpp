#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <omp.h>
#include <chrono>

#pragma region Defines

#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(x) (x).begin(),(x).end()

using pii = std::pair<int, int>;

#pragma endregion

using namespace std;

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

inline void dijkstra(const vector < vector < pii > >& g, int f, vector < int >& distance, vector < int >& parent)
{
   priority_queue < pii > q;           // [first]: weight, [second]: vertexTo

   distance.resize((int)g.size(), INT_MAX);
   parent.resize((int)g.size());

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
}

inline void getPath(const vector < int >& distance, const vector < int >& parent, const int f, const int s, string& outStr)
{
   //outStr = to_string(f) + "\t\t" + to_string(s) + "\t\t" + to_string(distance[s]);
   outStr = "Begin: " + to_string(f) + ",\tend: " + to_string(s) + ",\tdistance: " + to_string(distance[s]) + ",\tpath: ";
   vector < int > path;
   for (int x = s; x != f; x = parent[x])
      path.pb(x);
   path.pb(f);
   reverse(all(path));

   for (auto x : path)
      outStr += to_string(x) + " ";
}

inline void getAllRoutes(const vector < vector < pii > >& graph, ostream& out)
{
   int graphSize = (int)graph.size();

   #pragma omp parallel for schedule(dynamic, 100)
   for (int startVertex = 1; startVertex < graphSize; ++startVertex)
   {
      vector <int> distance;
      vector <int> parent;
      string path;
      dijkstra(graph, startVertex, distance, parent);

      for (int i = 1; i < (int)graph.size(); ++i)
      {
         if (i == startVertex || distance[i] == INT_MAX)
            continue;

         getPath(distance, parent, startVertex, i, path);

         out << path + "\n";
      }
   }

}

int main()
{
   setlocale(LC_ALL, "");

   Timer timer;

   ifstream in; in.open("input.txt");
   if (!in.is_open()) throw exception("Input file is not open!");

   int n, m;
   in >> n >> m;

   vector < vector < pii > > g(n + 1);  // [first]: vertexTo, [second]: weight 

   for (int i = 1; i <= m; ++i)
   {
      int u, v, w;
      in >> u >> v >> w;
      g[u].pb(mp(v, w));
      g[v].pb(mp(u, w));
   }

   in.close();

   ofstream out("output.txt");
   if (!out.is_open()) throw exception("Output file is not open!");

   timer.reset();
   getAllRoutes(g, out);
   cout << timer.elapsed() << endl;

   out.close();
   return 0;
}