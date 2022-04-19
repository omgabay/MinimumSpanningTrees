#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Kruskal.h"
using namespace std;
unsigned int Vertex::vertex_number = 0;
int main(int argc, char *argv[]) {

    Graph &g = Graph::MakeEmptyGraph(4);
    bool logging = true;
    g.AddEdge(1,2,10);
    g.AddEdge(2,3,7);
    g.AddEdge(3,4,5);
    g.AddEdge(4,2,-2);
    g.AddEdge(3,1,-1);
    g.printMe();
    Kruskal(g,logging);



    // Reading input-file and running Kruskal

    std::cout << std::endl <<"finding MST from input file.." << std::endl;
    Graph *g2;
    ifstream myFile;
    myFile.open(argv[1]);
    if(myFile.is_open()){
        string line;
        getline(myFile,line);
        std::stringstream ss(line);
        int graph_size, edges_count;
        ss >> graph_size;
        g2 = new Graph(graph_size);
        getline(myFile,line);
        ss = stringstream(line);
        ss >> edges_count;

        while(edges_count>0){
            getline(myFile,line);
            ss = stringstream(line);

            int src,dst,w;
            ss >> src >> dst >> w;
            g2->AddEdge(src,dst,w);
            edges_count--;
        }
        g2->printMe();
        Kruskal(*g2);
        int edgesRemoved = 0;
        while(getline(myFile,line)){
            ss = stringstream(line);
            int u,v;
            ss >> u >> v;
            if(logging){
                cout << "Removing the edge (" << u << "," << v << ")" << std::endl;
            }
            g2->RemoveEdge(u,v);
            edgesRemoved++;
        }

        std::cout << std::endl <<"finding MST after removing "<< edgesRemoved <<" edges.." << std::endl;
        Kruskal(*g2);



    }else{
        std::cerr << "Error opening file " << argv[1] << "!" <<std::endl;
        exit(1);
    }

    myFile.close();
    delete g2;
    return 0;
}





