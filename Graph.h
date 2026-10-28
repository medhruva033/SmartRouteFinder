
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

struct Edge {
    int destination;
    double distance;
};

struct RouteResult {
    std::vector<int> path;
    double totalDistance;
    bool found;
};

class Graph {
private:
    std::vector<std::string> locations;
    std::vector<std::vector<Edge>> adjacencyList;

public:
    void addLocation(const std::string& name);
    void addRoad(int from, int to, double distance);

    int size() const;
    std::string getLocation(int id) const;

    RouteResult dijkstra(int start, int goal) const;
    RouteResult aStar(int start, int goal) const;
};

#endif
