/**
 * @file multiple.h
 * @author 黄李全 (846863428@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-27
 * @copyright 个人版权所有 Copyright (c) 2023
 */
#ifndef __MULTIPLE_IMAGE_H__
#define __MULTIPLE_IMAGE_H__

#include <unistd.h>
#include <vector>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <atomic>
#include <unordered_map>
#include <thread>

typedef struct ProcInfo {
    pid_t pid;                    // 记录pid
    uint32_t max_memery;          // 最大内存占用不超过2M
    uint32_t max_cpu;             // 最大CPU占用不超过50%
    uint32_t count;               // 最大崩溃次数不超过5次
    std::string name;             // 进程名称
    std::string dir;              // 进程目录
    std::vector<std::string> arg; // 进程启动参数
    std::shared_ptr<char *> argv;
    bool enable;
} ProcInfo_t;

class MultipleImg {
 public:
   MultipleImg();
   ~MultipleImg();

   void Init();
   void Runing();
   void Stop();

 private:
   pid_t SpawnChild(std::string program);
   void QiutProcess();

   std::atomic<pid_t> child_pid_;
   std::unordered_map<std::string, ProcInfo_t> working_process_;
   std::thread check_thread_;
};

#endif
