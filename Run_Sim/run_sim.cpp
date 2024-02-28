#include <boost/program_options.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <TCanvas.h>
#include <TError.h>
#include <TF1.h>
#include <TFile.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TMarker.h>
#include <TMatrixD.h>
#include <TPaveText.h>
#include <TStyle.h>

#include "data.hpp"
#include "tasks.hpp"



// void test_tasks(std::string tasklist_file)
// {
//     tasks t1(tasklist_file);
//     for (auto& j : jobs) {
//         tl.process(j, detector_element, csv);
//     }

// }


int main(int argc, char** argv)
{
    // rootlogon();
    gErrorIgnoreLevel = kWarning;

    std::string task_fn = std::getenv("SIM_RUNLIST") ? std::string(std::getenv("SIM_RUNLIST")) : "";

    namespace po = boost::program_options;
    try {
        po::options_description desc("Allowed options");
        desc.add_options()("help", "produce help message")
            ("run-file,r", po::value<std::string>(), "input runlist file");

        po::positional_options_description p;
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << "Usage: options_description [options]\n";
            std::cout << desc;
            return EXIT_SUCCESS;
        }

        if (vm.count("run-file")) {
            std::cout << "Run-list file is: "
                << vm["run-file"].as<std::string>() << "\n";
            task_fn = vm["run-file"].as<std::string>();
        }

        tasks t1(task_fn);


    }
    catch (std::exception& e) {
        std::cout << e.what() << "\n";
        return EXIT_FAILURE;
    }
    exit(EXIT_SUCCESS);




}