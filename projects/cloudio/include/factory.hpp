/*******************************************************************************
 * Project: Factory - Creation of multiple objects of the same base type
 * Date: 31/01/23
 * Author: HRD26
 * Reviwer: TBD
*******************************************************************************/
#ifndef __ILRD_HRD26_FACTORY_HPP__
#define __ILRD_HRD26_FACTORY_HPP__

#include <unordered_map> // std::unordered_map(hashtable)
#include <memory>        // std::shared_ptr
#include <functional>    // std::function

#include "singleton.hpp"

namespace ilrd
{
namespace hrd26
{

template <typename KEY, typename BASE, typename ARGS>
class Factory
{
public:
    //Base must contain static CreateFunc !!important
    using CreateFunc = std::function<std::shared_ptr<BASE>(ARGS args_)>;

    Factory(const Factory& other_) = delete;
    Factory& operator=(const Factory& other_) = delete;
    

    //overrides a current method if already exists
    void Add(const KEY& key_, CreateFunc create_func_);
    // Create may throw exception
    std::shared_ptr<BASE> Create(const KEY& key_, ARGS args_);
private:
    ~Factory() = default;

    explicit Factory() = default;

    std::unordered_map<KEY, CreateFunc> m_map;

    friend class Singleton<Factory>;
};
/********************************IMPLEMENTATION********************************/
template <typename KEY, typename BASE, typename ARGS>
void Factory< KEY,BASE, ARGS>::Add(const KEY& key_, CreateFunc create_func_)
{
    m_map[key_] = create_func_;
}
/*return SH_ptr to created derived instance*/
template <typename KEY, typename BASE, typename ARGS>
std::shared_ptr<BASE> Factory<KEY,BASE, ARGS>::Create(const KEY& key_, ARGS args_)
{
    return m_map[key_](args_);
}

} // namespace hrd26
} // namespace ilrd

#endif//__ILRD_HRD26_FACTORY_HPP__

