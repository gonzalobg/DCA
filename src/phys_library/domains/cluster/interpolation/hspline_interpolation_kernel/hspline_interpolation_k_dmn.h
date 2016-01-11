//-*-C++-*-

#ifndef HERMITE_SPLINE_INTERPOLATION_KERNEL_K_DMN_H
#define HERMITE_SPLINE_INTERPOLATION_KERNEL_K_DMN_H

/*!
 *  \ingroup INTERPOLATION
 *
 *  \author  Peter Staar
 *  \brief   This class implements a Hermite spline interpolation technique in momentum space.
 */
template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
class hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t> 
{
  const static int N_delta = 3;

  typedef k_cluster<cluster_representation, base_cluster_type> k_cluster_type;

  const static int DIMENSION = k_cluster<cluster_representation, base_cluster_type>::DIMENSION;

  typedef k_cluster<cluster_representation, base_cluster_type> source_k_dmn_t;
  typedef r_cluster<cluster_representation, base_cluster_type> source_r_dmn_t;

public:

  hspline_interpolation_kernel();
  hspline_interpolation_kernel(double A);

  ~hspline_interpolation_kernel();

  void reset();

  scalartype* get_interpolation_matrix();

  void set_dense_interpolation_matrix();
  void get_dense_interpolation_matrix(std::vector<int>& col_index, scalartype*& I_ptr);

  void execute(scalartype* input, scalartype* output);

  void execute(scalartype* input, scalartype* output, int n);

  void execute_on_transpose(scalartype* input, scalartype* output, int n);

private:

  void resize_k0_indices();

  void delete_data_structures();
  void allocate_data_structures();

  void find_neighbours();

  void find_basis();
  void find_super_basis();

  void find_k_vecs();
  void find_k_indices();

  double evaluate_hermite_kernel(double x);
  double evaluate_hermite_kernel_at(std::vector<double>& k_vec);

  void generate_k0_indices(std::vector<double> k_vec);

  void construct_interpolation_matrix();
  void construct_interpolation_matrix_fast();

  static double volume(double* b0, double* b1);
  static double volume(double* b0, double* b1, double* b);

  static void coordinates(double* b0, double* b1,             double* r, double* x); 
  static void coordinates(double* b0, double* b1, double* b2, double* r, double* x); 

private:

  double a;

  int N_s;
  int N_k;

  std::vector<std::vector<double> > neighbours;

  double k_basis    [DIMENSION*DIMENSION];
  double k_basis_inv[DIMENSION*DIMENSION];

  double k_super_basis    [DIMENSION*DIMENSION];
  double k_super_basis_inv[DIMENSION*DIMENSION];

  double* k_vecs_target;
  double* k_vecs_source;
  double* k_vecs_affine;

  double*     k_vecs;
  double*     k_vecs_index;

  std::vector<int> k0_indices;

  scalartype* interpolation_matrix;

  std::vector<int> col_indices;
  scalartype*      interpolation_matrix_dense;
};

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::hspline_interpolation_kernel():
  a(-0.5),

  N_s(k_cluster_type::get_size()),
  N_k(target_k_dmn_t::get_size()),

  neighbours(0),

  k_vecs_target(NULL),
  k_vecs_source(NULL),
  k_vecs_affine(NULL),

  k_vecs(NULL),
  k_vecs_index(NULL),

  k0_indices(0),

  interpolation_matrix(NULL),

  col_indices(0),
  interpolation_matrix_dense(NULL)
{
  resize_k0_indices();

  find_neighbours();

  find_basis();
  find_super_basis();

  find_k_vecs();
  find_k_indices();

  construct_interpolation_matrix();
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::hspline_interpolation_kernel(double A):
  a(A),

  N_s(k_cluster_type::get_size()),
  N_k(target_k_dmn_t::get_size()),

  neighbours(0),

  k_vecs_target(NULL),
  k_vecs_source(NULL),
  k_vecs_affine(NULL),

  k_vecs(NULL),
  k_vecs_index(NULL),

  k0_indices(0),

  interpolation_matrix(NULL),

  col_indices(0),
  interpolation_matrix_dense(NULL)
{
  resize_k0_indices();

  allocate_data_structures();

  find_neighbours();

  find_basis();
  find_super_basis();

  find_k_vecs();
  find_k_indices();

  //construct_interpolation_matrix();
  
  construct_interpolation_matrix_fast();
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::~hspline_interpolation_kernel()
{
  delete_data_structures();
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::resize_k0_indices()
{
  int n = 1;
  
  for(int d=0; d<DIMENSION; ++d)
    n *= (2*N_delta+1);
  
  k0_indices.resize(n);
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::delete_data_structures()
{
  delete [] k_vecs_source;
  delete [] k_vecs_target;
  delete [] k_vecs_affine;
  
  delete [] k_vecs;
  delete [] k_vecs_index;
  delete [] interpolation_matrix;

  if(interpolation_matrix_dense != NULL) delete [] interpolation_matrix_dense;
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::allocate_data_structures()
{
  N_s = k_cluster_type::get_size();
  N_k = target_k_dmn_t::get_size();
  
  k_vecs_target = new double[DIMENSION*N_k];
  k_vecs_source = new double[DIMENSION*N_k];
  k_vecs_affine = new double[DIMENSION*N_k];
  
  k_vecs       = new double[DIMENSION*N_k];
  k_vecs_index = new double[DIMENSION*N_k];
  
  interpolation_matrix = new scalartype[N_s*N_k];
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::reset()
{
  if(N_k != target_k_dmn_t::get_size()){
    delete_data_structures();
    allocate_data_structures();
  }

  find_k_vecs();
  find_k_indices();

  //construct_interpolation_matrix();
  
  construct_interpolation_matrix_fast();
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
scalartype* hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::get_interpolation_matrix()
{
  return interpolation_matrix;
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::execute(scalartype* input, 
															     scalartype* output)
{
  gemm_plan<scalartype> gemm(target_k_dmn_t::get_size(), source_k_dmn_t::get_size(), 1.);
    
  gemm.A = interpolation_matrix;
  gemm.B = input;
  gemm.C = output;
    
  gemm.execute_plan();
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::execute(scalartype* input, 
															     scalartype* output,
															     int n)
{
  gemm_plan<scalartype> gemm(target_k_dmn_t::get_size(), source_k_dmn_t::get_size(), n);
  
  gemm.A = interpolation_matrix;
  gemm.B = input;
  gemm.C = output;

  gemm.execute_plan();
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::execute_on_transpose(scalartype* input, scalartype* output, int n)
{
  gemm_plan<scalartype> gemm(n, source_k_dmn_t::get_size(), target_k_dmn_t::get_size());
  
  gemm.TRANSA = 'N';
  gemm.TRANSB = 'T';

  gemm.LDA = n;
  gemm.LDB = target_k_dmn_t::get_size();
  gemm.LDC = n;

  gemm.A = input;
  gemm.B = interpolation_matrix;
  gemm.C = output;

  gemm.execute_plan();
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::set_dense_interpolation_matrix()
{
  int N_k_source = source_k_dmn_t::get_size();
  int N_k_target = target_k_dmn_t::get_size();

  col_indices.resize(0);
  
  for(int j=0; j<N_k_source; ++j){
    
    bool col_is_zero=true;

    for(int i=0; i<N_k_target; ++i)
      if(abs_value(interpolation_matrix[i+j*N_k_target])>1.e-6)
	col_is_zero=false;

    if(not col_is_zero)
      col_indices.push_back(j);
  }

  if(interpolation_matrix_dense != NULL) 
    delete [] interpolation_matrix_dense;

  int Nc = col_indices.size();

  interpolation_matrix_dense = new scalartype[N_k_target*Nc];

  for(int j=0; j<Nc; ++j)
    memcpy(&interpolation_matrix_dense[N_k_target*j], &interpolation_matrix[N_k_target*col_indices[j]], sizeof(scalartype)*N_k_target);
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::get_dense_interpolation_matrix(std::vector<int>& col_index, 
																		    scalartype*&      I_ptr)
{
  col_index = col_indices;
  
  I_ptr = interpolation_matrix_dense;
}


template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::find_neighbours()
{
  neighbours.resize(0);

  neighbours = tetrahedron_neighbour_domain<k_cluster_type>::get_elements();

//   tetrahedron_mesh<k_cluster_type> tet_mesh(1);
//   neighbours.resize(0);
//   for(size_t f_ind=0; f_ind<tet_mesh.get_facets().size(); ++f_ind){    
//     std::vector<double> k(DIMENSION,0.);    
//     for(size_t k_ind=0; k_ind<tet_mesh.get_facets()[f_ind].index.size(); ++k_ind)
//       k = VECTOR_OPERATIONS::ADD(k, tet_mesh.get_simplices()[tet_mesh.get_facets()[f_ind].index[k_ind]].k_vec);
//     neighbours.push_back(k);
//   }
//   assert(neighbours.size() == tet_mesh.get_facets().size());
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::find_basis()
{
  for(int d0=0; d0<DIMENSION; ++d0)
    for(int d1=0; d1<DIMENSION; ++d1)
      k_basis[d1+d0*DIMENSION] = source_k_dmn_t::get_super_basis_vectors()[d0][d1];

  {
    invert_plan<double> invert_pln(DIMENSION);
    memcpy(invert_pln.Matrix, k_basis             , sizeof(double)*DIMENSION*DIMENSION);
    invert_pln.execute_plan();
    memcpy(k_basis_inv, invert_pln.inverted_matrix, sizeof(double)*DIMENSION*DIMENSION);
  }

  for(int d0=0; d0<DIMENSION; ++d0)
    for(int d1=0; d1<DIMENSION; ++d1)
      k_basis[d1+d0*DIMENSION] = source_k_dmn_t::get_super_basis_vectors()[d0][d1];
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::find_super_basis()
{
  for(int d0=0; d0<DIMENSION; ++d0)
    for(int d1=0; d1<DIMENSION; ++d1)
      k_super_basis[d1+d0*DIMENSION] = source_k_dmn_t::get_basis_vectors()[d0][d1];

  {
    invert_plan<double> invert_pln(DIMENSION);
    memcpy(invert_pln.Matrix, k_super_basis             , sizeof(double)*DIMENSION*DIMENSION);
    invert_pln.execute_plan();
    memcpy(k_super_basis_inv, invert_pln.inverted_matrix, sizeof(double)*DIMENSION*DIMENSION);
  }

  for(int d0=0; d0<DIMENSION; ++d0)
    for(int d1=0; d1<DIMENSION; ++d1)
      k_super_basis[d1+d0*DIMENSION] = source_k_dmn_t::get_basis_vectors()[d0][d1];
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::find_k_vecs()
{
  for(int l=0; l<target_k_dmn_t::get_size(); ++l)
    for(int d=0; d<DIMENSION; ++d)
      k_vecs_target[d+l*DIMENSION] = target_k_dmn_t::get_elements()[l][d];

  {
    gemm_plan<double> gemm(DIMENSION, DIMENSION, target_k_dmn_t::get_size());
    
    gemm.A = k_basis_inv;
    gemm.B = k_vecs_target;
    gemm.C = k_vecs_source;

    gemm.execute_plan();
  }

  for(int l=0; l<target_k_dmn_t::get_size(); ++l){
    for(int d=0; d<DIMENSION; ++d){

      while(k_vecs_source[d+l*DIMENSION] > 1.-1.e-6)
	k_vecs_source[d+l*DIMENSION] -= 1.;

      while(k_vecs_source[d+l*DIMENSION] < -1.e-6)
	k_vecs_source[d+l*DIMENSION] += 1.;

      assert(k_vecs_source[d+l*DIMENSION] > 0.-1.e-6);
      assert(k_vecs_source[d+l*DIMENSION] < 1.+1.e-6);
    }
  }

  {
    gemm_plan<double> gemm(DIMENSION, DIMENSION, target_k_dmn_t::get_size());
    
    gemm.A = k_basis;
    gemm.B = k_vecs_source;
    gemm.C = k_vecs;

    gemm.execute_plan();
  }
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::find_k_indices()
{
  int N_k = target_k_dmn_t::get_size();

  {
    gemm_plan<double> gemm(DIMENSION, DIMENSION, N_k);
    
    gemm.A = k_super_basis_inv;
    gemm.B = k_vecs;
    gemm.C = k_vecs_affine;

    gemm.execute_plan();
  }

  for(int l=0; l<N_k; ++l)
    for(int d=0; d<DIMENSION; ++d)
      k_vecs_affine[d+l*DIMENSION] = floor(k_vecs_affine[d+l*DIMENSION]);

  {
    gemm_plan<double> gemm(DIMENSION, DIMENSION, N_k);
    
    gemm.A = k_super_basis;
    gemm.B = k_vecs_affine;
    gemm.C = k_vecs_index;

    gemm.execute_plan();
  }
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
inline double hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::volume(double* b0, double* b1)
{
  return (b0[0]*b1[1]-b0[1]*b1[0]);
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
inline double hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::volume(double* b0, double* b1, double* b2)
{
  return (-b0[2]*b1[1]*b2[0] + b0[1]*b1[2]*b2[0] + b0[2]*b1[0]*b2[1] - b0[0]*b1[2]*b2[1] - b0[1]*b1[0]*b2[2] + b0[0]*b1[1]*b2[2]);
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
inline void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::coordinates(double* b0, double* b1, 
																	double* r, double* x)
{
  double inv_det = 1./(b0[0]*b1[1]-b0[1]*b1[0]);

  x[0] =  b1[1]*r[0] - b1[0]*r[1];
  x[1] = -b0[1]*r[0] + b0[0]*r[1];

  x[0] *= inv_det;
  x[1] *= inv_det;
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
inline void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::coordinates(double* b0, double* b1, double* b2, 
																	double* r, double* x)
{
  double inv_det = 1./(-b0[2]*b1[1]*b2[0] + b0[1]*b1[2]*b2[0] + b0[2]*b1[0]*b2[1] - b0[0]*b1[2]*b2[1] - b0[1]*b1[0]*b2[2] + b0[0]*b1[1]*b2[2]);

  x[0] = (-b1[2]*b2[1] + b1[1]*b2[2])*r[0] + ( b1[2]*b2[0] - b1[0]*b2[2])*r[1] + (-b1[1]*b2[0] + b1[0]*b2[1])*r[2];
  x[1] = ( b0[2]*b2[1] - b0[1]*b2[2])*r[0] + (-b0[2]*b2[0] + b0[0]*b2[2])*r[1] + ( b0[1]*b2[0] - b0[0]*b2[1])*r[2];
  x[2] = (-b0[2]*b1[1] + b0[1]*b1[2])*r[0] + ( b0[2]*b1[0] - b0[0]*b1[2])*r[1] + (-b0[1]*b1[0] + b0[0]*b1[1])*r[2];

  x[0] *= inv_det;
  x[1] *= inv_det;
  x[2] *= inv_det;
}


template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
inline double hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::evaluate_hermite_kernel(double x)
{
  double absX = std::fabs(x);

  if(absX>2)
    return 0.;

  if(absX>1)
    return a*pow(absX,3)-5.*a*pow(absX,2)+8.*a*absX-4.*a;

  return (a+2.)*pow(absX,3)-(a+3.)*pow(absX,2)+1.;

  /*
  if(absX <= 1.)
    return (a+2)*pow(absX,3)-(a+3)*pow(absX,2)+1;

  if(absX > 1. and absX <= 2.)
    return a*pow(absX,3)-5.*a*pow(absX,2)+8*a*absX-4*a;

  return 0.;
  */
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
inline double hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::evaluate_hermite_kernel_at(std::vector<double>& k_vec)
{
  std::vector<double> x(DIMENSION,0);

  double count  = 0.;
  double result = 0.;

  switch(DIMENSION)
    {
    case 1:
      {
	double Hx;
	for(size_t n0=0; n0<neighbours.size(); ++n0){
	    
	  x[0] = k_vec[0]/std::fabs(neighbours[n0][0]);
  
	  Hx = evaluate_hermite_kernel(x[0]);
	  
	  count  += 1.;
	  result += Hx;
	}
      }
      break;

    case 2:
      {
	double Hx, Hy;
	for(size_t n0=0; n0<neighbours.size(); ++n0){
	  for(size_t n1=0; n1<neighbours.size(); ++n1){
	    
	    if(std::fabs(volume(&neighbours[n0][0], &neighbours[n1][0])) > 1.e-6){

	      coordinates(&neighbours[n0][0], &neighbours[n1][0], &k_vec[0], &x[0]);
	      
	      Hx = evaluate_hermite_kernel(x[0]);
	      Hy = evaluate_hermite_kernel(x[1]);
	      
	      count  += 1.;
	      result += Hx*Hy;	    
	    }
	  }
	}
      }
      break;

    case 3:
      {
	double Hx, Hy, Hz;
	for(size_t n0=0; n0<neighbours.size(); ++n0){
	  for(size_t n1=0; n1<neighbours.size(); ++n1){
	    for(size_t n2=0; n2<neighbours.size(); ++n2){
	    
	      if(std::fabs(volume(&neighbours[n0][0], &neighbours[n1][0], &neighbours[n2][0])) > 1.e-6){

		coordinates(&neighbours[n0][0], &neighbours[n1][0], &neighbours[n2][0], &k_vec[0], &x[0]);
		
		Hx = evaluate_hermite_kernel(x[0]);
		Hy = evaluate_hermite_kernel(x[1]);
		Hz = evaluate_hermite_kernel(x[2]);
		
		count  += 1.;
		result += Hx*Hy*Hz;
	      }
	    }
	  }
	}
      }
      break;
      
    default :
      throw std::logic_error(__FUNCTION__);
    };

  if(count>0)
    return result/count;
  else
    return 0.;
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::construct_interpolation_matrix()
{
  cout << __FUNCTION__ << endl;

  int N_k_ext = extended_k_domain<source_k_dmn_t>::get_size();

  interpolation_matrix = new scalartype[target_k_dmn_t::get_size()*source_k_dmn_t::get_size()];

  for(int i=0; i<target_k_dmn_t::get_size()*source_k_dmn_t::get_size(); ++i)
    interpolation_matrix[i] = 0.;

  std::vector<double> K_vec (DIMENSION, 0.);

  std::vector<double> k_vec (DIMENSION, 0.);
  std::vector<double> k_diff(DIMENSION, 0.);

  for(int k_ind=0; k_ind<target_k_dmn_t::get_size(); ++k_ind){

    for(int d=0; d<DIMENSION; ++d)
      k_vec[d] = k_vecs[d+k_ind*DIMENSION];
        
    for(int n_ind=0; n_ind<N_k_ext; ++n_ind){
      
      K_vec = extended_k_domain<source_k_dmn_t>::get_elements()[n_ind];
      
      int K_ind = extended_k_domain<source_k_dmn_t>::get_cluster_index(n_ind);

      k_diff = VECTOR_OPERATIONS::SUBTRACT(k_vec, K_vec);

      interpolation_matrix[k_ind+target_k_dmn_t::get_size()*K_ind] += evaluate_hermite_kernel_at(k_diff);
    }
  }
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
inline void  hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::generate_k0_indices(std::vector<double> k_vec)
{
  typedef extended_k_domain<source_k_dmn_t> extended_k_dmn_t;

  std::vector<double> t_vec(DIMENSION, 0);

  switch(DIMENSION)
    {
    case 1:
      {
	for(int n0=-N_delta; n0<=N_delta; ++n0){

	  t_vec = k_vec;

	  for(int d=0; d<DIMENSION; ++d)
	    t_vec[d] += (n0*k_cluster_type::get_basis_vectors()[0][d]);

	  int index = (n0+N_delta);

	  k0_indices[index] = extended_k_dmn_t::get_index(t_vec);
	}
      }
      break;

    case 2:
      {
	for(int n0=-N_delta; n0<=N_delta; ++n0){
	  for(int n1=-N_delta; n1<=N_delta; ++n1){
	    
	    t_vec = k_vec;

	    for(int d=0; d<DIMENSION; ++d)
	      t_vec[d] += (n0*k_cluster_type::get_basis_vectors()[0][d]
			   + n1*k_cluster_type::get_basis_vectors()[1][d]);

	    int index = (n0+N_delta) + (2*N_delta+1)*(n1+N_delta);
	    
	    k0_indices[index] = extended_k_dmn_t::get_index(t_vec);
	  }
	}
      }
      break;

    case 3:
      {
	for(int n0=-N_delta; n0<=N_delta; ++n0){
	  for(int n1=-N_delta; n1<=N_delta; ++n1){
	    for(int n2=-N_delta; n2<=N_delta; ++n2){

	      t_vec = k_vec;

	      for(int d=0; d<DIMENSION; ++d)
		t_vec[d] += (n0*k_cluster_type::get_basis_vectors()[0][d]
			     + n1*k_cluster_type::get_basis_vectors()[1][d]
			     + n2*k_cluster_type::get_basis_vectors()[2][d]);
	      
	      int index = (n0+N_delta) + (2*N_delta+1)*(n1+N_delta) + (2*N_delta+1)*(2*N_delta+1)*(n2+N_delta);

	      k0_indices[index] = extended_k_dmn_t::get_index(t_vec);
	    }
	  }
	}
      }
      break;
      
    default :
      throw std::logic_error(__FUNCTION__);
    };
}

template<typename scalartype, cluster_representation_type cluster_representation, typename base_cluster_type, typename target_k_dmn_t>
void hspline_interpolation_kernel<scalartype, k_cluster<cluster_representation, base_cluster_type>, target_k_dmn_t>::construct_interpolation_matrix_fast()
{
  typedef extended_k_domain<source_k_dmn_t> extended_k_dmn_t;

  int N_k_source = source_k_dmn_t::get_size();
  int N_k_target = target_k_dmn_t::get_size();

  for(int i=0; i<N_k_target*N_k_source; ++i)
    interpolation_matrix[i] = 0.;

  std::vector<double> K_vec(DIMENSION, 0.);
  std::vector<double> K_aff(DIMENSION, 0.);

  std::vector<double> k_vec (DIMENSION, 0.);
  std::vector<double> k_diff(DIMENSION, 0.);

  for(int k_ind=0; k_ind<N_k_target; ++k_ind)
    {
      {
	for(int d=0; d<DIMENSION; ++d)
	  K_aff[d] = k_vecs_index[d+k_ind*DIMENSION];
	
	generate_k0_indices(K_aff);
      }

      {
	for(int d=0; d<DIMENSION; ++d)
	  k_vec[d] = k_vecs[d+k_ind*DIMENSION];
	
	for(size_t l=0; l<k0_indices.size(); ++l)
	  {
	    int k0_ind = k0_indices[l];
	    int K_ind  = extended_k_dmn_t::get_cluster_index(k0_ind);
	    
	    K_vec = extended_k_dmn_t::get_elements()[k0_ind];
	    
	    k_diff = VECTOR_OPERATIONS::SUBTRACT(k_vec, K_vec);
	    
	    interpolation_matrix[k_ind+N_k_target*K_ind] += evaluate_hermite_kernel_at(k_diff);
	  }
      }
    }
}

#endif





















