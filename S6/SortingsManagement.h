
#ifndef SORTINGS_MANAGEMENT_H
#define SORTINGS_MANAGEMENT_H

#include <iostream>
#include <deque>
#include <random>
#include <algorithm>
#include <list>
#include <chrono>

#include "ForwardList.h"
#include "List.h"
#include "Sortings.h"

namespace siobko{
  template< typename Ty, typename Compare >
  class SortingsManagement {
  public:
    explicit SortingsManagement(std::size_t container_size);
    ~SortingsManagement() = default;

    void testSortings(std::ostream& out);
    void testBucketSort(std::ostream& out);
    void testQuickSort(std::ostream& out);
    void testMergeSort(std::ostream& out);

  private:
    template< typename Container >
    void printStructure(Container c, std::ostream& out);

    Ty generateRandom();

    std::vector< Ty > container_;
    Compare comp_;
  };

  template< typename Ty, typename Compare >
  Ty SortingsManagement< Ty, Compare >::generateRandom()
  {
    static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_real_distribution< double > dist(-1000, 1000);
    return dist(gen);
  }
  template< typename Ty, typename Compare >
  template< typename Container >
  void SortingsManagement< Ty, Compare >::printStructure(Container c, std::ostream& out)
  {
    auto it = c.begin();
    out << (*it++);
    while (it != c.end()) {
      out << " " << (*it++);
    }
    out << '\n';
  }

  template< typename Ty, typename Compare >
  SortingsManagement< Ty, Compare >::SortingsManagement(std::size_t container_size)
  {
    if (container_size <= 0) {
      throw std::logic_error("Error: container size must be positive.");
    }

    container_ = std::vector< Ty >(container_size);
    for (size_t i = 0; i < container_size; ++i) {
      container_[i] = generateRandom();
    }
  }
  template< typename Ty, typename Compare >
  void SortingsManagement< Ty, Compare >::testSortings(std::ostream& out)
  {
    printStructure(container_, out);
    testBucketSort(out);
    testQuickSort(out);
    testMergeSort(out);
  }

  template< typename Ty, typename Compare >
  void SortingsManagement< Ty, Compare >::testBucketSort(std::ostream& out)
  {
    std::deque< Ty > deque;
    std::copy(container_.begin(), container_.end(), std::back_inserter(deque));
    bucketSort(deque, deque.size(), comp_);
    printStructure(deque, out);

    List< Ty > list;
    std::copy(container_.begin(), container_.end(), std::back_inserter(list));
    bucketSort(list, list.size(), comp_);
    printStructure(list, out);

    ForwardList< Ty > frwdList;
    std::copy(container_.begin(), container_.end(), std::front_inserter(frwdList));
    bucketSort(frwdList, frwdList.size(), comp_);
    printStructure(frwdList, out);
  }

  template< typename Ty, typename Compare >
  void SortingsManagement< Ty, Compare >::testQuickSort(std::ostream& out)
  {
    std::deque< Ty > deque;
    std::copy(container_.begin(), container_.end(), std::back_inserter(deque));
    quickSort(deque.begin(), deque.end(), comp_);
    printStructure(deque, out);

    std::list< Ty > list;
    std::copy(container_.begin(), container_.end(), std::back_inserter(list));
    quickSort(list.begin(), list.end(), comp_);
    printStructure(list, out);
  }

  template< typename Ty, typename Compare >
  void SortingsManagement< Ty, Compare >::testMergeSort(std::ostream& out)
  {
    std::deque< Ty > deque;
    std::copy(container_.begin(), container_.end(), std::back_inserter(deque));
    mergeSort(deque.begin(), deque.end(), comp_);
    printStructure(deque, out);
  }
}
#endif
