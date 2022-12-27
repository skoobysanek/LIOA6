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

int checker(struct node* temp1, struct node* temp2);  //�������� �� ������

void freedom(int** g, int n); //����������� ������ ��� ���������� ������� (�������)
void createMatrix(int** g, int n); //�������� �������
void printMatrix(int** g, int n); //����� �������
int** matchVertex(int** g_old, int n); //�������������� ������ �������
int** constrictEdge(int** g_old, int n);  //���������� ����� �������
int** splitVertex(int** g_old, int n);  //����������� ������� �������

void freedom(struct Graph* graph); //����������� ������ ��� ���������� ������� (�����)
void addEdge(struct Graph* graph, int src, int dest); //�������� �����
void printGraph(struct Graph* graph); //����� ����� � ���� ������ ���������
void fillGraph(struct Graph* graph, int** g, int n); //���������� ������ ���������
struct Graph* matchVertex(struct Graph* graph);    //�������������� ������ �����
struct Graph* constrictEdge(struct Graph* graph);    //���������� ����� �����
struct Graph* splitVertex(struct Graph* graph);    //����������� ������� �����
void constrictEdge();  //���������� ����� �����
void splitVertex();    //����������� ������� �����

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));
    int n1, ** g1;

    cout << "������� ���������� ������ ��� �����: ";
    cin >> n1;
    cout << endl;

    g1 = (int**)malloc(n1 * sizeof(int*)); //�������� ������ ��� ������� ����������

    createMatrix(g1, n1);
    printMatrix(g1, n1);

    struct Graph* graph1 = createGraph(n1);
    fillGraph(graph1, g1, graph1->numVertices);

    printGraph(graph1);
    printMatrix(g1, n1);

    g1 = matchVertex(g1, _msize(g1) / sizeof(int*));
    printMatrix(g1, _msize(g1) / sizeof(int*));
    g1 = constrictEdge(g1, _msize(g1) / sizeof(int*));
    printMatrix(g1, _msize(g1) / sizeof(int*));
    g1 = splitVertex(g1, _msize(g1) / sizeof(int*));
    printMatrix(g1, _msize(g1) / sizeof(int*));
    
    graph1 = matchVertex(graph1);
    printGraph(graph1);
    graph1 = constrictEdge(graph1);
    printGraph(graph1);
    graph1 = splitVertex(graph1);
    printGraph(graph1);


    freedom(g1, _msize(g1) / sizeof(int*));
    freedom(graph1);
	_getch();
}

int checker(struct node* temp1, int E)
{
    if (temp1 == 0) return 0;
    return (E == temp1->vertex) + checker(temp1->next, E);
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
    // Add edge from src to dest
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
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
    cout << endl;
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

struct Graph* matchVertex(struct Graph* graph) {
    int v1, v2, k;
    struct node* temp1, * temp2;
    cout << "������� ������ ������ ��� ��������������:" << endl;
    cin >> v1 >> v2;
    for (int i = 0; i < graph->numVertices; i++) {  //����������� ��������� � ������ ��������������� ������
        temp1 = graph->adjLists[i];
        while (temp1)
        {
            if (temp1->vertex > v2) {
                temp1->vertex--;
            }
            else if (temp1->vertex == v2) {
                temp1->vertex = v1;
            }
            temp1 = temp1->next;
        }
    }
    temp1 = graph->adjLists[v1];
    temp2 = graph->adjLists[v2];
    while (temp2)
    {
        if (!checker(temp1, temp2->vertex)) {
            addEdge(graph, v1, temp2->vertex);
        }
        temp2 = temp2->next;
    }
    for (int i = 0; i < graph->numVertices; i++) {  //�������� ����������
        k = 0;
        temp1 = graph->adjLists[i];
        while (temp1)
        {
            if (k != 0) {
                if (temp1->vertex == v1) {
                    temp2->next = temp1->next;
                    free(temp1);
                    break;
                }
            }
            temp2 = temp1;
            if (temp1->vertex == v1) {
                k++;
            }
            temp1 = temp1->next;
        }
    }

    //����������� �����
    struct Graph* graph1 = createGraph(graph->numVertices-1);
    k = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        if (i != v2) {
            temp1 = graph->adjLists[i];
            while (temp1)
            {
                addEdge(graph1, k, temp1->vertex);
                temp1 = temp1->next;
            }
            k++;
        }
    }
    freedom(graph);
    return graph1;
}

struct Graph* constrictEdge(struct Graph* graph) {
    int v1, v2, k;
    struct node* temp1, * temp2;
    cout << "������� ������ ������ ��� ���������� ����� ����� ����:" << endl;
    cin >> v1 >> v2;
    temp1 = graph->adjLists[v1];
    while (temp1)   //�������� ������� �����
    {
        if (temp1->vertex == v2) {
            break;
        }
        else if (temp1->next == 0) {
            cout << "����� �����������, ���������� �� ���������" << endl;
            return graph;
        }
        temp1 = temp1->next;
    }
    for (int i = 0; i < graph->numVertices; i++) {  //������ ������ ������ ������� �� ������ � ���������� ������� �� 1, ������� ��� ����� ������ �������
        temp1 = graph->adjLists[i];
        while (temp1)
        {
            if (temp1->vertex > v2) {
                temp1->vertex--;
            }
            else if (temp1->vertex == v2) {
                temp1->vertex = v1;
            }
            temp1 = temp1->next;
        }
    }
    temp1 = graph->adjLists[v1];
    temp2 = graph->adjLists[v2];
    while (temp2)   //������� ���� �� ������ �� ������ ������� � ��������� �� ������� ��������
    {
        if (!checker(temp1, temp2->vertex)) {
            addEdge(graph, v1, temp2->vertex);
        }
        temp2 = temp2->next;
    }
    for (int i = 0; i < graph->numVertices; i++) {  //�������� �������� ����������� � ���������� ������
        k = 0;
        temp1 = graph->adjLists[i];
        while (temp1)
        {
            if (k != 0) {
                if (temp1->vertex == v1) {
                    temp2->next = temp1->next;
                    free(temp1);
                    break;
                }
            }
            temp2 = temp1;
            if (temp1->vertex == v1) {
                k++;
            }
            temp1 = temp1->next;
        }
    }
    temp1 = graph->adjLists[v1];
    temp2 = graph->adjLists[v1];
    while (temp1)   //�������� �����
    {
        temp2 = temp1->next;
        if (temp1->vertex == v1) {
            free(temp1);
            graph->adjLists[v1] = temp2;
            break;
        }
        else if (temp2->vertex == v1) {
            temp1->next = temp2->next;
            free(temp2);
            break;
        }
        temp1 = temp1->next;
    }

    struct Graph* graph1 = createGraph(graph->numVertices - 1);
    k = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        if (i != v2) {
            temp1 = graph->adjLists[i];
            while (temp1)
            {
                addEdge(graph1, k, temp1->vertex);
                temp1 = temp1->next;
            }
            k++;
        }
    }
    freedom(graph);
    return graph1;
}

struct Graph* splitVertex(struct Graph* graph) {
    int v1, v2, k;
    struct node* temp1, * temp2;
    cout << "������� ����� ������� ��� �����������:" << endl;
    cin >> v1;
    v2 = v1 + 1;
    struct Graph* graph1 = createGraph(graph->numVertices + 1);
    k = 0;
    for (int i = 0; i < graph1->numVertices; i++) {
        temp1 = graph->adjLists[k];
        if (i == v1) {
            while (temp1)
            {
                addEdge(graph1, i, temp1->vertex);
                temp1 = temp1->next;
            }
        }
        else {
            while (temp1)
            {
                addEdge(graph1, i, temp1->vertex);
                temp1 = temp1->next;
            }
            k++;
        }
    }
    freedom(graph);
    for (int i = 0; i < graph1->numVertices; i++) { //��������� ������ ������ ������� ���� ��� ���� ������ � ���������� ������� �� 1, ������� ��� ����� ������ �������
        temp1 = graph1->adjLists[i];
        while (temp1)
        {
            if (temp1->vertex > v1) {
                temp1->vertex++;
            }
            if (temp1->vertex == v1) {
                addEdge(graph1, i, v2);
            }
            temp1 = temp1->next;
        }
    }
    if (!checker(graph1->adjLists[v1], v2)) {
        addEdge(graph1, v1, v2);
        addEdge(graph1, v2, v1);
    }
    return graph1;
}

void createMatrix(int** g, int n) {
    for (int i = 0; i < n; i++) {
        *(g + i) = (int*)malloc(n * sizeof(int)); //�������� ������ ��� ��������� �� ������
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

int** matchVertex(int** g_old, int n) {
    int m = n - 1, v1, v2, k1, k2;
    cout << "������� ������ ������ ��� ��������������:" << endl;
    cin >> v1 >> v2;
    int** g = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        *(g + i) = (int*)malloc(m * sizeof(int));
    }
    for (int j = 0; j < n; j++)     //���������� ���������� ���� ������ � ���� (���������� �� ������)
    {
        *(*(g_old + v1) + j) = *(*(g_old + v1) + j) | *(*(g_old + v2) + j);
        *(*(g_old + j) + v1) = *(*(g_old + v1) + j);
    }
    if (*(*(g_old + v1) + v2) == 1) {   //���� ���� ����� �� ����� �� ������
        *(*(g_old + v1) + v1) = 1;
    }

    k1 = 0;
    for (int i = 0; i < n; i++)  // ���� �� �������
    {
        k2 = 0;
        if (i != v2) {  //���������� ������ ���������� ������� �� ��� ������� �������������
            for (int j = 0; j < n; j++)  // ���� �� �������� ������
            {
                if (j != v2) {  //���������� ������� ���������� ������� �� ��� ������� �������������
                    *(*(g + k1) + k2) = *(*(g_old + i) + j);
                    k2++;
                }
            }
            k1++;
        }
    }
    freedom(g_old, n);
    return g;
}

int** constrictEdge(int** g_old, int n) {
    int m = n - 1, v1, v2, k1, k2;
    cout << "������� ������ ������ ��� ���������� ����� ����� ����:" << endl;
    cin >> v1 >> v2;
    if (*(*(g_old + v1) + v2) == 0) {
        cout << "����� �����������, ���������� �� ���������" << endl;
        return g_old;
    }
    else if (v1 == v2) {
        *(*(g_old + v1) + v2) = 0;
        return g_old;
    }
    else {
        int** g = (int**)malloc(m * sizeof(int*));
        for (int i = 0; i < m; i++) {
            *(g + i) = (int*)malloc(m * sizeof(int));
        }
        for (int j = 0; j < n; j++)     //���������� ���������� ���� ������ � ���� (���������� �� ������)
        {
            *(*(g_old + v1) + j) = *(*(g_old + v1) + j) | *(*(g_old + v2) + j);
            *(*(g_old + j) + v1) = *(*(g_old + v1) + j);
        }
        *(*(g_old + v1) + v1) = 0;

        k1 = 0;
        for (int i = 0; i < n; i++)  // ���� �� �������
        {
            k2 = 0;
            if (i != v2) {  //���������� ������ ���������� ������� �� ��� ������� �������������
                for (int j = 0; j < n; j++)  // ���� �� �������� ������
                {
                    if (j != v2) {  //���������� ������� ���������� ������� �� ��� ������� �������������
                        *(*(g + k1) + k2) = *(*(g_old + i) + j);
                        k2++;
                    }
                }
                k1++;
            }
        }
        freedom(g_old, n);
        return g;
    }
}

int** splitVertex(int** g_old, int n) {
    int m = n + 1, v1, v2, k1, k2;
    cout << "������� ����� ������� ��� �����������:" << endl;
    cin >> v1;
    v2 = v1 + 1;
    int** g = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        *(g + i) = (int*)malloc(m * sizeof(int));
    }

    k1 = 0;
    for (int i = 0; i < m; i++)  // ���� �� �������
    {
        k2 = 0;
        if (i != v1) {  //��������� ����� ������ ���������� �� ���������� ���� ��� ���
            for (int j = 0; j < m; j++)  // ���� �� �������� ������
            {
                if (j != v1) {  //��������� ����� ������� �������� �� ����������� ���� ��� ��
                    *(*(g + i) + j) = *(*(g_old + k1) + k2);
                    k2++;
                }
                else {
                    *(*(g + i) + j) = *(*(g_old + k1) + k2);
                }
            }
            k1++;
        }
        else {
            for (int j = 0; j < m; j++)  // ���� �� �������� ������
            {
                if (j != v1) {  //��������� ����� ������� �������� �� ����������� ���� ��� ��
                    *(*(g + i) + j) = *(*(g_old + k1) + k2);
                    k2++;
                }
                else {
                    *(*(g + i) + j) = *(*(g_old + k1) + k2);
                }
            }
        }
    }
    *(*(g + v1) + v2) = 1;
    *(*(g + v2) + v1) = 1;
    freedom(g_old, n);
    return g;
}

void freedom(int** g, int n) {
    for (int i = 0; i < n; i++) {
        free(*(g + i)); //����������� ������
    }
    free(g); //����������� ������
}

void freedom(struct Graph* graph) {
    struct node* temp1, * temp2;
    for (int i = 0; i < graph->numVertices; i++) {
        temp1 = graph->adjLists[i];
        temp2 = graph->adjLists[i];
        while (temp2)
        {
            temp1 = temp1->next;
            free(temp2);
            temp2 = temp1;
        } 
    }
    free(graph); //����������� ������
}