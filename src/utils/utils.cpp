#include "utils.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "../test.h"

std::vector<std::string> split_string(std::string to_split,
                                      const std::string &delimiter) {
    size_t pos = 0;
    std::vector<std::string> elements;
    while ((pos = to_split.find(delimiter)) != std::string::npos) {
        elements.emplace_back(to_split.substr(0, pos));
        to_split.erase(0, pos + delimiter.length());
    }
    elements.emplace_back(to_split);
    return elements;
}

std::string get_date_str() {
    std::time_t t = std::time(nullptr);
    std::stringstream tm;
    tm << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    return tm.str();
}

void print_result_ls(const int64_t &best_time,
                     const Solution &solution,
                     const long &turn) {
//    fmt::print(Parameters::p->output,
//               "{},{},{},{},{},{},{}\n",
//               get_date_str(),
//               Parameters::p->local_search_str,
//               Graph::g->name,
//               Parameters::p->line_csv,
//               turn,
//               best_time,
//               solution.line_csv());
//     solution.line_csv();
     for (int k=0;k<solution.colors().size();k++){
         result_colors.push_back(solution.colors()[k]);
     }

//     std :: cout << solution.score_wvcp() << std::endl;
}