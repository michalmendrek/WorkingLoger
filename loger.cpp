#include <loger.h>
#include <sys/inotify.h>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

log_loger::log_loger(std::string FileName) {
  LogFileName = FileName;
  LogFile.open(LogFileName, std::ifstream::in);
}

log_loger::~log_loger() { LogFile.close(); }

void log_loger::ReadWholeLog() {
  if (LogFile.good()) {
    FileLineNumber=GetLineNumber();
    LogContent.clear();
    LogFile.seekg(0, std::ios::end);
    LogContent.reserve(LogFile.tellg());
    LogFile.seekg(0, std::ios::beg);
    LogContent.assign((std::istreambuf_iterator<char>(LogFile)),
                      std::istreambuf_iterator<char>());
  }
  LastContentRead = 0;
}

int log_loger::GetLineNumber() {
  int number(0);
  int tmp(0);
  std::string unused;
  while (std::getline(LogFile, unused)) {
    ++number;
  }
  LogFile.close();
  LogFile.open(LogFileName);
  return number;
}

void log_loger::ReadWholeLog(int num_read) {
  int number = GetLineNumber();
    FileLineNumber = number;
    LastContentRead=num_read;
    std::string unused;
    int tmp(0);
    while (std::getline(LogFile, unused)) {
      ++tmp;
      if (tmp > (number - num_read)) {
        LogContent += unused;
        LogContent += "\n\r";
      }
    }
  LogFile.close();
  LogFile.open(LogFileName);
}

std::string log_loger::ReadNewData() {
  if (LogContent.length() > LogContentOld.length()) {
    return EraseOldContent(LogContent, LogContentOld);
  }
  return " ";
}

void log_loger::UpdateData() {
  OldFileLineNumber=FileLineNumber;
  int diff= GetLineNumber() - OldFileLineNumber;

  std::cout <<"Diff in len in file: " << diff <<std::endl;

  LogContentOld.clear();
  LogContentOld = LogContent;
  if(diff > 0)
  {
    ReadWholeLog(diff);

  }
  /*
  if (LastContentRead == 0) {
    ReadWholeLog(LastContentRead);
  } else if (LastContentRead > 0) {
    ReadWholeLog(LastContentRead);
  }*/
}

std::string log_loger::ReadLog() { return LogContent; }

std::string log_loger::EraseOldContent(std::string& ActualData,
                                       const std::string& OldContent) {
  std::string temporary = ActualData;
  if (OldContent == ActualData) {
    return " ";
  }

  size_t position = temporary.find(OldContent);
  if (position != std::string::npos) {
    temporary.erase(position, OldContent.length());
  }
  return temporary;
}

std::string log_loger::GetFileName() { return LogFileName; }
