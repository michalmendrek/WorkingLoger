#include <log_module.h>
#include <iostream>
//#include <loger.h>

using namespace std;

void funkcja_testu(std::string data, std::string name) {
  std::cout << "ModName: " << name << "\n\rData: " << data << std::endl;
}

void funkcja_dwa(std::string data, std::string name) {
  std::cout << "Dwa" << std::endl;
  std::cout << "ModName: " << name << "\n\rData: " << data << std::endl;
}

int main() {
  //log_loger plik("/var/log/DrowsinessModule.err.log");
  //cout << plik.GetLineNumber() << endl;
  //plik.ReadWholeLog(10);
  //cout << plik.ReadLog() << endl;
  log_module plik("/var/log/");
  plik.AddModule("DrowsinessModule", funkcja_testu);
  std::cout << plik.GetWholeLog("DrowsinessModule", 20) << std::endl;
  while (1)
    ;
}
