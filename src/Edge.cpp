#include "../include/Edge.h"
#include <stdexcept>

Edge::Edge() : source(0), target(0), distance(0.0), time(0.0), cost(0.0) {}

Edge::Edge(int source, int target, double distance, double time, double cost)
    : source(source), target(target), distance(distance), time(time), cost(cost) {}

int Edge::getSource() const { return source; }
int Edge::getTarget() const { return target; }
double Edge::getDistance() const { return distance; }
double Edge::getTime() const { return time; }
double Edge::getCost() const { return cost; }

void Edge::setSource(int source) { this->source = source; }
void Edge::setTarget(int target) { this->target = target; }
void Edge::setDistance(double distance) { this->distance = distance; }
void Edge::setTime(double time) { this->time = time; }
void Edge::setCost(double cost) { this->cost = cost; }

double Edge::getWeight(const std::string &criterion) const
{
    if (criterion == "distance")
        return distance;
    if (criterion == "time")
        return time;
    if (criterion == "cost")
        return cost;
    throw std::invalid_argument("Invalid criterion. Use 'distance', 'time', or 'cost'");
}

bool Edge::operator<(const Edge &other) const
{
    return this->distance < other.distance;
}