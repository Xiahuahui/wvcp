#pragma once

#include "../representation/Solution.h"

/**
 * @brief Local search grenade from ILSTS
 *
 * From :
 * Nogueira, B., Tavares, E., Maciel, P., 2021.
 * Iterated local search with tabu search for the weighted vertex coloring problem.
 * Computers & Operations Research 125, 105087.
 * https://doi.org/10.1016/j.cor.2020.105087
 *
 * @param solution solution to use, the solution will be modified
 * @param verbose True if print csv line each time new best scores is found
 */
void ilsts(Solution &solution, const bool verbose = false);

/**
 * @brief Step 1,2 and 3 of ILSTS algorithm
 *
 * @param solution solution
 * @param iter number of iterations for tabu list
 * @return true modification of the solution
 * @return false no modification
 */
bool M_1_2_3(Solution &solution, const long iter);

/**
 * @brief Step 3 of ILSTS algorithm
 *
 * @param solution solution
 * @param iter number of iterations for tabu list
 * @param min_cost minimal cost to do a grenade operator
 * @param min_vertex vertex to move
 * @param min_c color to use for the vertex
 * @return true modification of the solution
 * @return false no modification
 */
bool M_3(Solution &solution,
         const long iter,
         const int min_cost,
         const int min_vertex,
         const int min_c);

/**
 * @brief Step 4 of ILSTS algorithm
 *
 * @param solution solution
 * @param iter number of iterations for tabu list
 * @param free_vertices shuffled free vertices
 * @return true modification of the solution
 * @return false no modification
 */
bool M_4(Solution &solution, const long iter, const std::vector<int> &free_vertices);

/**
 * @brief Step 5 of ILSTS algorithm
 *
 * @param solution solution
 * @param iter number of iterations for tabu list
 * @param free_vertices shuffled free vertices
 * @return true modification of the solution
 * @return false no modification
 */
bool M_5(Solution &solution, const long iter, const std::vector<int> &free_vertices);

/**
 * @brief Step 6 of ILSTS algorithm
 *
 * @param solution solution
 * @param iter number of iterations for tabu list
 * @return true modification of the solution
 * @return false no modification
 */
bool M_6(Solution &solution, const long iter);
