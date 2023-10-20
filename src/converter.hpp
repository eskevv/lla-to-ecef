#pragma once

#include "models.hpp"

#include <cmath>

namespace wgs {
// since i am computing at runtime here I wont use #define to be safe
const double FLATTENING_FACTOR = 1.0 / 298.257223563;
const double SEMI_MAJOR = 6378137.0;
const double SEMI_MINOR = (SEMI_MAJOR * (1.0 - FLATTENING_FACTOR));
const double ECCENTRICITY_SQ = FLATTENING_FACTOR * (2.0 - FLATTENING_FACTOR); // or minor^2 / major^2

inline auto to_radians(double degrees) -> double {
  return degrees * M_PI / 180.0;
}

inline auto lla_to_ecef(LLA_Entry lla) -> ECES_Entry {
  double lat_rad = to_radians(lla.latitude);
  double lon_rad = to_radians(lla.longitude);

  double sin_lat = sin(lat_rad);
  double cos_lat = cos(lat_rad);
  double sin_lon = sin(lon_rad);
  double cos_lon = cos(lon_rad);

  double N = wgs::SEMI_MAJOR / sqrt(1 - wgs::ECCENTRICITY_SQ * sin_lat * sin_lat);

  double x = (N + lla.altitude) * cos_lat * cos_lon;
  double y = (N + lla.altitude) * cos_lat * sin_lon;
  double z = (N * (1 - wgs::ECCENTRICITY_SQ) + lla.altitude) * sin_lat;

  return ECES_Entry{lla.time, {x, y, z}};
}
} // namespace wgs
