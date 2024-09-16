#include <cstring>
#include <vector>
#include <cstring>
#include <iostream>
#include <unistd.h>

#include "globals.h"

void* write_data_to_shm(
    void* args
);

/*
void* write_data_to_shm(
    thread_args* thd_args,
    std::vector<uint8_t>& packet
);
*/