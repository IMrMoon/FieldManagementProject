cmake_minimum_required(VERSION 3.27)
project(FieldManagementProject)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(SQLiteCpp)

add_executable(FieldManagementProject
        main.cpp
        DataAccessLayer.h
        DataAccessLayer.cpp
        Field.h
        Date.h
        Field.cpp
        Date.cpp
        Manager.cpp
        Manager.h
        Menu.cpp
        Menu.h
        Order.cpp
        Order.h
        Player.cpp
        Player.h
        Validation.cpp
        Validation.h
        Color.cpp
        Color.h
)

target_link_libraries(FieldManagementProject SQLiteCpp)

target_link_directories(FieldManagementProject PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SQLiteCpp/include)