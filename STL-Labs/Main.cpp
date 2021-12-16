#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <queue>
#include <sstream>
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

pair < vector < int >, vector < int > > dijkstra (vector < vector < pii > > g, int f) {
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

string getPath(vector < int > distance, vector < int > parent, int f, int s)
{
   stringstream outSs;

   if (distance[s] != INT_MAX)
   {
      outSs << "Vertex to: " << s << ", distance: " << distance[s] << ", path: ";

      vector < int > path;
      for (int x = s; x != f; x = parent[x])
         path.pb(x);
      path.pb(f);
      reverse(all(path));

      for (auto x : path)
         outSs << x << ' ';
      outSs << endl;
   }
   else
   {
      outSs << "There is no path from " << f << " to " << s << endl;
   }
   return outSs.str();
}

void getAllRoutesBy(int startVertex, vector < vector < pii > > graph)
{
   ofstream out; out.open(outputPath + to_string(startVertex) + ".txt");
   if (!out.is_open()) throw exception("Output file is not open!");
   
   pair < vector < int >, vector < int > > babah = dijkstra(graph, startVertex);

   vector < int > d = babah.F;
   vector < int > p = babah.S;

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
   //   stringstream ss;
   //   ss << "Getting routes to vertex " << i << endl;
   //   cerr << ss.str();

   //   getAllRoutesBy(i, g);

   //   ss.str("");
   //   ss << "All routes to vertex " << i << " is already printed" << endl;
   //   cerr << ss.str();
   //}

   //cerr << "Linear program is over by " << timer.elapsed() << " second" << endl;

   timer.reset();
#pragma omp parallel for num_threads(12) schedule(dynamic)
   for (int i = 1; i < g.size(); ++i)
   {
      stringstream ss;
      ss << "Getting routes to vertex " << i << endl;
      cerr << ss.str();

      getAllRoutesBy(i, g);

      ss.str("");
      ss << "All routes to vertex " << i << " is already printed" << endl;
      cerr << ss.str();
   }

   cerr << "Parallel program is over by " << timer.elapsed() << " second" << endl;

   return 0;
}