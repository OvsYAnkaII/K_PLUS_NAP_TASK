cmake_minimum_required(VERSION 4.0)
project(NAP_task_cpp_executer)

set(CMAKE_CXX_STANDARD 20)

# ПРАВИЛЬНО: add_executable(ИМЯ_ПРОГРАММЫ файлы.cpp)
add_executable(cpp_executer
        main.cpp
        file_pair_words_search_distance.h
        test.h)

# Указываем папку для заголовочных файлов (если они в подпапках)
target_include_directories(cpp_executer PRIVATE .)