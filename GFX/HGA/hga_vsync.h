/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_VSYCN_H
#define HGA_VSYCN_H

namespace hga {

	/**
     *  @brief Synchronise to the start of a vertical retrace
     *  @details Use the CRTC status port to wait until the start of new vertical sync.
     *  This is a read only register - MDA only two bits of the value read from this port are defined but
     *  for a Hercules adapter a third bit (7) is available to read for vertical synchronization.
     *  @note If bit 7 vsync is 0 then vsync is active and 1 when it is off
     *          03BA
     *          ?7?6?5?4?3?2?1?0?
     *          ? ? ? ? ? ? ? ? ?
     *          ?????????????????  bits
     *           ? ? ? ? ? ? ? ???? 0:  H-Sync          0 = off     1 = on
     *           ? ? ? ? ? ? ?????? 1:
     *           ? ? ? ? ? ???????? 2:
     *           ? ? ? ? ?????????? 3:  Current pixel   0 = off     1 = on
     *           ? ? ? ???????????? 4:  0?          1?               1?
     *           ? ? ?????????????? 5:  0??Hercules 0??Hercules Plus 0??Hercules InColor
     *           ? ???????????????? 6:  0?          0?               1?
     *           ?????????????????? 7:  V-Sync          0 = *on*    1 = off
     *
     */
    void vsync() {
        __asm {
            .8086
            mov     dx, CRTC_STATUS_PORT    ; read port 3BAh
VWAIT0:     in      al, dx                  ; read status
            test    al, 10000000b           ; is bit 7 clear ? (in a vertical retrace interval)
            jz      VWAIT0                  ; yes, keep waiting
VWAIT1:     in      al, dx                  ; read status again
            test    al, 10000000b           ; is bit 7 clear ? (just started a vertical retrace interval)
            jz      VWAIT1                  ; no, keep waiting
        }
    }

}

#endif