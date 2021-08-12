cmake_minimum_required(VERSION 3.0.0)
project(msc VERSION 0.1.0)

# include(CTest)
# enable_testing()

# aux_source_directory(src/package/mimilib/mimiObject mimiObject)#将./cli目录中的文件名称赋值给变量 cli_src
# aux_source_directory(src/package/mimilib/mimiData mimiData)#将./cli目录中的文件名称赋值给变量 cli_src
# aux_source_directory(src/package/mimilib/mimiTest mimiTest)#将./cli目录中的文件名称赋值给变量 cli_src
# aux_source_directory(src/package/mimilib/mimiEvent mimiEvent)#将./cli目录中的文件名称赋值给变量 cli_src
# aux_source_directory(src/package/mimilib/mimiDevice mimiDevice)#将./cli目录中的文件名称赋值给变量 cli_src
# aux_source_directory(src/package/mimilib/mimiSH mimiSH)#将./cli目录中的文件名称赋值给变量 cli_src
# aux_source_directory(src/package/mimiscript-api mimiscriptApi)#将./cli目录中的文件名称赋值给变量 cli_src
# aux_source_directory(src/package/mimiscript-compiler mimiscriptCompiler)#将./cli目录中的文件名称赋值给变量 cli_src

include_directories(src/package/mimilib/mimiTest)
include_directories(src/package/mimilib/mimiDevice)
include_directories(src/package/mimilib/mimiSH)
include_directories(src/package/mimilib/mimiEvent)
include_directories(src/package/mimilib/mimiObject)
include_directories(src/package/mimilib/mimiData)
include_directories(src/package/mimiscript-api)
include_directories(src/package/mimiscript-compiler)

add_subdirectory(src/package/mimiscript-compiler)
add_subdirectory(src/package/mimiscript-api)
add_subdirectory(src/package/mimilib)
add_subdirectory(src/package/googletest)
add_subdirectory(src/test)

# add_executable(msc
#             src/boot/msc-linux/main.c
#             ${mimiData}
#             ${mimiObject}
#             # ${mimiSH}
#             # ${mimiEvent}
#             # ${mimiDevice}
#             # ${mimiTest}
#             ${mimiscriptCompiler}
#             ${mimiscriptApi}
#             )

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
