cmake_minimum_required(VERSION 3.27)
project(Projekt)

set(CMAKE_CXX_STANDARD 20)

add_executable(Projekt main.cpp
        api_suhtlus.cpp
        retsepti_otsing.cpp
        CLI.cpp
        utility.h
        api_suhtlus.h
        CLI.h
        retsepti_otsing.h
        failid.cpp
        failid.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/curl-8.7.1_7-win64-mingw/curl-8.7.1_7-win64-mingw/include)

target_link_libraries(Projekt ${CMAKE_CURRENT_SOURCE_DIR}/curl-8.7.1_7-win64-mingw/curl-8.7.1_7-win64-mingw/lib/libcurl.dll.a)

# kui tuleb error "Process finished with exit code -1073741515 (0xC0000135)"
# siis lisada system pathi C:\Users\{user}\CLionProjects\Projekt\curl-8.7.1_7-win64-mingw\curl-8.7.1_7-win64-mingw\bin
