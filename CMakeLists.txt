cmake_minimum_required (VERSION 3.8)

project ("ClassGenerator")

file(GLOB source_files
            "src/*.hpp"
            "src/*.cpp"            
    )

add_executable (ClassGenerator "main.cpp" ${source_files})
