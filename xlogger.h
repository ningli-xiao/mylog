//
// Created by lixiaoning on 2022/1/6.
//

#ifndef LOGTEST_XLOGGER_H
#define LOGTEST_XLOGGER_H

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <ctime>
#include <chrono>

#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h" // or "../stdout_sinks.h" if no color needed
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

#define ToString(name) #name
struct LogCfgMessage{
    std::string debugLevel = "trace";
    std::string logMode = "console";
    std::string logDir = "./log";
    std::string logName = "test_";
};

/*
 * extern variable
 */
extern LogCfgMessage xLogCfgMessage;

/*
 * extern function
 */
extern int xLoggerInit(std::string cfgMessage);

//
// Created by lixiaoning on 2022/1/7.
//
#include "xlogger.h"
class XLogger {
public:
    //对外提供接口
    static XLogger *getInstance() {
        static XLogger xlogger;
        return &xlogger;
    }

    std::shared_ptr<spdlog::logger> getLogger() {
        return m_logger;
    }

    //自定义打印指针
    template<typename T1>
    int sendPtr(const char *file, int line, std::string message, T1 ptrValue);

private:
    // make constructor private to avoid outside instance
    XLogger() {
        // hardcode log path
        const std::string log_dir = xLogCfgMessage.logDir; // should create the folder if not exist
        const std::string logger_name_prefix = xLogCfgMessage.logName;

        try {
            // logger name with timestamp
            int date = NowDateToInt();
            int time = NowTimeToInt();
            const std::string logger_name = logger_name_prefix + std::to_string(date) + "_" + std::to_string(time);

            // 定义打印到控制台还是文件中
            if(xLogCfgMessage.logMode == "console") {
                m_logger = spdlog::stdout_color_st(logger_name); // single thread console output faster
            }
            else if(xLogCfgMessage.logMode == "file"){
                //m_logger = spdlog::create_async<spdlog::sinks::basic_file_sink_mt>(logger_name, log_dir + "/" + logger_name + ".log");
                m_logger = spdlog::create_async<spdlog::sinks::rotating_file_sink_mt>(logger_name,
                                                                                      log_dir + "/" + logger_name +
                                                                                      ".log", 5 * 1024 * 1024, 3);
            }
            else{
                m_logger = spdlog::stdout_color_st(logger_name); // single thread console output faster
            }
            // 设置打印格式
            m_logger->set_pattern(
                    "%Y-%m-%d %H:%M:%S.%f <thread %t> [%l] [%@] [%^%l%$] %v"); // with timestamp, thread_id, filename and line number

            //设置打印级别,低于级别的打印不显示
            if(xLogCfgMessage.debugLevel=="trace") {
                m_logger->set_level(spdlog::level::trace);
                m_logger->flush_on(spdlog::level::trace);
            }
            else if(xLogCfgMessage.debugLevel=="debug") {
                m_logger->set_level(spdlog::level::debug);
                m_logger->flush_on(spdlog::level::debug);
            }
            else if(xLogCfgMessage.debugLevel=="info") {
                m_logger->set_level(spdlog::level::info);
                m_logger->flush_on(spdlog::level::info);
            }
            else if(xLogCfgMessage.debugLevel=="warn") {
                m_logger->set_level(spdlog::level::warn);
                m_logger->flush_on(spdlog::level::warn);
            }
            else if(xLogCfgMessage.debugLevel=="err") {
                m_logger->set_level(spdlog::level::err);
                m_logger->flush_on(spdlog::level::err);
            }
            else if(xLogCfgMessage.debugLevel=="critical") {
                m_logger->set_level(spdlog::level::critical);
                m_logger->flush_on(spdlog::level::critical);
            }
            else if(xLogCfgMessage.debugLevel=="off") {
                m_logger->set_level(spdlog::level::off);
                m_logger->flush_on(spdlog::level::off);
            }
            else{
                m_logger->set_level(spdlog::level::off);
                m_logger->flush_on(spdlog::level::off);
            }

        }
        catch (const spdlog::spdlog_ex &ex) {
            std::cout << "Log initialization failed: " << ex.what() << std::endl;
        }
    }

    ~XLogger() {
        spdlog::drop_all(); // must do this
    }

    //成员函数说明
    int NowDateToInt();

    int NowTimeToInt();

    void *operator new(size_t size) {}

    XLogger(const XLogger &) = delete;

    XLogger &operator=(const XLogger &) = delete;

private:
    //私有变量定义
    std::shared_ptr<spdlog::logger> m_logger;
};

template<typename T1>
int XLogger::sendPtr(const char *file, int line, std::string message, T1 ptrValue) {
    if (std::is_pointer<T1>::value == true){
        std::cout << file << "：" << line << "：" << message << " ptr is : " << static_cast<void *>(ptrValue)
                  << std::endl;
    }
    else {
        std::cout << file << "：" << line << "：" << message << " ptr is : " << &ptrValue << std::endl;
    }
    return 0;
}
//自定义打印指针值接口,仅调试用
#define MYLOG_PTR_CALL(...)  XLogger::getInstance()->sendPtr(__VA_ARGS__)

// use embedded macro to support file and line number
#define XLOG_TRACE(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::trace, __VA_ARGS__)//省略号只能代替最后面的宏参数
#define XLOG_DEBUG(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::debug, __VA_ARGS__)
#define XLOG_INFO(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::info, __VA_ARGS__)
#define XLOG_WARN(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::warn, __VA_ARGS__)
#define XLOG_ERROR(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::err, __VA_ARGS__)
#define XLOG_PTR(...)   MYLOG_PTR_CALL(__VA_ARGS__)

#endif //LOGTEST_XLOGGER_H
