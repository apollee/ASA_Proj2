#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <limits.h>
/*-------------------------------------------------------------------------*/

typedef struct edge{
    int capacity;
    int id;
    int flow; 
}Edge;

typedef struct vertex{
    int height;
    int excess_flow;
    int limit;
    std::vector<Edge> adjs;
}Vertex;


/*-------------------------------------------------------------------------*/
int readInput();
void printGraph();
Vertex inicializeVertex(int height, int flow, int limit);
Edge inicializeEdge(int capacity, int id, int flow);

/*----------------Global Vars-----------------*/
std::vector<Vertex> graph;
int numberSuppliers, numberVertexs;

int main(){
    readInput();
    printGraph();
}


int readInput() {
    int i;
    int numberStations, numberConnections;
    int productionOfSupplier, capacityOfStation;
    int originConnection, destinationConnection, capacityConnection;

    if(scanf("%d %d %d", &numberSuppliers, &numberStations, &numberConnections) != 3) {
        return -1;
    }else{
        numberVertexs = numberSuppliers + numberStations + 2;
        std::vector<Vertex> graph(numberVertexs);
    }

    Vertex source = inicializeVertex(numberVertexs, 0 , 0);
    graph.push_back(source);

    Vertex target = inicializeVertex(0, 0, INT_MAX);
    graph.push_back(target);

    for(i = 0; i < numberSuppliers; i++) {
        if(scanf("%d ", &productionOfSupplier) != 1) {
            return -1;
        }else{
            Vertex supplier = inicializeVertex(0, productionOfSupplier, productionOfSupplier);
            graph.push_back(supplier);
        }
    }

    for(i = 0; i < numberStations; i++) {
        if(scanf("%d ", &capacityOfStation) != 1) {
            return -1;
        }else{
            Vertex station = inicializeVertex(0, 0, capacityOfStation);
            graph.push_back(station);
        }
    }

    for(i = 0; i < numberConnections; i++) {
        if(scanf("%d %d %d", &originConnection, &destinationConnection,
        &capacityConnection) != 3) {
            return -1;
        }else{
            Edge connection = inicializeEdge(capacityConnection, destinationConnection, 0);
            graph[originConnection].adjs.push_back(connection);
        }
    }
    return 0;
}

void printGraph() {
    int i;
    for(i = 0; i < numberVertexs; i++){
        printf("-------------------%d----------------\n", i);
        printf("altura: %d\nexcesso: %d\nlimite: %d\n", graph[i].height, graph[i].excess_flow, graph[i].limit);
        printf("---------connections-------\n");
        for(auto adj: graph[i].adjs)
            printf("capacidade: %d\nid: %d\nflow: %d\n", adj.capacity, adj.id, adj.flow);
    }
}


Vertex inicializeVertex(int height, int flow, int limit){
    Vertex v;
    v.height = height;
    v.excess_flow = flow;
    v.limit = limit;
    return v;
}

Edge inicializeEdge(int capacity, int id, int flow){
    Edge e;
    e.capacity = capacity;
    e.id = id;
    e.flow = flow;
    return e;
}
/*
Discharge(u)
    while (e[u] > 0)
        do v = current[u]
            if v = NIL
                then Relabel(u)
                    current[u] = head[N[u]]
            else if cf(u,v) > 0 and h[u] = h[v] +1
                then Push(u,v)
            else current[u] = next_neighbor[v]*/

/*
Relabel-To-Front(G,s,t)
    Initialize-Preflow(G,s)
    L = V − {s,t} por qualquer ordem
    for each u ∈ V − {s,t}
        do current[u] = head[N[u]]
    u = head[L]
    while u 6= NIL
        do oldh = h[u]
            Discharge(u)
            if h[u] > oldh
               then colocar u na frente da lista L
            u = next[u]
    return f*/