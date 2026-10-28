
#include "Graph.h"

#include <iomanip>
#include <iostream>

using namespace std;

void displayLocations(const Graph& graph) {
    cout << "\nAvailable Locations:\n";

    for (int i = 0; i < graph.size(); ++i) {
        cout << i + 1 << ". "
             << graph.getLocation(i) << '\n';
    }
}

void displayRoute(
    const Graph& graph,
    const RouteResult& result,
    double costPerKm,
    const char* algorithm
) {
    cout << "\n--- " << algorithm << " Result ---\n";

    if (!result.found) {
        cout << "No route found.\n";
        return;
    }

    cout << "Route: ";

    for (size_t i = 0; i < result.path.size(); ++i) {
        if (i > 0) cout << " -> ";
        cout << graph.getLocation(result.path[i]);
    }

    cout << fixed << setprecision(2);
    cout << "\nTotal distance: "
         << result.totalDistance << " km\n";

    cout << "Estimated travel cost: Rs. "
         << result.totalDistance * costPerKm << '\n';
}

int main() {
    Graph graph;

    graph.addLocation("College");
    graph.addLocation("Bus Stand");
    graph.addLocation("Railway Station");
    graph.addLocation("City Center");
    graph.addLocation("Airport");
    graph.addLocation("Shopping Mall");

    graph.addRoad(0, 1, 3);
    graph.addRoad(0, 2, 5);
    graph.addRoad(1, 2, 2);
    graph.addRoad(1, 3, 4);
    graph.addRoad(2, 3, 2);
    graph.addRoad(2, 4, 8);
    graph.addRoad(3, 4, 5);
    graph.addRoad(3, 5, 2);
    graph.addRoad(5, 4, 4);

    int choice = -1;

    while (true) {
        cout << "\n====== SMART ROUTE FINDER ======\n";
        cout << "1. Display locations\n";
        cout << "2. Find route using Dijkstra\n";
        cout << "3. Find route using A*\n";
        cout << "4. Compare algorithms\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            return 1;
        }

        if (choice == 0) {
            cout << "Smart Route Finder closed.\n";
            break;
        }

        if (choice == 1) {
            displayLocations(graph);
            continue;
        }

        if (choice < 2 || choice > 4) {
            cout << "Invalid choice.\n";
            continue;
        }

        displayLocations(graph);

        int source, destination;
        double costPerKm;

        cout << "Enter source number: ";
        if (!(cin >> source)) return 1;

        cout << "Enter destination number: ";
        if (!(cin >> destination)) return 1;

        cout << "Enter cost per kilometre (Rs.): ";
        if (!(cin >> costPerKm)) return 1;

        if (source < 1 || source > graph.size() ||
            destination < 1 || destination > graph.size() ||
            costPerKm < 0) {
            cout << "Invalid location or cost.\n";
            continue;
        }

        --source;
        --destination;

        RouteResult d = graph.dijkstra(source, destination);
        RouteResult a = graph.aStar(source, destination);

        if (choice == 2) {
            displayRoute(graph, d, costPerKm, "Dijkstra");
        } else if (choice == 3) {
            displayRoute(graph, a, costPerKm, "A*");
        } else {
            displayRoute(graph, d, costPerKm, "Dijkstra");
            displayRoute(graph, a, costPerKm, "A*");

            cout << "\nBoth algorithms found the same "
                    "shortest distance: "
                 << (d.found && a.found &&
                     d.totalDistance == a.totalDistance
                     ? "Yes" : "No") << '\n';
        }
    }

    return 0;
}
