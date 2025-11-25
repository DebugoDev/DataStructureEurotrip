#include "../include/Dijkstra.h"
#include <queue>
#include <iostream>
#include <iomanip>

struct DijkstraNode
{
    int vertex;
    double distance;

    bool operator>(const DijkstraNode &other) const
    {
        return distance > other.distance;
    }
};

DijkstraResult Dijkstra::run(const Graph &graph, int source, const std::string &criterion)
{
    int n = graph.getNumVertices();
    DijkstraResult result(n);

    if (source < 0 || source >= n)
        return result;

    std::priority_queue<DijkstraNode, std::vector<DijkstraNode>, std::greater<DijkstraNode>> pq;

    result.distances[source] = 0.0;
    pq.push({source, 0.0});

    std::vector<bool> visited(n, false);

    while (!pq.empty())
    {
        DijkstraNode current = pq.top();
        pq.pop();

        int u = current.vertex;
        if (visited[u])
            continue;
        visited[u] = true;

        for (const Edge &edge : graph.getAdjacents(u))
        {
            int v = edge.getTarget();
            double weight = edge.getWeight(criterion);

            if (result.distances[u] + weight < result.distances[v])
            {
                result.distances[v] = result.distances[u] + weight;
                result.predecessors[v] = u;
                pq.push({v, result.distances[v]});
            }
        }
    }

    result.success = true;
    return result;
}

std::vector<int> Dijkstra::rebuildPath(const DijkstraResult &result, int target)
{
    std::vector<int> path;

    if (result.predecessors[target] == -1 && result.distances[target] != 0.0)
        return path;

    for (int v = target; v != -1; v = result.predecessors[v])
        path.push_back(v);

    std::reverse(path.begin(), path.end());
    return path;
}

void Dijkstra::calculatePathCosts(const Graph &graph, const std::vector<int> &path,
                                  double &totalDistance, double &totalTime, double &totalCost)
{
    totalDistance = totalTime = totalCost = 0.0;

    for (size_t i = 0; i < path.size() - 1; i++)
    {
        int u = path[i];
        int v = path[i + 1];

        for (const Edge &edge : graph.getAdjacents(u))
        {
            if (edge.getTarget() == v)
            {
                totalDistance += edge.getDistance();
                totalTime += edge.getTime();
                totalCost += edge.getCost();
                break;
            }
        }
    }
}

void Dijkstra::printResult(const Graph &graph, const DijkstraResult &result,
                           int source, int target)
{
    std::cout << "\n=== DIJKSTRA RESULT ===" << std::endl;
    std::cout << "Source: " << graph.getVertexName(source) << std::endl;
    std::cout << "Destination: " << graph.getVertexName(target) << std::endl;

    std::vector<int> path = rebuildPath(result, target);

    if (path.empty())
    {
        std::cout << "No available path!" << std::endl;
        return;
    }

    std::cout << "Path: ";
    for (size_t i = 0; i < path.size(); i++)
    {
        std::cout << graph.getVertexName(path[i]);
        if (i < path.size() - 1)
            std::cout << " -> ";
    }
    std::cout << std::endl;

    double totalDistance, totalTime, totalCost;
    calculatePathCosts(graph, path, totalDistance, totalTime, totalCost);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Distance: " << totalDistance << " km" << std::endl;
    std::cout << "Total Time: " << totalTime << " hours" << std::endl;
    std::cout << "Total Cost: $" << totalCost << std::endl;
}