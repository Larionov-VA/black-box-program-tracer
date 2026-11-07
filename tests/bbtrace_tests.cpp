
#include "../src/event.hpp"
#include "../src/ring_buffer.hpp"
#include "../src/text_exporter.hpp"

#include <gtest/gtest.h>

#include <sstream>
#include <vector>

namespace {

template <std::size_t N>
std::vector<int> snapshot(const RingBuffer<int, N> &buffer) {
  std::vector<int> result;
  buffer.visit([&result](const int &value) { result.push_back(value); });
  return result;
}

TEST(RingBufferTest, EmptyBufferHasNoElements) {
  RingBuffer<int, 3> buffer;

  EXPECT_TRUE(snapshot(buffer).empty());
}

TEST(RingBufferTest, KeepsInsertionOrder) {
  RingBuffer<int, 3> buffer;

  buffer.push(1);
  buffer.push(2);

  EXPECT_EQ(snapshot(buffer), (std::vector<int>{1, 2}));
}

TEST(RingBufferTest, OverwritesOldestElement) {
  RingBuffer<int, 3> buffer;

  buffer.push(1);
  buffer.push(2);
  buffer.push(3);
  buffer.push(4);

  EXPECT_EQ(snapshot(buffer), (std::vector<int>{2, 3, 4}));
}

TEST(TextExporterTest, WritesEventsInOrder) {
  RingBuffer<EventTrace, 2> buffer;

  buffer.push(EventTrace{1, event_time{}, "first"});
  buffer.push(EventTrace{2, event_time{}, "second"});

  std::ostringstream output;
  bbtrace_output::export_text(buffer, output);

  EXPECT_EQ(output.str(), "1\t0\tfirst\n2\t0\tsecond\n");
}

} // namespace
