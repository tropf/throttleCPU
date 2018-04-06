#include <map>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>

std::map<std::string, unsigned int> readConfigFile(){
    std::ifstream conffile("/etc/throttleCPU.conf");
    std::string line, key;
    unsigned int value;
    std::map<std::string, unsigned int> config;

    while (std::getline(conffile, line))
    {
        std::istringstream iss(line);
        iss >> key;
        std::cout << "KEY: " << key << std::endl;
        iss >> value;
        std::cout << "VALUE: " << value << std::endl;
        config[key] = value;
    }

    if(config.size() == 0){
        std::cout << "WARNING: EMPTY CONFIG" << std::endl;
    }
    return config;
}

int writeMaxCpuFreq(unsigned int cpu, unsigned long freq){
    std::string path = "/sys/devices/system/cpu/cpu";
    path += std::to_string(cpu);
    path += "/cpufreq/scaling_max_freq";
    std::ofstream freqFile;
    freqFile.open (path);
    freqFile << freq;
    freqFile.close();
}

bool isCharging(){
    std::string status;
    std::ifstream file("/sys/class/power_supply/AC/online");
    std::getline(file, status);
    if(status == "1") return true;
    return false;
}

int main(int argc, char *argv[])
{
    auto config = readConfigFile();
    auto dischargeFreq = config["DISCHARGE"];
    auto chargeFreq = config["CHARGE"];
    auto repeat = config["REPEAT"];
    auto stateNow = isCharging();
    auto stateLast = !stateNow;
    int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    std::cout << "NUMCPU: " << numCPU << std::endl;
    int freq;

    while(true){
        if(stateNow != stateLast){
            for(int cpu = 0; cpu < numCPU; cpu++){
                freq = dischargeFreq;
                if(stateNow == true){
                    freq = chargeFreq;
                }
                std::cout << "SET CPU " << cpu << " TO "
                    << freq << "Hz" << std::endl;
                writeMaxCpuFreq(cpu, freq);
            }
        stateLast = stateNow;
        }
        std::this_thread::sleep_for(std::chrono::seconds(repeat));
        stateNow = isCharging();
    }
    return 0;
}
