/**
 *
 *  @brief     IBM Codepage 437 PC/XT/AT graphics characters     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      27.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef SYSTEM_GRAPHICS_CHARACTERS_H
#define SYSTEM_GRAPHICS_CHARACTERS_H

#define	LIGHT_SHADE		176
#define	MEDIUM_SHADE	177
#define	DARK_SHADE		178

/**
 * graphics characters for border of a sector
 * Peter Norton's Assembly Language Book for the IBM PC pg.170
 */
#define VERTICL_BAR		0xBA
#define HORIZONTAL_BAR	0xCD
#define UPPER_LEFT		OxC9
#define UPPER_RIGHT		0xBB
#define LOWER_LEFT		0xC8
#define LOWER_RIGHT		0xBC
#define TOP_T_BAR		0xCB
#define BOTTOM_T_BAR	0xCA
#define TOP_TICK		0xD1
#define BOTTOM_TICK		0xCF

};

#endif