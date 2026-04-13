cmake_minimum_required(VERSION 3.31)

# Set the project name
set(CMAKE_PROJECT_NAME Env_Monitoring_System)

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(SIZE arm-none-eabi-size)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add color diagnostics
set(CMAKE_COLOR_DIAGNOSTICS ON)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Core project settings
project(${CMAKE_PROJECT_NAME})

# Enable CMake support for ASM, C and CXX languages
enable_language(C CXX ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    # -T "${CMAKE_SOURCE_DIR}/STM32F103XX_FLASH.ld"
    # --specs=nano.specs
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -Wl,--gc-sections
)

# Add STM32CubeMX generated sources
add_subdirectory(${CMAKE_SOURCE_DIR}/cmake/stm32cubemx)

# Exclude main.c from build to use main.cpp instead
set_source_files_properties(${CMAKE_SOURCE_DIR}/Core/Src/main.c PROPERTIES HEADER_FILE_ONLY TRUE)

# Remove warning
add_compile_options(-w)

function(USER_ADD_DIR dir)
    file(GLOB USER_SOURCE
            ${dir}/*.h
            ${dir}/*.c
            ${dir}/*.hpp
            ${dir}/*.cpp
            ${dir}/*.cc
    )
    target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${USER_SOURCE})
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${dir})
endfunction()

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Core/Src/main.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Core/Src)

USER_ADD_DIR(${CMAKE_SOURCE_DIR}/User)

target_link_libraries(${CMAKE_PROJECT_NAME}
        stm32cubemx
        -lstdc++
        -lsupc++
#        ${CMAKE_SOURCE_DIR}/Middlewares/ST/ARM/DSP/Lib/libarm_cortexM7lfdp_math.a
)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin
        COMMENT "Building hex & bin file...\nEXCUTABLE SIZE:"
        COMMAND ${SIZE} ${PROJECT_NAME}.elf
)
