# features/steps/word_pairs_steps.py
import os
import subprocess
from behave import given, when, then

# Получаем абсолютный путь к проекту
current_dir = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(current_dir))
CPP_PROGRAM = os.path.join(PROJECT_ROOT, "../", "cpp_executer", "cmake-build-debug", "cpp_executer")

print(f"PROJECT_ROOT: {PROJECT_ROOT}")
print(f"CPP_PROGRAM: {CPP_PROGRAM}")


@given('существует файл "{filename}" с содержимым')
def step_create_test_file(context, filename):
    """Создает тестовый файл с заданным содержимым"""
    print(f"Создаю файл: {filename}")

    # Создаем абсолютный путь
    absolute_path = os.path.join(PROJECT_ROOT, filename)
    print(f"Абсолютный путь к файлу: {absolute_path}")

    # Создаем папку если её нет
    folder = os.path.dirname(absolute_path)
    if folder and not os.path.exists(folder):
        os.makedirs(folder)
        print(f"Создана папка: {folder}")

    # Записываем содержимое
    with open(absolute_path, 'w', encoding='utf-8') as f:
        f.write(context.text)

    print(f"Файл создан успешно")


@when('я вызываю программу с параметрами "{filename}" "{word1}" "{word2}" "{max_distance}"')
def step_call_cpp_program_four_args(context, filename, word1, word2, max_distance):
    """Вызывает C++ программу с 4 параметрами"""
    _call_cpp_program(context, filename, word1, word2, max_distance)


@when('я вызываю программу с параметрами "{filename}" "{word1}" "{word2}"')
def step_call_cpp_program_three_args(context, filename, word1, word2):
    """Вызывает C++ программу с 3 параметрами"""
    _call_cpp_program(context, filename, word1, word2)


@when('я вызываю программу с параметрами "{filename}" "{word1}"')
def step_call_cpp_program_two_args(context, filename, word1):
    """Вызывает C++ программу с 2 параметрами"""
    _call_cpp_program(context, filename, word1)


@when('я вызываю программу с параметрами "{filename}"')
def step_call_cpp_program_one_arg(context, filename):
    """Вызывает C++ программу с 1 параметром"""
    _call_cpp_program(context, filename)


def _call_cpp_program(context, *args):
    """Общая функция для вызова C++ программы"""
    absolute_file_path = os.path.join(PROJECT_ROOT, args[0])

    # Преобразуем все аргументы
    program_args = [CPP_PROGRAM]
    for arg in args:
        if arg == args[0]:  # первый аргумент - это filename
            program_args.append(absolute_file_path)
        else:
            program_args.append(arg)

    print(f"Вызываю программу: {CPP_PROGRAM}")
    print(f"С параметрами: {' '.join(program_args[1:])}")

    if not os.path.exists(CPP_PROGRAM):
        raise FileNotFoundError(f"C++ программа не найдена: {CPP_PROGRAM}")

    result = subprocess.run(
        program_args,
        capture_output=True,
        text=True,
        encoding='utf-8'
    )

    context.result = result
    print(f"Код возврата: {result.returncode}")
    print(f"Stdout: '{result.stdout}'")
    print(f"Stderr: '{result.stderr}'")


@then('программа должна завершиться успешно')
def step_check_success(context):
    assert context.result.returncode == 0, f"Код ошибки: {context.result.returncode}, Stderr: {context.result.stderr}"


@then('программа должна завершиться с ошибкой')
def step_check_error(context):
    assert context.result.returncode != 0, "Ожидалась ошибка, но программа завершилась успешно"


@then('результат должен быть {expected_result:d}')
def step_check_result(context, expected_result):
    actual_result = int(context.result.stdout.strip())
    assert actual_result == expected_result, f"Ожидалось {expected_result}, получено {actual_result}"