import java.util.*;

class KosarajuSCC {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Taking input for number of vertices and edges
        System.out.println("Enter number of vertices:");
        int V = sc.nextInt();
        System.out.println("Enter number of edges:");
        int E = sc.nextInt();

        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        // Taking edges input
        System.out.println("Enter the edges (format: from to):");
        for (int i = 0; i < E; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            adj.get(u).add(v);
        }

        sc.close();

        // Running Kosaraju's algorithm
        KosarajuSCC solver = new KosarajuSCC();
        List<List<Integer>> sccs = solver.kosaraju(adj, V);

        // Printing the result
        System.out.println("Number of Strongly Connected Components: " + sccs.size());
        System.out.println("Strongly Connected Components:");
        for (List<Integer> scc : sccs) {
            System.out.println(scc);
        }
    }

    // Kosaraju's algorithm implementation
    public List<List<Integer>> kosaraju(ArrayList<ArrayList<Integer>> adj, int V) {
        boolean[] visited = new boolean[V];
        Stack<Integer> finishStack = new Stack<>();

        // Step 1: Fill stack with finishing times using DFS
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsFill(i, adj, visited, finishStack);
            }
        }

        // Step 2: Transpose the graph (reverse all edges)
        ArrayList<ArrayList<Integer>> transposed = transposeGraph(adj, V);

        // Step 3: Perform DFS on transposed graph to find SCCs
        Arrays.fill(visited, false);
        List<List<Integer>> sccs = new ArrayList<>();

        while (!finishStack.isEmpty()) {
            int node = finishStack.pop();
            if (!visited[node]) {
                List<Integer> component = new ArrayList<>();
                dfsTranspose(node, transposed, visited, component);
                sccs.add(component);
            }
        }

        return sccs;
    }

    // DFS to fill stack with finishing times
    private void dfsFill(int node, ArrayList<ArrayList<Integer>> adj, boolean[] visited, Stack<Integer> finishStack) {
        visited[node] = true;
        for (int neighbor : adj.get(node)) {
            if (!visited[neighbor]) {
                dfsFill(neighbor, adj, visited, finishStack);
            }
        }
        finishStack.push(node);
    }

    // Function to create the transposed graph (reverse all edges)
    private ArrayList<ArrayList<Integer>> transposeGraph(ArrayList<ArrayList<Integer>> adj, int V) {
        ArrayList<ArrayList<Integer>> transposed = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            transposed.add(new ArrayList<>());
        }

        for (int i = 0; i < V; i++) {
            for (int neighbor : adj.get(i)) {
                transposed.get(neighbor).add(i);
            }
        }

        return transposed;
    }

    // DFS on transposed graph to collect SCCs
    private void dfsTranspose(int node, ArrayList<ArrayList<Integer>> transposed, boolean[] visited, List<Integer> component) {
        visited[node] = true;
        component.add(node);
        for (int neighbor : transposed.get(node)) {
            if (!visited[neighbor]) {
                dfsTranspose(neighbor, transposed, visited, component);
            }
        }
    }
}
