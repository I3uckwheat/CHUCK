#pragma once

namespace helpers {
  template <class T>
  T clamp(T num, T low, T high) {
    return num < low ? low : (num > high ? high : num);
  }
}