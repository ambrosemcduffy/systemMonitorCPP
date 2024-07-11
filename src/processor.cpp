#include "processor.h"
#include <vector>
#include "linux_parser.h"
#include <string>
#include <iostream>
#include <thread>
#include <chrono>


// TODO: Return the aggregate CPU utilization
//float Processor::Utilization() { 
//        float cpuUtils = cpuUtilization();
//        return cpuUtils;
//}

std::vector<float> getCpuTimeBaby(){

        std::vector<long> valueToLong;
        std::vector<std::string> utilizationsArr= LinuxParser::CpuUtilization();
        if (utilizationsArr.size() != 0){
                for (auto cpuValue:utilizationsArr){
                       // std::cout << cpuValue << std::endl;
                        valueToLong.push_back(std::stol(cpuValue));
                }
        }
        long user = valueToLong[0];
        long nice = valueToLong[1];
        long system = valueToLong[2];
        long idle = valueToLong[3];
        long iowait = valueToLong[4];
        long irq = valueToLong[5];
        long softirq = valueToLong[6];
        long steal = valueToLong[7];
        long guest = valueToLong[8];
        long guest_nice = valueToLong[9];
        
        float active_time = user + nice + system + irq + softirq + steal;
        float idle_time = idle + iowait;
        float total_time = active_time + idle_time;
        return {total_time, active_time};

}

float cpuUtilization(){

        std::vector<float> timeVec = getCpuTimeBaby();
        
        float totalTimePrev = timeVec[0]; 
        float active_timePrev = timeVec[1];
                
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::vector<float> timeVec2 = getCpuTimeBaby();
        
        float totalTimeNow = timeVec2[0]; 
        float active_timeNow = timeVec2[1];

        float currentTime = totalTimeNow - totalTimePrev;
        float currentActiveTime = active_timeNow - active_timePrev;
        float cpuUtil = currentActiveTime/currentTime;
        return cpuUtil;
}

float Processor::Utilization() { 
        float cpuUtils = cpuUtilization();
        return cpuUtils;
}

//int main(){
//        float cpuUtils = cpuUtilization();
//}
