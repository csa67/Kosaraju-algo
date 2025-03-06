#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>

using namespace std;

void Kosaraju(vector<vector<int>>& adjList, int V){
    
    vector<bool> visited(V, false);
    stack<int> finishStack;

    //Step 1:Perform DFS and fill stack with finishing times
    for(int i=0; i<V;i++){
        if(!visited[i]){
            dfsFillStack(i,adjList,visited,finishStack);
        }
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

void dfsTranspose(int node, vector<vector<int>>& adjList, vector<bool>& visited){

    visited[node] = true;
    vector<int>& neighborsList = adjList[node];
    for(int neighbor:neighborsList){
        if(!visited[neighbor]){
            dfsTranspose(neighbor,adjList,visited);
        }
    }
}
