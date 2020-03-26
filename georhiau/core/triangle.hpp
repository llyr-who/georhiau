#pragma once
#include "core/polygon.hpp"

namespace georhiau {
namespace core {
template <typename T>
using triangle = polygon<T, 3>;

template <typename T>
T area(const triangle<T>& t) {}

}  // namespace core
}  // namespace georhiau

