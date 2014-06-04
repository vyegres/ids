cmake_minimum_required( VERSION 2.8 )
set( BIN ids )
project( ${BIN} )
 
set( SOURCE_ROOT ./src )

file (GLOB HEADERS ${SOURCE_ROOT}/*.h
                   ${SOURCE_ROOT}/clientlayer/*.h
                   ${SOURCE_ROOT}/logiclayer/*.h
                   ${SOURCE_ROOT}/serverlayer/*.h
)
file (GLOB SOURCES ${SOURCE_ROOT}/*.cpp
                   ${SOURCE_ROOT}/clientlayer/*.cpp
                   ${SOURCE_ROOT}/logiclayer/*.cpp
                   ${SOURCE_ROOT}/serverlayer/*.cpp
)

set( REQUIRED_LIBRARIES
		mongoclient
		boost_system
		boost_filesystem
		boost_program_options
		boost_thread
		pthread
		config++
		msgpack
		zmq	
                glog
)
 
set( CMAKE_CXX_FLAGS "-std=c++11 -O2" ) 
 
add_executable( ${BIN} ${HEADERS} ${SOURCES} )

target_link_libraries( ${BIN} ${REQUIRED_LIBRARIES} )
