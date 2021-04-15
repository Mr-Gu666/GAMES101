cmake_minimum_required (VERSION 3.2.0) #cmake版本要求
project (GAMES101) #命名这个project
include_directories("C:/Program Files (x86)/Eigen3/include/eigen3") #引用Eigen，${PROJECT_SOURCE_DIR}即GAMES101/的绝对路径，代码框架里引用Eigen的方式是<eigen3/Eigen/Eigen>
add_subdirectory(0) # 1为作业1的文件夹的名字，它命令CMAKE执行文件夹1下的CMakeLists.txt
add_subdirectory(1)
add_subdirectory(2)