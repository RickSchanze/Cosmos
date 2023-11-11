//
// Created by Echo on 2023/10/3.
//

#include "Core/Log/Logger.h"
#include "Global/GlobalDefiniation.h"

Logger::Logger(const char *logger_name, const char *filepath, const char *pattern) {
  auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  if (filepath == nullptr) {
    m_logger = std::make_shared<spdlog::logger>("cosmos-logger", spdlog::sinks_init_list{consoleSink});
  } else {
    auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filepath, true);
    m_logger = std::make_shared<spdlog::logger>(logger_name, spdlog::sinks_init_list{consoleSink, fileSink});
  }
#ifdef COSMOS_DEBUG
  m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e][thread %t][%@,%!][%l]: %v");
#else
  m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e][thread %t][%s,%!][%l]: %v");
#endif
  if (pattern != nullptr) {
    m_logger->set_pattern(pattern);
  }
}
