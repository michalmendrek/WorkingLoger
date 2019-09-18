#ifndef LOG_MODULE
#define LOG_MODULE

#include <loger.h>
#include <notification.h>
#include <unix_crawler.h>
#include <memory>

class log_module {
 private:
  std::vector<std::string> LinksToLog;
  std::string PathToLogDir;
  std::vector<log_loger *> Loger;
  notify *Notify;
 public:
  log_module(std::string Path);
  ~log_module();
  //notify *Notify;
  //std::vector<log_loger *> Loger;
  void AddModule(std::string ModuleName, std::function<void(std::string,std::string)> CallBack);
  std::string GetWholeLog(std::string ModuleName, int len =0);
};

#endif
