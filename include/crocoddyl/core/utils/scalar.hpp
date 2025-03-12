///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (C) 2025-2025, Heriot-Watt University
// Copyright note valid unless otherwise stated in individual files.
// All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#ifndef CROCODDYL_UTILS_SCALAR_HPP_
#define CROCODDYL_UTILS_SCALAR_HPP_

#include <type_traits>

#include "crocoddyl/core/utils/conversions.hpp"

namespace crocoddyl {

// Trait to extract base scalar type
template <typename T>
struct ScalarBaseType {
  typedef T type;
};

#ifdef CROCODDYL_WITH_CODEGEN

template <typename T>
struct ScalarBaseType<CppAD::AD<T>> {
  typedef typename ScalarBaseType<T>::type type;
};

template <typename T>
struct ScalarBaseType<CppAD::cg::CG<T>> {
  typedef typename ScalarBaseType<T>::type type;
};

#endif

// Main function
template <typename Scalar>
Scalar ScaleNumerics(double base_value, double float_multiplier = 1e3) {
  typedef typename ScalarBaseType<Scalar>::type Base;
  return std::is_same<Base, float>::value
             ? static_cast<Scalar>(base_value * float_multiplier)
             : static_cast<Scalar>(base_value);
}

}  // namespace crocoddyl

#endif  // CROCODDYL_UTILS_SCALAR_HPP_
