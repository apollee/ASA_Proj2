#include <stdio.h>
#include <stdlib.h>
#include <vector>

/*-------------------------------------------------------------------------*/

struct Vertex {
    int height;
    int ex_flow;
};

struct Edge {
    int flow;
    int capacity;
    int id_vertex;
};

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