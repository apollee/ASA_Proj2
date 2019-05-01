#include <stdio.h>
#include <stdlib.h>
#include <vector>

/*-------------------------------------------------------------------------*/
typedef struct vertex{
    int height;
    int excess;
    std::vector<int> adjs;
}Vertex;

typedef struct edge{
    int capacity;
    int id;
    int flow; 
}Edge;


/*-------------------------------------------------------------------------*/
int readInput();


int main(){
    readInput();
}


int readInput() {
    int i;
    int numberSuppliers, numberStations, numberConnections;
    int productionOfSupplier, capacityOfStation;
    int originConnection, destinationConnection, capacityConnection;

    if(scanf("%d %d %d", &numberSuppliers, &numberStations, &numberConnections) != 3) {
        return -1;
    }

    for(i = 0; i < numberSuppliers; i++) {
        if(scanf("%d ", &productionOfSupplier) != 1) {
            return -1;
        }
    }

    for(i = 0; i < numberStations; i++) {
        if(scanf("%d ", &capacityOfStation) != 1) {
            return -1;
        }
    }

    for(i = 0; i < numberConnections; i++) {
        if(scanf("%d %d %d", &originConnection, &destinationConnection,
        &capacityConnection) != 1) {
            return -1;
        }
    }
    return 0;
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