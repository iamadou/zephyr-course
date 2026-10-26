#include<zephyr/kernel.h>
#include<zephyr/shell/shell.h>
#include<zephyr/device.h>
#include<zephyr/drivers/sensor.h>

/* Get our sensor driver device instance via the device tree node label */
#define OUR_SENSOR_DRIVER_SHELL DEVICE_DT_GET(DT_NODELABEL(our_sensor_driver0))

/* Fetch: Subsystem */
static int our_sensor_driver_shell_fetch(const struct shell *shell, size_t argc, char **argv) {
    const struct device *dev = OUR_SENSOR_DRIVER_SHELL;

    if(!device_is_ready(dev)) {
        shell_error(shell, "Our Sensor Driver device is not ready");
        return -ENODEV;
    }

    /* Call the global API sensor_sample_fetch */
    int ret = sensor_sample_fetch(dev);
    if (ret < 0) {
        shell_error(shell, "Failed to fetch sensor data: %d", ret);
        return ret;
    }
    shell_print(shell, "Sensor data fetched successfully");
    return 0;
}

/* Read or get: Subsystem */
static int our_sensor_driver_shell_read(const struct shell *shell, size_t argc, char **argv) {
    const struct device *dev = OUR_SENSOR_DRIVER_SHELL;

    if(!device_is_ready(dev)) {
        shell_error(shell, "Our Sensor Driver device is not ready");
        return -ENODEV;
    }

    struct sensor_value val;
    /* Call the global API sensor_channel_get */
    int ret = sensor_channel_get(dev, SENSOR_CHAN_VOLTAGE, &val);
    if (ret < 0) {
        shell_error(shell, "Failed to get sensor data: %d", ret);
        return ret;
    }
    shell_print(shell, "Sensor value: %d.%06d", val.val1, val.val2);
    return 0;
}

/* info : Subsystem */
static int our_sensor_driver_shell_info(const struct shell *shell, size_t argc, char **argv) {
    const struct device *dev = OUR_SENSOR_DRIVER_SHELL;

    if(!device_is_ready(dev)) {
        shell_error(shell, "Our Sensor Driver device is not ready");
        return -ENODEV;
    }

    shell_print(shell, "Our Sensor Driver Information:");
    shell_print(shell, "Device Name: %s", dev->name);
    shell_print(shell, "Device State: %s", device_is_ready(dev) ? "Ready" : "Not Ready");
    return 0;
}

/* Define the shell commands for our sensor driver */
SHELL_STATIC_SUBCMD_SET_CREATE(our_sensor_driver_shell_cmds,
    SHELL_CMD(fetch, NULL, "Fetch sensor data", our_sensor_driver_shell_fetch),
    SHELL_CMD(read, NULL, "Get sensor value", our_sensor_driver_shell_read),
    SHELL_CMD(info, NULL, "Get sensor driver information", our_sensor_driver_shell_info),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensorroot, &our_sensor_driver_shell_cmds, "Our Sensor Driver root Shell Commands", NULL);


