#pragma once

#include <format>
#include <iostream>

#define LOG_INFO(msg)                                                          \
  do {                                                                         \
    std::cout << std::format("[INFO] {}", msg) << std::endl;                   \
  } while (0)

#define LOG_ERROR(msg)                                                         \
  do {                                                                         \
    std::cerr << std::format("[ERROR] {}", msg) << std::endl;                  \
  } while (0)

#ifdef DEBUG
#define LOG_DEBUG(msg)                                                         \
  do {                                                                         \
    std::cout << std::format("[DEBUG] in {}:{}: {}", __FILE__, __LINE__, msg)  \
              << std::endl;                                                    \
  } while (0)
#else
#define LOG_DEBUG(msg)                                                         \
  do {                                                                         \
  } while (0)
#endif
