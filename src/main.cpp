#include "features/greeting/greeting_service.hpp"
#include <fmt/core.h>
#include <ranges>
#include <vector>

int main() {
  using namespace features::greeting;
  GreetingService service;

  // C++20 Ranges を使用した宣言的なデータ処理
  std::vector<GreetingData> users = {{"Alice"}, {""}, {"Bob"}};

  auto results =
      users | std::views::transform([&](const auto &user) { return service.createMessage(user); });

  for (const auto &res : results) {
    if (res) {
      fmt::print("{}\n", *res); // fmt::print による出力
    } else {
      fmt::print(stderr, "Error: Invalid user data provided.\n");
    }
  }

  return 0;
}