#include <log_module.h>
#include <notification.h>
#include <utility>
#include <regex>
#include <algorithm>
#include <iterator>



std::vector<std::string> splitter(std::string in_pattern, std::string content){
    std::vector<std::string> split_content;

    std::regex pattern(in_pattern);
    std::copy(std::sregex_token_iterator(content.begin(), content.end(), pattern, -1),
    std::sregex_token_iterator(),back_inserter(split_content));
    return split_content;
}



std::string eraseSubStr(std::string mainStr, const std::string &toErase) {
  // Search for the substring in string
  size_t pos = mainStr.find(toErase);

  if (pos != std::string::npos) {
    // If found then erase it from string
    mainStr.erase(pos, toErase.length());
  }
  return mainStr;
}

log_module::log_module(std::string Path) {
  PathToLogDir = Path;
  Notify = new notify(Path);
}

log_module::~log_module() {}

void log_module::AddModule(
    std::string ModuleName,
    std::function<void(std::string, std::string)> CallBack) {
  crawler data(ModuleName, PathToLogDir + '*');
  LinksToLog = data.GetLinks();
  for (auto it : LinksToLog) {
    //std::cout << it << std::endl;
    Loger.push_back(new log_loger(it));
    Notify->AddFileName(eraseSubStr(it, "/var/log/"), CallBack);
  }
  Notify->AddLogerInstance(Loger);
}

std::string log_module::GetWholeLog(std::string ModuleName, int len) {
  std::string WholeLog;

  for (auto it : Loger) {
    auto out = (it->GetFileName()).find(ModuleName);
    if (out != std::string::npos) {
      it->ReadWholeLog();
      if(len==0){
      WholeLog += it->ReadLog();
      } else
     if(len >0)
     {
	int tmp_len=0;
	std::vector<std::string> lines = splitter(R"(\n)", it->ReadLog());
	std::vector<std::string>::reverse_iterator rit = lines.rbegin();
	for(; rit!=lines.rend();++rit)
	{
	 WholeLog+=*rit;
	 WholeLog+="\n\r";
	if(++tmp_len>len){break;}
	}

     }
    }
  }
  if(len>0)
 {
 std::vector<std::string> lines = splitter(R"(\n)", WholeLog);
 std::vector<std::string>::reverse_iterator rit = lines.rbegin();
 WholeLog.clear();
 for(; rit!=lines.rend();++rit)
        {
         WholeLog+=*rit;
         WholeLog+="\n\r";
        }
}
  return WholeLog;
}
