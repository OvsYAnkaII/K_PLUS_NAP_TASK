# features/word_pairs.feature
Feature: Подсчет пар слов в файле

  Scenario: Успешный подсчет пар слов
    Given существует файл "test_files/sample.txt" с содержимым
      """
      apple orange banana
      banana grape apple
      apple pear banana
      """
    When я вызываю программу с параметрами "test_files/sample.txt" "apple" "banana" "0"
    Then программа должна завершиться успешно
    And результат должен быть 0

  Scenario: Успешный подсчет пар слов без существующего слова
    When я вызываю программу с параметрами "test_files/sample.txt" "apple" "watermelon" "0"
    Then программа должна завершиться успешно
    And результат должен быть 0

  Scenario: Успешный подсчет пар слов
    Given существует файл "test_files/mathew_sample2.txt" с содержимым
      """
      apple orange banana
      banana grape apple
      apple pear banana
      """
    When я вызываю программу с параметрами "test_files/mathew_sample2.txt" "apple" "banana" "0"
    Then программа должна завершиться успешно
    And результат должен быть 0

    Scenario: Успешный подсчет пар слов
    Given существует файл "test_files/mathew_sample3.txt" с содержимым
      """
      apple orange banana grape apple orange banana
      banana grape apple
      apple pear banana
      """
    When я вызываю программу с параметрами "test_files/mathew_sample3.txt" "apple" "banana" "1"
    Then программа должна завершиться успешно
    And результат должен быть 3

  Scenario: Файл не существует
    When я вызываю программу с параметрами "test_files/nonexistent.txt" "word1" "word2" "5"
    Then программа должна завершиться с ошибкой

  Scenario: Отрицательный ввод расстояния
    When я вызываю программу с параметрами "test_files/sample.txt" "apple" "banana" "-1"
    Then программа должна завершиться с ошибкой

  Scenario: Невалидный ввод расстояния
    When я вызываю программу с параметрами "test_files/mathew_sample3.txt" "word1" "word2" "пять"
    Then программа должна завершиться с ошибкой

  Scenario: Отсутствует параметр
    When я вызываю программу с параметрами "word1" "word2" "5"
    Then программа должна завершиться с ошибкой

    When я вызываю программу с параметрами "test_files/mathew_sample3.txt" "word1" "5"
    Then программа должна завершиться с ошибкой

    When я вызываю программу с параметрами "test_files/mathew_sample3.txt" "word1" "word2"
    Then программа должна завершиться с ошибкой

Scenario: Загружаем картинку вместо файла
    When я вызываю программу с параметрами "target_files/mid_jump.jpeg" "word1" "word2" "5"
    Then программа должна завершиться успешно
  And результат должен быть 0