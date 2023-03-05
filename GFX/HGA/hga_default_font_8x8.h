/**
 *  @brief 8x8 monochrome bitmap fonts for rendering 8 bit characters ASCII codes 0 - 255 
 *  @details Composed of:
 *  + ASCII   0 - 127 as unicode points U+0000 - U+007F (basic latin)
 *  + ASCII 128 - 223 as unicode points U+00A0 - U+00FF (extended latin)
 *  + ASCII 224 - 255 as unicode points U+2580 - U+259F (block elements)
 *  @note *msb* is first pixel variation of Daniel Hepper's lsb version below
 *  @author    Jeremy Thornton
 *  @date      23.06.2022 v2 03/05/2023
 *  @copyright � Jeremy Thornton, 2022. All right reserved.
 *
 *  @note Based on:
 * Author: Daniel Hepper <daniel@hepper.net> (note lsb is left most pixel)
 *
 * License: Public Domain
 *
 * Based on:
 * // Summary: font8x8.h
 * // 8x8 monochrome bitmap fonts for rendering
 * //
 * // Author:
 * //     Marcel Sondaar
 * //     International Business Machines (public domain VGA fonts)
 * //
 * // License:
 * //     Public Domain
 *
 * Fetched from: http://dimensionalrift.homelinux.net/combuster/mos3/?p=viewsource&file=/modules/gfx/font8_8.asm
 **/
#ifndef HGA_DEFAULT_FONT_H
#define HGA_DEFAULT_FONT_H

#include <stdint.h>

namespace hga {

    /**
    * Original header:

    ; Summary: font8_8.asm
    ; 8x8 monochrome bitmap fonts for rendering
    ;
    ; Author:
    ;     Marcel Sondaar
    ;     International Business Machines (public domain VGA fonts)
    ;
    ; License:
    ;     Public Domain
    ;

    */
    const uint8_t default_font_data[256][8] = {
        // unicode points U+0000 - U+007F (basic latin)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0000 (NUL)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0001 (SOH)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0002 (STX)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0003 (ETX)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0004 (EOT)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0005 (ENQ)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0006 (ACK)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0007 (BEL)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0008 (BS)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0009 (HTAB)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+000A (LF)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+000B (VT)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+000C (FF)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+000D (CR)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+000E (SO)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+000F (SI)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0010 (DLE)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0011 (DC1)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0012 (DC2)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0013 (DC3)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0014 (DC4)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0015 (NAK)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0016 (SYN)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0017 (ETB)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0018 (CAN)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0019 (EM)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+001A (SUB)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+001B (ESC)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+001C (FS)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+001D (GS)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+001E (RS)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+001F (US)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0020 ( )
        { 0x18, 0x3c, 0x3c, 0x18, 0x18, 0x00, 0x18, 0x00},	// U+0021 (!)
        { 0x6c, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0022 (")
        { 0x6c, 0x6c, 0xfe, 0x6c, 0xfe, 0x6c, 0x6c, 0x00},	// U+0023 (#)
        { 0x30, 0x7c, 0xc0, 0x78, 0x0c, 0xf8, 0x30, 0x00},	// U+0024 ($)
        { 0x00, 0xc6, 0xcc, 0x18, 0x30, 0x66, 0xc6, 0x00},	// U+0025 (%)
        { 0x38, 0x6c, 0x38, 0x76, 0xdc, 0xcc, 0x76, 0x00},	// U+0026 (&)
        { 0x60, 0x60, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0027 (')
        { 0x18, 0x30, 0x60, 0x60, 0x60, 0x30, 0x18, 0x00},	// U+0028 (()
        { 0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60, 0x00},	// U+0029 ())
        { 0x00, 0x66, 0x3c, 0xff, 0x3c, 0x66, 0x00, 0x00},	// U+002A (*)
        { 0x00, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x00, 0x00},	// U+002B (+)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x60},	// U+002C (,)
        { 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00},	// U+002D (-)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00},	// U+002E (.)
        { 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00},	// U+002F (/)
        { 0x7c, 0xc6, 0xce, 0xde, 0xf6, 0xe6, 0x7c, 0x00},	// U+0030 (0)
        { 0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x00},	// U+0031 (1)
        { 0x78, 0xcc, 0x0c, 0x38, 0x60, 0xcc, 0xfc, 0x00},	// U+0032 (2)
        { 0x78, 0xcc, 0x0c, 0x38, 0x0c, 0xcc, 0x78, 0x00},	// U+0033 (3)
        { 0x1c, 0x3c, 0x6c, 0xcc, 0xfe, 0x0c, 0x1e, 0x00},	// U+0034 (4)
        { 0xfc, 0xc0, 0xf8, 0x0c, 0x0c, 0xcc, 0x78, 0x00},	// U+0035 (5)
        { 0x38, 0x60, 0xc0, 0xf8, 0xcc, 0xcc, 0x78, 0x00},	// U+0036 (6)
        { 0xfc, 0xcc, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x00},	// U+0037 (7)
        { 0x78, 0xcc, 0xcc, 0x78, 0xcc, 0xcc, 0x78, 0x00},	// U+0038 (8)
        { 0x78, 0xcc, 0xcc, 0x7c, 0x0c, 0x18, 0x70, 0x00},	// U+0039 (9)
        { 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00},	// U+003A (:)
        { 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x60},	// U+003B (;)
        { 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x00},	// U+003C (<)
        { 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00},	// U+003D (=)
        { 0x60, 0x30, 0x18, 0x0c, 0x18, 0x30, 0x60, 0x00},	// U+003E (>)
        { 0x78, 0xcc, 0x0c, 0x18, 0x30, 0x00, 0x30, 0x00},	// U+003F (?)
        { 0x7c, 0xc6, 0xde, 0xde, 0xde, 0xc0, 0x78, 0x00},	// U+0040 (@)
        { 0x30, 0x78, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0x00},	// U+0041 (A)
        { 0xfc, 0x66, 0x66, 0x7c, 0x66, 0x66, 0xfc, 0x00},	// U+0042 (B)
        { 0x3c, 0x66, 0xc0, 0xc0, 0xc0, 0x66, 0x3c, 0x00},	// U+0043 (C)
        { 0xf8, 0x6c, 0x66, 0x66, 0x66, 0x6c, 0xf8, 0x00},	// U+0044 (D)
        { 0xfe, 0x62, 0x68, 0x78, 0x68, 0x62, 0xfe, 0x00},	// U+0045 (E)
        { 0xfe, 0x62, 0x68, 0x78, 0x68, 0x60, 0xf0, 0x00},	// U+0046 (F)
        { 0x3c, 0x66, 0xc0, 0xc0, 0xce, 0x66, 0x3e, 0x00},	// U+0047 (G)
        { 0xcc, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0xcc, 0x00},	// U+0048 (H)
        { 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00},	// U+0049 (I)
        { 0x1e, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78, 0x00},	// U+004A (J)
        { 0xe6, 0x66, 0x6c, 0x78, 0x6c, 0x66, 0xe6, 0x00},	// U+004B (K)
        { 0xf0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xfe, 0x00},	// U+004C (L)
        { 0xc6, 0xee, 0xfe, 0xfe, 0xd6, 0xc6, 0xc6, 0x00},	// U+004D (M)
        { 0xc6, 0xe6, 0xf6, 0xde, 0xce, 0xc6, 0xc6, 0x00},	// U+004E (N)
        { 0x38, 0x6c, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00},	// U+004F (O)
        { 0xfc, 0x66, 0x66, 0x7c, 0x60, 0x60, 0xf0, 0x00},	// U+0050 (P)
        { 0x78, 0xcc, 0xcc, 0xcc, 0xdc, 0x78, 0x1c, 0x00},	// U+0051 (Q)
        { 0xfc, 0x66, 0x66, 0x7c, 0x6c, 0x66, 0xe6, 0x00},	// U+0052 (R)
        { 0x78, 0xcc, 0xe0, 0x70, 0x1c, 0xcc, 0x78, 0x00},	// U+0053 (S)
        { 0xfc, 0xb4, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00},	// U+0054 (T)
        { 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xfc, 0x00},	// U+0055 (U)
        { 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x00},	// U+0056 (V)
        { 0xc6, 0xc6, 0xc6, 0xd6, 0xfe, 0xee, 0xc6, 0x00},	// U+0057 (W)
        { 0xc6, 0xc6, 0x6c, 0x38, 0x38, 0x6c, 0xc6, 0x00},	// U+0058 (X)
        { 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x30, 0x78, 0x00},	// U+0059 (Y)
        { 0xfe, 0xc6, 0x8c, 0x18, 0x32, 0x66, 0xfe, 0x00},	// U+005A (Z)
        { 0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x00},	// U+005B ([)
        { 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x02, 0x00},	// U+005C (\)
        { 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00},	// U+005D (])
        { 0x10, 0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00, 0x00},	// U+005E (^)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff},	// U+005F (_)
        { 0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+0060 (`)
        { 0x00, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x76, 0x00},	// U+0061 (a)
        { 0xe0, 0x60, 0x60, 0x7c, 0x66, 0x66, 0xdc, 0x00},	// U+0062 (b)
        { 0x00, 0x00, 0x78, 0xcc, 0xc0, 0xcc, 0x78, 0x00},	// U+0063 (c)
        { 0x1c, 0x0c, 0x0c, 0x7c, 0xcc, 0xcc, 0x76, 0x00},	// U+0064 (d)
        { 0x00, 0x00, 0x78, 0xcc, 0xfc, 0xc0, 0x78, 0x00},	// U+0065 (e)
        { 0x38, 0x6c, 0x60, 0xf0, 0x60, 0x60, 0xf0, 0x00},	// U+0066 (f)
        { 0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8},	// U+0067 (g)
        { 0xe0, 0x60, 0x6c, 0x76, 0x66, 0x66, 0xe6, 0x00},	// U+0068 (h)
        { 0x30, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00},	// U+0069 (i)
        { 0x0c, 0x00, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78},	// U+006A (j)
        { 0xe0, 0x60, 0x66, 0x6c, 0x78, 0x6c, 0xe6, 0x00},	// U+006B (k)
        { 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00},	// U+006C (l)
        { 0x00, 0x00, 0xcc, 0xfe, 0xfe, 0xd6, 0xc6, 0x00},	// U+006D (m)
        { 0x00, 0x00, 0xf8, 0xcc, 0xcc, 0xcc, 0xcc, 0x00},	// U+006E (n)
        { 0x00, 0x00, 0x78, 0xcc, 0xcc, 0xcc, 0x78, 0x00},	// U+006F (o)
        { 0x00, 0x00, 0xdc, 0x66, 0x66, 0x7c, 0x60, 0xf0},	// U+0070 (p)
        { 0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0x1e},	// U+0071 (q)
        { 0x00, 0x00, 0xdc, 0x76, 0x66, 0x60, 0xf0, 0x00},	// U+0072 (r)
        { 0x00, 0x00, 0x7c, 0xc0, 0x78, 0x0c, 0xf8, 0x00},	// U+0073 (s)
        { 0x10, 0x30, 0x7c, 0x30, 0x30, 0x34, 0x18, 0x00},	// U+0074 (t)
        { 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0x76, 0x00},	// U+0075 (u)
        { 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x00},	// U+0076 (v)
        { 0x00, 0x00, 0xc6, 0xd6, 0xfe, 0xfe, 0x6c, 0x00},	// U+0077 (w)
        { 0x00, 0x00, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0x00},	// U+0078 (x)
        { 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8},	// U+0079 (y)
        { 0x00, 0x00, 0xfc, 0x98, 0x30, 0x64, 0xfc, 0x00},	// U+007A (z)
        { 0x1c, 0x30, 0x30, 0xe0, 0x30, 0x30, 0x1c, 0x00},	// U+007B ({)
        { 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00},	// U+007C (|)
        { 0xe0, 0x30, 0x30, 0x1c, 0x30, 0x30, 0xe0, 0x00},	// U+007D (})
        { 0x76, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+007E (~)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// U+007F (DEL)
        // unicode points U+00A0 - U+00FF (extended latin)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	// U+00A0 (no break space)
        { 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00 },	// U+00A1 (inverted !)
        { 0x18, 0x18, 0x7e, 0xc0, 0xc0, 0x7e, 0x18, 0x18 },	// U+00A2 (dollarcents)
        { 0x38, 0x6c, 0x64, 0xf0, 0x60, 0xe6, 0xfc, 0x00 },	// U+00A3 (pound sterling)
        { 0x00, 0x00, 0xc6, 0x7c, 0x6c, 0x7c, 0xc6, 0x00 },	// U+00A4 (currency mark)
        { 0xcc, 0xcc, 0x78, 0xfc, 0x30, 0xfc, 0x30, 0x30 },	// U+00A5 (yen)
        { 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00 },	// U+00A6 (broken pipe)
        { 0x3e, 0x63, 0x38, 0x6c, 0x6c, 0x38, 0xcc, 0x78 },	// U+00A7 (paragraph)
        { 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	// U+00A8 (diaeresis)
        { 0x3c, 0x42, 0x99, 0xa1, 0xa1, 0x99, 0x42, 0x3c },	// U+00A9 (copyright symbol)
        { 0x3c, 0x6c, 0x6c, 0x3e, 0x00, 0x00, 0x00, 0x00 },	// U+00AA (superscript a)
        { 0x00, 0x33, 0x66, 0xcc, 0x66, 0x33, 0x00, 0x00 },	// U+00AB (<<)
        { 0x00, 0x00, 0x00, 0xfc, 0x0c, 0x0c, 0x00, 0x00 },	// U+00AC (gun pointing left)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	// U+00AD (soft hyphen)
        { 0x3c, 0x42, 0xb9, 0xa5, 0xb9, 0xa5, 0x42, 0x3c },	// U+00AE (registered symbol)
        { 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	// U+00AF (macron)
        { 0x38, 0x6c, 0x6c, 0x38, 0x00, 0x00, 0x00, 0x00 },	// U+00B0 (degree)
        { 0x18, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x7e, 0x00 },	// U+00B1 (plusminus)
        { 0x38, 0x0c, 0x18, 0x30, 0x3c, 0x00, 0x00, 0x00 },	// U+00B2 (superscript 2)
        { 0x38, 0x0c, 0x18, 0x0c, 0x38, 0x00, 0x00, 0x00 },	// U+00B2 (superscript 3)
        { 0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	// U+00B2 (aigu)
        { 0x00, 0x00, 0x66, 0x66, 0x66, 0x7c, 0x60, 0xc0 },	// U+00B5 (mu)
        { 0x7f, 0xdb, 0xdb, 0x7b, 0x1b, 0x1b, 0x1b, 0x00 },	// U+00B6 (pilcrow)
        { 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00 },	// U+00B7 (central dot)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x0c, 0x78 },	// U+00B8 (cedille)
        { 0x10, 0x30, 0x10, 0x38, 0x00, 0x00, 0x00, 0x00 },	// U+00B9 (superscript 1)
        { 0x38, 0x6c, 0x6c, 0x38, 0x00, 0x00, 0x00, 0x00 },	// U+00BA (superscript 0)
        { 0x00, 0xcc, 0x66, 0x33, 0x66, 0xcc, 0x00, 0x00 },	// U+00BB (>>)
        { 0xc3, 0xc6, 0xcc, 0xbd, 0x37, 0x6f, 0xcf, 0xc0 },	// U+00BC (1/4)
        { 0xc3, 0xc6, 0xcc, 0xde, 0x33, 0x66, 0xcc, 0x0f },	// U+00BD (1/2)
        { 0xc0, 0x23, 0xc6, 0x2d, 0xdb, 0x35, 0x67, 0x01 },	// U+00BE (3/4)
        { 0x30, 0x00, 0x30, 0x60, 0xc0, 0xcc, 0x78, 0x00 },	// U+00BF (inverted ?)
        { 0xe0, 0x00, 0x38, 0x6c, 0xc6, 0xfe, 0xc6, 0x00 },	// U+00C0 (A grave)
        { 0x0e, 0x00, 0x38, 0x6c, 0xc6, 0xfe, 0xc6, 0x00 },	// U+00C1 (A aigu)
        { 0x38, 0x6c, 0x00, 0x7c, 0xc6, 0xfe, 0xc6, 0x00 },	// U+00C2 (A circumflex)
        { 0x76, 0xdc, 0x00, 0x7c, 0xc6, 0xfe, 0xc6, 0x00 },	// U+00C3 (A ~)
        { 0xc6, 0x38, 0x6c, 0xc6, 0xfe, 0xc6, 0xc6, 0x00 },	// U+00C4 (A umlaut)
        { 0x30, 0x30, 0x00, 0x78, 0xcc, 0xfc, 0xcc, 0x00 },	// U+00C5 (A ring)
        { 0x3e, 0x6c, 0xcc, 0xfe, 0xcc, 0xcc, 0xce, 0x00 },	// U+00C6 (AE)
        { 0x78, 0xcc, 0xc0, 0xcc, 0x78, 0x18, 0x0c, 0x78 },	// U+00C7 (C cedille)
        { 0xe0, 0x00, 0xfc, 0x60, 0x78, 0x60, 0xfc, 0x00 },	// U+00C8 (E grave)
        { 0x1c, 0x00, 0xfc, 0x60, 0x78, 0x60, 0xfc, 0x00 },	// U+00C9 (E aigu)
        { 0x30, 0x48, 0xfc, 0x60, 0x78, 0x60, 0xfc, 0x00 },	// U+00CA (E circumflex)
        { 0x6c, 0x00, 0xfc, 0x60, 0x78, 0x60, 0xfc, 0x00 },	// U+00CB (E umlaut)
        { 0xe0, 0x00, 0x78, 0x30, 0x30, 0x30, 0x78, 0x00 },	// U+00CC (I grave)
        { 0x1c, 0x00, 0x78, 0x30, 0x30, 0x30, 0x78, 0x00 },	// U+00CD (I aigu)
        { 0x30, 0x48, 0x00, 0x78, 0x30, 0x30, 0x78, 0x00 },	// U+00CE (I circumflex)
        { 0xcc, 0x00, 0x78, 0x30, 0x30, 0x30, 0x78, 0x00 },	// U+00CF (I umlaut)
        { 0xfc, 0x66, 0xf6, 0xf6, 0x66, 0x66, 0xfc, 0x00 },	// U+00D0 (Eth)
        { 0xfc, 0x00, 0xcc, 0xec, 0xfc, 0xdc, 0xcc, 0x00 },	// U+00D1 (N ~)
        { 0x70, 0x00, 0x18, 0x3c, 0x66, 0x3c, 0x18, 0x00 },	// U+00D2 (O grave)
        { 0x0e, 0x00, 0x18, 0x3c, 0x66, 0x3c, 0x18, 0x00 },	// U+00D3 (O aigu)
        { 0x3c, 0x66, 0x18, 0x3c, 0x66, 0x3c, 0x18, 0x00 },	// U+00D4 (O circumflex)
        { 0x76, 0xdc, 0x00, 0x7c, 0xc6, 0xc6, 0x7c, 0x00 },	// U+00D5 (O ~)
        { 0xc3, 0x18, 0x3c, 0x66, 0x66, 0x3c, 0x18, 0x00 },	// U+00D6 (O umlaut)
        { 0x00, 0x6c, 0x38, 0x10, 0x38, 0x6c, 0x00, 0x00 },	// U+00D7 (multiplicative x)
        { 0x3a, 0x6c, 0xce, 0xde, 0xf6, 0x6c, 0xb8, 0x00 },	// U+00D8 (O stroke)
        { 0x70, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00 },	// U+00D9 (U grave)
        { 0x0e, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00 },	// U+00DA (U aigu)
        { 0x3c, 0x66, 0x00, 0x66, 0x66, 0x66, 0x3c, 0x00 },	// U+00DB (U circumflex)
        { 0xcc, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x00 },	// U+00DC (U umlaut)
        { 0x0e, 0x00, 0x66, 0x66, 0x3c, 0x18, 0x18, 0x00 },	// U+00DD (Y aigu)
        { 0xf0, 0x60, 0x7c, 0x66, 0x66, 0x7c, 0x60, 0xf0 },	// U+00DE (Thorn)
        { 0x00, 0x78, 0xcc, 0xf8, 0xcc, 0xf8, 0xc0, 0xc0 },	// U+00DF (beta)
        { 0xe0, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x7e, 0x00 },	// U+00E0 (a grave)
        { 0x1c, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x7e, 0x00 },	// U+00E1 (a aigu)
        { 0x7e, 0xc3, 0x3c, 0x06, 0x3e, 0x66, 0x3f, 0x00 },	// U+00E2 (a circumflex)
        { 0x76, 0xdc, 0x78, 0x0c, 0x7c, 0xcc, 0x7e, 0x00 },	// U+00E3 (a ~)
        { 0xcc, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x7e, 0x00 },	// U+00E4 (a umlaut)
        { 0x30, 0x30, 0x78, 0x0c, 0x7c, 0xcc, 0x7e, 0x00 },	// U+00E5 (a ring)
        { 0x00, 0x00, 0x7f, 0x0c, 0x7f, 0xcc, 0x7f, 0x00 },	// U+00E6 (ae)
        { 0x00, 0x00, 0x78, 0xc0, 0xc0, 0x78, 0x0c, 0x38 },	// U+00E7 (c cedille)
        { 0xe0, 0x00, 0x78, 0xcc, 0xfc, 0xc0, 0x78, 0x00 },	// U+00E8 (e grave)
        { 0x1c, 0x00, 0x78, 0xcc, 0xfc, 0xc0, 0x78, 0x00 },	// U+00E9 (e aigu)
        { 0x7e, 0xc3, 0x3c, 0x66, 0x7e, 0x60, 0x3c, 0x00 },	// U+00EA (e circumflex)
        { 0xcc, 0x00, 0x78, 0xcc, 0xfc, 0xc0, 0x78, 0x00 },	// U+00EB (e umlaut)
        { 0xe0, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00 },	// U+00EC (i grave)
        { 0x38, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00 },	// U+00ED (i augu)
        { 0x7c, 0xc6, 0x38, 0x18, 0x18, 0x18, 0x3c, 0x00 },	// U+00EE (i circumflex)
        { 0xcc, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00 },	// U+00EF (i umlaut)
        { 0xd8, 0x70, 0xd8, 0x0c, 0x7c, 0xcc, 0x78, 0x00 },	// U+00F0 (eth)
        { 0x00, 0xf8, 0x00, 0xf8, 0xcc, 0xcc, 0xcc, 0x00 },	// U+00F1 (n ~)
        { 0x00, 0xe0, 0x00, 0x78, 0xcc, 0xcc, 0x78, 0x00 },	// U+00F2 (o grave)
        { 0x00, 0x1c, 0x00, 0x78, 0xcc, 0xcc, 0x78, 0x00 },	// U+00F3 (o aigu)
        { 0x78, 0xcc, 0x00, 0x78, 0xcc, 0xcc, 0x78, 0x00 },	// U+00F4 (o circumflex)
        { 0x76, 0xdc, 0x00, 0x78, 0xcc, 0xcc, 0x78, 0x00 },	// U+00F5 (o ~)
        { 0x00, 0xcc, 0x00, 0x78, 0xcc, 0xcc, 0x78, 0x00 },	// U+00F6 (o umlaut)
        { 0x18, 0x18, 0x00, 0x7e, 0x00, 0x18, 0x18, 0x00 },	// U+00F7 (division)
        { 0x00, 0x06, 0x3c, 0x6e, 0x7e, 0x76, 0x3c, 0x60 },	// U+00F8 (o stroke)
        { 0x00, 0xe0, 0x00, 0xcc, 0xcc, 0xcc, 0x7e, 0x00 },	// U+00F9 (u grave)
        { 0x00, 0x1c, 0x00, 0xcc, 0xcc, 0xcc, 0x7e, 0x00 },	// U+00FA (u aigu)
        { 0x78, 0xcc, 0x00, 0xcc, 0xcc, 0xcc, 0x7e, 0x00 },	// U+00FB (u circumflex)
        { 0x00, 0xcc, 0x00, 0xcc, 0xcc, 0xcc, 0x7e, 0x00 },	// U+00FC (u umlaut)
        { 0x00, 0x1c, 0x00, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8 },	// U+00FD (y aigu)
        { 0x00, 0x00, 0x60, 0x7c, 0x66, 0x7c, 0x60, 0x00 },	// U+00FE (thorn)
        { 0x00, 0xcc, 0x00, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8 },	// U+00FF (y umlaut)
        // unicode points U+2580 - U+259F (block elements)
        { 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00 },	// U+2580 (top half)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff },	// U+2581 (box 1/8)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff },	// U+2582 (box 2/8)
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff },	// U+2583 (box 3/8)
        { 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff },	// U+2584 (bottom half)
        { 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff },	// U+2585 (box 5/8)
        { 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },	// U+2586 (box 6/8)
        { 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },	// U+2587 (box 7/8)
        { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },	// U+2588 (solid)
        { 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe },	// U+2589 (box 7/8)
        { 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc },	// U+258A (box 6/8)
        { 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8 },	// U+258B (box 5/8)
        { 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0 },	// U+258C (left half)
        { 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0 },	// U+258D (box 3/8)
        { 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0 },	// U+258E (box 2/8)
        { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 },	// U+258F (box 1/8)
        { 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f },	// U+2590 (right half)
        { 0xaa, 0x00, 0x55, 0x00, 0xaa, 0x00, 0x55, 0x00 },	// U+2591 (25% solid)
        { 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 },	// U+2592 (50% solid)
        { 0xff, 0x55, 0xff, 0xaa, 0xff, 0x55, 0xff, 0xaa },	// U+2593 (75% solid)
        { 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	// U+2594 (box 1/8)
        { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },	// U+2595 (box 1/8)
        { 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0 },	// U+2596 (box bottom left)
        { 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f },	// U+2597 (box bottom right)
        { 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00 },	// U+2598 (box top left)
        { 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff },	// U+2599 (boxes left and bottom)
        { 0xf0, 0xf0, 0xf0, 0xf0, 0x0f, 0x0f, 0x0f, 0x0f },	// U+259A (boxes top-left and bottom right)
        { 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0 },	// U+259B (boxes top and left)
        { 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f },	// U+259C (boxes top and right)
        { 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00 },	// U+259D (box top right)
        { 0x0f, 0x0f, 0x0f, 0x0f, 0xf0, 0xf0, 0xf0, 0xf0 },	// U+259E (boxes top right and bottom left)
        { 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff }	// U+259F (boxes right and bottom)
    };
}

#endif 

