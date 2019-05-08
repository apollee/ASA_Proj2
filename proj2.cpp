#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <limits.h>
#include <queue>
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
int min(int v1, int v2);
int min_edges(Vertex v1);
void printGraph();
void initializeQueue();
Vertex initializeVertex(int height, int flow, int limit);
Edge initializeEdge(int capacity, int id, int flow);
int searchBackEdge(std::vector<Edge> e, int id);
int relabelToFront();
void initializeQueue();

/*----------------Global Vars-----------------*/
std::vector<Vertex> graph;
std::queue<int> queueList;
int numberSuppliers, numberVertexs;
int listRelabel;

int main(){
    readInput();
    printGraph();
    relabelToFront(); 
    printGraph();
    printf("FLUXO: %d\n", graph[0].excess_flow);
    return 0;
}


int readInput() {
    int i;
    int flow = 0;
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

    Vertex source = initializeVertex(numberVertexs, 0 , INT_MAX);
    graph.push_back(source);

  
    for(i = 0; i < numberSuppliers; i++) {
        if(scanf("%d ", &productionOfSupplier) != 1) {
            return -1;
        }else{
            Vertex supplier = initializeVertex(0, 0, productionOfSupplier);
            graph.push_back(supplier);
            Edge s_v = initializeEdge(INT_MAX, 0, 0);
            graph[i + 2].adjs.push_back(s_v);
            Edge back = initializeEdge(0, i + 2, 0);
            graph[0].adjs.push_back(back);
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
            if(destinationConnection == 1){
                flow += graph[originConnection].limit;
                graph[originConnection].excess_flow = min(graph[originConnection].limit, capacityConnection);
                Edge connection = initializeEdge(capacityConnection, originConnection, min(graph[originConnection].limit, capacityConnection));
                graph[destinationConnection].adjs.push_back(connection);
                Edge back = initializeEdge(0, destinationConnection, - min(graph[originConnection].limit, capacityConnection));
                graph[originConnection].adjs.push_back(back);
            }
            else{
                Edge connection = initializeEdge(capacityConnection, originConnection, 0);
                graph[destinationConnection].adjs.push_back(connection);
                Edge back = initializeEdge(0, destinationConnection, 0);
                graph[originConnection].adjs.push_back(back);
            }
        }
    }
    graph[1].excess_flow = -flow;
    
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

void Push(Vertex &v1, Vertex &v2, Edge &edge, int index){
    int current_flow;
    int limit;
    if(v2.excess_flow == 0 && edge.id != 0){
        queueList.push(edge.id);
    }
    current_flow = min(v1.excess_flow, edge.capacity - edge.flow);
    limit = min(current_flow, v2.limit - v2.excess_flow);
    edge.flow += limit;
    v2.adjs[index].flow -= limit;
    v1.excess_flow -= limit;
    v2.excess_flow += limit;
}

void Relabel(Vertex &v1){
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
        if((graph[adj.id].limit - graph[adj.id].excess_flow) > 0 && (adj.capacity - adj.flow) > 0)
            min = min > graph[adj.id].height ? graph[adj.id].height : min;
    }
    return min;
} 

void discharge(Vertex &v1, int id){
    std::vector<Edge>::iterator it = v1.adjs.begin();
    printf("%d", id);
    while(v1.excess_flow > 0){
        if(it == v1.adjs.end()){
            Relabel(v1);
            it = v1.adjs.begin();
        }
        else if(((*it).capacity - (*it).flow) > 0 && v1.height == graph[(*it).id].height + 1 && (graph[(*it).id].limit - graph[(*it).id].excess_flow ) > 0){
            int e = searchBackEdge(graph[(*it).id].adjs, id);
            Push(v1, graph[(*it).id], *it, e);
        }
        else{
            it++;
        }
    }
    printf("adeus\n");
}

int searchBackEdge(std::vector<Edge> e, int id){
    int i = 0;
    for(auto adj : e){
        if(adj.id == id){
            return i;
        }
        i++;
    }
    return -1;
}

int relabelToFront(){
    int flow = 0;
    initializeQueue();
    while(!queueList.empty()){
        discharge(graph[queueList.front()], queueList.front());
        queueList.pop();
    }
    return flow;
}

void initializeQueue(){
    int i;
    for(i = 2; i < numberVertexs; i++){
        if(graph[i].excess_flow > 0){
            queueList.push(i);
        } 
    }
}