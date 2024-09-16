#include "write_data_to_shm.hpp"

void* write_data_to_shm(void* args) 
{
    thread_args* thd_args = (thread_args*)args;
    size_t total_data_size = 0;
    int pthread_count = 0;

    while(1) {
        sem_wait(&(thd_args->sem_write_thread));

        std::cout << "bbb" << std::endl;

        sem_wait(thd_args->sem_write);

        std::cout << "Waiting for data" << std::endl;

        pthread_mutex_lock(&(thd_args->mutex));

        //pthread_cond_wait(&(thd_args->cond), &(thd_args->mutex));
        pthread_count++;
        std::cout << "shm.cpp pthread_count: " << pthread_count << std::endl;

        total_data_size += thd_args->frame_data_info->data_size;
        std::cout << "Total data size: " << total_data_size << std::endl;

        // Gets data from NVENC
        //thd_args->frame_data_info->data_size = packet.size();
        //memcpy(thd_args->data, packet.data(), packet.size());
        // For debugging
        std::cout << "Data size: " << thd_args->frame_data_info->data_size << std::endl;
        std::cout << "Data[10]: " << (int)thd_args->data[10] << std::endl;

        // Copy data to shared memory
        memcpy(thd_args->shm_for_data_info, thd_args->frame_data_info, sizeof(frame_data_info));
        memcpy(thd_args->shm_for_data, thd_args->data, thd_args->frame_data_info->data_size);

        //pthread_cond_signal(&(thd_args->cond));

        sem_post(thd_args->sem_read);

        //usleep(50000);

        pthread_mutex_unlock(&(thd_args->mutex));

        sem_post(&(thd_args->sem_read_thread));
    }

    return NULL;
}

/*
void* write_data_to_shm(
    thread_args* thd_args,
    std::vector<uint8_t>& packet
    ) 
{

    while(1) {
        sem_wait(thd_args->sem);

        pthread_mutex_lock(&(thd_args->mutex));

        pthread_cond_wait(&(thd_args->cond), &(thd_args->mutex));

        // Gets data from NVENC
        thd_args->frame_data_info->data_size = packet.size();
        //memcpy(thd_args->data, packet.data(), packet.size());
        // For debugging
        std::cout << "Data size: " << thd_args->frame_data_info->data_size << std::endl;
        std::cout << "Data[10]: " << (int)thd_args->data[10] << std::endl;

        // Copy data to shared memory
        memcpy(thd_args->shm_for_data_info, thd_args->frame_data_info, sizeof(frame_data_info));
        //memcpy(thd_args->shm_for_data, thd_args->data, thd_args->frame_data_info->data_size);
        memcpy(thd_args->shm_for_data, packet.data(), thd_args->frame_data_info->data_size);

        //pthread_cond_signal(&(thd_args->cond));

        pthread_mutex_unlock(&(thd_args->mutex));

        sem_post(thd_args->sem);
    }

    return NULL;
}
*/