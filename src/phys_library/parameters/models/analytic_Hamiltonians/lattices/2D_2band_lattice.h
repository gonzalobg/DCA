//-*-C++-*-

#ifndef TWOBAND_LATTICE_2D_H
#define TWOBAND_LATTICE_2D_H

/*!
 *  \author Peter Staar, Andrei Plamada
 */
template<typename point_group_type>
class twoband_lattice
{
public:

  typedef no_symmetry<2>   LDA_point_group;
  typedef point_group_type DCA_point_group;

  const static cluster_shape_type DCA_cluster_shape = BETT_CLUSTER;
  const static cluster_shape_type LDA_cluster_shape = PARALLELEPIPED;

  const static int DIMENSION = 2;
  const static int BANDS     = 2;

public:
  static double* initialize_r_DCA_basis();
  static double* initialize_k_DCA_basis();

  static double* initialize_r_LDA_basis();
  static double* initialize_k_LDA_basis();

  static std::vector<int>                  get_flavors();
  static std::vector<std::vector<double> > get_a_vectors();

  static std::vector<std::pair<std::pair<int,int>, std::pair<int,int> > > get_orbital_permutations();

  template<class domain, class parameters_type>
  static void initialize_H_interaction(FUNC_LIB::function<double , domain >& H_interaction,
                                       parameters_type&            parameters);

  template<class domain>
  static void initialize_H_symmetry(FUNC_LIB::function<int, domain>& H_symmetry);

  template<class domain, class parameters_type>
  static void initialize_H_LDA(FUNC_LIB::function<std::complex<double> , domain >& H_LDA,
                               parameters_type&                          parameters);

  template<class parameters_type>
  static std::complex<double> get_LDA_Hamiltonians(parameters_type& parameters,
                                                   std::vector<double> k, int b1, int s1, int b2, int s2);
};

template<typename point_group_type>
double* twoband_lattice<point_group_type>::initialize_r_DCA_basis()
{
  static double* r_DCA = new double[4];

  r_DCA[0] = 1.0;  r_DCA[1] = 0.0;
  r_DCA[2] = 0.0;  r_DCA[3] = 1.0;

  return r_DCA;
}

template<typename point_group_type>
double* twoband_lattice<point_group_type>::initialize_k_DCA_basis()
{
  static double* k_DCA = new double[4];

  k_DCA[0] = 2*M_PI;  k_DCA[1] = 0.;
  k_DCA[2] = 0.;      k_DCA[3] = 2*M_PI;

  return k_DCA;
}

template<typename point_group_type>
double* twoband_lattice<point_group_type>::initialize_r_LDA_basis()
{
  static double* r_LDA = new double[4];

  r_LDA[0] = 1.;  r_LDA[1] = 0.;
  r_LDA[2] = 0.;  r_LDA[3] = 1.;

  return r_LDA;
}

template<typename point_group_type>
double* twoband_lattice<point_group_type>::initialize_k_LDA_basis()
{
  static double* k_LDA = new double[4];

  k_LDA[0] = 2.*M_PI;  k_LDA[1] = 0.;
  k_LDA[2] = 0.;       k_LDA[3] = 2.*M_PI;

  return k_LDA;
}

template<typename point_group_type>
std::vector<int> twoband_lattice<point_group_type>::get_flavors()
{
  static std::vector<int> flavors(BANDS);

  flavors[0]=0;
  flavors[1]=1;

  return flavors;
}

template<typename point_group_type>
std::vector<std::vector<double> > twoband_lattice<point_group_type>::get_a_vectors()
{
  static std::vector<std::vector<double> > a_vecs(BANDS, std::vector<double>(DIMENSION, 0.));

  return a_vecs;
}

template<typename point_group_type>
std::vector<std::pair<std::pair<int,int>, std::pair<int,int> > > twoband_lattice<point_group_type>::get_orbital_permutations()
{
  static std::vector<std::pair<std::pair<int,int>, std::pair<int,int> > > permutations(0);
  return permutations;
}

template<typename point_group_type>
template<class domain, class parameters_type>
void twoband_lattice<point_group_type>::initialize_H_interaction(FUNC_LIB::function<double , domain >& H_interaction,
                                                                 parameters_type&            parameters)
{
  H_interaction = 0.;

  double U0       = parameters.get_U0();
  H_interaction(0,0,0,1,0) = U0;
  H_interaction(0,1,0,0,0) = U0;
}

template<typename point_group_type>
template<class domain>
void twoband_lattice<point_group_type>::initialize_H_symmetry(FUNC_LIB::function<int, domain>& H_symmetries)
{
  H_symmetries = -1;

  H_symmetries(0,0, 0,0) = 0;
  H_symmetries(0,1, 0,1) = 0;

  H_symmetries(1,0, 1,0) = 1;
  H_symmetries(1,1, 1,1) = 1;
}

template<typename point_group_type>
template<class domain, class parameters_type>
void twoband_lattice<point_group_type>::initialize_H_LDA(FUNC_LIB::function<std::complex<double>, domain>& H_LDA,
                                                         parameters_type&                        parameters)
{
  typedef typename parameters_type::b b;
  typedef typename parameters_type::s s;

  typedef typename parameters_type::k_LDA k_LDA;

  std::vector<double> k;

  for(int k_ind=0; k_ind<k_LDA::dmn_size(); k_ind++)
    {
      k = k_LDA::parameter_type::get_elements()[k_ind];

      for(int b_ind1=0; b_ind1<b::dmn_size(); b_ind1++)
        for(int s_ind1=0; s_ind1<s::dmn_size(); s_ind1++)
          for(int b_ind2=0; b_ind2<b::dmn_size(); b_ind2++)
            for(int s_ind2=0; s_ind2<s::dmn_size(); s_ind2++)
              H_LDA(b_ind1, s_ind1, b_ind2, s_ind2, k_ind) = get_LDA_Hamiltonians(parameters, k, b_ind1, s_ind1, b_ind2, s_ind2);
    }
}

template<typename point_group_type>
template<class parameters_type>
std::complex<double> twoband_lattice<point_group_type>::get_LDA_Hamiltonians(parameters_type& parameters,
                                                                             std::vector<double> k,
                                                                             int b1, int s1, int b2, int s2)
{
  const static std::complex<double> I(0,1);

  double ei0       = parameters.get_ei0();
  double eb0       = parameters.get_eb0();
  double t0       = parameters.get_t0();

  std::complex<double> H_LDA = 0.;

  if(s1==s2)
    {
      if(b1==b2)
	  if(b1==0)
	      H_LDA += ei0;
	  else
	      H_LDA += eb0;
      else
	  H_LDA += t0;
    }

  return H_LDA;
}

#endif
