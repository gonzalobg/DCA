// Copyright (C) 2009-2016 ETH Zurich
// Copyright (C) 2007?-2016 Center for Nanophase Materials Sciences, ORNL
// All rights reserved.
//
// See LICENSE.txt for terms of usage.
// See CITATION.txt for citation guidelines if you use this code for scientific publications.
//
// Author: Giovanni Balduzzi (gbalduzz@itp.phys.ethz.ch)
//         Jérémie Bouquet (bouquetj@gmail.com).
//
//

#include "dca/phys/dca_step/cluster_solver/ctint/walker/tools/d_matrix_builder.hpp"

#include "dca/linalg/make_constant_view.hpp"
#include "dca/linalg/matrix_view.hpp"
#include "dca/phys/dca_step/cluster_solver/ctint/walker/tools/kernels_interface.hpp"
#include "dca/phys/dca_step/cluster_solver/ctint/device_memory/global_memory_manager.hpp"

namespace dca {
namespace phys {
namespace solver {
namespace ctint {
// dca::phys::solver::ctint::

using linalg::CPU;
using linalg::GPU;

DMatrixBuilder<CPU>::DMatrixBuilder(const G0Interpolation<CPU>& g0,
                                    const linalg::Matrix<int, linalg::CPU>& site_diff,
                                    const std::vector<int>& sbdm_step,
                                    const std::array<double, 3>& alphas)
    : g0_ref_(g0),
      alpha_1_(alphas[0]),
      alpha_2_(alphas[1]),
      alpha_3_(alphas[2]),
      n_bands_(sbdm_step[1]),
      sbdm_step_(sbdm_step),
      site_diff_(site_diff) {
  assert(sbdm_step.size() == 3);
}

void DMatrixBuilder<CPU>::buildSQR(MatrixPair& S, MatrixPair& Q,
                                   MatrixPair& R,
                                   const SolverConfiguration<linalg::CPU>& config) const {
  std::array<int, 2> size_increase = config.sizeIncrease();

  for (int s = 0; s < 2; ++s) {
    const int delta = size_increase[s];
    const Sector& sector = config.getSector(s);
    const int n = sector.size() - delta;

    Q[s].resizeNoCopy(std::make_pair(n, delta));
    R[s].resizeNoCopy(std::make_pair(delta, n));
    S[s].resizeNoCopy(std::make_pair(delta, delta));

    for (int j = 0; j < delta; j++)
      for (int i = 0; i < n; i++)
        Q[s](i, j) = computeD(i, n + j, sector);
    for (int j = 0; j < n; j++)
      for (int i = 0; i < delta; i++)
        R[s](i, j) = computeD(i + n, j, sector);
    for (int j = 0; j < delta; j++)
      for (int i = 0; i < delta; i++)
        S[s](i, j) = computeD(n + i, n + j, sector);
  }
}

double DMatrixBuilder<CPU>::computeD(const int i, const int j, const Sector& configuration) const {
  assert(configuration.size() > i and configuration.size() > j);

  auto alphaField = [&](const int type) {
    switch (std::abs(type)) {
      case 1:
        return type < 0 ? (0.5 + alpha_1_) : (0.5 - alpha_1_);
      case 2:
        return type < 0 ? (0.5 + alpha_2_) : (0.5 - alpha_2_);
      case 3:
        return type < 0 ? alpha_3_ : -alpha_3_;
      default:
        throw(std::logic_error("type not recognized."));
    }
  };

  const int b1 = configuration.getLeftB(i);
  const int b2 = configuration.getRightB(j);
  const int delta_r = site_diff_(configuration.getLeftR(i), configuration.getRightR(j));
  const int p_index = label(b1, b2, delta_r);
  const double delta_tau = configuration.getTau(i) - configuration.getTau(j);
  const double g0_val = g0_ref_(delta_tau, p_index);
  if (i == j)
    return g0_val - alphaField(configuration.getAuxFieldType(i));
  else
    return g0_val;
}

int DMatrixBuilder<CPU>::label(const int b1, const int b2, const int r) const {
  return b1 + b2 * sbdm_step_[1] + r * sbdm_step_[2];
}


double DMatrixBuilder<CPU>::computeAlpha(const int aux_spin_type) const {
  switch (std::abs(aux_spin_type)) {
    case 1:
      return aux_spin_type < 0 ? (0.5 + alpha_1_) : (0.5 - alpha_1_);
    case 2:
      return aux_spin_type < 0 ? (0.5 + alpha_2_) : (0.5 - alpha_2_);
    case 3:
      return aux_spin_type < 0 ? alpha_3_ : -alpha_3_;
    default:
      throw(std::logic_error("type not recognized."));
  }
}

double DMatrixBuilder<CPU>::computeDSubmatrix(const int i, const int j, const Sector& configuration) const {
  assert(configuration.size() > i and  configuration.size() > j);

  const int b1 = configuration.getLeftB(i);
  const int b2 = configuration.getRightB(j);
  const int delta_r = site_diff_(configuration.getLeftR(i), configuration.getRightR(j));
  const int p_index = label(b1, b2, delta_r);
  const double delta_tau = configuration.getTau(i) - configuration.getTau(j);
  const double g0_val = g0_ref_(delta_tau, p_index);
  if (i == j)
    return computeF(computeAlpha(configuration.getAuxFieldType(i))) -
           g0_val * (computeF(computeAlpha(configuration.getAuxFieldType(j))) - 1);
  else
    return - g0_val * (computeF(computeAlpha(configuration.getAuxFieldType(j))) - 1);
}

double DMatrixBuilder<CPU>::computeF(const double alpha) const {
  return alpha / (alpha - 1);
}

double DMatrixBuilder<CPU>::computeF(const int i, const Sector& configuration) const {
  return computeF(computeAlpha(configuration.getAuxFieldType(i)));
}

double DMatrixBuilder<CPU>::computeF(const int aux_spin_type) const {
  if (aux_spin_type == 0)
    return 1;
  else
    return computeF(computeAlpha(aux_spin_type));
}

double DMatrixBuilder<CPU>::computeGamma(const int aux_spin_type, const int new_aux_spin_type) const {
  return (computeF(new_aux_spin_type) - computeF(aux_spin_type)) / computeF(aux_spin_type);
}

double DMatrixBuilder<CPU>::computeG(const int i, const int j, const Sector& configuration, const Matrix& M) const {
  double result = 0;
  int b1, b2, delta_r, p_index;
  double delta_tau, g0_val;

  for (int k = 0; k < M.size().first; ++k) {
    b1 = configuration.getLeftB(k);
    b2 = configuration.getRightB(j);
    delta_r = site_diff_(configuration.getLeftR(k), configuration.getRightR(j));
    p_index = label(b1, b2, delta_r);
    delta_tau = configuration.getTau(k) - configuration.getTau(j);
    g0_val = g0_ref_(delta_tau, p_index);

    result += M(i,k) * g0_val;
  }

  return result;
}

//Compute G with fastest formula. Works only when auxilliary spin at index j is not zero.

double DMatrixBuilder<CPU>::computeGFast(const int i, const int j, const int aux_spin_type, const double M_ij) const {
  double f = computeF(aux_spin_type);

  return (M_ij * f - int(i==j)) / (f - 1);
}

double DMatrixBuilder<CPU>::computeG0(const int i, const int j, const Sector& configuration) const {
  int b1 = configuration.getLeftB(i);
  int b2 = configuration.getRightB(j);
  int delta_r = site_diff_(configuration.getLeftR(i), configuration.getRightR(j));
  int p_index = label(b1, b2, delta_r);
  double delta_tau = configuration.getTau(i) - configuration.getTau(j);
  double g0_val = g0_ref_(delta_tau, p_index);

  return g0_val;
}


void DMatrixBuilder<CPU>::computeG0Init(Matrix& G0, const Sector& configuration, const int n_init, const int n_max) const {
  int b_i, b_j, r_i, r_j;
  double tau_i, tau_j;

  G0.resize(n_max);

  for (int i = 0; i < n_init; ++i) {
    b_i = configuration.getLeftB(i);
    tau_i = configuration.getTau(i);
    r_i = configuration.getLeftR(i);

    for (int j = n_init; j < n_max; ++j) {
      b_j = configuration.getRightB(j);
      tau_j = configuration.getTau(j);
      r_j = configuration.getRightR(j);

      G0(i,j) = g0_ref_(tau_i - tau_j, label(b_i, b_j, site_diff_(r_i, r_j)));
    }
  }

  for (int i = n_init; i < n_max; ++i) {
    b_i = configuration.getLeftB(i);
    tau_i = configuration.getTau(i);
    r_i = configuration.getLeftR(i);

    for (int j = 0; j < n_max; ++j) {
      b_j = configuration.getRightB(j);
      tau_j = configuration.getTau(j);
      r_j = configuration.getRightR(j);

      G0(i,j) = g0_ref_(tau_i - tau_j, label(b_i, b_j, site_diff_(r_i, r_j)));
    }
  }
}

//Compute only the parts of G0 required at a given moment. (Re)Computing every element is not needed in most situations.
  
void DMatrixBuilder<CPU>::computeG0(Matrix& G0, const Sector& configuration, const int n_init, const int n_max, const int which_section) const {
  int b_i, b_j, r_i, r_j;
  double tau_i, tau_j;

  if (which_section == 0) {
    //G0.resize(std::make_pair(n_max - n_init, n_init));

    for (int i = n_init; i < n_max; ++i) {
      b_i = configuration.getLeftB(i);
      tau_i = configuration.getTau(i);
      r_i = configuration.getLeftR(i);

      for (int j = 0; j < n_init; ++j) {
        b_j = configuration.getRightB(j);
        tau_j = configuration.getTau(j);
        r_j = configuration.getRightR(j);

        G0(i-n_init,j) = g0_ref_(tau_i - tau_j, label(b_i, b_j, site_diff_(r_i, r_j)));
      }
    }
  }

  else {
    //G0.resize(std::make_pair(n_max, n_max - n_init));

    for (int i = 0; i < n_max; ++i) {
      b_i = configuration.getLeftB(i);
      tau_i = configuration.getTau(i);
      r_i = configuration.getLeftR(i);

      for (int j = n_init; j < n_max; ++j) {
        b_j = configuration.getRightB(j);
        tau_j = configuration.getTau(j);
        r_j = configuration.getRightR(j);

        G0(i,j-n_init) = g0_ref_(tau_i - tau_j, label(b_i, b_j, site_diff_(r_i, r_j)));
      }
    }
  }
}

#ifdef DCA_HAVE_CUDA

DMatrixBuilder<linalg::GPU>::DMatrixBuilder(const G0Interpolation<GPU>& g0,
                                            const linalg::Matrix<int, linalg::CPU>& site_diff,
                                            const std::vector<int>& sbdm_step,
                                            const std::array<double, 3>& alpha)
    : BaseClass(g0.get_host_interpolation(), site_diff, sbdm_step, alpha), g0_ref_(g0) {
  assert(sbdm_step.size() == 3);

  ctint::GlobalMemoryManager::initializeCluster(*linalg::makeConstantView(site_diff), sbdm_step);
}

void DMatrixBuilder<linalg::GPU>::buildSQR(MatrixPair<linalg::GPU>& S, MatrixPair<linalg::GPU>& Q,
                                           MatrixPair<linalg::GPU>& R,
                                           SolverConfiguration<linalg::GPU>& config,
                                           int thread_id) const {
  std::array<int, 2> size_increase = config.sizeIncrease();

  for (int s = 0; s < 2; ++s) {
    const Sector& sector = config.getSector(s);
    const int delta = size_increase[s];
    const int n = sector.size() - delta;
    const auto stream = linalg::util::getStream(thread_id, s);

    config.upload(s, thread_id);
    assert(cudaDeviceSynchronize() == cudaSuccess);

    Q[s].resizeNoCopy(std::make_pair(n, delta));
    R[s].resizeNoCopy(std::make_pair(delta, n));
    S[s].resizeNoCopy(std::make_pair(delta, delta));

    using MatrixView = linalg::MatrixView<double, linalg::GPU>;
    assert(GlobalMemoryManager::isInitialized());
    details::computeD(MatrixView(Q[s]), MatrixView(R[s]), MatrixView(S[s]), n, delta, alpha_1_,
                      alpha_2_, alpha_3_, config.getDeviceData(s), g0_ref_, stream);

    assert(cudaDeviceSynchronize() == cudaSuccess);
  }
}

#endif  // DCA_HAVE_CUDA

}  // ctint
}  // solver
}  // phys
}  // dca