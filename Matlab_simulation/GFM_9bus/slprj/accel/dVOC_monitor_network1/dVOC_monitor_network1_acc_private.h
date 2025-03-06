#ifndef RTW_HEADER_dVOC_monitor_network1_acc_private_h_
#define RTW_HEADER_dVOC_monitor_network1_acc_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"
#include "dVOC_monitor_network1_acc.h"
#include "dVOC_monitor_network1_acc_types.h"
#if !defined(ss_VALIDATE_MEMORY)
#define ss_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
    ssSetErrorStatus(S, RT_MEMORY_ALLOCATION_ERROR);\
    }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((ptr));\
    (ptr) = (NULL);\
    }
#else
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((void *)(ptr));\
    (ptr) = (NULL);\
    }
#endif
#endif
#ifndef __RTW_UTFREE__
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
extern void rt_invd5x5_snf ( const real_T u [ 25 ] , real_T y [ 25 ] ) ;
boolean_T dVOC_monitor_network1_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T
tMinusDelay , real_T * * uBufPtr , boolean_T isfixedbuf , boolean_T
istransportdelay , int_T * maxNewBufSzPtr ) ; real_T
dVOC_monitor_network1_acc_rt_VTDelayfindtDInterpolate ( real_T x , real_T *
uBuf , int_T bufSz , int_T head , int_T tail , int_T * pLast , real_T t ,
real_T tStart , boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput
, real_T initOutput , real_T * appliedDelay ) ; extern real_T look1_pbinlxpw
( real_T u0 , const real_T bp0 [ ] , const real_T table [ ] , uint32_T
prevIndex [ ] , uint32_T maxIndex ) ; void
dVOC_monitor_network1_Subsystempi2delay_Init ( SimStruct * S ,
B_Subsystempi2delay_dVOC_monitor_network1_T * localB ,
P_Subsystempi2delay_dVOC_monitor_network1_T * localP ) ; void
dVOC_monitor_network1_Subsystempi2delay_Disable ( SimStruct * S ,
DW_Subsystempi2delay_dVOC_monitor_network1_T * localDW ) ; void
dVOC_monitor_network1_Subsystempi2delay ( SimStruct * S , uint8_T rtu_Enable
, const real_T rtu_alpha_beta [ 2 ] , real_T rtu_wt ,
B_Subsystempi2delay_dVOC_monitor_network1_T * localB ,
DW_Subsystempi2delay_dVOC_monitor_network1_T * localDW ) ; void
dVOC_monitor_network1_Subsystem1_Init ( SimStruct * S ,
B_Subsystem1_dVOC_monitor_network1_T * localB ,
P_Subsystem1_dVOC_monitor_network1_T * localP ) ; void
dVOC_monitor_network1_Subsystem1_Disable ( SimStruct * S ,
DW_Subsystem1_dVOC_monitor_network1_T * localDW ) ; void
dVOC_monitor_network1_Subsystem1 ( SimStruct * S , uint8_T rtu_Enable , const
real_T rtu_alpha_beta [ 2 ] , real_T rtu_wt ,
B_Subsystem1_dVOC_monitor_network1_T * localB ,
DW_Subsystem1_dVOC_monitor_network1_T * localDW ) ; void
dVOC_monitor_network1_Subsystempi2delay_c_Init ( SimStruct * S ,
B_Subsystempi2delay_dVOC_monitor_network1_b_T * localB ,
P_Subsystempi2delay_dVOC_monitor_network1_g_T * localP ) ; void
dVOC_monitor_network1_Subsystempi2delay_p_Disable ( SimStruct * S ,
DW_Subsystempi2delay_dVOC_monitor_network1_d_T * localDW ) ; void
dVOC_monitor_network1_Subsystempi2delay_o ( SimStruct * S , uint8_T
rtu_Enable , real_T rtu_dq , real_T rtu_dq_h , real_T rtu_wt ,
B_Subsystempi2delay_dVOC_monitor_network1_b_T * localB ,
DW_Subsystempi2delay_dVOC_monitor_network1_d_T * localDW ) ; void
dVOC_monitor_network1_Subsystem1_m_Init ( SimStruct * S ,
B_Subsystem1_dVOC_monitor_network1_m_T * localB ,
P_Subsystem1_dVOC_monitor_network1_a_T * localP ) ; void
dVOC_monitor_network1_Subsystem1_d_Disable ( SimStruct * S ,
DW_Subsystem1_dVOC_monitor_network1_k_T * localDW ) ; void
dVOC_monitor_network1_Subsystem1_b ( SimStruct * S , uint8_T rtu_Enable ,
real_T rtu_dq , real_T rtu_dq_m , real_T rtu_wt ,
B_Subsystem1_dVOC_monitor_network1_m_T * localB ,
DW_Subsystem1_dVOC_monitor_network1_k_T * localDW ) ; void
dVOC_monitor_network1_AutomaticGainControl_Init ( SimStruct * S ,
B_AutomaticGainControl_dVOC_monitor_network1_T * localB ,
P_AutomaticGainControl_dVOC_monitor_network1_T * localP ,
X_AutomaticGainControl_dVOC_monitor_network1_T * localX ) ; void
dVOC_monitor_network1_AutomaticGainControl_Deriv ( SimStruct * S ,
B_AutomaticGainControl_dVOC_monitor_network1_T * localB ,
DW_AutomaticGainControl_dVOC_monitor_network1_T * localDW ,
P_AutomaticGainControl_dVOC_monitor_network1_T * localP ,
XDot_AutomaticGainControl_dVOC_monitor_network1_T * localXdot ) ; void
dVOC_monitor_network1_AutomaticGainControl_ZC ( SimStruct * S ,
B_AutomaticGainControl_dVOC_monitor_network1_T * localB ,
DW_AutomaticGainControl_dVOC_monitor_network1_T * localDW ,
P_AutomaticGainControl_dVOC_monitor_network1_T * localP ,
ZCV_AutomaticGainControl_dVOC_monitor_network1_T * localZCSV ) ; void
dVOC_monitor_network1_AutomaticGainControl_Disable ( SimStruct * S ,
DW_AutomaticGainControl_dVOC_monitor_network1_T * localDW ) ; void
dVOC_monitor_network1_AutomaticGainControl_Update ( SimStruct * S ,
B_AutomaticGainControl_dVOC_monitor_network1_T * localB ,
DW_AutomaticGainControl_dVOC_monitor_network1_T * localDW ,
P_AutomaticGainControl_dVOC_monitor_network1_T * localP ,
X_AutomaticGainControl_dVOC_monitor_network1_T * localX ) ; void
dVOC_monitor_network1_AutomaticGainControl ( SimStruct * S , real_T
rtu_Enable , real_T rtu_Freq , real_T rtu_wt , const real_T rtu_Vabc [ 3 ] ,
B_AutomaticGainControl_dVOC_monitor_network1_T * localB ,
DW_AutomaticGainControl_dVOC_monitor_network1_T * localDW ,
P_AutomaticGainControl_dVOC_monitor_network1_T * localP ,
X_AutomaticGainControl_dVOC_monitor_network1_T * localX ,
XDis_AutomaticGainControl_dVOC_monitor_network1_T * localXdis ) ; void
dVOC_monitor_network1_AutomaticGainControlTID4 ( SimStruct * S ,
B_AutomaticGainControl_dVOC_monitor_network1_T * localB ,
DW_AutomaticGainControl_dVOC_monitor_network1_T * localDW ,
P_AutomaticGainControl_dVOC_monitor_network1_T * localP ) ; void
dVOC_monitor_network1_Subsystempi2delay_Term ( SimStruct * const S ) ; void
dVOC_monitor_network1_Subsystem1_Term ( SimStruct * const S ) ; void
dVOC_monitor_network1_Subsystempi2delay_b_Term ( SimStruct * const S ) ; void
dVOC_monitor_network1_Subsystem1_e_Term ( SimStruct * const S ) ; void
dVOC_monitor_network1_AutomaticGainControl_Term ( SimStruct * const S ) ;
#endif
