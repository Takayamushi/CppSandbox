#pragma once

#include <ios>
#include <istream>
#include <ostream>
#include <iomanip>

#define manip_scientific std::scientific
#define manip_hexfloat std::hexfloat
#define manip_fixed std::fixed
#define manip_defaultfloat std::defaultfloat
#define manip_precision(x) std::cout.precision(x)