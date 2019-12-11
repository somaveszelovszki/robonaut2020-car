#include <cfg_board.h>
#include <micro/utils/log.hpp>
#include <micro/hw/MPU9250_Gyroscope.hpp>
#include <micro/task/common.hpp>
#include <micro/sensor/Filter.hpp>

#include <globals.hpp>

#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

using namespace micro;

static hw::MPU9250 gyro(i2c_Gyro, hw::Ascale::AFS_2G, hw::Gscale::GFS_250DPS, hw::Mscale::MFS_16BITS, MMODE_ODR_100Hz);
static LowPassFilter<degree_t, 5> gyroAngleFilter;

extern "C" void runGyroTask(const void *argument) {

    vTaskDelay(300); // gives time to other tasks to wake up

    gyro.initialize();

    globals::isGyroTaskInitialized = true;
    LOG_DEBUG("Gyro task initialized");

    while (true) {
        const point3<gauss_t> mag = gyro.readMagData();
        if (!isZero(mag.X) || !isZero(mag.Y) || !isZero(mag.Z)) {
            globals::car.pose.angle = normalize360(gyroAngleFilter.update(atan2(mag.Y, mag.X)));
            // TODO handle ~180deg bug
        }

        vTaskDelay(5);
    }

    vTaskDelete(nullptr);
}
