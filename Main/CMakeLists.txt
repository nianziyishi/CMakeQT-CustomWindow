# CMakeList.txt: 子级 Main 项目文件
# 
#

# ==================配置项目信息==================

# 项目名称
project(QCustomWindow LANGUAGES CXX)

# 引入Qt库
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

# 创建可执行程序
add_executable(${PROJECT_NAME} main.cpp)


# =================链接依赖库==================

# 指定依赖GUI库文件
add_dependencies(${PROJECT_NAME} GUI)

# 设置并引用头文件路径
set(INCLUDE_PATH
	${PROJECT_SOURCE_DIR}/../GUI
)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_PATH})

# 链接GUI库文件的目录
target_link_directories(${PROJECT_NAME} PUBLIC ${OUTPUT_DIRECTORY})

# 链接GUI库文件
if(WIN32)
    target_link_libraries(${PROJECT_NAME} GUI.lib)
else()
    target_link_libraries(${PROJECT_NAME} GUI)
endif()


# ==================打印环境信息==================

#打印项目路径
message( STATUS "${PROJECT_NAME} 项目目录 = ${PROJECT_SOURCE_DIR}" )
message( STATUS "${PROJECT_NAME} 输出目录 = ${OUTPUT_DIRECTORY}" )
