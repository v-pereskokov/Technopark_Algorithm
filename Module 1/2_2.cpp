#include <cstdio>
#include <vector>
#include <cmath>

using u_int = unsigned int;
using coord = double;

class Point {
 public:
  Point(const coord x, const coord y)
  : _x(x), _y(y) {}
  Point(const Point& rhs)
  : _x(rhs._x), _y(rhs._y) {}
  coord setX() {
    return _x;
  }
  coord setY() {
    return _y;
  }
 private:
  coord _x;
  coord _y;
};

int main() {
  u_int N;
  scanf("%d", &N);
  if (N < 1000) {
    std::vector<Point> points;
    coord x, y;
    for (std::size_t i = 0; i < N; ++i) {
      scanf("%lf %lf", &x, &y);
      if (x < 10000 && y < 10000)
        points.push_back(Point(x, y));
    }
    points.push_back(Point(points[0].setX(), points[0].setY()));
    double sum_x = 0;
    double sum_y = 0;
    for (std::size_t i = 0; i < N; i += 1) {
      sum_x += points[i].setX() * points[i + 1].setY();
      sum_y += points[i].setY() * points[i + 1].setX();
    }
    double square = std::abs((sum_x - sum_y) / 2);
    printf("%.1f\n", square);
  }
  return 0;
}
