class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, pair<int, int>>>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], {edge[2], edge[3]}});
        }

        vector<long long> dist(n, -1);
        dist[0] = 0;

        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [time, u] = pq.top();
            pq.pop();

            if (time > dist[u] && dist[u] != -1) {
                continue;
            }

            for (const auto& edge : adj[u]) {
                int v = edge.first;
                long long start = edge.second.first;
                long long end = edge.second.second;

                long long departure_time = max(time, start);
                if (departure_time <= end) {
                    long long arrival_time = departure_time + 1;
                    if (dist[v] == -1 || arrival_time < dist[v]) {
                        dist[v] = arrival_time;
                        pq.push({arrival_time, v});
                    }
                }
            }
        }
        return static_cast<int>(dist[n - 1]);
    }
};
