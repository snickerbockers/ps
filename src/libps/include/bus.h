// Copyright 2019 Michael Rodriguez
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
// OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
// CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <stdint.h>

struct libps_gpu;

struct libps_dma_channel
{
    // Base address
    uint32_t madr;

    // Block Control
    uint32_t bcr;

    // Channel Control
    uint32_t chcr;
};

struct libps_bus
{
    // Main RAM (first 64K reserved for BIOS)
    uint8_t* ram;

    uint8_t scratch_pad[4096];

    // 0x1F801070 - I_STAT - Interrupt status register
    // (R=Status, W=Acknowledge)
    uint32_t i_stat;

    // 0x1F801074 - I_MASK - Interrupt mask register (R/W)
    uint32_t i_mask;

    // 0x1F8010F0 - DMA Control Register (R/W)
    uint32_t dpcr;

    // 0x1F8010F4 - DMA Interrupt Register (R/W)
    uint32_t dicr;

    // GPU instance
    struct libps_gpu* gpu;

    // DMA channel 2 - GPU (lists + image data)
    struct libps_dma_channel dma_gpu_channel;

    // DMA channel 6 - OTC (reverse clear OT)
    struct libps_dma_channel dma_otc_channel;
};

// Allocates memory for a `libps_bus` structure and returns a pointer to it if
// memory allocation was successful, or `NULL` otherwise. This function should
// not be called anywhere other than `libps_system_create()`.
//
// `bios_data_ptr` should be a pointer to BIOS data, passed by
// `libps_system_create()`.
struct libps_bus* libps_bus_create(uint8_t* const bios_data_ptr);

// Deallocates memory held by `bus`. This function should not be called
// anywhere other than `libps_system_destroy()`.
void libps_bus_destroy(struct libps_bus* bus);

// Resets the system bus, which resets the peripherals to their startup state.
void libps_bus_reset(struct libps_bus* bus);

// Handles DMA requests.
void libps_bus_step(struct libps_bus* bus);

// Returns a word from memory referenced by physical address `paddr`.
uint32_t libps_bus_load_word(struct libps_bus* bus, const uint32_t paddr);

// Returns a halfword from memory referenced by physical address `paddr`.
uint16_t libps_bus_load_halfword(struct libps_bus* bus, const uint32_t paddr);

// Returns a byte from memory referenced by physical address `paddr`.
uint8_t libps_bus_load_byte(struct libps_bus* bus, const uint32_t paddr);

// Stores word `data` into memory referenced by phsyical address `paddr`.
void libps_bus_store_word(struct libps_bus* bus,
                          const uint32_t paddr,
                          const uint32_t data);

// Stores halfword `data` into memory referenced by phsyical address `paddr`.
void libps_bus_store_halfword(struct libps_bus* bus,
                              const uint32_t paddr,
                              const uint16_t data);

// Stores byte `data` into memory referenced by phsyical address `paddr`.
void libps_bus_store_byte(struct libps_bus* bus,
                          const uint32_t paddr,
                          const uint8_t data);

#ifdef __cplusplus
}
#endif // __cplusplus
