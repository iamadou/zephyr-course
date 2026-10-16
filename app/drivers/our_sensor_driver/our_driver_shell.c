#include <zephyr/shell/shell.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>


static int cmd_channel_get_handler(const struct shell *shell, size_t argc, char **argv) {
    const struct device *dev = shell_device_get_binding(argv[1]);
    if (!dev) {
        shell_error(shell, "Device not found: %s", argv[1]);
        return -ENODEV;
    }
    struct sensor_value val;
    int ret = sensor_channel_get(dev, SENSOR_CHAN_VOLTAGE, &val);
    if (ret < 0) {
        shell_error(shell, "Failed to get channel: %d", ret);
        return ret;
    }

    shell_info(shell, "Hello from channel get %d", val.val1);
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(our_driver_subcmd,
    SHELL_CMD_ARG(channel_get, NULL, "Get the channel of my driver",cmd_channel_get_handler, 1, 0),
    SHELL_SUBCMD_SET_END,
);

SHELL_CMD_REGISTER(our_driver, &our_driver_subcmd, "Our driver set of commands", NULL);