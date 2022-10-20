// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: BSD-3-Clause
// See: https://spdx.org/licenses/

#include <message_infrastructure/csrc/core/message_infrastructure_logging.h>

namespace message_infrastructure {

namespace {

// const char *kLogModuleName[] = {
//   "LOG_MULL_MODULE",
//   "LOG_MPROC",  // multiprocess
//   "LOG_ACTOR",
//   "LOG_LAYER",
//   "LOG_SHMEM",
//   "LOG_SHSKT"
// };

signed int GetPid() {
  return getpid();
}

std::string GetTime() {
  char buf[MAX_SIZE_LOG_TIME] = {};
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);
  int end = strftime(buf, sizeof(buf), "%Y-%m-%d.%X", gmtime(&ts.tv_sec));
  snprintf(buf + end, MAX_SIZE_LOG_TIME-end, " %09ld", ts.tv_nsec);
  std::string ret = std::string(buf);
  return ret;
}

}  // namespace

LogMsg::LogMsg(const std::string &msg_data,
               const char *log_file,
               const int log_line,
               const char *log_level)
    : msg_data_(msg_data),
      msg_line_(log_line),
      msg_file_(log_file),
      msg_level_(log_level) {
  msg_time_ = GetTime();
}

std::string LogMsg::GetEntireLogMsg(int pid) {
  std::stringstream buf;
  buf << msg_time_    << " ";
  buf << msg_level_   << " ";
  buf << pid          << " ";
  buf << msg_file_    << ":";
  buf << msg_line_    << " ";
  buf << msg_data_;
  return buf.str();
}

MessageInfrastructureLog::MessageInfrastructureLog() {
  char *log_path = getenv("MSG_LOG_PATH");
  if (log_path == NULL) {
    log_path = getcwd(NULL, 0);
    log_path_ = log_path;
    free(log_path);
    return;
  }
  log_path_ = log_path;
}

// multithread safe
void MessageInfrastructureLog::LogWrite(const LogMsg& msg) {
  std::lock_guard<std::mutex> lg(log_lock_);
  log_queue_.push(msg);
    if (log_queue_.size() == MAX_SIZE_LOG) {
      WriteDown();
  }
}

// multithread unsafe
void MessageInfrastructureLog::Clear() {
  std::queue<LogMsg>().swap(log_queue_);
}

// multithread unsafe
void MessageInfrastructureLog::WriteDown() {
  if (log_queue_.empty()) return;
  int i = 0;
  signed int pid = GetPid();
  std::stringstream log_file_name;
  log_file_name << log_path_ << "/" << DEBUG_LOG_MODULE << "_pid_" << pid \
                << "." << DEBUG_LOG_FILE_SUFFIX;
  std::fstream log_file;
  log_file.open(log_file_name.str(), std::ios::app);
  while (!log_queue_.empty()) {
    std::string log_str = log_queue_.front().GetEntireLogMsg(pid);
    log_file << log_str;
    log_queue_.pop();
  }
  log_file.close();
}

MessageInfrastructureLog::~MessageInfrastructureLog() {
  WriteDown();
}

void LogClear() {
#if MSG_LOG_PRINT_MODE & LOG_PRINT_MASK_FILE
  GetLogInstance()->Clear();
#endif
}

MessageInfrastructureLogPtr log_instance;

MessageInfrastructureLogPtr GetLogInstance() {
  if (log_instance == nullptr) {
    log_instance = std::make_shared<MessageInfrastructureLog>();
  }
  return log_instance;
}

}  // namespace message_infrastructure
