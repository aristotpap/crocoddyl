///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (C) 2019-2023, LAAS-CNRS, University of Edinburgh, IRI: CSIC-UPC
//                          Heriot-Watt University
// Copyright note valid unless otherwise stated in individual files.
// All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#include "crocoddyl/multibody/actuations/multicopter-base.hpp"

#include "python/crocoddyl/multibody/multibody.hpp"
#include "python/crocoddyl/utils/copyable.hpp"

namespace crocoddyl {
namespace python {

void exposeActuationModelMultiCopterBase() {
  bp::register_ptr_to_python<
      std::shared_ptr<crocoddyl::ActuationModelMultiCopterBase> >();

  bp::class_<ActuationModelMultiCopterBase, bp::bases<ActuationModelAbstract> >(
      "ActuationModelMultiCopterBase",
      "Actuation models with base actuated by several propellers (e.g. aerial "
      "manipulators).",
      bp::init<std::shared_ptr<StateMultibody>,
               Eigen::Matrix<double, 6, Eigen::Dynamic> >(
          bp::args("self", "state", "tau_f"),
          "Initialize the full actuation model.\n\n"
          ":param state: state of multibody system\n"
          ":param tau_f: matrix that maps rotors thrust to generalized torque "
          "of the flying base."))
      .def(bp::init<std::shared_ptr<StateMultibody>, std::size_t,
                    Eigen::Matrix<double, 6, Eigen::Dynamic> >(
          bp::args("self", "state", "nrotors", "tau_f"),
          "Initialize the full actuation model.\n\n"
          ":param state: state of multibody system, \n"
          ":param nrotors: number of rotors of the flying base, \n"
          ":param tau_f: matrix that maps rotors thrust to generalized torque "
          "of the flying base."))
      .def<void (ActuationModelMultiCopterBase::*)(
          const std::shared_ptr<ActuationDataAbstract>&,
          const Eigen::Ref<const Eigen::VectorXd>&,
          const Eigen::Ref<const Eigen::VectorXd>&)>(
          "calc", &ActuationModelMultiCopterBase::calc,
          bp::args("self", "data", "x", "u"),
          "Compute the actuation signal and actuation set from the joint "
          "torque input u.\n\n"
          ":param data: multicopter-base actuation data\n"
          ":param x: state point (dim. state.nx)\n"
          ":param u: joint torque input (dim. nu)")
      .def("calcDiff", &ActuationModelMultiCopterBase::calcDiff,
           bp::args("self", "data", "x", "u"),
           "Compute the derivatives of the actuation model.\n\n"
           "It computes the partial derivatives of the full actuation. It "
           "assumes that calc\n"
           "has been run first. The reason is that the derivatives are "
           "constant and\n"
           "defined in createData. The Hessian is constant, so we don't write "
           "again this value.\n"
           ":param data: multicopter-base actuation data\n"
           ":param x: state point (dim. state.nx)\n"
           ":param u: joint torque input (dim. nu)")
      .def("commands", &ActuationModelMultiCopterBase::commands,
           bp::args("self", "data", "x", "tau"),
           "Compute the joint torque commands from the generalized torques.\n\n"
           "It stores the results in data.u.\n"
           ":param data: actuation data\n"
           ":param x: state point (dim. state.nx)\n"
           ":param tau: generalized torques (dim state.nv)")
      .def("torqueTransform", &ActuationModelMultiCopterBase::torqueTransform,
           bp::args("self", "data", "x", "tau"),
           "Compute the torque transform from generalized torques to joint "
           "torque inputs.\n\n"
           "It stores the results in data.Mtau.\n"
           ":param data: actuation data\n"
           ":param x: state point (dim. state.nx)\n"
           ":param tau: generalized torques (dim state.nv)")
      .def("createData", &ActuationModelMultiCopterBase::createData,
           bp::args("self"),
           "Create the multicopter-base actuation data.\n\n"
           "Each actuation model (AM) has its own data that needs to be "
           "allocated.\n"
           "This function returns the allocated data for a predefined AM.\n"
           ":return AM data.")
      .add_property(
          "nrotors",
          bp::make_function(&ActuationModelMultiCopterBase::get_nrotors),
          "Number of rotors in the flying base")
      .add_property(
          "tauf",
          bp::make_function(&ActuationModelMultiCopterBase::get_tauf,
                            bp::return_value_policy<bp::return_by_value>()),
          bp::make_function(&ActuationModelMultiCopterBase::set_tauf),
          "Matrix mapping from thrusts to body torque")
      .def(CopyableVisitor<ActuationModelMultiCopterBase>());
}

}  // namespace python
}  // namespace crocoddyl
