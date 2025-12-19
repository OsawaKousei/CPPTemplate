cmake_minimum_required(VERSION 3.22)
project(CppTemplate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 1. tl::expected の自動取得 (Result型アプローチ)
include(FetchContent)
set(EXPECTED_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  expected
  GIT_REPOSITORY https://github.com/TartanLlama/expected.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(expected)
if(NOT expected_POPULATED)
  FetchContent_Populate(expected)
  # SYSTEMフラグを付けて追加（警告を無視させる）
  add_subdirectory(${expected_SOURCE_DIR} ${expected_BINARY_DIR} SYSTEM)
endif()

# 2. fmt (FetchContent で管理)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        10.1.1 # バージョンを固定
)
FetchContent_MakeAvailable(fmt)
if(NOT fmt_POPULATED)
  FetchContent_Populate(fmt)
  add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR} SYSTEM)
endif()

# 3. 実行ファイルの定義
add_executable(app 
    src/main.cpp 
    src/features/greeting/greeting_service.cpp
)

# Sanitizerフラグを変数にまとめて管理（コンパイルとリンクの両方に適用するため）
set(SANITIZER_FLAGS "-fsanitize=address,undefined")

# コンパイルオプションの適用
target_compile_options(app PRIVATE 
    -Wall -Wextra -Werror 
    ${SANITIZER_FLAGS}
    -fno-omit-frame-pointer # デバッグ時のスタックトレースを読みやすくする
)

# リンカオプションの適用
target_link_options(app PRIVATE 
    ${SANITIZER_FLAGS}
)

target_link_libraries(app PRIVATE fmt::fmt tl::expected)