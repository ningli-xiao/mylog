# ---------------------------------------------------------------------------------------
# IDE support for headers
# ---------------------------------------------------------------------------------------
file(GLOB MYLOG_TOP_HEADERS "${CMAKE_CURRENT_LIST_DIR}/../include/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/../include/spdlog/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/../*.h"
)

set(MYLOG_ALL_HEADERS ${MYLOG_TOP_HEADERS})

source_group("Header Files\\MYLOG" FILES ${MYLOG_TOP_HEADERS})
