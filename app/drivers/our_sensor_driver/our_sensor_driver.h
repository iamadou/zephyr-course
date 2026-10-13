#ifndef OUR_SENSOR_DRIVER_H
#define OUR_SENSOR_DRIVER_H 


#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>


/* Extended API configuration for the sensor driver */
struct our_sensor_driver_extended_api_config {
    struct sensor_driver_api base_api;  /* Base sensor driver API */
    int (*set_calibration)(const struct device *dev, int32_t called_value);
};

/* Set the calibration value for the sensor */
static inline int our_sensor_driver_set_calibration(const struct device *dev, int32_t called_value) {

    /* Get the extended API configuration */
    const struct our_sensor_driver_extended_api_config *api = (const struct our_sensor_driver_extended_api_config *)dev->api;

    /* Check if the extended API is available and the set_calibration function is implemented */
    if(api == NULL || api->set_calibration == NULL) {
        return -ENOTSUP;
    }
    
    return api->set_calibration(dev, called_value);
}

#endif  /* OUR_SENSOR_DRIVER_H */