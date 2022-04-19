
#include "Graph.h"

Graph::Graph(int graph_size) {
    n = graph_size;
    m = 0;
    adjList= new Vertex[graph_size+1];
    for(int i=1; i<=n; i++){
        adjList[i] = Vertex(i);
    }


}

void Graph::AddEdge(unsigned int u, unsigned int v, int weight) {
    if(u>n || v>n)
        return;   // out of bounds - vertex does not exist!
    adjList[u].edges->addEdge(u,v,weight);
    adjList[v].edges->addEdge(v,u,weight);
    adjList[u].in_degree = adjList[u].out_degree +=1;
    adjList[v].in_degree = adjList[v].out_degree +=1;
    m++;
}

bool Graph::RemoveEdge(unsigned int u, unsigned int v) {
    if(u>n || v>n)
        return false;   // out of bounds - vertex does not exist!
    bool flag = adjList[u].edges->removeEdge(u,v);
    adjList[v].edges->removeEdge(v,u);
    return flag;
}

bool Graph::IsAdjacent(unsigned int u, unsigned int v) {
    if(u>n || v>n)
        return false;   // out of bounds - vertex does not exist!
    return adjList[u].edges->isAdjacent(v);

}

Graph &Graph::MakeEmptyGraph(size_t n) {
    Vertex::set_vertex_number(0);
    Graph *g = new Graph(n);
    return *g;
}


Edge *Graph::getEdgeList() {
    if(m == 0)
        return nullptr;
    Edge *edgeLst = new Edge[m];
    for(int i=1,count=0; i<=n && count<m; i++){
        Edge *e = adjList[i].edges->head;
        while(e){
            if(e->src < e->dst){
                edgeLst[count] = *e;
                edgeLst[count].next = nullptr;
                count++;
            }
            e = e->next;
        }
    }
    return edgeLst;
}


Graph::~Graph() {
    delete [] adjList;
}

void Graph::printMe() {
    for(int i=1; i<=n; i++){
        std::cout <<i << ":[";
        Edge *e = adjList[i].edges->head;
        while(e){
            std::cout <<"(" << e->dst << ",w=" <<e->weight<<")  ";
            e=e->next;
        }
        std::cout << "]" << std::endl;
    }

}
