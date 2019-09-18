#ifndef NOTIFICATION
#define NOTIFICATION
#include <limits.h>
#include <loger.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

class notify {
 private:
  std::vector<std::tuple<std::string, std::function<void(std::string,std::string)>>> File;
  std::string Path;
  int inotifyFD;
  int inotifyWD;
  struct sigaction sig_a;
  std::function<void(int)> callback;
  char buff[BUF_LEN];
  char *p;
  struct inotify_event *event;
  ssize_t numRead;
  void handler(int sig);
  std::vector<log_loger *> Loger;
  std::string eraseSubStr(std::string mainStr, const std::string &toErase);

 public:
  notify(std::string LogDir);
  ~notify();
  void AddLogerInstance(std::vector<log_loger *> LogInst);
  void AddFileName(std::string FileName,
                   std::function<void(std::string,std::string)> func = nullptr);
};

#endif
