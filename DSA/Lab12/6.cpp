typedef pair<int, char> NodePair;
typedef map<char, vector<NodePair>> WeightedAdjList;

void dijkstra(const WeightedAdjList& graph, char source, char target) {
    map<char, int> dist;
    map<char, char> parent;
    
    for (const auto& pair : graph) {
        dist[pair.first] = INF;
        parent[pair.first] = '\0';
    }
    
    dist[source] = 0;

    priority_queue<NodePair, vector<NodePair>, greater<NodePair>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int d = pq.top().first;
        char u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        if (u == target) break;

        for (const auto& edge : graph.at(u)) {
            char v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    
    cout << "Shortest Path from " << source << " to " << target << "\n";
    cout << "Distance: " << dist[target] << "\n";

    cout << "Path: ";
    if (dist[target] == INF) {
        cout << "No path exists.\n";
    } else {
        vector<char> path;
        char current = target;
        while (current != '\0') {
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        cout << "\n";
    }
}
