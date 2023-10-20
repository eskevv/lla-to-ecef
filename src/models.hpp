#pragma once

#include <cmath>
#include <iostream>
#include <ostream>

struct Vec3 {
  double x;
  double y;
  double z;

  inline auto operator-(const Vec3 &v) -> Vec3 {
    return Vec3{x - v.x, y - v.y, z - v.z};
  }

  inline auto operator/(double n) -> Vec3 {
    return Vec3{x / n, y / n, z / n};
  }

  inline auto magnitude() -> double {
    return std::sqrt(x * x + y * y + z * z);
  }

  inline auto operator==(const Vec3 v) -> bool {
    return x == v.x && y == v.y && z == v.z;
  }

  inline friend auto operator<<(std::ostream &os, const Vec3 &v) -> std::ostream & {
    os << "x: " << v.x;
    os << " y: " << v.y;
    os << " z: " << v.z;
    return os;
  }
};

struct LLA_Entry {
  double time;
  double latitude;
  double longitude;
  double altitude;

  inline friend auto operator<<(std::ostream &os, const LLA_Entry &lla_entry) -> std::ostream & {
    os << "time: " << std::fixed << lla_entry.time;
    os << " lat: " << lla_entry.latitude;
    os << " lon: " << lla_entry.longitude;
    os << " alt: " << lla_entry.altitude;
    return os;
  }
};

struct ECES_Entry {
  double time;
  Vec3 coords;

  inline friend auto operator<<(std::ostream &os, const ECES_Entry &eces_entry) -> std::ostream & {
    os << "time: " << std::fixed << eces_entry.time;
    os << eces_entry.coords;
    return os;
  }
};
