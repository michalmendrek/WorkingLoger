#ifndef UNIX_CRAWLER
#define UNIX_CRAWLER

#include <iostream>
#include <string>
#include <vector>

class crawler {
 private:
  std::vector<std::string> LinksToLog;

 public:
  crawler(const std::string& Name, const std::string& Path);
  ~crawler();
  std::vector<std::string> GetLinks();
};

#endif
