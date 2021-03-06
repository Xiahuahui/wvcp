#pragma once

#include <memory>
#include <string>
#include <vector>

/**
 * @brief Struct Graph use information from .col and .col.w files to create an instance of
 * a graph
 *
 */
struct Graph {

    /** @brief Graph used for the search, refer as Graph::g*/
    static std::unique_ptr<const Graph> g;

    /** @brief Name of the instance*/
    const std::string name;

    /** @brief Number of vertices in the graph*/
    const int nb_vertices;

    /** @brief Number of edges in the graph*/
    const int nb_edges;

    /** @brief List of the edges in the graph*/
    const std::vector<std::pair<int, int>> edges_list;

    /** @brief Adjacency matrix, true if there is an edge between vertex i and vertex j*/
    const std::vector<std::vector<bool>> adjacency_matrix;

    /** @brief For each vertex, the list of its neighbors*/
    const std::vector<std::vector<int>> neighborhood;

    /** @brief For each vertex, its degree*/
    const std::vector<int> degrees;

    /** @brief For each vertex, its weight*/
    const std::vector<int> weights;

    /** @brief Set the Graph for the search*/
    static void init_graph(std::unique_ptr<const Graph> graph_);

    /**
     * @brief Construct a new Graph
     *
     * @param name_ Name of the instance
     * @param nb_vertices_ Number of vertices in the graph
     * @param nb_edges_ Number of edges in the graph
     * @param edges_list_ List of the edges in the graph
     * @param adjacency_matrix_ Adjacency matrix, true if there is an edge between vertex
     * i and vertex j
     * @param neighborhood_ For each vertex, the list of its neighbors
     * @param degrees_ For each vertex, its degree
     * @param weights_ For each vertex, its weight
     */
    explicit Graph(const std::string &name_,
                   const int &nb_vertices_,
                   const int &nb_edges_,
                   const std::vector<std::pair<int, int>> &edges_list_,
                   const std::vector<std::vector<bool>> &adjacency_matrix_,
                   const std::vector<std::vector<int>> &neighborhood_,
                   const std::vector<int> &degrees_,
                   const std::vector<int> &weights_);

    /**
     * @brief Construct a copy of a Graph object deleted
     *
     * @param other the graph to not copy
     */
    Graph(const Graph &other) = delete;
};

/**
 * Load graph previously reduced from a _r.col file from the
 * instances/wvcp_reduced/ directory
 *
 * @param instance_name : name of the instance (without the .col extension)
 * @param wvcp_problem : true if wvcp problem, false if gcp problem
 * @return : shared ptr to the Graph
 */
const std::unique_ptr<const Graph> load_graph(int** info,int** edges_list_info,int** weight_list_info,const std::string &instance_name,
                                              const bool wvcp_problem);
