cmake_minimum_required (VERSION 3.10.2)

set (PROJECT_NAME "Chronos_Test_SW" VERSION 1.0 LANGUAGES C)

project (${PROJECT_NAME})

set (CMAKE_C_FLAGS "-mstm8 --std-sdcc11 --Werror -D__REV_X302__=0")
set (CMAKE_C_FLAGS_DEBUG "--debug --out-fmt-elf")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set (CMAKE_EXE_LINKER_FLAGS "-lstm8 --out-fmt-elf")
    set (CMAKE_EXECUTABLE_SUFFIX ".elf")
else ()
    set (CMAKE_EXE_LINKER_FLAGS "-lstm8")
endif ()

add_executable (${PROJECT_NAME} src/main.c src/clock.c src/gpio.c src/timers.c src/usart.c src/adc.c src/dac.c src/spi.c src/iwdg.c src/interrupts.c src/nop.c src/mcp41010.c)
include_directories (inc)
