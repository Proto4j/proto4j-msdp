// The MIT License (MIT)
// 
// Copyright (c) 2022 Proto4j
// 
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

/**
 * @file msdpclient.hpp
 * @author 
 * 
 * @brief 
 * 
 * 
 * @version 0.1
 * @date 2022-09-26
 * 
 * @copyright Copyright (c) 2022 Proto4j
 * 
 */

#if !defined(__MSDP_TYPES_H__)
#define __MSDP_TYPES_H__

namespace msdp
{
  
typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned int uint_32;

enum class stdcode {
  OP_INI,
  OP_ERR,
  OP_QRY,
  OP_RSP,
  OP_LVE
};

namespace packet
{
  typedef uint_8 *MSDPPacket;
} // namespace packet

namespace uuid
{
  typedef uint_8 *msdpuuid;

  const uint_8 MSDP_UUID_LENGTH = 12;
} // namespace uuid


} // namespace msdp


#endif // __MSDP_TYPES_H__
