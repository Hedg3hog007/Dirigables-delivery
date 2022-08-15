#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> all_routes;
void search( vector<int> g_route, vector<int> g_unvisited, vector<int> g_goods,
             vector<vector<int>> distance, int g_dist, int& min_dist, vector<int>& min_route, bool one_more) {
    if (g_unvisited.empty() == false || g_goods.empty() == false) {
        if (g_goods.size() == 0) {
            for (int i = 0; i < g_unvisited.size(); ++i) {
                int dist = g_dist;
                vector<int> unvisited = g_unvisited;
                vector<int> goods = g_goods;
                vector<int> route = g_route;
                dist += distance[route.back()][unvisited.at(i) * 2];
                route.push_back(unvisited.at(i) * 2);
                goods.push_back(unvisited.at(i) * 2);
                unvisited.erase(unvisited.begin() + i);
                search(route, unvisited, goods, distance, dist, min_dist, min_route, false);
                search(route, unvisited, goods, distance, dist, min_dist, min_route, true);

            }
        } else if (g_goods.size() == 1) {

            //Доставка  1 груза
            if (one_more == false) {
                int dist = g_dist;
                dist += distance[g_route.back()][g_goods[0] + 1];
                g_route.push_back(g_goods[0] + 1);
                g_goods.erase(g_goods.begin());
                search(g_route, g_unvisited, g_goods, distance, dist, min_dist, min_route, false);
            }

            //Подобрать 2 груз
            if (one_more == true) {
                for (int i = 0; i < g_unvisited.size(); ++i) {
                    vector<int> goods = g_goods;
                    int dist = g_dist;
                    vector<int> route = g_route;
                    vector<int> unvisited = g_unvisited;
                    goods.push_back(unvisited[i] * 2);
                    dist += distance[route.back()][unvisited[i] * 2];
                    route.push_back(unvisited[i] * 2);
                    unvisited.erase(unvisited.begin() + i);
                    search(route, unvisited, goods, distance, dist, min_dist, min_route, false);

                }
            }
        }

        else if (g_goods.size() == 2) {
            for (int i = 0; i < 2; ++i) {
                int dist = g_dist;
                vector<int> goods = g_goods;
                vector<int> route = g_route;
                dist += distance[route.back()][goods[i] + 1];
                route.push_back(goods[i] + 1);
                goods.erase(goods.begin() + i);
                search(route, g_unvisited, goods, distance, dist, min_dist, min_route, false);
                search(route, g_unvisited, goods, distance, dist, min_dist, min_route, true);
            }
        }
        else {
            cout << "Egor, you are idiot. Goods is more than 2 now -_-";
        }
    }
    else {
        if (g_dist < min_dist || min_dist == 0) {
            min_dist = g_dist;
            min_route = g_route;
        }
        all_routes.push_back(g_route);
    }
}

int main (){
    int min_dist = 0;
    vector<int> min_route;
//    vector<vector<int>> distance {{0, 20, 3, 5, 5, 4, 11, 15, 9, 6}, //Матрица смежности
//                                  {20, 0, 4, 2, 8, 3, 1, 13, 7, 8},
//                                  {3, 4, 0, 15, 4, 8, 17, 3, 8, 6},
//                                  {5, 2, 15, 0, 1, 2, 8, 2, 10, 9},
//                                  {5, 8, 4, 1, 0, 6, 6, 12, 4, 8},
//                                  {4, 3, 8, 2, 6, 0, 9, 11, 15, 16},
//                                  {11, 1, 17, 8, 6, 9, 0, 5, 8, 4},
//                                  {15, 13, 3, 2, 12, 11, 5, 0, 2, 4},
//                                  {9, 7, 8, 10, 4, 15, 8, 2, 0, 3},
//                                  {6, 8, 6, 9, 8, 16, 4, 4, 3, 0}};

    vector<vector<int>> distance {{0, 10, 2, 7, 4, 6},
                                  {10, 0, 8, 3, 6, 4},
                                  {2, 8, 0, 5, 2, 4},
                                  {7, 3, 5, 0, 3, 1},
                                  {4, 6, 2, 3, 0, 2},
                                  {6, 4, 4, 1 ,2, 0} };

    //    Полный перебор
    int n = distance.size() / 2;
        vector<int> unvisited(n);
        for (int j = 0; j < n; ++j) {
            unvisited.at(j) = j;
        }
        search({0}, unvisited,{}, distance, 0,min_dist,min_route, false);
    cout << "The shortest distance is " << min_dist << endl;
    cout << "On the way" << endl;
    for (int i = 1; i < min_route.size(); ++i) {
        cout << min_route[i] << " ";
    }
    cout << endl << endl;
    for (int i = 1; i < all_routes.size(); ++i) {
        for (int j = 1; j < all_routes[i].size(); ++j) {
            cout << all_routes[i][j] << " ";
        }
        cout << endl;
    }
}