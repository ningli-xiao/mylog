//#include <vector>

#include "xlogger.h"
LogCfgMessage xLogCfgMessage;

int XLogger::NowDateToInt() {
    time_t now;
    time(&now);
    // choose thread save version in each platform
    tm p;
#ifdef _WIN32
    localtime_s(&p, &now);
#else
    localtime_r(&now, &p);
#endif // _WIN32
    int now_date = (1900 + p.tm_year) * 10000 + (p.tm_mon + 1) * 100 + p.tm_mday;
    return now_date;
}

int XLogger::NowTimeToInt() {
    time_t now;
    time(&now);
    // choose thread save version in each platform
    tm p;
#ifdef _WIN32
    localtime_s(&p, &now);
#else
    localtime_r(&now, &p);
#endif // _WIN32

    int now_int = p.tm_hour * 10000 + p.tm_min * 100 + p.tm_sec;
    return now_int;
}
/*
 * 函数名：split
 * 功能：
 * 输入：
 * 输出：
 */
std::vector<std::string> stringSplit(const std::string &str, const std::string &pattern)
{
    std::vector<std::string> res;
    if(str == "") {
        return res;
    }

    //在字符串末尾也加入分隔符，方便截取最后一段
    std::string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while(pos != strs.npos)
    {
        std::string temp = strs.substr(0, pos);
        res.push_back(temp);
        //去掉已分割的字符串,在剩下的字符串中进行分割
        strs = strs.substr(pos+1, strs.size());
        pos = strs.find(pattern);
    }

    return res;
}

/*
 * 函数名：xLoggerInit
 * 功能：初始化接口定义
 * 输入：指定格式的字符串:"debugLevel";"logMode";"logDir";"logName";
 * 输出：return 0
 */
int xLoggerInit(std::string cfgMessage) {
    std::vector<std::string> temp = stringSplit(cfgMessage, ";");

    if(temp.size()!=4){
        std::cout<<"the pram is not match\r"<<std::endl;
        return 0;
    }

    xLogCfgMessage.debugLevel =temp[0];
    xLogCfgMessage.logMode = temp[1];
    xLogCfgMessage.logDir = temp[2];
    xLogCfgMessage.logName = temp[3];

    temp.clear();
    return 0;
}