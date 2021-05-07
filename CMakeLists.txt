cmake_minimum_required(VERSION 2.8)

project(Example-facilio)




add_library(mylibs "./src/websocketwrapper.cpp")


target_link_libraries(mylibs -lpthread)
#target_link_libraries(mylibs -lhdt)
target_link_libraries(mylibs "-L/usr/local/lib/")

target_link_libraries(mylibs "/usr/local/lib/libfacil.io.a")

#target_link_libraries(mylibs "/Users/aalobaid/workspaces/Cworkspace/facil.io-0.7.5/build/libfacil.io.a")
#target_link_libraries(mylibs "/usr/local/lib/getoptpp/libgetopt_pp.a")
#target_link_libraries(mylibs "/usr/local/lib/libmitie.a")
#target_link_libraries(mylibs "/usr/local/lib/SmarTerp/libSmarTerpLookup.a")
#target_link_libraries(mylibs -lmitie)


#set(SOURCES
#    src/main.cpp
#    src/br_tokenizer.cpp
#    src/nlp.cpp)

set(SOURCES
    src/main.cpp
    src/websocketwrapper.cpp)

set(HEADERS
    include/websocketwrapper.hpp)
#set(HEADERS
#    include/br_tokenizer.hpp
#    include/nlp.hpp)



# This is to get rid of the the c++11 warnings
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()




include_directories("include" "/usr/local/include")



include_directories("/usr/local/include")
include_directories("/usr/local/include/facil")
include_directories("/usr/local/include/facil/http")
include_directories("/usr/local/include/facil/fiobj")
include_directories("/usr/local/include/facil/cli")
include_directories("/usr/local/include/facil/legacy")
include_directories("/usr/local/include/facil/tls")

#include_directories("/Users/aalobaid/workspaces/Cworkspace/facil.io-0.7.5/lib")
#include_directories("/Users/aalobaid/workspaces/Cworkspace/facil.io-0.7.5/lib/facil")
#include_directories("/Users/aalobaid/workspaces/Cworkspace/facil.io-0.7.5/lib/facil/http")
#include_directories("/Users/aalobaid/workspaces/Cworkspace/facil.io-0.7.5/lib/facil/fiobj")
#include_directories("/Users/aalobaid/workspaces/Cworkspace/facil.io-0.7.5/lib/facil/cli")
#include_directories("/Users/aalobaid/workspaces/Cworkspace/facil.io-0.7.5/lib/facil/legacy")
#include_directories("/Users/aalobaid/workspaces/Cworkspace/facil.io-0.7.5/lib/facil/tls")


add_executable("${PROJECT_NAME}" "${SOURCES}" "${HEADERS}")

target_link_libraries("${PROJECT_NAME}" mylibs)


# Theses are not tested yet
#include(GNUInstallDirs)
#install(TARGETS mylibs DESTINATION lib/SmarTerp)
##install(TARGETS "${PROJECT_NAME}" DESTINATION lib/SmarTerp)
#install(FILES include/nlp.hpp DESTINATION include/SmarTerp)


