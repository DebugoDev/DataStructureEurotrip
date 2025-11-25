#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include "Edge.h"

class Graph {
private:
    int numVertices;
    std::vector<std::vector<Edge>> adjList;
    std::vector<std::string> vertexNames;  
    
public:
    Graph();
    Graph(int numVertices);
    
    void addEdge(int source, int target, double distance, double time, double cost);
    void addBidirectionalEdge(int source, int target, double distance, double time, double cost);
    void removeEdge(int source, int target);
    
    int getNumVertices() const;
    const std::vector<Edge>& getAdjacents(int vertex) const;
    std::vector<Edge> getAllEdges() const;
    
    void setVertexName(int vertex, const std::string& name);
    std::string getVertexName(int vertex) const;
    
    bool edgeExists(int source, int target) const;
    void printGraph() const;
    
    ~Graph();
};

#endif