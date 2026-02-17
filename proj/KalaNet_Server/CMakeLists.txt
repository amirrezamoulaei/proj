cmake_minimum_required(VERSION 3.16)

project(KalaNet_Server LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_executable(KalaNet_Server
  main.cpp
  kalanetserver.h kalanetserver.cpp
)
target_link_libraries(KalaNet_Server PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt6::Network)

include(GNUInstallDirs)
install(TARGETS KalaNet_Server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
