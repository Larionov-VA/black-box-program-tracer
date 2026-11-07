#pragma once

#include <ostream>

namespace bbtrace_output {
template <typename Buffer>
void export_text(const Buffer &buffer, std::ostream &output) {
  buffer.visit([&](const auto &event) {
    output << event.sequence << '\t'
           << event.timestamp.time_since_epoch().count() << '\t'
           << event.message << '\n';
  });
}
} // namespace bbtrace_output
