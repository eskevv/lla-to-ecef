#include "calculator.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cmath>

const ECES_Entry sample_1{300, 37.9, -41.6, 50.9};
const ECES_Entry sample_2{380, 27.9, -21.6, 30.9};
const ECES_Entry sample_3{350, 27.9, -21.6, 30.9};
const ECES_Entry sample_4{360, 27.9, -21.6, 30.9};
const ECES_Entry sample_5{370, 27.9, -21.6, 30.9};
const ECES_Entry sample_6{330, 27.9, -21.6, 30.9};
const ECES_Entry sample_7{1532332859, 3792769.06, -416065.11, 5093881.45};
const ECES_Entry sample_8{1532332864, 3792743.47, -416192.94, 5093890.24};
const ECES_Entry sample_9{1532333999.040000, {2988601.383388, -2641468.443807, 4964379.611029}};
const ECES_Entry sample_10{1532334000.000000, {2987769.791737, -2642928.988627, 4964104.179107}};

auto round(double number, int decimals) -> double {
  int accuracy = std::pow(10, decimals);
  return std::round(number * accuracy) / accuracy;
}

auto round(Vec3 v) -> Vec3 {
  return Vec3{round(v.x, 6), round(v.y, 6), round(v.z, 6)};
}

// the absolute speed of the object (scalar)
TEST_CASE("Accurate velocity between two points", "[velocity]") {
  REQUIRE(wgs::calculate_velocity(sample_1, sample_2) == 0.3750);
  REQUIRE(round(wgs::calculate_velocity(sample_7, sample_8), 4) == 26.1324);
}

// the vector velocity
TEST_CASE("Vectory velocity between two points", "[velocity]") {
  REQUIRE((round(wgs::velocity_vector(sample_9, sample_10)) == Vec3{-866.241269, -1521.400794, -286.908241}));
}
