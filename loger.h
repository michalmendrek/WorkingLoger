#ifndef LOG_LOGER
#define LOG_LOGER

#include <fstream>
#include <iostream>

class log_loger {
 private:
  std::string LogFileName;
  std::string LogContent;
  std::string LogContentOld;
  int LastContentRead;
  int FileLineNumber;
  int OldFileLineNumber;
  std::ifstream LogFile;
  //int GetLineNumber();
  std::string EraseOldContent(std::string& ActualData,
                              const std::string& OldContent);

 public:
  log_loger(std::string FileName);
  ~log_loger();
  std::string ReadNewData();
  std::string ReadLog();
  void UpdateData();
  void ReadWholeLog();
  void ReadWholeLog(int num_read);
  std::string GetFileName();
  int GetLineNumber();
};

#endif
