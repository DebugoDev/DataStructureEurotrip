#include "../include/Kruskal.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

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

KruskalResult Kruskal::run(const Graph &graph, const string &criteria_)
{
    KruskalResult result;

    vector<Edge> edges = graph.getAllEdges();

    sort(edges.begin(), edges.end(), [&criteria_](const Edge &a, const Edge &b)
              { return a.getWeight(criteria_) < b.getWeight(criteria_); });

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
    if (!result.success)
    {
        cout << "Could not construct the MST!" << endl;
        return;
    }

    cout << "Selected edges:" << endl;
    for (const Edge &edge : result.edges)
    {
        cout << graph.getVertexName(edge.getSource()) << " -- "
                  << graph.getVertexName(edge.getTarget())
                  << " (D:" << edge.getDistance()
                  << ", T:" << edge.getTime()
                  << ", C:" << edge.getCost() << ")" << endl;
    }

    cout << fixed << setprecision(2) << endl;
    cout << "Total Distance: " << result.totalDistance << " km" << endl;
    cout << "Total Time: " << result.totalTime << " hours" << endl;
    cout << "Total Cost: $" << result.totalCost << endl;
}