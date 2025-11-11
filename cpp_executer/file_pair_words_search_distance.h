#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>


// Функция очистки слова от знаков препинания

inline std::string cleanWord(const std::string& word) {
    if (word.empty()) return "";

    // Функция проверки символа
    auto isValidChar = [](unsigned char c) -> bool {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <= 'Z') ||
               (c >= '0' && c <= '9') ||
               (c >= 128); // все не-ASCII (русские и др.)
    };

    // Ищем первую валидную букву слева
    size_t left = 0;
    while (left < word.size() && !isValidChar(word[left])) {
        left++;
    }
    if (left == word.size()) return "";

    // Ищем последнюю валидную букву справа
    size_t right = word.size() - 1;
    while (right > left && !isValidChar(word[right])) {
        right--;
    }

    return word.substr(left, right - left + 1);
}


inline int countWordPairsAtMaxDistance(const std::string& filename, const std::string& word1, const std::string& word2, int maxDistance) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return -1;
    }

    std::queue<std::string> window;
    std::unordered_map<std::string, int> wordCount;
    int pairCount = 0;
    std::string currentWord;

    // Инициализируем счетчики для целевых слов
    wordCount[word1] = 0;
    wordCount[word2] = 0;

    while (file >> currentWord) {
        currentWord = cleanWord(currentWord);
        // Добавляем текущее слово в окно
        window.push(currentWord);

        // Если слово целевое - добавляем пары со всеми противоположными словами в окне
        if (currentWord == word1) {
            wordCount[word1]++;
        }
        if (currentWord == word2) {
            pairCount += wordCount[word1];
        }

        // Удаляем слово из начала окна, если окно превысило maxDistance + 1
        // (т.к. расстояние = слова между, значит окно должно быть размером maxDistance + 2 слов)
        if (window.size() > maxDistance + 1) {
            std::string oldestWord = window.front();
            window.pop();

            if (oldestWord == word1) {
                wordCount[word1]--;
            }
        }
    }

    file.close();
    return pairCount;
}
