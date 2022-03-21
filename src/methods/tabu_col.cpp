#include "tabu_col.h"

#include <algorithm>
#include <assert.h>

#include "../utils/random_generator.h"
#include "../utils/utils.h"

void tabu_col(Solution &best_solution, const bool verbose) {

    const auto max_time{std::chrono::high_resolution_clock::now() +
                        std::chrono::seconds(Parameters::p->max_time_local_search)};

    int64_t best_time{0};

    if (best_solution.nb_non_empty_colors() < Solution::best_nb_colors) {
        Solution::best_nb_colors = static_cast<int>(best_solution.nb_non_empty_colors());
    }
    std::uniform_int_distribution<int> distribution(0, 10);
    Solution working_solution(best_solution);
    int turn_main{0};
    while (not Parameters::p->time_limit_reached_sub_method(max_time) and
           turn_main < Parameters::p->nb_iter_local_search) {

        ++turn_main;

        if (working_solution.nb_non_empty_colors() == Solution::best_nb_colors and
            working_solution.nb_conflicts() == 0) {
            working_solution.reduce_nb_colors(Solution::best_nb_colors - 1);
        } else {
            working_solution.reduce_nb_colors(
                static_cast<int>(working_solution.nb_non_empty_colors()) - 1);
        }

        int best_nb_conflicts{working_solution.nb_conflicts()};

        std::vector<std::vector<int>> tabu_matrix(
            Graph::g->nb_vertices, std::vector<int>(working_solution.nb_colors(), 0));
        long turn{0};
        while (not Parameters::p->time_limit_reached_sub_method(max_time) and
               best_nb_conflicts != 0) {
            ++turn;
            std::vector<std::pair<int, int>> best_actions;
            int best_evaluation{std::numeric_limits<int>::max()};
            for (const auto &vertex : working_solution.free_vertices()) {
                if (working_solution.has_conflicts(vertex)) {
                    for (const auto &color : working_solution.non_empty_colors()) {
                        if (color == working_solution.color(vertex)) {
                            continue;
                        }
                        const int test_conflict{
                            working_solution.delta_conflicts(vertex, color)};
                        if ((test_conflict < best_evaluation and
                             tabu_matrix[vertex][color] <= turn) or
                            (working_solution.nb_conflicts() + test_conflict == 0)) {
                            best_actions.clear();
                            best_actions.emplace_back(
                                std::pair<int, int>({vertex, color}));
                            best_evaluation = test_conflict;
                        } else if ((test_conflict == best_evaluation and
                                    tabu_matrix[vertex][color] <= turn) or
                                   (working_solution.nb_conflicts() + test_conflict ==
                                    0)) {
                            best_actions.emplace_back(
                                std::pair<int, int>({vertex, color}));
                        }
                    }
                }
            }
            if (not best_actions.empty()) {
                const auto chosen_one{rd::choice(best_actions)};
                const int old_color{working_solution.delete_from_color(chosen_one.first)};
                working_solution.add_to_color(chosen_one.first, chosen_one.second);
                tabu_matrix[chosen_one.first][old_color] =
                    static_cast<int>(turn) + distribution(rd::generator) +
                    static_cast<int>(working_solution.nb_conflicts() * 0.6);
                if (working_solution.nb_conflicts() < best_nb_conflicts) {
                    best_nb_conflicts = working_solution.nb_conflicts();
                    if (verbose) {
                        print_result_ls(Parameters::p->elapsed_time(
                                            std::chrono::high_resolution_clock::now()),
                                        working_solution,
                                        0);
                    }
                }
            }
        }

        if (working_solution.nb_conflicts() == 0) {
            best_solution = working_solution;
            if (working_solution.nb_non_empty_colors() < Solution::best_nb_colors) {
                Solution::best_nb_colors =
                    static_cast<int>(working_solution.nb_non_empty_colors());
            }
            if (verbose) {
                best_time = Parameters::p->elapsed_time(
                    std::chrono::high_resolution_clock::now());
                print_result_ls(best_time, working_solution, turn);
            }
        }
    }
    if (verbose) {
        print_result_ls(best_time, best_solution, turn_main);
    }
}
