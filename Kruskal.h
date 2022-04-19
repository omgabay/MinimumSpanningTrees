//
// Created by omerg on 4/19/2022.
//
#ifndef SPANNING_TREES_KRUSKAL_H
#define SPANNING_TREES_KRUSKAL_H
#include "unionFind.h"
#include "Graph.h"
#include <cstddef>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <iostream>


int Partition(Edge *edges, size_t size);
void randomizedQuickSort(Edge *edges, size_t size);
std::random_device rd;
std::default_random_engine eng(rd());


/*
 * Input - Undirected weighted Graph G
 * The algorithm is implemented using the Disjoint-Sets ADT
 * Output - Returns Minimum Spanning Tree or Spanning Forest(in case the graph is not connected)
 */
void Kruskal(Graph &g, bool logging=false){
    Edge *edges = g.getEdgeList();
    if(logging){
        std::cout << "Before sorting the edges array" << std::endl;
        for(int i=0; i<g.m; i++){
            Edge e = edges[i];
            std::cout << "(" << e.src << "," << e.dst << ") weight=" <<e.weight <<std::endl;
        }
    }
    std::cout << "-- Sorting -- " << std::endl;
    int m = g.m; // number of edges in the graph
    randomizedQuickSort(edges, m);
    if(logging){
        for(int i=0; i<g.m; i++){
            Edge e = edges[i];
            std::cout << "(" << e.src << "," << e.dst << ") weight=" <<e.weight << " sorted!"<<std::endl;
        }
        std::cout << "-- Sorting Done -- " << std::endl;
    }

    unionFind uf = unionFind(g.n);
    int total_weight = 0;
    for(int i=0; i<m && !uf.isConnected(); i++){
        Edge &e = edges[i];
        if(uf.Union(e.src-1,e.dst-1)){
            std::cout << "(" << e.src << "," << e.dst << ") weight=" <<e.weight << " was added to MST!"<<std::endl;
            total_weight += e.weight;
        }
    }

    if(!uf.isConnected()){
        std::cout << "No MST" << std::endl;
        std::cout << "Graph has " << uf.getNumberOfComponents() << std::endl;
        std::cout << "Kruskal-MSForest total-weight " << total_weight << std::endl;
    }
    std::cout << "Kruskal-MST total-weight " << total_weight << std::endl;

    delete [] edges;
}


void randomizedQuickSort(Edge *edges, size_t size){
    if(size <= 1)
        return;
    std::uniform_int_distribution<int> distr(0, size-1);
    int pivot = distr(eng);
    Edge tmp = edges[0];
    edges[0] = edges[pivot];
    edges[pivot] = tmp;
    pivot = Partition(edges, size);
    randomizedQuickSort(edges,pivot);
    randomizedQuickSort(&edges[pivot+1],size-pivot-1);
}

/*
 * Partitioning based on pivot element at index 0 - modifies the elements in-place
 * The Method returns the index of pivot after partitioning
 */
int Partition(Edge *edges, size_t size){
    if(size <= 1)
        return 0;
    Edge p = edges[0];
    int w = p.weight;
    int left=0,right=size, pivot=0;
    while(pivot+1<right){
        if(edges[pivot+1].weight<=w){
            // pivot moves to the right -- left partition increases
            edges[pivot] = edges[pivot+1];
            pivot++;
        }else{
            // the element is bigger and copied to the right partition
            right--;
            Edge tmp = edges[right];
            edges[right] = edges[pivot+1];
            edges[pivot+1] = tmp;
        }
    }
    edges[pivot] = p;
    return pivot;
}


#endif //SPANNING_TREES_KRUSKAL_H
