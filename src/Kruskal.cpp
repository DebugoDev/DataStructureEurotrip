#include "../include/Kruskal.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

UnionFind::UnionFind(int n)
{
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; i++)
        parent[i] = i;
}

int UnionFind::find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

bool UnionFind::unite(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY)
        return false;

    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else
    {
        parent[rootY] = rootX;
        rank[rootX]++;
    }

    return true;
}

KruskalResult Kruskal::run(const Graph &graph, const std::string &criterion)
{
    KruskalResult result;

    std::vector<Edge> edges = graph.getAllEdges();

    std::sort(edges.begin(), edges.end(), [&criterion](const Edge &a, const Edge &b)
              { return a.getWeight(criterion) < b.getWeight(criterion); });

    UnionFind uf(graph.getNumVertices());

    for (const Edge &edge : edges)
    {
        if (uf.unite(edge.getSource(), edge.getTarget()))
        {
            result.edges.push_back(edge);
            result.totalDistance += edge.getDistance();
            result.totalTime += edge.getTime();
            result.totalCost += edge.getCost();

            if (result.edges.size() == (size_t)(graph.getNumVertices() - 1))
                break;
        }
    }

    result.success = (result.edges.size() == (size_t)(graph.getNumVertices() - 1));
    return result;
}

void Kruskal::printResult(const Graph &graph, const KruskalResult &result)
{
    std::cout << "\n=== MINIMUM SPANNING TREE (KRUSKAL) ===" << std::endl;

    if (!result.success)
    {
        std::cout << "Could not construct the MST!" << std::endl;
        return;
    }

    std::cout << "Selected edges:" << std::endl;
    for (const Edge &edge : result.edges)
    {
        std::cout << graph.getVertexName(edge.getSource()) << " -- "
                  << graph.getVertexName(edge.getTarget())
                  << " (D:" << edge.getDistance()
                  << ", T:" << edge.getTime()
                  << ", C:" << edge.getCost() << ")" << std::endl;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nMST Totals:" << std::endl;
    std::cout << "Total Distance: " << result.totalDistance << " km" << std::endl;
    std::cout << "Total Time: " << result.totalTime << " hours" << std::endl;
    std::cout << "Total Cost: $" << result.totalCost << std::endl;
}