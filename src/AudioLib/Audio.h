#pragma once
#include <stdint.h>

constexpr int64_t output_hz = 48000;
typedef int16_t sample_t;

extern sample_t spu_ring_buffer[];
extern uint16_t spu_ring_cursor;

void audio_init();
void audio_stop();
void audio_post(int input_hz, sample_t in_l_i, sample_t in_r_i);
int  audio_queue_size();
