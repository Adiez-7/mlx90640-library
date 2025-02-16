#include "mlx90640_i2c_driver.hpp"
#include <iostream>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>

#define MLX90640_I2C_ADDR 0x33

static int i2c_fd = -1;

void MLX90640_I2CInit() {
    i2c_fd = open("/dev/i2c-1", O_RDWR);
    if (i2c_fd < 0) {
        std::cerr << "Failed to open I2C bus" << std::endl;
    }
}

int MLX90640_I2CRead(uint8_t slaveAddr, uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data) {
    if (i2c_fd < 0) return -1;
    
    uint8_t reg[2] = { static_cast<uint8_t>(startAddress >> 8), static_cast<uint8_t>(startAddress & 0xFF) };
    if (write(i2c_fd, reg, 2) != 2) return -1;
    
    uint8_t buf[nMemAddressRead * 2];
    if (read(i2c_fd, buf, sizeof(buf)) != sizeof(buf)) return -1;
    
    for (uint16_t i = 0; i < nMemAddressRead; ++i) {
        data[i] = (buf[2 * i] << 8) | buf[2 * i + 1];
    }
    return 0;
}

int MLX90640_I2CWrite(uint8_t slaveAddr, uint16_t writeAddress, uint16_t data) {
    if (i2c_fd < 0) return -1;
    
    uint8_t buf[4] = {
        static_cast<uint8_t>(writeAddress >> 8), static_cast<uint8_t>(writeAddress & 0xFF),
        static_cast<uint8_t>(data >> 8), static_cast<uint8_t>(data & 0xFF)
    };
    return write(i2c_fd, buf, sizeof(buf)) == sizeof(buf) ? 0 : -1;
}

void MLX90640_I2CFreqSet(int freq) {
    // Not implemented
}

int MLX90640_I2CErrno() {
    return errno;
}

void MLX90640_ReadImage(float *image_data) {
    uint16_t frame_data[834];
    MLX90640_I2CRead(MLX90640_I2C_ADDR, 0x2400, 832, frame_data);
    for (int i = 0; i < 768; ++i) {
        image_data[i] = static_cast<float>(frame_data[i]);
    }
}
