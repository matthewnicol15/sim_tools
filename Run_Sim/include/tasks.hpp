//  Created by Steffen Strauch on 9/7/22.
//

#ifndef tasks_hpp
#define tasks_hpp

#include <map>
#include <stdio.h>
#include <string>
#include <vector>


class tasks {
public:

    struct data_entry
    {
        int run_number;
        std::string file_name;
        int momentum;
        std::string target;

    };
    tasks(std::string filename);

    std::map<int, data_entry> data_map;

    std::string default_run_list;
};

#endif /* tasks_hpp */
