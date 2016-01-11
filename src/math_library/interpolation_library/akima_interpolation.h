//-*-C++-*-

#ifndef AKIMA_INTERPOLATION_H
#define AKIMA_INTERPOLATION_H

/*!
 *  \class   akima_interpolation
 *  \ingroup INTERPOLATION
 *
 *  \author  Peter Staar
 *  \brief   This class preforms an Akima interpolation in 1D.
 */
template<typename scalartype>
class akima_interpolation
{
public:

  akima_interpolation(int n);
  ~akima_interpolation();

  void initialize         (scalartype* x, scalartype* y);
  void initialize_periodic(scalartype* x, scalartype* y);
  
  scalartype evaluate(scalartype x);

  scalartype get_alpha(int l, int i);

private:

  void compute_coefficients(scalartype* x_array, scalartype* y_array);

private:

  int      size;

  scalartype* X; 
  scalartype* Y; 
  
  scalartype* a; 
  scalartype* b; 
  scalartype* c; 
  scalartype* d; 

  scalartype* m; 
  scalartype* _m; 
};

template<typename scalartype>
akima_interpolation<scalartype>::akima_interpolation(int n):
  size(n),
  
  X(NULL),
  Y(NULL),

  a(NULL),
  b(NULL),
  c(NULL),
  d(NULL),
  
  m(NULL),
  _m(NULL)
{
  X = new scalartype[size];
  Y = new scalartype[size];
  
  a = new scalartype[size];
  b = new scalartype[size];
  c = new scalartype[size]; //(scalartype *) malloc (size * sizeof (scalartype));
  d = new scalartype[size];//(scalartype *) malloc (size * sizeof (scalartype));

  _m = new scalartype[size+4]; //(scalartype *) malloc ((size + 4) * sizeof (scalartype));

}

template<typename scalartype>
akima_interpolation<scalartype>::~akima_interpolation()
{
  if(X != NULL) delete [] X;
  if(Y != NULL) delete [] Y;

  if(a != NULL) delete [] a;
  if(b != NULL) delete [] b;
  if(c != NULL) delete [] c;
  if(d != NULL) delete [] d;

  if(_m != NULL) delete [] _m;
}

template<typename scalartype>
scalartype akima_interpolation<scalartype>::get_alpha(int l, int i)
{
  assert(i>-1 and i<size-1);

  switch(l)
    {
    case 0:
      return a[i];

    case 1:
      return b[i];

    case 2:
      return c[i];

    case 3:
      return d[i];
      
    default:
      throw std::logic_error(__FUNCTION__);
    }
}

template<typename scalartype>
void akima_interpolation<scalartype>::initialize(scalartype* x_array, scalartype* y_array)
{
  for(int i=0; i<size; i++){
    X[i] = x_array[i];
    Y[i] = y_array[i];
  }

  m = _m + 2; /* offset so we can address the -1,-2 components */
  
  for (int i = 0; i <= size-2; i++)
    m[i] = (y_array[i + 1] - y_array[i]) / (x_array[i + 1] - x_array[i]);
  
  /* non-periodic boundary conditions */
  m[-2] = 3.0 * m[0] - 2.0 * m[1];
  m[-1] = 2.0 * m[0] - m[1];
  m[size - 1] = 2.0 * m[size - 2] - m[size - 3];
  m[size] = 3.0 * m[size - 2] - 2.0 * m[size - 3];
  
  compute_coefficients(x_array, y_array);
}

template<typename scalartype>
void akima_interpolation<scalartype>::initialize_periodic(scalartype* x_array, scalartype* y_array)
{
  m = _m + 2; /* offset so we can address the -1,-2 components */

  for (int i = 0; i <= size - 2; i++)
    m[i] = (y_array[i + 1] - y_array[i]) / (x_array[i + 1] - x_array[i]);
  
  /* periodic boundary conditions */
  m[-2] = m[size - 1 - 2];
  m[-1] = m[size - 1 - 1];
  m[size - 1] = m[0];
  m[size] = m[1];
  
  compute_coefficients(x_array, y_array);
}

template<typename scalartype>
void akima_interpolation<scalartype>::compute_coefficients(scalartype* x_array, scalartype* y_array)
{
  for(int i=0; i<(size-1); i++)
    {
      a[i] = y_array[i];

      const scalartype NE = std::fabs(m[i + 1] - m[i]) + fabs (m[i - 1] - m[i - 2]);

      if (NE == 0.0)
        {
          b[i] = m[i];
          c[i] = 0.0;
          d[i] = 0.0;
        }
      else
        {
          const scalartype h_i = x_array[i + 1] - x_array[i];
          const scalartype NE_next = std::fabs(m[i + 2] - m[i + 1]) + fabs (m[i] - m[i - 1]);
          const scalartype alpha_i = std::fabs(m[i - 1] - m[i - 2]) / NE;

          scalartype alpha_ip1;
          scalartype tL_ip1;

          if (NE_next == 0.0)
            {
              tL_ip1 = m[i];
            }
          else
            {
              alpha_ip1 = std::fabs(m[i] - m[i - 1]) / NE_next;
              tL_ip1 = (1.0 - alpha_ip1) * m[i] + alpha_ip1 * m[i + 1];
            }

          b[i] = (1.0 - alpha_i) * m[i - 1] + alpha_i * m[i];
          c[i] = (3.0 * m[i] - 2.0 * b[i] - tL_ip1) / h_i;
          d[i] = (b[i] + tL_ip1 - 2.0 * m[i]) / (h_i * h_i);
        }

//       cout << x_array[i] 
// 	   << "\t" << a[i]
// 	   << "\t" << b[i]
// 	   << "\t" << c[i]
// 	   << "\t" << d[i]
// 	   << endl;
    }

//   cout << endl;
}

template<typename scalartype>
scalartype akima_interpolation<scalartype>::evaluate(scalartype x)
{
  if(x<X[0]+1.e-6)
    return Y[0];

  if(x>=X[size-1]-1.e-6)
    return Y[size-1];

  int index=-1;
  for(int i=0; i<size-1; ++i)
    if(X[i]<=x and x<X[i+1])
      index = i;
  
  assert(index>-1 and index<size);
  
  const scalartype x_lo = X[index];
  const scalartype delx = x - x_lo;
  
  const scalartype a0 = a[index];
  const scalartype a1 = b[index];
  const scalartype a2 = c[index];
  const scalartype a3 = d[index];
  
  return a0 + delx * (a1 + delx * (a2 + a3 * delx));
}


// void akima_eval_deriv (const void * vstate,
// 		       const double x_array[], const double y_array[], int size,
// 		       double x,
// 		       gsl_interp_accel * a,
// 		       double *dydx)
// {
//   const akima_state_t *state = (const akima_state_t *) vstate;

//   int index;

//   DISCARD_POINTER(y_array); /* prevent warning about unused parameter */
  
//   if (a != 0)
//     {
//       index = gsl_interp_accel_find (a, x_array, size, x);
//     }
//   else
//     {
//       index = gsl_interp_bsearch (x_array, x, 0, size - 1);
//     }
  
//   /* evaluate */
//   {
//     double x_lo = x_array[index];
//     double delx = x - x_lo;
//     double b = state->b[index];
//     double c = state->c[index];
//     double d = state->d[index];
//     *dydx = b + delx * (2.0 * c + 3.0 * d * delx);
//     return GSL_SUCCESS;
//   }
// }


// void akima_eval_deriv2(const void * vstate,
// 			const double x_array[], const double y_array[], int size,
// 			double x,
// 			gsl_interp_accel * a,
// 			double *y_pp)
// {
//   const akima_state_t *state = (const akima_state_t *) vstate;

//   int index;

//   DISCARD_POINTER(y_array); /* prevent warning about unused parameter */

//   if (a != 0)
//     {
//       index = gsl_interp_accel_find (a, x_array, size, x);
//     }
//   else
//     {
//       index = gsl_interp_bsearch (x_array, x, 0, size - 1);
//     }
  
//   /* evaluate */
//   {
//     const double x_lo = x_array[index];
//     const double delx = x - x_lo;
//     const double c = state->c[index];
//     const double d = state->d[index];
//     *y_pp = 2.0 * c + 6.0 * d * delx;
//   }
// }

// void akima_eval_integ (const void * vstate,
// 		       const double x_array[], const double y_array[], int size,
// 		       gsl_interp_accel * acc,
// 		       double a, double b,
// 		       double * result)
// {
//   const akima_state_t *state = (const akima_state_t *) vstate;

//   int i, index_a, index_b;

//   if (acc != 0)
//     {
//       index_a = gsl_interp_accel_find (acc, x_array, size, a);
//       index_b = gsl_interp_accel_find (acc, x_array, size, b);
//     }
//   else
//     {
//       index_a = gsl_interp_bsearch (x_array, a, 0, size - 1);
//       index_b = gsl_interp_bsearch (x_array, b, 0, size - 1);
//     }
  
//   *result = 0.0;

//   /* interior intervals */
  
//   for(i=index_a; i<=index_b; i++) {
//     const double x_hi = x_array[i + 1];
//     const double x_lo = x_array[i];
//     const double y_lo = y_array[i];
//     const double dx = x_hi - x_lo;
//     if(dx != 0.0) {

//       if (i == index_a || i == index_b)
//         {
//           double x1 = (i == index_a) ? a : x_lo;
//           double x2 = (i == index_b) ? b : x_hi;
//           *result += integ_eval (y_lo, state->b[i], state->c[i], state->d[i],
//                                  x_lo, x1, x2);
//         }
//       else
//         {
//           *result += dx * (y_lo 
//                            + dx*(0.5*state->b[i] 
//                                  + dx*(state->c[i]/3.0 
//                                        + 0.25*state->d[i]*dx)));
//         }
//     }
//     else {
//       *result = 0.0;
//     }
//   }
// }

#endif
