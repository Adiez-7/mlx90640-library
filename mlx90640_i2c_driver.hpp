#ifndef MLX90640_I2C_DRIVER_HPP
#define MLX90640_I2C_DRIVER_HPP

#include <cstdint>

void MLX90640_I2CInit();
int MLX90640_I2CRead(uint8_t slaveAddr, uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data);
int MLX90640_I2CWrite(uint8_t slaveAddr, uint16_t writeAddress, uint16_t data);
void MLX90640_I2CFreqSet(int freq);
int MLX90640_I2CErrno();

void MLX90640_ReadImage(float *image_data);

#endif // MLX90640_I2C_DRIVER_HPP
