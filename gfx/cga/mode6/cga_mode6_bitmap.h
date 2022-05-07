/**
 *
 *  @file      cga_mode6_bitmap.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      26.03.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef CGA_MODE6_BITMAP_H
#define CGA_MODE6_BITMAP_H

#include <stdint.h>

#include "../../../dos/dos_segmented_memory_block.h"
#include "../../../jtl/size_t.h"
#include "../../../jtl/array.h"

#include "../cga_constants.h"
#include "cga_mode6_constants.h"

namespace cga {

	namespace mode6 {

		template<jtl::size_t WORD_WIDTH, jtl::size_t WIDTH, jtl::size_t HEIGHT>
		class bitmap {

			typedef jtl::array<jtl::size_t, PIXELS_PER_BYTE>  offset_table_t;

		public:

			typedef jtl::size_t size_type;
			typedef dos::segmented_memory_block<uint8_t> memory_block_t;

			bitmap() :
				line_size_(WORD_WIDTH * 2 * PIXELS_PER_BYTE),
				size_(line_size_ * HEIGHT),
				pixels_(dos::segmented_memory_block<uint8_t>(size_))
			{}

			/**
			*  @brief  generates an array of 8 pre-shifted bitmaps 
			* 
			* Pre-calculating the right shifted bitmaps saves time when drawing to the screen at the expense of memory
			* Restricting the underlying memory map width to multiples of words also speeds the drawing to screen
			*/
			void extrapolate() {}

			void fill(uint8_t byte) {
				for (size_type y = 0; y < HEIGHT; ++y) {
					for (size_type x = 0; x < (WORD_WIDTH * 2) - 1; ++x) {
						pixels_[x + (y * line_size_)] = byte;
					}
				}
			}

			inline size_type width() {
				return WIDTH;
			}

			inline size_type height() {
				return HEIGHT;
			}

			inline size_type word_width() {
				return WORD_WIDTH;
			}

			inline size_type size() {
				return size_;
			}

			inline memory_block_t& pixels() {
				return pixels_;
			}

		   /**
			*  @brief  draw directly to the mode6 screen video RAM
			*  @param  x - top left corner x coordinate
			*  @param  y - top left corner y coordinate
			*/
			void draw_to_screen(size_type x, size_type y) {
				size_type bmp_segment = pixels_.data_address().memory.segment;
				size_type bmp_select = offset_table_[x & 0x7];
				__asm {
					.8086
					//push    ax
					//push    bx
					//push    cx
					//push    dx
					//push    di
					//push    si
					//push    ds
					//push    es

					//mov		ax, CGA_EVEN_VRAM_SEGMENT	; assume even lines segment
					/*mov     dx, 0; no odd line offset
					mov     di, y           ; load y into DI
    				test	di, 1h			; is y even ?
					jz		EVEN		    ; yes skip
					mov		ax, CGA_ODD_VRAM_SEGMENT    ; otherwise load odd lines segment
					mov     dx, CGA_BYTES_PER_LINE      ; so odd lines need to start a scan line down
			EVEN:	mov		es, ax			; transfer odd/even VRAM segment into ES

					mov		ax, x			; load x into AX 
        			shr		ax, 1			; calculate column byte x / 8
					shr		ax, 1			; 8086 limited to single step shifts
					shr		ax, 1			; 
					and		di, 0FFFEh		; mask out even / odd row bit from y
					shl		di, 1			; 8086 shift left 3 time
					shl		di, 1			; as per binary simplification of y/2 * 80 above
					shl		di, 1			;
					mov		cx, di			; temp result in CX
					shl		cx, 1			; 8086 shift left twice
					shl		cx, 1			;
					add		di, cx          ; add back into DI
					add		di, ax          ; add in column byte, ES:[DI] points to VRAM row and column byte

					mov     ax, bmp_segment ; load the bitmap buffer segment 
					mov     ds, ax          ; into DS
					mov     si, bmp_select  ; DS:[SI] points to 1 of 8 interpolated bitmaps 

					push    dx              ; preserve odd line offset
					mov     dx, CGA_BYTES_PER_LINE  ; each scan line is 80 bytes longand there are 200 scan lines
					sub     dx, byte_width  ; DX as now the offset additive to the next line
					mov     cx, height      ; load bitmap height into CX
					shr     cx, 1           ; halve it 
					push    cx              ; save CX on the stack to use again 
					push    di              ; save DI on the stack to use again 
					mov     ax, word_width  ; load ax with bitmap width in words to save time in loops
					cld 

#ifdef SYNCHRONIZED
                    VSYNC_ASM(V0, V1)
#endif 
			L0:     mov     bx, cx          ; store the scan line counter in BX
					mov     cx, ax          ; load the bitmap words per row into CX
					rep     movsw           ; repeatedly move DS:[SI] word into ES:[DI] and increment DI and SI until CX = 0
					add     di, dx          ; next scan line
					mov     cx, bx          ; reload the scan line count
					loop    L0              ; loop until all even lines copied 

					pop     di              ; retrieve DI
					pop     cx              ; retrieve half height
					pop     bx              ; retrieve line offset
					add     di, bx          ; add line offset to di (even = 0, odd = 80)
					mov     bx, es          ; copy the destination segment
					xor     bx, 200h        ; XOR swap segment (B800h XOR BA00h = 200h)
					mov     es, bx          ; ES:[DI] now points to opposite scan line VRAM
#ifdef SYNCHRONIZED
                VSYNC_ASM(V2, V3)
#endif 
			L1:     mov     bx, cx          ; store the scan line counter in BX
					mov     cx, ax          ; load the bitmap words per row into CX
					rep     movsw           ; repeatedly move DS:[SI] word into ES:[DI] and increment DI and SI until CX = 0
					add     di, dx          ; next scan line
					mov     cx, bx          ; reload the scan line count
					loop    L1              ; loop until all even lines copied
					*/
					//pop     es
					//pop     ds
					//pop     si
					//pop     di
					//pop     dx
					//pop     cx
					//pop     bx
					//pop     ax
				}
			}

		private:

			size_type line_size_;
			size_type size_;
			memory_block_t pixels_;
			offset_table_t  offset_table_;

		};

	}

}

#endif