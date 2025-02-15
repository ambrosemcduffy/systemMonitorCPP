#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid() const;                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization() const;                  // TODO: See src/process.cpp
  std::string Ram() const;                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
 bool operator<(Process const& a) const;  // TODO: See src/process.cpp
 // bool operator<(Process a) const;  // TODO: See src/process.cpp
 
  void setPid(int);
  // TODO: Declare any necessary private members
 private:
  int pid;
  int ram;
};

#endif
