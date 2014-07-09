// bslh_spookyhashalgorithm.h                                         -*-C++-*-
#ifndef INCLUDED_BSLH_SPOOKYHASHALGORITHM
#define INCLUDED_BSLH_SPOOKYHASHALGORITHM

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide a way to use spooky hash algorithm with 'bslh::Hash<>'.
//
//@CLASSES:
// bslh::SpookyHashAlgorithm: Spooky hash algorithm.
//
//@SEE_ALSO: bslh_hash, bslh_spookhashalgorithmimp
//
//@DESCRIPTION: 'bslh::SpookyHashAlgorithm' implements the spooky hashing
//  algorithm by Bob Jenkins. The algorithm is a general purpose algorithm
//  that is known to quickly reach good avalance performance and is very fast.
//  It is a good choice to use as a default hashing algorithm for associative
//  containters. See: http://burtleburtle.net/bob/hash/spooky.html
//
///Security Gaurentees
///-------------------
// This hashing algorithm is NOT a secure hash algorithm and makes no security
// garuntees. If you are looking to mitigate denial of service attacks on an
// associative container, see 'bslh_SipHashAlgorithm'.
//
///Performance
///-----------
// This hashing algorithm is a fast, general purpose algorithm. It is quicker
// than specialized algorithms such as SipHash, but not as fast as identity
// hashing. Output hashes will be well distributed and will avalanche, which
// means changing one bit on the input will completely change the output. This
// will prevent similar values from funneling to the same hash or bucket.
//
///Endianness
///----------
// This hash is endian-specific. It is designed for little endian machines,
// however, it will run on big endian machines. On big endian machines, the
// Performance and Security Garentees still apply, however the hashes produced
// will be different from those produced by the cannonical implementation. The
// creator of this algorithm aknowledges this and says that the big-endian
// hashes are just as good as the little-endian ones. Be aware that this means
// storing hashes in memory or transmitting them across the network is not
// reccomended.

#ifndef INCLUDED_BSLH_SPOOKYHASHALGORITHMIMP
#include <bslh_spookyhashalgorithmimp.h>
#endif

#ifndef INCLUDED_BSLMF_ISBITWISEMOVEABLE
#include <bslmf_isbitwisemoveable.h>
#endif

#ifndef INCLUDED_BSLS_TYPES
#include <bsls_types.h>
#endif

#ifndef INCLUDED_CSTDDEF
#include <cstddef>  // for 'std::size_t'
#define INCLUDED_CSTDDEF
#endif

namespace BloombergLP {

namespace bslh {


                          // ===============================
                          // class bslh::SpookyHashAlgorithm
                          // ===============================

class SpookyHashAlgorithm
{
    // This class wraps an implementation of the "SpookyHash" hash algorithm
    // (see http://burtleburtle.net/bob/hash/spooky.html)

    typedef bsls::Types::Uint64 uint64;
    SpookyHashAlgorithmImp d_state;

  public:
    typedef bsls::Types::Uint64 result_type;
        // Typedef indicating the type of value this algorithm returns

    SpookyHashAlgorithm(uint64 seed1 = 1, uint64 seed2 = 2);                    //TODO explicit?
        // Create an instance of 'SpookyHashAlgorithm' and optionally specify a
        // 'seed1' and 'seed2' to be used as the higher and lower order bits
        // respectively of the 128-bit seed for the algorithm.

    void operator()(void const* key, size_t length);
        // Incorporates the specified 'key' of 'length' bytes into the internal
        // state of the hashing algorithm.

    result_type computeHash();
        // Return the finalized version of the hash that has been accumulated.
        // Note that this changes the internal state of the object, so calling
        // 'computeHash' multiple times in a row will return different results,
        // and only the first result returned will match the expected result of
        // the algorithm.
};

SpookyHashAlgorithm::SpookyHashAlgorithm(SpookyHashAlgorithm::uint64 seed1,
                                         SpookyHashAlgorithm::uint64 seed2)
: d_state()
{
    d_state.Init(seed1, seed2);
}

void SpookyHashAlgorithm::operator()(void const* key, size_t length)
{
    d_state.Update(key, length);
}

SpookyHashAlgorithm::result_type SpookyHashAlgorithm::computeHash()
{
    bsls::Types::Uint64 h1, h2;
    d_state.Final(&h1, &h2);
    return h1;
}

}  // close namespace bslh

// ============================================================================
//                                TYPE TRAITS
// ============================================================================

namespace bslmf {
template <>
struct IsBitwiseMoveable<bslh::SpookyHashAlgorithm>
    : bsl::true_type {};
}  // close namespace bslmf

}  // close namespace BloombergLP

#endif

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Bloomberg Finance L.P.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

// ----------------------------- END-OF-FILE ----------------------------------
