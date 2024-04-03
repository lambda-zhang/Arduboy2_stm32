#pragma once

enum Dice {
    EMPTY = 0,
    WHITE_1,
    WHITE_2,
    WHITE_3,
    WHITE_4,
    WHITE_5,
    WHITE_6,
    WHITE_COL_2, // First phase of collapsing
    WHITE_COL_3,
    WHITE_COL_4,
    WHITE_COL_5,
    WHITE_COL_6, // Completely collapsed
    BLACK_1,
    BLACK_2,
    BLACK_3,
    BLACK_4,
    BLACK_5,
    BLACK_6,
    BLACK_COL_2, // First phase of collapsing
    BLACK_COL_3,
    BLACK_COL_4,
    BLACK_COL_5,
    BLACK_COL_6, // Completely collapsed
    INVALID
};

Dice dice_prev_stack(Dice item)
{
    switch (item)
    {
        case EMPTY:
        case WHITE_6:
        case BLACK_6:
        case WHITE_COL_2:
        case WHITE_COL_3:
        case WHITE_COL_4:
        case WHITE_COL_5:
        case WHITE_COL_6:
        case BLACK_COL_2:
        case BLACK_COL_3:
        case BLACK_COL_4:
        case BLACK_COL_5:
        case BLACK_COL_6:
            return INVALID;
        default:
#ifndef STM32F103xB
            return item + 1;
#else
            return (Dice)(item + 1);
#endif /* STM32F103xB */
    }
}

Dice dice_end_stack(Dice item)
{
    switch (item)
    {
        case WHITE_COL_2:
        case WHITE_COL_3:
        case WHITE_COL_4:
        case WHITE_COL_5:
        case WHITE_COL_6:
        case BLACK_COL_2:
        case BLACK_COL_3:
        case BLACK_COL_4:
        case BLACK_COL_5:
        case BLACK_COL_6:
#ifndef STM32F103xB
            return item - 4;
#else
            return (Dice)(item - 4);
#endif /* STM32F103xB */
        case WHITE_1:
        case BLACK_1:
#ifndef STM32F103xB
            return item + 1;
#else
            return (Dice)(item + 1);
#endif /* STM32F103xB */
        default:
            return INVALID;
    }
}

/* Somewhat unsafe operation; confirm with dice_end_stack first */
Dice dice_get_end_version(Dice item)
{
#ifndef STM32F103xB
    return item + 5;
#else
    return (Dice)(item + 5);
#endif /* STM32F103xB */
}
