#include <iostream>
#include <string>
#include "xlogger.h"
/**
 * main函数:使用案例
 * @return
 */
int main() {
    // print log test, you can transfer any param to do format
    int paramNum = 1024;
    int paramArray[5] = {0,1,2,3,4};
    int *paramPtr = &paramNum;
    std::string paramString = "spdlog is good";
    const char * p = "hello";

    xLoggerInit("trace;console;./log;lixiaoning_");
    XLOG_PTR(__FILE__,__LINE__,ToString(paramArray),paramArray);//目前不可打印到日志
    XLOG_PTR(__FILE__,__LINE__,ToString(paramNum),paramNum);//目前不可打印到日志
#if 1
    XLOG_TRACE("this is trace log record, param: {}",paramNum); // 注意trace小于debug,不会被打印

    XLOG_DEBUG("this is debug log record, param: {}", paramString);//打印字符串变量


    XLOG_DEBUG("this is debug log record, param: {} ", paramArray[0]);//打印字符串
    XLOG_DEBUG("this is debug log record, param: {}", *paramPtr);//打印paramPtr地址的值

    XLOG_DEBUG("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b} ", paramNum);

    XLOG_DEBUG("this is debug log record, param: {:03.3f}", 1.24123);//自动识别变量格式并打印


    XLOG_INFO("this is info log record, param: {}", paramNum);
    XLOG_WARN("this is warn log record, param: {}", double(++paramNum)); // double type param is ok
    XLOG_ERROR("this is error log record, param: {}", std::to_string(++paramNum)); // string type param is ok
#endif
    return 0;
}
