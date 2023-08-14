
#ifndef SORTINGS_H
#define SORTINGS_H

#include <vector>
#include <cmath>
#include <algorithm>

namespace siobko{
  template< typename Container, typename Compare >
  void bucketSort(Container& container, Compare cmp);

  template< typename RandomAccessIterator, typename Compare >
  void mergeSort(RandomAccessIterator left, RandomAccessIterator right, Compare cmp);

  template< typename RandomAccessIterator, typename Compare >
  void quickSort(RandomAccessIterator left, RandomAccessIterator right, Compare cmp);

  template< typename RandomAccessIterator, typename Compare >
  RandomAccessIterator partition(RandomAccessIterator left, RandomAccessIterator right, Compare cmp);

  template< typename RandomAccessIterator, typename Compare >
  void merge(RandomAccessIterator left, RandomAccessIterator middle, RandomAccessIterator right, Compare cmp);

  template< typename Container, typename Compare >
  void bucketSort(Container& container, std::size_t size, Compare cmp)
  {
    using value_type = typename Container::value_type;

    std::size_t bucketsAmount = size;
    value_type min = *(std::min_element(container.begin(), container.end()));
    value_type max = *(std::max_element(container.begin(), container.end()));

    double range = std::floor(max - min + 1);
    std::vector< std::vector< value_type > > buckets(bucketsAmount);
    for (auto& item: container) {
      int i = std::floor(bucketsAmount * (item - min) / range);
      buckets[i].push_back(item);
    }
    for (auto& bucket: buckets) {
      quickSort(bucket.begin(), bucket.end(), cmp);
    }

    auto container_iterator = container.begin();

    if (cmp(min, max)) {
      for (auto it = buckets.begin(); it != buckets.end(); it++) {
        for (auto bucketIt = it->begin(); bucketIt != it->end(); bucketIt++, container_iterator++) {
          *container_iterator = *bucketIt;
        }
      }
      return;
    }
    for (auto it = buckets.rbegin(); it != buckets.rend(); it++) {
      for (auto bucketIt = it->begin(); bucketIt != it->end(); bucketIt++, container_iterator++) {
        *container_iterator = *bucketIt;
      }
    }
  }

  template< typename RandomAccessIterator, typename Compare >
  void mergeSort(RandomAccessIterator left, RandomAccessIterator right, Compare cmp)
  {
    if (right - left > 1) {
      RandomAccessIterator middle = left + (right - left) / 2;
      mergeSort(left, middle, cmp);
      mergeSort(middle, right, cmp);
      std::inplace_merge(left, middle, right, cmp);
    }
  }

  template< typename RandomAccessIterator, typename Compare >
  void quickSort(RandomAccessIterator left, RandomAccessIterator right, Compare cmp)
  {
    if (std::distance(left, right) < 2) {
      return;
    }

    RandomAccessIterator pivot = siobko::partition(left, right, cmp);
    quickSort(left, pivot, cmp);
    quickSort(std::next(pivot), right, cmp);
  }

  template< typename RandomAccessIterator, typename Compare >
  RandomAccessIterator partition(RandomAccessIterator left, RandomAccessIterator right, Compare cmp)
  {
    RandomAccessIterator pivot = left;
    RandomAccessIterator tmp = std::next(left);
    for (RandomAccessIterator i = std::next(left); i != right; ++i) {
      if (cmp((*i), (*pivot))) {
        std::swap((*tmp++), (*i));
      }
    }
    std::swap((*pivot), *(std::prev(tmp)));
    return prev(tmp);
  }

  template< typename RandomAccessIterator, typename Compare >
  void merge(RandomAccessIterator left, RandomAccessIterator middle, RandomAccessIterator right, Compare cmp)
  {
    std::vector< typename RandomAccessIterator::value_type > result(std::distance(left, right));

    auto leftIt = left;
    auto rightIt = middle;

    while (leftIt != middle && rightIt != right) {
      result.push_back(cmp(*leftIt, *rightIt) ? std::move(*leftIt++) : std::move(*rightIt++));
    }

    result.insert(result.end(), std::make_move_iterator(leftIt), std::make_move_iterator(middle));
    result.insert(result.end(), std::make_move_iterator(rightIt), std::make_move_iterator(right));
    std::move(result.begin(), result.end(), left);
  }
}
#endif
