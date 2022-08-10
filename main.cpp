#include <iostream>
#include <vector>

using namespace std;

const int n = 5;

void norm_search(int m, vector<vector<int>> distance, vector<int> g_unvisited, int& min_dist, vector<int>& min_route){
    if (g_unvisited.size() > 0) {
        int next_dist = 0;
        int opti_vertex;
        int to_erase;
        vector<int> unvisited = g_unvisited;
        for (int j = 0; j < m; ++j) {
            if (distance[min_route.back()][unvisited.at(j) * 2] < next_dist || next_dist == 0) {
                next_dist = distance[min_route.back()][unvisited.at(j) * 2]; //Вот тут критерий
                opti_vertex = unvisited.at(j) * 2;
                to_erase = j;
            }
        }
        unvisited.erase(unvisited.begin() + to_erase);
        min_route.push_back(opti_vertex);
        min_route.push_back(opti_vertex + 1);
        norm_search(m-1, distance, unvisited, min_dist, min_route);
    }
}

void search1(int iteration, vector<int> g_route, vector<int> g_unvisited,
             vector<vector<int>> distance, int g_dist, int& min_dist, vector<int>& min_route) {
    bool go_on = false;
    if (g_unvisited.size() > 0) {
        go_on = true;
    } //Проверяем есть ли непосещенные заказы

    if (go_on == true) {
        for (int i = 0; i < iteration; ++i) {
            iteration -= 1;
            vector<int> route = g_route;
            int dist = g_dist;
            vector<int> unvisited = g_unvisited;

            //Идем в непосещенные точки -> рекурсия
            dist += distance[route.back()][unvisited.at(i) * 2]; // Путь до товара
            route.push_back(unvisited.at(i) * 2);
            dist += distance[unvisited.at(i) * 2][unvisited.at(i) * 2 + 1]; //Доставляем товар до склада
            route.push_back(unvisited.at(i) * 2 + 1);
            unvisited.erase(unvisited.begin() + i); //отмечаем точку как посещенную
            search1(iteration, route, unvisited, distance, dist, min_dist, min_route);
        }
    }
    else {
        if (g_dist < min_dist || min_dist == 0) {
            min_dist = g_dist;
            min_route = g_route;
        }
    }
}

int main() {
    int min_dist = 0;
    vector<int> min_route;
//  vector<int> departure = {0, 2, 4};
//  vector<int> arrival = {1, 3, 5};
    vector<vector<int>> distance {{0, 20, 3, 5, 5, 4, 11, 15, 9, 6}, //Матрица смежности
                                  {20, 0, 4, 2, 8, 3, 1, 13, 7, 8},
                                  {3, 4, 0, 15, 4, 8, 17, 3, 8, 6},
                                  {5, 2, 15, 0, 1, 2, 8, 2, 10, 9},
                                  {5, 8, 4, 1, 0, 6, 6, 12, 4, 8},
                                  {4, 3, 8, 2, 6, 0, 9, 11, 15, 16},
                                  {11, 1, 17, 8, 6, 9, 0, 5, 8, 4},
                                  {15, 13, 3, 2, 12, 11, 5, 0, 2, 4},
                                  {9, 7, 8, 10, 4, 15, 8, 2, 0, 3},
                                  {6, 8, 6, 9, 8, 16, 4, 4, 3, 0}};

//    Полный перебор
    for (int i = 0; i < n; ++i) {
        vector<int> unvisited(n);
        for (int i = 0; i < n; ++i) {
            unvisited.at(i) = i;
        }
        unvisited.erase(unvisited.begin() + i);
        search1(n, {i*2, i*2+1}, unvisited, distance,distance[0][i*2] + distance[i*2][i*2+1],min_dist,min_route);
    }

    cout << "The real shortest distance is " << min_dist << endl;
    cout << "On the way ";
    for (int i = 0; i < min_route.size(); ++i) {
        cout << min_route.at(i)<<" ";
    }
    cout << endl << endl;
    min_dist = 0;
    min_route.clear();

 //Блок с моим алгоритмом поиска. Получился тупой жадный поиск
    vector<int> g_unvisited(n);
    for (int i = 0; i < n; ++i) {
        g_unvisited[i] = i;
    }
    int opti_vertex;
    int next_dist = 0;
    for (int i = 0; i < n; ++i) {
        if (distance[0][g_unvisited.at(i) * 2] < next_dist || next_dist == 0) { //Какая должна быть первая точка?
            next_dist = distance[0][g_unvisited.at(i) * 2];
            opti_vertex = g_unvisited.at(i) * 2;
        }
    }
    g_unvisited.erase(g_unvisited.begin() + opti_vertex/2);
    min_route.push_back(opti_vertex);
    min_route.push_back(opti_vertex + 1);
    norm_search(g_unvisited.size(), distance, g_unvisited, min_dist, min_route);
    min_dist += distance[0][min_route[0]]; //Путь до первой точки
    for (int i = 0; i < n * 2 - 1; ++i) {
        min_dist += distance[min_route[i]][min_route[i+1]];  //Весь оставшийся путь
    }

    cout << "The algos shortest distance is " << min_dist << endl;
    cout << "On the way ";
    for (int i = 0; i < min_route.size(); ++i) {
        cout << min_route.at(i)<<" ";
    }
}
