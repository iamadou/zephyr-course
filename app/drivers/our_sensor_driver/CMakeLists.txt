
# target_sources(app PRIVATE our_sensor_driver.c)

# add_dependencies(app offsets_h)

if (CONFIG_OUR_SENSOR_DRIVER)
    target_sources(app PRIVATE our_sensor_driver.c)
    if(CONFIG_SHELL)
<<<<<<< HEAD
        target_sources(app PRIVATE sensor_root_shell.c)
=======
        target_sources(app PRIVATE osensor_apiext_shell.c)
>>>>>>> myshellapiextension
    endif()
    zephyr_include_directories(.)
endif()
