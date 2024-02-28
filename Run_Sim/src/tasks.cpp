// Created by Matt Nicol on 27th Feb 24

#include "data.hpp"
#include "tasks.hpp"
#include <regex>
#include <sstream>
#include <fstream>
#include <iostream>


tasks::tasks(std::string filename)
    : default_run_list("")
{

    default_run_list = std::getenv("SIM_RUNLIST") ? std::string(std::getenv("SIM_RUNLIST")) + "/" : "";


    std::ifstream run_list(filename);
    if (!run_list.is_open()) {
        abort();
    }

    std::regex regex_comment(R"(\s*#.*|\s*)");
    std::regex regex_data_block(R"(\s*DATA)");
    std::regex regex_data_block_item(R"(\s*(\d+)\s*(\S+)\s*(\S+)\s*(\"(.*)\"|))");
    std::regex regex_end(R"(\s*END)");
    std::smatch m;


    for (std::string line; std::getline(run_list, line);) {

        if (std::regex_match(line, regex_data_block)) {
            for (std::string line; std::getline(run_list, line);) {

                if (std::regex_match(line, regex_comment))
                    continue;
                if (std::regex_match(line, regex_end))
                    break;
                if (std::regex_match(line, m, regex_data_block_item)) {
                    data_entry d;
                    d.run_number = std::atoi(std::string(m[1]).c_str());
                    d.momentum = std::atoi(std::string(m[2]).c_str());
                    d.target = m[3];
                    if (data_map.find(d.run_number) == data_map.end()) {
                        data_map[d.run_number] = d;
                    }
                    else {
                        std::cout << "ERROR: redeclaration of run " << d.run_number << "\n";
                        abort();
                    }
                }
                else {
                    std::cout << "ERROR: syntax error.\n";
                    abort();


                }
            }
        }
    }
    run_list.close();
    std::cout << " done\n";
}

