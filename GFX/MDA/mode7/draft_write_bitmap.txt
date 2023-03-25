// draw_bitmap mode 7 design decision is to write character and attribute data 
// vs character or attribute separately draw_bitmap_character and draw_bitmap_attribute as mode 7 specialisations?

// DS:SI points to bitmap - 
// word width
// word height
// word offset in bytes to raw pixel data
// word size in bytes of raw pixel data
// byte depth
// byte mode - DOS screen modes + HGA0, HGA1, HGA2 (for herc, herc+, herc incolor)
// ...
// raw pixel data

#define WIDTH_OFFSET = 0
#define HEIGHT_OFFSET = 

__asm {
          .8086
            
          //calculate ES:DI to point to x,y
          mov		ax, MDA_VIDEO_RAM_SEGMENT
					mov		es, ax					          ; ES:DI will point to x,y screen byte 
					mov		bx, x					            ; load x into bx then perform screen clipping
					cmp   bx, SCREEN_X_MAX          ; compare bx with x maximum boundry
					jge   END						            ; nothing to plot
					mov		ax, y					            ; load y into ax then perform screen clipping
					cmp   ax, SCREEN_Y_MAX          ; compare ax with y maximum boundry
					jge   END                       ; nothing to plot
#ifdef ENABLE_MUL
					mov     cl, BYTES_PER_LINE
					mul     cl						          ; calculate y * 80 i.e. AX * 160 bytes
					mov		  di, ax
#else		
					shl		ax, 1					; on 8086 sp this bitwise multiplication is faster thamul 
					shl		ax, 1					; y * 80 = (y * 16) + (y * 64)
					shl		ax, 1					; 8086 limited to single step shifts
					shl		ax, 1					; y * 16
					mov		di, ax					; copy result
					shl		ax, 1
					shl		ax, 1					; y * 64
					add		di, ax					; di = y * 80
#endif
					shl		bx, 1					; x * 2 as 2 bytes per character cell
					add		di, bx					; di = (y * 80 ) + x
            
          	// DS:SI to point to bitmap and read width and height 
          	mov   	ax, addr_segment
          	mov   	ds, ax
          	mov   	ax, addr_offset
          	mov   	si, ax                 		; DS:SI points to bitmap
          	mov   	bx, ds:[si + BMP_WIDTH]   	; copy of width in BX
          	mov   	cx, ds:[si + BMP_HEIGHT]  	; load CX with height
		add   	si, ds:[si + BMP_DATA]    	; point DS:SI to raw pixel data
			
		// copy pixel data to character bytes rectangle x,y,w,h
          	cld					; increment
L0:		mov 	dx, cx				; copy height into DX
		// draw row
		mov 	cx, bx				; load width
 	  	rep movsw				; bmp data to screen in 16 bit chr:attrib word
		
		mov 	cx, dx				; restore row count
		loop 	L0				; next y
   
			
// character only data would be...
            
          	// copy pixel data to character bytes rectangle x,y,w,h
          	cld					; increment
L0:		mov 	dx, cx				; copy height into DX
		// draw row
		mov 	cx, bx				; load width
L1: 	  	movsb					; bmp data to screen 8 bit character byte
		inc 	di				; skip attribute byte
		loop 	L1				; next x
			
		mov 	cx, dx				; restore row count
		loop 	L0				; next y
   
// attribute data only would be...   
			
		// copy pixel data to character bytes rectangle x,y,w,h
          	cld					; increment
L0:		mov 	dx, cx				; copy height into DX
		// draw row
		mov 	cx, bx				; load width
L1: 	  	inc 	di				; skip character byte
		movsb					; bmp data to screen 8 bit attribute byte	
		loop 	L1				; next x
			
		mov 	cx, dx				; restore row count
		loop 	L0				; next y
   
