/* ------------------------------------------------------------------------ */
/*  HOS-V4  kernel configuration                                            */
/*    kernel object create and initialize                                   */
/*                                                                          */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "kernel_id.h"

#include "sample.h"
#include "MinSys3069.h"



/* ------------------------------------------ */
/*                 idle stack                 */
/* ------------------------------------------ */

VP         mknl_idl_stkblk[((128) + sizeof(VP) - 1) / sizeof(VP)];	/* idle stack block*/
const VP   mknl_idl_stk   = (VP)(mknl_idl_stkblk);	/* idle stack */
const SIZE mknl_idl_stksz = (SIZE)sizeof(mknl_idl_stkblk);	/* idle stack size */



/* ------------------------------------------ */
/*           create ready queue               */
/* ------------------------------------------ */

T_MKNL_QUE mknl_rdq_tbl[8];
const INT  mknl_rdq_cnt = 8;



/* ------------------------------------------ */
/*                kernel heap                 */
/* ------------------------------------------ */

VP kernel_heap_mem[((32768) + sizeof(VP) - 1) / sizeof(VP)];	/* kernel heap */



/* ------------------------------------------ */
/*               set time tic                 */
/* ------------------------------------------ */

const UW kernel_tic_deno = TIC_DENO;
const UW kernel_tic_div  = TIC_NUME / TIC_DENO;
const UW kernel_tic_mod  = TIC_NUME % TIC_DENO;



/* ------------------------------------------ */
/*          create task objects               */
/* ------------------------------------------ */

/* stack area */
static VP kernel_tsk1_stk[((128) + sizeof(VP) - 1) / sizeof(VP)];
static VP kernel_tsk2_stk[((256) + sizeof(VP) - 1) / sizeof(VP)];
static VP kernel_tsk3_stk[((256) + sizeof(VP) - 1) / sizeof(VP)];

/* task control block for rom area */
const T_KERNEL_TCB_ROM kernel_tcb_rom[3] =
	{
		{(ATR)(TA_HLNG | TA_ACT), (VP_INT)(1), (FP)(idletask), (PRI)(8), (SIZE)(128), (VP)kernel_tsk1_stk},
		{(ATR)(TA_HLNG), (VP_INT)(1), (FP)(taskA), (PRI)(1), (SIZE)(256), (VP)kernel_tsk2_stk},
		{(ATR)(TA_HLNG), (VP_INT)(1), (FP)(taskB), (PRI)(2), (SIZE)(256), (VP)kernel_tsk3_stk},
	};

/* task control block for ram area */
T_KERNEL_TCB_RAM kernel_tcb_ram[3];

/* task control block table */
T_KERNEL_TCB_RAM *kernel_tcb_ram_tbl[8] =
	{
		&kernel_tcb_ram[0],
		&kernel_tcb_ram[1],
		&kernel_tcb_ram[2],
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
	};

/* task control block count */
const INT kernel_tcb_cnt = 8;



/* ------------------------------------------ */
/*         create semaphore objects           */
/* ------------------------------------------ */

/* semaphore control block count */
const INT kernel_semcb_cnt = 0;



/* ------------------------------------------ */
/*        create event flag objects           */
/* ------------------------------------------ */

/* event flag control block count */
const INT kernel_flgcb_cnt = 0;



/* ------------------------------------------ */
/*        create data queue objects           */
/* ------------------------------------------ */

/* data queue control block count */
const INT kernel_dtqcb_cnt = 0;



/* ------------------------------------------ */
/*         create mail box objects            */
/* ------------------------------------------ */

/* mail box control block count */
const INT kernel_mbxcb_cnt = 0;



/* ------------------------------------------ */
/*      create message buffer objects         */
/* ------------------------------------------ */

/* mail box control block count */
const INT kernel_mbfcb_cnt = 0;



/* ------------------------------------------ */
/*   create fixed size memory-pool objects    */
/* ------------------------------------------ */

/* fixed size memory-pool area */
static VP kernel_mpf1_heap[2][(((256) + sizeof(VP) - 1) / sizeof(VP))];

/* fixed size memory-pool control block for rom area */
const T_KERNEL_MPFCB_ROM kernel_mpfcb_rom[1] =
	{
		{(ATR)(TA_TPRI), (UINT)(2), (SIZE)sizeof(kernel_mpf1_heap[0]), (VP)kernel_mpf1_heap},
	};

/* fixed size memory-pool control block for ram area */
T_KERNEL_MPFCB_RAM kernel_mpfcb_ram[1];

/* fixed size memory-pool control block table */
T_KERNEL_MPFCB_RAM *kernel_mpfcb_ram_tbl[1] =
	{
		&kernel_mpfcb_ram[0],
	};

/* fixed size memory-pool control block count */
const INT kernel_mpfcb_cnt = 1;



/* ------------------------------------------ */
/*  create variable size memory-pool objects  */
/* ------------------------------------------ */

/* variable size memory-pool control block count */
const INT kernel_mplcb_cnt = 0;



/* ------------------------------------------ */
/*       create cyclic handler objects        */
/* ------------------------------------------ */

/* cyclic handler control block count */
const INT kernel_cyccb_cnt = 0;



/* ------------------------------------------ */
/*       create alarm handler objects         */
/* ------------------------------------------ */

/* alarm handler control block count */
const INT kernel_almcb_cnt = 0;



/* ------------------------------------------ */
/*        interrupt control objects           */
/* ------------------------------------------ */

/* interrupt control */
T_KERNEL_INTCB kernel_intcb_tbl[257];		/* interrupt control block table */
const INT      kernel_intcb_cnt = 257;		/* interrupt control block count */
const INTNO    kernel_min_intno = 0;		/* minimum intrrupt number */

/* interrupt service routine control */
const INT      kernel_isrcb_cnt = 0;		/* ISR control block count */



/* ------------------------------------------ */
/*    CPU exception handler control objects   */
/* ------------------------------------------ */

/* interrupt control */
T_KERNEL_EXCCB kernel_exccb_tbl[1];		/* CPU exception handler control block table */
const INT      kernel_exccb_cnt = 1;		/* CPU exception handler control block count */
const EXCNO    kernel_min_excno = 0;		/* minimum CPU exception handler number */



/* ------------------------------------------ */
/*          initialize functions              */
/* ------------------------------------------ */

/* object initialize */
void kernel_cfg_init(void)
{
	int i;
	
	
	/* initialize task control block */
	for ( i = 0; i < 3; i++ )
	{
		kernel_tcb_ram[i].tcb_rom = &kernel_tcb_rom[i];
	}
	
	
	/* initialize fixed size memory-pool control block */
	for ( i = 0; i < 1; i++ )
	{
		kernel_mpfcb_ram[i].mpfcb_rom = &kernel_mpfcb_rom[i];
	}

	/* initialize interrupt table */
	kernel_intcb_tbl[24].exinf = (VP_INT)(0);
	kernel_intcb_tbl[24].isr   = (FP)(SystemTimerHandler);
	kernel_intcb_tbl[57].exinf = (VP_INT)(0);
	kernel_intcb_tbl[57].isr   = (FP)(SCI1_RXI_handler);
	kernel_intcb_tbl[56].exinf = (VP_INT)(0);
	kernel_intcb_tbl[56].isr   = (FP)(SCI1_ERI_handler);
}

/* start up */
void kernel_cfg_start(void)
{
	kernel_ini_mem(kernel_heap_mem, sizeof(kernel_heap_mem));		/* initialize kernel heap */

	kernel_ini_tsk();		/* initialize task */
	kernel_ini_mpf();		/* initialize fixed size memory-pool */

	/* call initialize routine*/
	((FP)(initSystemTimer))((VP_INT)(0));
	((FP)(OnHosStart))((VP_INT)(0));
}


/* ------------------------------------------------------------------------ */
/*  End of file                                                             */
/* ------------------------------------------------------------------------ */
