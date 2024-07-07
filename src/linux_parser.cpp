#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
        float memTotal{0};
        float memFree{0};
        float buffers{0};
        float cache{0};
        string line;
        string key;
        float value;
        string mem;
        std::ifstream stream(kProcDirectory+kMeminfoFilename);
        while (std::getline(stream, line)){
                std::istringstream linestream(line);
                linestream >> key >> value >> mem;
                if (key=="MemTotal:"){
                        memTotal = value;
                }else if (key=="MemFree:"){
                        memFree = value;
                } else if (key=="Buffers:"){
                        buffers=value;
                } else if (key=="Cached:"){
                        cache=value;
                        break;
                }

        };
        //std::istringstream linestream(line);
        //linestream >> key >> value >> mem;
        //std::cout << key << std::endl;
        //std::cout << memFree << std::endl;
        //std::cout << buffer << std::endl;
        float totalMemoryUsed = (memTotal-memFree);
        float nonCacheBufferMem = totalMemoryUsed - (buffers+cache);
        return nonCacheBufferMem/memTotal;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
        std::ifstream stream(kProcDirectory+kUptimeFilename);
        string line;
        std::getline(stream, line);
        std::istringstream linestream(line);

        long systemUptime;
        long idleUptime;
        linestream >> systemUptime >> idleUptime;
        return systemUptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
        std::ifstream stream(kProcDirectory+kStatFilename);
        string line;
        string key;
        int value;
        if (stream.is_open()){
                while(std::getline(stream, line)){
                        std::istringstream stream(line);
                        stream >> key >> value;
                        if (key=="processes"){
                                return value;
                        }

                }
        }
        return 0; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
        std::ifstream stream(kProcDirectory+kStatFilename);
        string line;
        string key;
        int value;
        if (stream.is_open()){
                while(std::getline(stream, line)){
                        std::istringstream stream(line);
                        stream >> key >> value;
                        if (key=="procs_running"){
                                return value;
                        }

                }
        }
        return 0; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
        
        string line;

        string _stringPid = std::to_string(pid);
        std::ifstream stream(kProcDirectory+_stringPid+kCmdlineFilename);
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream  >> line;
        return line;
        }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
        string line;
        string key;
        string value;
        string memsize;

        string _stringPid = std::to_string(pid);
        std::ifstream stream(kProcDirectory+_stringPid+kStatusFilename);
        if (stream.is_open()){
                while(std::getline(stream, line)){
                                std::istringstream linestream(line);
                                linestream >> key >> value >> memsize;
                                if (key=="VmSize:"){
                                return value;}
                                }
        }
        return " "; 

}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {

        string line;
        string key;
        string value;
        string other;
        
        string _stringPid = std::to_string(pid);
        std::ifstream stream(kProcDirectory+_stringPid+kStatusFilename);
        if (stream.is_open()){
                while(std::getline(stream, line)){
                                std::istringstream linestream(line);
                                linestream >> key >> value >> other;
                                if (key=="Uid:"){
                                        return value;
                                }
                }
        }
        return " "; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
        string userName;
        string userPassword;
        string userID;
        string other;
        string processUid = LinuxParser::Uid(pid);

        string line;
        string _stringPid = std::to_string(pid);
        std::ifstream stream(kPasswordPath);
        if (stream.is_open()){
                while(std::getline(stream, line)){
                        std::replace(line.begin(), line.end(),':', ' ');
                        std::istringstream linestream(line);
                        linestream >> userName >> userPassword >> userID >> other;
                        if (userID == processUid){
                        return userName;
                        }
                }
        }


        return " "; 

}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) {return 0; }
