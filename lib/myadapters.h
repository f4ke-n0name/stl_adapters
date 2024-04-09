#include "myiterators.h"

template <typename Range, typename Function>
class TransformView {
 public:
  using const_iterator =
      TransformIterator<typename Range::const_iterator, Function>;
  TransformView(const Range& range, const Function& function)
      : begin_({range.begin(), function}), end_({range.end(), function}) {}
  const_iterator begin() const { return begin_; }
  const_iterator end() const { return end_; }

 private:
  const_iterator begin_;
  const_iterator end_;
};

template <class Function>
class Transform {
 private:
  Function function_;

 public:
  Transform(const Function& function) : function_(function) {}
  Function GetFunction() const { return function_; }
};

template <typename Range, typename Function>
class FilterView {
 public:
  using const_iterator =
      FilterIterator<typename Range::const_iterator, Function>;

  FilterView(const Range& range, const Function& function)
      : begin_({range.begin(), range.end(), function}),
        end_({range.end(), range.begin(), function}) {
    while (begin_ != end_ && !function(*begin_)) {
      ++begin_;
    }
  }
  const_iterator begin() const { return begin_; }

  const_iterator end() const { return end_; }

 private:
  const_iterator begin_;
  const_iterator end_;
};

template <class Function>
class Filter {
 private:
  Function function_;

 public:
  Filter(const Function& function) : function_(function) {}
  Function GetFunction() const { return function_; }
};

template <typename Range>
class TakeView {
 public:
  using const_iterator = Range::const_iterator;

  TakeView(const Range& range, size_t num)
      : begin_({range.begin()}), end_({range.begin()}) {
    while (end_ != range.end() && num) {
      --num;
      ++end_;
    }
  }
  const_iterator begin() { return begin_; }
  const_iterator end() { return end_; }

 private:
  const_iterator begin_;
  const_iterator end_;
};

class Take {
 private:
  size_t num_;

 public:
  Take(size_t num) : num_(num) {}
  size_t GetNum() const { return num_; }
};

template <typename Range>
class DropView {
 public:
  using const_iterator = Range::const_iterator;

  DropView(const Range& range, size_t num)
      : begin_({range.begin()}), end_({range.end()}) {
    while (begin_ != end_ && num) {
      --num;
      ++begin_;
    }
  }
  const_iterator begin() { return begin_; }
  const_iterator end() { return end_; }

 private:
  const_iterator begin_;
  const_iterator end_;
};

class Drop {
 private:
  size_t num_;

 public:
  Drop(size_t num) : num_(num) {}
  size_t GetNum() const { return num_; }
};

template <typename Range>
class ReverseView {
 public:
  using const_iterator = ReverseIterator<typename Range::const_iterator>;
  ReverseView(const Range& range) : begin_(range.end()), end_(range.begin()) {}
  const_iterator begin() const { return begin_; }
  const_iterator end() const { return end_; }

 private:
  const_iterator begin_;
  const_iterator end_;
};

class Reverse {};

template <typename Range>
class KeysView {
 public:
  using const_iterator = KeysIterator<typename Range::const_iterator>;
  KeysView(const Range& range) : begin_({range.begin()}), end_({range.end()}) {}
  const_iterator begin() const { return begin_; }
  const_iterator end() const { return end_; }

 private:
  const_iterator begin_;
  const_iterator end_;
};

class Keys;

template <typename Range>
class ValuesView {
 public:
  using const_iterator = ValuesIterator<typename Range::const_iterator>;
  ValuesView(const Range& range)
      : begin_({range.begin()}), end_({range.end()}) {}
  const_iterator begin() const { return begin_; }
  const_iterator end() const { return end_; }

 private:
  const_iterator begin_;
  const_iterator end_;
};

class Values;

template <typename Range, typename Function>
TransformView<Range, Function> operator|(
    const Range& range, const Transform<Function>& transform_function) {
  return {range, transform_function.GetFunction()};
}

template <typename Range, typename Function>
FilterView<Range, Function> operator|(const Range& range,
                                      const Filter<Function>& filter_function) {
  return {range, filter_function.GetFunction()};
}

template <typename Range>
TakeView<Range> operator|(const Range& range, const Take& take_function) {
  return {range, take_function.GetNum()};
}

template <typename Range>
DropView<Range> operator|(const Range& range, const Drop& drop_function) {
  return {range, drop_function.GetNum()};
}

template <typename Range>
ReverseView<Range> operator|(const Range& range, const Reverse&) {
  return {range};
}

template <typename Range>
KeysView<Range> operator|(const Range& range, const Keys&) {
  return {range};
}

template <typename Range>
ValuesView<Range> operator|(const Range& range, const Values&) {
  return {range};
}