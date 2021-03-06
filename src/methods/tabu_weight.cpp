#include "tabu_weight.h"

#include "../utils/random_generator.h"
#include "../utils/utils.h"

void tabu_weight(Solution &best_solution, const bool verbose) {

    auto max_time{std::chrono::high_resolution_clock::now() +
                  std::chrono::seconds(Parameters::p->max_time_local_search)};

    int64_t best_time{0};
    std::vector<long> tabu_list(Graph::g->nb_vertices, 0);
    Solution solution = best_solution;
    long turn{0};
    while (not Parameters::p->time_limit_reached_sub_method(max_time) and
           turn < Parameters::p->nb_iter_local_search and
           best_solution.score_wvcp() != Parameters::p->target) {
        ++turn;
        std::vector<Action> best_actions;
        int best_evaluation{std::numeric_limits<int>::max()};
        auto possible_colors{solution.non_empty_colors()};
        possible_colors.push_back(-1);
        for (const auto &vertex : solution.free_vertices()) {
            for (const int &color : possible_colors) {
                if (color == solution.color(vertex) or
                    (color != -1 and solution.conflicts_colors(color, vertex) != 0)) {
                    continue;
                }
                const int test_score{solution.score_wvcp() +
                                     solution.delta_wvcp_score(vertex, color)};
                if ((test_score < best_evaluation and tabu_list[vertex] <= turn) or
                    (test_score < best_solution.score_wvcp())) {
                    best_actions.clear();
                    best_actions.emplace_back(Action{vertex, color, test_score});
                    best_evaluation = test_score;
                } else if (test_score == best_evaluation and
                           (tabu_list[vertex] <= turn or
                            test_score < best_solution.score_wvcp())) {
                    best_actions.emplace_back(Action{vertex, color, test_score});
                }
            }
        }
        if (not best_actions.empty()) {
            const Action chosen_one{rd::choice(best_actions)};
            solution.delete_from_color(chosen_one.vertex);
            solution.add_to_color(chosen_one.vertex, chosen_one.color);
            tabu_list[chosen_one.vertex] = turn + solution.nb_non_empty_colors();
            if (solution.score_wvcp() < best_solution.score_wvcp()) {
                best_solution = solution;
                if (verbose) {
                    best_time = Parameters::p->elapsed_time(
                        std::chrono::high_resolution_clock::now());
                    print_result_ls(best_time, best_solution, turn);
                }
            }
        }
    }
    if (verbose) {
        print_result_ls(best_time, best_solution, turn);
    }
}
