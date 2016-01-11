//-*-C++-*-

namespace COMP_LIB
{
  enum PARALLELIZATION_LIBRARY_NAMES {SERIAL_LIBRARY, POSIX_LIBRARY, OMP_LIBRARY, MPI_LIBRARY};
}

#include "interfaces/type_map_interface.h"

#include "interfaces/processor_grouping_interface.h"

#include "interfaces/packing_interface.h"

#include "interfaces/RNG_interface.h"

#include "interfaces/collective_min_interface.h"
#include "interfaces/collective_max_interface.h"
#include "interfaces/collective_sum_interface.h"

#include "interfaces/print_on_shell_interface.h"

#include "parallelization_template.h"

// MPI
#include <mpi.h>

#include "interfaces/type_map_interface_mpi.h"

#include "interfaces/processor_grouping_interface_mpi.h"

#include "interfaces/packing_interface_mpi.h"
#include "interfaces/collective_sum_interface_mpi.h"

#include "interfaces/collective_min_interface_mpi.h"
#include "interfaces/collective_max_interface_mpi.h"
#include "interfaces/collective_sum_interface_mpi.h"

#include "parallelization_mpi.h"

// POSIX

#include <pthread.h>

#include "interfaces/collective_sum_interface_pthreads.h"

#include "interfaces/processor_grouping_interface_pthreads.h"

#include "parallelization_pthreads.h"

// thread-manager

#include "thread_manager_sum.h"
