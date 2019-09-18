#include <log_module.h>
#include <iostream>
using namespace std;

void funkcja_testu(std::string data, std::string name) {
  std::cout << "ModName: " << name << "\n\rData: " << data << std::endl;
}

void funkcja_dwa(std::string data, std::string name) {
  std::cout << "Dwa" << std::endl;
  std::cout << "ModName: " << name << "\n\rData: " << data << std::endl;
}

int main() {
  log_module plik("/var/log/");
  plik.AddModule("DrowsinessModule", funkcja_testu);
  std::cout << plik.GetWholeLog("DrowsinessModule") << std::endl;
  while (1)
    ;
}
