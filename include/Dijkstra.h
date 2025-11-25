#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <string>
#include <limits>
#include "Graph.h"

struct DijkstraResult
{
    std::vector<double> distances;
    std::vector<int> predecessors;
    bool success;

    DijkstraResult(int numVertices)
    {
        distances.resize(numVertices, std::numeric_limits<double>::infinity());
        predecessors.resize(numVertices, -1);
        success = false;
    }
};

class Dijkstra
{
public:
    static DijkstraResult run(const Graph &graph, int source, const std::string &criteria_ = "DISTANCE");

    static std::vector<int> rebuildPath(const DijkstraResult &result, int target);

    static void calculatePathCosts(const Graph &graph, const std::vector<int> &path, double &totalDistance, double &totalTime, double &totalCost);
    static void printResult(const Graph &graph, const DijkstraResult &result, int source, int target);
};

#endif