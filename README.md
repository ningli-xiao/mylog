``# Logger

基于spdlog库封装好接口的logger库

使用方式：    
一、加入到本地工程中  
1.下载此工程,将include文件夹和xlogger.cpp/h文件添加到自己的项目中   
2.包含头文件"xlogger.h"到要使用打印的文件中    
二、git方式     
1.在工程目录下新建一个deps目录  
2.添加xxx.cmake文件,里面加入以下内容    
```
include(FetchContent)   
FetchContent_Declare(   
logger  
GIT_REPOSITORY https://reporter:iict1234@gitlab.ictidei.cn/band-intel-center/cpp-base/logger.git    
GIT_TAG origin/feature  
)   
FetchContent_MakeAvailable(logger)
```
3.在主CMakeLists里加入连接
```
include(deps/xlog.cmake)
target_link_libraries(xxx xLog) 
```
4.包含头文件"xlogger.h"到要使用打印的文件中  

注：建议使用第二种方式,这样更新日志库后使用者无需修改代码

打印方式：   
1.参考本工程main.cpp用法   
2.参考spdlog库用法：https://github.com/gabime/spdlog  
3.联系作者本人
# mylog
