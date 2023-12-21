#include <iostream>
#include <vector>
#include <limits>
#include <map>
#include <stack>

using namespace std;

const int INF = numeric_limits<int>::max();
//

class Graph
{
    //class graph creation
public:
    int vertices;
    vector<string> buildingNames;
    vector<vector<pair<int, int>>> adjList;
    //vector pair

    Graph(int V) : vertices(V), adjList(V)
    {
        //GRAPH
    }

    void addEdge(int src, int dest, int weight)
    {
        adjList[src].emplace_back(dest, weight);
        //emplace back is used to insert the items at the end of the list
        adjList[dest].emplace_back(src, weight);
    }

    vector<int> dijkstra(int src, map<int, int>& predecessors)
    {
        //finding shortest path
        //vector creation
        vector<int> distance(vertices, INF);
        vector<bool> visited(vertices, false);

        distance[src] = 0;

        for (int i = 0; i < vertices - 1; ++i)
            {
            int u = minDistance(distance, visited);
            visited[u] = true;

            for (const auto &neighbor : adjList[u])
                {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!visited[v] && distance[u] != INF && distance[u] + weight < distance[v])
                    {
                    distance[v] = distance[u] + weight;
                    predecessors[v] = u;
                }
            }
        }

        return distance;
        //normal distance between the points
    }

    int minDistance(const vector<int> &distance, const vector<bool> &visited)
    {
        int minDist = INF;
        int minIndex = -1;

        for (int v = 0; v < vertices; ++v)
        {
            if (!visited[v] && distance[v] < minDist)
                {
                minDist = distance[v];
                minIndex = v;
            }
        }

        return minIndex;
    }

    void printSolution(const vector<int> &distance, const map<int, int>& predecessors, int dest)
    {
        cout << "Shortest distance from " << buildingNames[0] << " to " << buildingNames[dest] << ": " << distance[dest] << " units\n";

        cout << "Shortest path: ";
        stack<int> path;
        int current = dest;
        while (current != -1)
            {
            path.push(current);
            current = predecessors.at(current);
        }

        while (!path.empty())
            {
            cout << buildingNames[path.top()] << " -> ";
            path.pop();
        }
        cout << endl;
        //next line
    }

    map<pair<string, string>, int> calculateDistances()
    {
        map<pair<string, string>, int> distanceMap;

        for (int i = 0; i < vertices; ++i)
            {
            for (const auto &neighbor : adjList[i])
            {
                int v = neighbor.first;
                int weight = neighbor.second;

                distanceMap[{buildingNames[i], buildingNames[v]}] = weight;
            }
        }

        return distanceMap;
        //returning shortest distance
        //or shortest path
    }

    map<pair<string, string>, int> calculateMinDistances()
    {
        //map
        map<pair<string, string>, int> minDistanceMap;

        for (int i = 0; i < vertices; ++i)
            {
            map<int, int> predecessors;
            vector<int> distances = dijkstra(i, predecessors);

            for (int j = 0; j < vertices; ++j)
                {
                if (i != j)
                {
                    minDistanceMap[{buildingNames[i], buildingNames[j]}] = distances[j];
                }
            }
        }

        return minDistanceMap;
    }
};

int main()
{
    cout<<"--------------------WELCOME TO CAMPUS NAVIGATION SYSTEM!--------------------------------"<<endl;
    cout<<"-------- JAYPEE INSTITUTE OF INFORMATION TECHNOLOGY, NOIDA SECTOR - 62-----------------"<<endl;
    cout<<"----------TOTAL 6 BUILDINGS HAVE BEEN TAKEN INTO CONSIDERATION ----------------------"<<endl;
    cout<<"----------ABB I---------\n";
    cout<<"----------ABB II (JBS)-------------\n";
    cout<<"----------ABB III-------------------\n";
    cout<<"----------CAFETERIA------------------\n";
    cout<<"-----------REGISTRAR------------------\n";
    cout<<"-----------HOSTEL BUILDINGS (AS ONE UNIT)-------------\n";
    cout<<endl;
    cout<<endl;
    cout<<"------------------------BY PARINIKA KATH (22103094)------------\n";
    cout<<endl;
    cout<<endl;
    Graph campus(6);

    campus.buildingNames = {"ABB I", "ABB II", "ABB III (JBS)", "CAFETERIA", "REGISTRAR", "HOSTELS"};

    campus.addEdge(0, 1, 3);
    campus.addEdge(0, 2, 5);
    campus.addEdge(1, 2, 2);
    campus.addEdge(1, 3, 6);
    campus.addEdge(2, 4, 4);
    campus.addEdge(3, 4, 1);
    campus.addEdge(3, 5, 7);
    campus.addEdge(4, 5, 2);
    //source, destination, weight
    //insertion one by one and
    //graph creation


    map<pair<string, string>, int> distanceMap = campus.calculateDistances();

    // Calculate and display distances between all pairs of buildings

    cout << "Distances between buildings:\n";

    for (const auto &entry : distanceMap)
    {
        cout << entry.first.first << " to " << entry.first.second << ": " << entry.second << " units\n";
    }

    // Calculate and display minimum distances between all pairs of buildings

    map<pair<string, string>, int> minDistanceMap = campus.calculateMinDistances();

    cout << "\nMinimum distances between buildings:\n";
    //print final

    for (const auto &entry : minDistanceMap)
        {
        cout << entry.first.first << " to " << entry.first.second << ": " << entry.second << " units\n";
    }

    return 0;
    //main close
}
//program ends!
