#include <I2C/maini2c.h>

// The slave implements a 256 byte memory. To write a series of bytes, the master first
// writes the memory address, followed by the data. The address is automatically incremented
// for each byte transferred, looping back to 0 upon reaching the end. Reading is done
// sequentially from the current memory address.
static struct
{
    uint8_t mem[256];
    uint8_t mem_address;
    bool mem_address_written;
} context;

void maini2c::init_master() {
    gpio_init(I2C_MASTER_SDA_PIN);
    gpio_set_function(I2C_MASTER_SDA_PIN, GPIO_FUNC_I2C);
    // pull-ups are already active on slave side, this is just a fail-safe in case the wiring is faulty
    gpio_pull_up(I2C_MASTER_SDA_PIN);

    gpio_init(I2C_MASTER_SCL_PIN);
    gpio_set_function(I2C_MASTER_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_MASTER_SCL_PIN);

    i2c_init(i2c1, I2C_BAUDRATE);

}

void maini2c::send_message(ModuleState state, uint address) {
    uint8_t msgLength = sizeof(ModuleState);
    uint8_t buf[msgLength + 1];
    buf[0] = 0;
    memcpy(buf + 1, &state, msgLength);
    int count = i2c_write_blocking(i2c1, address, buf, 1 + msgLength, false);
    if (count < 0) {
        puts("Couldn't write to slave, please check your wiring!");
        return;
    }
    hard_assert(count == 1 + msgLength);
}

void maini2c::read_message(ModuleState& state, uint address) {
    uint8_t msgLength = sizeof(state);
    uint8_t buf[msgLength];
    uint8_t writeAddress = 14;
    // seek to mem_address
    int count = i2c_write_blocking(i2c1, address, &writeAddress, 1, true);
    printf("I am ashamed to say that I wrote %d bytes\n\n", count);
    hard_assert(count == 1);
    // partial read
    uint8_t split = 5;
    count = i2c_read_blocking(i2c1, address, buf, split, true);
    hard_assert(count == split);
    
    // read the remaining bytes, continuing from last address
    count = i2c_read_blocking(i2c1, address, buf + split, msgLength - split, false);

    memcpy(&state, buf, msgLength);

    printf("%d", state.state);
    puts("\n");
    printf("%d", state.theta);
    puts("\n");
    printf("%d", state.v);
    puts("\n");
    printf("%d", state.bat);
    puts("\n");
    printf("%d", state.time);
    puts("\n");

}