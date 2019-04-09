/* ------------------------------------------------------------------------ */
/*  HOS-V4  kernel configuration                                            */
/*    kernel object ID definition                                           */
/*                                                                          */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__kernel_cfg_h__
#define __HOS_V4__kernel_cfg_h__



/* time tic */
#define TIC_NUME		1
#define TIC_DENO		1


/* task ID definetion */
#define tskID_Z		1
#define tskID_CHK_BTN		2
#define tskID_BTN_HDL		3

#define TMAX_TSKID		8


/* semaphore ID definetion */
#define SEMID_SCI		1

#define TMAX_SEMID		1



#endif	/* __HOS_V4__kernel_cfg_h__ */


/* ------------------------------------------------------------------------ */
/*  End of file                                                             */
/* ------------------------------------------------------------------------ */
