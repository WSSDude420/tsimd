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

#include <iostream>

#include "tsimd/tsimd.h"

using namespace tsimd;

template <typename PACK_T>
inline void print(PACK_T &p)
{
  std::cout << "{" << p[0];
  foreach(p, [](typename PACK_T::value_t &v, int i) {
    if (i != 0)
      std::cout << ", " << v;
  });

  std::cout << "}" << std::endl;
}

int main()
{
  // test foreach() and construction //

  std::cout << "test foreach() and construction" << std::endl;

  {
    vfloat v1(2.f);

    print(v1);
  }

  std::cout << std::endl;

  // test operator+() //

  std::cout << "test operator+()" << std::endl;

  {
    vfloat v1(1.f), v2(2.f);

    std::cout << "#1: " << all((v1 + v2)  == vfloat(3.f)) << std::endl;
    std::cout << "#2: " << all((v1 + 2.f) == vfloat(3.f)) << std::endl;
    std::cout << "#3: " << all((2.f + v1) == vfloat(3.f)) << std::endl;
  }

  std::cout << std::endl;

  // test any() //

  std::cout << "test any()" << std::endl;

  {
    vbool m(vfalse);

    print(m);

    std::cout << "#1: " << !tsimd::any(m) << std::endl;
    m[0] = vtrue;
    std::cout << "#2: " << tsimd::any(m) << std::endl;
  }

  std::cout << std::endl;

  // test operator==() //

  std::cout << "test operator==()" << std::endl;

  {
    vint v1(1);
    vint v2(2);

    auto b1 = v1 != v2;
    print(b1);

    std::cout << "#1: " << tsimd::all(v1 != v2) << std::endl;
    std::cout << "#2: " << tsimd::all(1  != v2) << std::endl;
    std::cout << "#3: " << tsimd::all(v2 != 1) << std::endl;

    v1[0] = 2;

    std::cout << "#4: " << !tsimd::all(v1 != v2) << std::endl;
  }

  std::cout << std::endl;

  return 0;
}