#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <alg5.h>
#define V 9

// ---------- структура ребра (узел списка) ----------
typedef struct Node {
    int vertex;             // куда ведёт ребро
    int weight;             // вес
    struct Node* next;      // следующее ребро
} Node;

// ---------- список смежности для каждой вершины ----------
typedef struct {
    Node* head;
} AdjList;

AdjList graph[V];

// ---------- добавление ребра ----------
void addEdge(int src, int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = graph[src].head;
    graph[src].head = newNode;
}

// ---------- поиск вершины с минимальным расстоянием ----------
int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, index = -1;

    for (int i = 0; i < V; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

// ---------- алгоритм Дейкстры ----------
void dijkstra(int src, int dest) {
    int dist[V];
    int visited[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int i = 0; i < V - 1; i++) {
        int u = minDistance(dist, visited);
        if (u == -1) break;

        visited[u] = 1;

        Node* temp = graph[u].head;
        while (temp != NULL) {
            int v = temp->vertex;
            int w = temp->weight;

            if (!visited[v] && dist[u] != INT_MAX &&
                dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    // ---------- вывод пути ----------
    if (dist[dest] == INT_MAX) {
        printf("Пути нет\n");
        return;
    }

    int path[V];
    int count = 0;
    int cur = dest;

    while (cur != -1) {
        path[count++] = cur;
        cur = parent[cur];
    }

    printf("Кратчайший путь от %d до %d: ", src + 1, dest + 1);
    for (int i = count - 1; i >= 0; i--)
        printf("%d ", path[i] + 1);

    printf("\nРасстояние: %d\n", dist[dest]);
}

void floydWarshall(int src, int dest) {
    int dist[V][V];
    int next[V][V];

    // ---------- инициализация ----------
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = (i == j) ? 0 : INT_MAX;
            next[i][j] = -1;
        }
    }

    // ---------- заполняем матрицу из списка смежности ----------
    for (int i = 0; i < V; i++) {
        Node* temp = graph[i].head;
        while (temp != NULL) {
            int j = temp->vertex;
            dist[i][j] = temp->weight;
            next[i][j] = j;
            temp = temp->next;
        }
    }

    // ---------- основной алгоритм ----------
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // ---------- восстановление пути ----------
    printf("\nFloyd-Warshall: путь от %d до %d: ", src + 1, dest + 1);

    if (next[src][dest] == -1) {
        printf("пути нет\n");
        return;
    }

    int u = src;
    printf("%d ", u + 1);

    while (u != dest) {
        u = next[u][dest];
        printf("%d ", u + 1);
    }

    printf("\nРасстояние: %d\n", dist[src][dest]);
}


// ---------- main ----------
void alg5_run() {
    // инициализация списков
    for (int i = 0; i < V; i++)
        graph[i].head = NULL;

    // ---------- задание графа (циклом) ----------
    addEdge(0, 1, 2);
    addEdge(0, 6, 1);
    addEdge(0, 7, 3);

    addEdge(1, 2, 5);
    addEdge(1, 3, 6);
    addEdge(1, 7, 3);

    addEdge(3, 2, 1);
    addEdge(3, 8, 6);

    addEdge(4, 5, 9);
    addEdge(4, 6, 6);

    addEdge(6, 7, 4);
    addEdge(6, 8, 1);

    addEdge(7, 8, 4);

    int start = 0; // вершина 1
    int end = 8;   // вершина 9

    dijkstra(start, end);
    floydWarshall(start, end);


    return 0;
}   
