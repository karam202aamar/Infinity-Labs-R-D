 /*******************************************************************************
* Project: BitSet - represents a fixed-size sequence of SIZE bits
* Date: 26.01.2023
* Author: karam
* Reviewer: raz 
* Version: 1.0
*******************************************************************************/
#ifndef __ILRD_HRD26_BITSET_HPP___
#define __ILRD_HRD26_BITSET_HPP___
/******************************************************************************/
#include <cstddef>       //size_t
#include <iostream>      //ostream
#include <vector>        //vector
#include <bits/stdc++.h> //CHAR_BIT
/******************************************************************************/
static const size_t WORD_SIZE = sizeof(size_t) * CHAR_BIT;
/******************************************************************************/
namespace ilrd::hrd26
{

template <size_t SIZE>
class BitSet;

template <size_t SIZE>
std::ostream& operator<<(std::ostream& os_, const BitSet<SIZE>& bitset_);

template <size_t SIZE>
class BitSet
{
private:
    class BitProxy;

public:        
    explicit BitSet();
    //using generated Copy Ctor, Copy Assignment and Dtor
    bool operator==(const BitSet& other_) const;
    BitSet& operator&=(const BitSet& other_);
    BitSet& operator|=(const BitSet& other_);
    BitSet& operator^=(const BitSet& other_);

    bool operator[](size_t index_) const;
    BitProxy operator[](size_t index_);

    size_t CountTrueBits() const;

private:
    std::vector<size_t> m_vector;
    static const size_t s_size = (SIZE / sizeof(size_t)) +
                                                ((SIZE % sizeof(size_t)) != 0);

    friend std::ostream& operator<<<SIZE>(std::ostream& os_,
                                                 const BitSet<SIZE>& bitset_);

};//class BitSet

/***********************************BITPROXY***********************************/
template <size_t SIZE>
class BitSet<SIZE>::BitProxy 
{
public:
    explicit BitProxy(BitSet<SIZE>& bitset_, size_t index_);
    BitProxy& operator=(bool b_); //handles: BitProxy(b1, 7).operator=(true)
    BitProxy& operator=(const BitProxy& other_); //handles: b1[3] = b1[7]
    operator bool() const;

private:
    BitSet<SIZE>& m_bitset;
    size_t m_index;
}; 

/********************************IMPLEMENTATIONS*******************************/
template <size_t SIZE>
BitSet<SIZE>::BitSet(): m_vector(s_size, 0)
{
    //EMPTY
}
/***********************************IS EQUAL***********************************/
template <size_t SIZE>
bool BitSet<SIZE>::operator==(const BitSet& other_) const
{
    
    return std::equal(m_vector.begin(), m_vector.end(), other_.m_vector.begin());
}
/**************************************&=**************************************/
template <size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator&=(const BitSet& other_)
{
    std::transform(m_vector.begin(), m_vector.end(), 
            other_.m_vector.begin(), m_vector.begin(), std::bit_and<size_t>());

    return *this;
}
/**************************************|=**************************************/
template <size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator|=(const BitSet& other_)
{
    std::transform(m_vector.begin(), m_vector.end(), 
            other_.m_vector.begin(), m_vector.begin(), std::bit_or<size_t>());

    return *this;
}
/**************************************^=**************************************/
template <size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator^=(const BitSet& other_)
{
    std::transform(m_vector.begin(), m_vector.end(), 
            other_.m_vector.begin(), m_vector.begin(), std::bit_xor<size_t>());

    return *this;
}
/*******************************CONST OPERATOR[]*******************************/
template <size_t SIZE>
bool BitSet<SIZE>::operator[](size_t index_) const
{
    /*get the num inside the vector*/
    size_t num_in_chunk = this->m_vector[index_ / (WORD_SIZE)];
    size_t bit_loc_in_chunk = index_ % CHAR_BIT;
    return (num_in_chunk & (1UL << bit_loc_in_chunk));
}
/********************************COUNT TRUE BITS*******************************/
template <size_t SIZE>
size_t BitSet<SIZE>::CountTrueBits() const
{
    size_t tmp = 0;
    std::vector<size_t>::const_iterator vec_iterator;
    size_t ret = 0;

    for(vec_iterator=m_vector.begin(); vec_iterator<m_vector.end(); ++vec_iterator)
    {
        tmp = *vec_iterator;
        while(tmp)
        {
            /*turn off most right bit*/
            tmp &= tmp - 1;
            ++ret;
        }
    }
    return ret;
}
/*******************************PRINTING OPERATOR******************************/
template <size_t SIZE>
std::ostream& operator<<(std::ostream& os, const BitSet<SIZE>& bitset)
{
    std::vector<size_t>::const_iterator vec_iterator;

    for(vec_iterator=bitset.m_vector.begin(); vec_iterator
                                        <bitset.m_vector.end(); ++vec_iterator)
    {
        size_t tmp = *vec_iterator;
        size_t bit_mask = (size_t)1 << ((sizeof(size_t) * CHAR_BIT) - 1);

        for(size_t i=0; i<((sizeof(size_t)*CHAR_BIT)-1); ++i)
        {
            os << ((bit_mask >> i) & tmp ? "1" : "0");
        }
    }
    return os;
}
/*******************************BOOL ASSIGNMENT********************************/
template <size_t SIZE>
typename BitSet<SIZE>::BitProxy& BitSet<SIZE>::BitProxy::operator=(bool b)
{
    size_t* map = &(m_bitset.m_vector[m_index / (sizeof(size_t) * CHAR_BIT)]);
    size_t bit_mask = (size_t)b << ((sizeof(size_t) * CHAR_BIT - 1) - 
                                    (m_index % ((sizeof(size_t) * CHAR_BIT))));

    *map &= (~bit_mask);
    *map |= bit_mask; 
    
    return *this;
}
/********************************Broxy Ctor************************************/
template <size_t SIZE>
BitSet<SIZE>::BitProxy::BitProxy(BitSet<SIZE>& bitset, size_t index)
    : m_bitset(bitset)
    , m_index(index)
{
    //empty
}
/********************************OPERATOR[] PROXY******************************/
template <size_t SIZE>
typename BitSet<SIZE>::BitProxy BitSet<SIZE>::operator[](size_t index)
{
    return BitSet<SIZE>::BitProxy(*this, index);
}
/********************************ASSIGNMENT Broxy*****************************/
template <size_t SIZE>
typename BitSet<SIZE>::BitProxy& BitSet<SIZE>::BitProxy::operator=
                                                    (const BitProxy& rhs)
{
    /* after 'bool cast' call 'bool assignment' */
    *this = (bool)rhs;
    /* return this (proxy type)*/
    return *this;
}
/**********************************BOOL CAST***********************************/
template <size_t SIZE>
BitSet<SIZE>::BitProxy::operator bool() const
{
    size_t mask = 1;
    size_t ret_bool = m_bitset.m_vector[m_index / SIZE] >> (63 - m_index);

    return mask & ret_bool;  
   
}

} //ilrd::hrd26

#endif //__ILRD_HRD26_BITSET_HPP___



