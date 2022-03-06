# CMakeList.txt: 子级 GUI 项目文件
# 
#

# ==================配置项目信息==================

# 项目名称
project(GUI LANGUAGES CXX)

# 设置生成动态库(默认静态库)
set(BUILD_SHARED_LIBS ON)

# 引入Qt库
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

# 查找当前目录Demo下的所有源文件，将名称保存到 DIR_SRCS 变量中
aux_source_directory(. DIR_SRCS)
aux_source_directory(./Demo DIR_SRCS)

# 添加工程源文件到库
add_library(${PROJECT_NAME} ${DIR_SRCS})

# 设置并引用头文件路径
set(INCLUDE_PATH
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/Demo
)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_PATH})

# 定义导出符号的宏定义
if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PUBLIC GUI_LIB)
    # 定义库类型的宏定义
    if(BUILD_SHARED_LIBS)
        target_compile_definitions(${PROJECT_NAME} PUBLIC SHARED_LIB)
    endif()
endif()


# =================链接依赖库==================

# 将Qt的库链接至程序
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)

# 指定依赖BaseModule库文件
add_dependencies(${PROJECT_NAME} BaseModule)

# 设置并引用BaseModule的头文件路径
set(LIB_INCLUDE_PATH
	${PROJECT_SOURCE_DIR}/../BaseModule
	${PROJECT_SOURCE_DIR}/../BaseModule/BaseWidget
)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_INCLUDE_PATH})

# 链接GUI库文件的目录
target_link_directories(${PROJECT_NAME} PUBLIC ${OUTPUT_DIRECTORY})

# 链接BaseModule库文件
if(WIN32)
    target_link_libraries(${PROJECT_NAME} BaseModule.lib)
else()
    target_link_libraries(${PROJECT_NAME} BaseModule)
endif()

# ==================打印环境信息==================

# 打印项目路径
message( STATUS "${PROJECT_NAME} 项目目录 = ${PROJECT_SOURCE_DIR}" )
message( STATUS "${PROJECT_NAME} 输出目录 = ${OUTPUT_DIRECTORY}" )
