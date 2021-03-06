//=================================================================================================
/*!
//  \file blaze/math/typetraits/IsPadded.h
//  \brief Header file for the IsPadded type trait
//
//  Copyright (C) 2012-2020 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_MATH_TYPETRAITS_ISPADDED_H_
#define _BLAZE_MATH_TYPETRAITS_ISPADDED_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include "../../util/IntegralConstant.h"


namespace blaze {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Compile time check for data types with padding.
// \ingroup math_type_traits
//
// This type trait tests whether the given data type employs or simulates padding such that no
// special treatment of remainder elements is necessary for vectorized operations on the type.
// In case the data type is padded, the \a value member constant is set to \a true, the nested
// type definition \a Type is \a TrueType, and the class derives from \a TrueType. Otherwise
// \a value is set to \a false, \a Type is \a FalseType, and the class derives from \a FalseType.
// Examples:

   \code
   blaze::IsPadded< blaze::StaticVector<int,3UL> >::value     // Evaluates to 1
   blaze::IsPadded< const blaze::HybridVector<float> >::Type  // Results in TrueType
   blaze::IsPadded< volatile blaze::DynamicMatrix<double> >   // Is derived from TrueType
   blaze::IsPadded< int >::value                              // Evaluates to 0
   blaze::IsPadded< const CompressedVector<int> >::Type       // Results in FalseType
   blaze::IsPadded< volatile CompressedMatrix<double> >       // Is derived from FalseType
   \endcode
*/
template< typename T >
struct IsPadded
   : public FalseType
{};
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Specialization of the IsPadded type trait for const types.
// \ingroup math_type_traits
*/
template< typename T >
struct IsPadded< const T >
   : public IsPadded<T>
{};
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Specialization of the IsPadded type trait for volatile types.
// \ingroup math_type_traits
*/
template< typename T >
struct IsPadded< volatile T >
   : public IsPadded<T>
{};
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Specialization of the IsPadded type trait for cv qualified types.
// \ingroup math_type_traits
*/
template< typename T >
struct IsPadded< const volatile T >
   : public IsPadded<T>
{};
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Auxiliary variable template for the IsPadded type trait.
// \ingroup math_type_traits
//
// The IsPadded_v variable template provides a convenient shortcut to access the nested \a value
// of the IsPadded class template. For instance, given the type \a T the following two statements
// are identical:

   \code
   constexpr bool value1 = blaze::IsPadded<T>::value;
   constexpr bool value2 = blaze::IsPadded_v<T>;
   \endcode
*/
template< typename T >
constexpr bool IsPadded_v = IsPadded<T>::value;
//*************************************************************************************************

} // namespace blaze

#endif
