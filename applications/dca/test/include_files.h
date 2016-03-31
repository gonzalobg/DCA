// File: include_files.h

// Utilities library
#include <cstdlib>
#include <typeinfo>
#include <ctime>

// Numeric limits
#include <limits>

// Error handling
#include <stdexcept>
#include <cassert>

// Strings library
#include <cstring>

// Containers library
#include <vector>
#include <map>
#include <queue>

// Algorithms library
#include <algorithm>

// Numerics library
#include <cmath>
#include <complex>

// Input/output library
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>

// Parallelization libraries
#include <pthread.h>
// #include <omp.h>

// Deprecated libraries (<XXX.h> replaced by <cXXX>)
// #include <stdio.h>
// #include <math.h>
// #include <string.h>
// #include <stdlib.h>
// #include <assert.h>
// #include <time.h>

// Unused libaries
// #include <unistd.h>
// #include <dirent.h>

// #include <sys/resource.h>  // Placed into src/comp_library/profiler_library/events/time_file_name_changed.h
// #include <sys/time.h>      // Placed into performance_inspector_CPU.h and performance_inspector_GPU.h
// #include <bitset>          // Placed into advanced_fermionic_ed_type_definitions.h


// typelist-operations
#include "type_list.h"
#include "type_list_definitions.h"
using namespace TL;

// enumerations
#include "enumerations.hpp"

// BIT
const static bool QMC_INTEGRATOR_BIT = false;


// NFFT <--> DFT
const static bool DO_NFFT = true;


// blas/lapack
#include "comp_library/blas_lapack_plans/blas_lapack_plans.hpp"
#include "comp_library/linalg/linalg.hpp"

// various
#include "static_functions.h"
#include "include_symmetry_library.h"
//#include "statistical_methods.h"

// include generic-algorithms
// #include "generic_assert.h"
#include "include_generic_methods.h"

// include function-library
#include "include_function_library.h"

// IO-library
#include "include_IO_operations.h"

// include plotting
#include "include_plotting.h"

// random number generator
#include "include_random_number_generator.h"

// include block-matrix operations
//#include "include_blocked_blas_calls.h"

// parallelization
#include "include_parallelization_library.h"

// profiling
#include "include_profiling.h"

#include "include_math_library.h"

// include domains
#include "include_DCA_domains.h"
// #include "numerical_error_domain.h"
// #include "DCA_iteration_domain.h"
// #include "Feynman_expansion_order_domain.h"
// #include "electron_band_domain.h"
// #include "electron_spin_domain.h"
// #include "HS_spin_domain.h"
// #include "HS_field_sign_domain.h"
// #include "particle_number_domain.h"
// #include "brillouin_zone_cut_domain.h"
// #include "Brillouin_zone_cut.h"
// #include "legendre_domain.h"
// #include "point_group_operation_dmn.h"
// #include "time_domain.h"
// #include "time_domain_left_oriented.h"
// #include "frequency_domain.h"
// #include "frequency_domain_real_axis.h"
// #include "frequency_domain_imag_axis.h"
// #include "frequency_domain_compact.h"

// type-dependent-conversions
#include "convert_DCA_types_to_index.h"

// include models
#include "include_Hamiltonians.h"
// #include "dft_model.h"
// #include "Koshevnikov_model.h"

// include algorithms
#include "include_symmetries.h"
// #include "include_tetrahedron_mesh.h"
// #include "include_symmetries.h"
#include "compute_band_structure.h"
// #include "adjust_chemical_potential.h"

#include "include_DCA_steps.h"

// include parameters
#include "include_Parameters.h"

#include "include_DCA+_data.h"

// #include "include_DCA_steps.h"

#include "include_cluster_solver.h"

#include "include_DCA+_loop.h"

// include CPE
//#include "include_CPE.h"

// include ED
//#include "include_ed.h"

// include SE
//#include "include_series_expansion.h"

// analysis
#include "include_analysis.h"
