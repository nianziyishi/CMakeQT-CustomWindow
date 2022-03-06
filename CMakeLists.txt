# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

# ==================配置项目信息==================

# 项目名称
project(QCustomWindow LANGUAGES CXX)


# 包含当前目录
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置c++语言标准，这里使用c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 自动调用moc, uic, rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ==================配置项目环境==================

# 根据当前平台进行配置
	# 设置qt路径
	# 设置程序和库输出路径的变量
if(WIN32)
	message( STATUS "PLATFORM = IS_WINDOWS" )
	set(QTLIB_DIRECTORY  C:/Qt/Qt5.15.2/5.15.2/msvc2019_64)
	set(OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/out/bin/${CMAKE_BUILD_TYPE})
elseif(UNIX)
	message( STATUS "PLATFORM = IS_LINUX" )
	set(QTLIB_DIRECTORY  $ENV{HOME}/qt/Qt5.15.2/5.15.2/gcc_64/lib/cmake)
	set(OUTPUT_DIRECTORY  $ENV{HOME}/${CMAKE_PROJECT_NAME}/bin/${CMAKE_BUILD_TYPE})
elseif(APPLE)
	message( STATUS "PLATFORM = IS_MACOS" )
endif()

# 设置可执行文件输出位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")

# 设置静态库文件输出位置
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")

# 设置动态库文件输出位置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")

# 设置Qt5的cmake模块所在目录，如果不设置将使用系统提供的版本
set(CMAKE_PREFIX_PATH ${QTLIB_DIRECTORY})


# 包含子项目
add_subdirectory(Main)
add_subdirectory(GUI)
add_subdirectory(BaseModule)

# windows平台设置增量链接
if(MSVC)
	# 关闭警告
	#add_definitions(-w)
	#target_compile_options(${PROJECT_NAME} PUBLIC "/ZI")
	target_link_options(${PROJECT_NAME} PUBLIC "/INCREMENTAL")
endif()

# ==================打印环境信息==================

# 打印项目名称
message( STATUS "项目名称 = ${CMAKE_PROJECT_NAME}" )
# 打印项目路径
message( STATUS "项目目录 = ${PROJECT_SOURCE_DIR}" )
# 打印项目输出路径
message( STATUS "输出目录 = ${OUTPUT_DIRECTORY}" )

# 打印编译后程序路径
#message("编译后可执行程序目录 = " ${EXECUTABLE_OUTPUT_PATH})
# 打印编译后库文件路径
#message("编译后库文件目录 = " ${LIBRARY_OUTPUT_PATH})

# 打印当前处理器架构
message( STATUS "PROCESSOR = ${CMAKE_SYSTEM_PROCESSOR}" )
# 打印当前系统平台
message( STATUS "SYSTEM = ${CMAKE_SYSTEM}" )
#message( STATUS "SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}" )
#message( STATUS "SYSTEM_VERSION = ${CMAKE_SYSTEM_VERSION}" )

