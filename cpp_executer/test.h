#pragma once
#include <iosfwd>

using namespace std;

inline void generateTestFile() {
    ofstream file("test_input.txt");

    vector<string> words = {
        "apple", "banana", "orange", "apple", "banana",
        "orange", "apple", "apple", "banana", "orange",
        "apple", "banana", "orange", "apple", "banana",
        "other", "words", "here", "apple", "banana"
    };

    for (int i = 0; i < 50; i++) {
        file << words[i % words.size()] << " ";
        if (i % 10 == 9) file << "\n";
    }

    file.close();
    cout << "Тестовый файл 'test_input.txt' создан\n";
}

inline void createCustomTestFile() {
    ofstream file("custom_test.txt");
    file << "налоги на доходы физических лиц в России, налоги на доходы физических лиц в Казахстане";
    file.close();
    cout << "Кастомный тестовый файл 'custom_test.txt' создан\n";
}

inline void createExactTestFile() {
    ofstream file("exact_test.txt");
    file << "A B A B A B A B"; // A = apple, B = banana для простоты
    file.close();
    cout << "Точный тестовый файл 'exact_test.txt' создан\n";
}

inline void runCustomTests() {
    cout << "\n=== КАСТОМНЫЕ ТЕСТЫ ===\n";
    cout << "Текст: 'налоги на доходы физических лиц в России, налоги на доходы физических лиц в Казахстане'\n";
    cout << "Позиции: [0]налоги [1]на [2]доходы [3]физических [4]лиц [5]в [6]России, [7]налоги [8]на [9]доходы ...\n\n";

    // Тест 1: налоги Россия 5
    long long result1 = countWordPairsAtMaxDistance("custom_test.txt", "налоги", "России", 5);
    cout << "Кастом тест 1 (налоги-России, расстояние ≤ 5): " << result1 << " пар\n";
    cout << "  Ожидается: 1 пара ([0]налоги-[6]России, расстояние = 5 слов между)\n";

    // Тест 2: налоги Россия 4
    long long result2 = countWordPairsAtMaxDistance("custom_test.txt", "налоги", "России", 4);
    cout << "Кастом тест 2 (налоги-России, расстояние ≤ 4): " << result2 << " пар\n";
    cout << "  Ожидается: 0 пар (расстояние между [0]налоги и [6]России = 5 > 4)\n";

    // Тест 3: налоги доходы 1
    long long result3 = countWordPairsAtMaxDistance("custom_test.txt", "налоги", "доходы", 1);
    cout << "Кастом тест 3 (налоги-доходы, расстояние ≤ 1): " << result3 << " пар\n";
    cout << "  Ожидается: 2 пары ([0]налоги-[2]доходы, [7]налоги-[9]доходы)\n";

    // Тест 4: налоги доходы 100
    long long result4 = countWordPairsAtMaxDistance("custom_test.txt", "налоги", "доходы", 100);
    cout << "Кастом тест 4 (налоги-доходы, расстояние ≤ 100): " << result4 << " пар\n";
    cout << "  Ожидается: 2 пары ([0]налоги-[2]доходы, [0]налоги-[9]доходы)\n";
}

inline void runExactTests() {
    cout << "\n=== ТОЧНЫЕ ТЕСТЫ ===\n";

    // Файл: "A B A B A B A B" (8 слов)
    // Позиции: [0]A [1]B [2]A [3]B [4]A [5]B [6]A [7]B

    // Тест 1: Расстояние ≤ 0 (только соседние слова)
    long long result1 = countWordPairsAtMaxDistance("exact_test.txt", "A", "B", 0);
    cout << "Точный тест 1 (A-B, расстояние ≤ 0): " << result1 << " пар\n";
    cout << "  Ожидается: 4 пары (0-1, 2-3, 4-5, 6-7)\n";

    // Тест 2: Расстояние ≤ 1 (соседи + через 1 слово)
    long long result2 = countWordPairsAtMaxDistance("exact_test.txt", "A", "B", 1);
    cout << "Точный тест 2 (A-B, расстояние ≤ 1): " << result2 << " пар\n";
    cout << "  Ожидается: 10 пар\n";
    cout << "  Пары: 0-1, 0-3, 1-2, 1-4, 2-3, 2-5, 3-4, 3-6, 4-5, 4-7, 5-6, 6-7\n";

    // Тест 3: Расстояние ≤ 2 (все возможные пары)
    long long result3 = countWordPairsAtMaxDistance("exact_test.txt", "A", "B", 2);
    cout << "Точный тест 3 (A-B, расстояние ≤ 2): " << result3 << " пар\n";
    cout << "  Ожидается: 12 пар (все комбинации A и B)\n";

    // Тест 4: Только слово A (должно быть 0 пар)
    long long result4 = countWordPairsAtMaxDistance("exact_test.txt", "A", "C", 2);
    cout << "Точный тест 4 (A-C, слова C нет): " << result4 << " пар\n";
    cout << "  Ожидается: 0 пар\n";

    // Тест 5: Большое расстояние
    long long result5 = countWordPairsAtMaxDistance("exact_test.txt", "A", "B", 100);
    cout << "Точный тест 5 (A-B, расстояние ≤ 100): " << result5 << " пар\n";
    cout << "  Ожидается: 12 пар (все пары, т.к. максимальное расстояние = 7)\n";
}

inline void run_all_tests() {
    cout << "Генерация тестовых файлов...\n";
    generateTestFile();
    createCustomTestFile();
    createExactTestFile();

    cout << "\nЗапуск тестов...\n";
    //runBasicTests();
    runCustomTests();
    runExactTests();

    cout << "\nВсе тесты завершены!\n";
}