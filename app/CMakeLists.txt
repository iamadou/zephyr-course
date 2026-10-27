cmake_minimum_required(VERSION 3.20.0)


list(APPEND BOARD_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
list(APPEND DTS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)

# Add by iam in order to use the FRDM_MCXN236 board
set(DTS_EXTRA_OVERLAY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/app.overlay)


find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(my_zephyr_app)

add_subdirectory(drivers/our_sensor_driver)
# target_sources(app PRIVATE drivers/our_sensor_driver/our_sensor_driver.c)
# target_sources(app PRIVATE drivers/our_sensor_driver/osensor_apiext_shell.c)
# target_include_directories(app PRIVATE drivers/our_sensor_driver)

target_sources(app PRIVATE src/main.cpp)
