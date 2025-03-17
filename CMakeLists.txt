cmake_minimum_required(VERSION 3.20)
project(pool VERSION 0.1.1 LANGUAGES CXX)

# 标准设置
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)


# 路径配置（统一使用下划线命名）
# source
set(src ${CMAKE_CURRENT_SOURCE_DIR}/src)
# header
set(hdr ${CMAKE_CURRENT_SOURCE_DIR}/hdr)
# show src
set(ssc ${CMAKE_CURRENT_SOURCE_DIR}/ssc)
# script
set(scp ${CMAKE_CURRENT_SOURCE_DIR}/scp)


set(Qt6_DIR /home/vesita/Qt/6.8.2/gcc_64/lib/cmake/Qt6)
set(github_DIR /home/vesita/library/github)
set(mruby_DIR ${github_DIR}/mruby/build/host)
set(linguist_DIR ${github_DIR}/linguist)
set(tree_sitter_DIR ${github_DIR}/tree-sitter/lib)
set(tree_sitter_c_DIR ${github_DIR}/tree-sitter-c)
set(tree_sitter_cpp_DIR ${github_DIR}/tree-sitter-cpp)
set(tree_sitter_python_DIR ${github_DIR}/tree-sitter-python)
set(tree_sitter_javascript_DIR ${github_DIR}/tree-sitter-javascript)


file (GLOB_RECURSE source
    ${src}/*.cpp
    ${src}/*.c
)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Quick Qml)


# 自动处理 Qt 元对象系统
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 添加可执行目标
add_executable(${PROJECT_NAME}
    ${source}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${hdr}
    ${ssc}
    ${mruby_DIR}/include
    ${tree_sitter_DIR}/include
    ${tree_sitter_c_DIR}/src
    ${tree_sitter_cpp_DIR}/src
    ${tree_sitter_python_DIR}/src
    ${tree_sitter_javascript_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Quick
    Qt6::Qml
)


# 链接配置
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${mruby_DIR}/lib/libmruby.a
    ${github_DIR}/tree-sitter/libtree-sitter.a
    ${tree_sitter_c_DIR}/libtree-sitter-c.a
    ${tree_sitter_cpp_DIR}/libtree-sitter-cpp.a
    ${tree_sitter_python_DIR}/libtree-sitter-python.a
    ${tree_sitter_javascript_DIR}/libtree-sitter-javascript.a
)

qt_add_qml_module(${PROJECT_NAME}
    URI Pool  # 自定义QML模块标识符
    VERSION 1.0
    RESOURCE_PREFIX ssc
    QML_FILES
        ssc/pool.qml
)

# 处理 Ruby 脚本（仅复制到构建目录）
configure_file(
    ${scp}/run_linguist.rb
    ${CMAKE_CURRENT_BINARY_DIR}/run_linguist.rb
    COPYONLY
)

configure_file(
    ${linguist_DIR}/bin/github-linguist
    ${CMAKE_CURRENT_BINARY_DIR}/github-linguist
    COPYONLY
)
