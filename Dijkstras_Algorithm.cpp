#include <iostream>
#include <vector>
#include <string>
#include <list>
 
#include <set>
#include <algorithm>
#include <iterator>

using namespace std; 
 
typedef int vertex_t;
typedef int weight_t;
 
const weight_t max_weight = 1000000000;
 
struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) 
    { }
};
 
typedef vector<vector<neighbor> > adjacency_list_t;

template<typename T>
void resetVector(vector<T> &v, size_t n, T d)
{
    v.clear();
    v.resize(n, d);
}
 
void Dijkstra(vertex_t source,
              const adjacency_list_t &adjacency_list,
              vector<weight_t> &min_distance,
              vector<vertex_t> &previous)
{
    int n = adjacency_list.size();
    resetVector(min_distance, n, max_weight);
    min_distance[source] = 0;
    resetVector(previous, n, -1);
    set<pair<weight_t, vertex_t> > vertex_queue;
    vertex_queue.insert(make_pair(min_distance[source], source));
 
    while (!vertex_queue.empty()) 
    {
        weight_t dist = vertex_queue.begin()->first;
        vertex_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());
 
        // Visit each edge exiting u
        const vector<neighbor> &neighbors = adjacency_list[u];
        for (vector<neighbor>::const_iterator it = neighbors.begin(); it != neighbors.end(); it++)
        {
            vertex_t v = it->target;
            weight_t weight = it->weight;
            weight_t distance_through_u = dist + weight;
            if (distance_through_u < min_distance[v]) 
            {
                vertex_queue.erase(make_pair(min_distance[v], v));     
                min_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.insert(make_pair(min_distance[v], v)); 
            } 
        }
    }
}
 
 
list<vertex_t> GetPathTo(vertex_t vertex, const vector<vertex_t> &previous)
{
    list<vertex_t> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}
 
 
int main()
{
    // remember to insert edges both ways for an undirected graph
    adjacency_list_t adjacency_list(6);
    // 0 = a
    adjacency_list[0].push_back(neighbor(1, 7));
    adjacency_list[0].push_back(neighbor(2, 9));
    adjacency_list[0].push_back(neighbor(5, 14));
    // 1 = b
    adjacency_list[1].push_back(neighbor(0, 7));
    adjacency_list[1].push_back(neighbor(2, 10));
    adjacency_list[1].push_back(neighbor(3, 15));
    // 2 = c
    adjacency_list[2].push_back(neighbor(0, 9));
    adjacency_list[2].push_back(neighbor(1, 10));
    adjacency_list[2].push_back(neighbor(3, 11));
    adjacency_list[2].push_back(neighbor(5, 2));
    // 3 = d
    adjacency_list[3].push_back(neighbor(1, 15));
    adjacency_list[3].push_back(neighbor(2, 11));
    adjacency_list[3].push_back(neighbor(4, 6));
    // 4 = e
    adjacency_list[4].push_back(neighbor(3, 6));
    adjacency_list[4].push_back(neighbor(5, 9));
    // 5 = f
    adjacency_list[5].push_back(neighbor(0, 14));
    adjacency_list[5].push_back(neighbor(2, 2));
    adjacency_list[5].push_back(neighbor(4, 9));
 
    vector<weight_t> min_distance;
    vector<vertex_t> previous;
    Dijkstra(0, adjacency_list, min_distance, previous);
    cout << "Distance from 0 to 4: " << min_distance[4] << endl;
    list<vertex_t> path = GetPathTo(4, previous);
    for(list<vertex_t>::iterator it = path.begin(); it != path.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
 
    return 0;
}