

# 最低 CMake 版本要求
cmake_minimum_required(VERSION 3.20)

# 项目名称和版本
project(pool VERSION 0.0.1 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Qt6_path "/home/vesita/Qt/6.8.2/gcc_64")

# 自动处理 Qt 的 moc、uic 和 rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 查找 Qt6 库
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets PATHS ${Qt6_path})

# 如果使用 QML 或 Qt Quick
# find_package(Qt6 REQUIRED COMPONENTS Quick)

# 添加可执行文件
add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    origin.h
    origin.ui
)

# 链接 Qt 库
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
