#
# taka-wang
#

cmake_minimum_required(VERSION 2.8.9)
project(modbusd C)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(bin_name modbusd)
set(modbus_include /usr/include/modbus)
set(czmq_include /usr/include/)
set(bin_source json/cJSON.c json.c mb.c mbtcp.c main.c)

# Appends the cmake/modules path to MAKE_MODULE_PATH variable.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
include(GetGitRevisionDescription)
# set latest git tag as modbusd version string
git_describe(MODBUSD_VERSION --abbrev=0 --tags)
# define version string to main
#add_definitions(-DVERSION="${MODBUSD_VERSION}" )
add_definitions(-DVERSION="0.7.1" )

# cflag
set(EXT_C_FLAGS "-W -Wall -Wno-format-security -O3 -std=c99")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXT_C_FLAGS}")

# set install prefix
SET(CMAKE_INSTALL_PREFIX /)

include_directories(${czmq_include} ${modbus_include})
add_executable(${bin_name} ${bin_source} config/modbusd.json)
target_link_libraries(${bin_name} LINK_PUBLIC zmq czmq modbus m)

# install binary
install(TARGETS ${bin_name} DESTINATION /usr/bin COMPONENT binaries)
# install config
install(FILES config/modbusd.json DESTINATION /etc/${bin_name} COMPONENT config)
