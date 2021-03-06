/* Copyright 2018 kevin Lau (http://github.com/stormycatcat)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef _STL_MAX_HPP_
#define _STL_MAX_HPP_

#include <initializer_list>

namespace std
{

/**
 *@brief since c++14
 */
template <class T>
constexpr const T& max(const T& a,const T& b)
{
    return a<b?b:a;
}

/**
 *@brief since c++14
 */
template <class T,class Compare>
constexpr const T& max(const T& a,const T& b,Compare comp)
{
    return comp(a,b)?b:a;
}

/**
 *@brief since c++14
 */
template <class T>
constexpr T max(initializer_list<T> ilist)
{
    return *max_element(ilist.begin(),ilist.end());
}

}

#endif
