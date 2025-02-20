cmake_minimum_required(VERSION 3.29)
project(tp2_reseau_ip_CerberusX21)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
        ContratException.cpp
        Graphe.hpp
        Reseau.cpp
        Routeur.cpp
        main.cpp
)

set(HEADERS
        ContratException.h
        Graphe.h
        Reseau.h
        Routeur.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tp2_reseau_ip_CerberusX21 ${SOURCES})

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.12.x
)

FetchContent_MakeAvailable(googletest)

enable_testing()


add_subdirectory(tests)