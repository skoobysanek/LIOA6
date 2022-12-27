#include "stdafx.h"
#include <time.h>
#include <conio.h>
#include <iostream>

using namespace std;

void createMatrix(int** g, int n); //�������� �������
void printMatrix(int** g, int n); //����� �������
int** mergeMatrix(int** g1, int** g2, int n1, int n2);   //����������� ������
int** crossMatrix(int** g1, int** g2, int n1, int n2);   //����������� ������
int** ringSumMatrix(int** g1, int** g2, int n1, int n2);   //��������� ����� ������
void freedom(int** g, int n); //����������� ������ ��� ���������� ������� (�������)

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));
    int n1, n2, ** g1, ** g2, **merger, **crossing, **ringSum;

    cout << "������� ���������� ������ ��� �������� �����: ";
    cin >> n1;
    cout << "������� ���������� ������ ��� ������� �����: ";
    cin >> n2;
    cout << endl;

    g1 = (int**)malloc(n1 * sizeof(int*)); //�������� ������ ��� ������� ����������
    g2 = (int**)malloc(n2 * sizeof(int*));

    createMatrix(g1, n1);
    createMatrix(g2, n2);
    printMatrix(g1, n1);
    printMatrix(g2, n2);

    merger = mergeMatrix(g1, g2, n1, n2);
    cout << "����������� ������" << endl;
    printMatrix(merger, _msize(merger) / sizeof(int*));
    crossing = crossMatrix(g1, g2, n1, n2);
    cout << "����������� ������" << endl;
    printMatrix(crossing, _msize(crossing) / sizeof(int*));
    ringSum = ringSumMatrix(g1, g2, n1, n2);
    cout << "��������� ����� ������" << endl;
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
        *(g + i) = (int*)malloc(n * sizeof(int)); //�������� ������ ��� �������� ��������
    }
    for (int i = 0; i < n; i++)  // ���� �� �������
    {
        for (int j = i; j < n; j++)  // ���� �� �������� ������
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
    if (n1 > n2) {  //���� ������ ������� ������ ������
        int** temp2 = (int**)malloc(n1 * sizeof(int*));
        for (int i = 0; i < n1; i++)  // ���� �� �������
        {
            *(temp2 + i) = (int*)malloc(n1 * sizeof(int));
            for (int j = 0; j < n1; j++)  // ���� �� �������� ������
            {
                if (i >= n2 || j >= n2) {
                    *(*(temp2 + i) + j) = 0;
                }
                else {
                    *(*(temp2 + i) + j) = *(*(g2 + i) + j);
                }
            }
        }
        for (int i = 0; i < n1; i++)  // ���� �� �������
        {
            for (int j = 0; j < n1; j++)  // ���� �� �������� ������
            {
                *(*(temp2 + i) + j) = *(*(temp2 + i) + j) | *(*(g1 + i) + j);
            }
        }
        return temp2;
    }
    else if (n1 < n2) { //���� ������ ������� ������ ������
        int** temp1 = (int**)malloc(n2 * sizeof(int*));
        for (int i = 0; i < n2; i++)  // ���� �� �������
        {
            *(temp1 + i) = (int*)malloc(n2 * sizeof(int));
            for (int j = 0; j < n2; j++)  // ���� �� �������� ������
            {
                if (i >= n1 || j >= n1) {
                    *(*(temp1 + i) + j) = 0;
                }
                else {
                    *(*(temp1 + i) + j) = *(*(g1 + i) + j);
                }
            }
        }
        for (int i = 0; i < n2; i++)  // ���� �� �������
        {
            for (int j = 0; j < n2; j++)  // ���� �� �������� ������
            {
                *(*(temp1 + i) + j) = *(*(temp1 + i) + j) | *(*(g2 + i) + j);
            }
        }
        return temp1;
    }
    else {
        int** temp = (int**)malloc(n1 * sizeof(int*));
        for (int i = 0; i < n1; i++)  // ���� �� �������
        {
            *(temp + i) = (int*)malloc(n1 * sizeof(int));
            for (int j = 0; j < n1; j++)  // ���� �� �������� ������
            {
                *(*(temp + i) + j) = *(*(g1 + i) + j) | *(*(g2 + i) + j);
            }
        }
        return temp;
    }
}

int** crossMatrix(int** g1, int** g2, int n1, int n2) {
    if (n1 > n2) {  //���� ������ ������� ������ ������
        int** temp2 = (int**)malloc(n1 * sizeof(int*));
        for (int i = 0; i < n1; i++)  // ���� �� �������
        {
            *(temp2 + i) = (int*)malloc(n1 * sizeof(int));
            for (int j = 0; j < n1; j++)  // ���� �� �������� ������
            {
                if (i >= n2 || j >= n2) {
                    *(*(temp2 + i) + j) = 0;
                }
                else {
                    *(*(temp2 + i) + j) = *(*(g2 + i) + j);
                }
            }
        }
        for (int i = 0; i < n1; i++)  // ���� �� �������
        {
            for (int j = 0; j < n1; j++)  // ���� �� �������� ������
            {
                *(*(temp2 + i) + j) = *(*(temp2 + i) + j) & *(*(g1 + i) + j);
            }
        }
        return temp2;
    }
    else if (n1 < n2) { //���� ������ ������� ������ ������
        int** temp1 = (int**)malloc(n2 * sizeof(int*));
        for (int i = 0; i < n2; i++)  // ���� �� �������
        {
            *(temp1 + i) = (int*)malloc(n2 * sizeof(int));
            for (int j = 0; j < n2; j++)  // ���� �� �������� ������
            {
                if (i >= n1 || j >= n1) {
                    *(*(temp1 + i) + j) = 0;
                }
                else {
                    *(*(temp1 + i) + j) = *(*(g1 + i) + j);
                }
            }
        }
        for (int i = 0; i < n2; i++)  // ���� �� �������
        {
            for (int j = 0; j < n2; j++)  // ���� �� �������� ������
            {
                *(*(temp1 + i) + j) = *(*(temp1 + i) + j) & *(*(g2 + i) + j);
            }
        }
        return temp1;
    }
    else {
        int** temp = (int**)malloc(n1 * sizeof(int*));
        for (int i = 0; i < n1; i++)  // ���� �� �������
        {
            *(temp + i) = (int*)malloc(n1 * sizeof(int));
            for (int j = 0; j < n1; j++)  // ���� �� �������� ������
            {
                *(*(temp + i) + j) = *(*(g1 + i) + j) & *(*(g2 + i) + j);
            }
        }
        return temp;
    }
}

int** ringSumMatrix(int** g1, int** g2, int n1, int n2) {
    if (n1 > n2) {  //���� ������ ������� ������ ������
        int** temp2 = (int**)malloc(n1 * sizeof(int*));
        for (int i = 0; i < n1; i++)  // ���� �� �������
        {
            *(temp2 + i) = (int*)malloc(n1 * sizeof(int));
            for (int j = 0; j < n1; j++)  // ���� �� �������� ������
            {
                if (i >= n2 || j >= n2) {
                    *(*(temp2 + i) + j) = 0;
                }
                else {
                    *(*(temp2 + i) + j) = *(*(g2 + i) + j);
                }
            }
        }
        for (int i = 0; i < n1; i++)  // ���� �� �������
        {
            for (int j = 0; j < n1; j++)  // ���� �� �������� ������
            {
                *(*(temp2 + i) + j) = *(*(temp2 + i) + j) ^ *(*(g1 + i) + j);
            }
        }
        return temp2;
    }
    else if (n1 < n2) { //���� ������ ������� ������ ������
        int** temp1 = (int**)malloc(n2 * sizeof(int*));
        for (int i = 0; i < n2; i++)  // ���� �� �������
        {
            *(temp1 + i) = (int*)malloc(n2 * sizeof(int));
            for (int j = 0; j < n2; j++)  // ���� �� �������� ������
            {
                if (i >= n1 || j >= n1) {
                    *(*(temp1 + i) + j) = 0;
                }
                else {
                    *(*(temp1 + i) + j) = *(*(g1 + i) + j);
                }
            }
        }
        for (int i = 0; i < n2; i++)  // ���� �� �������
        {
            for (int j = 0; j < n2; j++)  // ���� �� �������� ������
            {
                *(*(temp1 + i) + j) = *(*(temp1 + i) + j) ^ *(*(g2 + i) + j);
            }
        }
        return temp1;
    }
    else {
        int** temp = (int**)malloc(n1 * sizeof(int*));
        for (int i = 0; i < n1; i++)  // ���� �� �������
        {
            *(temp + i) = (int*)malloc(n1 * sizeof(int));
            for (int j = 0; j < n1; j++)  // ���� �� �������� ������
            {
                *(*(temp + i) + j) = *(*(g1 + i) + j) ^ *(*(g2 + i) + j);
            }
        }
        return temp;
    }
}

void freedom(int** g, int n) {
    for (int i = 0; i < n; i++) {
        free(*(g + i)); //����������� ������
    }
    free(g); //����������� ������
}
