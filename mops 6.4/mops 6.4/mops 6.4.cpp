#include "stdafx.h"
#include <time.h>
#include <conio.h>
#include <iostream>

using namespace std;

void createMatrix(int** g, int n); //создание матрицы
void printMatrix(int** g, int n); //вывод матрицы
void decart(int** g1, int** g2, int** g3, int n1, int n2); //декартовое произведение
void freedom(int** g, int n); //освобждение памяти для двумерного массива (матрицы)

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));
    int n1, n2, ** g1, ** g2, **g3;

    cout << "Введите количество вершин для перевого графа: ";
    cin >> n1;
    cout << "Введите количество вершин для второго графа: ";
    cin >> n2;
    cout << endl;

    g1 = (int**)malloc(n1 * sizeof(int*)); //выделяем память под столбец указателей
    g2 = (int**)malloc(n2 * sizeof(int*));
    g3 = (int**)malloc(n1 * n2 * sizeof(int*));

    createMatrix(g1, n1);
    createMatrix(g2, n2);
    createMatrix(g3, n1 * n2);
    printMatrix(g1, n1);
    printMatrix(g2, n2);

    decart(g1, g2, g3, n1, n2);
    printMatrix(g3, n1 * n2);

    //printMatrix(merger, _msize(merger) / sizeof(int*));

    freedom(g1, n1);
    freedom(g2, n2);
    freedom(g3, n1 * n2);
	_getch();
}

void createMatrix(int** g, int n) {
    for (int i = 0; i < n; i++) {
        *(g + i) = (int*)malloc(n * sizeof(int)); //выделяем память под значения столбцов
    }
    for (int i = 0; i < n; i++)  // цикл по строкам
    {
        for (int j = i; j < n; j++)  // цикл по столбцам строки
        {
            if (i == j) {
                *(*(g + i) + j) = 0;
            }
            else {
                *(*(g + i) + j) = rand() % 2;
                *(*(g + j) + i) = *(*(g + i) + j);
            }
        }
    }
}

void printMatrix(int** g, int n) {
    cout << "  ";
    for (int i = 0; i < n; i++) {
        cout.width(3);
        cout << i;
    }
    cout << endl << endl;
    for (int i = 0; i < n; i++) {
        cout << i << " ";
        for (int j = 0; j < n; j++)
        {
            cout.width(3);
            cout << *(*(g + i) + j);
        }
        cout << endl;
    }
    cout << endl << endl;
}

void decart(int** g1, int** g2, int** g3, int n1, int n2) {
    int x = -1, y = -1;
    for (int i = 0; i < n1 * n2; i++) {
        g3[i] = (int*)malloc(n1 * n2 * sizeof(int)); //выделяем память под значения столбцов
        for (int j = 0; j < n1 * n2; j++) {
            g3[i][j] = 0;
        }
    }
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            x++;
            y = -1;
            for (int k = 0; k < n1; k++) {
                for (int l = 0; l < n2; l++) {
                    y++;
                    if (i == k) g3[x][y] = g2[j][l];
                    if (j == l) g3[x][y] = g1[i][k];
                }
            }
        }
    }
}

void freedom(int** g, int n) {
    for (int i = 0; i < n; i++) {
        free(*(g + i)); //освобождаем память
    }
    free(g); //освобождаем память
}
