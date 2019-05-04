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
    std::vector<Edge> back_edges;
}Vertex;


/*-------------------------------------------------------------------------*/
int readInput();
int min(int v1, int v2);
void printGraph();
Vertex initializeVertex(int height, int flow, int limit);
Edge initializeEdge(int capacity, int id, int flow);

/*----------------Global Vars-----------------*/
std::vector<Vertex> graph;
int numberSuppliers, numberVertexs;
int listRelabel;

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

    Vertex target = initializeVertex(0, 0, INT_MAX);
    graph.push_back(target);

    Vertex source = initializeVertex(numberVertexs, 0 , 0);
    graph.push_back(source);

  
    for(i = 0; i < numberSuppliers; i++) {
        if(scanf("%d ", &productionOfSupplier) != 1) {
            return -1;
        }else{
            Vertex supplier = initializeVertex(0, 0, productionOfSupplier);
            graph.push_back(supplier);
            Edge s_v = initializeEdge(INT_MAX, 0, 0);
            graph[i + 2].adjs.push_back(s_v);
        }
    }

    for(i = 0; i < numberStations; i++) {
        if(scanf("%d ", &capacityOfStation) != 1) {
            return -1;
        }else{
            Vertex station = initializeVertex(0, 0, capacityOfStation);
            graph.push_back(station);
        }
    }

    for(i = 0; i < numberConnections; i++) {
        if(scanf("%d %d %d", &originConnection, &destinationConnection,
        &capacityConnection) != 3) {
            return -1;
        }else{
            Edge connection = initializeEdge(capacityConnection, originConnection, 0);
            graph[destinationConnection].adjs.push_back(connection);
            Edge back = initializeEdge(0, destinationConnection, 0);
            graph[originConnection].back_edges.push_back(connection);
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
        printf("---------connections back edges-------\n");
        for(auto adj: graph[i].adjs)
            printf("capacidade: %d\nid: %d\nflow: %d\n", adj.capacity, adj.id, adj.flow);
    }
}


Vertex initializeVertex(int height, int flow, int limit){
    Vertex v;
    v.height = height;
    v.excess_flow = flow;
    v.limit = limit;
    return v;
}

Edge initializeEdge(int capacity, int id, int flow){
    Edge e;
    e.capacity = capacity;
    e.id = id;
    e.flow = flow;
    return e;
}

void Push(Vertex v1, Vertex v2, Edge edge, Edge back){
    int current_flow;
    current_flow = min(v1.excess_flow, edge.capacity);
    edge.flow += current_flow;
    back.flow -= current_flow;
    v1.excess_flow -= current_flow;
    v2.excess_flow += current_flow;
}

void Relabel(Vertex v1){
    v1.height = 1 + min_edges(v1);
}

Vertex getVertex(int id){
    return graph[id];
}

int min(int v1, int v2){
    return (v1 > v2 ? v2: v1);
}

int min_edges(Vertex v1){
    int min = INT_MAX;
    for(auto adj: v1.adjs){
        min = min > adj.id ? adj.id : min;
    }
    for(auto back_edge: v1.back_edges){
        min = min > back_edge.id ? back_edge.id : min; 
    }
    return min;
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