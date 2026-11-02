cmake_minimum_required(VERSION 3.10)
project(YoloV8_Demo)
set(CMAKE_CXX_STANDARD 11)

# 1. 查找 OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 2. 查找 OpenMP（关键新增）
find_package(OpenMP REQUIRED)

# 3. 指定 NCNN 路径
set(NCNN_ROOT "/home/senul/ncnn")
include_directories(${NCNN_ROOT}/src)
include_directories(${NCNN_ROOT}/build/src)

# 4. 生成可执行文件
add_executable(yolov8_demo main.cpp)

# 5. 链接库（关键新增 OpenMP::OpenMP_CXX）
target_link_libraries(yolov8_demo 
    ${OpenCV_LIBS} 
    OpenMP::OpenMP_CXX 
    ${NCNN_ROOT}/build/src/libncnn.a
)
