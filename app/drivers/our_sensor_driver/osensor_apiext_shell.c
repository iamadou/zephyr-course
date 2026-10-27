#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

#include <stdlib.h>
#include "our_sensor_driver.h"


#define OUR_SENSOR_DEVICE DEVICE_DT_GET(DT_NODELABEL(our_sensor_driver0))


static int cmd_sensor_info(const struct shell *sh, size_t argc, char **argv)
{
	const struct device *dev = OUR_SENSOR_DEVICE;
	shell_print(sh, "Device name: %s, Ready: %s", dev->name, device_is_ready(dev) ? "Yes" : "No");
	return 0;
}


static int cmd_sensor_set(const struct shell *shell, size_t argc, char **argv)
{
    const struct device *dev = OUR_SENSOR_DEVICE;
    char *endptr;
    
    /* Check if the device is ready */
    if (!device_is_ready(dev)) {
        shell_error(shell, "Error: Device not ready");
        return -ENODEV;
    }

    /* Parse the sensor value from the command line argument */
    long value = strtol(argv[1], &endptr, 10);

    /* Check if the input is valid */
    if (*endptr != '\0' || argv[1] == endptr) {
        shell_error(shell, "Error: %s is not a valid integer", argv[1]);
        return -EINVAL;
    }

    /* Check if the value is within the valid range */
    if (value < 0 || value > 10000) {
        shell_error(shell, "Error: Value %ld must be between 0 and 10000", value);
        return -EINVAL;
    }

    /* Call our API extension set calibration */
    int ret = our_sensor_driver_set_calibration(dev, (int32_t)value);
    if (ret < 0) {
        shell_error(shell, "Failed to set calibration: %d", ret);
        return ret;
    }

    shell_print(shell, "Success: Calibration value set to: %ld", value);
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(our_sensor_subcmd,

    SHELL_CMD(info,  NULL, "Prints device name and ready state", cmd_sensor_info),
    /*
     * SHELL_CMD_ARG(name, subcommands, help, handler, args_count, optional_args_count)
     * - set : Command name
     * - NULL : No subcommands for this command
     * - Help string describing the command
     * - cmd_sensor_set : Function to handle the command
     * - 2 : Number of required arguments (command name + value)
     * - 0 : Number of optional arguments    
    */
    SHELL_CMD_ARG(set, NULL, "Set sensor calibration value <0-10000>", cmd_sensor_set, 2, 0),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(custom_sensor, &our_sensor_subcmd, "Our sensor driver commands - iomico L7 task 2", NULL);