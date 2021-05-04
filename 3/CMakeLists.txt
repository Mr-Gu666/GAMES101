aux_source_directory (. DIR)

set(IDX 3)
add_executable (${IDX} ${DIR})

find_package(OpenCV REQUIRED)
target_link_libraries(${IDX} ${OpenCV_LIBS})

find_package(Eigen3 REQUIRED)
include_directories(EIGEN3_INCLUDE_DIR)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/${IDX}) #配置可执行文件的输出路径
