#include <chrono>
#include <string>

using event_time = std::chrono::steady_clock::time_point;

struct EventTrace {
  std::uint64_t sequence;
  event_time timestamp;
  std::string message;
};
