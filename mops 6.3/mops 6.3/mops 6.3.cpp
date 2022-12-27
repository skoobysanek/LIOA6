#include "stdafx.h"
#include <time.h>
#include <conio.h>
#include <iostream>

using namespace std;

void createMatrix(int** g, int n); //создание матрицы
void printMatrix(int** g, int n); //вывод матрицы
int** mergeMatrix(int** g1, int** g2, int n1, int n2);   //объединение графов
int** crossMatrix(int** g1, int** g2, int n1, int n2);   //пересечение графов
int** ringSumMatrix(int** g1, int** g2, int n1, int n2);   //кольцевая сумма графов
void freedom(int** g, int n); //освобждение памяти для двумерного массива (матрицы)

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));
    int n1, n2, ** g1, ** g2, **merger, **crossing, **ringSum;

    cout << "Введите количество вершин для перевого графа: ";
    cin >> n1;
    cout << "Введите количество вершин для второго графа: ";
    cin >> n2;
    cout << endl;

    g1 = (int**)malloc(n1 * sizeof(int*)); //выделяем память под столбец указателей
    g2 = (int**)malloc(n2 * sizeof(int*));

    createMatrix(g1, n1);
    createMatrix(g2, n2);
    printMatrix(g1, n1);
    printMatrix(g2, n2);

    merger = mergeMatrix(g1, g2, n1, n2);
    cout << "Объединение графов" << endl;
    printMatrix(merger, _msize(merger) / sizeof(int*));
    crossing = crossMatrix(g1, g2, n1, n2);
    cout << "Пересечение графов" << endl;
    printMatrix(crossing, _msize(crossing) / sizeof(int*));
    ringSum = ringSumMatrix(g1, g2, n1, n2);
    cout << "Кольцевая сумма графов" << endl;
    printMatrix(ringSum, _msize(ringSum) / sizeof(int*));

    freedom(g1, n1);
    freedom(g2, n2);
    freedom(merger, _msize(merger) / sizeof(int*));
    freedom(crossing, _msize(crossing) / sizeof(int*));
    freedom(ringSum, _msize(ringSum) / sizeof(int*));
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

int** mergeMatrix(int** g1, int** g2, int n1, int n2) {
    if (n1 > n2) {  //если первая матрица больше второй
        int** temp2 = (int**)malloc(n1 * sizeof(int*));
        for (int i = 0; i < n1; i++)  // цикл по строкам
        {
            *(temp2 + i) = (int*)malloc(n1 * sizeof(int));
            for (int j = 0; j < n1; j++)  // цикл по столбцам строки
            {
                if (i >= n2 || j >= n2) {
                    *(*(temp2 + i) + j) = 0;
                }
                else {
                    *(*(temp2 + i) + j) = *(*(g2 + i) + j);
                }
            }
        }
        for (int i = 0; i < n1; i++)  // цикл по строкам
        {
            for (int j = 0; j < n1; j++)  // цикл по столбцам строки
            {
                *(*(temp2 + i) + j) = *(*(temp2 + i) + j) | *(*(g1 + i) + j);
            }
        }
        return temp2;
    }
    else if (n1 < n2) { //если вторая матрица больше первой
        int** temp1 = (int**)malloc(n2 * sizeof(int*));
        for (int i = 0; i < n2; i++)  // цикл по строкам
        {
            *(temp1 + i) = (int*)malloc(n2 * sizeof(int));
            for (int j = 0; j < n2; j++)  // цикл по столбцам строки
            {
                if (i >= n1 || j >= n1) {
                    *(*(temp1 + i) + j) = 0;
                }
                else {
                    *(*(temp1 + i) + j) = *(*(g1 + i) + j);
                }
            }
        }
        for (int i = 0; i < n2; i++)  // цикл по строкам
        {
            for (int j = 0; j < n2; j++)  // цикл по столбцам строки
            {
                *(*(temp1 + i) + j) = *(*(temp1 + i) + j) | *(*(g2 + i) + j);
            }
        }
        return temp1;
    }
    else {
        int** temp = (int**)malloc(n1 * sizeof(int*));
        for (int i = 0; i < n1; i++)  // цикл по строкам
        {
            *(temp + i) = (int*)malloc(n1 * sizeof(int));
            for (int j = 0; j < n1; j++)  // цикл по столбцам строки
            {
                *(*(temp + i) + j) = *(*(g1 + i) + j) | *(*(g2 + i) + j);
            }
        }
        return temp;
    }
}

int** crossMatrix(int** g1, int** g2, int n1, int n2) {
    if (n1 > n2) {  //если первая матрица больше второй
        int** temp2 = (int**)malloc(n1 * sizeof(int*));
        for (int i = 0; i < n1; i++)  // цикл по строкам
        {
            *(temp2 + i) = (int*)malloc(n1 * sizeof(int));
            for (int j = 0; j < n1; j++)  // цикл по столбцам строки
            {
                if (i >= n2 || j >= n2) {
                    *(*(temp2 + i) + j) = 0;
                }
                else {
                    *(*(temp2 + i) + j) = *(*(g2 + i) + j);
                }
            }
        }
        for (int i = 0; i < n1; i++)  // цикл по строкам
        {
            for (int j = 0; j < n1; j++)  // цикл по столбцам строки
            {
                *(*(temp2 + i) + j) = *(*(temp2 + i) + j) & *(*(g1 + i) + j);
            }
        }
        return temp2;
    }
    else if (n1 < n2) { //если вторая матрица больше первой
        int** temp1 = (int**)malloc(n2 * sizeof(int*));
        for (int i = 0; i < n2; i++)  // цикл по строкам
        {
            *(temp1 + i) = (int*)malloc(n2 * sizeof(int));
            for (int j = 0; j < n2; j++)  // цикл по столбцам строки
            {
                if (i >= n1 || j >= n1) {
                    *(*(temp1 + i) + j) = 0;
                }
                else {
                    *(*(temp1 + i) + j) = *(*(g1 + i) + j);
                }
            }
        }
        for (int i = 0; i < n2; i++)  // цикл по строкам
        {
            for (int j = 0; j < n2; j++)  // цикл по столбцам строки
            {
                *(*(temp1 + i) + j) = *(*(temp1 + i) + j) & *(*(g2 + i) + j);
            }
        }
        return temp1;
    }
    else {
        int** temp = (int**)malloc(n1 * sizeof(int*));
        for (int i = 0; i < n1; i++)  // цикл по строкам
        {
            *(temp + i) = (int*)malloc(n1 * sizeof(int));
            for (int j = 0; j < n1; j++)  // цикл по столбцам строки
            {
                *(*(temp + i) + j) = *(*(g1 + i) + j) & *(*(g2 + i) + j);
            }
        }
        return temp;
    }
}

int** ringSumMatrix(int** g1, int** g2, int n1, int n2) {
    if (n1 > n2) {  //если первая матрица больше второй
        int** temp2 = (int**)malloc(n1 * sizeof(int*));
        for (int i = 0; i < n1; i++)  // цикл по строкам
        {
            *(temp2 + i) = (int*)malloc(n1 * sizeof(int));
            for (int j = 0; j < n1; j++)  // цикл по столбцам строки
            {
                if (i >= n2 || j >= n2) {
                    *(*(temp2 + i) + j) = 0;
                }
                else {
                    *(*(temp2 + i) + j) = *(*(g2 + i) + j);
                }
            }
        }
        for (int i = 0; i < n1; i++)  // цикл по строкам
        {
            for (int j = 0; j < n1; j++)  // цикл по столбцам строки
            {
                *(*(temp2 + i) + j) = *(*(temp2 + i) + j) ^ *(*(g1 + i) + j);
            }
        }
        return temp2;
    }
    else if (n1 < n2) { //если вторая матрица больше первой
        int** temp1 = (int**)malloc(n2 * sizeof(int*));
        for (int i = 0; i < n2; i++)  // цикл по строкам
        {
            *(temp1 + i) = (int*)malloc(n2 * sizeof(int));
            for (int j = 0; j < n2; j++)  // цикл по столбцам строки
            {
                if (i >= n1 || j >= n1) {
                    *(*(temp1 + i) + j) = 0;
                }
                else {
                    *(*(temp1 + i) + j) = *(*(g1 + i) + j);
                }
            }
        }
        for (int i = 0; i < n2; i++)  // цикл по строкам
        {
            for (int j = 0; j < n2; j++)  // цикл по столбцам строки
            {
                *(*(temp1 + i) + j) = *(*(temp1 + i) + j) ^ *(*(g2 + i) + j);
            }
        }
        return temp1;
    }
    else {
        int** temp = (int**)malloc(n1 * sizeof(int*));
        for (int i = 0; i < n1; i++)  // цикл по строкам
        {
            *(temp + i) = (int*)malloc(n1 * sizeof(int));
            for (int j = 0; j < n1; j++)  // цикл по столбцам строки
            {
                *(*(temp + i) + j) = *(*(g1 + i) + j) ^ *(*(g2 + i) + j);
            }
        }
        return temp;
    }
}

void freedom(int** g, int n) {
    for (int i = 0; i < n; i++) {
        free(*(g + i)); //освобождаем память
    }
    free(g); //освобождаем память
}
