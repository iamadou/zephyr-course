#define DT_DRV_COMPAT our_sensor_driver


#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>


LOG_MODULE_REGISTER(our_sensor_driver, LOG_LEVEL_INF);


/* 1.Immutable Configuration Structure (Flash/ROM) */
struct our_sensor_driver_config {
    const struct gpio_dt_spec led_gpio;
};

/* 2.Variable Data Structure (RAM) */
struct our_sensor_driver_data {
    /* Add any runtime data you need here */
    int32_t led_state;
};

/* sensor_sample_fetch : Turn on the LED */

static int our_sensor_driver_sample_fetch(const struct device *dev, enum sensor_channel chan) {
    const struct our_sensor_driver_config *config = dev->config;
    struct our_sensor_driver_data *data = dev->data;

    if(chan != SENSOR_CHAN_ALL) {
        return -ENOTSUP;
    }

    data->led_state = 1; // Set the LED state to ON
    int ret = gpio_pin_set_dt(&config->led_gpio, data->led_state);
    if (ret < 0) {
        LOG_ERR("Failed to set LED GPIO pin: %d", ret);
        return ret;
    }

    LOG_INF("LED turned ON");
    return 0;
}


/* Sensor_channel_get : turn off the LED */

static int our_sensor_driver_channel_get(const struct device *dev, enum sensor_channel chan, struct sensor_value *val) {
    const struct our_sensor_driver_config *config = dev->config;
    struct our_sensor_driver_data *data = dev->data;

    if(chan != SENSOR_CHAN_VOLTAGE) {
        return -ENOTSUP;
    }
    val->val1 = data->led_state; // Set the integer part of the value to 0
    val->val2 = 0; // Set the fractional part of the value to 0

    data->led_state = 0; // Set the LED state to OFF
    int ret = gpio_pin_set_dt(&config->led_gpio, data->led_state);
    if (ret < 0) {
        LOG_ERR("Failed to turn OFF the LED GPIO pin: %d", ret);
        return ret;
    }

    LOG_INF("LED turned OFF");
    return 0;
}

/*  Sensor Driver API Functions */
static const struct sensor_driver_api our_sensor_driver_api = {
    .sample_fetch = our_sensor_driver_sample_fetch,
    .channel_get = our_sensor_driver_channel_get,
};

/*  Driver Initialization Function */
static int our_sensor_driver_init(const struct device *dev) {
    const struct our_sensor_driver_config *config = dev->config;

    if(!gpio_is_ready_dt(&config->led_gpio)) {
        LOG_ERR("LED GPIO device is not ready");
        return -ENODEV;
    }

    int ret = gpio_pin_configure_dt(&config->led_gpio, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        LOG_ERR("Failed to configure LED GPIO pin: %d", ret);
        return ret;
    }

    LOG_INF("Our Sensor Driver initialized successfully");
    return 0;
}

/* Macro to define the sensor driver instance */
#define OUR_SENSOR_DRIVER_DEFINE(inst)                                                   \
    static struct our_sensor_driver_data our_sensor_driver_data_##inst;                  \
    static const struct our_sensor_driver_config our_sensor_driver_config_##inst = {     \
        .led_gpio = GPIO_DT_SPEC_INST_GET(inst, led_gpios),                              \
    };                                                                                   \
    DEVICE_DT_INST_DEFINE(inst,                                                          \
                          our_sensor_driver_init,                                        \
                          NULL,                                                          \
                          &our_sensor_driver_data_##inst,                                \
                          &our_sensor_driver_config_##inst,                              \
                          POST_KERNEL,                                                   \
                          CONFIG_KERNEL_INIT_PRIORITY_DEVICE,                            \
                          &our_sensor_driver_api);

DT_INST_FOREACH_STATUS_OKAY(OUR_SENSOR_DRIVER_DEFINE)