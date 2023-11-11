//
// Created by Echo on 2023/10/3.
//

#ifndef COSMOS_LOGGER_H
#define COSMOS_LOGGER_H

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "Global/ExternalVariables.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

class Logger {
public:
  explicit Logger(const char *logger_name, const char *filepath = nullptr, const char *pattern = nullptr);

  [[nodiscard]] const std::shared_ptr<spdlog::logger> &GetLogger() const { return m_logger; }

private:
  std::shared_ptr<class spdlog::logger> m_logger;
};

static Logger g_logger{"cosmos-logger", COSMOS_LOG_PATH "/log.log"};
#define LOG_INFO(...) SPDLOG_LOGGER_INFO(g_logger.GetLogger(), __VA_ARGS__);
#define LOG_WARN(...) SPDLOG_LOGGER_WARN(g_logger.GetLogger(), __VA_ARGS__);
#define LOG_ERROR(...) SPDLOG_LOGGER_ERROR(g_logger.GetLogger(), __VA_ARGS__);

#endif // COSMOS_LOGGER_H
