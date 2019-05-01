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