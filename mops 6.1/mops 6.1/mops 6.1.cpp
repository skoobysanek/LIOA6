#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;	

struct node
{
    int vertex; //����� �������
    struct node* next; //������ �� ����. �������
};
struct node* createNode(int); //�������� �������

struct Graph
{
    int numVertices; //���-�� ������
    struct node** adjLists; //������ �� ���������, ������� ������ ����� ������
};
struct Graph* createGraph(int vertices); //��������� ������� �����

void addEdge(struct Graph* graph, int src, int dest); //�������� �����
void printGraph(struct Graph* graph); //����� ����� � ���� ������ ���������
void fillGraph(struct Graph* graph, int** g, int n); //���������� ������ ���������

void createMatrix(int** g, int n); //�������� �������
void printMatrix(int** g, int n); //����� �������
void freedom(int** g, int n); //����������� ������ ��� ���������� ������� (�������)

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));
    int n, ** g1, ** g2;

    cout << "������� ���������� ������ ��� ������: ";
    cin >> n;
    cout << endl;

    g1 = (int**)malloc(n * sizeof(int*)); //�������� ������ ��� ������� ����������
    g2 = (int**)malloc(n * sizeof(int*));

    createMatrix(g1, n);
    createMatrix(g2, n);
    printMatrix(g1, n);
    printMatrix(g2, n);

    struct Graph* graph1 = createGraph(n);
    struct Graph* graph2 = createGraph(n);
    fillGraph(graph1, g1, n);
    fillGraph(graph2, g2, n);

    printGraph(graph1);
    cout << endl;
    printGraph(graph2);

    freedom(g1, n);
    freedom(g2, n);

	_getch();
}

struct node* createNode(int v)
{
    struct node* newNode = (node*)malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices)
{
    struct Graph* graph = (Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = (node**)malloc(vertices * sizeof(struct node*));

    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{

    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src
    //newNode = createNode(src);
    //newNode->next = graph->adjLists[dest];
    //graph->adjLists[dest] = newNode;
}

void printGraph(struct Graph* graph)
{
    for (int v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        cout << endl << "������ ��������� ������ " << v << endl;
        while (temp)
        {
            if (temp->next == NULL) {
                cout << temp->vertex;
            }
            else {
                cout << temp->vertex << " -> ";
            }
            temp = temp->next;
        }
        cout << endl;
    }
}

void fillGraph(struct Graph* graph, int** g, int n) {
    for (int i = 0; i < n; i++)  // ���� �� �������
    {
        for (int j = 0; j < n; j++)  // ���� �� �������� ������
        {
            if (*(*(g + i) + j) == 1) {
                addEdge(graph, i, j);
            }
        }
    }
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

void freedom(int** g, int n) {
    for (int i = 0; i < n; i++) {
        free(*(g + i)); //����������� ������
    }
    free(g); //����������� ������
}
