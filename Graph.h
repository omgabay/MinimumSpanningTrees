//
// Created by omerg on 4/19/2022.
//

#ifndef SPANNING_TREES_GRAPH_H
#define SPANNING_TREES_GRAPH_H
#include <cstdlib>
#include <iostream>
struct Edge{
    unsigned int src;   // id of src vertex
    unsigned int dst;   // id of dst vertex
    int weight; // the weight of the edge
    Edge *next;
    Edge(unsigned int src, unsigned int dst, int w):src(src),dst(dst),weight(w){next = nullptr;}
    Edge():src(0),dst(0),weight(0){next= nullptr;}
};
struct EdgeList{
    unsigned int src;
    Edge *head, *tail;
    size_t size = 0;
    EdgeList(unsigned int v){
        src = v;
        head = tail =nullptr;
        size = 0;
    }
    void addEdge(unsigned int u, unsigned int v, int w){
        if(this->src != u)
            return;

        Edge *e = new Edge(u,v,w);
        if(size == 0)
            head = tail = e;
        else {tail->next = e; tail = tail->next;}
        size++;
    }

    bool removeEdge(unsigned int u, unsigned int v){
        Edge *prev = nullptr;
        Edge *cur = head;
        while(cur){
            if(cur->src==u && cur->dst==v){
                size--;
                if(size == 0)
                    head = tail = nullptr;
                else if(prev == nullptr){
                    head = cur->next;    // removing the head
                }
                else if(cur->next == nullptr){
                    tail = prev;        // removing the tail
                    prev->next = nullptr;
                }else{
                    prev = cur->next;
                }
                cur->next = nullptr;
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }
    bool isAdjacent(unsigned int v){
        Edge *cur = head;
        while(cur){
            if(cur->dst == v)
                return true;
            cur = cur->next;
        }
        return false;
    }
};

struct Vertex{
    unsigned int in_degree;
    unsigned int out_degree;
    EdgeList *edges;
    static unsigned int vertex_number;
    Vertex(){
        edges = new EdgeList(vertex_number++);
        in_degree=out_degree = 0;
    }
    Vertex(int i){
        edges = new EdgeList(i);
        in_degree=out_degree = 0;
    }
    static void set_vertex_number(unsigned int n){vertex_number=n;}
   // ~Vertex(){delete edges;}

};

class Graph {
private:
    Vertex *adjList;

public:
    int n;
    int m;
    Graph(int n);
    static Graph &MakeEmptyGraph(size_t n);
    void AddEdge(unsigned int u, unsigned int v, int weight);
    bool RemoveEdge(unsigned int u, unsigned int v);
    bool IsAdjacent(unsigned int u, unsigned int v);
    Edge *getEdgeList();
    void printMe();
    ~Graph();

};


#endif //SPANNING_TREES_GRAPH_H
