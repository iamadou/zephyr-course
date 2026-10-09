
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>



/* The devicetree node identifier for the "led0" alias. */
//#define LED_NODE DT_ALIAS(led2)
//#define LED_NODE DT_NODELABEL(red_led)
//#define LED_NODE DT_PATH(leds, led_2)
//#define LED_NODE DT_ALIAS(app_led)


//static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    const struct device *sensor_dev = DEVICE_DT_GET(DT_NODELABEL(our_sensor_driver0));
    struct sensor_value val;
    int ret;

    /* Verify that the sensor device is ready to be used */
    if(!device_is_ready(sensor_dev)) {
        LOG_ERR("Sensor device not ready");
        return -ENODEV;
    }

    LOG_INF("Sensor device is ready");
    while (1) {

        /* 3. Fetch: Turn on the LED */
        ret = sensor_sample_fetch(sensor_dev);
        if(ret < 0) {
            LOG_ERR("Failed to fetch sensor sample: %d", ret);
            return ret;
        }

        /* Pause time before turning off the LED */
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);

        /* 4. Process: Toggle the LED state */
        ret = sensor_channel_get(sensor_dev, SENSOR_CHAN_VOLTAGE, &val);
        if(ret < 0) {
            LOG_ERR("Failed to get sensor channel value: %d", ret);
        }else {
            LOG_INF("Sensor channel value: %d", val.val1);
        }
        /* Pause time before next iteration */
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
}
