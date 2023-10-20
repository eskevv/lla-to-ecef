#include "calculator.hpp"
#include "converter.hpp"
#include "models.hpp"

#include <algorithm>
#include <math.h>

/* Additional tests are provided in the tests module */

inline auto velocity_at_time(std::vector<ECES_Entry> data, double time) -> Vec3 {
  for (size_t x = 0; x < data.size(); x++) {
    int at_time = static_cast<int>(time);
    int time_est = static_cast<int>(data[x].time);

    if (at_time == time_est) {
      return x == 0 ? Vec3{} : wgs::velocity_vector(data[x - 1], data[x]);
    } else if (time_est > at_time) { // interpolates for values not fixed in the table
      // linear interpolation will use the two closest times for accurate results
      ECES_Entry interpolated = wgs::do_interpolation(data[x - 1], data[x], time);
      return wgs::velocity_vector(data[x - 1], interpolated);
    }
  }
  return Vec3{}; // velocity couldn't be deduced from time (defaults to Zero)
}

int main() {
  // provide the LLA concrete parsing mechanism to create a list of LLA entries
  wgs::LLA_Parser parser{};
  std::vector<LLA_Entry> lla_data = wgs::parse_csv("data.csv", &parser);
  
  // convert the values to ECES
  std::vector<ECES_Entry> eces_data;
  eces_data.resize(lla_data.size());
  std::transform(lla_data.begin(), lla_data.end(), eces_data.begin(), wgs::lla_to_ecef);

  // output for assignment input
  std::cout << "\n  __RUNTIME__\n";
  std::cout << "\n Velocity(m/s) @TIME: 1532334000 = {" << velocity_at_time(eces_data, 1532334000.0) << "}\n";
  std::cout << " Velocity(m/s) @TIME: 1532335268 = {" << velocity_at_time(eces_data, 1532335268.0) << "}\n\n";

  return 0;
}
