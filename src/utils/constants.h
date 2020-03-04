#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "boost/math/constants/constants.hpp"

namespace constants
{

constexpr float pi = boost::math::constants::pi<float>();
constexpr float twoPi = boost::math::constants::two_pi<float>();

} // namespace constants

#endif // CONSTANTS_H