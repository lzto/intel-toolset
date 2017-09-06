/*
 * LBR Library Header
 * 2015 Tong Zhang <ztong@vt.edu>
 * tested on Intel i7-4790(Haswell), Linux-3.19.4-gentoo (64bit)
 * need msr kernel module
 */

#ifndef _LBR_H_
#define _LBR_H_

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sched.h>

/*
 * Register Offsets
 */

#define MSR_LBR_SELECT (0x1C8)

#define MSR_LASTBRANCH_TOS (0x1C9)

#define MSR_LASTBRANCH_TOS_MASK (0x0F)

#define IA32_DEBUGCTL (0x1D9)

#define MSR_LASTBRANCH_0_FROM_IP (0x680)
#define MSR_LASTBRANCH_1_FROM_IP (0x681)
#define MSR_LASTBRANCH_2_FROM_IP (0x682)
#define MSR_LASTBRANCH_3_FROM_IP (0x683)
#define MSR_LASTBRANCH_4_FROM_IP (0x684)
#define MSR_LASTBRANCH_5_FROM_IP (0x685)
#define MSR_LASTBRANCH_6_FROM_IP (0x686)
#define MSR_LASTBRANCH_7_FROM_IP (0x687)
#define MSR_LASTBRANCH_8_FROM_IP (0x688)
#define MSR_LASTBRANCH_9_FROM_IP (0x689)
#define MSR_LASTBRANCH_10_FROM_IP (0x68A)
#define MSR_LASTBRANCH_11_FROM_IP (0x68B)
#define MSR_LASTBRANCH_12_FROM_IP (0x68C)
#define MSR_LASTBRANCH_13_FROM_IP (0x68D)
#define MSR_LASTBRANCH_14_FROM_IP (0x68E)
#define MSR_LASTBRANCH_15_FROM_IP (0x68F)
#define MSR_LASTBRANCH_16_FROM_IP (0x690)
#define MSR_LASTBRANCH_17_FROM_IP (0x691)
#define MSR_LASTBRANCH_18_FROM_IP (0x692)
#define MSR_LASTBRANCH_19_FROM_IP (0x693)
#define MSR_LASTBRANCH_20_FROM_IP (0x694)
#define MSR_LASTBRANCH_21_FROM_IP (0x695)
#define MSR_LASTBRANCH_22_FROM_IP (0x696)
#define MSR_LASTBRANCH_23_FROM_IP (0x697)
#define MSR_LASTBRANCH_24_FROM_IP (0x698)
#define MSR_LASTBRANCH_25_FROM_IP (0x699)
#define MSR_LASTBRANCH_26_FROM_IP (0x69A)
#define MSR_LASTBRANCH_27_FROM_IP (0x69B)
#define MSR_LASTBRANCH_28_FROM_IP (0x69C)
#define MSR_LASTBRANCH_29_FROM_IP (0x69D)
#define MSR_LASTBRANCH_30_FROM_IP (0x69E)
#define MSR_LASTBRANCH_31_FROM_IP (0x69F)

#define MSR_LASTBRANCH_0_TO_IP (0x6C0)
#define MSR_LASTBRANCH_1_TO_IP (0x6C1)
#define MSR_LASTBRANCH_2_TO_IP (0x6C2)
#define MSR_LASTBRANCH_3_TO_IP (0x6C3)
#define MSR_LASTBRANCH_4_TO_IP (0x6C4)
#define MSR_LASTBRANCH_5_TO_IP (0x6C5)
#define MSR_LASTBRANCH_6_TO_IP (0x6C6)
#define MSR_LASTBRANCH_7_TO_IP (0x6C7)
#define MSR_LASTBRANCH_8_TO_IP (0x6C8)
#define MSR_LASTBRANCH_9_TO_IP (0x6C9)
#define MSR_LASTBRANCH_10_TO_IP (0x6CA)
#define MSR_LASTBRANCH_11_TO_IP (0x6CB)
#define MSR_LASTBRANCH_12_TO_IP (0x6CC)
#define MSR_LASTBRANCH_13_TO_IP (0x6CD)
#define MSR_LASTBRANCH_14_TO_IP (0x6CE)
#define MSR_LASTBRANCH_15_TO_IP (0x6CF)
#define MSR_LASTBRANCH_16_TO_IP (0x6D0)
#define MSR_LASTBRANCH_17_TO_IP (0x6D1)
#define MSR_LASTBRANCH_18_TO_IP (0x6D2)
#define MSR_LASTBRANCH_19_TO_IP (0x6D3)
#define MSR_LASTBRANCH_20_TO_IP (0x6D4)
#define MSR_LASTBRANCH_21_TO_IP (0x6D5)
#define MSR_LASTBRANCH_22_TO_IP (0x6D6)
#define MSR_LASTBRANCH_23_TO_IP (0x6D7)
#define MSR_LASTBRANCH_24_TO_IP (0x6D8)
#define MSR_LASTBRANCH_25_TO_IP (0x6D9)
#define MSR_LASTBRANCH_26_TO_IP (0x6DA)
#define MSR_LASTBRANCH_27_TO_IP (0x6DB)
#define MSR_LASTBRANCH_28_TO_IP (0x6DC)
#define MSR_LASTBRANCH_29_TO_IP (0x6DD)
#define MSR_LASTBRANCH_30_TO_IP (0x6DE)
#define MSR_LASTBRANCH_31_TO_IP (0x6DF)

#define MSR_LBR_INFO_0 (0xDC0)
#define MSR_LBR_INFO_1 (0xDC1)
#define MSR_LBR_INFO_2 (0xDC2)
#define MSR_LBR_INFO_3 (0xDC3)
#define MSR_LBR_INFO_4 (0xDC4)
#define MSR_LBR_INFO_5 (0xDC5)
#define MSR_LBR_INFO_6 (0xDC6)
#define MSR_LBR_INFO_7 (0xDC7)
#define MSR_LBR_INFO_8 (0xDC8)
#define MSR_LBR_INFO_9 (0xDC9)
#define MSR_LBR_INFO_10 (0xDCA)
#define MSR_LBR_INFO_11 (0xDCB)
#define MSR_LBR_INFO_12 (0xDCC)
#define MSR_LBR_INFO_13 (0xDCD)
#define MSR_LBR_INFO_14 (0xDCE)
#define MSR_LBR_INFO_15 (0xDCF)
#define MSR_LBR_INFO_16 (0xDD0)
#define MSR_LBR_INFO_17 (0xDD1)
#define MSR_LBR_INFO_18 (0xDD2)
#define MSR_LBR_INFO_19 (0xDD3)
#define MSR_LBR_INFO_20 (0xDD4)
#define MSR_LBR_INFO_21 (0xDD5)
#define MSR_LBR_INFO_22 (0xDD6)
#define MSR_LBR_INFO_23 (0xDD7)
#define MSR_LBR_INFO_24 (0xDD8)
#define MSR_LBR_INFO_25 (0xDD9)
#define MSR_LBR_INFO_26 (0xDDA)
#define MSR_LBR_INFO_27 (0xDDB)
#define MSR_LBR_INFO_28 (0xDDC)
#define MSR_LBR_INFO_29 (0xDDD)
#define MSR_LBR_INFO_30 (0xDDE)
#define MSR_LBR_INFO_31 (0xDDF)

/*
 * Refer 17.4.8.1 LBR Stack and Intel 64 Processors
 */
#define IA32_DEBUGCTL_LBR_MASK (0x00000001)
#define IA32_DEBUGCTL_FRZ_LBRS_ON_PMI_MASK (0x00000080)

#define MSR_LBR_SELECT_CPL_EQ_0_MASK (1<<0)
#define MSR_LBR_SELECT_CPL_NEQ_0_MASK (1<<1)
#define MSR_LBR_SELECT_JCC_MASK (1<<2)
#define MSR_LBR_SELECT_NEAR_REL_CALL_MASK (1<<3)
#define MSR_LBR_SELECT_NEAR_IND_CALL_MASK (1<<4)
#define MSR_LBR_SELECT_NEAR_RET_MASK (1<<5)
#define MSR_LBR_SELECT_NEAR_IND_JMP_MASK (1<<6)
#define MSR_LBR_SELECT_NEAR_REL_JMP_MASK (1<<7)
#define MSR_LBR_SELECT_FAR_BRANCH_MASK (1<<8)


/*
 * Refer 17.8.1 LBR Stack Enhancement
 */
#define MSR_LBR_CYCLE (0x000000000000FFFF)
#define MSR_LBR_DATA_MASK (0x0000FFFFFFFFFFFF)
#define MSR_LBR_SIGN_EXT_MASK (0x1FFF000000000000)
#define MSR_LBR_TSX_ABORT_MASK (0x2000000000000000)
#define MSR_LBR_IN_TSX_MASK (0x4000000000000000)
#define MSR_LBR_MISPRED_MASK (0x8000000000000000)

/*
 * for Haswell, there are 16 pairs of LBR Message
 */

#define LBR_STACK_SIZE (32)

/*
 * MSR should be accessed from ring0
 * use kernel facility to access msr
 */

#define MSR_DEV_FILE "/dev/cpu/%d/msr"

/*
 * support up to N CPUS
 */

#define MAX_CPU 16


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct _lbr_stack
{
	unsigned long msr_lastbranch_from_ip[32];
	unsigned long msr_lastbranch_to_ip[32];
    unsigned long msr_lbr_info[32];
} lbr_stack;

extern int msrfd[];

/*
 * start LBR facility for cpuid
 */
int start_lbr(int cpuid);

/*
 * stop LBR facility for cpuid
 * inline? stop_lbr to minimize impact of unrelated branch
 */
 #define stop_lbr(cpuid) \
 { \
 	int msr_fd = msrfd[cpuid]; \
	unsigned long ia32_debugctl; \
	pread(msr_fd,&ia32_debugctl,sizeof(unsigned long),IA32_DEBUGCTL); \
	ia32_debugctl &= ~IA32_DEBUGCTL_LBR_MASK; \
	ia32_debugctl &= ~IA32_DEBUGCTL_FRZ_LBRS_ON_PMI_MASK; \
	pwrite(msr_fd,&ia32_debugctl,sizeof(unsigned long),IA32_DEBUGCTL); \
}

/*
 * clean LBR facility for cpuid
 */
void cleanup_lbr(int cpuid);

/*
 * dump LBR info
 */

void dump_lbr(int cpuid, lbr_stack* lbrstack);

/*
 * Print LBR info
 */

void print_lbr(lbr_stack* lbrstack);

/*
 * inteprete LBR info
 */
void inteprete_lbr_info(lbr_stack* lbrstack);


#ifdef __cplusplus
}
#endif


#endif//_LBR_H_
