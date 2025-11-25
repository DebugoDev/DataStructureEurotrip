#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include <string>
#include "Graph.h"
#include "Edge.h"

class UnionFind
{
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    UnionFind(int n);
    int find(int x);
    bool unite(int x, int y);
};

struct KruskalResult
{
    std::vector<Edge> edges;
    double totalDistance;
    double totalTime;
    double totalCost;
    bool success;

    KruskalResult()
    {
        totalDistance = 0.0;
        totalTime = 0.0;
        totalCost = 0.0;
        success = false;
    }
};

class Kruskal
{
public:
    static KruskalResult run(const Graph &graph, const std::string &criterion = "distance");

    static void printResult(const Graph &graph, const KruskalResult &result);
};

#endif