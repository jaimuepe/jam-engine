#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "boost/math/constants/constants.hpp"

namespace constants
{

namespace renderdevices
{

constexpr float internalDeviceWidth = 1920.0f;
constexpr float internalDeviceHeight = 1080.0f;
constexpr float internalAspectRatio = internalDeviceWidth / internalDeviceHeight;

} // namespace renderdevices


namespace math
{

constexpr float halfPi = boost::math::constants::half_pi<float>();
constexpr float pi = boost::math::constants::pi<float>();
constexpr float twoPi = boost::math::constants::two_pi<float>();

} // namespace maths

} // namespace constants

#endif // CONSTANTS_H
