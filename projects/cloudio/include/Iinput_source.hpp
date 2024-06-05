/*******************************************************************************
* Project:   
* Date: 15-Feb-2023
* Author: HRD26
* Reviewer: TBD
* Version: 1.0
*******************************************************************************/
#ifndef __ILRD_HRD26_I_INPUT_SOURCE_HPP__
#define __ILRD_HRD26_I_INPUT_SOURCE_HPP__

namespace ilrd
{
namespace hrd26
{

template<typename Key, typename Args>
class IInputSource
{
public:
    explicit IInputSource() = default;
    virtual ~IInputSource() = default;
    virtual std::pair<Key,Args> Read() = 0;
    virtual int GetFD() = 0;
};

} // namespace hrd26
} // namespace ilrd
#endif //__ILRD_I_INPUT_SOURCE_HPP__




