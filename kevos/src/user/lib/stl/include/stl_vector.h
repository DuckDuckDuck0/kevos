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

#ifndef _STL_STL_VECTOR_H_
#define _STL_STL_VECTOR_H_

#include <climits>
#include <stdexcept>

#include <stl_alloc.h>
#include <stl_uninitialized.h>

namespace std
{

template <class T,class Alloc>
class vector;

template <class T,class Pointer,class Reference,class Alloc=alloc>
class __vector_reverse_iterator
{
protected:
    using vec=vector<T,Alloc>;
    using iterator=typename vec::iterator;
    using reverse_iterator=__vector_reverse_iterator<T,T*,T&,Alloc>;
    using self=__vector_reverse_iterator<T,Pointer,Reference,Alloc>;

public:
    using iterator_category=random_access_iterator_tag;
    using value_type=T;
    using pointer=Pointer;
    using reference=Reference;
    using size_type=size_t;
    using difference_type=ptrdiff_t;

    __vector_reverse_iterator()
    {
    }

    __vector_reverse_iterator(iterator i):iter(i)
    {
    }

    __vector_reverse_iterator(const __vector_reverse_iterator& other):iter(other.iter)
    {
    }

    bool operator==(const __vector_reverse_iterator& other)const
    {
        return iter==other.iter;
    }

    bool operator!=(const __vector_reverse_iterator& other)const
    {
        return iter!=other.iter;
    }

    bool operator<(const __vector_reverse_iterator& other)const
    {
        return iter<other.iter;
    }

    bool operator<=(const __vector_reverse_iterator& other)const
    {
        return iter<=other.iter;
    }

    bool operator>(const __vector_reverse_iterator& other)const
    {
        return iter>other.iter;
    }

    bool operator>=(const __vector_reverse_iterator& other)const
    {
        return iter>=other.iter;
    }

    T& operator*()const
    {
        return *iter;
    }

    T* operator->()const
    {
        return &(operator*());
    }

    self& operator++()
    {
        --iter;
        return *this;
    }

    self operator++(int)
    {
        self ret=*this;
        --iter;
        return ret;
    }

    self& operator--()
    {
        ++iter;
        return *this;
    }

    self operator--(int)
    {
        self ret=*this;
        ++iter;
        return ret;
    }

    self operator+(size_type n)
    {
        return iter-n;
    }

    self operator-(size_type n)
    {
        return iter+n;
    }

    self& operator+=(size_type n)
    {
        iter-=n;
        return *this;
    }

    self& operator-=(size_type n)
    {
        iter+=n;
        return *this;
    }

protected:
    iterator iter;
};


/**
 * @brief 基本符合STL标准的vector，该版本暂时参考于SGI STL
 */
template <class T,class Alloc=alloc>
class vector
{
public:

/**
 * @brief 每个容器及其迭代器都提供规范的界面用于编译器自动推导
 */
    using value_type=T;
    using pointer=T*;
    using reference=T&;
    using size_type=size_t;
    using difference_type=ptrdiff_t;
    using iterator=value_type*;
    using const_iterator=const iterator;
    using reverse_iterator=__vector_reverse_iterator<T,T*,T&,Alloc>;
    using const_reverse_iterator=const reverse_iterator;

protected:

/**
 * @brief 空间配置器，默认采用二级空间配置器  
 */
    using data_allocator=simple_alloc<T,Alloc>;

/**
 * @brief 分配n个T的内存并将内存中所有元素初始化为一个值
 *
 * @param n     元素数量
 * @param value 初始值
 * @return      数据起始位置的迭代器
 */
    iterator allocate_and_fill(size_type n,const T& value)
    {
        iterator ret=data_allocator::allocate(n);
        uninitialized_fill_n(ret,n,value);
        return ret;
    }

/**
 * @brief 分配、填充n个元素，并初始化容器持有的迭代器
 *
 * @param n     元素数量
 * @param value 初始值
 */
    void fill_initialize(size_type n,const T& value)
    {
        _start=allocate_and_fill(n,value);
        _end=_start+n;
        _end_of_storage=_end;
    }

/**
 * @brief 释放起始迭代器指向的内存段
 */
    void deallocate()
    {
        if(_start)
            data_allocator::deallocate(_start);
    }

/**
 * @brief 分配更大的内存块、拷贝所有元素到新内存，并在在末端插入一个元素，更新迭代器
 * 
 * @param x 元素初始值
 */
    void alloc_and_insert(const T&x);

public:

    /**
 * @brief 构造空的vector
 */
    vector():_start(0),_end(0),_end_of_storage(0)
    {
    }

/**
 * @brief 构造n个数量元素的vector，初始值为value 
 */
    vector(size_type n,const T& value)
    {
        fill_initialize(n,value);
    }

/**
 * @brief 构造vector，初始值从指定范围拷贝
 */
    vector(iterator first,iterator last)
    {
        _start=data_allocator::allocate(last-first);
        _end=uninitialized_copy(first,last,begin());
    }

/**
 * @brief 构造n个元素的vector，用省缺构造函数构造元素
 */
    explicit vector(size_type n)
    {
        fill_initialize(n,T());
    }

/**
 * @brief 复制构造函数
 */
    vector(const vector& other)
    {
        _start=data_allocator::allocate(other.size());
        _end=uninitialized_copy(other.begin(),other.end(),begin());     
    }

/**
 * @brief 析构函数
 */
    ~vector()
    {
        destroy(begin(),end());
        deallocate();
    }

    vector& operator=(const vector& other)
    {
        destroy(begin(),end());
        deallocate();
        _start=data_allocator::allocate(other.size());
        _end=uninitialized_copy(other.begin(),other.end(),begin());
    }

    data_allocator get_allocator()const
    {
        return data_allocator();
    }

    pointer data()
    {
        return _start;
    }

    const pointer data()const
    {
        return _start;
    }

/**
 * @brief 起始位置的迭代器
 */
    iterator begin()const
    {
        return _start;
    }

/**
 * @brief 内存末端后移一位的迭代器
 */
    iterator end()const
    {
        return _end;
    }

    reverse_iterator rbegin()const
    {
        return end()-1;
    }

    reverse_iterator rend()const
    {
        return begin()-1;
    }

/**
 * @brief 元素数量
 */
    size_type size()const
    {
        return size_type(end()-begin());
    }

/**
 * @brief 容器可获得的最大容量
 */
    size_type max_size()const
    {
        return UINT_MAX/sizeof(T);
    }

/**
 * @brief 容器当前拥有的容量
 */
    size_type capacity()const
    {
        return size_type(_end_of_storage-begin());
    }

/**
 * @brief 容器是否为空
 */
    bool empty()const
    {
        return begin()==end();
    }

/**
 * @brief 第n个元素
 */
    reference operator[](size_type n)
    {
        return *(begin()+n);
    }

    const reference operator[](size_type n)const
    {
        return *(begin()+n);
    }

    reference at(size_type n)
    {
        if(n<size())
            return operator[](n);
        // throw n;
    }

    const reference at(size_type n)const
    {
        if(n<size())
            return operator[](n);
        // throw n;
    }

/**
 * @brief 返回第一个元素
 */
    reference front()
    {
        return *begin();
    }

/**
 * @brief 返回最后一个元素
 */
    reference back()
    {
        return *(end()-1);
    }

/**
 * @brief 在末尾添加一个元素
 */
    void push_back(const T& x)
    {
        if(_end!=_end_of_storage)
        {
            construct(_end,x);
            ++_end;
        }
        else
        {
            alloc_and_insert(x);
        }
    }

/**
 * @brief 删除最后一个元素
 */
    void pop_back()
    {
        --_end;
        destroy(end());
    }

/**
 * @brief 删除pos位置的元素，返回下一个元素的位置
 */
    iterator erase(iterator pos)
    {
        uninitialized_copy(pos+1,end(),pos);
        --_end;
        destroy(end());
        return pos;
    }

/**
 * @brief 删除[__begin,__end)的元素，返回下一个元素的位置
 */
    iterator erase(iterator first,iterator last)
    {
        iterator new_end=uninitialized_copy(last,end(),first);
        destroy(new_end,end());
        _end=new_end;
        return first;
    }

/**
 * @brief 在pos位置插入元素，返回插入元素的位置
 */
    iterator insert(iterator pos,const T&x);

/**
 * @brief 在pos位置插入n个元素
 */
    void insert(iterator pos,size_type n,const T&x);

/**
 * @brief 在pos位置插入迭代器指向的某个范围的元素的拷贝
 */
    void insert(iterator pos,iterator first,iterator last);

    template <class... Args>
    void emplace_back(Args&&... args)
    {
    }

    template <class... Args>
    void emplace(iterator pos,Args&&... args)
    {
    }

/**
 * @brief 为容器保留一定的空间
 */
    void reserve(size_type n)
    {
        if(n>max_size())
            // throw length_error();
            return;
        if(n>capacity())
        {
            iterator new_start=data_allocator::allocate(n);
            _end=uninitialized_copy(begin(),end(),new_start);
            _start=new_start;
            _end_of_storage=_start+n;
        }
    }

/**
 * @brief 变更容器大小
 */
    void resize(size_type n,const T& x)
    {
        if(n<size())
        {
            erase(begin()+n,end());
        }
        else
        {

        }
    }

    void shrink_to_fit()
    {
        iterator new_start=data_allocator::allocate(size());
        _end=uninitialized_copy(begin(),end(),new_start);
        _start=new_start;
        _end_of_storage=_end;
    }

    void clear();

    void swap(vector& x);

protected:

/**
 * @brief 数据的起始位置     
 */
    iterator _start;

/**
 * @brief 数据末尾再后移一位
 */
    iterator _end;

/**
 * @brief 容器实际拥有的内存末端位置后移一位
 */
    iterator _end_of_storage;

};

template <class T,class Alloc>
void vector<T,Alloc>::alloc_and_insert(const T&x)
{
    size_type old_size=size();
    size_type len=old_size?2*old_size:1;
    iterator new_start=data_allocator::allocate(len);
    iterator new_end=uninitialized_copy(begin(),end(),new_start);
    construct(new_end,x);
    ++new_end;
    destroy(begin(),end());
    deallocate();
    _start=new_start;
    _end=new_end;
    _end_of_storage=new_start+len;
}

template <class T,class Alloc>
typename vector<T,Alloc>::iterator vector<T,Alloc>::insert(typename vector<T,Alloc>::iterator pos,const T&x)
{
    if(_end!=_end_of_storage)
    {
        _end=uninitialized_copy(pos,end(),pos+1);
        construct(pos,x);
        return pos;
    }
    else
    {
        size_type old_size=size();
        size_type len=old_size?2*old_size:1;
        iterator new_start=data_allocator::allocate(len);
        iterator new_end=uninitialized_copy(begin(),pos,new_start);
        construct(new_end,x);
        iterator __end=uninitialized_copy(pos,end(),new_end+1);
        destroy(begin(),end());
        deallocate();
        _start=new_start;
        _end=__end;
        _end_of_storage=new_start+len;
        return new_end;
    }
}

template <class T,class Alloc>
void vector<T,Alloc>::insert(typename vector<T,Alloc>::iterator pos,size_type n,const T&x)
{
    if(n>0)
    {
        if(size_type(_end_of_storage-end())>=n)
        {
            size_type after=end()-pos;
            uninitialized_copy(pos,end(),pos+n);
        }
        else
        {

        }
    }
    return end();
}

template <class T,class Alloc>
void vector<T,Alloc>::insert
(
    typename vector<T,Alloc>::iterator pos,
    typename vector<T,Alloc>::iterator __begin,
    typename vector<T,Alloc>::iterator __end
)
{
    return end();
}

template <class T,class Alloc>
void vector<T,Alloc>::clear()
{
    destroy(begin(),end());
    deallocate();
    _start=_end=_end_of_storage=0;
}

template <class T,class Alloc>
void vector<T,Alloc>::swap(vector<T,Alloc>& x)
{

}

}


#endif