/*
  Copyright (c) Alexander Zaitsev <zamazan4ik@gmail.com>, 2016

  Distributed under the Boost Software License, Version 1.0. (See
  accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt)

  See http://www.boost.org/ for latest version.
*/

/// \file  is_palindrome.hpp
/// \brief Checks the input sequence on palindrome.
/// \author Alexander Zaitsev

#ifndef BOOST_ALGORITHM_IS_PALINDROME_HPP
#define BOOST_ALGORITHM_IS_PALINDROME_HPP

#include <iterator>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost {  namespace algorithm {

/// \fn is_palindrome ( BidirectionalIterator begin, BidirectionalIterator end, Predicate p )
/// \return true if the entire sequence is palindrome
///
/// \param begin    The start of the input sequence
/// \param end		One past the end of the input sequence
/// \param p        A predicate used to compare the values.
///
/// \note This function will return true for empty sequences and for palindromes.
///     For other sequences function will return false.
///     Complexity: O(N).
template <typename BidirectionalIterator, typename Predicate>
bool is_palindrome(BidirectionalIterator begin, BidirectionalIterator end, Predicate p)
{
    if(begin == end)
    {
        return true;
    }

    --end;
    while(begin != end)
    {
        if(!p(*begin, *end))
        {
            return false;
        }
        ++begin;
        if(begin == end)
        {
            break;
        }
        --end;
    }
    return true;
}

/// \fn is_palindrome ( BidirectionalIterator begin, BidirectionalIterator end )
/// \return true if the entire sequence is palindrome
///
/// \param begin    The start of the input sequence
/// \param end		One past the end of the input sequence
///
/// \note This function will return true for empty sequences and for palindromes.
///     For other sequences function will return false.
///     Complexity: O(N).
template <typename BidirectionalIterator>
bool is_palindrome(BidirectionalIterator begin, BidirectionalIterator end)
{
    return is_palindrome(begin, end,
                         std::equal_to<typename std::iterator_traits<BidirectionalIterator>::value_type> ());
}

/// \fn is_palindrome ( const R& range )
/// \return true if the entire sequence is palindrome
///
/// \param range The range to be tested.
///
/// \note This function will return true for empty sequences and for palindromes.
///     For other sequences function will return false.
///     Complexity: O(N).
template <typename R>
bool is_palindrome(const R& range)
{
    return is_palindrome(boost::begin(range), boost::end(range));
}

/// \fn is_palindrome ( const R& range, Predicate p )
/// \return true if the entire sequence is palindrome
///
/// \param range The range to be tested.
/// \param p     A predicate used to compare the values.
///
/// \note This function will return true for empty sequences and for palindromes.
///     For other sequences function will return false.
///     Complexity: O(N).
template <typename R, typename Predicate>
bool is_palindrome(const R& range, Predicate p)
{
    return is_palindrome(boost::begin(range), boost::end(range), p);
}

//Disable is_palindrome for const char* because it work not properly.
//Please use string_view for const char* cases.
//Here we use dirty hack to disable 'is_palindrome' with 'const char*'
//URL: http://stackoverflow.com/questions/14637356/static-assert-fails-compilation-even-though-template-function-is-called-nowhere
template<typename T>
struct foobar : std::false_type
{ };

template<typename T = int>
bool is_palindrome(const char* str)
{
    static_assert(foobar<T>::value, "Using 'is_palindrome' for 'const char*' is dangerous, because result is always false"
                         "(reason: '\0' in the end of the string). You can use string_view in this case");
    return false;
}

}}

#endif // BOOST_ALGORITHM_IS_PALINDROME_HPP
