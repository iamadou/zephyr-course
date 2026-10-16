
# target_sources(app PRIVATE our_sensor_driver.c)

# add_dependencies(app offsets_h)

if (CONFIG_OUR_SENSOR_DRIVER)
    target_sources(app PRIVATE our_sensor_driver.c)
    if(CONFIG_SHELL)
        target_sources(app PRIVATE our_driver_shell.c)
    endif() 
    zephyr_include_directories(.)
endif()
