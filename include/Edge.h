#ifndef EDGE_H
#define EDGE_H

#include <string>

class Edge
{
private:
    int source;
    int target;
    double distance;
    double time;
    double cost;

public:
    Edge();
    Edge(int source, int target, double distance, double time, double cost);

    int getSource() const;
    int getTarget() const;
    double getDistance() const;
    double getTime() const;
    double getCost() const;

    void setSource(int source);
    void setTarget(int target);
    void setDistance(double distance);
    void setTime(double time);
    void setCost(double cost);

    double getWeight(const std::string &criterion) const;

    bool operator<(const Edge &other) const;
};

#endif