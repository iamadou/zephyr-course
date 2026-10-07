#define DT_DRV_COMPAT our_driver


#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>


LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

static int channel_get_my_impl(const struct device *dev, enum sensor_channel chan, struct sensor_value *val) {
    // Implementation of channel_get for our driver

    LOG_INF("Hello from Channel Get Implementation for channel: %d", chan);
    return 0;
}


static DEVICE_API(sensor, api_iomico_lecture) = {
    .channel_get = channel_get_my_impl,
};

static int init(const struct device *dev) {
    LOG_INF("Hello from Our Driver Init");
    return 0;
}

#define OUR_DRIVER_DEFINE(inst)                                        \
    DEVICE_DT_INST_DEFINE(inst,                                        \
                          init,                                        \
                          NULL,                                        \
                          NULL,                                        \
                          NULL,                                        \
                          POST_KERNEL,                                 \
                          CONFIG_KERNEL_INIT_PRIORITY_DEVICE,          \
                          &api_iomico_lecture);


DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL, POST_KERNEL, 80, &api_iomico_lecture);