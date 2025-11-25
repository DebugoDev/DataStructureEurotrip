#include "../include/Graph.h"
#include <iostream>
#include <iomanip>

using namespace std;

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
        cerr << "Error: Invalid vertices!" << endl;
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

const vector<Edge> &Graph::getAdjacents(int vertex) const
{
    return adjList[vertex];
}

vector<Edge> Graph::getAllEdges() const
{
    vector<Edge> edges;
    for (int i = 0; i < numVertices; i++)
    {
        for (const Edge &edge : adjList[i])
            edges.push_back(edge);
    }
    return edges;
}

void Graph::setVertexName(int vertex, const string &name)
{
    if (vertex >= 0 && vertex < numVertices)
        vertexNames[vertex] = name;
}

string Graph::getVertexName(int vertex) const
{
    if (vertex >= 0 && vertex < numVertices && !vertexNames[vertex].empty())
        return vertexNames[vertex];
    return to_string(vertex);
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
    for (int i = 0; i < numVertices; i++)
    {
        cout << getVertexName(i) << ": ";
        for (const Edge &edge : adjList[i])
        {
            cout << "(" << getVertexName(edge.getTarget())
                 << ", D:" << edge.getDistance()
                 << ", T:" << edge.getTime()
                 << ", C:" << edge.getCost() << ") ";
        }
        cout << endl;
    }
}

Graph::~Graph() {}