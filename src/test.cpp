#include <csignal>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wnull-dereference"
//#include "cxxopts.hpp"
#pragma GCC diagnostic pop

#include "methods/LocalSearch.h"
#include "methods/MCTS.h"
#include "representation/Graph.h"
#include "representation/Method.h"
#include "representation/Parameters.h"
#include "utils/random_generator.h"
#include "test.h"

std::vector<int> result_colors;

/**
 * @brief Signal handler to let the algorithm to finish its last turn
 *
 * @param signum signal number
 */
void signal_handler(int signum);

/**
 * @brief parse the argument for the search
 *
 * @param argc : number of arguments given to main
 * @param argv : list of arguments
 * @return std::shared_ptr<Method>
 */
std::shared_ptr<Method> parse(int** info,int** edges_list,int** weight_list);

//int main( int argc,const char **argv){
//    std::cout << "argc" << argc << argv<<std::endl;
//    return 0;
//}




void test(int** info,int** edges_list,int** weight_list, int** colors){
    std::cout <<"lasted1"<< std::endl;


    // see src/utils/parsing.cpp for default parameters
    // Get the method
//    int* m = (int*)list_data;
//    for(int i=0; i<leng; i++)
//    {
//        std::cout << m[i] << std::endl;
//    }
    //    char test_mid[10000];
    //    std::sprintf(test_mid,
    //                 "\nunknown problem %s\nselect : wvcp, gcp","erer");
    //    std::cout << test_mid;
    //    int argc=0;
    //    const char **argv;
    auto method(parse(info,edges_list,weight_list));
    std::cout << "解析结束"<< std::endl;
    // Set the signal handler to stop the search
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    // Start the search
    method->run();
    Parameters::p->end_search();
    int* m = (int*)colors;
    for (int i=0;i<result_colors.size();i++){
        std::cout <<"result_colors["<<i<<"]" <<result_colors[i]<<std::endl;
        m[i] = result_colors[i] ;
    }
    int result_lenght = result_colors.size();
    for (int i=0;i<result_lenght ;i++){
        std::cout << "before result的长度" << result_colors.size() << std::endl;
        result_colors.pop_back();
    }
    std::cout << "after result的长度" << result_colors.size() << std::endl;
}

void signal_handler(int signum) {
    //    fmt::print(stderr, "\nInterrupt signal ({}) received.\n", signum);
    char test_mid[10000];
    std::sprintf(test_mid,"\nInterrupt signal (%d) received.\n",signum);
    std::cout << test_mid;
    Parameters::p->time_stop = std::chrono::high_resolution_clock::now();
}

std::shared_ptr<Method> parse(int** info,int** edges_list,int** weight_list) {
    std::cout<< "解析开始" << std::endl;
//    // defaults values for parameters are located in representation/Parameter.cpp
//
//    // analyse command line options
//    try {
//        // init cxxopts
//        cxxopts::Options options(argv[0], "Program to launch : mcts, local search\n");
//
//        options.positional_help("[optional args]").show_positional_help();
//
//        options.allow_unrecognised_options().add_options()("h,help", "Print usage");
//        std::cout << "断点2" << std::endl;
//
//        /****************************************************************************
//         *
//         *                      Set defaults values down here
//         *
//         ***************************************************************************/
//
//        options.allow_unrecognised_options().add_options()(
//            "p,problem",
//            "problem (gcp, wvcp)",
//            cxxopts::value<std::string>()->default_value("wvcp"));
//
//        options.allow_unrecognised_options().add_options()(
//            "i,instance",
//            "name of the instance (located in instance/wvcp_reduced/)",
//            cxxopts::value<std::string>()->default_value(
//                //
//                // "p42"
//                "test"
//                //
//                ));
//
//        options.allow_unrecognised_options().add_options()(
//            "m,method",
//            "method (mcts, local_search)",
//            cxxopts::value<std::string>()->default_value(
//                //
//                // "mcts"
//                "local_search"
//                //
//                ));
//
//        options.allow_unrecognised_options().add_options()(
//            "r,rand_seed",
//            "random seed",
//            cxxopts::value<int>()->default_value(
//                //
//                // "1"
//                std::to_string(time(nullptr))
//                //
//                ));
//
//        options.allow_unrecognised_options().add_options()(
//            "T,target",
//            "if the target score is reach, the search is stopped",
//            cxxopts::value<int>()->default_value("9"));
//
//        const std::string time_limit{"8"};
//        options.allow_unrecognised_options().add_options()(
//            "t,time_limit",
//            "maximum execution time in seconds",
//            cxxopts::value<int>()->default_value(time_limit));
//
//        options.allow_unrecognised_options().add_options()(
//            "n,nb_max_iterations",
//            "number of iteration maximum for the mcts",
//            cxxopts::value<long>()->default_value(
//                std::to_string(std::numeric_limits<long>::max())));
//
//        options.allow_unrecognised_options().add_options()(
//            "I,initialization",
//            "Initialization of the solutions (random, constrained, deterministic)",
//            cxxopts::value<std::string>()->default_value(
//                //
//                // "random"
//                // "constrained"
//                "deterministic"
//                //
//                ));
//
//        options.allow_unrecognised_options().add_options()(
//            "N,nb_iter_local_search",
//            "Number max of iteration for local search when call from another method or "
//            "not, can be override by max_time_local_search or o and t time",
//            cxxopts::value<long>()->default_value(
//                //
//                std::to_string(std::numeric_limits<long>::max())
//                // "500"
//                //
//                ));
//
//        options.allow_unrecognised_options().add_options()(
//            "M,max_time_local_search",
//            "Time limit in seconds for local search when call from another method or not "
//            "can by override by nb_iter_local_search or o and t time",
//            cxxopts::value<int>()->default_value(
//                //
//                time_limit
//                // "-1"
//                //
//                ));
//
//        options.allow_unrecognised_options().add_options()(
//            "c,coeff_exploi_explo",
//            "Coefficient exploration vs exploitation for MCTS",
//            cxxopts::value<double>()->default_value("1"));
//
//        options.allow_unrecognised_options().add_options()(
//            "l,local_search",
//            "Local search selected",
//            cxxopts::value<std::string>()->default_value(
//                //
//                // "none"
//                // "hill_climbing"
//                // "tabu_weight"
//                // "tabu_col"
//                // "afisa"
//                // "afisa_original"
//                "redls"
//                //                "ilsts"
//                //
//                ));
//
//        options.allow_unrecognised_options().add_options()(
//            "s,simulation",
//            "Simulation for MCTS (greedy, local_search, depth, fit, depth_fit)",
//            cxxopts::value<std::string>()->default_value(
//                //
//                "greedy"
//                // "local_search"
//                // "fit"
//                // "depth"
//                // "depth_fit"
//                //
//                ));
//
//        options.allow_unrecognised_options().add_options()(
//            "O,O_time",
//            "O to calculate the time of RL : O+P*nb_vertices seconds",
//            cxxopts::value<int>()->default_value("4"));
//
//        options.allow_unrecognised_options().add_options()(
//            "P,P_time",
//            "P to calculate the time of RL : O+P*nb_vertices seconds",
//            cxxopts::value<double>()->default_value("0.01"));
//
//        options.allow_unrecognised_options().add_options()(
//            "o,ouput_to_file",
//            "output file, let empty if output to stdout",
//            cxxopts::value<std::string>()->default_value(""));
//
//        /****************************************************************************
//         *
//         *                      Set defaults values up here
//         *
//         ***************************************************************************/
//
//        const auto result = options.parse(argc, const_cast<char **&>(argv));
//        // help message
//        if (result.count("help")) {
//            // load instance names
//            std::ifstream i_file("../instances/instance_list.txt");
//            if (!i_file) {
//                //                fmt::print(stderr,
//                //                           "Unable to find : ../instances/instance_list.txt\n"
//                //                           "Check if you imported the submodule instance, commands :\n"
//                //                           "\tgit submodule init\n"
//                //                           "\tgit submodule update\n");
//                char test_mid[10000];
//                std::sprintf(test_mid,"Unable to find : ../instances/instance_list.txt\n"
//                                       "Check if you imported the submodule instance, commands :\n"
//                                       "\tgit submodule init\n"
//                                       "\tgit submodule update\n");
//                std::cout << test_mid;
//                exit(1);
//            }
//            std::string tmp;
//            std::vector<std::string> instance_names{};
//            while (!i_file.eof()) {
//                i_file >> tmp;
//                instance_names.push_back(tmp);
//            }
//            i_file.close();
//            // print help
//            //            fmt::print(stdout,
//            //                       "{}\nInstances :\n{}\n",
//            //                       options.help(),
//            //                       fmt::join(instance_names, " "));
//            //TODO 此处的join 有待改变
//            exit(0);
//        }

        // init rand seed
//        const int rand_seed{result["rand_seed"].as<int>()};
//        std::cout << "rand_seed"<< rand_seed << std::stoi(std::to_string(time(nullptr))) << std::endl;
        rd::generator.seed(std::stoi(std::to_string(time(nullptr))));

//        const std::string problem{result["problem"].as<std::string>()};
//        if (problem != "wvcp" and problem != "gcp") {
//            //            fmt::print(stderr,
//            //                       "unknown problem {}\n"
//            //                       "select : wvcp, gcp",
//            //                       problem);
//            char test_mid[10000];
//            std::sprintf(test_mid,
//                         "\nunknown problem %s\nselect : wvcp, gcp","problem");
//            std::cout << test_mid;
//            exit(1);
//        }


        // init graph
        Graph::init_graph(
            load_graph(info,edges_list,weight_list,"test", true));

//        const int max_time_local_search{
//            result["max_time_local_search"].as<int>() == -1
//                ? static_cast<int>(static_cast<double>(Graph::g->nb_vertices) *
//                                   result["P_time"].as<double>()) +
//                      result["O_time"].as<int>()
//                : result["max_time_local_search"].as<int>()};

        // init parameters

//        std::cout << result["nb_max_iterations"].as<long>()<<std::endl;
//        std::cout << <<std::endl;
//        std::cout << max_time_local_search <<std::endl;

        Parameters::init_parameters(
            std::make_unique<Parameters>("wvcp",
                                         "local_search",
                                         9,
                                         std::stoi(std::to_string(time(nullptr))),
                                         9,
                                         std::numeric_limits<long>::max(),
                                         "deterministic",
                                         std::numeric_limits<long>::max(),
                                         4,
                                         "redls",
                                         "greedy",
                                         1));


        // set output file if needed
        const std::string output_file{""};
        if (output_file != "") {
            std::FILE *file = std::fopen((output_file + ".running").c_str(), "w");
            if (!file) {
                //                fmt::print(stderr, "error while trying to access {}\n", output_file);
                // TODO
                exit(1);
            }
            Parameters::p->output = file;
            Parameters::p->output_file = output_file;
        } else {
            Parameters::p->output = stdout;
        }
//                std::cout << result["method"].as<std::string>()<<std::endl;
        const std::string method{"local_search"};

        // create the method
        if (method == "local_search") {
            return std::make_unique<LocalSearch>();
        }
        if (method == "mcts") {
            return std::make_unique<MCTS>();
        }

        //        fmt::print(stderr,
        //                   "error unknown method : {}\n"
        //                   "Possible method : mcts, local_search",
        //                   method);
        //TODO
        exit(1);

//    } catch (const cxxopts::OptionException &e) {
//        //        fmt::print(stderr, "error parsing options: {} \n", e.what());
//        //TODO
//        exit(1);
//    }
}

