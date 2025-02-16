file(GLOB_RECURSE SRC src/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SRC})

find_package(yaml-cpp REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS} include)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

target_link_libraries(${PROJECT_NAME} hik_driver)

target_link_libraries(${PROJECT_NAME} yaml-cpp)

