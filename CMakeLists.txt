cmake_minimum_required(VERSION 3.10)
project("e2")

add_definitions('-g')
add_definitions('-Wall')
add_definitions('-O3')
add_definitions('-std=c++20')
add_definitions('-Wno-div-by-zero')

# Set project version
set(E2Lan_VERSION_MAJOR "1")
set(E2Lan_VERSION_MINOR "0")
set(E2Lan_VERSION_PATCH "0")
set(E2Lan_VERSION_EXTRA "")
set(E2Lan_VERSION "${E2Lan_VERSION_MAJOR}.${E2Lan_VERSION_MINOR}")
set(E2Lan_VERSION_FULL "${E2Lan_VERSION_MAJOR}.${E2Lan_VERSION_MINOR}.${E2Lan_VERSION_PATCH}${E2Lan_VERSION_EXTRA}")

# number deci for expression
add_definitions(-DNUMBER_DECI=10000)



option(LIB "build application to library !" OFF) # OFF is the default

option(E2L_DEBUG "build application with debug" OFF) # OFF is the default

if(E2L_DEBUG)
    # for code  #ifdef DEBUG ... #endif
    add_compile_definitions( E2L_DEBUG )
endif(E2L_DEBUG) 

IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/generated)
    message ("generated  found!")
else()
    message ("generated not found!  create dir now.")
    EXECUTE_PROCESS( COMMAND mkdir -p  ${CMAKE_CURRENT_SOURCE_DIR}/generated)
endif()


# Configure header
configure_file(
    ${PROJECT_SOURCE_DIR}/include/utility/version.h.in
    ${PROJECT_SOURCE_DIR}/include/utility/version.h

    )

option(USE_CCACHE "" OFF)                                                                                    
set(CCACHE_OPTIONS "" CACHE STRING "options for ccache")                                            
# or cmake -DE2L_DEBUG=ON -DCMAKE_CXX_COMPILER_LAUNCHER=ccache  ../                                      

if (USE_CCACHE)                                         
    find_program(CCACHE_PROGRAM ccache)     
    if(CCACHE_PROGRAM)                                                                          
        set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")                              
        set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")                             
        message("Looking ccache library")                                                                  
    endif()                                                                                                 
endif()

EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )

if( ${ARCHITECTURE} STREQUAL "x86_64" )
    message( STATUS "X86 Architecture: ${ARCHITECTURE}" )
else()
    message( STATUS "ARM Architecture: ${ARCHITECTURE}" )

endif()

#set(CMAKE_INSTALL_LIBDIR "/usr/local/lib")


add_compile_definitions(SEARCH_PATH="${CMAKE_INSTALL_PREFIX}/include/e2")

#if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    set(CMAKE_INSTALL_LIBDIR "/opt/etomc2/lib")
#    set(CMAKE_INSTALL_INCLUDEDIR "/opt/etomc2/include")
#    message("macos sys")
#endif()


option(USE_CLANG "build application with clang" OFF) # OFF is the default

if(USE_CLANG)
    message("use clang compiler")
    #
    # apt-get install -y libzzip-dev zlib1g-dev
    # cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang ..
    #
    set(CMAKE_C_COMPILER "/usr/bin/clang")
    set(CMAKE_C_FLAGS "-Wall -std=c99 -ldl -lz -lncurses -rdynamic ")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    set(CMAKE_C_FLAGS_RELEASE "-O4 -DNDEBUG")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")


    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    set(CMAKE_CXX_FLAGS "-Wall -std=c++20")
    set(CMAKE_CXX_FLAGS_DEBUG "-gfull")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

    set(LLVM_TARGETS_TO_BUILD "X86")

    # set(CMAKE_AR "/usr/bin/llvm-ar")
    # set(CMAKE_LINKER "/usr/bin/llvm-ld")
    # set(CMAKE_NM "/usr/bin/llvm-nm")                          
    # set(CMAKE_OBJDUMP "/usr/bin/llvm-objdump")                
    # set(CMAKE_OBJDUMP "/usr/bin/llvm-objdump")                
    # set(CMAKE_RANLIB "/usr/bin/llvm-ranlib")                  

endif(USE_CLANG) 

## Flex/Bison configuration
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

## llvm
# cmake $LLVM_SRC_DIR -DCMAKE_BUILD_TYPE=Release \
#                    -DLLVM_TARGETS_TO_BUILD="ARM;X86;AArch64"
# macos brew install llvm@14
# cmake  -DUSE_CCACHE=ON -DE2L_DEBUG=ON  -DLLVM_DIR=/opt/homebrew/Cellar/llvm@14/14.0.6/lib/cmake/llvm ../ 
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include(LLVMConfig)
llvm_map_components_to_libnames(
    LLVM_LIBRARIES

    Interpreter
    MCJIT
    native
    X86
    ARM
    AArch64
    ipo
    )

#  apt-get install -y  libpthreadpool-dev libpthreadpool0  zlib1g-dev zlib1g
## thread
find_package(Threads REQUIRED)
if(Threads_FOUND)
    message ("Looking Threads found")
else()
    message (FATAL_ERROR "Cannot find Threads, apt-get install -y  libpthreadpool-dev libpthreadpool0")
endif()


if(WIN32)
    set(ADDITIONAL_FLEX_FLAGS "--wincompat")
else()
    set(ADDITIONAL_FLEX_FLAGS "")
endif()



flex_target(
    LEXER ${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/e2_lex.l
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/e2_lex.cpp
    DEFINES_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/e2_lex.hpp
    COMPILE_FLAGS
    ${ADDITIONAL_FLEX_FLAGS})

bison_target(PARSER ${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/e2_bison.y
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/e2_bison.cpp
    COMPILE_FLAGS "-d -v -Wcounterexamples")
add_flex_bison_dependency(LEXER PARSER)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LLVM_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/generated)

# If build targets includes "host" or "Native", then replace with native architecture.
foreach (NATIVE_KEYWORD host Native)
    list(FIND LLVM_TARGETS_TO_BUILD ${NATIVE_KEYWORD} idx)
    if( NOT idx LESS 0 )
        list(REMOVE_AT LLVM_TARGETS_TO_BUILD ${idx})
        list(APPEND LLVM_TARGETS_TO_BUILD ${LLVM_NATIVE_ARCH})
        list(REMOVE_DUPLICATES LLVM_TARGETS_TO_BUILD)
    endif()
endforeach()


list(FIND LLVM_TARGETS_TO_BUILD ${LLVM_NATIVE_ARCH} NATIVE_ARCH_IDX)

file(GLOB SOURCES
    src/assembler/*.cpp
    src/utility/*.cpp
    src/ast/*.cpp
    src/main.cpp
    )

if(LIB)
    add_library(${PROJECT_NAME} SHARED ${BISON_PARSER_OUTPUTS} ${FLEX_LEXER_OUTPUTS} ${SOURCES} )
    add_library(${PROJECT_NAME}_static STATIC ${BISON_PARSER_OUTPUTS} ${FLEX_LEXER_OUTPUTS} ${SOURCES} )
else()
    add_executable(${PROJECT_NAME} ${BISON_PARSER_OUTPUTS}
        ${FLEX_LEXER_OUTPUTS} ${SOURCES}  )
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    pthread

    ${LLVM_LIBRARIES}
    )

if(LIB)
    INSTALL(TARGETS ${PROJECT_NAME} 
        LIBRARY DESTINATION lib)

    INSTALL(TARGETS ${PROJECT_NAME}_static 
        LIBRARY DESTINATION lib)

    INSTALL (
        DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
endif()


set(ALL_FILE "coredumps")

# # target zoo is always built
add_custom_target( clean-all 
    COMMAND echo "clean core dump files ${ALL_FILE}"
    COMMAND rm -f /tmp/coredumps/*
    COMMAND rm -rf  /usr/local/include/e2/*
    COMMAND rm -f /usr/local/lib/libe2* 
    COMMAND ccache -C
    COMMAND make clean

    )



