#include <stdio.h>
#include <limits.h>
#include "alg5.h"

#define V 9  // количество вершин

// --------- Алгоритм Дейкстры ---------
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[V][V], int src, int dest) {
    int dist[V];       // кратчайшие расстояния
    int sptSet[V];     // вершины, включенные в кратчайший путь
    int parent[V];     // для восстановления пути

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // вывод пути
    printf("Dijkstra: Кратчайший путь от %d до %d: ", src + 1, dest + 1);
    int path[V];
    int count = 0, crawl = dest;
    while (crawl != -1) {
        path[count++] = crawl;
        crawl = parent[crawl];
    }
    for (int i = count - 1; i >= 0; i--) {
        printf("%d ", path[i] + 1);
    }
    printf("\nРасстояние: %d\n", dist[dest]);
}

// --------- Алгоритм Флойда–Уоршелла ---------
void floydWarshall(int graph[V][V], int src, int dest) {
    int dist[V][V];
    int next[V][V];

    // инициализация
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] == 0 && i != j) {
                dist[i][j] = INT_MAX;
            } else {
                dist[i][j] = graph[i][j];
            }
            next[i][j] = (graph[i][j] != 0) ? j : -1;
        }
    }

    // основной цикл
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX
                    && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // восстановление пути
    printf("Floyd-Warshall: Кратчайший путь от %d до %d: ", src + 1, dest + 1);
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

void alg5_run() {
    int graph[V][V] = {
        {0, 2, 0, 0, 0, 0, 1, 3, 0}, // 1
        {0, 0, 5, 6, 0, 0, 0, 3, 0}, // 2
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
        {0, 0, 1, 0, 0, 0, 0, 0, 6}, // 4
        {0, 0, 0, 0, 0, 9, 6, 0, 0}, // 5
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
        {0, 0, 0, 0, 0, 0, 0, 4, 1}, // 7
        {0, 0, 0, 0, 0, 0, 0, 0, 4}, // 8
        {0, 0, 0, 0, 0, 0, 0, 0, 0}  // 9
    };

    int start = 0; // вершина 1
    int end = 8;   // вершина 9

    dijkstra(graph, start, end);
    floydWarshall(graph, start, end);
}
