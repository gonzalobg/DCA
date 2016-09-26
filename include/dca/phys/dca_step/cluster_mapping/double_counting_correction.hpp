// Copyright (C) 2009-2016 ETH Zurich
// Copyright (C) 2007?-2016 Center for Nanophase Materials Sciences, ORNL
// All rights reserved.
//
// See LICENSE.txt for terms of usage.
// See CITATION.txt for citation guidelines if you use this code for scientific publications.
//
// Author: Peter Staar (taa@zurich.ibm.com)
//         Andrei Plamada (plamada@itp.phys.ethz.ch)
//
// Description

#ifndef DCA_PHYS_DCA_STEP_CLUSTER_MAPPING_DOUBLE_COUNTING_CORRECTION_HPP
#define DCA_PHYS_DCA_STEP_CLUSTER_MAPPING_DOUBLE_COUNTING_CORRECTION_HPP

#include <vector>

#include "comp_library/function_library/include_function_library.h"
#include "phys_library/domains/cluster/cluster_domain.h"
#include "phys_library/domains/Quantum_domain/electron_band_domain.h"
#include "phys_library/domains/Quantum_domain/electron_spin_domain.h"
#include "phys_library/domains/time_and_frequency/frequency_domain.h"

namespace dca {
namespace phys {
// dca::phys::

template <typename parameters_type, typename MOMS_type>
class double_counting_correction {
public:
  using concurrency_type = typename parameters_type::concurrency_type;

  using w = dmn_0<frequency_domain>;
  using b = dmn_0<electron_band_domain>;
  using s = dmn_0<electron_spin_domain>;
  using nu = dmn_variadic<b, s>;  // orbital-spin index

  using DCA_k_cluster_type = cluster_domain<double, parameters_type::lattice_type::DIMENSION,
                                            CLUSTER, MOMENTUM_SPACE, BRILLOUIN_ZONE>;
  using k_DCA = dmn_0<DCA_k_cluster_type>;

public:
  double_counting_correction(parameters_type& parameters_ref, MOMS_type& MOMS_ref);

  void initialize();

  void execute_before_solver();

  void execute_after_solver();

private:
  parameters_type& parameters;
  concurrency_type& concurrency;

  MOMS_type& MOMS;

  FUNC_LIB::function<double, nu> mu_HALF;
  FUNC_LIB::function<double, nu> DC;
};

template <typename parameters_type, typename MOMS_type>
double_counting_correction<parameters_type, MOMS_type>::double_counting_correction(
    parameters_type& parameters_ref, MOMS_type& MOMS_ref)
    : parameters(parameters_ref),
      concurrency(parameters.get_concurrency()),

      MOMS(MOMS_ref),

      mu_HALF("mu_HALF"),
      DC("DC") {
  initialize();
}

template <typename parameters_type, typename MOMS_type>
void double_counting_correction<parameters_type, MOMS_type>::initialize() {
  const std::vector<int>& interacting_bands = parameters.get_interacting_bands();

  for (int b_i_int = 0; b_i_int < interacting_bands.size(); b_i_int++) {
    int b_i = interacting_bands[b_i_int];

    for (int s_i = 0; s_i < s::dmn_size(); s_i++) {
      for (int b_j_int = 0; b_j_int < interacting_bands.size(); b_j_int++) {
        int b_j = interacting_bands[b_j_int];

        for (int s_j = 0; s_j < s::dmn_size(); s_j++)
          mu_HALF(b_i, s_i) += (1. / 2.) * (MOMS.H_interactions(b_j, s_j, b_i, s_i, 0) +
                                            MOMS.H_interactions(b_i, s_i, b_j, s_j, 0)) *
                               1. / 2.;
      }
    }
  }

  if (parameters.get_double_counting_method() == "constant-correction-without-U-correction")
    for (int b_ind = 0; b_ind < interacting_bands.size(); b_ind++)
      for (int s_ind = 0; s_ind < s::dmn_size(); s_ind++)
        DC(interacting_bands[b_ind], s_ind) =
            parameters.get_double_counting_correction();  //-mu_HALF(interacting_bands[b_ind],s_ind);

  if (parameters.get_double_counting_method() == "constant-correction-with-U-correction")
    for (int b_ind = 0; b_ind < interacting_bands.size(); b_ind++)
      for (int s_ind = 0; s_ind < s::dmn_size(); s_ind++)
        DC(interacting_bands[b_ind], s_ind) =
            parameters.get_double_counting_correction() - mu_HALF(interacting_bands[b_ind], s_ind);
}

template <typename parameters_type, typename MOMS_type>
void double_counting_correction<parameters_type, MOMS_type>::execute_before_solver() {
  if (parameters.get_double_counting_method() != "none") {
    const std::vector<int>& interacting_bands = parameters.get_interacting_bands();

    if (parameters.get_double_counting_method() == "constant-correction-with-U-correction" or
        parameters.get_double_counting_method() == "constant-correction-without-U-correction") {
      for (int b_ind = 0; b_ind < interacting_bands.size(); b_ind++)
        for (int s_ind = 0; s_ind < s::dmn_size(); s_ind++)
          for (int k_ind = 0; k_ind < k_DCA::dmn_size(); k_ind++)
            for (int w_ind = 0; w_ind < w::dmn_size(); w_ind++)
              MOMS.Sigma_cluster(interacting_bands[b_ind], s_ind, interacting_bands[b_ind], s_ind,
                                 k_ind, w_ind) += DC(interacting_bands[b_ind], s_ind);
    }
  }
}

template <typename parameters_type, typename MOMS_type>
void double_counting_correction<parameters_type, MOMS_type>::execute_after_solver() {
  if (parameters.get_double_counting_method() != "none") {
    const std::vector<int>& interacting_bands = parameters.get_interacting_bands();

    if (parameters.get_double_counting_method() == "constant-correction-with-U-correction" or
        parameters.get_double_counting_method() == "constant-correction-without-U-correction") {
      for (int b_ind = 0; b_ind < interacting_bands.size(); b_ind++)
        for (int s_ind = 0; s_ind < s::dmn_size(); s_ind++)
          for (int k_ind = 0; k_ind < k_DCA::dmn_size(); k_ind++)
            for (int w_ind = 0; w_ind < w::dmn_size(); w_ind++)
              MOMS.Sigma(interacting_bands[b_ind], s_ind, interacting_bands[b_ind], s_ind, k_ind,
                         w_ind) -= DC(interacting_bands[b_ind], s_ind);
    }
  }
}

}  // phys
}  // dca

#endif  // DCA_PHYS_DCA_STEP_CLUSTER_MAPPING_DOUBLE_COUNTING_CORRECTION_HPP
