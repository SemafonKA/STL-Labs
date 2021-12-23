#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>
#include <chrono>

#pragma region Trash)))

#define per(name, beg, en) for (int name = beg; name <= en; ++name)
#define rep(name, beg, en) for (int name = beg; name >= en; --name)

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()

#define F first
#define S second
#define FF first.first
#define FS first.second
#define SF second.first
#define SS second.second

#pragma endregion

using namespace std;

class Timer
{
private:
   // Псевдонимы типов используются для удобного доступа к вложенным типам
   using clock_t = std::chrono::high_resolution_clock;
   using second_t = std::chrono::duration<double, std::ratio<1> >;

   std::chrono::time_point<clock_t> m_beg;
   double last_elapsed;
public:
   Timer() : m_beg(clock_t::now()), last_elapsed(0)
   {
   }

   void reset()
   {
      m_beg = clock_t::now();
      last_elapsed = 0.0;
   }

   double elapsed()
   {
      last_elapsed = std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
      return last_elapsed;
   }

   inline double getLastElapsed()
   {
      return last_elapsed;
   }
};

using pii = pair<int, int>;

using GraphList = vector<vector<pii>>;       // Граф списком смежности
using GraphMatrix = vector<vector<int>>;     // Граф матрицей смежности

const int inf = INT_MAX;
const pii pinf = mp(inf, inf);

/// <summary>
/// Находит ребро с конечной вершиной [v] в списке смежности [vec] от начальной вершины
/// </summary>
/// <param name="vec"> - список смежности для начальной вершины</param>
/// <param name="v"> - конечная вершина</param>
/// <returns></returns>
inline pii finder(const vector < pii >& vec, int v)
{
   pii ans = pinf;
   for (const auto& x : vec)
      if (x.F == v && x.S < ans.S)
      {
         ans = x;
      }
   return ans;
}

inline void matrixPrinter(const GraphMatrix& graph, ostream& out)
{
   size_t size = graph.size();
   per(u, 1, size - 1)
   {
      per(v, 1, size - 1)
         out << ((graph[u][v] == inf) ? 0 : graph[u][v]) << " \t";
      out << endl;
   }
}

inline void listPrinter(const GraphMatrix& graph, ostream& out)
{
   size_t size = graph.size();
   per(u, 1, size - 1)
   {
      per(v, 1, size - 1)
      {
         if (u != v && graph[u][v] != inf)
         {
            out << u << " \t" << v << " \t" << graph[u][v] << endl;
         }
      }
   }
}

/// <summary>
/// Алгоритм Флойда от матрицы смежности
/// </summary>
/// <param name="sD"> Начальная матрица смежности, она же результат работы</param>
inline void _floyd(GraphMatrix& sD, int numThreads = omp_get_max_threads())
{
   size_t size = sD.size();

#pragma omp parallel for num_threads(numThreads) schedule(dynamic, 200)
   for (int i = 1; i < size; i++)
   {
      for (int u = 1; u < size; u++)
      {
         for (int v = 1; v < size; v++)
         {
            if (sD[u][i] < inf && sD[i][v] < inf)
               sD[u][v] = min(sD[u][v], sD[u][i] + sD[i][v]);
         }
      }
   }
}

void floydAlgMatrix(const GraphMatrix& graph, ostream& out, int numThreads = omp_get_max_threads())
{
   GraphMatrix sD = graph;
   int size = static_cast<int>(sz(graph));

   per(u, 1, size - 1)
      per(v, 1, size - 1)
         if (sD[u][v] == 0)
            sD[u][v] = inf;

   _floyd(sD, numThreads);

   listPrinter(sD, out);
}

void floydAlgList(const GraphList& graph, ostream& out, int numThreads = omp_get_max_threads())
{
   GraphMatrix sD;
   int size = static_cast<int>(sz(graph));
   sD.resize(size);

   per(i, 1, size - 1)
   {
      sD[i].pb(0);   // Заполняем нулевые элементы каждого ряда
      per(j, 1, size - 1)
      {
         sD[i].pb(finder(graph[i], j).S);
      }
   }

   _floyd(sD, numThreads);

   listPrinter(sD, out);
}

// Ввод данных и вызов методов
void solve(int num_threads)
{
   ifstream in("input.txt");
   if (!in.is_open()) throw exception("File input.txt wasn't open!");

   int n, m;
   in >> n >> m;

   GraphMatrix matrixGraph;         // граф матрицей смежности
   GraphList listGraph;             // граф списком смежности
   listGraph.resize(n + 1);
   matrixGraph.resize(n + 1);
   per(i, 1, n)
      matrixGraph[i].resize(n + 1, 0);

   per(i, 1, m)
   {
      int u, v, w;
      in >> u >> v >> w;
      matrixGraph[u][v] = matrixGraph[v][u] = (matrixGraph[u][v] == 0 ? w : min(w, matrixGraph[u][v]));
      listGraph[u].pb(mp(v, w));
      listGraph[v].pb(mp(u, w));
   }
   in.close();

   ofstream outMatrix("outMatrix.txt");
   Timer timer;
   floydAlgMatrix(matrixGraph, outMatrix, num_threads);
   timer.elapsed();
   cout << "Алгоритм по матрице завершил работу за " << timer.getLastElapsed() << " секунд" << endl;
   outMatrix.close();

   ofstream outList("outList.txt");
   timer.reset();
   floydAlgList(listGraph, outList, num_threads);
   timer.elapsed();
   cout << "Алгоритм по листу завершил работу за " << timer.getLastElapsed() << " секунд" << endl;
   outList.close();
}

int main()
{
   setlocale(LC_ALL, "ru");
   vector<int> numThreadsList = { 1 };
   for (int i = 2; i <= omp_get_max_threads(); i += 2) numThreadsList.push_back(i);

   for (auto& numThreads : numThreadsList)
   {
      cout << "************************************" << endl;
      cout << "Работа алгоритмов для [" << numThreads << "] потоков: " << endl << endl;
      solve(numThreads);
      cout << "************************************" << endl << endl;
   }
}