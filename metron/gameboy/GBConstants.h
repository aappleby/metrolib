#pragma once
#include <stdint.h>

const char**   get_op_strings();
const char**   get_op_strings2();
const char**   get_cb_strings();

const uint8_t* get_flag_mask();
const uint8_t* get_cb_flag_mask();
const uint8_t* get_DMG_ROM();
const uint8_t* get_vram_boot();
const uint8_t* get_framebuffer_boot();

const int*     get_op_sizes();

constexpr uint16_t BOOT_DIV = 0xEAF3;
constexpr uint16_t VRAM_ADDR_MASK = 0b1111111111111;

//-----------------------------------------------------------------------------
// Timing config

constexpr double TCYCLES_PER_SECOND = 4194304.0;
constexpr double PHASES_PER_SECOND = TCYCLES_PER_SECOND * 2.0;

#define TCYCLES_LINE      456
#define TCYCLES_OAM       80
#define TCYCLES_VRAM      172
#define TCYCLES_HBLANK    204

#define HBLANK_DELAY_START  8

#define MCYCLES_PER_FRAME (114 * 154)

//-----------------------------------------------------------------------------
// Memory map

#define ADDR_BOOT_ROM_BEGIN  0x0000
#define ADDR_BOOT_ROM_END    0x00FF

#define ADDR_CART_ROM_BEGIN  0x0000
#define ADDR_CART_ROM_END    0x7FFF

#define ADDR_VRAM_BEGIN      0x8000
#define ADDR_VRAM_END        0x9FFF

#define ADDR_CART_RAM_BEGIN  0xA000
#define ADDR_CART_RAM_END    0xBFFF

#define ADDR_MAIN_RAM_BEGIN  0xC000
#define ADDR_MAIN_RAM_END    0xDFFF

#define ADDR_ECHO_RAM_BEGIN  0xE000
#define ADDR_ECHO_RAM_END    0xFDFF

#define ADDR_OAM_BEGIN       0xFE00
#define ADDR_OAM_END         0xFE9F

#define ADDR_IOBUS_BEGIN     0xFF00
#define ADDR_IOBUS_END       0xFFFF

//----------

#define ADDR_TILE0       0x8000
#define ADDR_TILE1       0x8800
#define ADDR_MAP0        0x9800
#define ADDR_MAP1        0x9C00

//----------

#define ADDR_IOREG_BEGIN 0xFF00
#define ADDR_P1          0xFF00
#define ADDR_SB          0xFF01
#define ADDR_SC          0xFF02

#define ADDR_TIMER_BEGIN 0xFF04
#define ADDR_DIV         0xFF04
#define ADDR_TIMA        0xFF05
#define ADDR_TMA         0xFF06
#define ADDR_TAC         0xFF07
#define ADDR_TIMER_END   0xFF07

#define ADDR_IF          0xFF0F
#define ADDR_IOREG_END   0xFF0F

#define ADDR_SPU_BEGIN   0xFF10

#define ADDR_NR10        0xFF10
#define ADDR_NR11        0xFF11
#define ADDR_NR12        0xFF12
#define ADDR_NR13        0xFF13
#define ADDR_NR14        0xFF14

#define ADDR_NR21        0xFF16
#define ADDR_NR22        0xFF17
#define ADDR_NR23        0xFF18
#define ADDR_NR24        0xFF19

#define ADDR_NR30        0xFF1A
#define ADDR_NR31        0xFF1B
#define ADDR_NR32        0xFF1C
#define ADDR_NR33        0xFF1D
#define ADDR_NR34        0xFF1E

#define ADDR_NR41        0xFF20
#define ADDR_NR42        0xFF21
#define ADDR_NR43        0xFF22
#define ADDR_NR44        0xFF23

#define ADDR_NR50        0xFF24
#define ADDR_NR51        0xFF25
#define ADDR_NR52        0xFF26

#define ADDR_SPU_END     0xFF3F

#define ADDR_GPU_BEGIN   0xFF40
#define ADDR_LCDC        0xFF40
#define ADDR_STAT        0xFF41
#define ADDR_SCY         0xFF42
#define ADDR_SCX         0xFF43
#define ADDR_LY          0xFF44
#define ADDR_LYC         0xFF45
#define ADDR_DMA         0xFF46
#define ADDR_BGP         0xFF47
#define ADDR_OBP0        0xFF48
#define ADDR_OBP1        0xFF49
#define ADDR_WY          0xFF4A
#define ADDR_WX          0xFF4B
#define ADDR_GPU_END     0xFF4B

#define ADDR_DISABLE_BOOTROM 0xFF50

#define ADDR_UNUSABLE_BEGIN  0xFF4C
#define ADDR_UNUSABLE_END    0xFF47

#define ADDR_ZEROPAGE_BEGIN  0xFF80
#define ADDR_ZEROPAGE_END    0xFFFE

#define ADDR_IE     0xFFFF

//-----------------------------------------------------------------------------
// Flags

#define BIT_VBLANK  0
#define BIT_STAT    1
#define BIT_TIMER   2
#define BIT_SERIAL  3
#define BIT_JOYPAD  4

#define INT_VBLANK_MASK  0b00000001
#define INT_STAT_MASK    0b00000010
#define INT_TIMER_MASK   0b00000100
#define INT_SERIAL_MASK  0b00001000
#define INT_JOYPAD_MASK  0b00010000

#define EI_GLITCH    0b10000000
#define EI_LYC       0b01000000
#define EI_OAM       0b00100000
#define EI_VBLANK    0b00010000
#define EI_HBLANK    0b00001000

#define STAT_LYC     0b00000100

#define PPU_STATE_HBLANK 0
#define PPU_STATE_VBLANK 1
#define PPU_STATE_OAM    2
#define PPU_STATE_VRAM   3

#define FLAG_BG_ON        0x01
#define FLAG_OBJ_ON       0x02
#define FLAG_TALL_SPRITES 0x04
#define FLAG_BG_MAP_1     0x08
#define FLAG_TILE_0       0x10
#define FLAG_WIN_ON       0x20
#define FLAG_WIN_MAP_1    0x40
#define FLAG_LCD_ON       0x80

#define SPRITE_PRI    0x80
#define SPRITE_FLIP_Y 0x40
#define SPRITE_FLIP_X 0x20
#define SPRITE_PAL    0x10

#define TAC_RUN 0x04

#define MB_DELTA_AB   ((phase_total & 7) == 0)
#define MB_DELTA_BC   ((phase_total & 7) == 1)
#define MB_DELTA_CD   ((phase_total & 7) == 2)
#define MB_DELTA_DE   ((phase_total & 7) == 3)
#define MB_DELTA_EF   ((phase_total & 7) == 4)
#define MB_DELTA_FG   ((phase_total & 7) == 5)
#define MB_DELTA_GH   ((phase_total & 7) == 6)
#define MB_DELTA_HA   ((phase_total & 7) == 7)
