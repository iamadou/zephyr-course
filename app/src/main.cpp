#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>



/* The devicetree node identifier for the "led0" alias. */
#define LED_NODE DT_ALIAS(led2)
//#define LED_NODE DT_NODELABEL(red_led)
//#define LED_NODE DT_PATH(leds, led_2)
//#define LED_NODE DT_ALIAS(app_led)


static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

namespace {
    void test() {
        const struct device *driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
        if (!device_is_ready(driver)) {
            LOG_ERR("Le périphérique our_driver0 n'est pas prêt !");
            return;
        }

        struct sensor_value val;
        int ret = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
         if (ret == 0) {
            // Option A : Affichage en float en convertissant la valeur
            LOG_INF("Temperature: %f °C", sensor_value_to_double(&val));
            
            // Option B : Affichage brut (val.val1 = entiers, val.val2 = millionièmes)
            // LOG_INF("Temperature: %d.%06d °C", val.val1, val.val2);
        } else {
            LOG_ERR("Erreur lors de la lecture du canal : %d", ret);
        }
        LOG_INF("Sensor value: %d", ret);
    }
}

int main(void)
{
    bool led_state = true;

    /* Verify that the device is ready to be used */
    if (!gpio_is_ready_dt(&led)) {
        return 0;
    } 

     /* Configure the GPIO pin as an output active */
    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) {
        return 0;
    } 

    while (1) {
        if (gpio_pin_toggle_dt(&led) < 0) return 0;

        led_state = !led_state;
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
}
