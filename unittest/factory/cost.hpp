///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (C) 2019-2022, LAAS-CNRS, University of Edinburgh
// Copyright note valid unless otherwise stated in individual files.
// All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#ifndef CROCODDYL_COST_FACTORY_HPP_
#define CROCODDYL_COST_FACTORY_HPP_

#include "activation.hpp"
#include "crocoddyl/core/cost-base.hpp"
#include "crocoddyl/core/costs/cost-sum.hpp"
#include "crocoddyl/core/numdiff/cost.hpp"
#include "crocoddyl/multibody/states/multibody.hpp"
#include "state.hpp"

namespace crocoddyl {
namespace unittest {

struct CostModelTypes {
  enum Type {
    CostModelResidualState,
    CostModelResidualControl,
    CostModelResidualCoMPosition,
    // CostModelResidualCentroidalMomentum,  // @todo Figure out the pinocchio
    // callbacks.
    CostModelResidualFramePlacement,
    CostModelResidualFrameRotation,
    CostModelResidualFrameTranslation,
    CostModelResidualFrameVelocity,
    NbCostModelTypes
  };
  static std::vector<Type> init_all() {
    std::vector<Type> v;
    v.reserve(NbCostModelTypes);
    for (int i = 0; i < NbCostModelTypes; ++i) {
      v.push_back((Type)i);
    }
    return v;
  }
  static const std::vector<Type> all;
};

struct CostModelNoFFTypes {
  enum Type { CostModelResidualControlGrav, NbCostModelNoFFTypes };
  static std::vector<Type> init_all() {
    std::vector<Type> v;
    v.clear();
    for (int i = 0; i < NbCostModelNoFFTypes; ++i) {
      v.push_back((Type)i);
    }
    return v;
  }
  static const std::vector<Type> all;
};

#ifdef PINOCCHIO_WITH_HPP_FCL
struct CostModelCollisionTypes {
  enum Type { CostModelResidualPairCollision, NbCostModelCollisionTypes };
  static std::vector<Type> init_all() {
    std::vector<Type> v;
    v.clear();
    for (int i = 0; i < NbCostModelCollisionTypes; ++i) {
      v.push_back((Type)i);
    }
    return v;
  }
  static const std::vector<Type> all;
};
#endif  // PINOCCHIO_WITH_HPP_FCL

std::ostream& operator<<(std::ostream& os, CostModelTypes::Type type);
std::ostream& operator<<(std::ostream& os, CostModelNoFFTypes::Type type);
#ifdef PINOCCHIO_WITH_HPP_FCL
std::ostream& operator<<(std::ostream& os, CostModelCollisionTypes::Type type);
#endif  // PINOCCHIO_WITH_HPP_FCL

class CostModelFactory {
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  typedef crocoddyl::MathBaseTpl<double> MathBase;
  typedef typename MathBase::Vector6s Vector6d;
  typedef pinocchio::GeometryObject::CollisionGeometryPtr CollisionGeometryPtr;

  explicit CostModelFactory();
  ~CostModelFactory();

  std::shared_ptr<crocoddyl::CostModelAbstract> create(
      CostModelTypes::Type cost_type, StateModelTypes::Type state_type,
      ActivationModelTypes::Type activation_type,
      std::size_t nu = std::numeric_limits<std::size_t>::max()) const;
  std::shared_ptr<crocoddyl::CostModelAbstract> create(
      CostModelNoFFTypes::Type cost_type,
      ActivationModelTypes::Type activation_type,
      std::size_t nu = std::numeric_limits<std::size_t>::max()) const;

#ifdef PINOCCHIO_WITH_HPP_FCL
  std::shared_ptr<crocoddyl::CostModelAbstract> create(
      CostModelCollisionTypes::Type cost_type, StateModelTypes::Type state_type,
      std::size_t nu = std::numeric_limits<std::size_t>::max()) const;
#endif  // PINOCCHIO_WITH_HPP_FCL
};

std::shared_ptr<crocoddyl::CostModelAbstract> create_random_cost(
    StateModelTypes::Type state_type,
    std::size_t nu = std::numeric_limits<std::size_t>::max());
}  // namespace unittest
}  // namespace crocoddyl

#endif  // CROCODDYL_COST_FACTORY_HPP_
