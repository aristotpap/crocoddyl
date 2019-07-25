///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (C) 2018-2019, LAAS-CNRS
// Copyright note valid unless otherwise stated in individual files.
// All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#ifndef PYTHON_CROCODDYL_MULTIBODY_COSTS_STATE_HPP_
#define PYTHON_CROCODDYL_MULTIBODY_COSTS_STATE_HPP_

#include "crocoddyl/multibody/costs/state.hpp"

namespace crocoddyl {
namespace python {

namespace bp = boost::python;

void exposeCostState() {
  bp::class_<CostModelState, bp::bases<CostModelAbstract> >(
      "CostModelState", bp::init<pinocchio::Model*, StateAbstract*, ActivationModelAbstract*, Eigen::VectorXd, int>(
                            bp::args(" self", " model", " state", " activation", " xref", " nu=model.nv"),
                            "Initialize the state cost model.\n\n"
                            ":param model: Pinocchio model of the multibody system\n"
                            ":param state: state model\n"
                            ":param activation: activation model\n"
                            ":param xref: reference state\n"
                            ":param nu: dimension of control vector")[bp::with_custodian_and_ward<1, 4>()])
      .def<void (CostModelState::*)(boost::shared_ptr<CostDataAbstract>&, const Eigen::VectorXd&,
                                    const Eigen::VectorXd&)>("calc", &CostModelState::calc_wrap,
                                                             bp::args(" self", " data", " x", " u=None"),
                                                             "Compute the state cost.\n\n"
                                                             ":param data: cost data\n"
                                                             ":param x: time-discrete state vector\n"
                                                             ":param u: time-discrete control input")
      .def<void (CostModelState::*)(boost::shared_ptr<CostDataAbstract>&, const Eigen::VectorXd&)>(
          "calc", &CostModelState::calc_wrap, bp::args(" self", " data", " x"))
      .def<void (CostModelState::*)(boost::shared_ptr<CostDataAbstract>&, const Eigen::VectorXd&,
                                    const Eigen::VectorXd&, const bool&)>(
          "calcDiff", &CostModelState::calcDiff_wrap, bp::args(" self", " data", " x", " u=None", " recalc=True"),
          "Compute the derivatives of the state cost.\n\n"
          ":param data: action data\n"
          ":param x: time-discrete state vector\n"
          ":param u: time-discrete control input\n"
          ":param recalc: If true, it updates the state evolution and the cost value.")
      .def<void (CostModelState::*)(boost::shared_ptr<CostDataAbstract>&, const Eigen::VectorXd&,
                                    const Eigen::VectorXd&)>("calcDiff", &CostModelState::calcDiff_wrap,
                                                             bp::args(" self", " data", " x", " u"))
      .def<void (CostModelState::*)(boost::shared_ptr<CostDataAbstract>&, const Eigen::VectorXd&)>(
          "calcDiff", &CostModelState::calcDiff_wrap, bp::args(" self", " data", " x"))
      .def<void (CostModelState::*)(boost::shared_ptr<CostDataAbstract>&, const Eigen::VectorXd&, const bool&)>(
          "calcDiff", &CostModelState::calcDiff_wrap, bp::args(" self", " data", " x", " recalc"));
}

}  // namespace python
}  // namespace crocoddyl

#endif  // PYTHON_CROCODDYL_MULTIBODY_COSTS_STATE_HPP_