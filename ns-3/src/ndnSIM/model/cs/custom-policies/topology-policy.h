/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/* Topology policy
 * by modifying lfu policy
 */

#ifndef TOPOLOGY_POLICY_H_
#define TOPOLOGY_POLICY_H_

#include <boost/intrusive/options.hpp>
#include <boost/intrusive/set.hpp>
#include "../../ndn-spt.h"

namespace ns3 {
namespace ndn {

double getWeight(int nodeId, name::Component key);

namespace ndnSIM {

/**
 * @brief Traits for Topology replacement policy
 */
struct topology_policy_traits
{
  /// @brief Name that can be used to identify the policy (for NS-3 object model and logging)
  static std::string GetName () { return "Topology"; }

  struct policy_hook_type : public boost::intrusive::set_member_hook<> { double frequency; };

  template<class Container>
  struct container_hook
  {
    typedef boost::intrusive::member_hook< Container,
                                           policy_hook_type,
                                           &Container::policy_hook_ > type;
  };

  template<class Base,
           class Container,
           class Hook>
  struct policy
  {
    static double& get_order (typename Container::iterator item)
    {
      return static_cast<policy_hook_type*>
        (policy_container::value_traits::to_node_ptr(*item))->frequency;
    }

    static const double& get_order (typename Container::const_iterator item)
    {
      return static_cast<const policy_hook_type*>
        (policy_container::value_traits::to_node_ptr(*item))->frequency;
    }

    template<class Key>
    struct MemberHookLess
    {
      bool operator () (const Key &a, const Key &b) const
      {
        return get_order (&a) < get_order (&b);
      }
    };

    typedef boost::intrusive::multiset< Container,
                                   boost::intrusive::compare< MemberHookLess< Container > >,
                                   Hook > policy_container;

    // could be just typedef
    class type : public policy_container
    {
    public:
      typedef policy policy_base; // to get access to get_order methods from outside
      typedef Container parent_trie;

      type (Base &base)
        : base_ (base)
        , max_size_ (100)
      {
      }

      inline void
      update (typename parent_trie::iterator item)
      {
        policy_container::erase (policy_container::s_iterator_to (*item));
        //get_order (item) += 1;
        policy_container::insert (*item);
      }

      inline bool
      insert (typename parent_trie::iterator item)
      {
        //get_order (item) = 0;
        //TODO: get nodeId
        get_order (item) = getWeight(0, (*item).key ());

        if (max_size_ != 0 && policy_container::size () >= max_size_)
          {
            // this erases the "least frequently used item" from cache
            base_.erase (&(*policy_container::begin ()));
          }

        policy_container::insert (*item);

        return true;
      }

      inline void
      lookup (typename parent_trie::iterator item)
      {
        policy_container::erase (policy_container::s_iterator_to (*item));
        //get_order (item) += 1;
        policy_container::insert (*item);
      }

      inline void
      erase (typename parent_trie::iterator item)
      {
        policy_container::erase (policy_container::s_iterator_to (*item));
      }

      inline void
      clear ()
      {
        policy_container::clear ();
      }

      inline void
      set_max_size (size_t max_size)
      {
        max_size_ = max_size;
      }

      inline size_t
      get_max_size () const
      {
        return max_size_;
      }

    private:
      type () : base_(*((Base*)0)) { };

    private:
      Base &base_;
      size_t max_size_;
    };
  };
};

} // ndnSIM
} // ndn
} // ns3

#endif // TOPOLOGY_POLICY_H_
