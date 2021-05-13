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
 * @class PointWrapper
 * @brief Implements a class for wrappering a point with double coordinates.
 * Adding a field called index to represent the index of points in a list. The
 * time complexity of all operations is O(1).
 */
class PointWrapper : public Point<double> {
 public:
  /**
   * @brief Initializes a default new instance of PointWrapper.
   */
  PointWrapper() : PointWrapper(0, 0, 0) {}

  /**
   * @brief Initializes a new instance of PointWrapper by given coordinates and
   * index.
   * @param x: The value of abscissa.
   * @param y: The value of ordinate.
   * @param index: The index.
   */
  PointWrapper(double x, double y, int index)
      : Point<double>(x, y), index_(index) {}

  /**
   * @brief Gets the index.
   * @return: The reference.
   */
  int& index() { return index_; }

  /**
   * @brief Gets the index.
   * @return: The const reference.
   */
  const int& index() const { return index_; }

  /**
   * @brief Assign the value of other point wrapper to this wrapper.
   * @param rhs: The other point wrapper.
   * @return: this point wrapper.
   */
  PointWrapper& operator=(const PointWrapper& rhs) {
    if (this == &rhs) {
      return *this;
    }

    x() = rhs.x();
    y() = rhs.y();
    index_ = rhs.index_;
    return *this;
  }

 private:
  int index_;
};

/**
 * @brief Compares two points by their value of ordinate. Time complexity: O(1).
 * @param a: The point a.
 * @param b: The point b.
 * @return: true if a's ordinate is less than b's ordinate, otherwise false.
 */
bool CompareY(const PointWrapper& a, const PointWrapper& b) {
  return a.y() < b.y();
}

std::pair<double, std::vector<int>> BruteForce(
    const std::vector<PointWrapper>& points) {
  double min_dist = 1e9;
  std::vector<int> point_pair(2, 0);

  for (int i = 0; i < points.size(); ++i) {
    for (int j = i + 1; j < points.size(); ++j) {
      double dist = (points[j] - points[i]).Length();
      if (dist < min_dist) {
        min_dist = dist;
        point_pair[0] = points[i].index();
        point_pair[1] = points[j].index();
      }
    }
  }

  return std::make_pair(min_dist, point_pair);
}

/**
 * @brief Finds a pair of points with minimal distance in a set of points. Idea
 * and some codes refer to:
 * https://cp-algorithms.com/geometry/nearest_points.html Time complexity: O(n *
 * log n), where n is (right - left).
 * @param points: A set of points.
 * @param left: The left bound index (included).
 * @param right: The right bound index (not included).
 * @param min_dist: The current minimal distance.
 * @param indexes: The indexes of a pair of points that have minimal distance.
 */
std::pair<double, std::vector<int>> DivideAndConquer(
    const std::vector<PointWrapper>& points_sort_by_x,
    const std::vector<PointWrapper>& points_sort_by_y) {
  if (points_sort_by_x.size() <= 3) {
    return BruteForce(points_sort_by_x);
  }

  int n = points_sort_by_x.size();
  std::vector<PointWrapper> x_left(n / 2);
  std::vector<PointWrapper> x_right(n - n / 2);

  std::copy(points_sort_by_x.begin(), points_sort_by_x.begin() + n / 2,
            x_left.begin());
  std::copy(points_sort_by_x.begin() + n / 2, points_sort_by_x.end(),
            x_right.begin());

  double mid_x = points_sort_by_x[n / 2].x();

  std::vector<PointWrapper> y_left;
  std::vector<PointWrapper> y_right;
  for (auto& p : points_sort_by_y) {
    if (p.x() <= mid_x) {
      y_left.push_back(p);
    } else {
      y_right.push_back(p);
    }
  }

  auto pair1 = DivideAndConquer(x_left, y_left);
  auto pair2 = DivideAndConquer(x_right, y_right);
  auto min_pair = pair1;
  if (pair2.first < pair1.first) {
    min_pair = pair2;
  }

  std::vector<PointWrapper> stripe;
  for (auto& p : points_sort_by_y) {
    if (std::fabs(p.x() - mid_x) < min_pair.first) {
      stripe.push_back(p);
    }
  }

  for (int i = 0; i < stripe.size(); ++i) {
    for (int j = i + 1;
         j < stripe.size() && stripe[j].y() - stripe[i].y() < min_pair.first;
         ++j) {
      double dist = (stripe[j] - stripe[i]).Length();
      if (dist < min_pair.first) {
        min_pair.first = dist;
        min_pair.second[0] = stripe[i].index();
        min_pair.second[1] = stripe[j].index();
      }
    }
  }
  return min_pair;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a method based on divide and conquer for finding a pair of
 * points with minimal distance in a set of points. The worst time complexity is
 * O(n log n).
 * @param points: A set of points.
 * @return: The indexes for a pair of points with minimal distance between them.
 */
std::vector<int> ClosestPair(const std::vector<PointWrapper>& points) {
  std::vector<PointWrapper> points_sort_by_x(points);
  std::sort(points_sort_by_x.begin(), points_sort_by_x.end());

  std::vector<PointWrapper> points_sort_by_y(points);
  std::sort(points_sort_by_y.begin(), points_sort_by_y.end(), CompareY);

  auto result = DivideAndConquer(points_sort_by_x, points_sort_by_y);
  return result.second;
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
    vector<PointWrapper> points;
    points.reserve(n);

    for (int i = 0; i < n; ++i) {
      cin >> x >> y;
      points.emplace_back(x, y, i);
    }

    auto indexes = ClosestPair(points);
    cout << points[indexes[0]].x() << " " << points[indexes[0]].y() << " "
         << points[indexes[1]].x() << " " << points[indexes[1]].y() << endl;
  }

  return 0;
}