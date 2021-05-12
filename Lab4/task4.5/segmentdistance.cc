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
 * @class Point
 * @brief Implements a template class for representing a line segment. The time
 * complexity of all operations is O(1).
 */
template <class T1>
class LineSegment {
 public:
  /**
   * @brief Initializes a new instance of LineSegment by given endpoints.
   * @param start: The start point.
   * @param end: The end point.
   */
  LineSegment(const Point<T1>& start, const Point<T1>& end)
      : start_(start), end_(end) {
    if (end_ < start_) {
      std::swap(start_, end_);
    }

    a_ = start.y() - end.y();
    b_ = end.x() - start.x();
    c_ = -a_ * start.x() - b_ * start.y();

    Norm();
  }

  /**
   * @brief Finds the intersection between this line segment and the other line
   * segment. Time complexity: O(1).
   * @param other: The other line segment.
   * @return: The intersection points.
   */
  std::vector<Point<double>> Intersect(const LineSegment& other) {
    std::vector<Point<double>> result;

    // Bounding box check, idea comes from:
    // https://cp-algorithms.com/geometry/segments-intersection.html
    if (!Intersect(start_.x(), end_.x(), other.start_.x(), other.end_.x()) ||
        !Intersect(start_.y(), end_.y(), other.start_.y(), other.end_.y())) {
      return result;
    }

    double det = Determinant(a_, b_, other.a_, other.b_);
    if (std::fabs(det) < kEps) {
      // This line segment is parallel with the other line segment.

      // Not in same line, so no intersection.
      if (std::fabs(DistanceToLine(other.start_)) > kEps ||
          std::fabs(other.DistanceToLine(start_)) > kEps) {
        return result;
      }

      auto left = std::max(start_, other.start_);
      auto right = std::min(end_, other.end_);

      result.emplace_back(left.x(), left.y());

      if (right != left) {
        result.emplace_back(right.x(), right.y());
      }

    } else {
      double x = -Determinant(c_, b_, other.c_, other.b_) / det;
      double y = -Determinant(a_, c_, other.a_, other.c_) / det;

      // Avoid -0.00
      if (std::fabs(x) < kEps) {
        x = 0;
      }

      if (std::fabs(y) < kEps) {
        y = 0;
      }

      if (Between(start_.x(), end_.x(), x) &&
          Between(start_.y(), end_.y(), y) &&
          Between(other.start_.x(), other.end_.x(), x) &&
          Between(other.start_.y(), other.end_.y(), y)) {
        result.emplace_back(x, y);
      }
    }

    return result;
  }

  /**
   * @brief Computes the distance between two line segments, i.e., the shortest
   * distance between any point on the first line segment and any point on the
   * second line segment. Time complexity: O(1).
   * @param other: The other line segment.
   * @return: The distance.
   */
  double Distance(const LineSegment& other) {
    // Has intersection, so the distance is zero.
    auto intersect = Intersect(other);
    if (!intersect.empty()) {
      return 0;
    }

    double min_dist = 1e9;

    double dist = DistanceToLineSegment(other.start_);
    if (dist < min_dist) {
      min_dist = dist;
    }

    dist = DistanceToLineSegment(other.end_);
    if (dist < min_dist) {
      min_dist = dist;
    }

    dist = other.DistanceToLineSegment(start_);
    if (dist < min_dist) {
      min_dist = dist;
    }

    dist = other.DistanceToLineSegment(end_);
    if (dist < min_dist) {
      min_dist = dist;
    }

    return min_dist;
  }

 private:
  void Norm() {
    double z = std::sqrt(a_ * a_ + b_ * b_);
    if (std::fabs(z) > kEps) {
      a_ /= z;
      b_ /= z;
      c_ /= z;
    }
  }

  bool Intersect(double start1, double end1, double start2, double end2) const {
    if (start1 > end1) {
      std::swap(start1, end1);
    }

    if (start2 > end2) {
      std::swap(start2, end2);
    }

    return std::max(start1, start2) <= std::min(end1, end2) + kEps;
  }

  bool Between(double left, double right, double value) const {
    return std::min(left, right) <= value + kEps &&
           value <= std::max(left, right) + kEps;
  }

  double DistanceToLine(const Point<T1>& point) const {
    return a_ * point.x() + b_ * point.y() + c_;
  }

  double DistanceToLineSegment(const Point<T1>& point) const {
    auto ps = point - start_;
    if (start_ == end_) {
      return ps.Length();
    }

    auto es = end_ - start_;
    double ratio = (double)ps.Dot(es) / es.Dot(es);
    if (ratio > 1) {
      return (point - end_).Length();
    } else if (ratio < 0) {
      return ps.Length();
    } else {
      return std::fabs(DistanceToLine(point));
    }
  }

  double Determinant(double a, double b, double c, double d) const {
    return a * d - b * c;
  }

  const double kEps = 1e-9;

  Point<T1> start_;
  Point<T1> end_;

  double a_;
  double b_;
  double c_;
};

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  fixed(cout);
  cout.precision(2);

  int n;
  Point<int> p1, p2, p3, p4;

  cin >> n;
  while (n--) {
    cin >> p1 >> p2 >> p3 >> p4;

    LineSegment<int> l1(p1, p2), l2(p3, p4);
    cout << l1.Distance(l2) << endl;
  }

  return 0;
}
