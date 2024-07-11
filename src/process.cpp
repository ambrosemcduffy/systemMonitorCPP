#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"
#include "process.h"
using std::string;
using std::to_string;
using std::vector;

void Process::setPid(int newPid) { this->pid = newPid; }
// TODO: Return this process's ID
int Process::Pid() const { return this->pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() const { 
        //std::cout << LinuxParser::Ram(10) << std::endl;
        return LinuxParser::Ram(Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a [[maybe_unused]]) const {
//        const string ram = a.Ram();
//        return true;
//}
//

bool Process::operator<(Process const& a) const {
        long ram1 = std::stol(Ram());
        long ram2 = std::stol(a.Ram());
        return ram2 < ram1;
}
