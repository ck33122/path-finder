# path-finder

Поисковик лутбоксов на двумерном поле.

## Сборка

Требуется CMake версии не ниже 3.4 и компилятор C++ поддерживающий стандарт C++20.
Пример команд для сборки (из корня репозитория):
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Использование
Входные аргументы:
1. путь до входного файла с описанием игрового поля
2. путь до выходного файла
3. количество лутбоксов

Пример: `./path-finder input.txt output.txt 10`
