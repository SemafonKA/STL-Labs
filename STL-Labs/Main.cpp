#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <set>

using namespace std;

struct WeightedEdge
{
   size_t weight;
   size_t firstVertex;
   size_t secondVertex;
};

bool operator< (const WeightedEdge& first, const WeightedEdge& second)
{
   return first.weight < second.weight;
}

struct WeightedGraph
{
   vector<WeightedEdge> edges;
   set<size_t> vertices;

   void addEdge(WeightedEdge edge)
   {
      edges.push_back(edge);
      vertices.insert(edge.firstVertex);
      vertices.insert(edge.secondVertex);      
   }
};

WeightedGraph PrimaALgMinimalTree(WeightedGraph initialGraph)
{
   list<size_t> unchoosedVertices;
   for (auto& vertex : initialGraph.vertices)
   {
      unchoosedVertices.push_back(vertex);
   }

   list<size_t> choosedVertices;
   priority_queue<WeightedEdge> edges;

   while (unchoosedVertices.size() != 0)
   {
      // Если недобавленных рёбер нет, то добавляем в список вершину, у которой
      // должны найтись недобавленные рёбра
      if (edges.size() == 0)
      {
         auto vertex = unchoosedVertices.front();
         choosedVertices.push_back(vertex);
         unchoosedVertices.pop_front();

         // Добавляем все рёбра, связанные с этой вершиной
         for (auto& edge : initialGraph.edges)
         {
            if (edge.firstVertex == vertex || edge.secondVertex == vertex)
            {
               edges.push(edge);
            }
         }
      }
      
   }

   return initialGraph;
}

int main()
{
   //size_t numVertices, numEdges;
   //cin >> numVertices >> numEdges;

   //WeightedGraph initialGraph;
   //// Считали граф с файла по рёбрам
   //for (size_t i = 0; i < numEdges; i++)
   //{
   //   WeightedEdge edge;
   //   cin >> edge.firstVertex >> edge.secondVertex >> edge.weight;
   //   edge.firstVertex--; edge.secondVertex--;
   //   initialGraph.addEdge(edge);
   //}

   priority_queue<WeightedEdge> que;
   WeightedEdge edge; edge.firstVertex = 1; edge.secondVertex = 2, edge.weight = 4;
   que.push(edge);
   edge.firstVertex = 1; edge.secondVertex = 3, edge.weight = 6;
   que.push(edge);

   while (!que.empty())
   {
      edge = que.top();
      que.pop();
      cout << edge.weight << " " << edge.firstVertex << " " << edge.secondVertex << endl;
   }
}