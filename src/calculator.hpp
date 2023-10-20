#include "converter.hpp"
#include "models.hpp"
#include "parser.hpp"
#include <atomic>

namespace wgs {
// velocity as double at point b -> from a to b
inline auto calculate_velocity(ECES_Entry a, ECES_Entry b) -> double {
  Vec3 diff = b.coords - a.coords;
  double distance = diff.magnitude();
  double delta_t = b.time - a.time;
  return distance / delta_t;
}

inline auto velocity_vector(ECES_Entry a, ECES_Entry b) -> Vec3 {
  Vec3 diff = b.coords - a.coords;
  double delta_t = b.time - a.time;
  return diff / delta_t;
}

// this method doesn't interpolate for velocity instead it creates a new data Entry
inline auto do_interpolation(ECES_Entry min, ECES_Entry max, double target) -> ECES_Entry {
  double delta_t = max.time - min.time;
  double target_diff = target - min.time;
  double ratio = target_diff / delta_t;

  double interpolated_x = min.coords.x + (max.coords.x - min.coords.x) * ratio;
  double interpolated_y = min.coords.y + (max.coords.y - min.coords.y) * ratio;
  double interpolated_z = min.coords.z + (max.coords.z - min.coords.z) * ratio;

  // use this to more accurately interpolate with the min entry
  return ECES_Entry{target, Vec3{interpolated_x, interpolated_y, interpolated_z}};
}
}; // namespace wgs
