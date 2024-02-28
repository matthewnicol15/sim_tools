# Check if cmake has the required version
CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)

# Set project name
PROJECT(Run_Sim)

find_package(ROOT REQUIRED)
find_package(Boost 1.47 COMPONENTS system program_options program_options REQUIRED)
include(${ROOT_USE_FILE} ${Boost_INCLUDE_DIRS})

SET(INCLUDES ${ROOT_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${CLHEP_INCLUDE_DIRS} ${GSL_INCLUDE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES(${INCLUDES})

SET(TASKLISTS
    ${CMAKE_SOURCE_DIR}/RunList.txt
)
SOURCE_GROUP("Runlists" FILES ${RUNLISTS})

add_library(Run_Sim_lib
    # src/runcheck.cpp include/runcheck.hpp
    src/tasks.cpp include/tasks.hpp
    # src/data.cpp include/data.hpp
)

TARGET_LINK_LIBRARIES(Run_Sim_lib "-L${ROOT_LIBRARY_DIR}"  dl ${ROOT_LIBRARIES} MathMore Minuit2 Foam ${GSL_LIBRARIES} )

add_executable(Run_Sim run_sim.cpp ${TASKLISTS})

TARGET_LINK_LIBRARIES(Run_Sim Run_Sim_lib ${Boost_LIBRARIES} "-L${ROOT_LIBRARY_DIR}"  dl ${ROOT_LIBRARIES} ${GSL_LIBRARIES})
