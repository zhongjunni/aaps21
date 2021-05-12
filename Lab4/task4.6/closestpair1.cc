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
 * @brief Implements a method for finding a pair of points with minimal distance
 * in a set of points. Under the assumption that the points are uniformly
 * distributed in a sub square of R^2, the time complexity is O(n log n).
 * @param points: A set of points.
 * @return: The indexes for a pair of points with minimal distance between them.
 */
std::vector<int> ClosestPair(std::vector<Point<double>>& points) {
  std::vector<int> indexes(2, 0);
  indexes[0] = 0;
  indexes[1] = 1;

  // First sort the points, time complexity: O(n log n).
  sort(points.begin(), points.end());
  double min_dist = (points[1] - points[0]).Length();
  double dist = 0;

  for (int i = 2; i < points.size(); ++i) {
    for (int j = i - 1; j >= 0; --j) {
      dist = (points[i] - points[j]).Length();
      if (dist < min_dist) {
        min_dist = dist;
        indexes[0] = j;
        indexes[1] = i;
        continue;
      }

      // Break inner loop if x diff is larger than current minimal distance.
      if (points[i].x() - points[j].x() > min_dist) {
        break;
      }
    }
  }

  return indexes;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  fixed(cout);
  cout.precision(2);

  int n;
  while (cin >> n) {
    if (n == 0) {
      break;
    }

    double x, y;
    vector<Point<double>> points;
    points.reserve(n);

    for (int i = 0; i < n; ++i) {
      cin >> x >> y;
      points.emplace_back(x, y);
    }

    auto indexes = ClosestPair(points);
    cout << points[indexes[0]].x() << " " << points[indexes[0]].y() << " "
         << points[indexes[1]].x() << " " << points[indexes[1]].y() << endl;
  }

  return 0;
}