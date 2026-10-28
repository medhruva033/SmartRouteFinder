
#include "Graph.h"

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <utility>

using namespace std;

void Graph::addLocation(const string& name) {
    locations.push_back(name);
    adjacencyList.emplace_back();
}

void Graph::addRoad(int from, int to, double distance) {
    if (from < 0 || to < 0 ||
        from >= size() || to >= size() ||
        distance < 0) {
        return;
    }

    adjacencyList[from].push_back({to, distance});
    adjacencyList[to].push_back({from, distance});
}

int Graph::size() const {
    return static_cast<int>(locations.size());
}

string Graph::getLocation(int id) const {
    if (id < 0 || id >= size()) {
        return "Unknown";
    }
    return locations[id];
}

RouteResult Graph::dijkstra(int start, int goal) const {
    const double INF = numeric_limits<double>::infinity();

    if (start < 0 || goal < 0 ||
        start >= size() || goal >= size()) {
        return {{}, INF, false};
    }

    vector<double> dist(size(), INF);
    vector<int> parent(size(), -1);

    using State = pair<double, int>;
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        double currentDistance = pq.top().first;
int u = pq.top().second;
        pq.pop();

        if (currentDistance > dist[u]) continue;
        if (u == goal) break;

        for (const Edge& edge : adjacencyList[u]) {
            int v = edge.destination;
            double newDistance = dist[u] + edge.distance;

            if (newDistance < dist[v]) {
                dist[v] = newDistance;
                parent[v] = u;
                pq.push({newDistance, v});
            }
        }
    }

    if (dist[goal] == INF) {
        return {{}, INF, false};
    }

    vector<int> path;

    for (int v = goal; v != -1; v = parent[v]) {
        path.push_back(v);
    }

    reverse(path.begin(), path.end());

    return {path, dist[goal], true};
}

RouteResult Graph::aStar(int start, int goal) const {
    // Zero heuristic: correct for any non-negative road network,
    // but behaves like Dijkstra until a real heuristic is added.
    return dijkstra(start, goal);
}
