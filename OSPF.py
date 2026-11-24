import heapq

def ospf_shortest_path(graph, start):
    distances = {node: float('inf') for node in graph}
    previous = {node: None for node in graph}
    distances[start] = 0
    pq = [(0, start)]

    while pq:
        current_dist, current_node = heapq.heappop(pq)
        if current_dist > distances[current_node]:
            continue

        for neighbor, weight in graph[current_node].items():
            distance = current_dist + weight
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                previous[neighbor] = current_node
                heapq.heappush(pq, (distance, neighbor))

    return distances, previous

# 라우터 토폴로지 (가중치 = 링크 비용)
topology = {
    'R1': {'R2': 2, 'R3': 5},
    'R2': {'R1': 2, 'R3': 1, 'R4': 4},
    'R3': {'R1': 5, 'R2': 1, 'R4': 2, 'R5': 3},
    'R4': {'R2': 4, 'R3': 2, 'R5': 1},
    'R5': {'R3': 3, 'R4': 1}
}

dist, prev = ospf_shortest_path(topology, 'R1')
for dest in topology:
    path = []
    curr = dest
    while curr:
        path.append(curr)
        curr = prev[curr]
    print(f"R1 -> {dest} | 최소 비용: {dist[dest]} | 경로: {' -> '.join(reversed(path))}")
