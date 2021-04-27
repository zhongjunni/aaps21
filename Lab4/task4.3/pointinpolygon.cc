#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace aaps {
namespace zhoni04 {

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @class Point
 * @brief Implements a template class for representing a point in Cartesian
 * coordinate system. This class supports point wise addition/subtraction,
 * multiplication/division with scalar, scalar/cross product, distance of a
 * vector and angle between points. The time complexity of all operations is
 * O(1).
 */
template <class T1>
class Point {
 public:
  /**
   * @brief Initializes a default new instance of Point. The point is at origin.
   */
  Point() : Point(0, 0) {}

  /**
   * @brief Initializes a new instance of Point by given coordinate.
   * @param x: The value of abscissa.
   * @param y: The value of ordinate.
   */
  Point(const T1& x, const T1& y) : x_(x), y_(y) {}

  /**
   * @brief Calculates the dot product of this point(vector) and other
   * point(vector).
   * @param other: The other vector.
   * @return: The dot product.
   */
  T1 Dot(const Point& other) const { return x_ * other.x_ + y_ * other.y_; }

  /**
   * @brief Calculates the cross product of this point(vector) and other
   * point(vector).
   * @param other: The other vector.
   * @return: The scalar value of the calculated vector. Cross product of two
   * vectors is another vector in z-axis, so here I only return the scalar
   * value. If the scalar value is positive, then the vector points at +z-axis;
   * if the scalar value is negtive, then the vector points at -z-axis; if the
   * scalar value is zero, the vector is a zero vector.
   */
  T1 Cross(const Point& other) const { return x_ * other.y_ - y_ * other.x_; }

  /**
   * @brief Calculates the length of a point(vector).
   * @return: The length.
   */
  double Length() const { return std::sqrt(this->Dot(*this)); }

  /**
   * @brief Calculates the angle of two points(vectors).
   * @param other: The other vector.
   * @return: The angle in radian.
   */
  double Angle(const Point& other) const {
    auto dot = this->Dot(other);
    if (std::fabs(dot) < kEps) {
      return kPi / 2;
    }

    return std::acos(dot / (this->Length() * other.Length()));
  }

  /**
   * @brief Gets the abscissa.
   * @return: The reference.
   */
  T1& x() { return x_; }

  /**
   * @brief Gets the abscissa.
   * @return: The const reference.
   */
  const T1& x() const { return x_; }

  /**
   * @brief Gets the ordinate.
   * @return: The reference.
   */
  T1& y() { return y_; }

  /**
   * @brief Gets the ordinate.
   * @return: The const reference.
   */
  const T1& y() const { return y_; }

  /**
   * @brief Determines if two points are equal.
   * @param rhs: The other point.
   * @return: true if the two points are equal, otherwise false.
   */
  bool operator==(const Point& rhs) const {
    return x_ == rhs.x_ && y_ == rhs.y_;
  }

  /**
   * @brief Adds two points(vectors).
   * @param rhs: The other point.
   * @return: The new point.
   */
  Point operator+(const Point& rhs) const {
    return Point(x_ + rhs.x_, y_ + rhs.y_);
  }

  /**
   * @brief Subtracts two points(vectors).
   * @param rhs: The other point.
   * @return: The new point.
   */
  Point operator-(const Point& rhs) const {
    return Point(x_ - rhs.x_, y_ - rhs.y_);
  }

  /**
   * @brief Multiplies a point with a scalar.
   * @param scalar: The scalar.
   * @return: The new point.
   */
  template <class T2>
  Point operator*(const T2& scalar) const {
    return Point(x_ * scalar, y_ * scalar);
  }

  /**
   * @brief Divides a point by a scalar.
   * @param scalar: The scalar.
   * @return: The new point.
   */
  template <class T2>
  Point operator/(const T2& scalar) const {
    return Point((double)x_ / scalar, (double)y_ / scalar);
  }

  friend std::istream& operator>>(std::istream& input, Point& rhs) {
    input >> rhs.x_ >> rhs.y_;
    return input;
  }

 private:
  const double kEps = 1e-9;
  const double kPi = 3.14159265;

  T1 x_;
  T1 y_;
};

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a function to determine if a point is on a segment. Time
 * complexity: O(1).
 * @param a: One end point of the segment.
 * @param b: Another end point of the segment.
 * @param point: The point.
 * @return: true if the point is on the segment, otherwise false.
 */
template <class T>
bool OnSegment(const Point<T>& a, const Point<T>& b, const Point<T>& point) {
  if (a == point || b == point) {
    return true;
  }

  auto pa = a - point;
  auto pb = b - point;
  if (pa.Cross(pb) == 0 && pa.Dot(pb) < 0) {
    return true;
  }

  return false;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a function to determine whether a point is inside, on the
 * border or outside a simple polygon. The function is based on ray casting
 * algorithm. Time complexity: O(n), where n is the number of points in the
 * polygon.
 * @param point: The point.
 * @param poly: The polygon.
 * @return: -1 if the point is outside, 0 if the point is on the border, 1 if
 * the point is inside the polygon.
 */
template <class T>
int InsidePoly(const Point<T>& point, const std::vector<Point<T>>& poly) {
  int result = -2;
  int left_nodes = 0;

  for (int i = 0; i < poly.size(); ++i) {
    const auto& curr = poly[i];
    const auto& prev = i > 0 ? poly[i - 1] : poly.back();

    if (OnSegment(prev, curr, point)) {
      result = 0;
      break;
    }

    if ((curr.y() < point.y() && point.y() <= prev.y()) ||
        (prev.y() < point.y() && point.y() <= curr.y())) {
      double intersec_x = curr.x() + (prev.x() - curr.x()) *
                                         (point.y() - curr.y()) /
                                         (double)(prev.y() - curr.y());

      if (intersec_x < point.x()) {
        ++left_nodes;
      }
    }
  }

  if (result != 0) {
    result = left_nodes % 2 == 0 ? -1 : 1;
  }

  return result;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int n, m;
  while (cin >> n) {
    if (n == 0) {
      break;
    }

    vector<Point<int>> poly;
    int x, y;
    for (int i = 0; i < n; ++i) {
      cin >> x >> y;
      poly.emplace_back(x, y);
    }

    cin >> m;
    Point<int> point;
    for (int i = 0; i < m; ++i) {
      cin >> point;

      int result = InsidePoly(point, poly);
      if (result == -1) {
        cout << "out" << endl;
      } else if (result == 0) {
        cout << "on" << endl;
      } else {
        cout << "in" << endl;
      }
    }
  }

  return 0;
}
