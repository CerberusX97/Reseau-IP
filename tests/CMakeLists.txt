add_executable(
        TesteurReseau
        TesteurReseau.cpp
)


target_sources(TesteurReseau PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../ContratException.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Reseau.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Routeur.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../traceFC.txt
)

target_include_directories(TesteurReseau PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(
        TesteurReseau
        gtest_main
        gtest
        pthread
)

include(GoogleTest)

gtest_discover_tests(TesteurReseau)
# Enable testing
enable_testing()
