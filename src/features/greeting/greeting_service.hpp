#pragma once
#include "../../shared/result.hpp"
#include "greeting_data.hpp"

namespace features::greeting {
class GreetingService {
public:
  // 状態を変更しない const メソッド
  [[nodiscard]] Result<std::string> createMessage(const GreetingData &data) const;
};
} // namespace features::greeting