#pragma once
#include <array>
#include <cstddef>
#include <limits>

template <class Value, std::size_t N> class RingBuffer {
private:
  static constexpr std::size_t cRecordCountMax =
      std::numeric_limits<std::size_t>::max();
  std::array<Value, N> buffer_{};
  std::size_t write_index_ = 0;
  std::size_t total_records_count_ = 0;
  bool total_record_overflow_ = false;

public:
  static_assert(N > 0, "RingBuffer size must be positive");

  template <class Func> void visit(Func &&func) const {
    std::size_t elements_count =
        total_records_count_ < N ? total_records_count_ : N;
    std::size_t start_index =
        write_index_ < total_records_count_ ? write_index_ : 0;
    for (std::size_t i = 0; i < elements_count; ++i) {
      func(buffer_[(start_index + i) % N]);
    }
  }

  void push(const Value &element) {
    buffer_[write_index_] = element;
    if (!total_record_overflow_) {
      ++total_records_count_;
    }
    if (total_records_count_ == cRecordCountMax) {
      total_record_overflow_ = true;
    }
    write_index_ = (write_index_ + 1) % N;
  }

  std::size_t capacity() const noexcept { return N; }

  std::size_t records_count() const noexcept { return total_records_count_; }

  bool records_count_overflow() const noexcept {
    return total_record_overflow_;
  }
};
