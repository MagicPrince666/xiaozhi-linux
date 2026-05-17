#include <iostream>
#include <memory>
#include "interface.h"
#include "multiple.h"

#if defined(__unix__) || defined(__APPLE__)
#ifdef __GLIBC__
#include <execinfo.h>
#endif
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <iostream>

#define PRINT_SIZE_ 100
const char *g_exe_name;

void Execute(std::string cmdline, std::string &recv)
{
#if defined(__unix__) || defined(__APPLE__)
    FILE *stream = NULL;
    char buff[1024];
    char recv_buff[256]      = {0};

    memset(recv_buff, 0, sizeof(recv_buff));

    if ((stream = popen(cmdline.c_str(), "r")) != NULL) {
        while (fgets(buff, 1024, stream)) {
            strcat(recv_buff, buff);
        }
    }
    recv = recv_buff;
    pclose(stream);
#endif
}

void Addr2Line(std::string exe, std::vector<std::string>& strs)
{
#if defined(__unix__) || defined(__APPLE__)
    char str[1024] = {0};
    for (uint32_t i = 0; i < strs.size(); i++) {
        std::string line = strs[i];
        std::string::size_type index = line.find("(+"); // found start stuck
        line = line.substr(index + 1, line.size() - index - 1);
        if (index != std::string::npos) {
            index = line.find(")"); // foud end
            if (index != std::string::npos) {
                line = line.substr(0, index);
                int len = snprintf(str, sizeof(str), "addr2line -e %s %s", exe.c_str(), line.c_str());
                str[len] = 0;
                // std::cout << "Run " << str << std::endl;
                std::string recv;
                Execute(str, recv);
                std::ofstream outfile;
                if (recv.find("??") == std::string::npos) {
                    outfile.open("coredump.log", std::ios::out | std::ios::app);
                    if (outfile.is_open()) {
                        outfile << recv;
                        outfile.close();
                    }
                }
            }
        }
    }
#endif
}

static void _signal_handler(int signum)
{
#ifdef __GLIBC__
    void *array[PRINT_SIZE_];
    char **strings;

    size_t size = backtrace(array, PRINT_SIZE_);
    strings     = backtrace_symbols(array, size);

    if (strings == nullptr) {
        fprintf(stderr, "backtrace_symbols");
        exit(EXIT_FAILURE);
    }
#endif
    switch (signum) {
    case SIGSEGV:
        fprintf(stderr, "widebright received SIGSEGV! Stack trace:\n");
        break;

    case SIGPIPE:
        fprintf(stderr, "widebright received SIGPIPE! Stack trace:\n");
        break;

    case SIGFPE:
        fprintf(stderr, "widebright received SIGFPE! Stack trace:\n");
        break;

    case SIGABRT:
        fprintf(stderr, "widebright received SIGABRT! Stack trace:\n");
        break;

    default:
        break;
    }
#ifdef __GLIBC__
#ifdef BACKTRACE_DEBUG
    std::vector<std::string> strs;
    for (size_t i = 0; i < size; i++) {
        fprintf(stderr, "%ld %s \n", i, strings[i]);
        strs.push_back(strings[i]);
    }
    Addr2Line(g_exe_name, strs);
#else
    std::string path = std::string(g_exe_name) + ".log";
    std::ofstream outfile(path, std::ios::out | std::ios::app);
    if (outfile.is_open()) {
        outfile << "Commit ID: " << GIT_VERSION << std::endl;
        outfile << "Git path: " << GIT_PATH << std::endl;
        outfile << "Compile time: " << __TIME__ << " " << __DATE__ << std::endl;
    }
    for (size_t i = 0; i < size; i++) {
        fprintf(stderr, "%ld %s \n", i, strings[i]);
        if (outfile.is_open()) {
            outfile << strings[i] << std::endl;
        }
    }
    if (outfile.is_open()) {
        outfile.flush();
        outfile.close();
    }
#endif
    free(strings);
#endif
    signal(signum, SIG_DFL); /* 还原默认的信号处理handler */
    fprintf(stderr, "%s quit execute now\n", g_exe_name);
    fflush(stderr);
    exit(-1);
}
#endif

static void print_version(void)
{
    std::cout << "==============================================================" << std::endl;
    std::cout << "This is cputools ble device!!" << std::endl;
    std::cout << "commit ID: " << GIT_VERSION << std::endl;
    std::cout << "git path: " << GIT_PATH << std::endl;
    std::cout << "Compile time: " << __TIME__ << " : " << __DATE__ << std::endl;
    std::cout << "Author:          Leo Huang" << std::endl;
    std::cout << "==============================================================" << std::endl;
}

int main(int argc, char* argv[])
{
#if defined(__unix__) || defined(__APPLE__)
    signal(SIGPIPE, _signal_handler); // SIGPIPE，管道破裂。
    signal(SIGSEGV, _signal_handler); // SIGSEGV，非法内存访问
    signal(SIGFPE, _signal_handler);  // SIGFPE，数学相关的异常，如被0除，浮点溢出，等等
    signal(SIGABRT, _signal_handler); // SIGABRT，由调用abort函数产生，进程非正常退出
    g_exe_name = argv[0];
#endif

    print_version();

    std::unique_ptr<MultipleImg> image(new MultipleImg);
    image->Init();
    image->Runing();
    image->Stop();

    return 0;
}
