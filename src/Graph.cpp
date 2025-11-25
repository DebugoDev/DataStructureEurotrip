#include "../include/Graph.h"
#include <iostream>
#include <iomanip>

Graph::Graph() : numVertices(0) {}

Graph::Graph(int numVertices) : numVertices(numVertices)
{
    adjList.resize(numVertices);
    vertexNames.resize(numVertices);
}

void Graph::addEdge(int source, int target, double distance, double time, double cost)
{
    if (source < 0 || source >= numVertices || target < 0 || target >= numVertices)
    {
        std::cerr << "Error: Invalid vertices!" << std::endl;
        return;
    }

    Edge edge(source, target, distance, time, cost);
    adjList[source].push_back(edge);
}

void Graph::addBidirectionalEdge(int source, int target, double distance, double time, double cost)
{
    addEdge(source, target, distance, time, cost);
    addEdge(target, source, distance, time, cost);
}

void Graph::removeEdge(int source, int target)
{
    if (source < 0 || source >= numVertices)
        return;

    for (auto it = adjList[source].begin(); it != adjList[source].end(); ++it)
    {
        if (it->getTarget() == target)
        {
            adjList[source].erase(it);
            break;
        }
    }
}

int Graph::getNumVertices() const { return numVertices; }

const std::vector<Edge> &Graph::getAdjacents(int vertex) const
{
    return adjList[vertex];
}

std::vector<Edge> Graph::getAllEdges() const
{
    std::vector<Edge> edges;
    for (int i = 0; i < numVertices; i++)
    {
        for (const Edge &edge : adjList[i])
            edges.push_back(edge);
    }
    return edges;
}

void Graph::setVertexName(int vertex, const std::string &name)
{
    if (vertex >= 0 && vertex < numVertices)
        vertexNames[vertex] = name;
}

std::string Graph::getVertexName(int vertex) const
{
    if (vertex >= 0 && vertex < numVertices && !vertexNames[vertex].empty())
        return vertexNames[vertex];
    return std::to_string(vertex);
}

bool Graph::edgeExists(int source, int target) const
{
    if (source < 0 || source >= numVertices)
        return false;

    for (const Edge &edge : adjList[source])
    {
        if (edge.getTarget() == target)
            return true;
    }
    return false;
}

void Graph::printGraph() const
{
    std::cout << "\n=== GRAPH ===" << std::endl;
    for (int i = 0; i < numVertices; i++)
    {
        std::cout << getVertexName(i) << " -> ";
        for (const Edge &edge : adjList[i])
        {
            std::cout << "(" << getVertexName(edge.getTarget())
                      << ", D:" << edge.getDistance()
                      << ", T:" << edge.getTime()
                      << ", C:" << edge.getCost() << ") ";
        }
        std::cout << std::endl;
    }
}

Graph::~Graph() {}