#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

constexpr auto INFINITY = std::numeric_limits<int>::max() / 2;

struct Point {
  int x = 0;
  int y = 0;

  constexpr Point() = default;
};

using LoopError = std::runtime_error;

constexpr int distance(Point a, Point b, bool is_coin) {
  const int weight = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
  return is_coin ? -weight : weight;
}

static_assert(distance({0, 0}, {10, 10}, false) == 200);
static_assert(distance({0, 0}, {-3, 4}, true) + distance({-3, 4}, {10, 10}, false) == 180);

auto read_vertices() {
  int n;
  std::cin >> n;

  std::vector<Point> vertices(n);
  for (int i = 0; i < n; ++i) {
    // add point to graph
    std::cin >> vertices[i].x >> vertices[i].y;
  }

  return vertices;
}


auto read_coins(int n_vertices) {
  int n;
  std::cin >> n;

  std::vector<bool> coins(n_vertices);
  for (int i = 0; i < n; ++i) {
    int index;
    std::cin >> index;

    // mark point i as a coin
    coins[index] = true;
  }

  return coins;
}

auto read_edges(int n_vertices) {
  std::vector<bool> adjacency_matrix(n_vertices * n_vertices);

  // statement is *incorrect*, it *will* read edges for the end vertex
  // for (int i = 0; i < n_vertices - 1; ++i) {
  for (int u = 0; u < n_vertices; ++u) {
    int n_edges;
    std::cin >> n_edges;

    for (int v = 0; v < n_edges; ++v) {
      int index;
      std::cin >> index;

      // add edge i -> index to graph g
      adjacency_matrix[u * n_vertices + index] = true;
    }
  }

  return adjacency_matrix;
}

auto floyd_warshall(const std::vector<Point> &vertices,
                    const std::vector<bool> &coins,
                    const std::vector<bool> &edges) {
  const int N = vertices.size();

  std::vector<int> vertices_lex(N);
  std::iota(vertices_lex.begin(), vertices_lex.end(), 0);
  std::sort(vertices_lex.begin(), vertices_lex.end(),
            [](int a, int b) { return std::to_string(a) < std::to_string(b); });

  std::vector<int> dist(N * N, INFINITY);
  std::vector<int> next(N * N, -1);

  for (auto u : vertices_lex) {
    for (auto v : vertices_lex) {
      if (edges[u * N + v]) {
        dist[u * N + v] = distance(vertices[u], vertices[v], coins[v]);
        next[u * N + v] = v;
      }
    }
  }

  // for (int i = 0; i < N; ++i) {
  //   dist[i * N + i] = 0;
  //   next[i * N + i] = i;
  // }

  for (int k = 0; k < N; ++k) {
    for (auto u : vertices_lex) {
      for (auto v : vertices_lex) {
        int weight = dist[u * N + k] + dist[k * N + v];
        if (weight < dist[u * N + v]) {
          dist[u * N + v] = weight;
          next[u * N + v] = next[u * N + k];
        }
      }
    }
  }

  std::vector<int> route;

  int u = 0, v = N - 1;
  if (next[u * N + v] == -1) {
    return route;
  }

  for (int u = 0; u < N; ++u) {
    if (dist[u * N + u] < 0) {
      throw LoopError("loop detected");
    }
  }

  route.push_back(u);
  while (u != v) {
    u = next[u * N + v];
    route.push_back(u);
  }
  return route;
}

void bellman_ford(const std::vector<Point> &vertices,
                  const std::vector<bool> &coins,
                  const std::vector<bool> &edges) {
  const int N = vertices.size();

  std::vector<int> vertices_lex(N);
  std::iota(vertices_lex.begin(), vertices_lex.end(), 0);
  std::sort(vertices_lex.begin(), vertices_lex.end(),
            [](int a, int b) { return std::to_string(a) < std::to_string(b); });

  std::vector<int> dist(N, INFINITY);
  std::vector<int> prev(N, -1);

  dist[0] = 0;

  for (int i = 0; i < N - 1; ++i) {
    for (auto u : vertices_lex) {
      for (auto v : vertices_lex) {
        if (edges[u * N + v]) {
          int alt = dist[u] + distance(vertices[u], vertices[v], coins[v]);
          if (alt < dist[v]) {
            dist[v] = alt;
            prev[v] = u;
          }
        }
      }
    }
  }

  for (auto u : vertices_lex) {
    for (auto v : vertices_lex) {
      if (edges[u * N + v]) {
        int weight = dist[u] + distance(vertices[u], vertices[v], coins[v]);
        if (weight < dist[v]) {
          std::cout << "LOOP\n";
          return;
        }
      }
    }
  }

  std::vector<int> route;

  int u = N - 1;
  if (prev[u] == -1) {
    return;
  }

  while (u != -1) {
    route.push_back(u);
    u = prev[u];
  }

  if (route.back() != 0) {
    return;
  }

  std::cout << dist[N - 1];
  for (auto it = route.rbegin(); it != route.rend(); ++it) {
    std::cout << ' ' << *it;
  }
  std::cout << '\n';
}

auto revert_matrix(const std::vector<bool> &edges, int N) {
    // N x N
    // i * N + j -> j * N + i
}

void test_case() {
  auto vertices = read_vertices();
  const int N = vertices.size();

  auto coins = read_coins(N);
  auto edges = read_edges(N);

  // print_vertices(vertices, coins);
  // print_edges(vertices, coins, edges);

  // revert edges
  auto

  try {
    auto route = floyd_warshall(vertices, coins, edges);
    if (route.empty()) {
      return;
    }

    // TODO: calculate path length
    for (auto u : route) {
      std::cout << ' ' << u;
    }
    std::cout << '\n';
  } catch (const LoopError&) {
    std::cout << "LOOP\n";
  }

  // std::cout << "bf ";
//   bellman_ford(vertices, coins, edges);
}


int main() {
  int test_cases;
  std::cin >> test_cases;

  for (int i = 0; i < test_cases; ++i) {
    test_case();
  }

  return 0;
}
