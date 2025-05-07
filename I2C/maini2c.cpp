#include <maini2c.h>

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


void maini2c::run_master() {
    
    for (uint8_t mem_address = 0;; mem_address = (mem_address + 32) % 256) {
        char msg[32];
        snprintf(msg, sizeof(msg), "Hello, I2C slave! - 0x%02X", mem_address);
        uint8_t msg_len = strlen(msg);

        uint8_t buf[32];
        buf[0] = mem_address;
        memcpy(buf + 1, msg, msg_len);
        // write message at mem_address
        printf("Write at 0x%02X: '%s'\n", mem_address, msg);
        int count = i2c_write_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, 1 + msg_len, false);
        if (count < 0) {
            puts("Couldn't write to slave, please check your wiring!");
            return;
        }
        hard_assert(count == 1 + msg_len);

        // seek to mem_address
        count = i2c_write_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, 1, true);
        hard_assert(count == 1);
        // partial read
        uint8_t split = 5;
        count = i2c_read_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, split, true);
        hard_assert(count == split);
        buf[count] = '\0';
        printf("Read  at 0x%02X: '%s'\n", mem_address, buf);
        hard_assert(memcmp(buf, msg, split) == 0);
        // read the remaining bytes, continuing from last address
        count = i2c_read_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, msg_len - split, false);
        hard_assert(count == msg_len - split);
        buf[count] = '\0';
        printf("Read  at 0x%02X: '%s'\n", mem_address + split, buf);
        hard_assert(memcmp(buf, msg + split, msg_len - split) == 0);

        puts("");
        sleep_ms(100);
    }
};

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

void maini2c::send_message(ModuleState state) {
    uint8_t msgLength = sizeof(ModuleState);
    uint8_t buf[msgLength + 1];
    buf[0] = 0;
    memcpy(buf + 1, &state, msgLength);
    int count = i2c_write_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, 1 + msgLength, false);
    if (count < 0) {
        puts("Couldn't write to slave, please check your wiring!");
        return;
    }
    hard_assert(count == 1 + msgLength);
}

void maini2c::read_message(ModuleState& state) {
    uint8_t msgLength = sizeof(state);
    uint8_t buf[msgLength];
    uint8_t address = 14;
    // seek to mem_address
    int count = i2c_write_blocking(i2c1, I2C_SLAVE_ADDRESS, &address, 1, true);
    printf("I am ashamed to say that I wrote %d bytes\n\n", count);
    hard_assert(count == 1);
    // partial read
    uint8_t split = 5;
    count = i2c_read_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, split, true);
    hard_assert(count == split);
    
    // read the remaining bytes, continuing from last address
    count = i2c_read_blocking(i2c1, I2C_SLAVE_ADDRESS, buf + split, msgLength - split, false);

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