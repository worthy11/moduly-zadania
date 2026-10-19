cmake_minimum_required(VERSION 3.28)
project(LibraryFines LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FINES_SOURCES
    legacy_fines.cpp
    fines.cpp
)
set(FINES_MODULES
    fines.cppm
)

add_executable(fines_cli main_fines.cpp ${FINES_SOURCES})
target_include_directories(fines_cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(fines_cli PRIVATE cxx_std_20)
target_sources(fines_cli PRIVATE FILE_SET CXX_MODULES FILES ${FINES_MODULES})

add_executable(receipt_check main_receipt.cpp receipt.cpp ${FINES_SOURCES})
target_include_directories(receipt_check PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(receipt_check PRIVATE cxx_std_20)
target_sources(receipt_check PRIVATE FILE_SET CXX_MODULES FILES
    ${FINES_MODULES}
    receipt.cppm
)
