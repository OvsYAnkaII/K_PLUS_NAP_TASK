#include <iostream>
#include "file_pair_words_search_distance.h"
//#include "test.h"

using namespace std;
int main(int argc, char* argv[]) {
    // Проверяем количество аргументов
    if (argc != 5) {
        std::cerr << "неправильное число аргументов" << std::endl;
        return -1;
    }

    std::string file_path = argv[1];
    std::string target1 = argv[2];
    std::string target2 = argv[3];
    int max_distance;

    try {
        max_distance = std::stoi(argv[4]);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: максимальное расстояние должно быть числом" << std::endl;
        return -1;
    }

    if (max_distance < 0) {
        std::cerr << "Ошибка: минимальное расстояние между словами должно быть не меньше 0" << std::endl;
        return -1;
    }

    int result = countWordPairsAtMaxDistance(file_path, target1, target2, max_distance);
    if (result < 0) {
        std::cerr << "Не удалось открыть файл: " << file_path << std::endl;
        return -1;
    }

    std::cout << result << std::endl;
    return 0;
}