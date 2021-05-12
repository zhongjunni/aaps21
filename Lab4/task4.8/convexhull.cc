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
   * @brief Initializes a new instance of Point by given point.
   * @param other: The other point.
   */
  Point(const Point& other) : x_(other.x_), y_(other.y_) {}

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
   * @brief Assign the value of other point to this point.
   * @param rhs: The other point.
   * @return: this point.
   */
  Point& operator=(const Point& rhs) {
    if (this == &rhs) {
      return *this;
    }

    x_ = rhs.x_;
    y_ = rhs.y_;
    return *this;
  }

  /**
   * @brief Determines if two points are equal.
   * @param rhs: The other point.
   * @return: true if the two points are equal, otherwise false.
   */
  bool operator==(const Point& rhs) const {
    return std::fabs(x_ - rhs.x_) < kEps && std::fabs(y_ - rhs.y_) < kEps;
  }

  /**
   * @brief Determines if two points are not equal.
   * @param rhs: The other point.
   * @return: true if the two points are not equal, otherwise false.
   */
  bool operator!=(const Point& rhs) const { return !(*this == rhs); }

  /**
   * @brief Determines if this point is on the left of the other point.
   * @param rhs: The other point.
   * @return: true if this point is on the left of the other point, otherwise
   * false.
   */
  bool operator<(const Point& rhs) const {
    return x_ < rhs.x_ - kEps ||
           (std::fabs(x_ - rhs.x_) < kEps && y_ < rhs.y_ - kEps);
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
 * @brief Determines if the given three points are in clockwise order. Time
 * complexity: O(1).
 * @param a: Point a.
 * @param b: Point b.
 * @param c: Point c.
 * @return: true if are in clockwise order, otherwise false.
 */
template <class T>
bool IsClockWise(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
  return a.x() * (b.y() - c.y()) + b.x() * (c.y() - a.y()) +
             c.x() * (a.y() - b.y()) <
         0;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Determines if the given three points are in counter clockwise order.
 * Time complexity: O(1).
 * @param a: Point a.
 * @param b: Point b.
 * @param c: Point c.
 * @return: true if are in counter clockwise order, otherwise false.
 */
template <class T>
bool IsCounterClockWise(const Point<T>& a, const Point<T>& b,
                        const Point<T>& c) {
  return a.x() * (b.y() - c.y()) + b.x() * (c.y() - a.y()) +
             c.x() * (a.y() - b.y()) >
         0;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a method based on Graham's Scan
 * (https://cp-algorithms.com/geometry/grahams-scan-convex-hull.html) for
 * computing the convex hull of a set of points. Time complexity is O(n log n).
 * @param points: A set of points.
 * @return: An array with the points on the border of the hull ordered by
 * counter clockwise.
 */
template <class T>
std::vector<Point<T>> ConvexHull(const std::vector<Point<T>>& points) {
  // Remove repeated points.
  std::set<Point<T>> point_set(points.begin(), points.end());
  std::vector<Point<T>> distinct_points(point_set.begin(), point_set.end());

  int point_num = distinct_points.size();
  if (point_num < 2) {
    return distinct_points;
  }

  std::sort(distinct_points.begin(), distinct_points.end());

  auto left_most = distinct_points[0];
  auto right_most = distinct_points.back();
  std::vector<Point<T>> up, down;
  up.push_back(left_most);
  down.push_back(left_most);

  for (int i = 1; i < point_num; ++i) {
    if (i == point_num - 1 ||
        IsClockWise(left_most, distinct_points[i], right_most)) {
      while (up.size() >= 2 &&
             !IsClockWise(up[up.size() - 2], up[up.size() - 1],
                          distinct_points[i])) {
        up.pop_back();
      }

      up.push_back(distinct_points[i]);
    }

    if (i == point_num - 1 ||
        IsCounterClockWise(left_most, distinct_points[i], right_most)) {
      while (down.size() >= 2 &&
             !IsCounterClockWise(down[down.size() - 2], down[down.size() - 1],
                                 distinct_points[i])) {
        down.pop_back();
      }

      down.push_back(distinct_points[i]);
    }
  }

  // Get border points in counter clockwise direction.
  std::vector<Point<T>> result;
  for (int i = 0; i < down.size(); ++i) {
    result.push_back(down[i]);
  }

  for (int i = up.size() - 2; i > 0; --i) {
    result.push_back(up[i]);
  }

  return result;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int n;
  while (cin >> n) {
    if (n == 0) {
      break;
    }

    int x, y;
    vector<Point<int>> points;
    points.reserve(n);
    for (int i = 0; i < n; ++i) {
      cin >> x >> y;
      points.emplace_back(x, y);
    }

    auto res = ConvexHull(points);
    cout << res.size() << endl;
    for (auto& p : res) {
      cout << p.x() << " " << p.y() << endl;
    }
  }

  return 0;
}