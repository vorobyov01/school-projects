package com.company;

import java.util.*;

class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int INF = Integer.MAX_VALUE / 2; // "Бесконечность"
        int vNum; // количество вершин

        vNum = in.nextInt();
        int[][] graph = new int[vNum][vNum];
        for (int i = 0; i < vNum; i++) {
            for (int j = 0; j < vNum; j++) {
                graph[i][j] = INF;
            }
        }

        for (int i = 0; i < vNum; i++) {
            for (int j = 0; j < vNum; j++) {
                int a = in.nextInt();
                if (a != 0) {
                    graph[i][j] = a;
                }
            }
        }
        dijkstra(0, vNum, INF, graph);

    }

    /* Алгоритм Дейкстры за O(V^2) */
    static void dijkstra (int start, int vNum, int INF, int[][] graph) {
        ArrayList<Boolean> used = new ArrayList<Boolean>(); // массив пометок
        for (int i = 0; i < vNum; i++) {
            used.add(false);
        }
        ArrayList<Integer> dist = new ArrayList<Integer>(); // массив расстояния. dist[v] = минимальное_расстояние
        ArrayList<Integer> pred = new ArrayList<Integer>();
        for (int i = 0; i < vNum; i++) {
            pred.add(-1);
        }
        dist.add(0);
        for (int i=1; i<vNum; i++) {
            dist.add(INF);
        } // устанавливаем расстояние до всех вершин INF
        dist.set(start, 0); // для начальной вершины положим 0

        for (;;) {
            int v = -1;
            for (int nv = 0; nv < vNum; nv++) // перебираем вершины
                if (!used.get(nv) && dist.get(nv) < INF && (v == -1 || dist.get(v) > dist.get(nv))) // выбираем самую близкую непомеченную вершину
                    v = nv;
            if (v == -1) break; // ближайшая вершина не найдена
                used.set(v, true); // помечаем ее
            for (int nv = 0; nv < vNum; nv++) {
                if (!used.get(nv) && graph[v][nv] < INF) { // для всех непомеченных смежных
                    dist.set(nv, Math.min(dist.get(nv), dist.get(v) + graph[v][nv])); // улучшаем оценку расстояния (релаксация)
                    pred.set(nv, v);
                }
            }

        }
        System.out.println(dist.get(3));
    }
}
/*
0 2 3 0 0 0 0
2 0 0 10 5 0 0
3 0 0 0 0 0 0
0 10 0 0 0 0 0
0 5 0 0 0 6 18
0 0 0 0 6 0 2
0 0 0 0 18 2 0
*/