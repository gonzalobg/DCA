//-*-C++-*-

#ifndef DNFFT_ATOMIC_CONVOLUTION_H
#define DNFFT_ATOMIC_CONVOLUTION_H

namespace MATH_ALGORITHMS
{
  namespace NFFT
  {
    enum NFFT_MODE_NAMES {EXACT, LINEAR, CUBIC};

    template<int max_count, int count>
    struct nfft_atomic_convolution
    {
      template<typename scalar_type>
      inline static void execute_linear(scalar_type* f, scalar_type* M, scalar_type* y)
      {
        f[count] += (M[0+2*count]*y[0]+M[1+2*count]*y[1]);

        nfft_atomic_convolution<max_count, count+1>::execute_linear(f, M, y);
      }

      template<typename scalar_type>
      inline static void execute_cubic(scalar_type* f, scalar_type* M, scalar_type* y)
      {
        f[count] += (M[0+4*count]*y[0]+M[1+4*count]*y[1]+M[2+4*count]*y[2]+M[3+4*count]*y[3]);

        nfft_atomic_convolution<max_count, count+1>::execute_cubic(f, M, y);
      }

      template<typename scalar_type>
      inline static void execute_M_y_2(scalar_type* f, scalar_type* M, int LDA, scalar_type* y)
      {
	execute_Mt_y_1(f, M+0*LDA, y+0);
	execute_Mt_y_1(f, M+1*LDA, y+1);
      }

      template<typename scalar_type>
      inline static void execute_M_y_4(scalar_type* f, scalar_type* M, int LDA, scalar_type* y)
      {
	execute_Mt_y_1(f, M+0*LDA, y+0);
	execute_Mt_y_1(f, M+1*LDA, y+1);
	execute_Mt_y_1(f, M+0*LDA, y+2);
	execute_Mt_y_1(f, M+1*LDA, y+3);
      }

      template<typename scalar_type>
      inline static void execute_Mt_y_1(scalar_type* f, scalar_type* M, scalar_type* y)
      {
        f[count] += M[count]*y[0];

        nfft_atomic_convolution<max_count, count+1>::execute_Mt_y_1(f, M, y);
      }

      template<typename scalar_type>
      inline static void execute_Mt_y_2(scalar_type* f, scalar_type* M, scalar_type* y)
      {
        f[count] += (M[0+2*count]*y[0]+M[1+2*count]*y[1]);

        nfft_atomic_convolution<max_count, count+1>::execute_Mt_y_2(f, M, y);
      }

      template<typename scalar_type>
      inline static void execute_Mt_y_4(scalar_type* f, scalar_type* M, scalar_type* y)
      {
        f[count] += (M[0+4*count]*y[0]+M[1+4*count]*y[1]+M[2+4*count]*y[2]+M[3+4*count]*y[3]);

        nfft_atomic_convolution<max_count, count+1>::execute_Mt_y_4(f, M, y);
      }

    };

    template<int max_count>
    struct nfft_atomic_convolution<max_count, max_count>
    {
      template<typename scalar_type>
      inline static void execute_linear(scalar_type* /*f*/, scalar_type* /*y*/, scalar_type* /*M*/)
      {}

      template<typename scalar_type>
      inline static void execute_cubic(scalar_type* /*f*/, scalar_type* /*y*/, scalar_type* /*M*/)
      {}

      template<typename scalar_type>
      inline static void execute_Mt_y_2(scalar_type* /*f*/, scalar_type* /*M*/, scalar_type* /*y*/)
      {}

      template<typename scalar_type>
      inline static void execute_Mt_y_4(scalar_type* /*f*/, scalar_type* /*M*/, scalar_type* /*y*/)
      {}
    };

  }

}

#endif

/*

void 
mmul(const float *a, const float *b, float *r)
{
  for (int i=0; i<16; i+=4)
    for (int j=0; j<4; j++)
      r[i+j] = b[i]*a[j] + b[i+1]*a[j+4] + b[i+2]*a[j+8] + b[i+3]*a[j+12];
}

void
mmul_sse(const float * a, const float * b, float * r)
{
  __m128 a_line, b_line, r_line;
  for (int i=0; i<16; i+=4) {
    // unroll the first step of the loop to avoid having to initialize r_line to zero
    a_line = _mm_load_ps(a);         // a_line = vec4(column(a, 0))
    b_line = _mm_set1_ps(b[i]);      // b_line = vec4(b[i][0])
    r_line = _mm_mul_ps(a_line, b_line); // r_line = a_line * b_line
    for (int j=1; j<4; j++) {
      a_line = _mm_load_ps(&a[j*4]); // a_line = vec4(column(a, j))
      b_line = _mm_set1_ps(b[i+j]);  // b_line = vec4(b[i][j])
                                     // r_line += a_line * b_line
      r_line = _mm_add_ps(_mm_mul_ps(a_line, b_line), r_line);
    }
    _mm_store_ps(&r[i], r_line);     // r[i] = r_line
  }
}

void mmul_vec4
(const float * a, const float * b, float * r)
{
  for (int i=0; i<16; i+=4) {
    vec4 rl = vec4(a) * vec4(b[i]);
    for (int j=1; j<4; j++)
      rl += vec4(&a[j*4]) * vec4(b[i+j]);
    rl >> &r[i];
  }
}

struct vec4
{
  __m128 xmm;

  vec4 (__m128 v) : xmm (v) {}

  vec4 (float v) { xmm = _mm_set1_ps(v); }

  vec4 (float x, float y, float z, float w)
  { xmm = _mm_set_ps(w,z,y,x); }

  vec4 (const float *v) { xmm = _mm_load_ps(v); }

  vec4 operator* (const vec4 &v) const
  { return vec4(_mm_mul_ps(xmm, v.xmm)); }

  vec4 operator+ (const vec4 &v) const
  { return vec4(_mm_add_ps(xmm, v.xmm)); }

  vec4 operator- (const vec4 &v) const
  { return vec4(_mm_sub_ps(xmm, v.xmm)); }

  vec4 operator/ (const vec4 &v) const
  { return vec4(_mm_div_ps(xmm, v.xmm)); }

  void operator*= (const vec4 &v)
  { xmm = _mm_mul_ps(xmm, v.xmm); }

  void operator+= (const vec4 &v)
  { xmm = _mm_add_ps(xmm, v.xmm); }

  void operator-= (const vec4 &v)
  { xmm = _mm_sub_ps(xmm, v.xmm); }

  void operator/= (const vec4 &v)
  { xmm = _mm_div_ps(xmm, v.xmm); }

  void operator>> (float *v)
  { _mm_store_ps(v, xmm); }

};
 */
