#ifndef __BOARD_CONFIG_HPP__
#define __BOARD_CONFIG_HPP__

#define BUTTON_L 38
#define BUTTON_M 37
#define BUTTON_R 39


#if defined (TTGO_T4_V12) || (TTGO_T4_V13)
    #define TFT_CS 27
    #define TFT_MOSI 23
    #define TFT_CLK 18
    #define TFT_RST 5
    #define TFT_MISO 12
    #define TFT_BL 4 // GPIO not managed by library
#endif

#ifdef TTGO_TM
    #define TFT_CS 5
    #define TFT_DC 16
    #define TFT_MOSI 23
    #define TFT_CLK 18
    #define TFT_RST 17
    #define TFT_MISO -1
    #define TFT_BL 4 // GPIO not managed by library
#endif

#ifdef TTGO_T4_V12
    #define TFT_DC 26
#endif

#ifdef TTGO_T4_V13
    #define TFT_DC 32
#endif

#endif
