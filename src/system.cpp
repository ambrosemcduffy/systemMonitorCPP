#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

#include <iostream>

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  std::vector<int> processPids;
  processPids = LinuxParser::Pids();

  for (auto pid : processPids) {
    Process myprocess;
    myprocess.setPid(pid);
    if (!myprocess.Ram().empty() && !myprocess.Command().empty()){
     processes_.push_back(myprocess);

    }
   }
  return processes_;
}

//int main(){
//        System mysys;
//        vector<Process>& procs = mysys.Processes();
//        for(auto proc:procs){
//                std::cout << proc.Pid() << "  " << proc.User() << "  " << proc.Ram() << "  " << proc.Command() << "  " << std::endl;
//        }
//}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }
