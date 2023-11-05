#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread> // Для функции sleep

using namespace std;

const int rows = 10;
const int cols = 10;

void initializeGrid(bool grid[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = rand() % 2; // Инициализируем сетку случайными 0 и 1 (мёртвые и живые клетки)
        }
    }
}

void printGrid(bool grid[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << (grid[i][j] ? "*" : " "); // Выводим сетку на экран, звёздочка - живая клетка, пробел - мёртвая
        }
        cout << endl;
    }
}

void updateGrid(bool grid[rows][cols]) {
    bool newGrid[rows][cols];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int neighbors = 0;

            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue;

                    int newX = i + x;
                    int newY = j + y;

                    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY]) {
                        neighbors++; // Подсчитываем количество соседей у каждой клетки
                    }
                }
            }

            // Добавленные правила:
            if (grid[i][j] == 1) {
                if (neighbors == 1 || neighbors == 3) {
                    newGrid[i][j] = 1; // Правило 101 -> 111
                } else {
                    newGrid[i][j] = 0; // Иначе клетка умирает
                }
            } else {
                if (neighbors == 3) {
                    newGrid[i][j] = 1; // Правило 111 -> 010
                } else {
                    newGrid[i][j] = 0; // Иначе клетка остаётся мёртвой
                }
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = newGrid[i][j]; // Обновляем сетку в соответствии с новыми значениями
        }
    }
}

int main() {
    srand(time(0));
    bool grid[rows][cols];

    initializeGrid(grid); // Инициализируем сетку случайными значениями

    while (true) {
        system("clear"); // Очищаем экран

        printGrid(grid); // Выводим текущее состояние сетки
        updateGrid(grid); // Обновляем сетку на основе правил

        this_thread::sleep_for(chrono::seconds(1));

    }

    return 0;
}