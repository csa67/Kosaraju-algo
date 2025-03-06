def kosaraju(adjList, V):
    """Finds and prints the Strongly Connected Components (SCCs) using Kosaraju's Algorithm."""
    visited = [False] * V
    finishStack = []

    #Step 1:Perform DFS and fill stack with finishing times
    for node in range(V):
        if not visited[node]:
            dfsFinishStack(node, adjList, visited, finishStack)

    #Step 2: Transpose the graph
    transposed_graph = getTransposedGraph(adjList)

    visited = [False] * V
    scc_cnt = 0
    scc_list = []

    #Step 3: Perform DFS based on the finish stack on the transposed graph
    while finishStack:
        node = finishStack.pop()
        if not visited[node]:
            scc = []
            dfsTranspose(node, transposed_graph, visited, scc)
            scc_cnt += 1
            scc_list.append(scc)

    return scc_cnt, scc_list


def dfsFinishStack(node, adjList, visited, finishStack):
    """Performs DFS and pushes nodes to finishStack based on their finishing time."""
    visited[node] = True
    for neighbor in adjList.get(node, []):
        if not visited[neighbor]:
            dfsFinishStack(neighbor, adjList, visited, finishStack)
    finishStack.append(node)


def getTransposedGraph(adjList):
    """Returns the transposed graph where all edges are reversed."""
    transposed_graph = {i: [] for i in adjList}
    for u in adjList:
        for v in adjList[u]:
            transposed_graph[v].append(u)
    return transposed_graph


def dfsTranspose(node, adjList, visited, scc):
    """Performs DFS on the transposed graph to find SCCs."""
    visited[node] = True
    scc.append(node)
    for neighbor in adjList.get(node, []):
        if not visited[neighbor]:
            dfsTranspose(neighbor, adjList, visited, scc)


def get_user_input():
    """Takes user input for graph vertices, edges, and adjacency list."""
    V = int(input("Enter number of vertices: "))
    E = int(input("Enter number of edges: "))

    adjList = {i: [] for i in range(V)}
    print("\nEnter the edges (format: from to):")
    for _ in range(E):
        u, v = map(int, input().split())
        adjList[u].append(v)

    return adjList, V


if __name__ == "__main__":
    adjList, V = get_user_input()
    scc_cnt, scc_list = kosaraju(adjList, V)

    print("\nNumber of Strongly Connected Components:", scc_cnt)
    print("SCCs:", scc_list)
