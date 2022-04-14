#include "Graph.h"

#include <fstream>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
//#include <fmt/printf.h>
#pragma GCC diagnostic pop

std::unique_ptr<const Graph> Graph::g = nullptr;

void Graph::init_graph(std::unique_ptr<const Graph> graph_) {
    Graph::g = std::move(graph_);
}

Graph::Graph(const std::string &name_,
             const int &nb_vertices_,
             const int &nb_edges_,
             const std::vector<std::pair<int, int>> &edges_list_,
             const std::vector<std::vector<bool>> &adjacency_matrix_,
             const std::vector<std::vector<int>> &neighborhood_,
             const std::vector<int> &degrees_,
             const std::vector<int> &weights_)
    : name(name_),
      nb_vertices(nb_vertices_),
      nb_edges(nb_edges_),
      edges_list(edges_list_),
      adjacency_matrix(adjacency_matrix_),
      neighborhood(neighborhood_),
      degrees(degrees_),
      weights(weights_) {
}

const std::unique_ptr<const Graph> load_graph(int** info,int** edges_list_info,int** weight_list_info,const std::string &instance_name,
                                              const bool wvcp_problem) {

    std::cout << "wvcp_problem3" << wvcp_problem << std::endl;

//    for(int i=0; i<2; i=i+1)
//    {
//        std::cout << "n1"<< m[i] << std::endl;
//        std::cout <<"n2" << m[i+1] << std::endl;
//    }
//     load the edges and vertices of the graph
//    std::ifstream file;
//    if (wvcp_problem) {
//        file.open("./gc_wvcp_mcts/instances/wvcp_reduced/" + instance_name + ".col");
//    } else {
//        file.open("./gc_wvcp_mcts/instances/wvcp_original/" + instance_name + ".col");
//    }
//    if (!file) {
////        fmt::print(stderr,
////                   "Didn't find {} in ../instances/wvcp_reduced/ or wvcp_original (if "
////                   "problem == gcp)\n"
////                   "Did you run \n\n"
////                   "git submodule init\n"
////                   "git submodule update\n\n"
////                   "before executing the program ?(import instances)\n"
////                   "Otherwise check that you are in the build "
////                   "directory before executing the program\n",
////                   instance_name);
//        //TODO
//        std::cout<<"Graph load graph" <<std::endl;
//        exit(1);
//    }
    int nb_vertices{0}, nb_edges{0}, n1{0}, n2{0};
    int* m = (int*)info;
    std::cout << "节点数"<< m[0] << std::endl;
    std::cout <<"边数" << m[1] << std::endl;
    nb_vertices = m[0];
    nb_edges = m[1];

    //初始化边向量
    std::vector<std::pair<int, int>> edges_list;
    edges_list.reserve(nb_edges);   //申请nb_edge空间

    int* m2 = (int*)edges_list_info;

    for(int k=0; k<(m[1]*2); k=k+2){
        std::cout << "起始节点" <<m2[k] << "终止节点"<<m2[k+1] << std::endl;
        n1 = m2[k];
        n2 = m2[k+1];
        edges_list.emplace_back(--n1, --n2);
    }
//    std::string first;
//    file >> first;
//    while (!file.eof()) {
//        if (first == "e") {
//            file >> n1 >> n2;
//            std::cout << "n1: " << n1 << "n2: "<<n2<<std::endl;
//            edges_list.emplace_back(--n1, --n2);
//        } else if (first == "p") {
//            file >> first >> nb_vertices >> nb_edges;
//            std::cout << "nb_vertices"<< nb_vertices << "nb_edges" << nb_edges << std::endl;
//            edges_list.reserve(nb_edges);
//        } else {
//            getline(file, first);
//        }
//        file >> first;
//    }
//    file.close();

    std::vector<int> weights(nb_vertices, 1);

    int* m3 = (int*)weight_list_info;
    for(int k=0; k<nb_vertices; k++){
        std::cout << "第"<< k <<"节点" <<m3[k] <<"权重为： " << m3[k] << std::endl;
        weights[k] = m3[k];
    }


//    if (wvcp_problem) {
//        // load the weights of the vertices
//        std::ifstream w_file("./gc_wvcp_mcts/instances/wvcp_reduced/" + instance_name + ".col.w");
//        if (!w_file) {
////            fmt::print(stderr,
////                       "Didn't find weights for {} in ../instances/wvcp_reduced/\n",
////                       instance_name);
//            std::cout<<"load graph2" << std::endl;
//            exit(1);
//        }
//        size_t i(0);
//        while (!w_file.eof()) {
//            w_file >> weights[i];
//            std::cout << "weight[i]" << weights[i];
//            ++i;
//        }
//        w_file.close();
//    }
    std::cout<<"结束2"<< std::endl;
    std::cout<<"节点数"<< nb_vertices << std::endl;
    std::vector<std::vector<bool>> adjacency_matrix(
        nb_vertices, std::vector<bool>(nb_vertices, false));
    std::vector<std::vector<int>> neighborhood(nb_vertices, std::vector<int>(0));
    std::vector<int> degrees(nb_vertices, 0);
    // Init adjacency matrix and neighborhood of the vertices
    for (auto p : edges_list) {
        std::cout<<"p.first" <<p.first <<"p.second"<<p.second<<std::endl;
        if (not adjacency_matrix[p.first][p.second]) {
            adjacency_matrix[p.first][p.second] = true;
            adjacency_matrix[p.second][p.first] = true;
            neighborhood[p.first].push_back(p.second);
            neighborhood[p.second].push_back(p.first);
            ++nb_edges;
        }
    }
    std::cout<<"结束3"<< std::endl;

    // Init degrees_ of the vertices
    for (int vertex{0}; vertex < nb_vertices; ++vertex) {
        degrees[vertex] = static_cast<int>(neighborhood[vertex].size());
    }
    // Uncomment to check if the vertices are well sorted
     for(int vertex(0); vertex < nb_vertices-1; ++vertex){

         if(weights[vertex] < weights[vertex + 1] or (
             weights[vertex] == weights[vertex + 1] and
             degrees[vertex] < degrees[vertex + 1]
         )){
             std::cout <<"error v "<<vertex << "d "<<degrees[vertex] <<"before v "<<vertex<<"w "<<weights[vertex]<<"d "<< degrees[vertex] << "\nVertices must be sorted\n";

         }
     }
     //输出图的邻接矩阵
     std::cout << "<<<<<<<<<<<<测试节点数<<<<<<<<<<<<<<"<<std::endl;
     std::cout<<"nb_edges"<<nb_vertices<<std::endl;
     std::cout << "<<<<<<<<<<<<测试边数<<<<<<<<<<<<<<"<<std::endl;
     std::cout<<"nb_edges"<<nb_edges<<std::endl;
     std::cout << "<<<<<<<<<<<<测试边集<<<<<<<<<<<<<<"<<std::endl;
     for(int i=0;i<edges_list.size();i++){
         std::cout << edges_list[i].first << " " << edges_list[i].second << std::endl;
     }
     std::cout << "<<<<<<<<<<<<测试矩阵<<<<<<<<<<<<<<"<<std::endl;
     for(int i=0;i<nb_vertices;i++){
         for(int j=0;j<nb_vertices;j++){
             std::cout<<adjacency_matrix[i][j]<<" ";
         }
         std::cout << std::endl;
     }
     std::cout << "<<<<<<<<<<<<测试邻居节点<<<<<<<<<<<<<<"<<std::endl;
     for(int i=0;i<nb_vertices;i++){
         std::cout<< "节点" << i <<"的邻居节点 :";
         for(int j=0;j<neighborhood[i].size();j++){
             std::cout << neighborhood[i][j];

         }
         std::cout << std::endl;
     }
     std::cout << "<<<<<<<<<<<<测试节点度数<<<<<<<<<<<<<<"<<std::endl;
     for(int i=0;i<degrees.size();i++){
         std::cout<< "节点" << i <<"的度数 : " << degrees[i];
         std::cout << std::endl;
     }
     std::cout << "<<<<<<<<<<<<测试节点权重<<<<<<<<<<<<<<"<<std::endl;
     for(int i=0;i<weights.size();i++){
         std::cout<< "节点" << i <<"的权重 : " << weights[i];
         std::cout << std::endl;
     }


    return std::make_unique<Graph>(instance_name,
                                   nb_vertices,
                                   nb_edges,
                                   edges_list,
                                   adjacency_matrix,
                                   neighborhood,
                                   degrees,
                                   weights);
}
