// ========================================================================== //
// The MIT License (MIT)                                                      //
//                                                                            //
// Copyright (c) 2017 Jefferson Amstutz                                       //
//                                                                            //
// Permission is hereby granted, free of charge, to any person obtaining a    //
// copy of this software and associated documentation files (the "Software"), //
// to deal in the Software without restriction, including without limitation  //
// the rights to use, copy, modify, merge, publish, distribute, sublicense,   //
// and/or sell copies of the Software, and to permit persons to whom the      //
// Software is furnished to do so, subject to the following conditions:       //
//                                                                            //
// The above copyright notice and this permission notice shall be included in //
// in all copies or substantial portions of the Software.                     //
//                                                                            //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    //
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    //
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        //
// DEALINGS IN THE SOFTWARE.                                                  //
// ========================================================================== //

#pragma once

#include "../pack.h"

namespace tsimd {

  template <typename T, int W, typename FCN_T>
  inline void foreach(pack<T, W> &p, FCN_T &&fcn)
  {
    #pragma omp simd
    for (int i = 0; i < W; ++i)
      fcn(p[i], i);
  }

  template <int W, typename FCN_T>
  inline void foreach_active(const mask<W> &m, FCN_T &&fcn)
  {
    #pragma omp simd
    for (int i = 0; i < W; ++i)
      if (m[i])
        fcn(i);
  }

  template <typename T, int W, typename FCN_T>
  inline void foreach_active(const mask<W> &m, pack<T, W> &p, FCN_T &&fcn)
  {
    #pragma omp simd
    for (int i = 0; i < W; ++i)
      if (m[i])
        fcn(p[i]);
  }

  // any() ////////////////////////////////////////////////////////////////////

  // 1-wide //

  // TODO

  // 4-wide //

  // TODO

  // 8-wide //

  inline bool any(const vboolf8& a)
  {
#if defined(__AVX512__) || defined(__AVX__)
    return !_mm256_testz_ps(a, a);
#else
    NOT_IMPLEMENTED;
#endif
  }

  // 16-wide //

  // TODO

  // none() ///////////////////////////////////////////////////////////////////

  // 1-wide //

  // TODO

  // 4-wide //

  // TODO

  // 8-wide //

  inline bool none(const vboolf8 &m)
  {
    return !any(m);
  }

  // 16-wide //

  // TODO

  // all() ////////////////////////////////////////////////////////////////////

  // 1-wide //

  // TODO

  // 4-wide //

  // TODO

  // 8-wide //

  inline bool all(const vboolf8& a)
  {
#if defined(__AVX512__) || defined(__AVX__)
    return _mm256_movemask_ps(a) == (unsigned int)0xff;
#else
    NOT_IMPLEMENTED;
#endif
  }

  // 16-wide //

  // TODO

  // select() /////////////////////////////////////////////////////////////////

  // 1-wide //

  // TODO

  // 4-wide //

  // TODO

  // 8-wide //

  inline vfloat8 select(const vboolf8& m, const vfloat8& t, const vfloat8& f)
  {
#if defined(__AVX512__)
    return _mm256_mask_blend_ps(m, f, t);
#elif defined(__AVX__)
    return _mm256_blendv_ps(f, t, m);
#else
    vfloat8 result;

    #pragma omp simd
    for (int i = 0; i < vfloat8::static_size; ++i) {
      if (m[i])
        result[i] = t[i];
      else
        result[i] = f[i];
    }

    return result;
#endif
  }

  inline vint8 select(const vboolf8& m, const vint8& t, const vint8& f)
  {
#if defined(__AVX512__) || defined(__AVX__)
    return _mm256_castps_si256(
        _mm256_blendv_ps(_mm256_castsi256_ps(f), _mm256_castsi256_ps(t), m)
    );
#else
    vint8 result;

    #pragma omp simd
    for (int i = 0; i < vint8::static_size; ++i) {
      if (m[i])
        result[i] = t[i];
      else
        result[i] = f[i];
    }

    return result;
#endif
  }

  // 16-wide //

  // TODO

} // ::tsimd