// #include <vector>
// #include <iostream>
// using namespace std;

// template<typename Tv>
// class Vertex {
// public:
//     Tv data;
//     int dTime, fTime;
//     int degree;
//     vector<Edge<Tv>*> neighbors;
//     Vertex(const Tv& d): 
//         data(d), degree(0), dTime(-1), fTime(-1) {}
//     connect(Edge<Tv>* e) {
//         neighbors.push_back(e);
//         degree ++;
//     }
// };

// template<typename Tv>
// class Edge {
// public:
//     Vertex<Tv>* src;
//     Vertex<Tv>* dst;
//     int weight;
//     Edge(Vertex<Tv> s, Vertex<Tv> d, int w): 
//         src(&s), dst(&d), weight(w) {}
// };

// template<typename Tv, typename Te>
// class Graph_mtx {
// private:
//     vector<Vertex<Tv>*> V;
//     vector<vector<int>> adj;
//     int n;
// public:
//     Graph_mtx(int n) : n(n) {
//         V.resize(n, nullptr);
//         adj.resize(n, vector<int>(n, 0));
//     }

//     ~Graph_mtx() {
//         for (int i = 0; i < n; i++) {
//             delete V[i];
//         }
//     }

//     bool insert_by_edge(Edge<Tv> edge) {
//         if (edge.src->degree >= n || edge.dst->degree >= n) {
//             return false;
//         }
//         adj[edge.src->degree][edge.dst->degree] = edge.weight;
//         edge.src->degree++;
//         edge.dst->degree++;
//         return true;
//     }

//     bool insert_by_vertex(Vertex<Tv> v) {
//         if (v.degree >= n) {
//             return false;
//         }
//         V[v.degree] = &v;
//         return true;
//     }
// };

// int main() {
//     Vertex<int> v1(1);
//     Vertex<int> v2(2);
//     Edge<int> e(v1, v2, 3);
//     Graph_mtx<int, int> g(2);
//     g.insert_by_edge(e);
//     return 0;
// }