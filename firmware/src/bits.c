#include"r232lc.h"

/**
 *	Fuses for the state of the microntroller through out
 *	the life time.
 */
FUSES =
{
	.low = LFUSE_DEFAULT,
	.high = HFUSE_DEFAULT,
};

/**
 *	Lock
 */
unsigned char __lock __attribute__((section (".lock"))) =
        (LB_MODE_1 & BLB0_MODE_3 & BLB1_MODE_4);


