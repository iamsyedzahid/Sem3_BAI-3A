typedef map<char, vector<char>> AdjList; typedef map<char, map<char, int>> AdjMatrixMap; 
void addEdge(AdjList& adjList, char u, char v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}
void displayAdjMatrix(const AdjMatrixMap& matrix) {
    vector<char> nodes;
    for (auto const& [key, val] : matrix) {
        nodes.push_back(key);
    }
    sort(nodes.begin(), nodes.end());

    cout << "  ";
    for (char node : nodes) cout << node << " ";
    cout << "\n";
    
    for (char rowNode : nodes) {
        cout << rowNode << " ";
        for (char colNode : nodes) {
            cout << matrix.at(rowNode).at(colNode) << " ";
        }
        cout << "\n";
    }
}
void sortAdjList(AdjList& adjList) {
    for (auto& pair : adjList) {
        sort(pair.second.begin(), pair.second.end());
    }
}
void bfs(const AdjList& graph, char startNode) {
    queue<char> q;
    map<char, bool> visited;
    
    q.push(startNode);
    visited[startNode] = true;
    
    cout << "BFS Traversal: ";
    while (!q.empty()) {
        char u = q.front();
        q.pop();
        cout << u << " ";
        
        for (char v : graph.at(u)) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << "\n";
}
void dfs(const AdjList& graph, char startNode) {
    stack<char> s;
    map<char, bool> visited;
    
    s.push(startNode);
    
    cout << "DFS Traversal: ";
    while (!s.empty()) {
        char u = s.top();
        s.pop();
        
        if (!visited[u]) {
            visited[u] = true;
            cout << u << " ";
            
            const vector<char>& neighbors = graph.at(u);
            for (int i = neighbors.size() - 1; i >= 0; --i) {
                char v = neighbors[i];
                if (!visited[v]) {
                    s.push(v);
                }
            }
        }
    }
    cout << "\n";
}
