#include "bg_vehicles_mp.h"
#include <clientscript/scr_const.h>

const unsigned __int16 *s_seatTags[11] =
{
    &scr_const.tag_gunner1,
    &scr_const.tag_gunner2,
    &scr_const.tag_gunner3,
    &scr_const.tag_gunner4,
    &scr_const.tag_passenger1,
    &scr_const.tag_passenger2,
    &scr_const.tag_passenger3,
    &scr_const.tag_passenger4,
    &scr_const.tag_passenger5,
    &scr_const.tag_passenger6
};


unsigned __int16 __cdecl BG_VehiclesGetSlotTagName(int seatIndex)
{
    return *s_seatTags[seatIndex];
}

