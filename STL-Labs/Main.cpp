#include <iostream>
#include <vector>

using namespace std;

struct WeightedEdge
{
   unsigned int vertex;
   unsigned int weight;
};

using WeightedGraph = vector<vector<WeightedEdge>>;

int main()
{
   size_t numVertex, numEdges;
   cin >> numVertex >> numEdges;

   auto initialGraph = WeightedGraph(numVertex);
   // Считали граф с файла по рёбрам
   for (size_t i = 0; i < numEdges; i++)
   {
      size_t vertex;  WeightedEdge edge;
      cin >> vertex >> edge.vertex >> edge.weight;
      edge.vertex--;
      initialGraph[vertex - 1].push_back(edge);
   }
}