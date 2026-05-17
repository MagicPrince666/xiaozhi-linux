#include <iostream>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include "multiple.h"
#include "json.hpp"
#if defined(__linux__) || defined(__APPLE__)
#include <sys/wait.h>
#elif defined(_WIN32)
pid_t fork()
{
    return -1;
}
void kill(pid_t pid, int sig)
{
    if (pid && sig) {}
    return;
}
pid_t wait(void* status)
{
    if (status);
    return -1;
}
#endif

using json = nlohmann::json;

std::vector<std::string> processes = {"gui/main", "control_center/control_center", "sound_app/sound_app"};

MultipleImg::MultipleImg () : child_pid_(-1) {
    working_process_.clear();
}

MultipleImg::~MultipleImg () {
    if (check_thread_.joinable()) {
        check_thread_.join();
	}
    for (std::unordered_map<std::string, ProcInfo_t>::iterator iter = working_process_.begin(); iter != working_process_.end(); iter++) {
        std::cout << "program " << iter->first << " pid " << iter->second.pid << std::endl;
        // 清場收工
        if (iter->second.pid > 0) {
            kill(iter->second.pid, SIGTERM);
        }
    }
}

void MultipleImg::QiutProcess() {
    while(1) {
        // 每隔一段時間檢查一次進程
        for (std::unordered_map<std::string, ProcInfo_t>::iterator iter = working_process_.begin(); iter != working_process_.end(); iter++) {
            ProcInfo_t tmpinfo = (*iter).second;
            // std::cout << "program " << iter->first << " pid " << tmpinfo.pid << " count " << tmpinfo.count << std::endl;
            // kill(iter->first, SIGTERM);
            std::string process_exists = "/proc/" + std::to_string(tmpinfo.pid);
            if (-1 == access(process_exists.c_str(), F_OK)) {
                std::cerr << "Program " << iter->first << " quit!" << std::endl;
                if(--tmpinfo.count > 0) { //重启次数减1
                    // 檢查pid不在運行
                    pid_t tmp_pid = SpawnChild(iter->first);
                    if(tmp_pid > 0) {
                        std::cout << "program " << iter->first << " pid " << tmpinfo.pid << std::endl;
                        // 更新pid
                        tmpinfo.pid = tmp_pid;
                        working_process_[iter->first] = tmpinfo;
                    }
                } else {
                    // 崩溃超过5次就不再拉起进程
                    working_process_.erase(iter->first);
                    break;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

pid_t MultipleImg::SpawnChild(std::string program)
{
    pid_t ch_pid = fork();
    if (ch_pid == -1) {
        std::cerr << "fork err = " << errno << " " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    } else if (ch_pid > 0) {
        std::cout << "spawn child with pid - " << ch_pid << std::endl;
        return ch_pid;
    } else {
        char* newArgv[] = {const_cast<char*>(program.c_str()), nullptr};
        std::string program_path = "./" + program;
        int ret = execvp(program_path.c_str(), newArgv);
        if(ret == -1) {
            std::cerr << "execl err = " << errno << " " << strerror(errno) << std::endl;
        }
        // exit(EXIT_FAILURE);
    }
    return ch_pid;
}

void MultipleImg::Init() {
    std::cout << "!!!!!!!!!!!!!!Start fork test!!!!!!!" << std::endl;
    check_thread_ = std::thread([](MultipleImg* pThis){
        pThis->QiutProcess();
    }, this);
}

void MultipleImg::Runing() {

    for (std::string itvec : processes) {
        if (-1 == access(itvec.c_str(), F_OK)) {
            std::cerr << "Program file " << itvec.c_str() << " does not exist in current directory!" << std::endl;
        } else {
            pid_t tmp_pid = SpawnChild(itvec);
            if(tmp_pid > 0) {
                ProcInfo_t tmp;
                tmp.pid = tmp_pid;
                working_process_[itvec] = tmp;
            }
        }
    }

    while ((child_pid_ = wait(nullptr)) > 0) {
        std::cout << "Program pid " << child_pid_ << " terminated" << std::endl;
    }
}

void MultipleImg::Stop() {
    std::cout << "!!!!!!!!!!!!! End fork test !!!!!!!!!!!!" << std::endl;
}
