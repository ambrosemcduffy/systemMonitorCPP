#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"
#include "format.h"

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
  return std::string();
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
vector<string> LinuxParser::CpuUtilization() {
        std::string line;
        std::string key;
        std::vector<std::string> linesArr;
        std::ifstream stream(kProcDirectory+kStatFilename);
        if (stream.is_open()){
                while(std::getline(stream, line)){
                        std::istringstream linestream(line);
                    while (std::getline(linestream,key, ' ')){
                    linesArr.push_back(key);
                    } 
                }
        }


        vector<std::string> cpuValues(linesArr.begin()+2, linesArr.begin()+12); 
        return cpuValues;
}

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
        if (stream.is_open()){
        std::getline(stream, line);
        }
        std::istringstream linestream(line);
        linestream  >> line;
        return line;
        }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
        string line;
        string key;
        int value;
        string memsize;

        string _stringPid = std::to_string(pid);
        std::ifstream stream(kProcDirectory+_stringPid+kStatusFilename);
        if (stream.is_open()){
                while(std::getline(stream, line)){
                                std::istringstream linestream(line);
                                linestream >> key >> value >> memsize;
                                if (key=="VmSize:"){
                                return std::to_string(value/1024);}
                                }
        }
        return std::string(); 

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
                                //std::replace(line.begin(), line.end(), ' ', '_');
                                //std::replace(line.begin(), line.end(), '-', ' ');
                                //std::replace(line.begin(), line.end(),':', ' ');
                                std::istringstream linestream(line);
                                linestream >> key >> value >> other;
                                if (key=="Uid:"){
                                        return value;
                                }
                } 
        }
        return std::string();
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
                        //std::cout << "PRINTING USER AND PROCESS USER ID" << userID << " " << processUid << std::endl;
                        if (userID == processUid){
                        return userName;
                        }
                }
        }


        return std::string(); 

}



std::vector<std::string> split(std::string &token, char delimiter) {
  std::vector<std::string> tokens;
  std::istringstream mystream(token);
  while (std::getline(mystream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}


// TODO: Read and return the uptime of a process

long LinuxParser::UpTime(int pid) {
  std::string path = "/proc/" + std::to_string(pid) + "/stat";
  std::ifstream file(path);
  std::string line;
  std::vector<std::string> _arr;
  if (file){
    while (getline(file, line)){
      std::vector<std::string> fields = split(line, ' ');
      long startTime = std::stol(fields[21]);
     // std::cout << fields[21] << std::endl;
      long secs = (long)startTime / sysconf(_SC_CLK_TCK);
      return secs;
    }
  }
  return -1.0;
}

std::string formatTime(long seconds) {
    long hours = seconds / 3600;
    long minutes = (seconds % 3600) / 60;
    long secs = seconds % 60;
    std::ostringstream timeStream;
    timeStream << (hours < 10 ? "0" : "") << hours << ":"
               << (minutes < 10 ? "0" : "") << minutes << ":"
               << (secs < 10 ? "0" : "") << secs;
    return timeStream.str();
}

