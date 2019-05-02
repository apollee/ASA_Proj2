#include <stdio.h>
#include <stdlib.h>
#include <vector>

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

    Vertex source;
    source.height = numberVertexs;
    source.excess_flow = 0;
    source.limit = 0;
    graph.push_back(source);

    for(i = 0; i < numberSuppliers; i++) {
        if(scanf("%d ", &productionOfSupplier) != 1) {
            return -1;
        }else{
            Vertex supplier;
            supplier.height = 0;
            supplier.excess_flow = productionOfSupplier;
            supplier.limit = productionOfSupplier;
            graph.push_back(supplier);
        }
    }

    for(i = 0; i < numberStations; i++) {
        if(scanf("%d ", &capacityOfStation) != 1) {
            return -1;
        }else{
            Vertex station;
            station.height = 0;
            station.excess_flow = 0;
            station.limit = capacityOfStation;
            graph.push_back(station);
        }
    }

    for(i = 0; i < numberConnections; i++) {
        if(scanf("%d %d %d", &originConnection, &destinationConnection,
        &capacityConnection) != 1) {
            return -1;
        }else{
            Edge connection;
            connection.id = destinationConnection;
            connection.capacity = capacityConnection;
            graph[originConnection].adjs.push_back(connection);
        }
    }
    return 0;
}

void printGraph() {
    int i;
    std::size_t j;
    for(i = 0; i < numberSuppliers; i++){
        printf("altura: %d\nexcesso: %d\nlimite: %d\n", graph[i].height, graph[i].excess_flow, graph[i].limit);
        for(auto adj: graph[i].adjs)
            printf("capacidade: %d\nid: %d\bflow: %d\n", adj.capacity, adj.id, adj.flow);
    }

    printf("O LAMEGO E UM BURRO DO CRLH\n");

    for(i = numberSuppliers; i < numberVertexs -2; i++){
        printf("altura: %d\nexcesso: %d\nlimite: %d\n", graph[i].height, graph[i].excess_flow, graph[i].limit);
        for(j = 1; j < graph[i].adjs.size(); j++){
            printf("capacidade: %d\nid: %d\bflow: %d\n", graph[i].adjs[j].capacity, graph[i].adjs[j].id, graph[i].adjs[j].flow);        
        }
        printf("%lu\n", graph[2].adjs.size());
    }
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