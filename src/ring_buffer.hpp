#pragma once
#include <array>
#include <cstddef>

template <class Value, std::size_t N> class RingBuffer {
private:
  std::array<Value, N> buffer_{};
  std::size_t write_index_ = 0;
  std::size_t records_count_ = 0;

public:
  static_assert(N > 0, "RingBuffer size must be positive");

  RingBuffer() {};

  template <class Func> void visit(Func &&func) {
    std::size_t elements_count = records_count_ < N ? records_count_ : N;
    std::size_t start_index = write_index_ < records_count_ ? write_index_ : 0;
    for (std::size_t i = 0; i < elements_count; ++i) {
      func(buffer_[(start_index + i) % N]);
    }
  }

  void push(const Value &element) {
    buffer_[write_index_] = element;
    ++records_count_;
    write_index_ = (write_index_ + 1) % N;
  };

  std::size_t getCapacity() const noexcept { return N; }

  std::size_t getRecordsCount() const noexcept { return records_count_; }
};
