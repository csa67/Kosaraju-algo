#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>

using namespace std;

void dfsFillStack(int node, vector<vector<int>>& adjList, vector<bool>& visited, stack<int>& finishStack);
void dfsTranspose(int node, vector<vector<int>>& adjList, vector<bool>& visited, vector<int>& scc_nodes);
vector<vector<int>> getTransposeGraph(vector<vector<int>>& adjList, int V);

void Kosaraju(vector<vector<int>>& adjList, int V){
    
    vector<bool> visited(V, false);
    stack<int> finishStack;

    //Step 1:Perform DFS and fill stack with finishing times
    for(int i=0; i<V;i++){
        if(!visited[i]){
            dfsFillStack(i,adjList,visited,finishStack);
        }
    }

    //Step2: Transpose the whole graph
    vector<vector<int>> transposedGraph = getTransposeGraph(adjList, V);

    for(const auto& edge:transposedGraph){
        for(int node:edge){
            cout<<node<<" ";
        }
        cout<<endl;
    }

    fill(visited.begin(),visited.end(),false);
    int scc = 0;
    vector<vector<int>> scc_list;

    //Step 3: Perform DFS based on the finish stack on the transposed graph
    while(!finishStack.empty()){
        int node = finishStack.top();
        finishStack.pop();

        if(!visited[node]){
            vector<int> scc_nodes;
            dfsTranspose(node,transposedGraph,visited,scc_nodes);
            scc++;
            scc_list.push_back(scc_nodes);
        }
    }

    cout<< "Total no:of strongly connected components: " << scc << endl;
    for(const auto& scc:scc_list){
        for(int node:scc){
            cout<<node<<" ";
        }
        cout<<endl;
    }
}

void dfsFillStack(int node, vector<vector<int>>& adjList, vector<bool>& visited, stack<int>& finishStack){

    visited[node] = true;
    vector<int>& neighborsList = adjList[node];
    for(int neighbor:neighborsList){
        if(!visited[neighbor]){
            dfsFillStack(neighbor,adjList,visited,finishStack);
        }
    }
    finishStack.push(node);
}

void dfsTranspose(int node, vector<vector<int>>& adjList, vector<bool>& visited, vector<int>& scc_nodes){

    visited[node] = true;
    scc_nodes.push_back(node);

    vector<int>& neighborsList = adjList[node];
    for(int neighbor:neighborsList){
        if(!visited[neighbor]){
            dfsTranspose(neighbor,adjList,visited,scc_nodes);
        }
    }
}

vector<vector<int>> getTransposeGraph(vector<vector<int>>& adjList, int V){
    vector<vector<int>> new_graph(V);
    for(int u=0; u<V;u++){
        for(int v: adjList[u]){
            new_graph[v].push_back(u);
        }
    }

    return new_graph;
}

int main(){
    int V,E;

    cout << "Enter number of vertices (V): ";
    cin >> V;
    cout << "Enter number of edges (E): ";
    cin >> E;

    vector<vector<int>> adjList(V);
    cout << "Enter the edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);  // Add edge u -> v
    }

    Kosaraju(adjList, V);

    return 0;
}