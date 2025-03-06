#include "dVOC_monitor_network1_acc.h"
#include "dVOC_monitor_network1_acc_types.h"
#include "rtwtypes.h"
#include "dVOC_monitor_network1_acc_private.h"
#include "mwmathutil.h"
#include <string.h>
#include "rt_look.h"
#include "rt_look1d.h"
#include "multiword_types.h"
#include "simstruc_types.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T dVOC_monitor_network1_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T
tMinusDelay , real_T * * uBufPtr , boolean_T isfixedbuf , boolean_T
istransportdelay , int_T * maxNewBufSzPtr ) { int_T testIdx ; int_T tail = *
tailPtr ; int_T bufSz = * bufSzPtr ; real_T * tBuf = * uBufPtr + bufSz ;
real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if ( istransportdelay ) {
numBuffer = 3 ; xBuf = * uBufPtr + 2 * bufSz ; } testIdx = ( tail < ( bufSz -
1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] ) && !
isfixedbuf ) { int_T j ; real_T * tempT ; real_T * tempU ; real_T * tempX = (
NULL ) ; real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024 ; if (
newBufSz > * maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU = (
real_T * ) utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if ( tempU
== ( NULL ) ) { return ( false ) ; } tempT = tempU + newBufSz ; if (
istransportdelay ) tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j
++ ) { tempT [ j - tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if
( istransportdelay ) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j <
tail ; j ++ ) { tempT [ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz -
tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j + bufSz - tail ] =
xBuf [ j ] ; } if ( * lastPtr > tail ) { * lastPtr -= tail ; } else { *
lastPtr += ( bufSz - tail ) ; } * tailPtr = 0 ; * headPtr = bufSz ; utFree (
uBuf ) ; * bufSzPtr = newBufSz ; * uBufPtr = tempU ; } else { * tailPtr =
testIdx ; } return ( true ) ; } real_T
dVOC_monitor_network1_acc_rt_VTDelayfindtDInterpolate ( real_T x , real_T *
uBuf , int_T bufSz , int_T head , int_T tail , int_T * pLast , real_T t ,
real_T tStart , boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput
, real_T initOutput , real_T * appliedDelay ) { int_T n , k ; real_T f ;
int_T kp1 ; real_T tminustD , tL , tR , uD , uL , uR , fU ; real_T * tBuf =
uBuf + bufSz ; real_T * xBuf = uBuf + 2 * bufSz ; if (
minorStepAndTAtLastMajorOutput ) { if ( * pLast == head ) { * pLast = ( *
pLast == 0 ) ? bufSz - 1 : * pLast - 1 ; } head = ( head == 0 ) ? bufSz - 1 :
head - 1 ; } if ( x <= 1 ) { return initOutput ; } k = * pLast ; n = 0 ; for
( ; ; ) { n ++ ; if ( n > bufSz ) break ; if ( x - xBuf [ k ] > 1.0 ) { if (
k == head ) { int_T km1 ; f = ( x - 1.0 - xBuf [ k ] ) / ( x - xBuf [ k ] ) ;
tminustD = ( 1.0 - f ) * tBuf [ k ] + f * t ; km1 = k - 1 ; if ( km1 < 0 )
km1 = bufSz - 1 ; tL = tBuf [ km1 ] ; tR = tBuf [ k ] ; uL = uBuf [ km1 ] ;
uR = uBuf [ k ] ; break ; } kp1 = k + 1 ; if ( kp1 == bufSz ) kp1 = 0 ; if (
x - xBuf [ kp1 ] <= 1.0 ) { f = ( x - 1.0 - xBuf [ k ] ) / ( xBuf [ kp1 ] -
xBuf [ k ] ) ; tL = tBuf [ k ] ; tR = tBuf [ kp1 ] ; uL = uBuf [ k ] ; uR =
uBuf [ kp1 ] ; tminustD = ( 1.0 - f ) * tL + f * tR ; break ; } k = kp1 ; }
else { if ( k == tail ) { f = ( x - 1.0 ) / xBuf [ k ] ; if ( discrete ) {
return ( uBuf [ tail ] ) ; } kp1 = k + 1 ; if ( kp1 == bufSz ) kp1 = 0 ;
tminustD = ( 1 - f ) * tStart + f * tBuf [ k ] ; tL = tBuf [ k ] ; tR = tBuf
[ kp1 ] ; uL = uBuf [ k ] ; uR = uBuf [ kp1 ] ; break ; } k = k - 1 ; if ( k
< 0 ) k = bufSz - 1 ; } } * pLast = k ; if ( tR == tL ) { fU = 1.0 ; } else {
fU = ( tminustD - tL ) / ( tR - tL ) ; } if ( discrete ) { uD = ( fU > ( 1.0
- fU ) ) ? uR : uL ; } else { uD = ( 1.0 - fU ) * uL + fU * uR ; } *
appliedDelay = t - tminustD ; return uD ; } real_T look1_pbinlxpw ( real_T u0
, const real_T bp0 [ ] , const real_T table [ ] , uint32_T prevIndex [ ] ,
uint32_T maxIndex ) { real_T frac ; real_T yL_0d0 ; uint32_T bpIdx ; uint32_T
found ; uint32_T iLeft ; uint32_T iRght ; if ( u0 <= bp0 [ 0U ] ) { bpIdx =
0U ; frac = ( u0 - bp0 [ 0U ] ) / ( bp0 [ 1U ] - bp0 [ 0U ] ) ; } else if (
u0 < bp0 [ maxIndex ] ) { bpIdx = prevIndex [ 0U ] ; iLeft = 0U ; iRght =
maxIndex ; found = 0U ; while ( found == 0U ) { if ( u0 < bp0 [ bpIdx ] ) {
iRght = bpIdx - 1U ; bpIdx = ( ( bpIdx + iLeft ) - 1U ) >> 1U ; } else if (
u0 < bp0 [ bpIdx + 1U ] ) { found = 1U ; } else { iLeft = bpIdx + 1U ; bpIdx
= ( ( bpIdx + iRght ) + 1U ) >> 1U ; } } frac = ( u0 - bp0 [ bpIdx ] ) / (
bp0 [ bpIdx + 1U ] - bp0 [ bpIdx ] ) ; } else { bpIdx = maxIndex - 1U ; frac
= ( u0 - bp0 [ maxIndex - 1U ] ) / ( bp0 [ maxIndex ] - bp0 [ maxIndex - 1U ]
) ; } prevIndex [ 0U ] = bpIdx ; yL_0d0 = table [ bpIdx ] ; return ( table [
bpIdx + 1U ] - yL_0d0 ) * frac + yL_0d0 ; } void rt_ssGetBlockPath (
SimStruct * S , int_T sysIdx , int_T blkIdx , char_T * * path ) {
_ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void rt_ssSet_slErrMsg (
void * S , void * diag ) { SimStruct * castedS = ( SimStruct * ) S ; if ( !
_ssIsErrorStatusAslErrMsg ( castedS ) ) { _ssSet_slErrMsg ( castedS , diag )
; } else { _ssDiscardDiagnostic ( castedS , diag ) ; } } void
rt_ssReportDiagnosticAsWarning ( void * S , void * diag ) {
_ssReportDiagnosticAsWarning ( ( SimStruct * ) S , diag ) ; } void
rt_ssReportDiagnosticAsInfo ( void * S , void * diag ) {
_ssReportDiagnosticAsInfo ( ( SimStruct * ) S , diag ) ; } void
dVOC_monitor_network1_Subsystempi2delay_Init ( SimStruct * S ,
B_Subsystempi2delay_dVOC_monitor_network1_T * localB ,
P_Subsystempi2delay_dVOC_monitor_network1_T * localP ) { localB ->
B_24_1752_13384 = localP -> P_0 [ 0 ] ; localB -> B_24_1753_13392 = localP ->
P_0 [ 1 ] ; } void dVOC_monitor_network1_Subsystempi2delay_Disable (
SimStruct * S , DW_Subsystempi2delay_dVOC_monitor_network1_T * localDW ) {
localDW -> Subsystempi2delay_MODE = false ; } void
dVOC_monitor_network1_Subsystempi2delay ( SimStruct * S , uint8_T rtu_Enable
, const real_T rtu_alpha_beta [ 2 ] , real_T rtu_wt ,
B_Subsystempi2delay_dVOC_monitor_network1_T * localB ,
DW_Subsystempi2delay_dVOC_monitor_network1_T * localDW ) { int32_T isHit ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) &&
ssIsModeUpdateTimeStep ( S ) ) { if ( rtu_Enable > 0 ) { if ( ! localDW ->
Subsystempi2delay_MODE ) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S )
) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } localDW ->
Subsystempi2delay_MODE = true ; } } else if ( localDW ->
Subsystempi2delay_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
dVOC_monitor_network1_Subsystempi2delay_Disable ( S , localDW ) ; } } if (
localDW -> Subsystempi2delay_MODE ) { localB -> B_24_1752_13384 =
rtu_alpha_beta [ 0 ] * muDoubleScalarSin ( rtu_wt ) - rtu_alpha_beta [ 1 ] *
muDoubleScalarCos ( rtu_wt ) ; localB -> B_24_1753_13392 = rtu_alpha_beta [ 0
] * muDoubleScalarCos ( rtu_wt ) + rtu_alpha_beta [ 1 ] * muDoubleScalarSin (
rtu_wt ) ; if ( ssIsModeUpdateTimeStep ( S ) ) { srUpdateBC ( localDW ->
Subsystempi2delay_SubsysRanBC ) ; } } } void
dVOC_monitor_network1_Subsystempi2delay_Term ( SimStruct * const S ) { } void
dVOC_monitor_network1_Subsystem1_Init ( SimStruct * S ,
B_Subsystem1_dVOC_monitor_network1_T * localB ,
P_Subsystem1_dVOC_monitor_network1_T * localP ) { localB -> B_25_1750_13368 =
localP -> P_0 [ 0 ] ; localB -> B_25_1751_13376 = localP -> P_0 [ 1 ] ; }
void dVOC_monitor_network1_Subsystem1_Disable ( SimStruct * S ,
DW_Subsystem1_dVOC_monitor_network1_T * localDW ) { localDW ->
Subsystem1_MODE = false ; } void dVOC_monitor_network1_Subsystem1 ( SimStruct
* S , uint8_T rtu_Enable , const real_T rtu_alpha_beta [ 2 ] , real_T rtu_wt
, B_Subsystem1_dVOC_monitor_network1_T * localB ,
DW_Subsystem1_dVOC_monitor_network1_T * localDW ) { int32_T isHit ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) && ssIsModeUpdateTimeStep (
S ) ) { if ( rtu_Enable > 0 ) { if ( ! localDW -> Subsystem1_MODE ) { if (
ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } localDW ->
Subsystem1_MODE = true ; } } else if ( localDW -> Subsystem1_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
dVOC_monitor_network1_Subsystem1_Disable ( S , localDW ) ; } } if ( localDW
-> Subsystem1_MODE ) { localB -> B_25_1750_13368 = rtu_alpha_beta [ 0 ] *
muDoubleScalarCos ( rtu_wt ) + rtu_alpha_beta [ 1 ] * muDoubleScalarSin (
rtu_wt ) ; localB -> B_25_1751_13376 = - rtu_alpha_beta [ 0 ] *
muDoubleScalarSin ( rtu_wt ) + rtu_alpha_beta [ 1 ] * muDoubleScalarCos (
rtu_wt ) ; if ( ssIsModeUpdateTimeStep ( S ) ) { srUpdateBC ( localDW ->
Subsystem1_SubsysRanBC ) ; } } } void dVOC_monitor_network1_Subsystem1_Term (
SimStruct * const S ) { } void dVOC_monitor_network1_Subsystempi2delay_c_Init
( SimStruct * S , B_Subsystempi2delay_dVOC_monitor_network1_b_T * localB ,
P_Subsystempi2delay_dVOC_monitor_network1_g_T * localP ) { localB ->
B_36_1728_13192 = localP -> P_0 [ 0 ] ; localB -> B_36_1729_13200 = localP ->
P_0 [ 1 ] ; } void dVOC_monitor_network1_Subsystempi2delay_p_Disable (
SimStruct * S , DW_Subsystempi2delay_dVOC_monitor_network1_d_T * localDW ) {
localDW -> Subsystempi2delay_MODE = false ; } void
dVOC_monitor_network1_Subsystempi2delay_o ( SimStruct * S , uint8_T
rtu_Enable , real_T rtu_dq , real_T rtu_dq_h , real_T rtu_wt ,
B_Subsystempi2delay_dVOC_monitor_network1_b_T * localB ,
DW_Subsystempi2delay_dVOC_monitor_network1_d_T * localDW ) { int32_T isHit ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) &&
ssIsModeUpdateTimeStep ( S ) ) { if ( rtu_Enable > 0 ) { if ( ! localDW ->
Subsystempi2delay_MODE ) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S )
) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } localDW ->
Subsystempi2delay_MODE = true ; } } else if ( localDW ->
Subsystempi2delay_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
dVOC_monitor_network1_Subsystempi2delay_p_Disable ( S , localDW ) ; } } if (
localDW -> Subsystempi2delay_MODE ) { localB -> B_36_1728_13192 = rtu_dq *
muDoubleScalarSin ( rtu_wt ) + rtu_dq_h * muDoubleScalarCos ( rtu_wt ) ;
localB -> B_36_1729_13200 = - rtu_dq * muDoubleScalarCos ( rtu_wt ) +
rtu_dq_h * muDoubleScalarSin ( rtu_wt ) ; if ( ssIsModeUpdateTimeStep ( S ) )
{ srUpdateBC ( localDW -> Subsystempi2delay_SubsysRanBC ) ; } } } void
dVOC_monitor_network1_Subsystempi2delay_b_Term ( SimStruct * const S ) { }
void dVOC_monitor_network1_Subsystem1_m_Init ( SimStruct * S ,
B_Subsystem1_dVOC_monitor_network1_m_T * localB ,
P_Subsystem1_dVOC_monitor_network1_a_T * localP ) { localB -> B_37_1726_13176
= localP -> P_0 [ 0 ] ; localB -> B_37_1727_13184 = localP -> P_0 [ 1 ] ; }
void dVOC_monitor_network1_Subsystem1_d_Disable ( SimStruct * S ,
DW_Subsystem1_dVOC_monitor_network1_k_T * localDW ) { localDW ->
Subsystem1_MODE = false ; } void dVOC_monitor_network1_Subsystem1_b (
SimStruct * S , uint8_T rtu_Enable , real_T rtu_dq , real_T rtu_dq_m , real_T
rtu_wt , B_Subsystem1_dVOC_monitor_network1_m_T * localB ,
DW_Subsystem1_dVOC_monitor_network1_k_T * localDW ) { int32_T isHit ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) && ssIsModeUpdateTimeStep (
S ) ) { if ( rtu_Enable > 0 ) { if ( ! localDW -> Subsystem1_MODE ) { if (
ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } localDW ->
Subsystem1_MODE = true ; } } else if ( localDW -> Subsystem1_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
dVOC_monitor_network1_Subsystem1_d_Disable ( S , localDW ) ; } } if ( localDW
-> Subsystem1_MODE ) { localB -> B_37_1726_13176 = rtu_dq * muDoubleScalarCos
( rtu_wt ) - rtu_dq_m * muDoubleScalarSin ( rtu_wt ) ; localB ->
B_37_1727_13184 = rtu_dq * muDoubleScalarSin ( rtu_wt ) + rtu_dq_m *
muDoubleScalarCos ( rtu_wt ) ; if ( ssIsModeUpdateTimeStep ( S ) ) {
srUpdateBC ( localDW -> Subsystem1_SubsysRanBC ) ; } } } void
dVOC_monitor_network1_Subsystem1_e_Term ( SimStruct * const S ) { } void
dVOC_monitor_network1_AutomaticGainControl_Init ( SimStruct * S ,
B_AutomaticGainControl_dVOC_monitor_network1_T * localB ,
P_AutomaticGainControl_dVOC_monitor_network1_T * localP ,
X_AutomaticGainControl_dVOC_monitor_network1_T * localX ) { localX ->
VariableTransportDelay_CSTATE_o3 = 0.0 ; localX -> integrator_CSTATE_f =
localP -> P_3 ; localX -> VariableTransportDelay_CSTATE_k = 0.0 ; localX ->
integrator_CSTATE_ot = localP -> P_6 ;
dVOC_monitor_network1_Subsystempi2delay_Init ( S , & localB ->
Subsystempi2delay , & localP -> Subsystempi2delay ) ;
dVOC_monitor_network1_Subsystem1_Init ( S , & localB -> Subsystem1 , & localP
-> Subsystem1 ) ; localB -> B_56_1669_12744 = localP -> P_0 ; } void
dVOC_monitor_network1_AutomaticGainControl_Disable ( SimStruct * S ,
DW_AutomaticGainControl_dVOC_monitor_network1_T * localDW ) { if ( localDW ->
Subsystempi2delay . Subsystempi2delay_MODE ) {
dVOC_monitor_network1_Subsystempi2delay_Disable ( S , & localDW ->
Subsystempi2delay ) ; } if ( localDW -> Subsystem1 . Subsystem1_MODE ) {
dVOC_monitor_network1_Subsystem1_Disable ( S , & localDW -> Subsystem1 ) ; }
localDW -> AutomaticGainControl_MODE = false ; } void
dVOC_monitor_network1_AutomaticGainControl ( SimStruct * S , real_T
rtu_Enable , real_T rtu_Freq , real_T rtu_wt , const real_T rtu_Vabc [ 3 ] ,
B_AutomaticGainControl_dVOC_monitor_network1_T * localB ,
DW_AutomaticGainControl_dVOC_monitor_network1_T * localDW ,
P_AutomaticGainControl_dVOC_monitor_network1_T * localP ,
X_AutomaticGainControl_dVOC_monitor_network1_T * localX ,
XDis_AutomaticGainControl_dVOC_monitor_network1_T * localXdis ) { real_T
B_56_1674_12784_0 ; int32_T isHit ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( ( isHit != 0 ) && ssIsModeUpdateTimeStep ( S ) ) { if ( rtu_Enable > 0.0 )
{ if ( ! localDW -> AutomaticGainControl_MODE ) { if ( ssGetTaskTime ( S , 1
) != ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
} ( void ) memset ( & ( localXdis -> VariableTransportDelay_CSTATE_o3 ) , 0 ,
4 * sizeof ( boolean_T ) ) ; localDW -> AutomaticGainControl_MODE = true ; }
} else { if ( ssGetTaskTime ( S , 1 ) == ssGetTStart ( S ) ) { ( void )
memset ( & ( localXdis -> VariableTransportDelay_CSTATE_o3 ) , 1 , 4 * sizeof
( boolean_T ) ) ; } if ( localDW -> AutomaticGainControl_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; ( void ) memset ( & (
localXdis -> VariableTransportDelay_CSTATE_o3 ) , 1 , 4 * sizeof ( boolean_T
) ) ; dVOC_monitor_network1_AutomaticGainControl_Disable ( S , localDW ) ; }
} } if ( localDW -> AutomaticGainControl_MODE ) { { real_T * * uBuffer = (
real_T * * ) & localDW -> VariableTransportDelay_PWORK . TUbufferPtrs [ 0 ] ;
real_T simTime = ssGetT ( S ) ; real_T appliedDelay ; localB ->
B_56_1659_12664 = dVOC_monitor_network1_acc_rt_VTDelayfindtDInterpolate (
localX -> VariableTransportDelay_CSTATE_o3 , * uBuffer , localDW ->
VariableTransportDelay_IWORK . CircularBufSize , localDW ->
VariableTransportDelay_IWORK . Head , localDW -> VariableTransportDelay_IWORK
. Tail , & localDW -> VariableTransportDelay_IWORK . Last , simTime , 0.0 , 0
, ( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ( * uBuffer + localDW ->
VariableTransportDelay_IWORK . CircularBufSize ) [ localDW ->
VariableTransportDelay_IWORK . Head ] == ssGetT ( S ) ) ) , localP -> P_2 , &
appliedDelay ) ; } localB -> B_56_1660_12672 = localX -> integrator_CSTATE_f
; localB -> B_56_1661_12680 = ssGetT ( S ) ; isHit = ssIsSampleHit ( S , 1 ,
0 ) ; if ( isHit != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { localDW ->
RelationalOperator_Mode = ( localB -> B_56_1661_12680 >= localB ->
B_56_1682_12848 ) ; } localB -> B_56_1692_12914 = localDW ->
RelationalOperator_Mode ; } if ( localB -> B_56_1692_12914 ) { localB ->
B_52_1688_12896 = localB -> B_56_1660_12672 - localB -> B_56_1659_12664 ;
localB -> B_52_1689_12904 = localB -> B_52_1688_12896 * rtu_Freq ; localB ->
B_56_1662_12688 = localB -> B_52_1689_12904 ; } else { localB ->
B_56_1662_12688 = localB -> B_56_1683_12856 ; } { real_T * * uBuffer = (
real_T * * ) & localDW -> VariableTransportDelay_PWORK_e . TUbufferPtrs [ 0 ]
; real_T simTime = ssGetT ( S ) ; real_T appliedDelay ; localB ->
B_56_1663_12696 = dVOC_monitor_network1_acc_rt_VTDelayfindtDInterpolate (
localX -> VariableTransportDelay_CSTATE_k , * uBuffer , localDW ->
VariableTransportDelay_IWORK_b . CircularBufSize , localDW ->
VariableTransportDelay_IWORK_b . Head , localDW ->
VariableTransportDelay_IWORK_b . Tail , & localDW ->
VariableTransportDelay_IWORK_b . Last , simTime , 0.0 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + localDW ->
VariableTransportDelay_IWORK_b . CircularBufSize ) [ localDW ->
VariableTransportDelay_IWORK_b . Head ] == ssGetT ( S ) ) ) , localP -> P_5 ,
& appliedDelay ) ; } localB -> B_56_1664_12704 = localX ->
integrator_CSTATE_ot ; localB -> B_56_1665_12712 = ssGetT ( S ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsModeUpdateTimeStep
( S ) ) { localDW -> RelationalOperator_Mode_n = ( localB -> B_56_1665_12712
>= localB -> B_56_1684_12864 ) ; } localB -> B_56_1693_12915 = localDW ->
RelationalOperator_Mode_n ; } if ( localB -> B_56_1693_12915 ) { localB ->
B_53_1686_12880 = localB -> B_56_1664_12704 - localB -> B_56_1663_12696 ;
localB -> B_53_1687_12888 = localB -> B_53_1686_12880 * rtu_Freq ; localB ->
B_56_1666_12720 = localB -> B_53_1687_12888 ; } else { localB ->
B_56_1666_12720 = localB -> B_56_1685_12872 ; } localB -> B_56_1658_12648 .
re = localB -> B_56_1662_12688 ; localB -> B_56_1658_12648 . im = localB ->
B_56_1666_12720 ; localB -> B_56_1667_12728 = muDoubleScalarHypot ( localB ->
B_56_1658_12648 . re , localB -> B_56_1658_12648 . im ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { if ( localB -> B_56_1667_12728 >= localP ->
P_7 ) { localDW -> Saturation_MODE = 1 ; } else if ( localB ->
B_56_1667_12728 > localP -> P_8 ) { localDW -> Saturation_MODE = 0 ; } else {
localDW -> Saturation_MODE = - 1 ; } } if ( localDW -> Saturation_MODE == 1 )
{ localB -> B_56_1668_12736 = localP -> P_7 ; } else if ( localDW ->
Saturation_MODE == - 1 ) { localB -> B_56_1668_12736 = localP -> P_8 ; } else
{ localB -> B_56_1668_12736 = localB -> B_56_1667_12728 ; } localB ->
B_56_1669_12744 = 1.0 / localB -> B_56_1668_12736 ; if ( rtu_Freq > localP ->
P_9 ) { localB -> B_56_1670_12752 = localP -> P_9 ; } else if ( rtu_Freq <
localP -> P_10 ) { localB -> B_56_1670_12752 = localP -> P_10 ; } else {
localB -> B_56_1670_12752 = rtu_Freq ; } localB -> B_56_1671_12760 = 1.0 /
localB -> B_56_1670_12752 ; if ( rtu_Freq > localP -> P_11 ) { localB ->
B_56_1672_12768 = localP -> P_11 ; } else if ( rtu_Freq < localP -> P_12 ) {
localB -> B_56_1672_12768 = localP -> P_12 ; } else { localB ->
B_56_1672_12768 = rtu_Freq ; } localB -> B_56_1673_12776 = 1.0 / localB ->
B_56_1672_12768 ; for ( isHit = 0 ; isHit < 3 ; isHit ++ ) {
B_56_1674_12784_0 = localP -> P_13 [ isHit ] * rtu_Vabc [ 0 ] ;
B_56_1674_12784_0 += localP -> P_13 [ isHit + 3 ] * rtu_Vabc [ 1 ] ;
B_56_1674_12784_0 += localP -> P_13 [ isHit + 6 ] * rtu_Vabc [ 2 ] ; localB
-> B_56_1674_12784 [ isHit ] = B_56_1674_12784_0 ; } localB ->
B_56_1677_12808 [ 0 ] = localP -> P_14 * localB -> B_56_1674_12784 [ 0 ] ;
localB -> B_56_1677_12808 [ 1 ] = localP -> P_14 * localB -> B_56_1674_12784
[ 1 ] ; localB -> B_56_1677_12808 [ 2 ] = localP -> P_14 * localB ->
B_56_1674_12784 [ 2 ] ; dVOC_monitor_network1_Subsystempi2delay ( S , localB
-> B_56_1691_12913 , & localB -> B_56_1677_12808 [ 0 ] , rtu_wt , & localB ->
Subsystempi2delay , & localDW -> Subsystempi2delay ) ;
dVOC_monitor_network1_Subsystem1 ( S , localB -> B_56_1690_12912 , & localB
-> B_56_1677_12808 [ 0 ] , rtu_wt , & localB -> Subsystem1 , & localDW ->
Subsystem1 ) ; if ( localB -> B_56_1690_12912 != 0 ) { localB ->
B_56_1680_12832 [ 0 ] = localB -> Subsystem1 . B_25_1750_13368 ; localB ->
B_56_1680_12832 [ 1 ] = localB -> Subsystem1 . B_25_1751_13376 ; } else {
localB -> B_56_1680_12832 [ 0 ] = localB -> Subsystempi2delay .
B_24_1752_13384 ; localB -> B_56_1680_12832 [ 1 ] = localB ->
Subsystempi2delay . B_24_1753_13392 ; } if ( ssIsModeUpdateTimeStep ( S ) ) {
srUpdateBC ( localDW -> AutomaticGainControl_SubsysRanBC ) ; } } } void
dVOC_monitor_network1_AutomaticGainControlTID4 ( SimStruct * S ,
B_AutomaticGainControl_dVOC_monitor_network1_T * localB ,
DW_AutomaticGainControl_dVOC_monitor_network1_T * localDW ,
P_AutomaticGainControl_dVOC_monitor_network1_T * localP ) { localB ->
B_56_1682_12848 = localP -> P_15 ; localB -> B_56_1683_12856 = localP -> P_16
; localB -> B_56_1684_12864 = localP -> P_17 ; localB -> B_56_1685_12872 =
localP -> P_18 ; localB -> B_56_1690_12912 = ( uint8_T ) ( localP -> P_19 ==
localP -> P_20 ) ; localB -> B_56_1691_12913 = ( uint8_T ) ( localP -> P_19
== localP -> P_21 ) ; if ( ssIsModeUpdateTimeStep ( S ) ) { srUpdateBC (
localDW -> AutomaticGainControl_SubsysRanBC ) ; } } void
dVOC_monitor_network1_AutomaticGainControl_Update ( SimStruct * S ,
B_AutomaticGainControl_dVOC_monitor_network1_T * localB ,
DW_AutomaticGainControl_dVOC_monitor_network1_T * localDW ,
P_AutomaticGainControl_dVOC_monitor_network1_T * localP ,
X_AutomaticGainControl_dVOC_monitor_network1_T * localX ) { if ( localDW ->
AutomaticGainControl_MODE ) { { real_T * * uBuffer = ( real_T * * ) & localDW
-> VariableTransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; localDW -> VariableTransportDelay_IWORK . Head = ( ( localDW
-> VariableTransportDelay_IWORK . Head < ( localDW ->
VariableTransportDelay_IWORK . CircularBufSize - 1 ) ) ? ( localDW ->
VariableTransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( localDW ->
VariableTransportDelay_IWORK . Head == localDW ->
VariableTransportDelay_IWORK . Tail ) { if ( !
dVOC_monitor_network1_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
VariableTransportDelay_IWORK . CircularBufSize , & localDW ->
VariableTransportDelay_IWORK . Tail , & localDW ->
VariableTransportDelay_IWORK . Head , & localDW ->
VariableTransportDelay_IWORK . Last , simTime - localP -> P_1 , uBuffer , (
boolean_T ) 0 , ( boolean_T ) 1 , & localDW -> VariableTransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "vtdelay memory allocation error"
) ; return ; } } ( * uBuffer + localDW -> VariableTransportDelay_IWORK .
CircularBufSize ) [ localDW -> VariableTransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer + 2 * localDW -> VariableTransportDelay_IWORK .
CircularBufSize ) [ localDW -> VariableTransportDelay_IWORK . Head ] = localX
-> VariableTransportDelay_CSTATE_o3 ; ( * uBuffer ) [ localDW ->
VariableTransportDelay_IWORK . Head ] = localB -> B_56_1660_12672 ; } {
real_T * * uBuffer = ( real_T * * ) & localDW ->
VariableTransportDelay_PWORK_e . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; localDW -> VariableTransportDelay_IWORK_b . Head = ( ( localDW ->
VariableTransportDelay_IWORK_b . Head < ( localDW ->
VariableTransportDelay_IWORK_b . CircularBufSize - 1 ) ) ? ( localDW ->
VariableTransportDelay_IWORK_b . Head + 1 ) : 0 ) ; if ( localDW ->
VariableTransportDelay_IWORK_b . Head == localDW ->
VariableTransportDelay_IWORK_b . Tail ) { if ( !
dVOC_monitor_network1_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
VariableTransportDelay_IWORK_b . CircularBufSize , & localDW ->
VariableTransportDelay_IWORK_b . Tail , & localDW ->
VariableTransportDelay_IWORK_b . Head , & localDW ->
VariableTransportDelay_IWORK_b . Last , simTime - localP -> P_4 , uBuffer , (
boolean_T ) 0 , ( boolean_T ) 1 , & localDW -> VariableTransportDelay_IWORK_b
. MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"vtdelay memory allocation error" ) ; return ; } } ( * uBuffer + localDW ->
VariableTransportDelay_IWORK_b . CircularBufSize ) [ localDW ->
VariableTransportDelay_IWORK_b . Head ] = simTime ; ( * uBuffer + 2 * localDW
-> VariableTransportDelay_IWORK_b . CircularBufSize ) [ localDW ->
VariableTransportDelay_IWORK_b . Head ] = localX ->
VariableTransportDelay_CSTATE_k ; ( * uBuffer ) [ localDW ->
VariableTransportDelay_IWORK_b . Head ] = localB -> B_56_1664_12704 ; } } }
void dVOC_monitor_network1_AutomaticGainControl_Deriv ( SimStruct * S ,
B_AutomaticGainControl_dVOC_monitor_network1_T * localB ,
DW_AutomaticGainControl_dVOC_monitor_network1_T * localDW ,
P_AutomaticGainControl_dVOC_monitor_network1_T * localP ,
XDot_AutomaticGainControl_dVOC_monitor_network1_T * localXdot ) { if (
localDW -> AutomaticGainControl_MODE ) { { real_T instantDelay ; instantDelay
= localB -> B_56_1671_12760 ; if ( instantDelay > localP -> P_1 ) {
instantDelay = localP -> P_1 ; } if ( instantDelay < 0.0 ) { localXdot ->
VariableTransportDelay_CSTATE_o3 = 0 ; } else { localXdot ->
VariableTransportDelay_CSTATE_o3 = 1.0 / instantDelay ; } } localXdot ->
integrator_CSTATE_f = localB -> B_56_1680_12832 [ 0 ] ; { real_T instantDelay
; instantDelay = localB -> B_56_1673_12776 ; if ( instantDelay > localP ->
P_4 ) { instantDelay = localP -> P_4 ; } if ( instantDelay < 0.0 ) {
localXdot -> VariableTransportDelay_CSTATE_k = 0 ; } else { localXdot ->
VariableTransportDelay_CSTATE_k = 1.0 / instantDelay ; } } localXdot ->
integrator_CSTATE_ot = localB -> B_56_1680_12832 [ 1 ] ; } else { { real_T *
dx ; int_T i ; dx = & ( localXdot -> VariableTransportDelay_CSTATE_o3 ) ; for
( i = 0 ; i < 4 ; i ++ ) { dx [ i ] = 0.0 ; } } } } void
dVOC_monitor_network1_AutomaticGainControl_ZC ( SimStruct * S ,
B_AutomaticGainControl_dVOC_monitor_network1_T * localB ,
DW_AutomaticGainControl_dVOC_monitor_network1_T * localDW ,
P_AutomaticGainControl_dVOC_monitor_network1_T * localP ,
ZCV_AutomaticGainControl_dVOC_monitor_network1_T * localZCSV ) { if ( localDW
-> AutomaticGainControl_MODE ) { localZCSV ->
RelationalOperator_RelopInput_ZC_jo = localB -> B_56_1661_12680 - localB ->
B_56_1682_12848 ; localZCSV -> RelationalOperator_RelopInput_ZC_k = localB ->
B_56_1665_12712 - localB -> B_56_1684_12864 ; localZCSV ->
Saturation_UprLim_ZC_a = localB -> B_56_1667_12728 - localP -> P_7 ;
localZCSV -> Saturation_LwrLim_ZC_o = localB -> B_56_1667_12728 - localP ->
P_8 ; } else { { real_T * zcsv = & ( localZCSV ->
RelationalOperator_RelopInput_ZC_jo ) ; int_T i ; for ( i = 0 ; i < 4 ; i ++
) { zcsv [ i ] = 0.0 ; } } } } void
dVOC_monitor_network1_AutomaticGainControl_Term ( SimStruct * const S ) { }
void rt_invd5x5_snf ( const real_T u [ 25 ] , real_T y [ 25 ] ) { real_T x [
25 ] ; real_T s ; real_T smax ; int32_T c ; int32_T ijA ; int32_T ix ;
int32_T iy ; int32_T jA ; int32_T jBcol ; int32_T jj ; int32_T jp1j ; int32_T
pipk ; int8_T ipiv [ 5 ] ; int8_T p [ 5 ] ; int8_T p_0 ; for ( ix = 0 ; ix <
25 ; ix ++ ) { y [ ix ] = 0.0 ; x [ ix ] = u [ ix ] ; } for ( ix = 0 ; ix < 5
; ix ++ ) { ipiv [ ix ] = ( int8_T ) ( ix + 1 ) ; } for ( pipk = 0 ; pipk < 4
; pipk ++ ) { jBcol = pipk * 6 + 1 ; jj = pipk * 6 ; c = 5 - pipk ; iy = 0 ;
smax = muDoubleScalarAbs ( x [ jj ] ) ; for ( jA = 2 ; jA <= c ; jA ++ ) { s
= muDoubleScalarAbs ( x [ ( jBcol + jA ) - 2 ] ) ; if ( s > smax ) { iy = jA
- 1 ; smax = s ; } } if ( x [ ( jBcol + iy ) - 1 ] != 0.0 ) { if ( iy != 0 )
{ ipiv [ pipk ] = ( int8_T ) ( ( pipk + iy ) + 1 ) ; iy = ( pipk + iy ) + 1 ;
for ( jA = 0 ; jA < 5 ; jA ++ ) { smax = x [ jA * 5 + pipk ] ; x [ pipk + jA
* 5 ] = x [ ( jA * 5 + iy ) - 1 ] ; x [ ( iy + jA * 5 ) - 1 ] = smax ; } } iy
= ( jBcol - pipk ) - 1 ; for ( ix = jBcol + 1 ; ix <= iy + 5 ; ix ++ ) { x [
ix - 1 ] /= x [ jj ] ; } } c = 3 - pipk ; jA = jj ; jj += 6 ; for ( jp1j = 0
; jp1j <= c ; jp1j ++ ) { if ( x [ ( jp1j * 5 + jj ) - 1 ] != 0.0 ) { smax =
- x [ ( jp1j * 5 + jj ) - 1 ] ; iy = jA + 7 ; ix = ( jA - pipk ) + 10 ; for (
ijA = iy ; ijA <= ix ; ijA ++ ) { x [ ijA - 1 ] += x [ ( ( ( jBcol + ijA ) -
jA ) - 6 ) - 1 ] * smax ; } } jA += 5 ; } } for ( ix = 0 ; ix < 5 ; ix ++ ) {
p [ ix ] = ( int8_T ) ( ix + 1 ) ; } if ( ipiv [ 0 ] > 1 ) { pipk = p [ ipiv
[ 0 ] - 1 ] ; p [ ipiv [ 0 ] - 1 ] = p [ 0 ] ; p [ 0 ] = ( int8_T ) pipk ; }
if ( ipiv [ 1 ] > 2 ) { pipk = p [ ipiv [ 1 ] - 1 ] ; p [ ipiv [ 1 ] - 1 ] =
p [ 1 ] ; p [ 1 ] = ( int8_T ) pipk ; } if ( ipiv [ 2 ] > 3 ) { pipk = p [
ipiv [ 2 ] - 1 ] ; p [ ipiv [ 2 ] - 1 ] = p [ 2 ] ; p [ 2 ] = ( int8_T ) pipk
; } if ( ipiv [ 3 ] > 4 ) { pipk = p [ 4 ] ; p [ 4 ] = p [ 3 ] ; p [ 3 ] = (
int8_T ) pipk ; } for ( jA = 0 ; jA < 5 ; jA ++ ) { jj = jA + 1 ; p_0 = p [
jA ] ; y [ jA + 5 * ( p_0 - 1 ) ] = 1.0 ; for ( pipk = jj ; pipk < 6 ; pipk
++ ) { if ( y [ ( ( p_0 - 1 ) * 5 + pipk ) - 1 ] != 0.0 ) { for ( ix = pipk +
1 ; ix < 6 ; ix ++ ) { y [ ( ix + 5 * ( p_0 - 1 ) ) - 1 ] -= y [ ( ( p_0 - 1
) * 5 + pipk ) - 1 ] * x [ ( ( pipk - 1 ) * 5 + ix ) - 1 ] ; } } } } for (
pipk = 0 ; pipk < 5 ; pipk ++ ) { jBcol = 5 * pipk ; for ( jA = 4 ; jA >= 0 ;
jA -- ) { jj = 5 * jA ; if ( y [ jA + jBcol ] != 0.0 ) { y [ jA + jBcol ] /=
x [ jA + jj ] ; iy = jA - 1 ; for ( ix = 0 ; ix <= iy ; ix ++ ) { y [ ix +
jBcol ] -= x [ ix + jj ] * y [ jA + jBcol ] ; } } } } } static void
mdlOutputs ( SimStruct * S , int_T tid ) { real_T B_136_1771_13536 ; real_T
B_136_1778_13592 ; real_T B_136_1792_13704 ; real_T B_136_1799_13760 ; real_T
B_136_1872_14344 ; real_T B_136_1873_14352 ; B_dVOC_monitor_network1_T * _rtB
; DW_dVOC_monitor_network1_T * _rtDW ; P_dVOC_monitor_network1_T * _rtP ;
PrevZCX_dVOC_monitor_network1_T * _rtZCE ; XDis_dVOC_monitor_network1_T *
_rtXdis ; X_dVOC_monitor_network1_T * _rtX ; real_T B_128_2152_16584 [ 25 ] ;
real_T rtb_B_128_2152_16584 [ 25 ] ; real_T rtb_B_136_2289_17680 [ 25 ] ;
real_T rtb_B_136_2273_17552 [ 16 ] ; real_T rtb_B_136_2259_17440 [ 5 ] ;
real_T tmpForInput [ 4 ] ; real_T rtb_B_128_2256_17416 [ 3 ] ; real_T
rtb_B_136_2214_17080 [ 3 ] ; real_T rtb_B_136_2264_17480 [ 3 ] ; real_T
rtb_B_136_2267_17504 [ 3 ] ; real_T rtb_B_136_2339_18080 [ 3 ] ; real_T
B_127_2177_16784_idx_0 ; real_T B_127_2177_16784_idx_1 ; real_T
B_136_1814_13880_idx_1 ; real_T rtb_B_127_2179_16800 ; real_T
rtb_B_127_2182_16824 ; real_T rtb_B_128_2144_16520 ; real_T
rtb_B_128_2147_16544 ; real_T rtb_B_136_1758_13432 ; real_T
rtb_B_136_1759_13440 ; real_T rtb_B_136_1807_13824 ; real_T
rtb_B_136_1808_13832 ; real_T rtb_B_136_1817_13904 ; real_T
rtb_B_136_1854_14200 ; real_T rtb_B_136_1864_14280 ; real_T
rtb_B_136_1884_14440 ; int32_T i ; int32_T i_0 ; int32_T i_1 ; uint32_T ri ;
boolean_T didZcEventOccur ; _rtDW = ( ( DW_dVOC_monitor_network1_T * )
ssGetRootDWork ( S ) ) ; _rtXdis = ( ( XDis_dVOC_monitor_network1_T * )
ssGetContStateDisabled ( S ) ) ; _rtZCE = ( ( PrevZCX_dVOC_monitor_network1_T
* ) _ssGetPrevZCSigState ( S ) ) ; _rtX = ( ( X_dVOC_monitor_network1_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_dVOC_monitor_network1_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_dVOC_monitor_network1_T * )
_ssGetModelBlockIO ( S ) ) ; i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 )
{ muDoubleScalarSinCos ( _rtDW -> Rotorangledthetae_DSTATE + _rtP -> P_72 *
ssGetTaskTime ( S , 2 ) , & rtb_B_136_1758_13432 , & rtb_B_136_1759_13440 ) ;
for ( i = 0 ; i < 5 ; i ++ ) { _rtB -> B_136_0_0 [ i ] = _rtDW ->
fluxes_DSTATE [ i ] ; } if ( _rtB -> B_136_885_7080 > 0.0 ) { i =
ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtB -> B_128_1065_8520 = 1.0 /
( ( _rtB -> B_128_1120_8960 [ 0 ] + _rtB -> B_128_1120_8960 [ 1 ] ) + 1.0 /
_rtDW -> Lmd_sat_DSTATE ) ; rtb_B_128_2147_16544 = muDoubleScalarAbs ( ( (
_rtP -> P_49 [ 0 ] * _rtB -> B_136_0_0 [ 1 ] + _rtP -> P_49 [ 1 ] * _rtB ->
B_136_0_0 [ 2 ] ) + _rtP -> P_49 [ 2 ] * _rtB -> B_136_0_0 [ 3 ] ) * _rtB ->
B_128_1065_8520 ) ; rtb_B_128_2144_16520 = look1_pbinlxpw (
rtb_B_128_2147_16544 , _rtP -> P_52 , _rtP -> P_51 , & _rtDW -> m_bpIndex ,
1U ) ; if ( rtb_B_128_2144_16520 != 0.0 ) { rtb_B_128_2147_16544 /=
rtb_B_128_2144_16520 ; } else { rtb_B_128_2147_16544 = _rtB ->
B_128_1119_8952 ; } _rtB -> B_128_1066_8528 = _rtP -> P_53 *
rtb_B_128_2147_16544 ; if ( _rtB -> B_128_1299_9923 ) { i = ssIsSampleHit ( S
, 2 , 0 ) ; if ( i != 0 ) { tmpForInput [ 0 ] = _rtB -> B_127_1202_9616 [ 0 ]
; tmpForInput [ 1 ] = _rtB -> B_127_1202_9616 [ 1 ] ; tmpForInput [ 2 ] =
_rtB -> B_127_1202_9616 [ 2 ] ; tmpForInput [ 3 ] = 1.0 / _rtDW ->
Lmq_sat_DSTATE ; _rtB -> B_127_1199_9592 = 1.0 / ( ( ( tmpForInput [ 0 ] +
tmpForInput [ 1 ] ) + tmpForInput [ 2 ] ) + tmpForInput [ 3 ] ) ;
rtb_B_127_2182_16824 = muDoubleScalarAbs ( ( _rtP -> P_38 [ 0 ] * _rtB ->
B_136_0_0 [ 0 ] + _rtP -> P_38 [ 1 ] * _rtB -> B_136_0_0 [ 4 ] ) * _rtB ->
B_127_1199_9592 ) ; rtb_B_127_2179_16800 = look1_pbinlxpw (
rtb_B_127_2182_16824 , _rtP -> P_41 , _rtP -> P_40 , & _rtDW -> m_bpIndex_b ,
1U ) ; if ( rtb_B_127_2179_16800 != 0.0 ) { rtb_B_127_2182_16824 /=
rtb_B_127_2179_16800 ; } else { rtb_B_127_2182_16824 = _rtB ->
B_127_1201_9608 ; } _rtB -> B_127_1200_9600 = _rtP -> P_42 *
rtb_B_127_2182_16824 ; } srUpdateBC ( _rtDW -> Lmq_sat_SubsysRanBC ) ; } if (
_rtB -> B_128_1300_9924 ) { _rtB -> B_128_1067_8536 = _rtB -> B_127_1200_9600
; } else { _rtB -> B_128_1067_8536 = _rtB -> B_128_1198_9584 ; } memcpy ( &
rtb_B_128_2152_16584 [ 0 ] , & _rtB -> B_128_1122_8976 [ 0 ] , 25U * sizeof (
real_T ) ) ; rtb_B_128_2152_16584 [ 0 ] = _rtB -> B_128_1067_8536 ;
rtb_B_128_2152_16584 [ 4 ] = _rtB -> B_128_1067_8536 ; rtb_B_128_2152_16584 [
20 ] = _rtB -> B_128_1067_8536 ; rtb_B_128_2152_16584 [ 24 ] = _rtB ->
B_128_1067_8536 ; for ( i = 0 ; i < 3 ; i ++ ) { rtb_B_128_2152_16584 [ 5 * (
i + 1 ) + 1 ] = _rtB -> B_128_1066_8528 ; rtb_B_128_2152_16584 [ 5 * ( i + 1
) + 2 ] = _rtB -> B_128_1066_8528 ; rtb_B_128_2152_16584 [ 5 * ( i + 1 ) + 3
] = _rtB -> B_128_1066_8528 ; } for ( i = 0 ; i < 25 ; i ++ ) {
B_128_2152_16584 [ i ] = rtb_B_128_2152_16584 [ i ] + _rtB -> B_128_1147_9176
[ i ] ; } rt_invd5x5_snf ( B_128_2152_16584 , _rtB -> B_128_1068_8544 ) ; for
( i = 0 ; i < 5 ; i ++ ) { for ( i_0 = 0 ; i_0 < 5 ; i_0 ++ ) {
rtb_B_128_2147_16544 = 0.0 ; for ( i_1 = 0 ; i_1 < 5 ; i_1 ++ ) {
rtb_B_128_2147_16544 += _rtB -> B_128_1172_9376 [ 5 * i_1 + i_0 ] * _rtB ->
B_128_1068_8544 [ 5 * i + i_1 ] ; } _rtB -> B_128_1093_8744 [ i_0 + 5 * i ] =
rtb_B_128_2147_16544 ; } } if ( _rtB -> B_128_1301_9925 ) { _rtB ->
B_128_1118_8944 = _rtB -> B_127_1199_9592 ; } else { _rtB -> B_128_1118_8944
= _rtB -> B_128_1197_9576 ; } } if ( ssIsModeUpdateTimeStep ( S ) ) {
srUpdateBC ( _rtDW -> Saturation_SubsysRanBC ) ; } } didZcEventOccur = ( _rtB
-> B_136_887_7096 >= _rtP -> P_74 ) ; if ( didZcEventOccur ) { memcpy ( &
B_128_2152_16584 [ 0 ] , & _rtB -> B_128_1068_8544 [ 0 ] , 25U * sizeof (
real_T ) ) ; } else { memcpy ( & B_128_2152_16584 [ 0 ] , & _rtB ->
B_136_888_7104 [ 0 ] , 25U * sizeof ( real_T ) ) ; } for ( i = 0 ; i < 5 ; i
++ ) { rtb_B_128_2147_16544 = 0.0 ; for ( i_0 = 0 ; i_0 < 5 ; i_0 ++ ) {
rtb_B_128_2147_16544 += B_128_2152_16584 [ 5 * i_0 + i ] * _rtB -> B_136_0_0
[ i_0 ] ; } rtb_B_136_2259_17440 [ i ] = _rtP -> P_75 [ i ] *
rtb_B_128_2147_16544 ; } rtb_B_127_2182_16824 = rtb_B_136_2259_17440 [ 0 ] *
rtb_B_136_1759_13440 + rtb_B_136_2259_17440 [ 1 ] * rtb_B_136_1758_13432 ;
rtb_B_127_2179_16800 = ( ( - rtb_B_136_2259_17440 [ 0 ] - 1.7320508075688772
* rtb_B_136_2259_17440 [ 1 ] ) * rtb_B_136_1759_13440 + ( 1.7320508075688772
* rtb_B_136_2259_17440 [ 0 ] - rtb_B_136_2259_17440 [ 1 ] ) *
rtb_B_136_1758_13432 ) * 0.5 ; rtb_B_128_2147_16544 = ( 0.0 -
rtb_B_127_2182_16824 ) - rtb_B_127_2179_16800 ; _rtB -> B_136_5_40 [ 0 ] =
_rtP -> P_76 * rtb_B_127_2182_16824 ; _rtB -> B_136_5_40 [ 1 ] = _rtP -> P_76
* rtb_B_127_2179_16800 ; _rtB -> B_136_5_40 [ 2 ] = _rtP -> P_76 *
rtb_B_128_2147_16544 ; } _rtB -> B_136_8_64 = _rtX -> Integrator_CSTATE ;
_rtB -> B_136_9_72 = _rtX -> Integrator_CSTATE_i ; _rtB -> B_136_10_80 = _rtX
-> Integrator1_CSTATE ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { for
( i = 0 ; i < 3 ; i ++ ) { rtb_B_136_2214_17080 [ i ] = _rtDW ->
Memory2_PreviousInput [ i ] ; rtb_B_128_2144_16520 = ( _rtP -> P_81 [ i + 3 ]
* _rtDW -> Memory2_PreviousInput [ 1 ] + _rtP -> P_81 [ i ] * _rtDW ->
Memory2_PreviousInput [ 0 ] ) + _rtP -> P_81 [ i + 6 ] * _rtDW ->
Memory2_PreviousInput [ 2 ] ; rtb_B_136_2264_17480 [ i ] =
rtb_B_128_2144_16520 ; _rtB -> B_136_11_88 [ i ] = _rtP -> P_82 *
rtb_B_128_2144_16520 ; } } _rtB -> B_136_14_112 = _rtX -> Integrator3_CSTATE
; dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1242_9866 , & _rtB ->
B_136_11_88 [ 0 ] , _rtB -> B_136_14_112 , & _rtB -> Subsystem1_p , & _rtDW
-> Subsystem1_p ) ; dVOC_monitor_network1_Subsystempi2delay ( S , _rtB ->
B_136_1243_9867 , & _rtB -> B_136_11_88 [ 0 ] , _rtB -> B_136_14_112 , & _rtB
-> Subsystempi2delay_h , & _rtDW -> Subsystempi2delay_h ) ; if ( _rtB ->
B_136_1242_9866 != 0 ) { _rtB -> B_136_15_120 [ 0 ] = _rtB -> Subsystem1_p .
B_25_1750_13368 ; _rtB -> B_136_15_120 [ 1 ] = _rtB -> Subsystem1_p .
B_25_1751_13376 ; } else { _rtB -> B_136_15_120 [ 0 ] = _rtB ->
Subsystempi2delay_h . B_24_1752_13384 ; _rtB -> B_136_15_120 [ 1 ] = _rtB ->
Subsystempi2delay_h . B_24_1753_13392 ; } _rtB -> B_136_17_136 = _rtB ->
B_136_10_80 - _rtB -> B_136_15_120 [ 0 ] ; _rtB -> B_136_18_144 = _rtP ->
P_84 * _rtB -> B_136_17_136 ; _rtB -> B_136_19_152 = _rtB -> B_136_9_72 +
_rtB -> B_136_18_144 ; _rtB -> B_136_20_160 = _rtP -> P_85 * _rtB ->
B_136_19_152 ; _rtB -> B_136_21_168 = 0.0 ; _rtB -> B_136_21_168 += _rtP ->
P_87 * _rtX -> TransferFcn4_CSTATE ; _rtB -> B_136_22_176 = _rtB ->
B_136_10_80 * _rtB -> B_136_10_80 + _rtB -> B_136_865_6920 ; _rtB ->
B_136_23_184 = _rtB -> B_136_21_168 / _rtB -> B_136_22_176 ; _rtB ->
B_136_24_192 = _rtB -> B_136_866_6928 - _rtB -> B_136_23_184 ; _rtB ->
B_136_25_200 = _rtP -> P_88 * _rtB -> B_136_24_192 ; _rtB -> B_136_26_208 =
_rtB -> B_136_861_6888 + _rtB -> B_136_25_200 ; _rtB -> B_136_27_216 = _rtP
-> P_89 * _rtB -> B_136_26_208 ; _rtB -> B_136_28_224 = _rtB -> B_136_15_120
[ 1 ] * _rtB -> B_136_27_216 ; _rtB -> B_136_29_232 = _rtB -> B_136_20_160 -
_rtB -> B_136_28_224 ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { for
( i = 0 ; i < 3 ; i ++ ) { rtb_B_136_2264_17480 [ i ] = _rtDW ->
Memory3_PreviousInput [ i ] ; rtb_B_128_2144_16520 = ( _rtP -> P_91 [ i + 3 ]
* _rtDW -> Memory3_PreviousInput [ 1 ] + _rtP -> P_91 [ i ] * _rtDW ->
Memory3_PreviousInput [ 0 ] ) + _rtP -> P_91 [ i + 6 ] * _rtDW ->
Memory3_PreviousInput [ 2 ] ; rtb_B_136_2339_18080 [ i ] =
rtb_B_128_2144_16520 ; _rtB -> B_136_30_240 [ i ] = _rtP -> P_92 *
rtb_B_128_2144_16520 ; } } dVOC_monitor_network1_Subsystem1 ( S , _rtB ->
B_136_1236_9860 , & _rtB -> B_136_30_240 [ 0 ] , _rtB -> B_136_14_112 , &
_rtB -> Subsystem1_e , & _rtDW -> Subsystem1_e ) ;
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1237_9861 , &
_rtB -> B_136_30_240 [ 0 ] , _rtB -> B_136_14_112 , & _rtB ->
Subsystempi2delay_k , & _rtDW -> Subsystempi2delay_k ) ; if ( _rtB ->
B_136_1236_9860 != 0 ) { _rtB -> B_136_33_264 [ 0 ] = _rtB -> Subsystem1_e .
B_25_1750_13368 ; _rtB -> B_136_33_264 [ 1 ] = _rtB -> Subsystem1_e .
B_25_1751_13376 ; } else { _rtB -> B_136_33_264 [ 0 ] = _rtB ->
Subsystempi2delay_k . B_24_1752_13384 ; _rtB -> B_136_33_264 [ 1 ] = _rtB ->
Subsystempi2delay_k . B_24_1753_13392 ; } _rtB -> B_136_35_280 = _rtP -> P_93
* _rtB -> B_136_33_264 [ 0 ] ; _rtB -> B_136_36_288 = _rtB -> B_136_29_232 +
_rtB -> B_136_35_280 ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { for
( i = 0 ; i < 3 ; i ++ ) { rtb_B_136_2339_18080 [ i ] = _rtDW ->
Memory1_PreviousInput [ i ] ; rtb_B_128_2144_16520 = ( _rtP -> P_95 [ i + 3 ]
* _rtDW -> Memory1_PreviousInput [ 1 ] + _rtP -> P_95 [ i ] * _rtDW ->
Memory1_PreviousInput [ 0 ] ) + _rtP -> P_95 [ i + 6 ] * _rtDW ->
Memory1_PreviousInput [ 2 ] ; rtb_B_136_2267_17504 [ i ] =
rtb_B_128_2144_16520 ; _rtB -> B_136_37_296 [ i ] = _rtP -> P_96 *
rtb_B_128_2144_16520 ; } } dVOC_monitor_network1_Subsystem1 ( S , _rtB ->
B_136_1238_9862 , & _rtB -> B_136_37_296 [ 0 ] , _rtB -> B_136_14_112 , &
_rtB -> Subsystem1_i , & _rtDW -> Subsystem1_i ) ;
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1239_9863 , &
_rtB -> B_136_37_296 [ 0 ] , _rtB -> B_136_14_112 , & _rtB ->
Subsystempi2delay_b , & _rtDW -> Subsystempi2delay_b ) ; if ( _rtB ->
B_136_1238_9862 != 0 ) { _rtB -> B_136_40_320 [ 0 ] = _rtB -> Subsystem1_i .
B_25_1750_13368 ; _rtB -> B_136_40_320 [ 1 ] = _rtB -> Subsystem1_i .
B_25_1751_13376 ; } else { _rtB -> B_136_40_320 [ 0 ] = _rtB ->
Subsystempi2delay_b . B_24_1752_13384 ; _rtB -> B_136_40_320 [ 1 ] = _rtB ->
Subsystempi2delay_b . B_24_1753_13392 ; } _rtB -> B_136_42_336 = _rtB ->
B_136_36_288 - _rtB -> B_136_40_320 [ 0 ] ; rtb_B_128_2144_16520 = _rtP ->
P_99 * _rtB -> B_136_26_208 ; B_136_1771_13536 = ( ( _rtP -> P_97 * _rtB ->
B_136_42_336 + _rtB -> B_136_8_64 ) * _rtP -> P_98 - _rtB -> B_136_40_320 [ 1
] * rtb_B_128_2144_16520 ) + _rtP -> P_100 * _rtB -> B_136_15_120 [ 0 ] ;
_rtB -> B_136_43_344 = _rtX -> Integrator1_CSTATE_m ; _rtB -> B_136_44_352 =
_rtP -> P_103 * _rtB -> B_136_33_264 [ 1 ] ; _rtB -> B_136_45_360 = _rtB ->
B_136_15_120 [ 0 ] * _rtB -> B_136_27_216 ; _rtB -> B_136_46_368 = _rtX ->
Integrator1_CSTATE_f ; _rtB -> B_136_47_376 = _rtB -> B_136_870_6960 - _rtB
-> B_136_15_120 [ 1 ] ; _rtB -> B_136_48_384 = _rtP -> P_105 * _rtB ->
B_136_47_376 ; _rtB -> B_136_49_392 = _rtB -> B_136_46_368 + _rtB ->
B_136_48_384 ; _rtB -> B_136_50_400 = _rtP -> P_106 * _rtB -> B_136_49_392 ;
_rtB -> B_136_51_408 = _rtB -> B_136_45_360 + _rtB -> B_136_50_400 ; _rtB ->
B_136_52_416 = _rtB -> B_136_44_352 + _rtB -> B_136_51_408 ; _rtB ->
B_136_53_424 = _rtB -> B_136_52_416 - _rtB -> B_136_40_320 [ 1 ] ;
B_136_1778_13592 = ( ( _rtP -> P_107 * _rtB -> B_136_53_424 + _rtB ->
B_136_43_344 ) * _rtP -> P_108 + rtb_B_128_2144_16520 * _rtB -> B_136_40_320
[ 0 ] ) + _rtP -> P_101 * _rtB -> B_136_15_120 [ 1 ] ;
dVOC_monitor_network1_Subsystem1_b ( S , _rtB -> B_136_1244_9868 ,
B_136_1771_13536 , B_136_1778_13592 , _rtB -> B_136_14_112 , & _rtB ->
Subsystem1_b , & _rtDW -> Subsystem1_b ) ;
dVOC_monitor_network1_Subsystempi2delay_o ( S , _rtB -> B_136_1245_9869 ,
B_136_1771_13536 , B_136_1778_13592 , _rtB -> B_136_14_112 , & _rtB ->
Subsystempi2delay_o , & _rtDW -> Subsystempi2delay_o ) ; if ( _rtB ->
B_136_1244_9868 != 0 ) { rtb_B_128_2144_16520 = _rtB -> Subsystem1_b .
B_37_1726_13176 ; B_136_1814_13880_idx_1 = _rtB -> Subsystem1_b .
B_37_1727_13184 ; } else { rtb_B_128_2144_16520 = _rtB -> Subsystempi2delay_o
. B_36_1728_13192 ; B_136_1814_13880_idx_1 = _rtB -> Subsystempi2delay_o .
B_36_1729_13200 ; } for ( i = 0 ; i < 3 ; i ++ ) { rtb_B_128_2256_17416 [ i ]
= ( ( _rtP -> P_109 [ i + 3 ] * B_136_1814_13880_idx_1 + _rtP -> P_109 [ i ]
* rtb_B_128_2144_16520 ) + _rtP -> P_109 [ i + 6 ] * _rtB -> B_136_863_6904 )
* _rtP -> P_110 ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtB ->
B_136_54_432 = _rtDW -> Vdc_DSTATE ; _rtB -> B_136_55_440 = _rtP -> P_112 *
_rtB -> B_136_54_432 ; } rtb_B_128_2256_17416 [ 0 ] *= _rtB -> B_136_55_440 ;
rtb_B_128_2256_17416 [ 1 ] *= _rtB -> B_136_55_440 ; rtb_B_128_2256_17416 [ 2
] *= _rtB -> B_136_55_440 ; _rtB -> B_136_56_448 = rtb_B_128_2256_17416 [ 0 ]
- rtb_B_128_2256_17416 [ 1 ] ; _rtB -> B_136_57_456 = rtb_B_128_2256_17416 [
1 ] - rtb_B_128_2256_17416 [ 2 ] ; i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i
!= 0 ) { _rtB -> B_136_58_464 = _rtDW -> Idc_DSTATE ; } _rtB -> B_136_59_472
= _rtX -> Integrator_CSTATE_n ; _rtB -> B_136_60_480 = _rtX ->
Integrator_CSTATE_p ; _rtB -> B_136_61_488 = _rtX -> Integrator1_CSTATE_i ; i
= ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { for ( i = 0 ; i < 3 ; i ++ )
{ rtb_B_136_2267_17504 [ i ] = _rtDW -> Memory2_PreviousInput_p [ i ] ;
rtb_B_128_2144_16520 = ( _rtP -> P_118 [ i + 3 ] * _rtDW ->
Memory2_PreviousInput_p [ 1 ] + _rtP -> P_118 [ i ] * _rtDW ->
Memory2_PreviousInput_p [ 0 ] ) + _rtP -> P_118 [ i + 6 ] * _rtDW ->
Memory2_PreviousInput_p [ 2 ] ; rtb_B_136_2339_18080 [ i ] =
rtb_B_128_2144_16520 ; _rtB -> B_136_62_496 [ i ] = _rtP -> P_119 *
rtb_B_128_2144_16520 ; } } _rtB -> B_136_65_520 = _rtX ->
Integrator3_CSTATE_o ; dVOC_monitor_network1_Subsystem1 ( S , _rtB ->
B_136_1256_9880 , & _rtB -> B_136_62_496 [ 0 ] , _rtB -> B_136_65_520 , &
_rtB -> Subsystem1_k , & _rtDW -> Subsystem1_k ) ;
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1257_9881 , &
_rtB -> B_136_62_496 [ 0 ] , _rtB -> B_136_65_520 , & _rtB ->
Subsystempi2delay_bp , & _rtDW -> Subsystempi2delay_bp ) ; if ( _rtB ->
B_136_1256_9880 != 0 ) { _rtB -> B_136_66_528 [ 0 ] = _rtB -> Subsystem1_k .
B_25_1750_13368 ; _rtB -> B_136_66_528 [ 1 ] = _rtB -> Subsystem1_k .
B_25_1751_13376 ; } else { _rtB -> B_136_66_528 [ 0 ] = _rtB ->
Subsystempi2delay_bp . B_24_1752_13384 ; _rtB -> B_136_66_528 [ 1 ] = _rtB ->
Subsystempi2delay_bp . B_24_1753_13392 ; } _rtB -> B_136_68_544 = _rtB ->
B_136_61_488 - _rtB -> B_136_66_528 [ 0 ] ; _rtB -> B_136_69_552 = _rtP ->
P_121 * _rtB -> B_136_68_544 ; _rtB -> B_136_70_560 = _rtB -> B_136_60_480 +
_rtB -> B_136_69_552 ; _rtB -> B_136_71_568 = _rtP -> P_122 * _rtB ->
B_136_70_560 ; _rtB -> B_136_72_576 = 0.0 ; _rtB -> B_136_72_576 += _rtP ->
P_124 * _rtX -> TransferFcn4_CSTATE_m ; _rtB -> B_136_73_584 = _rtB ->
B_136_61_488 * _rtB -> B_136_61_488 + _rtB -> B_136_876_7008 ; _rtB ->
B_136_74_592 = _rtB -> B_136_72_576 / _rtB -> B_136_73_584 ; _rtB ->
B_136_75_600 = _rtB -> B_136_877_7016 - _rtB -> B_136_74_592 ; _rtB ->
B_136_76_608 = _rtP -> P_125 * _rtB -> B_136_75_600 ; _rtB -> B_136_77_616 =
_rtB -> B_136_872_6976 + _rtB -> B_136_76_608 ; _rtB -> B_136_78_624 = _rtP
-> P_126 * _rtB -> B_136_77_616 ; _rtB -> B_136_79_632 = _rtB -> B_136_66_528
[ 1 ] * _rtB -> B_136_78_624 ; _rtB -> B_136_80_640 = _rtB -> B_136_71_568 -
_rtB -> B_136_79_632 ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { for
( i = 0 ; i < 3 ; i ++ ) { rtb_B_136_2339_18080 [ i ] = _rtDW ->
Memory3_PreviousInput_b [ i ] ; _rtB -> B_136_81_648 [ i ] = ( ( _rtP ->
P_128 [ i + 3 ] * _rtDW -> Memory3_PreviousInput_b [ 1 ] + _rtP -> P_128 [ i
] * _rtDW -> Memory3_PreviousInput_b [ 0 ] ) + _rtP -> P_128 [ i + 6 ] *
_rtDW -> Memory3_PreviousInput_b [ 2 ] ) * _rtP -> P_129 ; } }
dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1250_9874 , & _rtB ->
B_136_81_648 [ 0 ] , _rtB -> B_136_65_520 , & _rtB -> Subsystem1_c , & _rtDW
-> Subsystem1_c ) ; dVOC_monitor_network1_Subsystempi2delay ( S , _rtB ->
B_136_1251_9875 , & _rtB -> B_136_81_648 [ 0 ] , _rtB -> B_136_65_520 , &
_rtB -> Subsystempi2delay_g , & _rtDW -> Subsystempi2delay_g ) ; if ( _rtB ->
B_136_1250_9874 != 0 ) { _rtB -> B_136_84_672 [ 0 ] = _rtB -> Subsystem1_c .
B_25_1750_13368 ; _rtB -> B_136_84_672 [ 1 ] = _rtB -> Subsystem1_c .
B_25_1751_13376 ; } else { _rtB -> B_136_84_672 [ 0 ] = _rtB ->
Subsystempi2delay_g . B_24_1752_13384 ; _rtB -> B_136_84_672 [ 1 ] = _rtB ->
Subsystempi2delay_g . B_24_1753_13392 ; } _rtB -> B_136_86_688 = _rtP ->
P_130 * _rtB -> B_136_84_672 [ 0 ] ; _rtB -> B_136_87_696 = _rtB ->
B_136_80_640 + _rtB -> B_136_86_688 ; i = ssIsSampleHit ( S , 1 , 0 ) ; if (
i != 0 ) { rtb_B_128_2144_16520 = _rtDW -> Memory1_PreviousInput_m [ 1 ] ;
B_136_1814_13880_idx_1 = _rtDW -> Memory1_PreviousInput_m [ 0 ] ;
rtb_B_136_1817_13904 = _rtDW -> Memory1_PreviousInput_m [ 2 ] ; for ( i = 0 ;
i < 3 ; i ++ ) { _rtB -> B_136_88_704 [ i ] = ( ( _rtP -> P_132 [ i + 3 ] *
rtb_B_128_2144_16520 + _rtP -> P_132 [ i ] * B_136_1814_13880_idx_1 ) + _rtP
-> P_132 [ i + 6 ] * rtb_B_136_1817_13904 ) * _rtP -> P_133 ; } }
dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1252_9876 , & _rtB ->
B_136_88_704 [ 0 ] , _rtB -> B_136_65_520 , & _rtB -> Subsystem1_h , & _rtDW
-> Subsystem1_h ) ; dVOC_monitor_network1_Subsystempi2delay ( S , _rtB ->
B_136_1253_9877 , & _rtB -> B_136_88_704 [ 0 ] , _rtB -> B_136_65_520 , &
_rtB -> Subsystempi2delay_ct , & _rtDW -> Subsystempi2delay_ct ) ; if ( _rtB
-> B_136_1252_9876 != 0 ) { _rtB -> B_136_91_728 [ 0 ] = _rtB -> Subsystem1_h
. B_25_1750_13368 ; _rtB -> B_136_91_728 [ 1 ] = _rtB -> Subsystem1_h .
B_25_1751_13376 ; } else { _rtB -> B_136_91_728 [ 0 ] = _rtB ->
Subsystempi2delay_ct . B_24_1752_13384 ; _rtB -> B_136_91_728 [ 1 ] = _rtB ->
Subsystempi2delay_ct . B_24_1753_13392 ; } _rtB -> B_136_93_744 = _rtB ->
B_136_87_696 - _rtB -> B_136_91_728 [ 0 ] ; rtb_B_128_2144_16520 = _rtP ->
P_136 * _rtB -> B_136_77_616 ; B_136_1792_13704 = ( ( _rtP -> P_134 * _rtB ->
B_136_93_744 + _rtB -> B_136_59_472 ) * _rtP -> P_135 - _rtB -> B_136_91_728
[ 1 ] * rtb_B_128_2144_16520 ) + _rtP -> P_137 * _rtB -> B_136_66_528 [ 0 ] ;
_rtB -> B_136_94_752 = _rtX -> Integrator1_CSTATE_g ; _rtB -> B_136_95_760 =
_rtP -> P_140 * _rtB -> B_136_84_672 [ 1 ] ; _rtB -> B_136_96_768 = _rtB ->
B_136_66_528 [ 0 ] * _rtB -> B_136_78_624 ; _rtB -> B_136_97_776 = _rtX ->
Integrator1_CSTATE_b ; _rtB -> B_136_98_784 = _rtB -> B_136_881_7048 - _rtB
-> B_136_66_528 [ 1 ] ; _rtB -> B_136_99_792 = _rtP -> P_142 * _rtB ->
B_136_98_784 ; _rtB -> B_136_100_800 = _rtB -> B_136_97_776 + _rtB ->
B_136_99_792 ; _rtB -> B_136_101_808 = _rtP -> P_143 * _rtB -> B_136_100_800
; _rtB -> B_136_102_816 = _rtB -> B_136_96_768 + _rtB -> B_136_101_808 ; _rtB
-> B_136_103_824 = _rtB -> B_136_95_760 + _rtB -> B_136_102_816 ; _rtB ->
B_136_104_832 = _rtB -> B_136_103_824 - _rtB -> B_136_91_728 [ 1 ] ;
B_136_1799_13760 = ( ( _rtP -> P_144 * _rtB -> B_136_104_832 + _rtB ->
B_136_94_752 ) * _rtP -> P_145 + rtb_B_128_2144_16520 * _rtB -> B_136_91_728
[ 0 ] ) + _rtP -> P_138 * _rtB -> B_136_66_528 [ 1 ] ;
dVOC_monitor_network1_Subsystem1_b ( S , _rtB -> B_136_1258_9882 ,
B_136_1792_13704 , B_136_1799_13760 , _rtB -> B_136_65_520 , & _rtB ->
Subsystem1_o , & _rtDW -> Subsystem1_o ) ;
dVOC_monitor_network1_Subsystempi2delay_o ( S , _rtB -> B_136_1259_9883 ,
B_136_1792_13704 , B_136_1799_13760 , _rtB -> B_136_65_520 , & _rtB ->
Subsystempi2delay_dn , & _rtDW -> Subsystempi2delay_dn ) ; if ( _rtB ->
B_136_1258_9882 != 0 ) { rtb_B_128_2144_16520 = _rtB -> Subsystem1_o .
B_37_1726_13176 ; B_136_1814_13880_idx_1 = _rtB -> Subsystem1_o .
B_37_1727_13184 ; } else { rtb_B_128_2144_16520 = _rtB ->
Subsystempi2delay_dn . B_36_1728_13192 ; B_136_1814_13880_idx_1 = _rtB ->
Subsystempi2delay_dn . B_36_1729_13200 ; } for ( i = 0 ; i < 3 ; i ++ ) {
rtb_B_128_2256_17416 [ i ] = ( ( _rtP -> P_146 [ i + 3 ] *
B_136_1814_13880_idx_1 + _rtP -> P_146 [ i ] * rtb_B_128_2144_16520 ) + _rtP
-> P_146 [ i + 6 ] * _rtB -> B_136_874_6992 ) * _rtP -> P_147 ; } i =
ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtB -> B_136_105_840 = _rtDW
-> Vdc_DSTATE_j ; _rtB -> B_136_106_848 = _rtP -> P_149 * _rtB ->
B_136_105_840 ; } rtb_B_128_2256_17416 [ 0 ] *= _rtB -> B_136_106_848 ;
rtb_B_128_2256_17416 [ 1 ] *= _rtB -> B_136_106_848 ; rtb_B_128_2256_17416 [
2 ] *= _rtB -> B_136_106_848 ; _rtB -> B_136_107_856 = rtb_B_128_2256_17416 [
0 ] - rtb_B_128_2256_17416 [ 1 ] ; _rtB -> B_136_108_864 =
rtb_B_128_2256_17416 [ 1 ] - rtb_B_128_2256_17416 [ 2 ] ; i = ssIsSampleHit (
S , 2 , 0 ) ; if ( i != 0 ) { _rtB -> B_136_109_872 = _rtDW -> Idc_DSTATE_j ;
} _rtB -> B_136_110_880 = 0.0 ; for ( ri = _rtP -> P_962 [ 0U ] ; ri < _rtP
-> P_962 [ 1U ] ; ri ++ ) { _rtB -> B_136_110_880 += _rtP -> P_153 * _rtX ->
Internal_CSTATE ; } if ( ssIsModeUpdateTimeStep ( S ) ) { if ( _rtB ->
B_136_110_880 >= _rtP -> P_155 ) { _rtDW -> Saturation_MODE = 1 ; } else if (
_rtB -> B_136_110_880 > _rtP -> P_156 ) { _rtDW -> Saturation_MODE = 0 ; }
else { _rtDW -> Saturation_MODE = - 1 ; } } if ( _rtDW -> Saturation_MODE ==
1 ) { _rtB -> B_136_111_888 = _rtP -> P_155 ; } else if ( _rtDW ->
Saturation_MODE == - 1 ) { _rtB -> B_136_111_888 = _rtP -> P_156 ; } else {
_rtB -> B_136_111_888 = _rtB -> B_136_110_880 ; } _rtB -> B_136_112_896 =
ssGetT ( S ) ; if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> Switch_Mode = (
_rtB -> B_136_112_896 > _rtP -> P_157 ) ; } if ( _rtDW -> Switch_Mode ) {
_rtB -> B_136_113_904 = _rtB -> B_136_111_888 ; } else { _rtB ->
B_136_113_904 = _rtB -> B_136_110_880 ; } _rtB -> B_136_114_912 = 0.0 ; for (
ri = _rtP -> P_968 [ 0U ] ; ri < _rtP -> P_968 [ 1U ] ; ri ++ ) { _rtB ->
B_136_114_912 += _rtP -> P_160 * _rtX -> Internal_CSTATE_n ; } if (
ssIsModeUpdateTimeStep ( S ) ) { if ( _rtB -> B_136_114_912 >= _rtP -> P_162
) { _rtDW -> Saturation_MODE_c = 1 ; } else if ( _rtB -> B_136_114_912 > _rtP
-> P_163 ) { _rtDW -> Saturation_MODE_c = 0 ; } else { _rtDW ->
Saturation_MODE_c = - 1 ; } } if ( _rtDW -> Saturation_MODE_c == 1 ) { _rtB
-> B_136_115_920 = _rtP -> P_162 ; } else if ( _rtDW -> Saturation_MODE_c ==
- 1 ) { _rtB -> B_136_115_920 = _rtP -> P_163 ; } else { _rtB ->
B_136_115_920 = _rtB -> B_136_114_912 ; } _rtB -> B_136_116_928 = ssGetT ( S
) ; if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> Switch_Mode_b = ( _rtB ->
B_136_116_928 > _rtP -> P_164 ) ; } if ( _rtDW -> Switch_Mode_b ) { _rtB ->
B_136_117_936 = _rtB -> B_136_115_920 ; } else { _rtB -> B_136_117_936 = _rtB
-> B_136_114_912 ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
ssCallAccelRunBlock ( S , 136 , 176 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_136_209_1672 = _rtDW -> dw_delay_DSTATE ; _rtB -> B_136_210_1680 = _rtP ->
P_176 * _rtB -> B_136_209_1672 - _rtDW -> dw_predict_DSTATE ;
rtb_B_136_1807_13824 = _rtB -> B_136_996_7968 + _rtB -> B_136_210_1680 ;
rtb_B_136_1808_13832 = _rtP -> P_178 * rtb_B_136_1807_13824 ; _rtB ->
B_136_211_1688 = _rtP -> P_179 * rtb_B_136_1808_13832 ; } _rtB ->
B_136_212_1696 = _rtP -> P_180 * _rtB -> B_136_26_208 ; _rtB ->
B_136_213_1704 = _rtP -> P_181 * _rtB -> B_136_77_616 ; _rtB ->
B_136_1223_9784 [ 0 ] = _rtB -> B_136_211_1688 ; _rtB -> B_136_1223_9784 [ 1
] = _rtB -> B_136_212_1696 ; _rtB -> B_136_1223_9784 [ 2 ] = _rtB ->
B_136_213_1704 ; i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { if ( _rtB
-> B_136_939_7512 >= _rtP -> P_183 ) { B_127_2177_16784_idx_0 = _rtB ->
B_128_1118_8944 ; B_127_2177_16784_idx_1 = _rtB -> B_128_1065_8520 ; } else {
B_127_2177_16784_idx_0 = _rtB -> B_136_940_7520 [ 0 ] ;
B_127_2177_16784_idx_1 = _rtB -> B_136_940_7520 [ 1 ] ; }
rtb_B_128_2144_16520 = _rtP -> P_182 [ 0 ] * _rtB -> B_136_0_0 [ 0 ] *
B_127_2177_16784_idx_0 ; B_136_1814_13880_idx_1 = _rtP -> P_182 [ 1 ] * _rtB
-> B_136_0_0 [ 4 ] * B_127_2177_16784_idx_0 ; rtb_B_136_1817_13904 = ( _rtP
-> P_184 [ 0 ] * _rtB -> B_136_0_0 [ 1 ] * B_127_2177_16784_idx_1 + _rtP ->
P_184 [ 1 ] * _rtB -> B_136_0_0 [ 2 ] * B_127_2177_16784_idx_1 ) + _rtP ->
P_184 [ 2 ] * _rtB -> B_136_0_0 [ 3 ] * B_127_2177_16784_idx_1 ;
B_127_2177_16784_idx_0 = _rtP -> P_185 * _rtB -> B_136_118_944 [ 15 ] ;
B_127_2177_16784_idx_1 = _rtP -> P_185 * _rtB -> B_136_118_944 [ 16 ] ; _rtB
-> B_136_214_1712 = ( ( 2.0 * B_127_2177_16784_idx_0 + B_127_2177_16784_idx_1
) * rtb_B_136_1759_13440 + 1.7320508075688772 * B_127_2177_16784_idx_1 *
rtb_B_136_1758_13432 ) * 0.33333333333333331 ; _rtB -> B_136_215_1720 = ( (
2.0 * B_127_2177_16784_idx_0 + B_127_2177_16784_idx_1 ) *
rtb_B_136_1758_13432 + - 1.7320508075688772 * B_127_2177_16784_idx_1 *
rtb_B_136_1759_13440 ) * 0.33333333333333331 ; _rtB -> B_136_216_1728 [ 0 ] =
_rtP -> P_190 [ 0 ] * rtb_B_127_2182_16824 ; _rtB -> B_136_216_1728 [ 1 ] =
_rtP -> P_190 [ 1 ] * rtb_B_127_2179_16800 ; _rtB -> B_136_216_1728 [ 2 ] =
_rtP -> P_190 [ 2 ] * rtb_B_128_2147_16544 ; _rtB -> B_136_216_1728 [ 3 ] =
rtb_B_136_2259_17440 [ 0 ] * _rtP -> P_190 [ 3 ] ; _rtB -> B_136_216_1728 [ 4
] = rtb_B_136_2259_17440 [ 1 ] * _rtP -> P_190 [ 4 ] ; _rtB -> B_136_216_1728
[ 5 ] = rtb_B_136_2259_17440 [ 2 ] * _rtP -> P_190 [ 5 ] ; _rtB ->
B_136_216_1728 [ 6 ] = rtb_B_136_2259_17440 [ 4 ] * _rtP -> P_190 [ 6 ] ; if
( _rtB -> B_136_1298_9922 ) { rtb_B_128_2147_16544 = rtb_B_136_2259_17440 [ 0
] ; } else { rtb_B_128_2147_16544 = _rtB -> B_136_884_7072 ; } _rtB ->
B_136_216_1728 [ 7 ] = _rtP -> P_190 [ 7 ] * rtb_B_128_2147_16544 ; _rtB ->
B_136_216_1728 [ 8 ] = rtb_B_136_2259_17440 [ 3 ] * _rtP -> P_190 [ 8 ] ;
_rtB -> B_136_216_1728 [ 9 ] = ( rtb_B_128_2144_16520 +
B_136_1814_13880_idx_1 ) * _rtP -> P_190 [ 9 ] ; _rtB -> B_136_216_1728 [ 10
] = _rtP -> P_190 [ 10 ] * rtb_B_136_1817_13904 ; _rtB -> B_136_216_1728 [ 11
] = _rtP -> P_190 [ 11 ] * _rtB -> B_136_214_1712 ; _rtB -> B_136_216_1728 [
12 ] = _rtP -> P_190 [ 12 ] * _rtB -> B_136_215_1720 ; if ( _rtB ->
B_136_913_7304 >= _rtP -> P_186 ) { rtb_B_128_2147_16544 = _rtB ->
B_128_1067_8536 ; } else { rtb_B_128_2147_16544 = _rtB -> B_136_942_7536 [ 0
] ; } _rtB -> B_136_216_1728 [ 13 ] = _rtP -> P_190 [ 13 ] *
rtb_B_128_2147_16544 ; if ( _rtB -> B_136_913_7304 >= _rtP -> P_186 ) {
rtb_B_128_2147_16544 = _rtB -> B_128_1066_8528 ; } else {
rtb_B_128_2147_16544 = _rtB -> B_136_942_7536 [ 1 ] ; } _rtB ->
B_136_216_1728 [ 14 ] = _rtP -> P_190 [ 14 ] * rtb_B_128_2147_16544 ; _rtB ->
B_136_216_1728 [ 15 ] = _rtP -> P_187 * muDoubleScalarAtan2 ( _rtB ->
B_136_215_1720 , _rtB -> B_136_214_1712 ) * _rtP -> P_190 [ 15 ] ; _rtB ->
B_136_216_1728 [ 16 ] = ( _rtB -> B_136_214_1712 * rtb_B_136_2259_17440 [ 0 ]
+ _rtB -> B_136_215_1720 * rtb_B_136_2259_17440 [ 1 ] ) * _rtP -> P_188 *
_rtP -> P_190 [ 16 ] ; _rtB -> B_136_216_1728 [ 17 ] = ( _rtB ->
B_136_214_1712 * rtb_B_136_2259_17440 [ 1 ] - _rtB -> B_136_215_1720 *
rtb_B_136_2259_17440 [ 0 ] ) * _rtP -> P_189 * _rtP -> P_190 [ 17 ] ; } i =
ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { rtb_B_136_1758_13432 =
rtb_B_136_2214_17080 [ 1 ] ; rtb_B_136_1759_13440 = rtb_B_136_2214_17080 [ 0
] ; rtb_B_128_2147_16544 = rtb_B_136_2214_17080 [ 2 ] ; for ( i = 0 ; i < 3 ;
i ++ ) { _rtB -> B_136_234_1872 [ i ] = ( ( _rtP -> P_191 [ i + 3 ] *
rtb_B_136_1758_13432 + _rtP -> P_191 [ i ] * rtb_B_136_1759_13440 ) + _rtP ->
P_191 [ i + 6 ] * rtb_B_128_2147_16544 ) * _rtP -> P_192 ; } }
dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1234_9858 , & _rtB ->
B_136_234_1872 [ 0 ] , _rtB -> B_136_14_112 , & _rtB -> Subsystem1_g , &
_rtDW -> Subsystem1_g ) ; dVOC_monitor_network1_Subsystempi2delay ( S , _rtB
-> B_136_1235_9859 , & _rtB -> B_136_234_1872 [ 0 ] , _rtB -> B_136_14_112 ,
& _rtB -> Subsystempi2delay_c , & _rtDW -> Subsystempi2delay_c ) ; if ( _rtB
-> B_136_1234_9858 != 0 ) { _rtB -> B_136_237_1896 [ 0 ] = _rtB ->
Subsystem1_g . B_25_1750_13368 ; _rtB -> B_136_237_1896 [ 1 ] = _rtB ->
Subsystem1_g . B_25_1751_13376 ; } else { _rtB -> B_136_237_1896 [ 0 ] = _rtB
-> Subsystempi2delay_c . B_24_1752_13384 ; _rtB -> B_136_237_1896 [ 1 ] =
_rtB -> Subsystempi2delay_c . B_24_1753_13392 ; } i = ssIsSampleHit ( S , 1 ,
0 ) ; if ( i != 0 ) { rtb_B_128_2144_16520 = rtb_B_136_2264_17480 [ 1 ] ;
rtb_B_136_1758_13432 = rtb_B_136_2264_17480 [ 0 ] ; rtb_B_136_1759_13440 =
rtb_B_136_2264_17480 [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) { _rtB ->
B_136_239_1912 [ i ] = ( ( _rtP -> P_193 [ i + 3 ] * rtb_B_128_2144_16520 +
_rtP -> P_193 [ i ] * rtb_B_136_1758_13432 ) + _rtP -> P_193 [ i + 6 ] *
rtb_B_136_1759_13440 ) * _rtP -> P_194 ; } } dVOC_monitor_network1_Subsystem1
( S , _rtB -> B_136_1232_9856 , & _rtB -> B_136_239_1912 [ 0 ] , _rtB ->
B_136_14_112 , & _rtB -> Subsystem1 , & _rtDW -> Subsystem1 ) ;
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1233_9857 , &
_rtB -> B_136_239_1912 [ 0 ] , _rtB -> B_136_14_112 , & _rtB ->
Subsystempi2delay , & _rtDW -> Subsystempi2delay ) ; if ( _rtB ->
B_136_1232_9856 != 0 ) { _rtB -> B_136_242_1936 [ 0 ] = _rtB -> Subsystem1 .
B_25_1750_13368 ; _rtB -> B_136_242_1936 [ 1 ] = _rtB -> Subsystem1 .
B_25_1751_13376 ; } else { _rtB -> B_136_242_1936 [ 0 ] = _rtB ->
Subsystempi2delay . B_24_1752_13384 ; _rtB -> B_136_242_1936 [ 1 ] = _rtB ->
Subsystempi2delay . B_24_1753_13392 ; } _rtB -> B_136_244_1952 = _rtB ->
B_136_237_1896 [ 0 ] * _rtB -> B_136_242_1936 [ 0 ] ; _rtB -> B_136_245_1960
= _rtB -> B_136_237_1896 [ 1 ] * _rtB -> B_136_242_1936 [ 1 ] ; i =
ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_136_246_1968 = _rtB
-> B_136_234_1872 [ 2 ] * _rtB -> B_136_239_1912 [ 2 ] * _rtP -> P_195 ; }
_rtB -> B_136_247_1976 = ( _rtB -> B_136_244_1952 + _rtB -> B_136_245_1960 )
+ _rtB -> B_136_246_1968 ; _rtB -> B_136_248_1984 = _rtP -> P_196 * _rtB ->
B_136_247_1976 ; _rtB -> B_136_249_1992 = _rtP -> P_197 * _rtB ->
B_136_248_1984 ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) {
rtb_B_128_2144_16520 = rtb_B_136_2267_17504 [ 1 ] ; rtb_B_136_1758_13432 =
rtb_B_136_2267_17504 [ 0 ] ; rtb_B_136_1759_13440 = rtb_B_136_2267_17504 [ 2
] ; for ( i = 0 ; i < 3 ; i ++ ) { _rtB -> B_136_250_2000 [ i ] = ( ( _rtP ->
P_198 [ i + 3 ] * rtb_B_128_2144_16520 + _rtP -> P_198 [ i ] *
rtb_B_136_1758_13432 ) + _rtP -> P_198 [ i + 6 ] * rtb_B_136_1759_13440 ) *
_rtP -> P_199 ; } } dVOC_monitor_network1_Subsystem1 ( S , _rtB ->
B_136_1248_9872 , & _rtB -> B_136_250_2000 [ 0 ] , _rtB -> B_136_65_520 , &
_rtB -> Subsystem1_d , & _rtDW -> Subsystem1_d ) ;
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1249_9873 , &
_rtB -> B_136_250_2000 [ 0 ] , _rtB -> B_136_65_520 , & _rtB ->
Subsystempi2delay_d , & _rtDW -> Subsystempi2delay_d ) ; if ( _rtB ->
B_136_1248_9872 != 0 ) { _rtB -> B_136_253_2024 [ 0 ] = _rtB -> Subsystem1_d
. B_25_1750_13368 ; _rtB -> B_136_253_2024 [ 1 ] = _rtB -> Subsystem1_d .
B_25_1751_13376 ; } else { _rtB -> B_136_253_2024 [ 0 ] = _rtB ->
Subsystempi2delay_d . B_24_1752_13384 ; _rtB -> B_136_253_2024 [ 1 ] = _rtB
-> Subsystempi2delay_d . B_24_1753_13392 ; } i = ssIsSampleHit ( S , 1 , 0 )
; if ( i != 0 ) { rtb_B_128_2144_16520 = rtb_B_136_2339_18080 [ 1 ] ;
rtb_B_136_1758_13432 = rtb_B_136_2339_18080 [ 0 ] ; rtb_B_136_1759_13440 =
rtb_B_136_2339_18080 [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) { _rtB ->
B_136_255_2040 [ i ] = ( ( _rtP -> P_200 [ i + 3 ] * rtb_B_128_2144_16520 +
_rtP -> P_200 [ i ] * rtb_B_136_1758_13432 ) + _rtP -> P_200 [ i + 6 ] *
rtb_B_136_1759_13440 ) * _rtP -> P_201 ; } } dVOC_monitor_network1_Subsystem1
( S , _rtB -> B_136_1246_9870 , & _rtB -> B_136_255_2040 [ 0 ] , _rtB ->
B_136_65_520 , & _rtB -> Subsystem1_pc , & _rtDW -> Subsystem1_pc ) ;
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1247_9871 , &
_rtB -> B_136_255_2040 [ 0 ] , _rtB -> B_136_65_520 , & _rtB ->
Subsystempi2delay_hz , & _rtDW -> Subsystempi2delay_hz ) ; if ( _rtB ->
B_136_1246_9870 != 0 ) { _rtB -> B_136_258_2064 [ 0 ] = _rtB -> Subsystem1_pc
. B_25_1750_13368 ; _rtB -> B_136_258_2064 [ 1 ] = _rtB -> Subsystem1_pc .
B_25_1751_13376 ; } else { _rtB -> B_136_258_2064 [ 0 ] = _rtB ->
Subsystempi2delay_hz . B_24_1752_13384 ; _rtB -> B_136_258_2064 [ 1 ] = _rtB
-> Subsystempi2delay_hz . B_24_1753_13392 ; } _rtB -> B_136_260_2080 = _rtB
-> B_136_253_2024 [ 0 ] * _rtB -> B_136_258_2064 [ 0 ] ; _rtB ->
B_136_261_2088 = _rtB -> B_136_253_2024 [ 1 ] * _rtB -> B_136_258_2064 [ 1 ]
; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_136_262_2096 =
_rtB -> B_136_250_2000 [ 2 ] * _rtB -> B_136_255_2040 [ 2 ] * _rtP -> P_202 ;
} _rtB -> B_136_263_2104 = ( _rtB -> B_136_260_2080 + _rtB -> B_136_261_2088
) + _rtB -> B_136_262_2096 ; _rtB -> B_136_264_2112 = _rtP -> P_203 * _rtB ->
B_136_263_2104 ; _rtB -> B_136_265_2120 = _rtP -> P_204 * _rtB ->
B_136_264_2112 ; _rtB -> B_136_1226_9808 [ 0 ] = _rtB -> B_136_216_1728 [ 16
] ; _rtB -> B_136_1226_9808 [ 1 ] = _rtB -> B_136_249_1992 ; _rtB ->
B_136_1226_9808 [ 2 ] = _rtB -> B_136_265_2120 ; i = ssIsSampleHit ( S , 2 ,
0 ) ; if ( i != 0 ) { rtb_B_136_1758_13432 = muDoubleScalarPower ( _rtB ->
B_136_216_1728 [ 11 ] , 2.0 ) + muDoubleScalarPower ( _rtB -> B_136_216_1728
[ 12 ] , 2.0 ) ; _rtB -> B_136_266_2128 = muDoubleScalarSqrt (
rtb_B_136_1758_13432 ) ; } rtb_B_136_1758_13432 = _rtB -> B_136_15_120 [ 0 ]
* _rtB -> B_136_15_120 [ 0 ] ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0
) { _rtB -> B_136_267_2136 = _rtB -> B_136_11_88 [ 2 ] * _rtB -> B_136_11_88
[ 2 ] ; } rtb_B_136_1758_13432 = ( _rtB -> B_136_15_120 [ 1 ] * _rtB ->
B_136_15_120 [ 1 ] + rtb_B_136_1758_13432 ) + _rtB -> B_136_267_2136 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { if ( _rtDW -> Sqrt2_DWORK1 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; _rtDW ->
Sqrt2_DWORK1 = 0 ; } rtb_B_136_1759_13440 = muDoubleScalarSqrt (
rtb_B_136_1758_13432 ) ; } else if ( rtb_B_136_1758_13432 < 0.0 ) {
rtb_B_136_1759_13440 = - muDoubleScalarSqrt ( muDoubleScalarAbs (
rtb_B_136_1758_13432 ) ) ; _rtDW -> Sqrt2_DWORK1 = 1 ; } else {
rtb_B_136_1759_13440 = muDoubleScalarSqrt ( rtb_B_136_1758_13432 ) ; }
rtb_B_136_1758_13432 = _rtP -> P_205 * rtb_B_136_1759_13440 ; i =
ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_136_268_2144 = _rtB
-> B_136_62_496 [ 2 ] * _rtB -> B_136_62_496 [ 2 ] ; } rtb_B_136_1759_13440 =
( _rtB -> B_136_66_528 [ 0 ] * _rtB -> B_136_66_528 [ 0 ] + _rtB ->
B_136_66_528 [ 1 ] * _rtB -> B_136_66_528 [ 1 ] ) + _rtB -> B_136_268_2144 ;
if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( _rtDW -> Sqrt2_DWORK1_h != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; _rtDW ->
Sqrt2_DWORK1_h = 0 ; } rtb_B_136_1759_13440 = muDoubleScalarSqrt (
rtb_B_136_1759_13440 ) ; } else if ( rtb_B_136_1759_13440 < 0.0 ) {
rtb_B_136_1759_13440 = - muDoubleScalarSqrt ( muDoubleScalarAbs (
rtb_B_136_1759_13440 ) ) ; _rtDW -> Sqrt2_DWORK1_h = 1 ; } else {
rtb_B_136_1759_13440 = muDoubleScalarSqrt ( rtb_B_136_1759_13440 ) ; } _rtB
-> B_136_1229_9832 [ 0 ] = _rtB -> B_136_266_2128 ; _rtB -> B_136_1229_9832 [
1 ] = rtb_B_136_1758_13432 ; _rtB -> B_136_1229_9832 [ 2 ] = _rtP -> P_206 *
rtb_B_136_1759_13440 ; _rtB -> B_136_269_2152 = _rtB -> B_136_242_1936 [ 0 ]
* _rtB -> B_136_237_1896 [ 1 ] ; _rtB -> B_136_270_2160 = _rtB ->
B_136_237_1896 [ 0 ] * _rtB -> B_136_242_1936 [ 1 ] ; _rtB -> B_136_271_2168
= _rtB -> B_136_269_2152 - _rtB -> B_136_270_2160 ; _rtB -> B_136_272_2176 =
_rtP -> P_207 * _rtB -> B_136_271_2168 ; _rtB -> B_136_273_2184 = _rtP ->
P_208 * _rtB -> B_136_272_2176 ; _rtB -> B_136_274_2192 = _rtB ->
B_136_258_2064 [ 0 ] * _rtB -> B_136_253_2024 [ 1 ] ; _rtB -> B_136_275_2200
= _rtB -> B_136_253_2024 [ 0 ] * _rtB -> B_136_258_2064 [ 1 ] ; _rtB ->
B_136_276_2208 = _rtB -> B_136_274_2192 - _rtB -> B_136_275_2200 ; _rtB ->
B_136_277_2216 = _rtP -> P_209 * _rtB -> B_136_276_2208 ; _rtB ->
B_136_278_2224 = _rtP -> P_210 * _rtB -> B_136_277_2216 ; ssCallAccelRunBlock
( S , 136 , 269 , SS_CALL_MDL_OUTPUTS ) ; i = ssIsSampleHit ( S , 1 , 0 ) ;
if ( i != 0 ) { rtb_B_136_1758_13432 = _rtDW -> Memory_PreviousInput [ 1 ] ;
rtb_B_136_1759_13440 = _rtDW -> Memory_PreviousInput [ 0 ] ;
rtb_B_128_2147_16544 = _rtDW -> Memory_PreviousInput [ 2 ] ; for ( i = 0 ; i
< 3 ; i ++ ) { _rtB -> B_136_279_2232 [ i ] = ( ( _rtP -> P_212 [ i + 3 ] *
rtb_B_136_1758_13432 + _rtP -> P_212 [ i ] * rtb_B_136_1759_13440 ) + _rtP ->
P_212 [ i + 6 ] * rtb_B_128_2147_16544 ) * _rtP -> P_213 ; } }
dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1240_9864 , & _rtB ->
B_136_279_2232 [ 0 ] , _rtB -> B_136_14_112 , & _rtB -> Subsystem1_ge , &
_rtDW -> Subsystem1_ge ) ; dVOC_monitor_network1_Subsystempi2delay ( S , _rtB
-> B_136_1241_9865 , & _rtB -> B_136_279_2232 [ 0 ] , _rtB -> B_136_14_112 ,
& _rtB -> Subsystempi2delay_l , & _rtDW -> Subsystempi2delay_l ) ; if ( _rtB
-> B_136_1240_9864 != 0 ) { _rtB -> B_136_282_2256 [ 0 ] = _rtB ->
Subsystem1_ge . B_25_1750_13368 ; _rtB -> B_136_282_2256 [ 1 ] = _rtB ->
Subsystem1_ge . B_25_1751_13376 ; } else { _rtB -> B_136_282_2256 [ 0 ] =
_rtB -> Subsystempi2delay_l . B_24_1752_13384 ; _rtB -> B_136_282_2256 [ 1 ]
= _rtB -> Subsystempi2delay_l . B_24_1753_13392 ; } ssCallAccelRunBlock ( S ,
136 , 276 , SS_CALL_MDL_OUTPUTS ) ; i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i
!= 0 ) { tmpForInput [ 0 ] = _rtB -> B_136_210_1680 ; tmpForInput [ 1 ] = 0.0
; tmpForInput [ 2 ] = _rtB -> B_136_216_1728 [ 12 ] ; tmpForInput [ 3 ] =
_rtB -> B_136_216_1728 [ 11 ] ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace_PWORK . AQHandles && ssGetLogOutput ( S
) ) { sdiWriteSignal ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace_PWORK .
AQHandles , ssGetTaskTime ( S , 2 ) , ( char * ) & tmpForInput [ 0 ] + 0 ) ;
} } } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { rtb_B_136_1758_13432
= _rtDW -> Memory_PreviousInput_a [ 1 ] ; rtb_B_136_1759_13440 = _rtDW ->
Memory_PreviousInput_a [ 0 ] ; rtb_B_128_2147_16544 = _rtDW ->
Memory_PreviousInput_a [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) { _rtB ->
B_136_284_2272 [ i ] = ( ( _rtP -> P_215 [ i + 3 ] * rtb_B_136_1758_13432 +
_rtP -> P_215 [ i ] * rtb_B_136_1759_13440 ) + _rtP -> P_215 [ i + 6 ] *
rtb_B_128_2147_16544 ) * _rtP -> P_216 ; } } dVOC_monitor_network1_Subsystem1
( S , _rtB -> B_136_1254_9878 , & _rtB -> B_136_284_2272 [ 0 ] , _rtB ->
B_136_65_520 , & _rtB -> Subsystem1_gc , & _rtDW -> Subsystem1_gc ) ;
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1255_9879 , &
_rtB -> B_136_284_2272 [ 0 ] , _rtB -> B_136_65_520 , & _rtB ->
Subsystempi2delay_o4 , & _rtDW -> Subsystempi2delay_o4 ) ;
rtb_B_136_2273_17552 [ 2 ] = _rtB -> B_136_81_648 [ 2 ] ;
rtb_B_136_2273_17552 [ 5 ] = _rtB -> B_136_62_496 [ 2 ] ;
rtb_B_136_2273_17552 [ 0 ] = _rtB -> B_136_84_672 [ 0 ] ;
rtb_B_136_2273_17552 [ 3 ] = _rtB -> B_136_66_528 [ 0 ] ;
rtb_B_136_2273_17552 [ 6 ] = _rtB -> B_136_91_728 [ 0 ] ;
rtb_B_136_2273_17552 [ 1 ] = _rtB -> B_136_84_672 [ 1 ] ;
rtb_B_136_2273_17552 [ 4 ] = _rtB -> B_136_66_528 [ 1 ] ;
rtb_B_136_2273_17552 [ 7 ] = _rtB -> B_136_91_728 [ 1 ] ;
rtb_B_136_2273_17552 [ 8 ] = _rtB -> B_136_88_704 [ 2 ] ; if ( _rtB ->
B_136_1254_9878 != 0 ) { rtb_B_136_2273_17552 [ 9 ] = _rtB -> Subsystem1_gc .
B_25_1750_13368 ; rtb_B_136_2273_17552 [ 10 ] = _rtB -> Subsystem1_gc .
B_25_1751_13376 ; } else { rtb_B_136_2273_17552 [ 9 ] = _rtB ->
Subsystempi2delay_o4 . B_24_1752_13384 ; rtb_B_136_2273_17552 [ 10 ] = _rtB
-> Subsystempi2delay_o4 . B_24_1753_13392 ; } rtb_B_136_2273_17552 [ 11 ] =
_rtB -> B_136_284_2272 [ 2 ] ; rtb_B_136_2273_17552 [ 12 ] = _rtB ->
B_136_65_520 ; rtb_B_136_2273_17552 [ 13 ] = _rtB -> B_136_77_616 ;
rtb_B_136_2273_17552 [ 14 ] = _rtB -> B_136_265_2120 ; rtb_B_136_2273_17552 [
15 ] = _rtB -> B_136_278_2224 ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace1_PWORK . AQHandles && ssGetLogOutput ( S
) ) { sdiWriteSignal ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace1_PWORK .
AQHandles , ssGetTaskTime ( S , 0 ) , ( char * ) & rtb_B_136_2273_17552 [ 0 ]
+ 0 ) ; } } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { i =
ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) { _rtDW ->
RateTransition54_Buffer = _rtB -> B_136_216_1728 [ 16 ] ; } } i =
ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) { rtb_B_136_1758_13432 = _rtDW ->
RateTransition54_Buffer ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace10_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace10_PWORK . AQHandles , ssGetTaskTime ( S
, 3 ) , ( char * ) & rtb_B_136_1758_13432 + 0 ) ; } } } i = ssIsSampleHit ( S
, 1 , 0 ) ; if ( i != 0 ) { i = ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) {
_rtDW -> RateTransition12_Buffer = _rtB -> B_136_212_1696 ; } } i =
ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) { rtb_B_136_1758_13432 = _rtDW ->
RateTransition12_Buffer ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace11_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace11_PWORK . AQHandles , ssGetTaskTime ( S
, 3 ) , ( char * ) & rtb_B_136_1758_13432 + 0 ) ; } } } i = ssIsSampleHit ( S
, 1 , 0 ) ; if ( i != 0 ) { i = ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) {
_rtDW -> RateTransition53_Buffer = _rtB -> B_136_249_1992 ; } } i =
ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) { rtb_B_136_1758_13432 = _rtDW ->
RateTransition53_Buffer ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace12_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace12_PWORK . AQHandles , ssGetTaskTime ( S
, 3 ) , ( char * ) & rtb_B_136_1758_13432 + 0 ) ; } } } rtb_B_136_2273_17552
[ 2 ] = _rtB -> B_136_30_240 [ 2 ] ; rtb_B_136_2273_17552 [ 5 ] = _rtB ->
B_136_11_88 [ 2 ] ; rtb_B_136_2273_17552 [ 8 ] = _rtB -> B_136_37_296 [ 2 ] ;
rtb_B_136_2273_17552 [ 0 ] = _rtB -> B_136_33_264 [ 0 ] ;
rtb_B_136_2273_17552 [ 3 ] = _rtB -> B_136_15_120 [ 0 ] ;
rtb_B_136_2273_17552 [ 6 ] = _rtB -> B_136_40_320 [ 0 ] ;
rtb_B_136_2273_17552 [ 9 ] = _rtB -> B_136_282_2256 [ 0 ] ;
rtb_B_136_2273_17552 [ 1 ] = _rtB -> B_136_33_264 [ 1 ] ;
rtb_B_136_2273_17552 [ 4 ] = _rtB -> B_136_15_120 [ 1 ] ;
rtb_B_136_2273_17552 [ 7 ] = _rtB -> B_136_40_320 [ 1 ] ;
rtb_B_136_2273_17552 [ 10 ] = _rtB -> B_136_282_2256 [ 1 ] ;
rtb_B_136_2273_17552 [ 11 ] = _rtB -> B_136_279_2232 [ 2 ] ;
rtb_B_136_2273_17552 [ 12 ] = _rtB -> B_136_14_112 ; rtb_B_136_2273_17552 [
13 ] = _rtB -> B_136_26_208 ; rtb_B_136_2273_17552 [ 14 ] = _rtB ->
B_136_249_1992 ; rtb_B_136_2273_17552 [ 15 ] = _rtB -> B_136_273_2184 ; { if
( _rtDW -> _asyncqueue_inserted_for_ToWorkspace2_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace2_PWORK . AQHandles , ssGetTaskTime ( S ,
0 ) , ( char * ) & rtb_B_136_2273_17552 [ 0 ] + 0 ) ; } } { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace3_PWORK . AQHandles && ssGetLogOutput ( S
) ) { sdiWriteSignal ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace3_PWORK .
AQHandles , ssGetTaskTime ( S , 0 ) , ( char * ) & _rtB -> B_136_1223_9784 [
0 ] + 0 ) ; } } { if ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace5_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace5_PWORK . AQHandles , ssGetTaskTime ( S ,
0 ) , ( char * ) & _rtB -> B_136_1226_9808 [ 0 ] + 0 ) ; } } i =
ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { i = ssIsSampleHit ( S , 3 , 0 )
; if ( i != 0 ) { _rtDW -> RateTransition15_Buffer = _rtB -> B_136_213_1704 ;
} } i = ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) { rtb_B_136_1758_13432 =
_rtDW -> RateTransition15_Buffer ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace50_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace50_PWORK . AQHandles , ssGetTaskTime ( S
, 3 ) , ( char * ) & rtb_B_136_1758_13432 + 0 ) ; } } } i = ssIsSampleHit ( S
, 1 , 0 ) ; if ( i != 0 ) { i = ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) {
_rtDW -> RateTransition55_Buffer = _rtB -> B_136_265_2120 ; } } i =
ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) { rtb_B_136_1758_13432 = _rtDW ->
RateTransition55_Buffer ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace51_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace51_PWORK . AQHandles , ssGetTaskTime ( S
, 3 ) , ( char * ) & rtb_B_136_1758_13432 + 0 ) ; } } } i = ssIsSampleHit ( S
, 2 , 0 ) ; if ( i != 0 ) { i = ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) {
_rtDW -> RateTransition52_Buffer = _rtB -> B_136_211_1688 ; } } i =
ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) { rtb_B_136_1758_13432 = _rtDW ->
RateTransition52_Buffer ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace55_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace55_PWORK . AQHandles , ssGetTaskTime ( S
, 3 ) , ( char * ) & rtb_B_136_1758_13432 + 0 ) ; } } } { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace6_PWORK . AQHandles && ssGetLogOutput ( S
) ) { sdiWriteSignal ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace6_PWORK .
AQHandles , ssGetTaskTime ( S , 0 ) , ( char * ) & _rtB -> B_136_1229_9832 [
0 ] + 0 ) ; } } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
rtb_B_136_1854_14200 = _rtP -> P_217 * _rtB -> B_136_54_432 - _rtDW ->
prediction_DSTATE ; } rtb_B_136_1758_13432 = _rtB -> B_136_56_448 * _rtB ->
B_136_118_944 [ 72 ] ; i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtB
-> B_136_287_2296 = rtb_B_136_1854_14200 + _rtB -> B_136_860_6880 ; } _rtB ->
B_136_288_2304 = ( rtb_B_136_1758_13432 - _rtB -> B_136_57_456 * _rtB ->
B_136_118_944 [ 73 ] ) / _rtB -> B_136_287_2296 ; _rtB -> B_136_289_2312 =
0.0 - _rtB -> B_136_248_1984 ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0
) { _rtB -> B_136_290_2320 = ( _rtB -> B_136_862_6896 - _rtDW ->
Memory4_PreviousInput ) * _rtP -> P_220 ; _rtB -> B_136_291_2328 = _rtP ->
P_221 * _rtDW -> Memory4_PreviousInput ; } _rtB -> B_136_292_2336 = 0.0 ;
_rtB -> B_136_292_2336 += _rtP -> P_223 * _rtX -> TransferFcn2_CSTATE ; _rtB
-> B_136_293_2344 = _rtP -> P_224 * _rtB -> B_136_292_2336 ; _rtB ->
B_136_294_2352 = ( ( _rtB -> B_136_290_2320 + _rtB -> B_136_864_6912 ) + _rtB
-> B_136_291_2328 ) + _rtB -> B_136_293_2344 ; _rtB -> B_136_295_2360 = _rtP
-> P_225 * _rtB -> B_136_42_336 ; _rtB -> B_136_296_2368 = _rtP -> P_226 *
_rtB -> B_136_53_424 ; i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtB
-> B_136_297_2376 = _rtP -> P_227 * _rtB -> B_136_118_944 [ 60 ] ; _rtB ->
B_136_298_2384 = _rtP -> P_228 * _rtB -> B_136_118_944 [ 61 ] ; _rtB ->
B_136_299_2392 = _rtP -> P_229 * _rtB -> B_136_118_944 [ 62 ] ; _rtB ->
B_136_300_2400 = _rtP -> P_230 * _rtB -> B_136_118_944 [ 63 ] ; _rtB ->
B_136_301_2408 = _rtP -> P_231 * _rtB -> B_136_118_944 [ 64 ] ; _rtB ->
B_136_302_2416 = _rtP -> P_232 * _rtB -> B_136_118_944 [ 65 ] ; }
ssCallAccelRunBlock ( S , 136 , 355 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_136_303_2424 = _rtP -> P_233 * _rtB -> B_136_17_136 ; _rtB ->
B_136_304_2432 = _rtP -> P_234 * _rtB -> B_136_47_376 ; i = ssIsSampleHit ( S
, 2 , 0 ) ; if ( i != 0 ) { _rtB -> B_136_305_2440 = _rtP -> P_235 * _rtB ->
B_136_118_944 [ 46 ] ; _rtB -> B_136_306_2448 = _rtP -> P_236 * _rtB ->
B_136_118_944 [ 47 ] ; _rtB -> B_136_307_2456 = _rtP -> P_237 * _rtB ->
B_136_118_944 [ 48 ] ; _rtB -> B_136_308_2464 = _rtP -> P_238 * _rtB ->
B_136_118_944 [ 49 ] ; _rtB -> B_136_309_2472 = _rtP -> P_239 * _rtB ->
B_136_118_944 [ 50 ] ; _rtB -> B_136_310_2480 = _rtP -> P_240 * _rtB ->
B_136_118_944 [ 51 ] ; _rtB -> B_136_311_2488 = _rtP -> P_241 * _rtB ->
B_136_118_944 [ 52 ] ; } _rtB -> B_136_312_2496 = 0.0 ; _rtB ->
B_136_312_2496 += _rtP -> P_243 * _rtX -> TransferFcn4_CSTATE_l ; _rtB ->
B_136_313_2504 = _rtB -> B_136_10_80 * _rtB -> B_136_10_80 + _rtB ->
B_136_868_6944 ; _rtB -> B_136_314_2512 = _rtB -> B_136_312_2496 / _rtB ->
B_136_313_2504 ; _rtB -> B_136_315_2520 = _rtB -> B_136_869_6952 - _rtB ->
B_136_314_2512 ; _rtB -> B_136_316_2528 = _rtP -> P_244 * _rtB ->
B_136_315_2520 ; _rtB -> B_136_317_2536 = _rtB -> B_136_867_6936 - _rtB ->
B_136_10_80 * _rtB -> B_136_10_80 ; _rtB -> B_136_318_2544 = _rtP -> P_245 *
_rtB -> B_136_317_2536 ; _rtB -> B_136_319_2552 = _rtB -> B_136_318_2544 /
_rtB -> B_136_867_6936 ; _rtB -> B_136_320_2560 = _rtB -> B_136_316_2528 +
_rtB -> B_136_319_2552 ; _rtB -> B_136_321_2568 = _rtB -> B_136_320_2560 *
_rtB -> B_136_10_80 ; i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
rtb_B_136_1864_14280 = _rtP -> P_246 * _rtB -> B_136_105_840 - _rtDW ->
prediction_DSTATE_e ; } rtb_B_136_1758_13432 = _rtB -> B_136_108_864 * _rtB
-> B_136_118_944 [ 75 ] ; i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
_rtB -> B_136_322_2576 = rtb_B_136_1864_14280 + _rtB -> B_136_871_6968 ; }
_rtB -> B_136_323_2584 = ( _rtB -> B_136_107_856 * _rtB -> B_136_118_944 [ 74
] - rtb_B_136_1758_13432 ) / _rtB -> B_136_322_2576 ; _rtB -> B_136_324_2592
= 0.0 - _rtB -> B_136_264_2112 ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i !=
0 ) { _rtB -> B_136_325_2600 = ( _rtB -> B_136_873_6984 - _rtDW ->
Memory4_PreviousInput_c ) * _rtP -> P_249 ; _rtB -> B_136_326_2608 = _rtP ->
P_250 * _rtDW -> Memory4_PreviousInput_c ; } _rtB -> B_136_327_2616 = 0.0 ;
_rtB -> B_136_327_2616 += _rtP -> P_252 * _rtX -> TransferFcn2_CSTATE_a ;
_rtB -> B_136_328_2624 = _rtP -> P_253 * _rtB -> B_136_327_2616 ; _rtB ->
B_136_329_2632 = ( ( _rtB -> B_136_325_2600 + _rtB -> B_136_875_7000 ) + _rtB
-> B_136_326_2608 ) + _rtB -> B_136_328_2624 ; _rtB -> B_136_330_2640 = _rtP
-> P_254 * _rtB -> B_136_93_744 ; _rtB -> B_136_331_2648 = _rtP -> P_255 *
_rtB -> B_136_104_832 ; i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
_rtB -> B_136_332_2656 = _rtP -> P_256 * _rtB -> B_136_118_944 [ 66 ] ; _rtB
-> B_136_333_2664 = _rtP -> P_257 * _rtB -> B_136_118_944 [ 67 ] ; _rtB ->
B_136_334_2672 = _rtP -> P_258 * _rtB -> B_136_118_944 [ 68 ] ; _rtB ->
B_136_335_2680 = _rtP -> P_259 * _rtB -> B_136_118_944 [ 69 ] ; _rtB ->
B_136_336_2688 = _rtP -> P_260 * _rtB -> B_136_118_944 [ 70 ] ; _rtB ->
B_136_337_2696 = _rtP -> P_261 * _rtB -> B_136_118_944 [ 71 ] ; } _rtB ->
B_136_338_2704 = _rtP -> P_262 * _rtB -> B_136_68_544 ; _rtB ->
B_136_339_2712 = _rtP -> P_263 * _rtB -> B_136_98_784 ; i = ssIsSampleHit ( S
, 2 , 0 ) ; if ( i != 0 ) { _rtB -> B_136_340_2720 = _rtP -> P_264 * _rtB ->
B_136_118_944 [ 53 ] ; _rtB -> B_136_341_2728 = _rtP -> P_265 * _rtB ->
B_136_118_944 [ 54 ] ; _rtB -> B_136_342_2736 = _rtP -> P_266 * _rtB ->
B_136_118_944 [ 55 ] ; _rtB -> B_136_343_2744 = _rtP -> P_267 * _rtB ->
B_136_118_944 [ 56 ] ; _rtB -> B_136_344_2752 = _rtP -> P_268 * _rtB ->
B_136_118_944 [ 57 ] ; _rtB -> B_136_345_2760 = _rtP -> P_269 * _rtB ->
B_136_118_944 [ 58 ] ; _rtB -> B_136_346_2768 = _rtP -> P_270 * _rtB ->
B_136_118_944 [ 59 ] ; } _rtB -> B_136_347_2776 = _rtB -> B_136_878_7024 -
_rtB -> B_136_61_488 * _rtB -> B_136_61_488 ; _rtB -> B_136_348_2784 = _rtP
-> P_271 * _rtB -> B_136_347_2776 ; _rtB -> B_136_349_2792 = _rtB ->
B_136_348_2784 / _rtB -> B_136_878_7024 ; ssCallAccelRunBlock ( S , 136 , 497
, SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_136_350_2800 = 0.0 ; _rtB ->
B_136_350_2800 += _rtP -> P_273 * _rtX -> TransferFcn4_CSTATE_n ; _rtB ->
B_136_351_2808 = _rtB -> B_136_61_488 * _rtB -> B_136_61_488 + _rtB ->
B_136_879_7032 ; _rtB -> B_136_352_2816 = _rtB -> B_136_350_2800 / _rtB ->
B_136_351_2808 ; _rtB -> B_136_353_2824 = _rtB -> B_136_880_7040 - _rtB ->
B_136_352_2816 ; _rtB -> B_136_354_2832 = _rtP -> P_274 * _rtB ->
B_136_353_2824 ; _rtB -> B_136_355_2840 = _rtB -> B_136_354_2832 + _rtB ->
B_136_349_2792 ; _rtB -> B_136_356_2848 = _rtB -> B_136_355_2840 * _rtB ->
B_136_61_488 ; _rtB -> B_136_357_2856 = 0.0 ; for ( ri = _rtP -> P_974 [ 0U ]
; ri < _rtP -> P_974 [ 1U ] ; ri ++ ) { _rtB -> B_136_357_2856 += _rtP ->
P_277 * _rtX -> Internal_CSTATE_p ; } ssCallAccelRunBlock ( S , 136 , 521 ,
SS_CALL_MDL_OUTPUTS ) ; i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { {
B_136_1872_14344 = _rtP -> P_281 * _rtDW -> DiscreteStateSpace_DSTATE ;
B_136_1872_14344 += _rtP -> P_282 * _rtB -> B_136_210_1680 ; } _rtB ->
B_136_358_2864 = _rtP -> P_284 * B_136_1872_14344 ; { _rtB -> B_136_359_2872
= ( _rtP -> P_287 ) * _rtDW -> DiscreteStateSpace_DSTATE_n ; _rtB ->
B_136_359_2872 += _rtP -> P_288 * _rtB -> B_136_358_2864 ; } { _rtB ->
B_136_360_2880 = ( _rtP -> P_292 ) * _rtDW -> DiscreteStateSpace_DSTATE_d ;
_rtB -> B_136_360_2880 += _rtP -> P_293 * _rtB -> B_136_359_2872 ; } {
B_136_1873_14352 = ( _rtP -> P_297 ) * _rtDW -> DiscreteStateSpace_DSTATE_g ;
B_136_1873_14352 += _rtP -> P_298 * _rtB -> B_136_360_2880 ; } if (
B_136_1873_14352 > _rtP -> P_300 ) { _rtB -> B_136_361_2888 = _rtP -> P_300 ;
} else if ( B_136_1873_14352 < _rtP -> P_301 ) { _rtB -> B_136_361_2888 =
_rtP -> P_301 ; } else { _rtB -> B_136_361_2888 = B_136_1873_14352 ; }
rtb_B_136_1758_13432 = muDoubleScalarPower ( _rtB -> B_136_216_1728 [ 12 ] ,
2.0 ) + muDoubleScalarPower ( _rtB -> B_136_216_1728 [ 11 ] , 2.0 ) ; _rtB ->
B_136_362_2896 = muDoubleScalarSqrt ( rtb_B_136_1758_13432 ) ; } if (
ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX -> Integrator_CSTATE_o >= _rtP ->
P_303 ) { if ( _rtX -> Integrator_CSTATE_o != _rtP -> P_303 ) { _rtX ->
Integrator_CSTATE_o = _rtP -> P_303 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW -> Integrator_MODE
= 3 ; } else if ( _rtX -> Integrator_CSTATE_o <= _rtP -> P_304 ) { if ( _rtX
-> Integrator_CSTATE_o != _rtP -> P_304 ) { _rtX -> Integrator_CSTATE_o =
_rtP -> P_304 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE = 4 ; } else { if ( _rtDW -> Integrator_MODE != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW -> Integrator_MODE
= 0 ; } _rtB -> B_136_363_2904 = _rtX -> Integrator_CSTATE_o ; } else { _rtB
-> B_136_363_2904 = _rtX -> Integrator_CSTATE_o ; } i = ssIsSampleHit ( S , 2
, 0 ) ; if ( i != 0 ) { rtb_B_136_1854_14200 = ( _rtB -> B_136_216_1728 [ 5 ]
- _rtB -> B_136_882_7056 ) * _rtP -> P_305 ; if ( rtb_B_136_1854_14200 > _rtP
-> P_306 ) { _rtB -> B_136_364_2912 = _rtP -> P_306 ; } else if (
rtb_B_136_1854_14200 < _rtP -> P_307 ) { _rtB -> B_136_364_2912 = _rtP ->
P_307 ; } else { _rtB -> B_136_364_2912 = rtb_B_136_1854_14200 ; } } _rtB ->
B_136_365_2920 = _rtB -> B_136_363_2904 - _rtB -> B_136_364_2912 ; _rtB ->
B_136_366_2928 = 0.0 ; for ( ri = _rtP -> P_980 [ 0U ] ; ri < _rtP -> P_980 [
1U ] ; ri ++ ) { _rtB -> B_136_366_2928 += _rtP -> P_310 * _rtX ->
StateSpace_CSTATE ; } for ( ri = _rtP -> P_982 [ 0U ] ; ri < _rtP -> P_982 [
1U ] ; ri ++ ) { _rtB -> B_136_366_2928 += _rtP -> P_311 * _rtB ->
B_136_365_2920 ; } _rtB -> B_136_367_2936 = 0.0 ; for ( ri = _rtP -> P_988 [
0U ] ; ri < _rtP -> P_988 [ 1U ] ; ri ++ ) { _rtB -> B_136_367_2936 += _rtP
-> P_315 * _rtX -> StateSpace_CSTATE_n ; } i = ssIsSampleHit ( S , 2 , 0 ) ;
if ( i != 0 ) { _rtB -> B_136_368_2944 = _rtP -> P_317 * _rtB ->
B_136_216_1728 [ 5 ] ; } _rtB -> B_136_369_2952 = _rtP -> P_319 * _rtB ->
B_136_367_2936 ; _rtB -> B_136_370_2960 = _rtP -> P_318 * _rtB ->
B_136_367_2936 - _rtB -> B_136_368_2944 ; i = ssIsSampleHit ( S , 1 , 0 ) ;
if ( i != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
LowerRelop1_Mode = ( _rtB -> B_136_365_2920 > _rtB -> B_136_370_2960 ) ; }
_rtB -> B_136_1278_9902 = _rtDW -> LowerRelop1_Mode ; if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> UpperRelop_Mode = ( _rtB ->
B_136_365_2920 < _rtB -> B_136_369_2952 ) ; } _rtB -> B_136_1279_9903 = _rtDW
-> UpperRelop_Mode ; } _rtB -> B_136_371_2968 = ( ( ( _rtB -> B_136_997_7976
+ _rtB -> B_136_883_7064 ) - _rtB -> B_136_367_2936 ) + _rtB ->
B_136_361_2888 ) - _rtB -> B_136_366_2928 ; if ( ssIsModeUpdateTimeStep ( S )
) { if ( _rtB -> B_136_371_2968 >= _rtP -> P_320 ) { _rtDW -> VImin_MODE = 1
; } else if ( _rtB -> B_136_371_2968 > _rtP -> P_321 ) { _rtDW -> VImin_MODE
= 0 ; } else { _rtDW -> VImin_MODE = - 1 ; } } if ( _rtDW -> VImin_MODE == 1
) { _rtB -> B_136_372_2976 = _rtP -> P_320 ; } else if ( _rtDW -> VImin_MODE
== - 1 ) { _rtB -> B_136_372_2976 = _rtP -> P_321 ; } else { _rtB ->
B_136_372_2976 = _rtB -> B_136_371_2968 ; } _rtB -> B_136_373_2984 = 0.0 ;
for ( ri = _rtP -> P_990 [ 0U ] ; ri < _rtP -> P_990 [ 1U ] ; ri ++ ) { _rtB
-> B_136_373_2984 += _rtP -> P_322 * _rtB -> B_136_372_2976 ; } _rtB ->
B_136_374_2992 = _rtP -> P_323 * _rtB -> B_136_373_2984 ; _rtB ->
B_136_375_3000 = _rtB -> B_136_374_2992 - _rtB -> B_136_363_2904 ; _rtB ->
B_136_376_3008 = _rtP -> P_324 * _rtB -> B_136_375_3000 ; i = ssIsSampleHit (
S , 2 , 0 ) ; if ( i != 0 ) { _rtB -> B_136_377_3016 = _rtB -> B_136_859_6872
- ( rtb_B_136_1808_13832 - _rtB -> B_136_998_7984 ) * _rtP -> P_325 ; } if (
_rtB -> B_136_1278_9902 ) { rtb_B_128_2147_16544 = _rtB -> B_136_370_2960 ; }
else if ( _rtB -> B_136_1279_9903 ) { rtb_B_128_2147_16544 = _rtB ->
B_136_369_2952 ; } else { rtb_B_128_2147_16544 = _rtB -> B_136_365_2920 ; }
_rtB -> B_136_378_3024 = _rtP -> P_326 * rtb_B_128_2147_16544 ; i =
ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { rtb_B_136_1884_14440 = _rtP ->
P_327 [ 0 ] * rtb_B_136_2259_17440 [ 0 ] * _rtB -> B_136_0_0 [ 1 ] + _rtP ->
P_327 [ 1 ] * rtb_B_136_2259_17440 [ 1 ] * _rtB -> B_136_0_0 [ 0 ] ; memcpy (
& rtb_B_128_2152_16584 [ 0 ] , & _rtB -> B_136_944_7552 [ 0 ] , 25U * sizeof
( real_T ) ) ; rtb_B_128_2152_16584 [ 5 ] = rtb_B_136_1807_13824 ;
rtb_B_128_2152_16584 [ 1 ] = _rtP -> P_328 * rtb_B_136_1807_13824 ;
didZcEventOccur = ( _rtB -> B_136_886_7088 >= _rtP -> P_329 ) ; for ( i = 0 ;
i < 25 ; i ++ ) { if ( didZcEventOccur ) { rtb_B_128_2147_16544 = _rtB ->
B_128_1093_8744 [ i ] ; } else { rtb_B_128_2147_16544 = _rtB ->
B_136_914_7312 [ i ] ; } rtb_B_136_1808_13832 = ( ( 0.0 -
rtb_B_128_2152_16584 [ i ] ) - rtb_B_128_2147_16544 ) * _rtP -> P_330 ;
rtb_B_128_2152_16584 [ i ] = rtb_B_136_1808_13832 ; B_128_2152_16584 [ i ] =
_rtB -> B_136_969_7752 [ i ] - rtb_B_136_1808_13832 ; } rt_invd5x5_snf (
B_128_2152_16584 , rtb_B_136_2289_17680 ) ; for ( i = 0 ; i < 25 ; i ++ ) {
rtb_B_128_2152_16584 [ i ] += _rtB -> B_136_969_7752 [ i ] ; } for ( i = 0 ;
i < 5 ; i ++ ) { _rtB -> B_136_379_3032 [ i ] = 0.0 ; for ( i_0 = 0 ; i_0 < 5
; i_0 ++ ) { rtb_B_136_1808_13832 = 0.0 ; for ( i_1 = 0 ; i_1 < 5 ; i_1 ++ )
{ rtb_B_136_1808_13832 += rtb_B_136_2289_17680 [ 5 * i_1 + i ] *
rtb_B_128_2152_16584 [ 5 * i_0 + i_1 ] ; } _rtB -> B_136_379_3032 [ i ] +=
rtb_B_136_1808_13832 * _rtB -> B_136_0_0 [ i_0 ] ; } } for ( i = 0 ; i < 25 ;
i ++ ) { _rtB -> B_136_384_3072 [ i ] = _rtP -> P_331 * rtb_B_136_2289_17680
[ i ] ; } for ( i = 0 ; i < 5 ; i ++ ) { _rtB -> B_136_409_3272 [ i ] = _rtDW
-> voltages_DSTATE [ i ] ; } _rtB -> B_136_414_3312 = ssGetTaskTime ( S , 2 )
; } if ( _rtB -> B_136_414_3312 >= _rtP -> P_333 ) { rtb_B_136_2259_17440 [ 0
] = _rtB -> B_136_214_1712 + _rtB -> B_136_409_3272 [ 0 ] ;
rtb_B_136_2259_17440 [ 1 ] = _rtB -> B_136_215_1720 + _rtB -> B_136_409_3272
[ 1 ] ; rtb_B_136_2259_17440 [ 2 ] = _rtB -> B_136_378_3024 + _rtB ->
B_136_409_3272 [ 2 ] ; rtb_B_136_2259_17440 [ 3 ] = _rtB -> B_136_994_7952 [
0 ] + _rtB -> B_136_409_3272 [ 3 ] ; rtb_B_136_2259_17440 [ 4 ] = _rtB ->
B_136_994_7952 [ 1 ] + _rtB -> B_136_409_3272 [ 4 ] ; for ( i = 0 ; i < 5 ; i
++ ) { rtb_B_128_2147_16544 = 0.0 ; for ( i_0 = 0 ; i_0 < 5 ; i_0 ++ ) {
rtb_B_128_2147_16544 += _rtB -> B_136_384_3072 [ 5 * i_0 + i ] *
rtb_B_136_2259_17440 [ i_0 ] ; } _rtB -> B_136_415_3320 [ i ] = _rtB ->
B_136_379_3032 [ i ] + rtb_B_128_2147_16544 ; } } else { for ( i = 0 ; i < 5
; i ++ ) { _rtB -> B_136_415_3320 [ i ] = _rtB -> B_136_0_0 [ i ] ; } } i =
ssIsSampleHit ( S , 1 , 0 ) ; if ( ( i != 0 ) && ( _rtDW ->
RateTransition1_semaphoreTaken == 0 ) ) { _rtDW -> RateTransition1_Buffer0 =
_rtB -> B_136_357_2856 ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
_rtDW -> RateTransition1_semaphoreTaken = 1 ; rtb_B_136_1808_13832 = _rtDW ->
RateTransition1_Buffer0 ; _rtDW -> RateTransition1_semaphoreTaken = 0 ; _rtB
-> B_136_420_3360 = ( ( _rtP -> P_334 * rtb_B_136_1808_13832 /
rtb_B_136_1807_13824 - rtb_B_136_1884_14440 ) - _rtP -> P_335 *
rtb_B_136_1807_13824 ) * _rtP -> P_336 ; if ( _rtDW ->
Rotorspeeddeviationdw_SYSTEM_ENABLE != 0 ) { _rtB -> B_136_421_3368 = _rtDW
-> Rotorspeeddeviationdw_DSTATE ; } else { _rtB -> B_136_421_3368 = _rtP ->
P_337 * _rtB -> B_136_420_3360 + _rtDW -> Rotorspeeddeviationdw_DSTATE ; }
_rtB -> B_136_422_3376 = _rtP -> P_341 * _rtB -> B_136_210_1680 ; _rtB ->
B_136_423_3384 = _rtP -> P_342 * rtb_B_136_1807_13824 ; } i = ssIsSampleHit (
S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_136_424_3392 = _rtDW ->
Memory_PreviousInput_c ; if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
RelationalOperator_Mode = ( _rtX -> Integrator_CSTATE_j > _rtB ->
B_136_1000_8000 ) ; } _rtB -> B_136_1280_9904 = _rtDW ->
RelationalOperator_Mode ; } _rtB -> B_136_425_3400 = _rtX ->
Integrator_CSTATE_j - _rtB -> B_136_1000_8000 ; if ( ( _rtDW ->
Initial_FirstOutputTime == ( rtMinusInf ) ) || ( _rtDW ->
Initial_FirstOutputTime == ssGetTaskTime ( S , 0 ) ) ) { _rtDW ->
Initial_FirstOutputTime = ssGetTaskTime ( S , 0 ) ; _rtB -> B_136_426_3408 =
_rtP -> P_344 ; } else { _rtB -> B_136_426_3408 = _rtB -> B_136_425_3400 ; }
if ( ssIsModeUpdateTimeStep ( S ) ) { didZcEventOccur = ( _rtB ->
B_136_1280_9904 && ( _rtZCE -> Integrator_Reset_ZCE != POS_ZCSIG ) ) ; _rtZCE
-> Integrator_Reset_ZCE = _rtB -> B_136_1280_9904 ; if ( didZcEventOccur || (
_rtDW -> Integrator_IWORK != 0 ) ) { didZcEventOccur = ( _rtX ->
Integrator_CSTATE_j != _rtB -> B_136_426_3408 ) ; _rtX -> Integrator_CSTATE_j
= _rtB -> B_136_426_3408 ; if ( didZcEventOccur ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } } if ( _rtX ->
Integrator_CSTATE_j >= _rtP -> P_345 ) { if ( _rtX -> Integrator_CSTATE_j !=
_rtP -> P_345 ) { _rtX -> Integrator_CSTATE_j = _rtP -> P_345 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_f = 3 ; } else if ( _rtX -> Integrator_CSTATE_j <= _rtP ->
P_346 ) { if ( _rtX -> Integrator_CSTATE_j != _rtP -> P_346 ) { _rtX ->
Integrator_CSTATE_j = _rtP -> P_346 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_f = 4 ; } else { if ( _rtDW -> Integrator_MODE_f != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_f = 0 ; } _rtB -> B_136_427_3416 = _rtX ->
Integrator_CSTATE_j ; } else { _rtB -> B_136_427_3416 = _rtX ->
Integrator_CSTATE_j ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
_rtB -> B_136_428_3424 [ 0 ] = _rtP -> P_347 * _rtB -> B_136_118_944 [ 25 ] *
_rtP -> P_350 ; _rtB -> B_136_428_3424 [ 1 ] = _rtP -> P_348 * _rtB ->
B_136_118_944 [ 26 ] * _rtP -> P_350 ; _rtB -> B_136_428_3424 [ 2 ] = _rtP ->
P_349 * _rtB -> B_136_118_944 [ 27 ] * _rtP -> P_350 ; rtb_B_136_1807_13824 =
_rtB -> B_136_428_3424 [ 1 ] ; rtb_B_136_1884_14440 = _rtB -> B_136_428_3424
[ 0 ] ; rtb_B_136_1808_13832 = _rtB -> B_136_428_3424 [ 2 ] ; for ( i = 0 ; i
< 3 ; i ++ ) { rtb_B_128_2256_17416 [ i ] = ( ( _rtP -> P_351 [ i + 3 ] *
rtb_B_136_1807_13824 + _rtP -> P_351 [ i ] * rtb_B_136_1884_14440 ) + _rtP ->
P_351 [ i + 6 ] * rtb_B_136_1808_13832 ) * _rtP -> P_352 ; } _rtB ->
B_136_431_3448 = muDoubleScalarHypot ( rtb_B_128_2256_17416 [ 0 ] ,
rtb_B_128_2256_17416 [ 1 ] ) ; } ssCallAccelRunBlock ( S , 136 , 604 ,
SS_CALL_MDL_OUTPUTS ) ; dVOC_monitor_network1_AutomaticGainControl ( S , _rtB
-> B_136_999_7992 , _rtB -> B_136_424_3392 , _rtB -> B_136_427_3416 , _rtB ->
B_136_428_3424 , & _rtB -> AutomaticGainControl_g , & _rtDW ->
AutomaticGainControl_g , & _rtP -> AutomaticGainControl_g , & _rtX ->
AutomaticGainControl_g , & _rtXdis -> AutomaticGainControl_g ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX -> Integrator_CSTATE_i4 >= _rtP ->
P_355 ) { if ( _rtX -> Integrator_CSTATE_i4 != _rtP -> P_355 ) { _rtX ->
Integrator_CSTATE_i4 = _rtP -> P_355 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_j = 3 ; } else if ( _rtX -> Integrator_CSTATE_i4 <= _rtP ->
P_356 ) { if ( _rtX -> Integrator_CSTATE_i4 != _rtP -> P_356 ) { _rtX ->
Integrator_CSTATE_i4 = _rtP -> P_356 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_j = 4 ; } else { if ( _rtDW -> Integrator_MODE_j != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_j = 0 ; } _rtB -> B_136_432_3456 = _rtX ->
Integrator_CSTATE_i4 ; } else { _rtB -> B_136_432_3456 = _rtX ->
Integrator_CSTATE_i4 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT (
S ) ; real_T appliedDelay ; _rtB -> B_136_433_3464 =
dVOC_monitor_network1_acc_rt_VTDelayfindtDInterpolate ( ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE , * uBuffer , _rtDW ->
VariableTransportDelay_IWORK . CircularBufSize , _rtDW ->
VariableTransportDelay_IWORK . Head , _rtDW -> VariableTransportDelay_IWORK .
Tail , & _rtDW -> VariableTransportDelay_IWORK . Last , simTime , 0.0 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
VariableTransportDelay_IWORK . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK . Head ] == ssGetT ( S ) ) ) , _rtP -> P_358 , &
appliedDelay ) ; } _rtB -> B_136_434_3472 = _rtX -> integrator_CSTATE ; _rtB
-> B_136_435_3480 = ssGetT ( S ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i
!= 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
RelationalOperator_Mode_l = ( _rtB -> B_136_435_3480 >= _rtB ->
B_136_1001_8008 ) ; } _rtB -> B_136_1281_9905 = _rtDW ->
RelationalOperator_Mode_l ; } if ( _rtB -> B_136_1281_9905 ) { _rtB ->
B_105_1209_9672 = _rtB -> B_136_434_3472 - _rtB -> B_136_433_3464 ; _rtB ->
B_105_1210_9680 = _rtB -> B_105_1209_9672 * _rtB -> B_136_424_3392 ; _rtB ->
B_136_436_3488 = _rtB -> B_105_1210_9680 ; } else { _rtB -> B_136_436_3488 =
_rtB -> B_136_1002_8016 ; } _rtB -> B_136_437_3496 = _rtB -> B_136_436_3488 *
_rtB -> AutomaticGainControl_g . B_56_1669_12744 ; _rtB -> B_136_438_3504 =
_rtP -> P_360 * _rtB -> B_136_437_3496 ; _rtB -> B_136_439_3512 = _rtP ->
P_361 * _rtB -> B_136_437_3496 ; _rtB -> B_136_440_3520 = _rtP -> P_362 *
_rtB -> B_136_437_3496 ; _rtB -> B_136_441_3528 = 0.0 ; _rtB ->
B_136_441_3528 += _rtP -> P_364 * _rtX -> TransferFcn_CSTATE ; _rtB ->
B_136_441_3528 += _rtP -> P_365 * _rtB -> B_136_440_3520 ; _rtB ->
B_136_442_3536 = ( _rtB -> B_136_438_3504 + _rtB -> B_136_432_3456 ) + _rtB
-> B_136_441_3528 ; if ( ssIsModeUpdateTimeStep ( S ) ) { if ( _rtB ->
B_136_442_3536 >= _rtP -> P_366 ) { _rtDW -> Saturation2_MODE = 1 ; } else if
( _rtB -> B_136_442_3536 > _rtP -> P_367 ) { _rtDW -> Saturation2_MODE = 0 ;
} else { _rtDW -> Saturation2_MODE = - 1 ; } } if ( _rtDW -> Saturation2_MODE
== 1 ) { _rtB -> B_136_443_3544 = _rtP -> P_366 ; } else if ( _rtDW ->
Saturation2_MODE == - 1 ) { _rtB -> B_136_443_3544 = _rtP -> P_367 ; } else {
_rtB -> B_136_443_3544 = _rtB -> B_136_442_3536 ; } _rtB -> B_136_444_3552 =
_rtP -> P_368 * _rtB -> B_136_443_3544 ; if ( _rtDW -> LastMajorTime == (
rtInf ) ) { _rtB -> B_136_445_3560 = _rtB -> B_136_444_3552 ; } else {
rtb_B_136_1884_14440 = ssGetTaskTime ( S , 0 ) - _rtDW -> LastMajorTime ; if
( _rtDW -> LastMajorTime == ssGetTaskTime ( S , 0 ) ) { if ( _rtDW ->
PrevLimited ) { _rtB -> B_136_445_3560 = _rtDW -> PrevY ; } else { _rtB ->
B_136_445_3560 = _rtB -> B_136_444_3552 ; } } else { rtb_B_136_1808_13832 =
rtb_B_136_1884_14440 * _rtP -> P_369 ; rtb_B_136_1807_13824 = _rtB ->
B_136_444_3552 - _rtDW -> PrevY ; if ( rtb_B_136_1807_13824 >
rtb_B_136_1808_13832 ) { _rtB -> B_136_445_3560 = _rtDW -> PrevY +
rtb_B_136_1808_13832 ; didZcEventOccur = true ; } else { rtb_B_136_1884_14440
*= _rtP -> P_370 ; if ( rtb_B_136_1807_13824 < rtb_B_136_1884_14440 ) { _rtB
-> B_136_445_3560 = _rtDW -> PrevY + rtb_B_136_1884_14440 ; didZcEventOccur =
true ; } else { _rtB -> B_136_445_3560 = _rtB -> B_136_444_3552 ;
didZcEventOccur = false ; } } if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
PrevLimited = didZcEventOccur ; } } } _rtB -> B_136_446_3568 = _rtX ->
Integrator_x1_CSTATE ; _rtB -> B_136_447_3576 = _rtP -> P_372 * _rtB ->
B_136_446_3568 ; _rtB -> B_136_448_3584 = _rtX -> Integrator_x2_CSTATE ; _rtB
-> B_136_449_3592 = _rtP -> P_374 * _rtB -> B_136_448_3584 ; _rtB ->
B_136_450_3600 = _rtP -> P_375 * _rtB -> B_136_446_3568 ; _rtB ->
B_136_451_3608 = _rtP -> P_376 * _rtB -> B_136_448_3584 ; _rtB ->
B_136_452_3616 = _rtB -> B_136_447_3576 + _rtB -> B_136_449_3592 ; _rtB ->
B_136_453_3624 = _rtB -> B_136_450_3600 + _rtB -> B_136_451_3608 ; _rtB ->
B_136_454_3632 = _rtP -> P_377 * _rtB -> B_136_445_3560 ; _rtB ->
B_136_455_3640 = _rtB -> B_136_452_3616 + _rtB -> B_136_454_3632 ; _rtB ->
B_136_456_3648 = _rtP -> P_378 * _rtB -> B_136_445_3560 ; _rtB ->
B_136_457_3656 = _rtB -> B_136_453_3624 + _rtB -> B_136_456_3648 ; _rtB ->
B_136_458_3664 = ( _rtP -> P_379 * _rtB -> B_136_446_3568 + _rtP -> P_380 *
_rtB -> B_136_448_3584 ) + _rtP -> P_381 * _rtB -> B_136_445_3560 ; if ( _rtB
-> B_136_424_3392 > _rtP -> P_382 ) { _rtB -> B_136_459_3672 = _rtP -> P_382
; } else if ( _rtB -> B_136_424_3392 < _rtP -> P_383 ) { _rtB ->
B_136_459_3672 = _rtP -> P_383 ; } else { _rtB -> B_136_459_3672 = _rtB ->
B_136_424_3392 ; } _rtB -> B_136_460_3680 = 1.0 / _rtB -> B_136_459_3672 ;
rtb_B_136_1807_13824 = _rtB -> B_136_428_3424 [ 1 ] ; rtb_B_136_1884_14440 =
_rtB -> B_136_428_3424 [ 0 ] ; rtb_B_136_1808_13832 = _rtB -> B_136_428_3424
[ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) { rtb_B_136_1854_14200 = ( _rtP -> P_384
[ i + 3 ] * rtb_B_136_1807_13824 + _rtP -> P_384 [ i ] * rtb_B_136_1884_14440
) + _rtP -> P_384 [ i + 6 ] * rtb_B_136_1808_13832 ; _rtB -> B_136_461_3688 [
i ] = rtb_B_136_1854_14200 ; _rtB -> B_136_464_3712 [ i ] = _rtP -> P_385 *
rtb_B_136_1854_14200 ; } dVOC_monitor_network1_Subsystempi2delay ( S , _rtB
-> B_136_1261_9885 , & _rtB -> B_136_464_3712 [ 0 ] , _rtB -> B_136_427_3416
, & _rtB -> Subsystempi2delay_j , & _rtDW -> Subsystempi2delay_j ) ;
dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1260_9884 , & _rtB ->
B_136_464_3712 [ 0 ] , _rtB -> B_136_427_3416 , & _rtB -> Subsystem1_cm , &
_rtDW -> Subsystem1_cm ) ; if ( _rtB -> B_136_1260_9884 != 0 ) { _rtB ->
B_136_467_3736 [ 0 ] = _rtB -> Subsystem1_cm . B_25_1750_13368 ; _rtB ->
B_136_467_3736 [ 1 ] = _rtB -> Subsystem1_cm . B_25_1751_13376 ; } else {
_rtB -> B_136_467_3736 [ 0 ] = _rtB -> Subsystempi2delay_j . B_24_1752_13384
; _rtB -> B_136_467_3736 [ 1 ] = _rtB -> Subsystempi2delay_j .
B_24_1753_13392 ; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB ->
B_136_469_3752 = _rtDW -> Memory_PreviousInput_ap ; if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> RelationalOperator_Mode_n = ( _rtX
-> Integrator_CSTATE_h > _rtB -> B_136_1004_8032 ) ; } _rtB ->
B_136_1282_9906 = _rtDW -> RelationalOperator_Mode_n ; } _rtB ->
B_136_470_3760 = _rtX -> Integrator_CSTATE_h - _rtB -> B_136_1004_8032 ; if (
( _rtDW -> Initial_FirstOutputTime_g == ( rtMinusInf ) ) || ( _rtDW ->
Initial_FirstOutputTime_g == ssGetTaskTime ( S , 0 ) ) ) { _rtDW ->
Initial_FirstOutputTime_g = ssGetTaskTime ( S , 0 ) ; _rtB -> B_136_471_3768
= _rtP -> P_387 ; } else { _rtB -> B_136_471_3768 = _rtB -> B_136_470_3760 ;
} if ( ssIsModeUpdateTimeStep ( S ) ) { didZcEventOccur = ( _rtB ->
B_136_1282_9906 && ( _rtZCE -> Integrator_Reset_ZCE_p != POS_ZCSIG ) ) ;
_rtZCE -> Integrator_Reset_ZCE_p = _rtB -> B_136_1282_9906 ; if (
didZcEventOccur || ( _rtDW -> Integrator_IWORK_l != 0 ) ) { didZcEventOccur =
( _rtX -> Integrator_CSTATE_h != _rtB -> B_136_471_3768 ) ; _rtX ->
Integrator_CSTATE_h = _rtB -> B_136_471_3768 ; if ( didZcEventOccur ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } } if ( _rtX ->
Integrator_CSTATE_h >= _rtP -> P_388 ) { if ( _rtX -> Integrator_CSTATE_h !=
_rtP -> P_388 ) { _rtX -> Integrator_CSTATE_h = _rtP -> P_388 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_k = 3 ; } else if ( _rtX -> Integrator_CSTATE_h <= _rtP ->
P_389 ) { if ( _rtX -> Integrator_CSTATE_h != _rtP -> P_389 ) { _rtX ->
Integrator_CSTATE_h = _rtP -> P_389 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_k = 4 ; } else { if ( _rtDW -> Integrator_MODE_k != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_k = 0 ; } _rtB -> B_136_472_3776 = _rtX ->
Integrator_CSTATE_h ; } else { _rtB -> B_136_472_3776 = _rtX ->
Integrator_CSTATE_h ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
_rtB -> B_136_473_3784 [ 0 ] = _rtP -> P_390 * _rtB -> B_136_118_944 [ 28 ] *
_rtP -> P_393 ; _rtB -> B_136_473_3784 [ 1 ] = _rtP -> P_391 * _rtB ->
B_136_118_944 [ 29 ] * _rtP -> P_393 ; _rtB -> B_136_473_3784 [ 2 ] = _rtP ->
P_392 * _rtB -> B_136_118_944 [ 30 ] * _rtP -> P_393 ; rtb_B_136_1807_13824 =
_rtB -> B_136_473_3784 [ 1 ] ; rtb_B_136_1884_14440 = _rtB -> B_136_473_3784
[ 0 ] ; rtb_B_136_1808_13832 = _rtB -> B_136_473_3784 [ 2 ] ; for ( i = 0 ; i
< 3 ; i ++ ) { rtb_B_128_2256_17416 [ i ] = ( ( _rtP -> P_394 [ i + 3 ] *
rtb_B_136_1807_13824 + _rtP -> P_394 [ i ] * rtb_B_136_1884_14440 ) + _rtP ->
P_394 [ i + 6 ] * rtb_B_136_1808_13832 ) * _rtP -> P_395 ; } _rtB ->
B_136_476_3808 = muDoubleScalarHypot ( rtb_B_128_2256_17416 [ 0 ] ,
rtb_B_128_2256_17416 [ 1 ] ) ; } ssCallAccelRunBlock ( S , 136 , 659 ,
SS_CALL_MDL_OUTPUTS ) ; dVOC_monitor_network1_AutomaticGainControl ( S , _rtB
-> B_136_1003_8024 , _rtB -> B_136_469_3752 , _rtB -> B_136_472_3776 , _rtB
-> B_136_473_3784 , & _rtB -> AutomaticGainControl_k , & _rtDW ->
AutomaticGainControl_k , & _rtP -> AutomaticGainControl_k , & _rtX ->
AutomaticGainControl_k , & _rtXdis -> AutomaticGainControl_k ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX -> Integrator_CSTATE_nh >= _rtP ->
P_398 ) { if ( _rtX -> Integrator_CSTATE_nh != _rtP -> P_398 ) { _rtX ->
Integrator_CSTATE_nh = _rtP -> P_398 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_e = 3 ; } else if ( _rtX -> Integrator_CSTATE_nh <= _rtP ->
P_399 ) { if ( _rtX -> Integrator_CSTATE_nh != _rtP -> P_399 ) { _rtX ->
Integrator_CSTATE_nh = _rtP -> P_399 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_e = 4 ; } else { if ( _rtDW -> Integrator_MODE_e != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_e = 0 ; } _rtB -> B_136_477_3816 = _rtX ->
Integrator_CSTATE_nh ; } else { _rtB -> B_136_477_3816 = _rtX ->
Integrator_CSTATE_nh ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_l . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; real_T appliedDelay ; _rtB -> B_136_478_3824 =
dVOC_monitor_network1_acc_rt_VTDelayfindtDInterpolate ( ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_f , * uBuffer , _rtDW ->
VariableTransportDelay_IWORK_b . CircularBufSize , _rtDW ->
VariableTransportDelay_IWORK_b . Head , _rtDW ->
VariableTransportDelay_IWORK_b . Tail , & _rtDW ->
VariableTransportDelay_IWORK_b . Last , simTime , 0.0 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
VariableTransportDelay_IWORK_b . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK_b . Head ] == ssGetT ( S ) ) ) , _rtP -> P_401 ,
& appliedDelay ) ; } _rtB -> B_136_479_3832 = _rtX -> integrator_CSTATE_g ;
_rtB -> B_136_480_3840 = ssGetT ( S ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if
( i != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
RelationalOperator_Mode_d = ( _rtB -> B_136_480_3840 >= _rtB ->
B_136_1005_8040 ) ; } _rtB -> B_136_1283_9907 = _rtDW ->
RelationalOperator_Mode_d ; } if ( _rtB -> B_136_1283_9907 ) { _rtB ->
B_113_1207_9656 = _rtB -> B_136_479_3832 - _rtB -> B_136_478_3824 ; _rtB ->
B_113_1208_9664 = _rtB -> B_113_1207_9656 * _rtB -> B_136_469_3752 ; _rtB ->
B_136_481_3848 = _rtB -> B_113_1208_9664 ; } else { _rtB -> B_136_481_3848 =
_rtB -> B_136_1006_8048 ; } _rtB -> B_136_482_3856 = _rtB -> B_136_481_3848 *
_rtB -> AutomaticGainControl_k . B_56_1669_12744 ; _rtB -> B_136_483_3864 =
_rtP -> P_403 * _rtB -> B_136_482_3856 ; _rtB -> B_136_484_3872 = _rtP ->
P_404 * _rtB -> B_136_482_3856 ; _rtB -> B_136_485_3880 = _rtP -> P_405 *
_rtB -> B_136_482_3856 ; _rtB -> B_136_486_3888 = 0.0 ; _rtB ->
B_136_486_3888 += _rtP -> P_407 * _rtX -> TransferFcn_CSTATE_l ; _rtB ->
B_136_486_3888 += _rtP -> P_408 * _rtB -> B_136_485_3880 ; _rtB ->
B_136_487_3896 = ( _rtB -> B_136_483_3864 + _rtB -> B_136_477_3816 ) + _rtB
-> B_136_486_3888 ; if ( ssIsModeUpdateTimeStep ( S ) ) { if ( _rtB ->
B_136_487_3896 >= _rtP -> P_409 ) { _rtDW -> Saturation2_MODE_c = 1 ; } else
if ( _rtB -> B_136_487_3896 > _rtP -> P_410 ) { _rtDW -> Saturation2_MODE_c =
0 ; } else { _rtDW -> Saturation2_MODE_c = - 1 ; } } if ( _rtDW ->
Saturation2_MODE_c == 1 ) { _rtB -> B_136_488_3904 = _rtP -> P_409 ; } else
if ( _rtDW -> Saturation2_MODE_c == - 1 ) { _rtB -> B_136_488_3904 = _rtP ->
P_410 ; } else { _rtB -> B_136_488_3904 = _rtB -> B_136_487_3896 ; } _rtB ->
B_136_489_3912 = _rtP -> P_411 * _rtB -> B_136_488_3904 ; if ( _rtDW ->
LastMajorTime_n == ( rtInf ) ) { _rtB -> B_136_490_3920 = _rtB ->
B_136_489_3912 ; } else { rtb_B_136_1884_14440 = ssGetTaskTime ( S , 0 ) -
_rtDW -> LastMajorTime_n ; if ( _rtDW -> LastMajorTime_n == ssGetTaskTime ( S
, 0 ) ) { if ( _rtDW -> PrevLimited_p ) { _rtB -> B_136_490_3920 = _rtDW ->
PrevY_b ; } else { _rtB -> B_136_490_3920 = _rtB -> B_136_489_3912 ; } } else
{ rtb_B_136_1808_13832 = rtb_B_136_1884_14440 * _rtP -> P_412 ;
rtb_B_136_1807_13824 = _rtB -> B_136_489_3912 - _rtDW -> PrevY_b ; if (
rtb_B_136_1807_13824 > rtb_B_136_1808_13832 ) { _rtB -> B_136_490_3920 =
_rtDW -> PrevY_b + rtb_B_136_1808_13832 ; didZcEventOccur = true ; } else {
rtb_B_136_1884_14440 *= _rtP -> P_413 ; if ( rtb_B_136_1807_13824 <
rtb_B_136_1884_14440 ) { _rtB -> B_136_490_3920 = _rtDW -> PrevY_b +
rtb_B_136_1884_14440 ; didZcEventOccur = true ; } else { _rtB ->
B_136_490_3920 = _rtB -> B_136_489_3912 ; didZcEventOccur = false ; } } if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> PrevLimited_p = didZcEventOccur ; }
} } _rtB -> B_136_491_3928 = _rtX -> Integrator_x1_CSTATE_j ; _rtB ->
B_136_492_3936 = _rtP -> P_415 * _rtB -> B_136_491_3928 ; _rtB ->
B_136_493_3944 = _rtX -> Integrator_x2_CSTATE_m ; _rtB -> B_136_494_3952 =
_rtP -> P_417 * _rtB -> B_136_493_3944 ; _rtB -> B_136_495_3960 = _rtP ->
P_418 * _rtB -> B_136_491_3928 ; _rtB -> B_136_496_3968 = _rtP -> P_419 *
_rtB -> B_136_493_3944 ; _rtB -> B_136_497_3976 = _rtB -> B_136_492_3936 +
_rtB -> B_136_494_3952 ; _rtB -> B_136_498_3984 = _rtB -> B_136_495_3960 +
_rtB -> B_136_496_3968 ; _rtB -> B_136_499_3992 = _rtP -> P_420 * _rtB ->
B_136_490_3920 ; _rtB -> B_136_500_4000 = _rtB -> B_136_497_3976 + _rtB ->
B_136_499_3992 ; _rtB -> B_136_501_4008 = _rtP -> P_421 * _rtB ->
B_136_490_3920 ; _rtB -> B_136_502_4016 = _rtB -> B_136_498_3984 + _rtB ->
B_136_501_4008 ; _rtB -> B_136_503_4024 = ( _rtP -> P_422 * _rtB ->
B_136_491_3928 + _rtP -> P_423 * _rtB -> B_136_493_3944 ) + _rtP -> P_424 *
_rtB -> B_136_490_3920 ; if ( _rtB -> B_136_469_3752 > _rtP -> P_425 ) { _rtB
-> B_136_504_4032 = _rtP -> P_425 ; } else if ( _rtB -> B_136_469_3752 < _rtP
-> P_426 ) { _rtB -> B_136_504_4032 = _rtP -> P_426 ; } else { _rtB ->
B_136_504_4032 = _rtB -> B_136_469_3752 ; } _rtB -> B_136_505_4040 = 1.0 /
_rtB -> B_136_504_4032 ; rtb_B_136_1807_13824 = _rtB -> B_136_473_3784 [ 1 ]
; rtb_B_136_1884_14440 = _rtB -> B_136_473_3784 [ 0 ] ; rtb_B_136_1808_13832
= _rtB -> B_136_473_3784 [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) {
rtb_B_136_1854_14200 = ( _rtP -> P_427 [ i + 3 ] * rtb_B_136_1807_13824 +
_rtP -> P_427 [ i ] * rtb_B_136_1884_14440 ) + _rtP -> P_427 [ i + 6 ] *
rtb_B_136_1808_13832 ; _rtB -> B_136_506_4048 [ i ] = rtb_B_136_1854_14200 ;
_rtB -> B_136_509_4072 [ i ] = _rtP -> P_428 * rtb_B_136_1854_14200 ; }
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1263_9887 , &
_rtB -> B_136_509_4072 [ 0 ] , _rtB -> B_136_472_3776 , & _rtB ->
Subsystempi2delay_kj , & _rtDW -> Subsystempi2delay_kj ) ;
dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1262_9886 , & _rtB ->
B_136_509_4072 [ 0 ] , _rtB -> B_136_472_3776 , & _rtB -> Subsystem1_a , &
_rtDW -> Subsystem1_a ) ; if ( _rtB -> B_136_1262_9886 != 0 ) { _rtB ->
B_136_512_4096 [ 0 ] = _rtB -> Subsystem1_a . B_25_1750_13368 ; _rtB ->
B_136_512_4096 [ 1 ] = _rtB -> Subsystem1_a . B_25_1751_13376 ; } else { _rtB
-> B_136_512_4096 [ 0 ] = _rtB -> Subsystempi2delay_kj . B_24_1752_13384 ;
_rtB -> B_136_512_4096 [ 1 ] = _rtB -> Subsystempi2delay_kj . B_24_1753_13392
; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_136_514_4112
= _rtDW -> Memory_PreviousInput_j ; if ( ssIsModeUpdateTimeStep ( S ) ) {
_rtDW -> RelationalOperator_Mode_g = ( _rtX -> Integrator_CSTATE_a > _rtB ->
B_136_1008_8064 ) ; } _rtB -> B_136_1284_9908 = _rtDW ->
RelationalOperator_Mode_g ; } _rtB -> B_136_515_4120 = _rtX ->
Integrator_CSTATE_a - _rtB -> B_136_1008_8064 ; if ( ( _rtDW ->
Initial_FirstOutputTime_e == ( rtMinusInf ) ) || ( _rtDW ->
Initial_FirstOutputTime_e == ssGetTaskTime ( S , 0 ) ) ) { _rtDW ->
Initial_FirstOutputTime_e = ssGetTaskTime ( S , 0 ) ; _rtB -> B_136_516_4128
= _rtP -> P_430 ; } else { _rtB -> B_136_516_4128 = _rtB -> B_136_515_4120 ;
} if ( ssIsModeUpdateTimeStep ( S ) ) { didZcEventOccur = ( _rtB ->
B_136_1284_9908 && ( _rtZCE -> Integrator_Reset_ZCE_i != POS_ZCSIG ) ) ;
_rtZCE -> Integrator_Reset_ZCE_i = _rtB -> B_136_1284_9908 ; if (
didZcEventOccur || ( _rtDW -> Integrator_IWORK_f != 0 ) ) { didZcEventOccur =
( _rtX -> Integrator_CSTATE_a != _rtB -> B_136_516_4128 ) ; _rtX ->
Integrator_CSTATE_a = _rtB -> B_136_516_4128 ; if ( didZcEventOccur ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } } if ( _rtX ->
Integrator_CSTATE_a >= _rtP -> P_431 ) { if ( _rtX -> Integrator_CSTATE_a !=
_rtP -> P_431 ) { _rtX -> Integrator_CSTATE_a = _rtP -> P_431 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_h = 3 ; } else if ( _rtX -> Integrator_CSTATE_a <= _rtP ->
P_432 ) { if ( _rtX -> Integrator_CSTATE_a != _rtP -> P_432 ) { _rtX ->
Integrator_CSTATE_a = _rtP -> P_432 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_h = 4 ; } else { if ( _rtDW -> Integrator_MODE_h != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_h = 0 ; } _rtB -> B_136_517_4136 = _rtX ->
Integrator_CSTATE_a ; } else { _rtB -> B_136_517_4136 = _rtX ->
Integrator_CSTATE_a ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
_rtB -> B_136_518_4144 [ 0 ] = _rtP -> P_433 * _rtB -> B_136_118_944 [ 34 ] *
_rtP -> P_436 ; _rtB -> B_136_518_4144 [ 1 ] = _rtP -> P_434 * _rtB ->
B_136_118_944 [ 35 ] * _rtP -> P_436 ; _rtB -> B_136_518_4144 [ 2 ] = _rtP ->
P_435 * _rtB -> B_136_118_944 [ 36 ] * _rtP -> P_436 ; rtb_B_136_1807_13824 =
_rtB -> B_136_518_4144 [ 1 ] ; rtb_B_136_1884_14440 = _rtB -> B_136_518_4144
[ 0 ] ; rtb_B_136_1808_13832 = _rtB -> B_136_518_4144 [ 2 ] ; for ( i = 0 ; i
< 3 ; i ++ ) { rtb_B_128_2256_17416 [ i ] = ( ( _rtP -> P_437 [ i + 3 ] *
rtb_B_136_1807_13824 + _rtP -> P_437 [ i ] * rtb_B_136_1884_14440 ) + _rtP ->
P_437 [ i + 6 ] * rtb_B_136_1808_13832 ) * _rtP -> P_438 ; } _rtB ->
B_136_521_4168 = muDoubleScalarHypot ( rtb_B_128_2256_17416 [ 0 ] ,
rtb_B_128_2256_17416 [ 1 ] ) ; } ssCallAccelRunBlock ( S , 136 , 714 ,
SS_CALL_MDL_OUTPUTS ) ; dVOC_monitor_network1_AutomaticGainControl ( S , _rtB
-> B_136_1007_8056 , _rtB -> B_136_514_4112 , _rtB -> B_136_517_4136 , _rtB
-> B_136_518_4144 , & _rtB -> AutomaticGainControl_c , & _rtDW ->
AutomaticGainControl_c , & _rtP -> AutomaticGainControl_c , & _rtX ->
AutomaticGainControl_c , & _rtXdis -> AutomaticGainControl_c ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX -> Integrator_CSTATE_m >= _rtP ->
P_441 ) { if ( _rtX -> Integrator_CSTATE_m != _rtP -> P_441 ) { _rtX ->
Integrator_CSTATE_m = _rtP -> P_441 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_n = 3 ; } else if ( _rtX -> Integrator_CSTATE_m <= _rtP ->
P_442 ) { if ( _rtX -> Integrator_CSTATE_m != _rtP -> P_442 ) { _rtX ->
Integrator_CSTATE_m = _rtP -> P_442 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_n = 4 ; } else { if ( _rtDW -> Integrator_MODE_n != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_n = 0 ; } _rtB -> B_136_522_4176 = _rtX ->
Integrator_CSTATE_m ; } else { _rtB -> B_136_522_4176 = _rtX ->
Integrator_CSTATE_m ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_m . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; real_T appliedDelay ; _rtB -> B_136_523_4184 =
dVOC_monitor_network1_acc_rt_VTDelayfindtDInterpolate ( ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_j , * uBuffer , _rtDW ->
VariableTransportDelay_IWORK_k . CircularBufSize , _rtDW ->
VariableTransportDelay_IWORK_k . Head , _rtDW ->
VariableTransportDelay_IWORK_k . Tail , & _rtDW ->
VariableTransportDelay_IWORK_k . Last , simTime , 0.0 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
VariableTransportDelay_IWORK_k . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK_k . Head ] == ssGetT ( S ) ) ) , _rtP -> P_444 ,
& appliedDelay ) ; } _rtB -> B_136_524_4192 = _rtX -> integrator_CSTATE_d ;
_rtB -> B_136_525_4200 = ssGetT ( S ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if
( i != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
RelationalOperator_Mode_lj = ( _rtB -> B_136_525_4200 >= _rtB ->
B_136_1009_8072 ) ; } _rtB -> B_136_1285_9909 = _rtDW ->
RelationalOperator_Mode_lj ; } if ( _rtB -> B_136_1285_9909 ) { _rtB ->
B_121_1205_9640 = _rtB -> B_136_524_4192 - _rtB -> B_136_523_4184 ; _rtB ->
B_121_1206_9648 = _rtB -> B_121_1205_9640 * _rtB -> B_136_514_4112 ; _rtB ->
B_136_526_4208 = _rtB -> B_121_1206_9648 ; } else { _rtB -> B_136_526_4208 =
_rtB -> B_136_1010_8080 ; } _rtB -> B_136_527_4216 = _rtB -> B_136_526_4208 *
_rtB -> AutomaticGainControl_c . B_56_1669_12744 ; _rtB -> B_136_528_4224 =
_rtP -> P_446 * _rtB -> B_136_527_4216 ; _rtB -> B_136_529_4232 = _rtP ->
P_447 * _rtB -> B_136_527_4216 ; _rtB -> B_136_530_4240 = _rtP -> P_448 *
_rtB -> B_136_527_4216 ; _rtB -> B_136_531_4248 = 0.0 ; _rtB ->
B_136_531_4248 += _rtP -> P_450 * _rtX -> TransferFcn_CSTATE_f ; _rtB ->
B_136_531_4248 += _rtP -> P_451 * _rtB -> B_136_530_4240 ; _rtB ->
B_136_532_4256 = ( _rtB -> B_136_528_4224 + _rtB -> B_136_522_4176 ) + _rtB
-> B_136_531_4248 ; if ( ssIsModeUpdateTimeStep ( S ) ) { if ( _rtB ->
B_136_532_4256 >= _rtP -> P_452 ) { _rtDW -> Saturation2_MODE_e = 1 ; } else
if ( _rtB -> B_136_532_4256 > _rtP -> P_453 ) { _rtDW -> Saturation2_MODE_e =
0 ; } else { _rtDW -> Saturation2_MODE_e = - 1 ; } } if ( _rtDW ->
Saturation2_MODE_e == 1 ) { _rtB -> B_136_533_4264 = _rtP -> P_452 ; } else
if ( _rtDW -> Saturation2_MODE_e == - 1 ) { _rtB -> B_136_533_4264 = _rtP ->
P_453 ; } else { _rtB -> B_136_533_4264 = _rtB -> B_136_532_4256 ; } _rtB ->
B_136_534_4272 = _rtP -> P_454 * _rtB -> B_136_533_4264 ; if ( _rtDW ->
LastMajorTime_d == ( rtInf ) ) { _rtB -> B_136_535_4280 = _rtB ->
B_136_534_4272 ; } else { rtb_B_136_1884_14440 = ssGetTaskTime ( S , 0 ) -
_rtDW -> LastMajorTime_d ; if ( _rtDW -> LastMajorTime_d == ssGetTaskTime ( S
, 0 ) ) { if ( _rtDW -> PrevLimited_m ) { _rtB -> B_136_535_4280 = _rtDW ->
PrevY_n ; } else { _rtB -> B_136_535_4280 = _rtB -> B_136_534_4272 ; } } else
{ rtb_B_136_1808_13832 = rtb_B_136_1884_14440 * _rtP -> P_455 ;
rtb_B_136_1807_13824 = _rtB -> B_136_534_4272 - _rtDW -> PrevY_n ; if (
rtb_B_136_1807_13824 > rtb_B_136_1808_13832 ) { _rtB -> B_136_535_4280 =
_rtDW -> PrevY_n + rtb_B_136_1808_13832 ; didZcEventOccur = true ; } else {
rtb_B_136_1884_14440 *= _rtP -> P_456 ; if ( rtb_B_136_1807_13824 <
rtb_B_136_1884_14440 ) { _rtB -> B_136_535_4280 = _rtDW -> PrevY_n +
rtb_B_136_1884_14440 ; didZcEventOccur = true ; } else { _rtB ->
B_136_535_4280 = _rtB -> B_136_534_4272 ; didZcEventOccur = false ; } } if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> PrevLimited_m = didZcEventOccur ; }
} } _rtB -> B_136_536_4288 = _rtX -> Integrator_x1_CSTATE_m ; _rtB ->
B_136_537_4296 = _rtP -> P_458 * _rtB -> B_136_536_4288 ; _rtB ->
B_136_538_4304 = _rtX -> Integrator_x2_CSTATE_g ; _rtB -> B_136_539_4312 =
_rtP -> P_460 * _rtB -> B_136_538_4304 ; _rtB -> B_136_540_4320 = _rtP ->
P_461 * _rtB -> B_136_536_4288 ; _rtB -> B_136_541_4328 = _rtP -> P_462 *
_rtB -> B_136_538_4304 ; _rtB -> B_136_542_4336 = _rtB -> B_136_537_4296 +
_rtB -> B_136_539_4312 ; _rtB -> B_136_543_4344 = _rtB -> B_136_540_4320 +
_rtB -> B_136_541_4328 ; _rtB -> B_136_544_4352 = _rtP -> P_463 * _rtB ->
B_136_535_4280 ; _rtB -> B_136_545_4360 = _rtB -> B_136_542_4336 + _rtB ->
B_136_544_4352 ; _rtB -> B_136_546_4368 = _rtP -> P_464 * _rtB ->
B_136_535_4280 ; _rtB -> B_136_547_4376 = _rtB -> B_136_543_4344 + _rtB ->
B_136_546_4368 ; _rtB -> B_136_548_4384 = ( _rtP -> P_465 * _rtB ->
B_136_536_4288 + _rtP -> P_466 * _rtB -> B_136_538_4304 ) + _rtP -> P_467 *
_rtB -> B_136_535_4280 ; if ( _rtB -> B_136_514_4112 > _rtP -> P_468 ) { _rtB
-> B_136_549_4392 = _rtP -> P_468 ; } else if ( _rtB -> B_136_514_4112 < _rtP
-> P_469 ) { _rtB -> B_136_549_4392 = _rtP -> P_469 ; } else { _rtB ->
B_136_549_4392 = _rtB -> B_136_514_4112 ; } _rtB -> B_136_550_4400 = 1.0 /
_rtB -> B_136_549_4392 ; rtb_B_136_1807_13824 = _rtB -> B_136_518_4144 [ 1 ]
; rtb_B_136_1884_14440 = _rtB -> B_136_518_4144 [ 0 ] ; rtb_B_136_1808_13832
= _rtB -> B_136_518_4144 [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) {
rtb_B_136_1854_14200 = ( _rtP -> P_470 [ i + 3 ] * rtb_B_136_1807_13824 +
_rtP -> P_470 [ i ] * rtb_B_136_1884_14440 ) + _rtP -> P_470 [ i + 6 ] *
rtb_B_136_1808_13832 ; _rtB -> B_136_551_4408 [ i ] = rtb_B_136_1854_14200 ;
_rtB -> B_136_554_4432 [ i ] = _rtP -> P_471 * rtb_B_136_1854_14200 ; }
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1265_9889 , &
_rtB -> B_136_554_4432 [ 0 ] , _rtB -> B_136_517_4136 , & _rtB ->
Subsystempi2delay_lp , & _rtDW -> Subsystempi2delay_lp ) ;
dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1264_9888 , & _rtB ->
B_136_554_4432 [ 0 ] , _rtB -> B_136_517_4136 , & _rtB -> Subsystem1_p1 , &
_rtDW -> Subsystem1_p1 ) ; if ( _rtB -> B_136_1264_9888 != 0 ) { _rtB ->
B_136_557_4456 [ 0 ] = _rtB -> Subsystem1_p1 . B_25_1750_13368 ; _rtB ->
B_136_557_4456 [ 1 ] = _rtB -> Subsystem1_p1 . B_25_1751_13376 ; } else {
_rtB -> B_136_557_4456 [ 0 ] = _rtB -> Subsystempi2delay_lp . B_24_1752_13384
; _rtB -> B_136_557_4456 [ 1 ] = _rtB -> Subsystempi2delay_lp .
B_24_1753_13392 ; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB ->
B_136_559_4472 = _rtDW -> Memory_PreviousInput_m ; if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> RelationalOperator_Mode_k = ( _rtX
-> Integrator_CSTATE_c > _rtB -> B_136_1012_8096 ) ; } _rtB ->
B_136_1286_9910 = _rtDW -> RelationalOperator_Mode_k ; } _rtB ->
B_136_560_4480 = _rtX -> Integrator_CSTATE_c - _rtB -> B_136_1012_8096 ; if (
( _rtDW -> Initial_FirstOutputTime_d == ( rtMinusInf ) ) || ( _rtDW ->
Initial_FirstOutputTime_d == ssGetTaskTime ( S , 0 ) ) ) { _rtDW ->
Initial_FirstOutputTime_d = ssGetTaskTime ( S , 0 ) ; _rtB -> B_136_561_4488
= _rtP -> P_473 ; } else { _rtB -> B_136_561_4488 = _rtB -> B_136_560_4480 ;
} if ( ssIsModeUpdateTimeStep ( S ) ) { didZcEventOccur = ( _rtB ->
B_136_1286_9910 && ( _rtZCE -> Integrator_Reset_ZCE_l != POS_ZCSIG ) ) ;
_rtZCE -> Integrator_Reset_ZCE_l = _rtB -> B_136_1286_9910 ; if (
didZcEventOccur || ( _rtDW -> Integrator_IWORK_k != 0 ) ) { didZcEventOccur =
( _rtX -> Integrator_CSTATE_c != _rtB -> B_136_561_4488 ) ; _rtX ->
Integrator_CSTATE_c = _rtB -> B_136_561_4488 ; if ( didZcEventOccur ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } } if ( _rtX ->
Integrator_CSTATE_c >= _rtP -> P_474 ) { if ( _rtX -> Integrator_CSTATE_c !=
_rtP -> P_474 ) { _rtX -> Integrator_CSTATE_c = _rtP -> P_474 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_k4 = 3 ; } else if ( _rtX -> Integrator_CSTATE_c <= _rtP ->
P_475 ) { if ( _rtX -> Integrator_CSTATE_c != _rtP -> P_475 ) { _rtX ->
Integrator_CSTATE_c = _rtP -> P_475 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_k4 = 4 ; } else { if ( _rtDW -> Integrator_MODE_k4 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_k4 = 0 ; } _rtB -> B_136_562_4496 = _rtX ->
Integrator_CSTATE_c ; } else { _rtB -> B_136_562_4496 = _rtX ->
Integrator_CSTATE_c ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
_rtB -> B_136_563_4504 [ 0 ] = _rtP -> P_476 * _rtB -> B_136_118_944 [ 22 ] *
_rtP -> P_479 ; _rtB -> B_136_563_4504 [ 1 ] = _rtP -> P_477 * _rtB ->
B_136_118_944 [ 23 ] * _rtP -> P_479 ; _rtB -> B_136_563_4504 [ 2 ] = _rtP ->
P_478 * _rtB -> B_136_118_944 [ 24 ] * _rtP -> P_479 ; rtb_B_136_1807_13824 =
_rtB -> B_136_563_4504 [ 1 ] ; rtb_B_136_1884_14440 = _rtB -> B_136_563_4504
[ 0 ] ; rtb_B_136_1808_13832 = _rtB -> B_136_563_4504 [ 2 ] ; for ( i = 0 ; i
< 3 ; i ++ ) { rtb_B_128_2256_17416 [ i ] = ( ( _rtP -> P_480 [ i + 3 ] *
rtb_B_136_1807_13824 + _rtP -> P_480 [ i ] * rtb_B_136_1884_14440 ) + _rtP ->
P_480 [ i + 6 ] * rtb_B_136_1808_13832 ) * _rtP -> P_481 ; } _rtB ->
B_136_566_4528 = muDoubleScalarHypot ( rtb_B_128_2256_17416 [ 0 ] ,
rtb_B_128_2256_17416 [ 1 ] ) ; } ssCallAccelRunBlock ( S , 136 , 769 ,
SS_CALL_MDL_OUTPUTS ) ; dVOC_monitor_network1_AutomaticGainControl ( S , _rtB
-> B_136_1011_8088 , _rtB -> B_136_559_4472 , _rtB -> B_136_562_4496 , _rtB
-> B_136_563_4504 , & _rtB -> AutomaticGainControl_b , & _rtDW ->
AutomaticGainControl_b , & _rtP -> AutomaticGainControl_b , & _rtX ->
AutomaticGainControl_b , & _rtXdis -> AutomaticGainControl_b ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX -> Integrator_CSTATE_f >= _rtP ->
P_484 ) { if ( _rtX -> Integrator_CSTATE_f != _rtP -> P_484 ) { _rtX ->
Integrator_CSTATE_f = _rtP -> P_484 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_k5 = 3 ; } else if ( _rtX -> Integrator_CSTATE_f <= _rtP ->
P_485 ) { if ( _rtX -> Integrator_CSTATE_f != _rtP -> P_485 ) { _rtX ->
Integrator_CSTATE_f = _rtP -> P_485 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_k5 = 4 ; } else { if ( _rtDW -> Integrator_MODE_k5 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_k5 = 0 ; } _rtB -> B_136_567_4536 = _rtX ->
Integrator_CSTATE_f ; } else { _rtB -> B_136_567_4536 = _rtX ->
Integrator_CSTATE_f ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_p . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; real_T appliedDelay ; _rtB -> B_136_568_4544 =
dVOC_monitor_network1_acc_rt_VTDelayfindtDInterpolate ( ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_g , * uBuffer , _rtDW ->
VariableTransportDelay_IWORK_ka . CircularBufSize , _rtDW ->
VariableTransportDelay_IWORK_ka . Head , _rtDW ->
VariableTransportDelay_IWORK_ka . Tail , & _rtDW ->
VariableTransportDelay_IWORK_ka . Last , simTime , 0.0 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
VariableTransportDelay_IWORK_ka . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK_ka . Head ] == ssGetT ( S ) ) ) , _rtP -> P_487
, & appliedDelay ) ; } _rtB -> B_136_569_4552 = _rtX -> integrator_CSTATE_m ;
_rtB -> B_136_570_4560 = ssGetT ( S ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if
( i != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
RelationalOperator_Mode_j = ( _rtB -> B_136_570_4560 >= _rtB ->
B_136_1013_8104 ) ; } _rtB -> B_136_1287_9911 = _rtDW ->
RelationalOperator_Mode_j ; } if ( _rtB -> B_136_1287_9911 ) { _rtB ->
B_73_1217_9736 = _rtB -> B_136_569_4552 - _rtB -> B_136_568_4544 ; _rtB ->
B_73_1218_9744 = _rtB -> B_73_1217_9736 * _rtB -> B_136_559_4472 ; _rtB ->
B_136_571_4568 = _rtB -> B_73_1218_9744 ; } else { _rtB -> B_136_571_4568 =
_rtB -> B_136_1014_8112 ; } _rtB -> B_136_572_4576 = _rtB -> B_136_571_4568 *
_rtB -> AutomaticGainControl_b . B_56_1669_12744 ; _rtB -> B_136_573_4584 =
_rtP -> P_489 * _rtB -> B_136_572_4576 ; _rtB -> B_136_574_4592 = _rtP ->
P_490 * _rtB -> B_136_572_4576 ; _rtB -> B_136_575_4600 = _rtP -> P_491 *
_rtB -> B_136_572_4576 ; _rtB -> B_136_576_4608 = 0.0 ; _rtB ->
B_136_576_4608 += _rtP -> P_493 * _rtX -> TransferFcn_CSTATE_a ; _rtB ->
B_136_576_4608 += _rtP -> P_494 * _rtB -> B_136_575_4600 ; _rtB ->
B_136_577_4616 = ( _rtB -> B_136_573_4584 + _rtB -> B_136_567_4536 ) + _rtB
-> B_136_576_4608 ; if ( ssIsModeUpdateTimeStep ( S ) ) { if ( _rtB ->
B_136_577_4616 >= _rtP -> P_495 ) { _rtDW -> Saturation2_MODE_l = 1 ; } else
if ( _rtB -> B_136_577_4616 > _rtP -> P_496 ) { _rtDW -> Saturation2_MODE_l =
0 ; } else { _rtDW -> Saturation2_MODE_l = - 1 ; } } if ( _rtDW ->
Saturation2_MODE_l == 1 ) { _rtB -> B_136_578_4624 = _rtP -> P_495 ; } else
if ( _rtDW -> Saturation2_MODE_l == - 1 ) { _rtB -> B_136_578_4624 = _rtP ->
P_496 ; } else { _rtB -> B_136_578_4624 = _rtB -> B_136_577_4616 ; } _rtB ->
B_136_579_4632 = _rtP -> P_497 * _rtB -> B_136_578_4624 ; if ( _rtDW ->
LastMajorTime_k == ( rtInf ) ) { _rtB -> B_136_580_4640 = _rtB ->
B_136_579_4632 ; } else { rtb_B_136_1884_14440 = ssGetTaskTime ( S , 0 ) -
_rtDW -> LastMajorTime_k ; if ( _rtDW -> LastMajorTime_k == ssGetTaskTime ( S
, 0 ) ) { if ( _rtDW -> PrevLimited_a ) { _rtB -> B_136_580_4640 = _rtDW ->
PrevY_e ; } else { _rtB -> B_136_580_4640 = _rtB -> B_136_579_4632 ; } } else
{ rtb_B_136_1808_13832 = rtb_B_136_1884_14440 * _rtP -> P_498 ;
rtb_B_136_1807_13824 = _rtB -> B_136_579_4632 - _rtDW -> PrevY_e ; if (
rtb_B_136_1807_13824 > rtb_B_136_1808_13832 ) { _rtB -> B_136_580_4640 =
_rtDW -> PrevY_e + rtb_B_136_1808_13832 ; didZcEventOccur = true ; } else {
rtb_B_136_1884_14440 *= _rtP -> P_499 ; if ( rtb_B_136_1807_13824 <
rtb_B_136_1884_14440 ) { _rtB -> B_136_580_4640 = _rtDW -> PrevY_e +
rtb_B_136_1884_14440 ; didZcEventOccur = true ; } else { _rtB ->
B_136_580_4640 = _rtB -> B_136_579_4632 ; didZcEventOccur = false ; } } if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> PrevLimited_a = didZcEventOccur ; }
} } _rtB -> B_136_581_4648 = _rtX -> Integrator_x1_CSTATE_f ; _rtB ->
B_136_582_4656 = _rtP -> P_501 * _rtB -> B_136_581_4648 ; _rtB ->
B_136_583_4664 = _rtX -> Integrator_x2_CSTATE_o ; _rtB -> B_136_584_4672 =
_rtP -> P_503 * _rtB -> B_136_583_4664 ; _rtB -> B_136_585_4680 = _rtP ->
P_504 * _rtB -> B_136_581_4648 ; _rtB -> B_136_586_4688 = _rtP -> P_505 *
_rtB -> B_136_583_4664 ; _rtB -> B_136_587_4696 = _rtB -> B_136_582_4656 +
_rtB -> B_136_584_4672 ; _rtB -> B_136_588_4704 = _rtB -> B_136_585_4680 +
_rtB -> B_136_586_4688 ; _rtB -> B_136_589_4712 = _rtP -> P_506 * _rtB ->
B_136_580_4640 ; _rtB -> B_136_590_4720 = _rtB -> B_136_587_4696 + _rtB ->
B_136_589_4712 ; _rtB -> B_136_591_4728 = _rtP -> P_507 * _rtB ->
B_136_580_4640 ; _rtB -> B_136_592_4736 = _rtB -> B_136_588_4704 + _rtB ->
B_136_591_4728 ; _rtB -> B_136_593_4744 = ( _rtP -> P_508 * _rtB ->
B_136_581_4648 + _rtP -> P_509 * _rtB -> B_136_583_4664 ) + _rtP -> P_510 *
_rtB -> B_136_580_4640 ; if ( _rtB -> B_136_559_4472 > _rtP -> P_511 ) { _rtB
-> B_136_594_4752 = _rtP -> P_511 ; } else if ( _rtB -> B_136_559_4472 < _rtP
-> P_512 ) { _rtB -> B_136_594_4752 = _rtP -> P_512 ; } else { _rtB ->
B_136_594_4752 = _rtB -> B_136_559_4472 ; } _rtB -> B_136_595_4760 = 1.0 /
_rtB -> B_136_594_4752 ; rtb_B_136_1807_13824 = _rtB -> B_136_563_4504 [ 1 ]
; rtb_B_136_1884_14440 = _rtB -> B_136_563_4504 [ 0 ] ; rtb_B_136_1808_13832
= _rtB -> B_136_563_4504 [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) {
rtb_B_136_1854_14200 = ( _rtP -> P_513 [ i + 3 ] * rtb_B_136_1807_13824 +
_rtP -> P_513 [ i ] * rtb_B_136_1884_14440 ) + _rtP -> P_513 [ i + 6 ] *
rtb_B_136_1808_13832 ; _rtB -> B_136_596_4768 [ i ] = rtb_B_136_1854_14200 ;
_rtB -> B_136_599_4792 [ i ] = _rtP -> P_514 * rtb_B_136_1854_14200 ; }
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1267_9891 , &
_rtB -> B_136_599_4792 [ 0 ] , _rtB -> B_136_562_4496 , & _rtB ->
Subsystempi2delay_p , & _rtDW -> Subsystempi2delay_p ) ;
dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1266_9890 , & _rtB ->
B_136_599_4792 [ 0 ] , _rtB -> B_136_562_4496 , & _rtB -> Subsystem1_e4 , &
_rtDW -> Subsystem1_e4 ) ; if ( _rtB -> B_136_1266_9890 != 0 ) { _rtB ->
B_136_602_4816 [ 0 ] = _rtB -> Subsystem1_e4 . B_25_1750_13368 ; _rtB ->
B_136_602_4816 [ 1 ] = _rtB -> Subsystem1_e4 . B_25_1751_13376 ; } else {
_rtB -> B_136_602_4816 [ 0 ] = _rtB -> Subsystempi2delay_p . B_24_1752_13384
; _rtB -> B_136_602_4816 [ 1 ] = _rtB -> Subsystempi2delay_p .
B_24_1753_13392 ; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB ->
B_136_604_4832 = _rtDW -> Memory_PreviousInput_g ; if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> RelationalOperator_Mode_je = ( _rtX
-> Integrator_CSTATE_c0 > _rtB -> B_136_1016_8128 ) ; } _rtB ->
B_136_1288_9912 = _rtDW -> RelationalOperator_Mode_je ; } _rtB ->
B_136_605_4840 = _rtX -> Integrator_CSTATE_c0 - _rtB -> B_136_1016_8128 ; if
( ( _rtDW -> Initial_FirstOutputTime_du == ( rtMinusInf ) ) || ( _rtDW ->
Initial_FirstOutputTime_du == ssGetTaskTime ( S , 0 ) ) ) { _rtDW ->
Initial_FirstOutputTime_du = ssGetTaskTime ( S , 0 ) ; _rtB -> B_136_606_4848
= _rtP -> P_516 ; } else { _rtB -> B_136_606_4848 = _rtB -> B_136_605_4840 ;
} if ( ssIsModeUpdateTimeStep ( S ) ) { didZcEventOccur = ( _rtB ->
B_136_1288_9912 && ( _rtZCE -> Integrator_Reset_ZCE_o != POS_ZCSIG ) ) ;
_rtZCE -> Integrator_Reset_ZCE_o = _rtB -> B_136_1288_9912 ; if (
didZcEventOccur || ( _rtDW -> Integrator_IWORK_b != 0 ) ) { didZcEventOccur =
( _rtX -> Integrator_CSTATE_c0 != _rtB -> B_136_606_4848 ) ; _rtX ->
Integrator_CSTATE_c0 = _rtB -> B_136_606_4848 ; if ( didZcEventOccur ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } } if ( _rtX ->
Integrator_CSTATE_c0 >= _rtP -> P_517 ) { if ( _rtX -> Integrator_CSTATE_c0
!= _rtP -> P_517 ) { _rtX -> Integrator_CSTATE_c0 = _rtP -> P_517 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_d = 3 ; } else if ( _rtX -> Integrator_CSTATE_c0 <= _rtP ->
P_518 ) { if ( _rtX -> Integrator_CSTATE_c0 != _rtP -> P_518 ) { _rtX ->
Integrator_CSTATE_c0 = _rtP -> P_518 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_d = 4 ; } else { if ( _rtDW -> Integrator_MODE_d != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_d = 0 ; } _rtB -> B_136_607_4856 = _rtX ->
Integrator_CSTATE_c0 ; } else { _rtB -> B_136_607_4856 = _rtX ->
Integrator_CSTATE_c0 ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
_rtB -> B_136_608_4864 [ 0 ] = _rtP -> P_519 * _rtB -> B_136_118_944 [ 19 ] *
_rtP -> P_522 ; _rtB -> B_136_608_4864 [ 1 ] = _rtP -> P_520 * _rtB ->
B_136_118_944 [ 20 ] * _rtP -> P_522 ; _rtB -> B_136_608_4864 [ 2 ] = _rtP ->
P_521 * _rtB -> B_136_118_944 [ 21 ] * _rtP -> P_522 ; rtb_B_136_1807_13824 =
_rtB -> B_136_608_4864 [ 1 ] ; rtb_B_136_1884_14440 = _rtB -> B_136_608_4864
[ 0 ] ; rtb_B_136_1808_13832 = _rtB -> B_136_608_4864 [ 2 ] ; for ( i = 0 ; i
< 3 ; i ++ ) { rtb_B_128_2256_17416 [ i ] = ( ( _rtP -> P_523 [ i + 3 ] *
rtb_B_136_1807_13824 + _rtP -> P_523 [ i ] * rtb_B_136_1884_14440 ) + _rtP ->
P_523 [ i + 6 ] * rtb_B_136_1808_13832 ) * _rtP -> P_524 ; } _rtB ->
B_136_611_4888 = muDoubleScalarHypot ( rtb_B_128_2256_17416 [ 0 ] ,
rtb_B_128_2256_17416 [ 1 ] ) ; } ssCallAccelRunBlock ( S , 136 , 824 ,
SS_CALL_MDL_OUTPUTS ) ; dVOC_monitor_network1_AutomaticGainControl ( S , _rtB
-> B_136_1015_8120 , _rtB -> B_136_604_4832 , _rtB -> B_136_607_4856 , _rtB
-> B_136_608_4864 , & _rtB -> AutomaticGainControl_l , & _rtDW ->
AutomaticGainControl_l , & _rtP -> AutomaticGainControl_l , & _rtX ->
AutomaticGainControl_l , & _rtXdis -> AutomaticGainControl_l ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX -> Integrator_CSTATE_b >= _rtP ->
P_527 ) { if ( _rtX -> Integrator_CSTATE_b != _rtP -> P_527 ) { _rtX ->
Integrator_CSTATE_b = _rtP -> P_527 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_i = 3 ; } else if ( _rtX -> Integrator_CSTATE_b <= _rtP ->
P_528 ) { if ( _rtX -> Integrator_CSTATE_b != _rtP -> P_528 ) { _rtX ->
Integrator_CSTATE_b = _rtP -> P_528 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_i = 4 ; } else { if ( _rtDW -> Integrator_MODE_i != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_i = 0 ; } _rtB -> B_136_612_4896 = _rtX ->
Integrator_CSTATE_b ; } else { _rtB -> B_136_612_4896 = _rtX ->
Integrator_CSTATE_b ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_f . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; real_T appliedDelay ; _rtB -> B_136_613_4904 =
dVOC_monitor_network1_acc_rt_VTDelayfindtDInterpolate ( ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_o , * uBuffer , _rtDW ->
VariableTransportDelay_IWORK_i . CircularBufSize , _rtDW ->
VariableTransportDelay_IWORK_i . Head , _rtDW ->
VariableTransportDelay_IWORK_i . Tail , & _rtDW ->
VariableTransportDelay_IWORK_i . Last , simTime , 0.0 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
VariableTransportDelay_IWORK_i . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK_i . Head ] == ssGetT ( S ) ) ) , _rtP -> P_530 ,
& appliedDelay ) ; } _rtB -> B_136_614_4912 = _rtX -> integrator_CSTATE_o ;
_rtB -> B_136_615_4920 = ssGetT ( S ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if
( i != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
RelationalOperator_Mode_du = ( _rtB -> B_136_615_4920 >= _rtB ->
B_136_1017_8136 ) ; } _rtB -> B_136_1289_9913 = _rtDW ->
RelationalOperator_Mode_du ; } if ( _rtB -> B_136_1289_9913 ) { _rtB ->
B_81_1215_9720 = _rtB -> B_136_614_4912 - _rtB -> B_136_613_4904 ; _rtB ->
B_81_1216_9728 = _rtB -> B_81_1215_9720 * _rtB -> B_136_604_4832 ; _rtB ->
B_136_616_4928 = _rtB -> B_81_1216_9728 ; } else { _rtB -> B_136_616_4928 =
_rtB -> B_136_1018_8144 ; } _rtB -> B_136_617_4936 = _rtB -> B_136_616_4928 *
_rtB -> AutomaticGainControl_l . B_56_1669_12744 ; _rtB -> B_136_618_4944 =
_rtP -> P_532 * _rtB -> B_136_617_4936 ; _rtB -> B_136_619_4952 = _rtP ->
P_533 * _rtB -> B_136_617_4936 ; _rtB -> B_136_620_4960 = _rtP -> P_534 *
_rtB -> B_136_617_4936 ; _rtB -> B_136_621_4968 = 0.0 ; _rtB ->
B_136_621_4968 += _rtP -> P_536 * _rtX -> TransferFcn_CSTATE_ac ; _rtB ->
B_136_621_4968 += _rtP -> P_537 * _rtB -> B_136_620_4960 ; _rtB ->
B_136_622_4976 = ( _rtB -> B_136_618_4944 + _rtB -> B_136_612_4896 ) + _rtB
-> B_136_621_4968 ; if ( ssIsModeUpdateTimeStep ( S ) ) { if ( _rtB ->
B_136_622_4976 >= _rtP -> P_538 ) { _rtDW -> Saturation2_MODE_n = 1 ; } else
if ( _rtB -> B_136_622_4976 > _rtP -> P_539 ) { _rtDW -> Saturation2_MODE_n =
0 ; } else { _rtDW -> Saturation2_MODE_n = - 1 ; } } if ( _rtDW ->
Saturation2_MODE_n == 1 ) { _rtB -> B_136_623_4984 = _rtP -> P_538 ; } else
if ( _rtDW -> Saturation2_MODE_n == - 1 ) { _rtB -> B_136_623_4984 = _rtP ->
P_539 ; } else { _rtB -> B_136_623_4984 = _rtB -> B_136_622_4976 ; } _rtB ->
B_136_624_4992 = _rtP -> P_540 * _rtB -> B_136_623_4984 ; if ( _rtDW ->
LastMajorTime_e == ( rtInf ) ) { _rtB -> B_136_625_5000 = _rtB ->
B_136_624_4992 ; } else { rtb_B_136_1884_14440 = ssGetTaskTime ( S , 0 ) -
_rtDW -> LastMajorTime_e ; if ( _rtDW -> LastMajorTime_e == ssGetTaskTime ( S
, 0 ) ) { if ( _rtDW -> PrevLimited_k ) { _rtB -> B_136_625_5000 = _rtDW ->
PrevY_nq ; } else { _rtB -> B_136_625_5000 = _rtB -> B_136_624_4992 ; } }
else { rtb_B_136_1808_13832 = rtb_B_136_1884_14440 * _rtP -> P_541 ;
rtb_B_136_1807_13824 = _rtB -> B_136_624_4992 - _rtDW -> PrevY_nq ; if (
rtb_B_136_1807_13824 > rtb_B_136_1808_13832 ) { _rtB -> B_136_625_5000 =
_rtDW -> PrevY_nq + rtb_B_136_1808_13832 ; didZcEventOccur = true ; } else {
rtb_B_136_1884_14440 *= _rtP -> P_542 ; if ( rtb_B_136_1807_13824 <
rtb_B_136_1884_14440 ) { _rtB -> B_136_625_5000 = _rtDW -> PrevY_nq +
rtb_B_136_1884_14440 ; didZcEventOccur = true ; } else { _rtB ->
B_136_625_5000 = _rtB -> B_136_624_4992 ; didZcEventOccur = false ; } } if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> PrevLimited_k = didZcEventOccur ; }
} } _rtB -> B_136_626_5008 = _rtX -> Integrator_x1_CSTATE_k ; _rtB ->
B_136_627_5016 = _rtP -> P_544 * _rtB -> B_136_626_5008 ; _rtB ->
B_136_628_5024 = _rtX -> Integrator_x2_CSTATE_f ; _rtB -> B_136_629_5032 =
_rtP -> P_546 * _rtB -> B_136_628_5024 ; _rtB -> B_136_630_5040 = _rtP ->
P_547 * _rtB -> B_136_626_5008 ; _rtB -> B_136_631_5048 = _rtP -> P_548 *
_rtB -> B_136_628_5024 ; _rtB -> B_136_632_5056 = _rtB -> B_136_627_5016 +
_rtB -> B_136_629_5032 ; _rtB -> B_136_633_5064 = _rtB -> B_136_630_5040 +
_rtB -> B_136_631_5048 ; _rtB -> B_136_634_5072 = _rtP -> P_549 * _rtB ->
B_136_625_5000 ; _rtB -> B_136_635_5080 = _rtB -> B_136_632_5056 + _rtB ->
B_136_634_5072 ; _rtB -> B_136_636_5088 = _rtP -> P_550 * _rtB ->
B_136_625_5000 ; _rtB -> B_136_637_5096 = _rtB -> B_136_633_5064 + _rtB ->
B_136_636_5088 ; _rtB -> B_136_638_5104 = ( _rtP -> P_551 * _rtB ->
B_136_626_5008 + _rtP -> P_552 * _rtB -> B_136_628_5024 ) + _rtP -> P_553 *
_rtB -> B_136_625_5000 ; if ( _rtB -> B_136_604_4832 > _rtP -> P_554 ) { _rtB
-> B_136_639_5112 = _rtP -> P_554 ; } else if ( _rtB -> B_136_604_4832 < _rtP
-> P_555 ) { _rtB -> B_136_639_5112 = _rtP -> P_555 ; } else { _rtB ->
B_136_639_5112 = _rtB -> B_136_604_4832 ; } _rtB -> B_136_640_5120 = 1.0 /
_rtB -> B_136_639_5112 ; rtb_B_136_1807_13824 = _rtB -> B_136_608_4864 [ 1 ]
; rtb_B_136_1884_14440 = _rtB -> B_136_608_4864 [ 0 ] ; rtb_B_136_1808_13832
= _rtB -> B_136_608_4864 [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) {
rtb_B_136_1854_14200 = ( _rtP -> P_556 [ i + 3 ] * rtb_B_136_1807_13824 +
_rtP -> P_556 [ i ] * rtb_B_136_1884_14440 ) + _rtP -> P_556 [ i + 6 ] *
rtb_B_136_1808_13832 ; _rtB -> B_136_641_5128 [ i ] = rtb_B_136_1854_14200 ;
_rtB -> B_136_644_5152 [ i ] = _rtP -> P_557 * rtb_B_136_1854_14200 ; }
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1269_9893 , &
_rtB -> B_136_644_5152 [ 0 ] , _rtB -> B_136_607_4856 , & _rtB ->
Subsystempi2delay_n , & _rtDW -> Subsystempi2delay_n ) ;
dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1268_9892 , & _rtB ->
B_136_644_5152 [ 0 ] , _rtB -> B_136_607_4856 , & _rtB -> Subsystem1_dt , &
_rtDW -> Subsystem1_dt ) ; if ( _rtB -> B_136_1268_9892 != 0 ) { _rtB ->
B_136_647_5176 [ 0 ] = _rtB -> Subsystem1_dt . B_25_1750_13368 ; _rtB ->
B_136_647_5176 [ 1 ] = _rtB -> Subsystem1_dt . B_25_1751_13376 ; } else {
_rtB -> B_136_647_5176 [ 0 ] = _rtB -> Subsystempi2delay_n . B_24_1752_13384
; _rtB -> B_136_647_5176 [ 1 ] = _rtB -> Subsystempi2delay_n .
B_24_1753_13392 ; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB ->
B_136_649_5192 = _rtDW -> Memory_PreviousInput_n ; if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> RelationalOperator_Mode_a = ( _rtX
-> Integrator_CSTATE_pq > _rtB -> B_136_1020_8160 ) ; } _rtB ->
B_136_1290_9914 = _rtDW -> RelationalOperator_Mode_a ; } _rtB ->
B_136_650_5200 = _rtX -> Integrator_CSTATE_pq - _rtB -> B_136_1020_8160 ; if
( ( _rtDW -> Initial_FirstOutputTime_l == ( rtMinusInf ) ) || ( _rtDW ->
Initial_FirstOutputTime_l == ssGetTaskTime ( S , 0 ) ) ) { _rtDW ->
Initial_FirstOutputTime_l = ssGetTaskTime ( S , 0 ) ; _rtB -> B_136_651_5208
= _rtP -> P_559 ; } else { _rtB -> B_136_651_5208 = _rtB -> B_136_650_5200 ;
} if ( ssIsModeUpdateTimeStep ( S ) ) { didZcEventOccur = ( _rtB ->
B_136_1290_9914 && ( _rtZCE -> Integrator_Reset_ZCE_op != POS_ZCSIG ) ) ;
_rtZCE -> Integrator_Reset_ZCE_op = _rtB -> B_136_1290_9914 ; if (
didZcEventOccur || ( _rtDW -> Integrator_IWORK_c != 0 ) ) { didZcEventOccur =
( _rtX -> Integrator_CSTATE_pq != _rtB -> B_136_651_5208 ) ; _rtX ->
Integrator_CSTATE_pq = _rtB -> B_136_651_5208 ; if ( didZcEventOccur ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } } if ( _rtX ->
Integrator_CSTATE_pq >= _rtP -> P_560 ) { if ( _rtX -> Integrator_CSTATE_pq
!= _rtP -> P_560 ) { _rtX -> Integrator_CSTATE_pq = _rtP -> P_560 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_g = 3 ; } else if ( _rtX -> Integrator_CSTATE_pq <= _rtP ->
P_561 ) { if ( _rtX -> Integrator_CSTATE_pq != _rtP -> P_561 ) { _rtX ->
Integrator_CSTATE_pq = _rtP -> P_561 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_g = 4 ; } else { if ( _rtDW -> Integrator_MODE_g != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_g = 0 ; } _rtB -> B_136_652_5216 = _rtX ->
Integrator_CSTATE_pq ; } else { _rtB -> B_136_652_5216 = _rtX ->
Integrator_CSTATE_pq ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
_rtB -> B_136_653_5224 [ 0 ] = _rtP -> P_562 * _rtB -> B_136_118_944 [ 37 ] *
_rtP -> P_565 * _rtP -> P_566 ; _rtB -> B_136_653_5224 [ 1 ] = _rtP -> P_563
* _rtB -> B_136_118_944 [ 38 ] * _rtP -> P_565 * _rtP -> P_566 ; _rtB ->
B_136_653_5224 [ 2 ] = _rtP -> P_564 * _rtB -> B_136_118_944 [ 39 ] * _rtP ->
P_565 * _rtP -> P_566 ; rtb_B_136_1807_13824 = _rtB -> B_136_653_5224 [ 1 ] ;
rtb_B_136_1884_14440 = _rtB -> B_136_653_5224 [ 0 ] ; rtb_B_136_1808_13832 =
_rtB -> B_136_653_5224 [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) {
rtb_B_128_2256_17416 [ i ] = ( ( _rtP -> P_567 [ i + 3 ] *
rtb_B_136_1807_13824 + _rtP -> P_567 [ i ] * rtb_B_136_1884_14440 ) + _rtP ->
P_567 [ i + 6 ] * rtb_B_136_1808_13832 ) * _rtP -> P_568 ; } _rtB ->
B_136_656_5248 = muDoubleScalarHypot ( rtb_B_128_2256_17416 [ 0 ] ,
rtb_B_128_2256_17416 [ 1 ] ) ; } ssCallAccelRunBlock ( S , 136 , 880 ,
SS_CALL_MDL_OUTPUTS ) ; dVOC_monitor_network1_AutomaticGainControl ( S , _rtB
-> B_136_1019_8152 , _rtB -> B_136_649_5192 , _rtB -> B_136_652_5216 , _rtB
-> B_136_653_5224 , & _rtB -> AutomaticGainControl_a , & _rtDW ->
AutomaticGainControl_a , & _rtP -> AutomaticGainControl_a , & _rtX ->
AutomaticGainControl_a , & _rtXdis -> AutomaticGainControl_a ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX -> Integrator_CSTATE_jf >= _rtP ->
P_571 ) { if ( _rtX -> Integrator_CSTATE_jf != _rtP -> P_571 ) { _rtX ->
Integrator_CSTATE_jf = _rtP -> P_571 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_p = 3 ; } else if ( _rtX -> Integrator_CSTATE_jf <= _rtP ->
P_572 ) { if ( _rtX -> Integrator_CSTATE_jf != _rtP -> P_572 ) { _rtX ->
Integrator_CSTATE_jf = _rtP -> P_572 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_p = 4 ; } else { if ( _rtDW -> Integrator_MODE_p != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_p = 0 ; } _rtB -> B_136_657_5256 = _rtX ->
Integrator_CSTATE_jf ; } else { _rtB -> B_136_657_5256 = _rtX ->
Integrator_CSTATE_jf ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_o . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; real_T appliedDelay ; _rtB -> B_136_658_5264 =
dVOC_monitor_network1_acc_rt_VTDelayfindtDInterpolate ( ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_l , * uBuffer , _rtDW ->
VariableTransportDelay_IWORK_kh . CircularBufSize , _rtDW ->
VariableTransportDelay_IWORK_kh . Head , _rtDW ->
VariableTransportDelay_IWORK_kh . Tail , & _rtDW ->
VariableTransportDelay_IWORK_kh . Last , simTime , 0.0 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
VariableTransportDelay_IWORK_kh . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK_kh . Head ] == ssGetT ( S ) ) ) , _rtP -> P_574
, & appliedDelay ) ; } _rtB -> B_136_659_5272 = _rtX -> integrator_CSTATE_a ;
_rtB -> B_136_660_5280 = ssGetT ( S ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if
( i != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
RelationalOperator_Mode_ak = ( _rtB -> B_136_660_5280 >= _rtB ->
B_136_1021_8168 ) ; } _rtB -> B_136_1291_9915 = _rtDW ->
RelationalOperator_Mode_ak ; } if ( _rtB -> B_136_1291_9915 ) { _rtB ->
B_65_1219_9752 = _rtB -> B_136_659_5272 - _rtB -> B_136_658_5264 ; _rtB ->
B_65_1220_9760 = _rtB -> B_65_1219_9752 * _rtB -> B_136_649_5192 ; _rtB ->
B_136_661_5288 = _rtB -> B_65_1220_9760 ; } else { _rtB -> B_136_661_5288 =
_rtB -> B_136_1022_8176 ; } _rtB -> B_136_662_5296 = _rtB -> B_136_661_5288 *
_rtB -> AutomaticGainControl_a . B_56_1669_12744 ; _rtB -> B_136_663_5304 =
_rtP -> P_576 * _rtB -> B_136_662_5296 ; _rtB -> B_136_664_5312 = _rtP ->
P_577 * _rtB -> B_136_662_5296 ; _rtB -> B_136_665_5320 = _rtP -> P_578 *
_rtB -> B_136_662_5296 ; _rtB -> B_136_666_5328 = 0.0 ; _rtB ->
B_136_666_5328 += _rtP -> P_580 * _rtX -> TransferFcn_CSTATE_k ; _rtB ->
B_136_666_5328 += _rtP -> P_581 * _rtB -> B_136_665_5320 ; _rtB ->
B_136_667_5336 = ( _rtB -> B_136_663_5304 + _rtB -> B_136_657_5256 ) + _rtB
-> B_136_666_5328 ; if ( ssIsModeUpdateTimeStep ( S ) ) { if ( _rtB ->
B_136_667_5336 >= _rtP -> P_582 ) { _rtDW -> Saturation2_MODE_g = 1 ; } else
if ( _rtB -> B_136_667_5336 > _rtP -> P_583 ) { _rtDW -> Saturation2_MODE_g =
0 ; } else { _rtDW -> Saturation2_MODE_g = - 1 ; } } if ( _rtDW ->
Saturation2_MODE_g == 1 ) { _rtB -> B_136_668_5344 = _rtP -> P_582 ; } else
if ( _rtDW -> Saturation2_MODE_g == - 1 ) { _rtB -> B_136_668_5344 = _rtP ->
P_583 ; } else { _rtB -> B_136_668_5344 = _rtB -> B_136_667_5336 ; } _rtB ->
B_136_669_5352 = _rtP -> P_584 * _rtB -> B_136_668_5344 ; if ( _rtDW ->
LastMajorTime_du == ( rtInf ) ) { _rtB -> B_136_670_5360 = _rtB ->
B_136_669_5352 ; } else { rtb_B_136_1884_14440 = ssGetTaskTime ( S , 0 ) -
_rtDW -> LastMajorTime_du ; if ( _rtDW -> LastMajorTime_du == ssGetTaskTime (
S , 0 ) ) { if ( _rtDW -> PrevLimited_n ) { _rtB -> B_136_670_5360 = _rtDW ->
PrevY_o ; } else { _rtB -> B_136_670_5360 = _rtB -> B_136_669_5352 ; } } else
{ rtb_B_136_1808_13832 = rtb_B_136_1884_14440 * _rtP -> P_585 ;
rtb_B_136_1807_13824 = _rtB -> B_136_669_5352 - _rtDW -> PrevY_o ; if (
rtb_B_136_1807_13824 > rtb_B_136_1808_13832 ) { _rtB -> B_136_670_5360 =
_rtDW -> PrevY_o + rtb_B_136_1808_13832 ; didZcEventOccur = true ; } else {
rtb_B_136_1884_14440 *= _rtP -> P_586 ; if ( rtb_B_136_1807_13824 <
rtb_B_136_1884_14440 ) { _rtB -> B_136_670_5360 = _rtDW -> PrevY_o +
rtb_B_136_1884_14440 ; didZcEventOccur = true ; } else { _rtB ->
B_136_670_5360 = _rtB -> B_136_669_5352 ; didZcEventOccur = false ; } } if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> PrevLimited_n = didZcEventOccur ; }
} } _rtB -> B_136_671_5368 = _rtX -> Integrator_x1_CSTATE_ma ; _rtB ->
B_136_672_5376 = _rtP -> P_588 * _rtB -> B_136_671_5368 ; _rtB ->
B_136_673_5384 = _rtX -> Integrator_x2_CSTATE_p ; _rtB -> B_136_674_5392 =
_rtP -> P_590 * _rtB -> B_136_673_5384 ; _rtB -> B_136_675_5400 = _rtP ->
P_591 * _rtB -> B_136_671_5368 ; _rtB -> B_136_676_5408 = _rtP -> P_592 *
_rtB -> B_136_673_5384 ; _rtB -> B_136_677_5416 = _rtB -> B_136_672_5376 +
_rtB -> B_136_674_5392 ; _rtB -> B_136_678_5424 = _rtB -> B_136_675_5400 +
_rtB -> B_136_676_5408 ; _rtB -> B_136_679_5432 = _rtP -> P_593 * _rtB ->
B_136_670_5360 ; _rtB -> B_136_680_5440 = _rtB -> B_136_677_5416 + _rtB ->
B_136_679_5432 ; _rtB -> B_136_681_5448 = _rtP -> P_594 * _rtB ->
B_136_670_5360 ; _rtB -> B_136_682_5456 = _rtB -> B_136_678_5424 + _rtB ->
B_136_681_5448 ; _rtB -> B_136_683_5464 = ( _rtP -> P_595 * _rtB ->
B_136_671_5368 + _rtP -> P_596 * _rtB -> B_136_673_5384 ) + _rtP -> P_597 *
_rtB -> B_136_670_5360 ; if ( _rtB -> B_136_649_5192 > _rtP -> P_598 ) { _rtB
-> B_136_684_5472 = _rtP -> P_598 ; } else if ( _rtB -> B_136_649_5192 < _rtP
-> P_599 ) { _rtB -> B_136_684_5472 = _rtP -> P_599 ; } else { _rtB ->
B_136_684_5472 = _rtB -> B_136_649_5192 ; } _rtB -> B_136_685_5480 = 1.0 /
_rtB -> B_136_684_5472 ; rtb_B_136_1807_13824 = _rtB -> B_136_653_5224 [ 1 ]
; rtb_B_136_1884_14440 = _rtB -> B_136_653_5224 [ 0 ] ; rtb_B_136_1808_13832
= _rtB -> B_136_653_5224 [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) {
rtb_B_136_1854_14200 = ( _rtP -> P_600 [ i + 3 ] * rtb_B_136_1807_13824 +
_rtP -> P_600 [ i ] * rtb_B_136_1884_14440 ) + _rtP -> P_600 [ i + 6 ] *
rtb_B_136_1808_13832 ; _rtB -> B_136_686_5488 [ i ] = rtb_B_136_1854_14200 ;
_rtB -> B_136_689_5512 [ i ] = _rtP -> P_601 * rtb_B_136_1854_14200 ; }
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1271_9895 , &
_rtB -> B_136_689_5512 [ 0 ] , _rtB -> B_136_652_5216 , & _rtB ->
Subsystempi2delay_ho , & _rtDW -> Subsystempi2delay_ho ) ;
dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1270_9894 , & _rtB ->
B_136_689_5512 [ 0 ] , _rtB -> B_136_652_5216 , & _rtB -> Subsystem1_n , &
_rtDW -> Subsystem1_n ) ; if ( _rtB -> B_136_1270_9894 != 0 ) { _rtB ->
B_136_692_5536 [ 0 ] = _rtB -> Subsystem1_n . B_25_1750_13368 ; _rtB ->
B_136_692_5536 [ 1 ] = _rtB -> Subsystem1_n . B_25_1751_13376 ; } else { _rtB
-> B_136_692_5536 [ 0 ] = _rtB -> Subsystempi2delay_ho . B_24_1752_13384 ;
_rtB -> B_136_692_5536 [ 1 ] = _rtB -> Subsystempi2delay_ho . B_24_1753_13392
; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_136_694_5552
= _rtDW -> Memory_PreviousInput_c4 ; if ( ssIsModeUpdateTimeStep ( S ) ) {
_rtDW -> RelationalOperator_Mode_o = ( _rtX -> Integrator_CSTATE_oo > _rtB ->
B_136_1024_8192 ) ; } _rtB -> B_136_1292_9916 = _rtDW ->
RelationalOperator_Mode_o ; } _rtB -> B_136_695_5560 = _rtX ->
Integrator_CSTATE_oo - _rtB -> B_136_1024_8192 ; if ( ( _rtDW ->
Initial_FirstOutputTime_lf == ( rtMinusInf ) ) || ( _rtDW ->
Initial_FirstOutputTime_lf == ssGetTaskTime ( S , 0 ) ) ) { _rtDW ->
Initial_FirstOutputTime_lf = ssGetTaskTime ( S , 0 ) ; _rtB -> B_136_696_5568
= _rtP -> P_603 ; } else { _rtB -> B_136_696_5568 = _rtB -> B_136_695_5560 ;
} if ( ssIsModeUpdateTimeStep ( S ) ) { didZcEventOccur = ( _rtB ->
B_136_1292_9916 && ( _rtZCE -> Integrator_Reset_ZCE_m != POS_ZCSIG ) ) ;
_rtZCE -> Integrator_Reset_ZCE_m = _rtB -> B_136_1292_9916 ; if (
didZcEventOccur || ( _rtDW -> Integrator_IWORK_bu != 0 ) ) { didZcEventOccur
= ( _rtX -> Integrator_CSTATE_oo != _rtB -> B_136_696_5568 ) ; _rtX ->
Integrator_CSTATE_oo = _rtB -> B_136_696_5568 ; if ( didZcEventOccur ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } } if ( _rtX ->
Integrator_CSTATE_oo >= _rtP -> P_604 ) { if ( _rtX -> Integrator_CSTATE_oo
!= _rtP -> P_604 ) { _rtX -> Integrator_CSTATE_oo = _rtP -> P_604 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_m = 3 ; } else if ( _rtX -> Integrator_CSTATE_oo <= _rtP ->
P_605 ) { if ( _rtX -> Integrator_CSTATE_oo != _rtP -> P_605 ) { _rtX ->
Integrator_CSTATE_oo = _rtP -> P_605 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_m = 4 ; } else { if ( _rtDW -> Integrator_MODE_m != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_m = 0 ; } _rtB -> B_136_697_5576 = _rtX ->
Integrator_CSTATE_oo ; } else { _rtB -> B_136_697_5576 = _rtX ->
Integrator_CSTATE_oo ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
_rtB -> B_136_698_5584 [ 0 ] = _rtP -> P_606 * _rtB -> B_136_118_944 [ 31 ] *
_rtP -> P_609 ; _rtB -> B_136_698_5584 [ 1 ] = _rtP -> P_607 * _rtB ->
B_136_118_944 [ 32 ] * _rtP -> P_609 ; _rtB -> B_136_698_5584 [ 2 ] = _rtP ->
P_608 * _rtB -> B_136_118_944 [ 33 ] * _rtP -> P_609 ; rtb_B_136_1807_13824 =
_rtB -> B_136_698_5584 [ 1 ] ; rtb_B_136_1884_14440 = _rtB -> B_136_698_5584
[ 0 ] ; rtb_B_136_1808_13832 = _rtB -> B_136_698_5584 [ 2 ] ; for ( i = 0 ; i
< 3 ; i ++ ) { rtb_B_128_2256_17416 [ i ] = ( ( _rtP -> P_610 [ i + 3 ] *
rtb_B_136_1807_13824 + _rtP -> P_610 [ i ] * rtb_B_136_1884_14440 ) + _rtP ->
P_610 [ i + 6 ] * rtb_B_136_1808_13832 ) * _rtP -> P_611 ; } _rtB ->
B_136_701_5608 = muDoubleScalarHypot ( rtb_B_128_2256_17416 [ 0 ] ,
rtb_B_128_2256_17416 [ 1 ] ) ; } ssCallAccelRunBlock ( S , 136 , 935 ,
SS_CALL_MDL_OUTPUTS ) ; dVOC_monitor_network1_AutomaticGainControl ( S , _rtB
-> B_136_1023_8184 , _rtB -> B_136_694_5552 , _rtB -> B_136_697_5576 , _rtB
-> B_136_698_5584 , & _rtB -> AutomaticGainControl , & _rtDW ->
AutomaticGainControl , & _rtP -> AutomaticGainControl , & _rtX ->
AutomaticGainControl , & _rtXdis -> AutomaticGainControl ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX -> Integrator_CSTATE_pf >= _rtP ->
P_614 ) { if ( _rtX -> Integrator_CSTATE_pf != _rtP -> P_614 ) { _rtX ->
Integrator_CSTATE_pf = _rtP -> P_614 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_es = 3 ; } else if ( _rtX -> Integrator_CSTATE_pf <= _rtP ->
P_615 ) { if ( _rtX -> Integrator_CSTATE_pf != _rtP -> P_615 ) { _rtX ->
Integrator_CSTATE_pf = _rtP -> P_615 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_es = 4 ; } else { if ( _rtDW -> Integrator_MODE_es != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_es = 0 ; } _rtB -> B_136_702_5616 = _rtX ->
Integrator_CSTATE_pf ; } else { _rtB -> B_136_702_5616 = _rtX ->
Integrator_CSTATE_pf ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_e . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; real_T appliedDelay ; _rtB -> B_136_703_5624 =
dVOC_monitor_network1_acc_rt_VTDelayfindtDInterpolate ( ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_d , * uBuffer , _rtDW ->
VariableTransportDelay_IWORK_a . CircularBufSize , _rtDW ->
VariableTransportDelay_IWORK_a . Head , _rtDW ->
VariableTransportDelay_IWORK_a . Tail , & _rtDW ->
VariableTransportDelay_IWORK_a . Last , simTime , 0.0 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
VariableTransportDelay_IWORK_a . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK_a . Head ] == ssGetT ( S ) ) ) , _rtP -> P_617 ,
& appliedDelay ) ; } _rtB -> B_136_704_5632 = _rtX -> integrator_CSTATE_p ;
_rtB -> B_136_705_5640 = ssGetT ( S ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if
( i != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
RelationalOperator_Mode_e = ( _rtB -> B_136_705_5640 >= _rtB ->
B_136_1025_8200 ) ; } _rtB -> B_136_1293_9917 = _rtDW ->
RelationalOperator_Mode_e ; } if ( _rtB -> B_136_1293_9917 ) { _rtB ->
B_57_1221_9768 = _rtB -> B_136_704_5632 - _rtB -> B_136_703_5624 ; _rtB ->
B_57_1222_9776 = _rtB -> B_57_1221_9768 * _rtB -> B_136_694_5552 ; _rtB ->
B_136_706_5648 = _rtB -> B_57_1222_9776 ; } else { _rtB -> B_136_706_5648 =
_rtB -> B_136_1026_8208 ; } _rtB -> B_136_707_5656 = _rtB -> B_136_706_5648 *
_rtB -> AutomaticGainControl . B_56_1669_12744 ; _rtB -> B_136_708_5664 =
_rtP -> P_619 * _rtB -> B_136_707_5656 ; _rtB -> B_136_709_5672 = _rtP ->
P_620 * _rtB -> B_136_707_5656 ; _rtB -> B_136_710_5680 = _rtP -> P_621 *
_rtB -> B_136_707_5656 ; _rtB -> B_136_711_5688 = 0.0 ; _rtB ->
B_136_711_5688 += _rtP -> P_623 * _rtX -> TransferFcn_CSTATE_m ; _rtB ->
B_136_711_5688 += _rtP -> P_624 * _rtB -> B_136_710_5680 ; _rtB ->
B_136_712_5696 = ( _rtB -> B_136_708_5664 + _rtB -> B_136_702_5616 ) + _rtB
-> B_136_711_5688 ; if ( ssIsModeUpdateTimeStep ( S ) ) { if ( _rtB ->
B_136_712_5696 >= _rtP -> P_625 ) { _rtDW -> Saturation2_MODE_cy = 1 ; } else
if ( _rtB -> B_136_712_5696 > _rtP -> P_626 ) { _rtDW -> Saturation2_MODE_cy
= 0 ; } else { _rtDW -> Saturation2_MODE_cy = - 1 ; } } if ( _rtDW ->
Saturation2_MODE_cy == 1 ) { _rtB -> B_136_713_5704 = _rtP -> P_625 ; } else
if ( _rtDW -> Saturation2_MODE_cy == - 1 ) { _rtB -> B_136_713_5704 = _rtP ->
P_626 ; } else { _rtB -> B_136_713_5704 = _rtB -> B_136_712_5696 ; } _rtB ->
B_136_714_5712 = _rtP -> P_627 * _rtB -> B_136_713_5704 ; if ( _rtDW ->
LastMajorTime_o == ( rtInf ) ) { _rtB -> B_136_715_5720 = _rtB ->
B_136_714_5712 ; } else { rtb_B_136_1884_14440 = ssGetTaskTime ( S , 0 ) -
_rtDW -> LastMajorTime_o ; if ( _rtDW -> LastMajorTime_o == ssGetTaskTime ( S
, 0 ) ) { if ( _rtDW -> PrevLimited_b ) { _rtB -> B_136_715_5720 = _rtDW ->
PrevY_nc ; } else { _rtB -> B_136_715_5720 = _rtB -> B_136_714_5712 ; } }
else { rtb_B_136_1808_13832 = rtb_B_136_1884_14440 * _rtP -> P_628 ;
rtb_B_136_1807_13824 = _rtB -> B_136_714_5712 - _rtDW -> PrevY_nc ; if (
rtb_B_136_1807_13824 > rtb_B_136_1808_13832 ) { _rtB -> B_136_715_5720 =
_rtDW -> PrevY_nc + rtb_B_136_1808_13832 ; didZcEventOccur = true ; } else {
rtb_B_136_1884_14440 *= _rtP -> P_629 ; if ( rtb_B_136_1807_13824 <
rtb_B_136_1884_14440 ) { _rtB -> B_136_715_5720 = _rtDW -> PrevY_nc +
rtb_B_136_1884_14440 ; didZcEventOccur = true ; } else { _rtB ->
B_136_715_5720 = _rtB -> B_136_714_5712 ; didZcEventOccur = false ; } } if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> PrevLimited_b = didZcEventOccur ; }
} } _rtB -> B_136_716_5728 = _rtX -> Integrator_x1_CSTATE_a ; _rtB ->
B_136_717_5736 = _rtP -> P_631 * _rtB -> B_136_716_5728 ; _rtB ->
B_136_718_5744 = _rtX -> Integrator_x2_CSTATE_a ; _rtB -> B_136_719_5752 =
_rtP -> P_633 * _rtB -> B_136_718_5744 ; _rtB -> B_136_720_5760 = _rtP ->
P_634 * _rtB -> B_136_716_5728 ; _rtB -> B_136_721_5768 = _rtP -> P_635 *
_rtB -> B_136_718_5744 ; _rtB -> B_136_722_5776 = _rtB -> B_136_717_5736 +
_rtB -> B_136_719_5752 ; _rtB -> B_136_723_5784 = _rtB -> B_136_720_5760 +
_rtB -> B_136_721_5768 ; _rtB -> B_136_724_5792 = _rtP -> P_636 * _rtB ->
B_136_715_5720 ; _rtB -> B_136_725_5800 = _rtB -> B_136_722_5776 + _rtB ->
B_136_724_5792 ; _rtB -> B_136_726_5808 = _rtP -> P_637 * _rtB ->
B_136_715_5720 ; _rtB -> B_136_727_5816 = _rtB -> B_136_723_5784 + _rtB ->
B_136_726_5808 ; _rtB -> B_136_728_5824 = ( _rtP -> P_638 * _rtB ->
B_136_716_5728 + _rtP -> P_639 * _rtB -> B_136_718_5744 ) + _rtP -> P_640 *
_rtB -> B_136_715_5720 ; if ( _rtB -> B_136_694_5552 > _rtP -> P_641 ) { _rtB
-> B_136_729_5832 = _rtP -> P_641 ; } else if ( _rtB -> B_136_694_5552 < _rtP
-> P_642 ) { _rtB -> B_136_729_5832 = _rtP -> P_642 ; } else { _rtB ->
B_136_729_5832 = _rtB -> B_136_694_5552 ; } _rtB -> B_136_730_5840 = 1.0 /
_rtB -> B_136_729_5832 ; rtb_B_136_1807_13824 = _rtB -> B_136_698_5584 [ 1 ]
; rtb_B_136_1884_14440 = _rtB -> B_136_698_5584 [ 0 ] ; rtb_B_136_1808_13832
= _rtB -> B_136_698_5584 [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) {
rtb_B_136_1854_14200 = ( _rtP -> P_643 [ i + 3 ] * rtb_B_136_1807_13824 +
_rtP -> P_643 [ i ] * rtb_B_136_1884_14440 ) + _rtP -> P_643 [ i + 6 ] *
rtb_B_136_1808_13832 ; _rtB -> B_136_731_5848 [ i ] = rtb_B_136_1854_14200 ;
_rtB -> B_136_734_5872 [ i ] = _rtP -> P_644 * rtb_B_136_1854_14200 ; }
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1273_9897 , &
_rtB -> B_136_734_5872 [ 0 ] , _rtB -> B_136_697_5576 , & _rtB ->
Subsystempi2delay_a , & _rtDW -> Subsystempi2delay_a ) ;
dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1272_9896 , & _rtB ->
B_136_734_5872 [ 0 ] , _rtB -> B_136_697_5576 , & _rtB -> Subsystem1_f , &
_rtDW -> Subsystem1_f ) ; if ( _rtB -> B_136_1272_9896 != 0 ) { _rtB ->
B_136_737_5896 [ 0 ] = _rtB -> Subsystem1_f . B_25_1750_13368 ; _rtB ->
B_136_737_5896 [ 1 ] = _rtB -> Subsystem1_f . B_25_1751_13376 ; } else { _rtB
-> B_136_737_5896 [ 0 ] = _rtB -> Subsystempi2delay_a . B_24_1752_13384 ;
_rtB -> B_136_737_5896 [ 1 ] = _rtB -> Subsystempi2delay_a . B_24_1753_13392
; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_136_739_5912
= _rtDW -> Memory_PreviousInput_gc ; if ( ssIsModeUpdateTimeStep ( S ) ) {
_rtDW -> RelationalOperator_Mode_j1 = ( _rtX -> Integrator_CSTATE_d > _rtB ->
B_136_1028_8224 ) ; } _rtB -> B_136_1294_9918 = _rtDW ->
RelationalOperator_Mode_j1 ; } _rtB -> B_136_740_5920 = _rtX ->
Integrator_CSTATE_d - _rtB -> B_136_1028_8224 ; if ( ( _rtDW ->
Initial_FirstOutputTime_f == ( rtMinusInf ) ) || ( _rtDW ->
Initial_FirstOutputTime_f == ssGetTaskTime ( S , 0 ) ) ) { _rtDW ->
Initial_FirstOutputTime_f = ssGetTaskTime ( S , 0 ) ; _rtB -> B_136_741_5928
= _rtP -> P_646 ; } else { _rtB -> B_136_741_5928 = _rtB -> B_136_740_5920 ;
} if ( ssIsModeUpdateTimeStep ( S ) ) { didZcEventOccur = ( _rtB ->
B_136_1294_9918 && ( _rtZCE -> Integrator_Reset_ZCE_os != POS_ZCSIG ) ) ;
_rtZCE -> Integrator_Reset_ZCE_os = _rtB -> B_136_1294_9918 ; if (
didZcEventOccur || ( _rtDW -> Integrator_IWORK_d != 0 ) ) { didZcEventOccur =
( _rtX -> Integrator_CSTATE_d != _rtB -> B_136_741_5928 ) ; _rtX ->
Integrator_CSTATE_d = _rtB -> B_136_741_5928 ; if ( didZcEventOccur ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } } if ( _rtX ->
Integrator_CSTATE_d >= _rtP -> P_647 ) { if ( _rtX -> Integrator_CSTATE_d !=
_rtP -> P_647 ) { _rtX -> Integrator_CSTATE_d = _rtP -> P_647 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_dx = 3 ; } else if ( _rtX -> Integrator_CSTATE_d <= _rtP ->
P_648 ) { if ( _rtX -> Integrator_CSTATE_d != _rtP -> P_648 ) { _rtX ->
Integrator_CSTATE_d = _rtP -> P_648 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_dx = 4 ; } else { if ( _rtDW -> Integrator_MODE_dx != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_dx = 0 ; } _rtB -> B_136_742_5936 = _rtX ->
Integrator_CSTATE_d ; } else { _rtB -> B_136_742_5936 = _rtX ->
Integrator_CSTATE_d ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
_rtB -> B_136_743_5944 [ 0 ] = _rtP -> P_649 * _rtB -> B_136_118_944 [ 40 ] *
_rtP -> P_652 ; _rtB -> B_136_743_5944 [ 1 ] = _rtP -> P_650 * _rtB ->
B_136_118_944 [ 41 ] * _rtP -> P_652 ; _rtB -> B_136_743_5944 [ 2 ] = _rtP ->
P_651 * _rtB -> B_136_118_944 [ 42 ] * _rtP -> P_652 ; rtb_B_136_1807_13824 =
_rtB -> B_136_743_5944 [ 1 ] ; rtb_B_136_1884_14440 = _rtB -> B_136_743_5944
[ 0 ] ; rtb_B_136_1808_13832 = _rtB -> B_136_743_5944 [ 2 ] ; for ( i = 0 ; i
< 3 ; i ++ ) { rtb_B_128_2256_17416 [ i ] = ( ( _rtP -> P_653 [ i + 3 ] *
rtb_B_136_1807_13824 + _rtP -> P_653 [ i ] * rtb_B_136_1884_14440 ) + _rtP ->
P_653 [ i + 6 ] * rtb_B_136_1808_13832 ) * _rtP -> P_654 ; } _rtB ->
B_136_746_5968 = muDoubleScalarHypot ( rtb_B_128_2256_17416 [ 0 ] ,
rtb_B_128_2256_17416 [ 1 ] ) ; } ssCallAccelRunBlock ( S , 136 , 990 ,
SS_CALL_MDL_OUTPUTS ) ; dVOC_monitor_network1_AutomaticGainControl ( S , _rtB
-> B_136_1027_8216 , _rtB -> B_136_739_5912 , _rtB -> B_136_742_5936 , _rtB
-> B_136_743_5944 , & _rtB -> AutomaticGainControl_m , & _rtDW ->
AutomaticGainControl_m , & _rtP -> AutomaticGainControl_m , & _rtX ->
AutomaticGainControl_m , & _rtXdis -> AutomaticGainControl_m ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX -> Integrator_CSTATE_jn >= _rtP ->
P_657 ) { if ( _rtX -> Integrator_CSTATE_jn != _rtP -> P_657 ) { _rtX ->
Integrator_CSTATE_jn = _rtP -> P_657 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_il = 3 ; } else if ( _rtX -> Integrator_CSTATE_jn <= _rtP ->
P_658 ) { if ( _rtX -> Integrator_CSTATE_jn != _rtP -> P_658 ) { _rtX ->
Integrator_CSTATE_jn = _rtP -> P_658 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_il = 4 ; } else { if ( _rtDW -> Integrator_MODE_il != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_il = 0 ; } _rtB -> B_136_747_5976 = _rtX ->
Integrator_CSTATE_jn ; } else { _rtB -> B_136_747_5976 = _rtX ->
Integrator_CSTATE_jn ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_lv . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; real_T appliedDelay ; _rtB -> B_136_748_5984 =
dVOC_monitor_network1_acc_rt_VTDelayfindtDInterpolate ( ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_jz , * uBuffer , _rtDW ->
VariableTransportDelay_IWORK_l . CircularBufSize , _rtDW ->
VariableTransportDelay_IWORK_l . Head , _rtDW ->
VariableTransportDelay_IWORK_l . Tail , & _rtDW ->
VariableTransportDelay_IWORK_l . Last , simTime , 0.0 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
VariableTransportDelay_IWORK_l . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK_l . Head ] == ssGetT ( S ) ) ) , _rtP -> P_660 ,
& appliedDelay ) ; } _rtB -> B_136_749_5992 = _rtX -> integrator_CSTATE_j ;
_rtB -> B_136_750_6000 = ssGetT ( S ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if
( i != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
RelationalOperator_Mode_d4 = ( _rtB -> B_136_750_6000 >= _rtB ->
B_136_1029_8232 ) ; } _rtB -> B_136_1295_9919 = _rtDW ->
RelationalOperator_Mode_d4 ; } if ( _rtB -> B_136_1295_9919 ) { _rtB ->
B_89_1213_9704 = _rtB -> B_136_749_5992 - _rtB -> B_136_748_5984 ; _rtB ->
B_89_1214_9712 = _rtB -> B_89_1213_9704 * _rtB -> B_136_739_5912 ; _rtB ->
B_136_751_6008 = _rtB -> B_89_1214_9712 ; } else { _rtB -> B_136_751_6008 =
_rtB -> B_136_1030_8240 ; } _rtB -> B_136_752_6016 = _rtB -> B_136_751_6008 *
_rtB -> AutomaticGainControl_m . B_56_1669_12744 ; _rtB -> B_136_753_6024 =
_rtP -> P_662 * _rtB -> B_136_752_6016 ; _rtB -> B_136_754_6032 = _rtP ->
P_663 * _rtB -> B_136_752_6016 ; _rtB -> B_136_755_6040 = _rtP -> P_664 *
_rtB -> B_136_752_6016 ; _rtB -> B_136_756_6048 = 0.0 ; _rtB ->
B_136_756_6048 += _rtP -> P_666 * _rtX -> TransferFcn_CSTATE_e ; _rtB ->
B_136_756_6048 += _rtP -> P_667 * _rtB -> B_136_755_6040 ; _rtB ->
B_136_757_6056 = ( _rtB -> B_136_753_6024 + _rtB -> B_136_747_5976 ) + _rtB
-> B_136_756_6048 ; if ( ssIsModeUpdateTimeStep ( S ) ) { if ( _rtB ->
B_136_757_6056 >= _rtP -> P_668 ) { _rtDW -> Saturation2_MODE_nj = 1 ; } else
if ( _rtB -> B_136_757_6056 > _rtP -> P_669 ) { _rtDW -> Saturation2_MODE_nj
= 0 ; } else { _rtDW -> Saturation2_MODE_nj = - 1 ; } } if ( _rtDW ->
Saturation2_MODE_nj == 1 ) { _rtB -> B_136_758_6064 = _rtP -> P_668 ; } else
if ( _rtDW -> Saturation2_MODE_nj == - 1 ) { _rtB -> B_136_758_6064 = _rtP ->
P_669 ; } else { _rtB -> B_136_758_6064 = _rtB -> B_136_757_6056 ; } _rtB ->
B_136_759_6072 = _rtP -> P_670 * _rtB -> B_136_758_6064 ; if ( _rtDW ->
LastMajorTime_kb == ( rtInf ) ) { _rtB -> B_136_760_6080 = _rtB ->
B_136_759_6072 ; } else { rtb_B_136_1884_14440 = ssGetTaskTime ( S , 0 ) -
_rtDW -> LastMajorTime_kb ; if ( _rtDW -> LastMajorTime_kb == ssGetTaskTime (
S , 0 ) ) { if ( _rtDW -> PrevLimited_g ) { _rtB -> B_136_760_6080 = _rtDW ->
PrevY_l ; } else { _rtB -> B_136_760_6080 = _rtB -> B_136_759_6072 ; } } else
{ rtb_B_136_1808_13832 = rtb_B_136_1884_14440 * _rtP -> P_671 ;
rtb_B_136_1807_13824 = _rtB -> B_136_759_6072 - _rtDW -> PrevY_l ; if (
rtb_B_136_1807_13824 > rtb_B_136_1808_13832 ) { _rtB -> B_136_760_6080 =
_rtDW -> PrevY_l + rtb_B_136_1808_13832 ; didZcEventOccur = true ; } else {
rtb_B_136_1884_14440 *= _rtP -> P_672 ; if ( rtb_B_136_1807_13824 <
rtb_B_136_1884_14440 ) { _rtB -> B_136_760_6080 = _rtDW -> PrevY_l +
rtb_B_136_1884_14440 ; didZcEventOccur = true ; } else { _rtB ->
B_136_760_6080 = _rtB -> B_136_759_6072 ; didZcEventOccur = false ; } } if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> PrevLimited_g = didZcEventOccur ; }
} } _rtB -> B_136_761_6088 = _rtX -> Integrator_x1_CSTATE_c ; _rtB ->
B_136_762_6096 = _rtP -> P_674 * _rtB -> B_136_761_6088 ; _rtB ->
B_136_763_6104 = _rtX -> Integrator_x2_CSTATE_oa ; _rtB -> B_136_764_6112 =
_rtP -> P_676 * _rtB -> B_136_763_6104 ; _rtB -> B_136_765_6120 = _rtP ->
P_677 * _rtB -> B_136_761_6088 ; _rtB -> B_136_766_6128 = _rtP -> P_678 *
_rtB -> B_136_763_6104 ; _rtB -> B_136_767_6136 = _rtB -> B_136_762_6096 +
_rtB -> B_136_764_6112 ; _rtB -> B_136_768_6144 = _rtB -> B_136_765_6120 +
_rtB -> B_136_766_6128 ; _rtB -> B_136_769_6152 = _rtP -> P_679 * _rtB ->
B_136_760_6080 ; _rtB -> B_136_770_6160 = _rtB -> B_136_767_6136 + _rtB ->
B_136_769_6152 ; _rtB -> B_136_771_6168 = _rtP -> P_680 * _rtB ->
B_136_760_6080 ; _rtB -> B_136_772_6176 = _rtB -> B_136_768_6144 + _rtB ->
B_136_771_6168 ; _rtB -> B_136_773_6184 = ( _rtP -> P_681 * _rtB ->
B_136_761_6088 + _rtP -> P_682 * _rtB -> B_136_763_6104 ) + _rtP -> P_683 *
_rtB -> B_136_760_6080 ; if ( _rtB -> B_136_739_5912 > _rtP -> P_684 ) { _rtB
-> B_136_774_6192 = _rtP -> P_684 ; } else if ( _rtB -> B_136_739_5912 < _rtP
-> P_685 ) { _rtB -> B_136_774_6192 = _rtP -> P_685 ; } else { _rtB ->
B_136_774_6192 = _rtB -> B_136_739_5912 ; } _rtB -> B_136_775_6200 = 1.0 /
_rtB -> B_136_774_6192 ; rtb_B_136_1807_13824 = _rtB -> B_136_743_5944 [ 1 ]
; rtb_B_136_1884_14440 = _rtB -> B_136_743_5944 [ 0 ] ; rtb_B_136_1808_13832
= _rtB -> B_136_743_5944 [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) {
rtb_B_136_1854_14200 = ( _rtP -> P_686 [ i + 3 ] * rtb_B_136_1807_13824 +
_rtP -> P_686 [ i ] * rtb_B_136_1884_14440 ) + _rtP -> P_686 [ i + 6 ] *
rtb_B_136_1808_13832 ; _rtB -> B_136_776_6208 [ i ] = rtb_B_136_1854_14200 ;
_rtB -> B_136_779_6232 [ i ] = _rtP -> P_687 * rtb_B_136_1854_14200 ; }
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1275_9899 , &
_rtB -> B_136_779_6232 [ 0 ] , _rtB -> B_136_742_5936 , & _rtB ->
Subsystempi2delay_na , & _rtDW -> Subsystempi2delay_na ) ;
dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1274_9898 , & _rtB ->
B_136_779_6232 [ 0 ] , _rtB -> B_136_742_5936 , & _rtB -> Subsystem1_bc , &
_rtDW -> Subsystem1_bc ) ; if ( _rtB -> B_136_1274_9898 != 0 ) { _rtB ->
B_136_782_6256 [ 0 ] = _rtB -> Subsystem1_bc . B_25_1750_13368 ; _rtB ->
B_136_782_6256 [ 1 ] = _rtB -> Subsystem1_bc . B_25_1751_13376 ; } else {
_rtB -> B_136_782_6256 [ 0 ] = _rtB -> Subsystempi2delay_na . B_24_1752_13384
; _rtB -> B_136_782_6256 [ 1 ] = _rtB -> Subsystempi2delay_na .
B_24_1753_13392 ; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB ->
B_136_784_6272 = _rtDW -> Memory_PreviousInput_cp ; if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> RelationalOperator_Mode_m = ( _rtX
-> Integrator_CSTATE_nj > _rtB -> B_136_1032_8256 ) ; } _rtB ->
B_136_1296_9920 = _rtDW -> RelationalOperator_Mode_m ; } _rtB ->
B_136_785_6280 = _rtX -> Integrator_CSTATE_nj - _rtB -> B_136_1032_8256 ; if
( ( _rtDW -> Initial_FirstOutputTime_gw == ( rtMinusInf ) ) || ( _rtDW ->
Initial_FirstOutputTime_gw == ssGetTaskTime ( S , 0 ) ) ) { _rtDW ->
Initial_FirstOutputTime_gw = ssGetTaskTime ( S , 0 ) ; _rtB -> B_136_786_6288
= _rtP -> P_689 ; } else { _rtB -> B_136_786_6288 = _rtB -> B_136_785_6280 ;
} if ( ssIsModeUpdateTimeStep ( S ) ) { didZcEventOccur = ( _rtB ->
B_136_1296_9920 && ( _rtZCE -> Integrator_Reset_ZCE_c != POS_ZCSIG ) ) ;
_rtZCE -> Integrator_Reset_ZCE_c = _rtB -> B_136_1296_9920 ; if (
didZcEventOccur || ( _rtDW -> Integrator_IWORK_m != 0 ) ) { didZcEventOccur =
( _rtX -> Integrator_CSTATE_nj != _rtB -> B_136_786_6288 ) ; _rtX ->
Integrator_CSTATE_nj = _rtB -> B_136_786_6288 ; if ( didZcEventOccur ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } } if ( _rtX ->
Integrator_CSTATE_nj >= _rtP -> P_690 ) { if ( _rtX -> Integrator_CSTATE_nj
!= _rtP -> P_690 ) { _rtX -> Integrator_CSTATE_nj = _rtP -> P_690 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_mo = 3 ; } else if ( _rtX -> Integrator_CSTATE_nj <= _rtP ->
P_691 ) { if ( _rtX -> Integrator_CSTATE_nj != _rtP -> P_691 ) { _rtX ->
Integrator_CSTATE_nj = _rtP -> P_691 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
ssSetContTimeOutputInconsistentWithStateAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_mo = 4 ; } else { if ( _rtDW -> Integrator_MODE_mo != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_mo = 0 ; } _rtB -> B_136_787_6296 = _rtX ->
Integrator_CSTATE_nj ; } else { _rtB -> B_136_787_6296 = _rtX ->
Integrator_CSTATE_nj ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
_rtB -> B_136_788_6304 [ 0 ] = _rtP -> P_692 * _rtB -> B_136_118_944 [ 43 ] *
_rtP -> P_695 ; _rtB -> B_136_788_6304 [ 1 ] = _rtP -> P_693 * _rtB ->
B_136_118_944 [ 44 ] * _rtP -> P_695 ; _rtB -> B_136_788_6304 [ 2 ] = _rtP ->
P_694 * _rtB -> B_136_118_944 [ 45 ] * _rtP -> P_695 ; rtb_B_136_1807_13824 =
_rtB -> B_136_788_6304 [ 1 ] ; rtb_B_136_1884_14440 = _rtB -> B_136_788_6304
[ 0 ] ; rtb_B_136_1808_13832 = _rtB -> B_136_788_6304 [ 2 ] ; for ( i = 0 ; i
< 3 ; i ++ ) { rtb_B_128_2256_17416 [ i ] = ( ( _rtP -> P_696 [ i + 3 ] *
rtb_B_136_1807_13824 + _rtP -> P_696 [ i ] * rtb_B_136_1884_14440 ) + _rtP ->
P_696 [ i + 6 ] * rtb_B_136_1808_13832 ) * _rtP -> P_697 ; } _rtB ->
B_136_791_6328 = muDoubleScalarHypot ( rtb_B_128_2256_17416 [ 0 ] ,
rtb_B_128_2256_17416 [ 1 ] ) ; } ssCallAccelRunBlock ( S , 136 , 1045 ,
SS_CALL_MDL_OUTPUTS ) ; dVOC_monitor_network1_AutomaticGainControl ( S , _rtB
-> B_136_1031_8248 , _rtB -> B_136_784_6272 , _rtB -> B_136_787_6296 , _rtB
-> B_136_788_6304 , & _rtB -> AutomaticGainControl_b2 , & _rtDW ->
AutomaticGainControl_b2 , & _rtP -> AutomaticGainControl_b2 , & _rtX ->
AutomaticGainControl_b2 , & _rtXdis -> AutomaticGainControl_b2 ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX -> Integrator_CSTATE_fu >= _rtP ->
P_700 ) { if ( _rtX -> Integrator_CSTATE_fu != _rtP -> P_700 ) { _rtX ->
Integrator_CSTATE_fu = _rtP -> P_700 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_h5 = 3 ; } else if ( _rtX -> Integrator_CSTATE_fu <= _rtP ->
P_701 ) { if ( _rtX -> Integrator_CSTATE_fu != _rtP -> P_701 ) { _rtX ->
Integrator_CSTATE_fu = _rtP -> P_701 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_h5 = 4 ; } else { if ( _rtDW -> Integrator_MODE_h5 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE_h5 = 0 ; } _rtB -> B_136_792_6336 = _rtX ->
Integrator_CSTATE_fu ; } else { _rtB -> B_136_792_6336 = _rtX ->
Integrator_CSTATE_fu ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_g . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; real_T appliedDelay ; _rtB -> B_136_793_6344 =
dVOC_monitor_network1_acc_rt_VTDelayfindtDInterpolate ( ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_b , * uBuffer , _rtDW ->
VariableTransportDelay_IWORK_p . CircularBufSize , _rtDW ->
VariableTransportDelay_IWORK_p . Head , _rtDW ->
VariableTransportDelay_IWORK_p . Tail , & _rtDW ->
VariableTransportDelay_IWORK_p . Last , simTime , 0.0 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
VariableTransportDelay_IWORK_p . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK_p . Head ] == ssGetT ( S ) ) ) , _rtP -> P_703 ,
& appliedDelay ) ; } _rtB -> B_136_794_6352 = _rtX -> integrator_CSTATE_mw ;
_rtB -> B_136_795_6360 = ssGetT ( S ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if
( i != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
RelationalOperator_Mode_m2 = ( _rtB -> B_136_795_6360 >= _rtB ->
B_136_1033_8264 ) ; } _rtB -> B_136_1297_9921 = _rtDW ->
RelationalOperator_Mode_m2 ; } if ( _rtB -> B_136_1297_9921 ) { _rtB ->
B_97_1211_9688 = _rtB -> B_136_794_6352 - _rtB -> B_136_793_6344 ; _rtB ->
B_97_1212_9696 = _rtB -> B_97_1211_9688 * _rtB -> B_136_784_6272 ; _rtB ->
B_136_796_6368 = _rtB -> B_97_1212_9696 ; } else { _rtB -> B_136_796_6368 =
_rtB -> B_136_1034_8272 ; } _rtB -> B_136_797_6376 = _rtB -> B_136_796_6368 *
_rtB -> AutomaticGainControl_b2 . B_56_1669_12744 ; _rtB -> B_136_798_6384 =
_rtP -> P_705 * _rtB -> B_136_797_6376 ; _rtB -> B_136_799_6392 = _rtP ->
P_706 * _rtB -> B_136_797_6376 ; _rtB -> B_136_800_6400 = _rtP -> P_707 *
_rtB -> B_136_797_6376 ; _rtB -> B_136_801_6408 = 0.0 ; _rtB ->
B_136_801_6408 += _rtP -> P_709 * _rtX -> TransferFcn_CSTATE_d ; _rtB ->
B_136_801_6408 += _rtP -> P_710 * _rtB -> B_136_800_6400 ; _rtB ->
B_136_802_6416 = ( _rtB -> B_136_798_6384 + _rtB -> B_136_792_6336 ) + _rtB
-> B_136_801_6408 ; if ( ssIsModeUpdateTimeStep ( S ) ) { if ( _rtB ->
B_136_802_6416 >= _rtP -> P_711 ) { _rtDW -> Saturation2_MODE_cm = 1 ; } else
if ( _rtB -> B_136_802_6416 > _rtP -> P_712 ) { _rtDW -> Saturation2_MODE_cm
= 0 ; } else { _rtDW -> Saturation2_MODE_cm = - 1 ; } } if ( _rtDW ->
Saturation2_MODE_cm == 1 ) { _rtB -> B_136_803_6424 = _rtP -> P_711 ; } else
if ( _rtDW -> Saturation2_MODE_cm == - 1 ) { _rtB -> B_136_803_6424 = _rtP ->
P_712 ; } else { _rtB -> B_136_803_6424 = _rtB -> B_136_802_6416 ; } _rtB ->
B_136_804_6432 = _rtP -> P_713 * _rtB -> B_136_803_6424 ; if ( _rtDW ->
LastMajorTime_i == ( rtInf ) ) { _rtB -> B_136_805_6440 = _rtB ->
B_136_804_6432 ; } else { rtb_B_136_1884_14440 = ssGetTaskTime ( S , 0 ) -
_rtDW -> LastMajorTime_i ; if ( _rtDW -> LastMajorTime_i == ssGetTaskTime ( S
, 0 ) ) { if ( _rtDW -> PrevLimited_m0 ) { _rtB -> B_136_805_6440 = _rtDW ->
PrevY_ow ; } else { _rtB -> B_136_805_6440 = _rtB -> B_136_804_6432 ; } }
else { rtb_B_136_1808_13832 = rtb_B_136_1884_14440 * _rtP -> P_714 ;
rtb_B_136_1807_13824 = _rtB -> B_136_804_6432 - _rtDW -> PrevY_ow ; if (
rtb_B_136_1807_13824 > rtb_B_136_1808_13832 ) { _rtB -> B_136_805_6440 =
_rtDW -> PrevY_ow + rtb_B_136_1808_13832 ; didZcEventOccur = true ; } else {
rtb_B_136_1884_14440 *= _rtP -> P_715 ; if ( rtb_B_136_1807_13824 <
rtb_B_136_1884_14440 ) { _rtB -> B_136_805_6440 = _rtDW -> PrevY_ow +
rtb_B_136_1884_14440 ; didZcEventOccur = true ; } else { _rtB ->
B_136_805_6440 = _rtB -> B_136_804_6432 ; didZcEventOccur = false ; } } if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> PrevLimited_m0 = didZcEventOccur ;
} } } _rtB -> B_136_806_6448 = _rtX -> Integrator_x1_CSTATE_n ; _rtB ->
B_136_807_6456 = _rtP -> P_717 * _rtB -> B_136_806_6448 ; _rtB ->
B_136_808_6464 = _rtX -> Integrator_x2_CSTATE_gi ; _rtB -> B_136_809_6472 =
_rtP -> P_719 * _rtB -> B_136_808_6464 ; _rtB -> B_136_810_6480 = _rtP ->
P_720 * _rtB -> B_136_806_6448 ; _rtB -> B_136_811_6488 = _rtP -> P_721 *
_rtB -> B_136_808_6464 ; _rtB -> B_136_812_6496 = _rtB -> B_136_807_6456 +
_rtB -> B_136_809_6472 ; _rtB -> B_136_813_6504 = _rtB -> B_136_810_6480 +
_rtB -> B_136_811_6488 ; _rtB -> B_136_814_6512 = _rtP -> P_722 * _rtB ->
B_136_805_6440 ; _rtB -> B_136_815_6520 = _rtB -> B_136_812_6496 + _rtB ->
B_136_814_6512 ; _rtB -> B_136_816_6528 = _rtP -> P_723 * _rtB ->
B_136_805_6440 ; _rtB -> B_136_817_6536 = _rtB -> B_136_813_6504 + _rtB ->
B_136_816_6528 ; _rtB -> B_136_818_6544 = ( _rtP -> P_724 * _rtB ->
B_136_806_6448 + _rtP -> P_725 * _rtB -> B_136_808_6464 ) + _rtP -> P_726 *
_rtB -> B_136_805_6440 ; if ( _rtB -> B_136_784_6272 > _rtP -> P_727 ) { _rtB
-> B_136_819_6552 = _rtP -> P_727 ; } else if ( _rtB -> B_136_784_6272 < _rtP
-> P_728 ) { _rtB -> B_136_819_6552 = _rtP -> P_728 ; } else { _rtB ->
B_136_819_6552 = _rtB -> B_136_784_6272 ; } _rtB -> B_136_820_6560 = 1.0 /
_rtB -> B_136_819_6552 ; rtb_B_136_1807_13824 = _rtB -> B_136_788_6304 [ 1 ]
; rtb_B_136_1884_14440 = _rtB -> B_136_788_6304 [ 0 ] ; rtb_B_136_1808_13832
= _rtB -> B_136_788_6304 [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) {
rtb_B_136_1854_14200 = ( _rtP -> P_729 [ i + 3 ] * rtb_B_136_1807_13824 +
_rtP -> P_729 [ i ] * rtb_B_136_1884_14440 ) + _rtP -> P_729 [ i + 6 ] *
rtb_B_136_1808_13832 ; _rtB -> B_136_821_6568 [ i ] = rtb_B_136_1854_14200 ;
_rtB -> B_136_824_6592 [ i ] = _rtP -> P_730 * rtb_B_136_1854_14200 ; }
dVOC_monitor_network1_Subsystempi2delay ( S , _rtB -> B_136_1277_9901 , &
_rtB -> B_136_824_6592 [ 0 ] , _rtB -> B_136_787_6296 , & _rtB ->
Subsystempi2delay_e , & _rtDW -> Subsystempi2delay_e ) ;
dVOC_monitor_network1_Subsystem1 ( S , _rtB -> B_136_1276_9900 , & _rtB ->
B_136_824_6592 [ 0 ] , _rtB -> B_136_787_6296 , & _rtB -> Subsystem1_j , &
_rtDW -> Subsystem1_j ) ; if ( _rtB -> B_136_1276_9900 != 0 ) { _rtB ->
B_136_827_6616 [ 0 ] = _rtB -> Subsystem1_j . B_25_1750_13368 ; _rtB ->
B_136_827_6616 [ 1 ] = _rtB -> Subsystem1_j . B_25_1751_13376 ; } else { _rtB
-> B_136_827_6616 [ 0 ] = _rtB -> Subsystempi2delay_e . B_24_1752_13384 ;
_rtB -> B_136_827_6616 [ 1 ] = _rtB -> Subsystempi2delay_e . B_24_1753_13392
; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { if ( _rtB ->
B_136_1035_8280 >= _rtP -> P_734 ) { rtb_B_136_1807_13824 = _rtB ->
B_136_1040_8320 ; } else { rtb_B_136_1807_13824 = rt_Lookup ( & _rtP -> P_732
[ 0 ] , 6 , ssGetTaskTime ( S , 2 ) , & _rtP -> P_733 [ 0 ] ) ; } if ( _rtP
-> P_731 >= _rtP -> P_735 ) { if ( _rtB -> B_136_1036_8288 >= _rtP -> P_0 ) {
_rtB -> B_136_829_6632 = rtb_B_136_1807_13824 ; } else { _rtB ->
B_136_829_6632 = _rtB -> B_136_1039_8312 ; } } else { _rtB -> B_136_829_6632
= rt_Lookup ( & _rtP -> P_1 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP ->
P_2 [ 0 ] ) ; } if ( _rtP -> P_736 >= _rtP -> P_737 ) { if ( _rtB ->
B_136_1037_8296 >= _rtP -> P_3 ) { _rtB -> B_136_830_6640 =
rtb_B_136_1807_13824 ; } else { _rtB -> B_136_830_6640 = _rtB ->
B_136_1039_8312 ; } } else { _rtB -> B_136_830_6640 = rt_Lookup ( & _rtP ->
P_4 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP -> P_5 [ 0 ] ) ; } if ( _rtP
-> P_738 >= _rtP -> P_739 ) { if ( _rtB -> B_136_1038_8304 >= _rtP -> P_6 ) {
_rtB -> B_136_831_6648 = rtb_B_136_1807_13824 ; } else { _rtB ->
B_136_831_6648 = _rtB -> B_136_1039_8312 ; } } else { _rtB -> B_136_831_6648
= rt_Lookup ( & _rtP -> P_7 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP ->
P_8 [ 0 ] ) ; } if ( _rtB -> B_136_1041_8328 >= _rtP -> P_743 ) {
rtb_B_136_1807_13824 = _rtB -> B_136_1046_8368 ; } else {
rtb_B_136_1807_13824 = rt_Lookup ( & _rtP -> P_741 [ 0 ] , 6 , ssGetTaskTime
( S , 2 ) , & _rtP -> P_742 [ 0 ] ) ; } if ( _rtP -> P_740 >= _rtP -> P_744 )
{ if ( _rtB -> B_136_1042_8336 >= _rtP -> P_9 ) { _rtB -> B_136_832_6656 =
rtb_B_136_1807_13824 ; } else { _rtB -> B_136_832_6656 = _rtB ->
B_136_1045_8360 ; } } else { _rtB -> B_136_832_6656 = rt_Lookup ( & _rtP ->
P_10 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP -> P_11 [ 0 ] ) ; } if (
_rtP -> P_745 >= _rtP -> P_746 ) { if ( _rtB -> B_136_1043_8344 >= _rtP ->
P_12 ) { _rtB -> B_136_833_6664 = rtb_B_136_1807_13824 ; } else { _rtB ->
B_136_833_6664 = _rtB -> B_136_1045_8360 ; } } else { _rtB -> B_136_833_6664
= rt_Lookup ( & _rtP -> P_13 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP ->
P_14 [ 0 ] ) ; } if ( _rtP -> P_747 >= _rtP -> P_748 ) { if ( _rtB ->
B_136_1044_8352 >= _rtP -> P_15 ) { _rtB -> B_136_834_6672 =
rtb_B_136_1807_13824 ; } else { _rtB -> B_136_834_6672 = _rtB ->
B_136_1045_8360 ; } } else { _rtB -> B_136_834_6672 = rt_Lookup ( & _rtP ->
P_16 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP -> P_17 [ 0 ] ) ; } if (
_rtB -> B_136_1047_8376 >= _rtP -> P_752 ) { rtb_B_136_1807_13824 = _rtB ->
B_136_1052_8416 ; } else { rtb_B_136_1807_13824 = rt_Lookup ( & _rtP -> P_750
[ 0 ] , 6 , ssGetTaskTime ( S , 2 ) , & _rtP -> P_751 [ 0 ] ) ; } if ( _rtP
-> P_749 >= _rtP -> P_753 ) { if ( _rtB -> B_136_1048_8384 >= _rtP -> P_18 )
{ _rtB -> B_136_835_6680 = rtb_B_136_1807_13824 ; } else { _rtB ->
B_136_835_6680 = _rtB -> B_136_1051_8408 ; } } else { _rtB -> B_136_835_6680
= rt_Lookup ( & _rtP -> P_19 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP ->
P_20 [ 0 ] ) ; } if ( _rtP -> P_754 >= _rtP -> P_755 ) { if ( _rtB ->
B_136_1049_8392 >= _rtP -> P_21 ) { _rtB -> B_136_836_6688 =
rtb_B_136_1807_13824 ; } else { _rtB -> B_136_836_6688 = _rtB ->
B_136_1051_8408 ; } } else { _rtB -> B_136_836_6688 = rt_Lookup ( & _rtP ->
P_22 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP -> P_23 [ 0 ] ) ; } if (
_rtP -> P_756 >= _rtP -> P_757 ) { if ( _rtB -> B_136_1050_8400 >= _rtP ->
P_24 ) { _rtB -> B_136_837_6696 = rtb_B_136_1807_13824 ; } else { _rtB ->
B_136_837_6696 = _rtB -> B_136_1051_8408 ; } } else { _rtB -> B_136_837_6696
= rt_Lookup ( & _rtP -> P_25 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP ->
P_26 [ 0 ] ) ; } if ( _rtB -> B_136_1053_8424 >= _rtP -> P_761 ) {
rtb_B_136_1807_13824 = _rtB -> B_136_1058_8464 ; } else {
rtb_B_136_1807_13824 = rt_Lookup ( & _rtP -> P_759 [ 0 ] , 6 , ssGetTaskTime
( S , 2 ) , & _rtP -> P_760 [ 0 ] ) ; } if ( _rtP -> P_758 >= _rtP -> P_762 )
{ if ( _rtB -> B_136_1054_8432 >= _rtP -> P_27 ) { _rtB -> B_136_838_6704 =
rtb_B_136_1807_13824 ; } else { _rtB -> B_136_838_6704 = _rtB ->
B_136_1057_8456 ; } } else { _rtB -> B_136_838_6704 = rt_Lookup ( & _rtP ->
P_28 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP -> P_29 [ 0 ] ) ; } if (
_rtP -> P_763 >= _rtP -> P_764 ) { if ( _rtB -> B_136_1055_8440 >= _rtP ->
P_30 ) { _rtB -> B_136_839_6712 = rtb_B_136_1807_13824 ; } else { _rtB ->
B_136_839_6712 = _rtB -> B_136_1057_8456 ; } } else { _rtB -> B_136_839_6712
= rt_Lookup ( & _rtP -> P_31 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP ->
P_32 [ 0 ] ) ; } if ( _rtP -> P_765 >= _rtP -> P_766 ) { if ( _rtB ->
B_136_1056_8448 >= _rtP -> P_33 ) { _rtB -> B_136_840_6720 =
rtb_B_136_1807_13824 ; } else { _rtB -> B_136_840_6720 = _rtB ->
B_136_1057_8456 ; } } else { _rtB -> B_136_840_6720 = rt_Lookup ( & _rtP ->
P_34 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP -> P_35 [ 0 ] ) ; } if (
_rtB -> B_136_1059_8472 >= _rtP -> P_770 ) { rtb_B_136_1807_13824 = _rtB ->
B_136_1064_8512 ; } else { rtb_B_136_1807_13824 = rt_Lookup ( & _rtP -> P_768
[ 0 ] , 4 , ssGetTaskTime ( S , 2 ) , & _rtP -> P_769 [ 0 ] ) ; } if ( _rtP
-> P_767 >= _rtP -> P_771 ) { if ( _rtB -> B_136_1060_8480 >= _rtP -> P_61 )
{ _rtB -> B_136_841_6728 = rtb_B_136_1807_13824 ; } else { _rtB ->
B_136_841_6728 = _rtB -> B_136_1063_8504 ; } } else { _rtB -> B_136_841_6728
= rt_Lookup ( & _rtP -> P_62 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP ->
P_63 [ 0 ] ) ; } if ( _rtP -> P_772 >= _rtP -> P_773 ) { if ( _rtB ->
B_136_1061_8488 >= _rtP -> P_64 ) { _rtB -> B_136_842_6736 =
rtb_B_136_1807_13824 ; } else { _rtB -> B_136_842_6736 = _rtB ->
B_136_1063_8504 ; } } else { _rtB -> B_136_842_6736 = rt_Lookup ( & _rtP ->
P_65 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP -> P_66 [ 0 ] ) ; } if (
_rtP -> P_774 >= _rtP -> P_775 ) { if ( _rtB -> B_136_1062_8496 >= _rtP ->
P_67 ) { _rtB -> B_136_843_6744 = rtb_B_136_1807_13824 ; } else { _rtB ->
B_136_843_6744 = _rtB -> B_136_1063_8504 ; } } else { _rtB -> B_136_843_6744
= rt_Lookup ( & _rtP -> P_68 [ 0 ] , 5 , ssGetTaskTime ( S , 2 ) , & _rtP ->
P_69 [ 0 ] ) ; } } UNUSED_PARAMETER ( tid ) ; } static void mdlOutputsTID4 (
SimStruct * S , int_T tid ) { B_dVOC_monitor_network1_T * _rtB ;
DW_dVOC_monitor_network1_T * _rtDW ; P_dVOC_monitor_network1_T * _rtP ;
real_T rtb_B_136_2056_15816 ; _rtDW = ( ( DW_dVOC_monitor_network1_T * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( P_dVOC_monitor_network1_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_dVOC_monitor_network1_T * )
_ssGetModelBlockIO ( S ) ) ; memcpy ( & _rtB -> B_136_844_6752 [ 0 ] , & _rtP
-> P_776 [ 0 ] , 15U * sizeof ( real_T ) ) ; _rtB -> B_136_859_6872 = _rtP ->
P_781 ; _rtB -> B_136_860_6880 = _rtP -> P_782 ; _rtB -> B_136_861_6888 =
_rtP -> P_783 ; _rtB -> B_136_862_6896 = _rtP -> P_785 ; _rtB ->
B_136_863_6904 = _rtP -> P_786 ; rtb_B_136_2056_15816 = _rtP -> P_788 * _rtP
-> P_779 ; _rtB -> B_136_864_6912 = _rtP -> P_789 * rtb_B_136_2056_15816 ;
_rtB -> B_136_1232_9856 = ( uint8_T ) ( _rtP -> P_790 == _rtP -> P_791 ) ;
_rtB -> B_136_1233_9857 = ( uint8_T ) ( _rtP -> P_790 == _rtP -> P_792 ) ;
_rtB -> B_136_1234_9858 = ( uint8_T ) ( _rtP -> P_793 == _rtP -> P_794 ) ;
_rtB -> B_136_1235_9859 = ( uint8_T ) ( _rtP -> P_793 == _rtP -> P_795 ) ;
_rtB -> B_136_1236_9860 = ( uint8_T ) ( _rtP -> P_796 == _rtP -> P_797 ) ;
_rtB -> B_136_1237_9861 = ( uint8_T ) ( _rtP -> P_796 == _rtP -> P_798 ) ;
_rtB -> B_136_1238_9862 = ( uint8_T ) ( _rtP -> P_799 == _rtP -> P_800 ) ;
_rtB -> B_136_1239_9863 = ( uint8_T ) ( _rtP -> P_799 == _rtP -> P_801 ) ;
_rtB -> B_136_1240_9864 = ( uint8_T ) ( _rtP -> P_802 == _rtP -> P_803 ) ;
_rtB -> B_136_1241_9865 = ( uint8_T ) ( _rtP -> P_802 == _rtP -> P_804 ) ;
_rtB -> B_136_1242_9866 = ( uint8_T ) ( _rtP -> P_805 == _rtP -> P_806 ) ;
_rtB -> B_136_1243_9867 = ( uint8_T ) ( _rtP -> P_805 == _rtP -> P_807 ) ;
_rtB -> B_136_865_6920 = _rtP -> P_808 ; _rtB -> B_136_866_6928 =
rtb_B_136_2056_15816 / ( _rtP -> P_784 * _rtP -> P_784 ) ; _rtB ->
B_136_867_6936 = _rtP -> P_784 * _rtP -> P_784 ; _rtB -> B_136_868_6944 =
_rtP -> P_809 ; _rtB -> B_136_869_6952 = _rtP -> P_787 * _rtP -> P_778 / (
_rtP -> P_784 * _rtP -> P_784 ) ; _rtB -> B_136_870_6960 = _rtP -> P_810 ;
_rtB -> B_136_1244_9868 = ( uint8_T ) ( _rtP -> P_811 == _rtP -> P_812 ) ;
_rtB -> B_136_1245_9869 = ( uint8_T ) ( _rtP -> P_811 == _rtP -> P_813 ) ;
_rtB -> B_136_871_6968 = _rtP -> P_814 ; _rtB -> B_136_872_6976 = _rtP ->
P_815 ; _rtB -> B_136_873_6984 = _rtP -> P_817 ; _rtB -> B_136_874_6992 =
_rtP -> P_818 ; rtb_B_136_2056_15816 = _rtP -> P_820 * _rtP -> P_777 ; _rtB
-> B_136_875_7000 = _rtP -> P_821 * rtb_B_136_2056_15816 ; _rtB ->
B_136_1246_9870 = ( uint8_T ) ( _rtP -> P_822 == _rtP -> P_823 ) ; _rtB ->
B_136_1247_9871 = ( uint8_T ) ( _rtP -> P_822 == _rtP -> P_824 ) ; _rtB ->
B_136_1248_9872 = ( uint8_T ) ( _rtP -> P_825 == _rtP -> P_826 ) ; _rtB ->
B_136_1249_9873 = ( uint8_T ) ( _rtP -> P_825 == _rtP -> P_827 ) ; _rtB ->
B_136_1250_9874 = ( uint8_T ) ( _rtP -> P_828 == _rtP -> P_829 ) ; _rtB ->
B_136_1251_9875 = ( uint8_T ) ( _rtP -> P_828 == _rtP -> P_830 ) ; _rtB ->
B_136_1252_9876 = ( uint8_T ) ( _rtP -> P_831 == _rtP -> P_832 ) ; _rtB ->
B_136_1253_9877 = ( uint8_T ) ( _rtP -> P_831 == _rtP -> P_833 ) ; _rtB ->
B_136_1254_9878 = ( uint8_T ) ( _rtP -> P_834 == _rtP -> P_835 ) ; _rtB ->
B_136_1255_9879 = ( uint8_T ) ( _rtP -> P_834 == _rtP -> P_836 ) ; _rtB ->
B_136_1256_9880 = ( uint8_T ) ( _rtP -> P_837 == _rtP -> P_838 ) ; _rtB ->
B_136_1257_9881 = ( uint8_T ) ( _rtP -> P_837 == _rtP -> P_839 ) ; _rtB ->
B_136_876_7008 = _rtP -> P_840 ; _rtB -> B_136_877_7016 =
rtb_B_136_2056_15816 / ( _rtP -> P_816 * _rtP -> P_816 ) ; _rtB ->
B_136_878_7024 = _rtP -> P_816 * _rtP -> P_816 ; _rtB -> B_136_879_7032 =
_rtP -> P_841 ; _rtB -> B_136_880_7040 = _rtP -> P_819 * _rtP -> P_780 / (
_rtP -> P_816 * _rtP -> P_816 ) ; _rtB -> B_136_881_7048 = _rtP -> P_842 ;
_rtB -> B_136_1258_9882 = ( uint8_T ) ( _rtP -> P_843 == _rtP -> P_844 ) ;
_rtB -> B_136_1259_9883 = ( uint8_T ) ( _rtP -> P_843 == _rtP -> P_845 ) ;
_rtB -> B_136_882_7056 = _rtP -> P_846 ; _rtB -> B_136_883_7064 = _rtP ->
P_847 ; _rtB -> B_136_1298_9922 = _rtP -> P_994 ; _rtB -> B_136_884_7072 =
_rtP -> P_848 ; _rtB -> B_136_885_7080 = _rtP -> P_849 ; _rtB ->
B_136_886_7088 = _rtP -> P_850 ; _rtB -> B_136_887_7096 = _rtP -> P_851 ;
_rtB -> B_136_913_7304 = _rtP -> P_853 ; _rtB -> B_136_939_7512 = _rtP ->
P_855 ; _rtB -> B_136_940_7520 [ 0 ] = _rtP -> P_856 [ 0 ] ; _rtB ->
B_136_942_7536 [ 0 ] = _rtP -> P_857 [ 0 ] ; _rtB -> B_136_940_7520 [ 1 ] =
_rtP -> P_856 [ 1 ] ; _rtB -> B_136_942_7536 [ 1 ] = _rtP -> P_857 [ 1 ] ;
_rtB -> B_128_1299_9923 = _rtP -> P_991 ; _rtB -> B_128_1300_9924 = _rtP ->
P_992 ; _rtB -> B_128_1301_9925 = _rtP -> P_993 ; _rtB -> B_128_1119_8952 =
_rtP -> P_54 ; _rtB -> B_128_1120_8960 [ 0 ] = _rtP -> P_55 [ 0 ] ; _rtB ->
B_128_1120_8960 [ 1 ] = _rtP -> P_55 [ 1 ] ; _rtB -> B_127_1201_9608 = _rtP
-> P_43 ; _rtB -> B_127_1202_9616 [ 0 ] = _rtP -> P_44 [ 0 ] ; _rtB ->
B_127_1202_9616 [ 1 ] = _rtP -> P_44 [ 1 ] ; _rtB -> B_127_1202_9616 [ 2 ] =
_rtP -> P_44 [ 2 ] ; _rtB -> B_128_1197_9576 = _rtP -> P_59 ; _rtB ->
B_128_1198_9584 = _rtP -> P_60 ; memcpy ( & _rtB -> B_136_888_7104 [ 0 ] , &
_rtP -> P_852 [ 0 ] , 25U * sizeof ( real_T ) ) ; memcpy ( & _rtB ->
B_136_914_7312 [ 0 ] , & _rtP -> P_854 [ 0 ] , 25U * sizeof ( real_T ) ) ;
memcpy ( & _rtB -> B_136_944_7552 [ 0 ] , & _rtP -> P_858 [ 0 ] , 25U *
sizeof ( real_T ) ) ; memcpy ( & _rtB -> B_128_1122_8976 [ 0 ] , & _rtP ->
P_56 [ 0 ] , 25U * sizeof ( real_T ) ) ; memcpy ( & _rtB -> B_128_1147_9176 [
0 ] , & _rtP -> P_57 [ 0 ] , 25U * sizeof ( real_T ) ) ; memcpy ( & _rtB ->
B_128_1172_9376 [ 0 ] , & _rtP -> P_58 [ 0 ] , 25U * sizeof ( real_T ) ) ;
memcpy ( & _rtB -> B_136_969_7752 [ 0 ] , & _rtP -> P_859 [ 0 ] , 25U *
sizeof ( real_T ) ) ; _rtB -> B_136_994_7952 [ 0 ] = _rtP -> P_860 [ 0 ] ;
_rtB -> B_136_994_7952 [ 1 ] = _rtP -> P_860 [ 1 ] ; _rtB -> B_136_996_7968 =
_rtP -> P_861 ; _rtB -> B_136_997_7976 = _rtP -> P_862 ; _rtB ->
B_136_998_7984 = _rtP -> P_863 ;
dVOC_monitor_network1_AutomaticGainControlTID4 ( S , & _rtB ->
AutomaticGainControl_g , & _rtDW -> AutomaticGainControl_g , & _rtP ->
AutomaticGainControl_g ) ; _rtB -> B_136_999_7992 = _rtP -> P_864 ; _rtB ->
B_136_1000_8000 = _rtP -> P_865 ; _rtB -> B_136_1001_8008 = _rtP -> P_866 ;
_rtB -> B_136_1002_8016 = _rtP -> P_867 ; _rtB -> B_136_1260_9884 = ( uint8_T
) ( _rtP -> P_868 == _rtP -> P_869 ) ; _rtB -> B_136_1261_9885 = ( uint8_T )
( _rtP -> P_868 == _rtP -> P_870 ) ;
dVOC_monitor_network1_AutomaticGainControlTID4 ( S , & _rtB ->
AutomaticGainControl_k , & _rtDW -> AutomaticGainControl_k , & _rtP ->
AutomaticGainControl_k ) ; _rtB -> B_136_1003_8024 = _rtP -> P_871 ; _rtB ->
B_136_1004_8032 = _rtP -> P_872 ; _rtB -> B_136_1005_8040 = _rtP -> P_873 ;
_rtB -> B_136_1006_8048 = _rtP -> P_874 ; _rtB -> B_136_1262_9886 = ( uint8_T
) ( _rtP -> P_875 == _rtP -> P_876 ) ; _rtB -> B_136_1263_9887 = ( uint8_T )
( _rtP -> P_875 == _rtP -> P_877 ) ;
dVOC_monitor_network1_AutomaticGainControlTID4 ( S , & _rtB ->
AutomaticGainControl_c , & _rtDW -> AutomaticGainControl_c , & _rtP ->
AutomaticGainControl_c ) ; _rtB -> B_136_1007_8056 = _rtP -> P_878 ; _rtB ->
B_136_1008_8064 = _rtP -> P_879 ; _rtB -> B_136_1009_8072 = _rtP -> P_880 ;
_rtB -> B_136_1010_8080 = _rtP -> P_881 ; _rtB -> B_136_1264_9888 = ( uint8_T
) ( _rtP -> P_882 == _rtP -> P_883 ) ; _rtB -> B_136_1265_9889 = ( uint8_T )
( _rtP -> P_882 == _rtP -> P_884 ) ;
dVOC_monitor_network1_AutomaticGainControlTID4 ( S , & _rtB ->
AutomaticGainControl_b , & _rtDW -> AutomaticGainControl_b , & _rtP ->
AutomaticGainControl_b ) ; _rtB -> B_136_1011_8088 = _rtP -> P_885 ; _rtB ->
B_136_1012_8096 = _rtP -> P_886 ; _rtB -> B_136_1013_8104 = _rtP -> P_887 ;
_rtB -> B_136_1014_8112 = _rtP -> P_888 ; _rtB -> B_136_1266_9890 = ( uint8_T
) ( _rtP -> P_889 == _rtP -> P_890 ) ; _rtB -> B_136_1267_9891 = ( uint8_T )
( _rtP -> P_889 == _rtP -> P_891 ) ;
dVOC_monitor_network1_AutomaticGainControlTID4 ( S , & _rtB ->
AutomaticGainControl_l , & _rtDW -> AutomaticGainControl_l , & _rtP ->
AutomaticGainControl_l ) ; _rtB -> B_136_1015_8120 = _rtP -> P_892 ; _rtB ->
B_136_1016_8128 = _rtP -> P_893 ; _rtB -> B_136_1017_8136 = _rtP -> P_894 ;
_rtB -> B_136_1018_8144 = _rtP -> P_895 ; _rtB -> B_136_1268_9892 = ( uint8_T
) ( _rtP -> P_896 == _rtP -> P_897 ) ; _rtB -> B_136_1269_9893 = ( uint8_T )
( _rtP -> P_896 == _rtP -> P_898 ) ;
dVOC_monitor_network1_AutomaticGainControlTID4 ( S , & _rtB ->
AutomaticGainControl_a , & _rtDW -> AutomaticGainControl_a , & _rtP ->
AutomaticGainControl_a ) ; _rtB -> B_136_1019_8152 = _rtP -> P_899 ; _rtB ->
B_136_1020_8160 = _rtP -> P_900 ; _rtB -> B_136_1021_8168 = _rtP -> P_901 ;
_rtB -> B_136_1022_8176 = _rtP -> P_902 ; _rtB -> B_136_1270_9894 = ( uint8_T
) ( _rtP -> P_903 == _rtP -> P_904 ) ; _rtB -> B_136_1271_9895 = ( uint8_T )
( _rtP -> P_903 == _rtP -> P_905 ) ;
dVOC_monitor_network1_AutomaticGainControlTID4 ( S , & _rtB ->
AutomaticGainControl , & _rtDW -> AutomaticGainControl , & _rtP ->
AutomaticGainControl ) ; _rtB -> B_136_1023_8184 = _rtP -> P_906 ; _rtB ->
B_136_1024_8192 = _rtP -> P_907 ; _rtB -> B_136_1025_8200 = _rtP -> P_908 ;
_rtB -> B_136_1026_8208 = _rtP -> P_909 ; _rtB -> B_136_1272_9896 = ( uint8_T
) ( _rtP -> P_910 == _rtP -> P_911 ) ; _rtB -> B_136_1273_9897 = ( uint8_T )
( _rtP -> P_910 == _rtP -> P_912 ) ;
dVOC_monitor_network1_AutomaticGainControlTID4 ( S , & _rtB ->
AutomaticGainControl_m , & _rtDW -> AutomaticGainControl_m , & _rtP ->
AutomaticGainControl_m ) ; _rtB -> B_136_1027_8216 = _rtP -> P_913 ; _rtB ->
B_136_1028_8224 = _rtP -> P_914 ; _rtB -> B_136_1029_8232 = _rtP -> P_915 ;
_rtB -> B_136_1030_8240 = _rtP -> P_916 ; _rtB -> B_136_1274_9898 = ( uint8_T
) ( _rtP -> P_917 == _rtP -> P_918 ) ; _rtB -> B_136_1275_9899 = ( uint8_T )
( _rtP -> P_917 == _rtP -> P_919 ) ;
dVOC_monitor_network1_AutomaticGainControlTID4 ( S , & _rtB ->
AutomaticGainControl_b2 , & _rtDW -> AutomaticGainControl_b2 , & _rtP ->
AutomaticGainControl_b2 ) ; _rtB -> B_136_1031_8248 = _rtP -> P_920 ; _rtB ->
B_136_1032_8256 = _rtP -> P_921 ; _rtB -> B_136_1033_8264 = _rtP -> P_922 ;
_rtB -> B_136_1034_8272 = _rtP -> P_923 ; _rtB -> B_136_1276_9900 = ( uint8_T
) ( _rtP -> P_924 == _rtP -> P_925 ) ; _rtB -> B_136_1277_9901 = ( uint8_T )
( _rtP -> P_924 == _rtP -> P_926 ) ; _rtB -> B_136_1035_8280 = _rtP -> P_927
; _rtB -> B_136_1036_8288 = _rtP -> P_928 ; _rtB -> B_136_1037_8296 = _rtP ->
P_929 ; _rtB -> B_136_1038_8304 = _rtP -> P_930 ; _rtB -> B_136_1039_8312 =
_rtP -> P_931 ; _rtB -> B_136_1040_8320 = _rtP -> P_932 ; _rtB ->
B_136_1041_8328 = _rtP -> P_933 ; _rtB -> B_136_1042_8336 = _rtP -> P_934 ;
_rtB -> B_136_1043_8344 = _rtP -> P_935 ; _rtB -> B_136_1044_8352 = _rtP ->
P_936 ; _rtB -> B_136_1045_8360 = _rtP -> P_937 ; _rtB -> B_136_1046_8368 =
_rtP -> P_938 ; _rtB -> B_136_1047_8376 = _rtP -> P_939 ; _rtB ->
B_136_1048_8384 = _rtP -> P_940 ; _rtB -> B_136_1049_8392 = _rtP -> P_941 ;
_rtB -> B_136_1050_8400 = _rtP -> P_942 ; _rtB -> B_136_1051_8408 = _rtP ->
P_943 ; _rtB -> B_136_1052_8416 = _rtP -> P_944 ; _rtB -> B_136_1053_8424 =
_rtP -> P_945 ; _rtB -> B_136_1054_8432 = _rtP -> P_946 ; _rtB ->
B_136_1055_8440 = _rtP -> P_947 ; _rtB -> B_136_1056_8448 = _rtP -> P_948 ;
_rtB -> B_136_1057_8456 = _rtP -> P_949 ; _rtB -> B_136_1058_8464 = _rtP ->
P_950 ; _rtB -> B_136_1059_8472 = _rtP -> P_951 ; _rtB -> B_136_1060_8480 =
_rtP -> P_952 ; _rtB -> B_136_1061_8488 = _rtP -> P_953 ; _rtB ->
B_136_1062_8496 = _rtP -> P_954 ; _rtB -> B_136_1063_8504 = _rtP -> P_955 ;
_rtB -> B_136_1064_8512 = _rtP -> P_956 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) {
B_dVOC_monitor_network1_T * _rtB ; DW_dVOC_monitor_network1_T * _rtDW ;
P_dVOC_monitor_network1_T * _rtP ; XDis_dVOC_monitor_network1_T * _rtXdis ;
int32_T i ; _rtDW = ( ( DW_dVOC_monitor_network1_T * ) ssGetRootDWork ( S ) )
; _rtXdis = ( ( XDis_dVOC_monitor_network1_T * ) ssGetContStateDisabled ( S )
) ; _rtP = ( ( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) ; _rtB = (
( B_dVOC_monitor_network1_T * ) _ssGetModelBlockIO ( S ) ) ; i =
ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtDW ->
Rotorangledthetae_DSTATE += _rtP -> P_70 * _rtB -> B_136_422_3376 ; for ( i =
0 ; i < 5 ; i ++ ) { _rtDW -> fluxes_DSTATE [ i ] = _rtB -> B_136_415_3320 [
i ] ; } if ( _rtB -> B_136_885_7080 > 0.0 ) { i = ssIsSampleHit ( S , 2 , 0 )
; if ( i != 0 ) { _rtDW -> Lmd_sat_DSTATE = _rtB -> B_128_1066_8528 ; if (
_rtB -> B_128_1299_9923 ) { i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
_rtDW -> Lmq_sat_DSTATE = _rtB -> B_127_1200_9600 ; } } } } } i =
ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtDW -> Memory2_PreviousInput
[ 0 ] = _rtB -> B_136_309_2472 ; _rtDW -> Memory2_PreviousInput [ 1 ] = _rtB
-> B_136_310_2480 ; _rtDW -> Memory2_PreviousInput [ 2 ] = _rtB ->
B_136_311_2488 ; _rtDW -> Memory3_PreviousInput [ 0 ] = _rtB ->
B_136_297_2376 ; _rtDW -> Memory3_PreviousInput [ 1 ] = _rtB ->
B_136_298_2384 ; _rtDW -> Memory3_PreviousInput [ 2 ] = _rtB ->
B_136_299_2392 ; _rtDW -> Memory1_PreviousInput [ 0 ] = _rtB ->
B_136_300_2400 ; _rtDW -> Memory1_PreviousInput [ 1 ] = _rtB ->
B_136_301_2408 ; _rtDW -> Memory1_PreviousInput [ 2 ] = _rtB ->
B_136_302_2416 ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtDW ->
Vdc_DSTATE = _rtB -> B_136_118_944 [ 17 ] ; _rtDW -> Idc_DSTATE = _rtB ->
B_136_288_2304 ; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtDW ->
Memory2_PreviousInput_p [ 0 ] = _rtB -> B_136_344_2752 ; _rtDW ->
Memory2_PreviousInput_p [ 1 ] = _rtB -> B_136_345_2760 ; _rtDW ->
Memory2_PreviousInput_p [ 2 ] = _rtB -> B_136_346_2768 ; _rtDW ->
Memory3_PreviousInput_b [ 0 ] = _rtB -> B_136_332_2656 ; _rtDW ->
Memory3_PreviousInput_b [ 1 ] = _rtB -> B_136_333_2664 ; _rtDW ->
Memory3_PreviousInput_b [ 2 ] = _rtB -> B_136_334_2672 ; _rtDW ->
Memory1_PreviousInput_m [ 0 ] = _rtB -> B_136_335_2680 ; _rtDW ->
Memory1_PreviousInput_m [ 1 ] = _rtB -> B_136_336_2688 ; _rtDW ->
Memory1_PreviousInput_m [ 2 ] = _rtB -> B_136_337_2696 ; } i = ssIsSampleHit
( S , 2 , 0 ) ; if ( i != 0 ) { _rtDW -> Vdc_DSTATE_j = _rtB -> B_136_118_944
[ 18 ] ; _rtDW -> Idc_DSTATE_j = _rtB -> B_136_323_2584 ; ssCallAccelRunBlock
( S , 136 , 176 , SS_CALL_MDL_UPDATE ) ; _rtDW -> dw_delay_DSTATE = _rtB ->
B_136_421_3368 ; _rtDW -> dw_predict_DSTATE = _rtB -> B_136_209_1672 ; } i =
ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtDW -> Memory_PreviousInput [
0 ] = _rtB -> B_136_306_2448 ; _rtDW -> Memory_PreviousInput [ 1 ] = _rtB ->
B_136_307_2456 ; _rtDW -> Memory_PreviousInput [ 2 ] = _rtB -> B_136_308_2464
; _rtDW -> Memory_PreviousInput_a [ 0 ] = _rtB -> B_136_341_2728 ; _rtDW ->
Memory_PreviousInput_a [ 1 ] = _rtB -> B_136_342_2736 ; _rtDW ->
Memory_PreviousInput_a [ 2 ] = _rtB -> B_136_343_2744 ; } i = ssIsSampleHit (
S , 2 , 0 ) ; if ( i != 0 ) { _rtDW -> prediction_DSTATE = _rtB ->
B_136_54_432 ; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtDW ->
Memory4_PreviousInput = _rtB -> B_136_305_2440 ; } i = ssIsSampleHit ( S , 2
, 0 ) ; if ( i != 0 ) { _rtDW -> prediction_DSTATE_e = _rtB -> B_136_105_840
; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtDW ->
Memory4_PreviousInput_c = _rtB -> B_136_340_2720 ; } i = ssIsSampleHit ( S ,
2 , 0 ) ; if ( i != 0 ) { { real_T xnew [ 1 ] ; xnew [ 0 ] = _rtP -> P_279 *
_rtDW -> DiscreteStateSpace_DSTATE ; xnew [ 0 ] += _rtP -> P_280 * _rtB ->
B_136_210_1680 ; ( void ) memcpy ( & _rtDW -> DiscreteStateSpace_DSTATE ,
xnew , sizeof ( real_T ) * 1 ) ; } { real_T xnew [ 1 ] ; xnew [ 0 ] = _rtP ->
P_285 * _rtDW -> DiscreteStateSpace_DSTATE_n ; xnew [ 0 ] += _rtP -> P_286 *
_rtB -> B_136_358_2864 ; ( void ) memcpy ( & _rtDW ->
DiscreteStateSpace_DSTATE_n , xnew , sizeof ( real_T ) * 1 ) ; } { real_T
xnew [ 1 ] ; xnew [ 0 ] = _rtP -> P_290 * _rtDW ->
DiscreteStateSpace_DSTATE_d ; xnew [ 0 ] += _rtP -> P_291 * _rtB ->
B_136_359_2872 ; ( void ) memcpy ( & _rtDW -> DiscreteStateSpace_DSTATE_d ,
xnew , sizeof ( real_T ) * 1 ) ; } { real_T xnew [ 1 ] ; xnew [ 0 ] = _rtP ->
P_295 * _rtDW -> DiscreteStateSpace_DSTATE_g ; xnew [ 0 ] += _rtP -> P_296 *
_rtB -> B_136_360_2880 ; ( void ) memcpy ( & _rtDW ->
DiscreteStateSpace_DSTATE_g , xnew , sizeof ( real_T ) * 1 ) ; } } switch (
_rtDW -> Integrator_MODE ) { case 3 : if ( _rtB -> B_136_376_3008 < 0.0 ) {
_rtDW -> Integrator_MODE = 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( S
) ; } break ; case 4 : if ( _rtB -> B_136_376_3008 > 0.0 ) { _rtDW ->
Integrator_MODE = 2 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; }
break ; } _rtXdis -> Integrator_CSTATE_o = ( ( _rtDW -> Integrator_MODE == 3
) || ( _rtDW -> Integrator_MODE == 4 ) ) ; i = ssIsSampleHit ( S , 2 , 0 ) ;
if ( i != 0 ) { _rtDW -> voltages_DSTATE [ 0 ] = _rtB -> B_136_214_1712 ;
_rtDW -> voltages_DSTATE [ 1 ] = _rtB -> B_136_215_1720 ; _rtDW ->
voltages_DSTATE [ 2 ] = _rtB -> B_136_378_3024 ; _rtDW -> voltages_DSTATE [ 3
] = _rtB -> B_136_994_7952 [ 0 ] ; _rtDW -> voltages_DSTATE [ 4 ] = _rtB ->
B_136_994_7952 [ 1 ] ; _rtDW -> Rotorspeeddeviationdw_SYSTEM_ENABLE = 0U ;
_rtDW -> Rotorspeeddeviationdw_DSTATE = _rtP -> P_337 * _rtB ->
B_136_420_3360 + _rtB -> B_136_421_3368 ; _rtDW -> theta_DSTATE += _rtP ->
P_339 * _rtB -> B_136_423_3384 ; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i
!= 0 ) { _rtDW -> Memory_PreviousInput_c = _rtB -> B_136_458_3664 ; } _rtDW
-> Integrator_IWORK = 0 ; switch ( _rtDW -> Integrator_MODE_f ) { case 3 : if
( _rtB -> B_136_443_3544 < 0.0 ) { _rtDW -> Integrator_MODE_f = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_443_3544 > 0.0 ) { _rtDW -> Integrator_MODE_f = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_j = ( ( _rtDW -> Integrator_MODE_f == 3 ) || ( _rtDW ->
Integrator_MODE_f == 4 ) ) ;
dVOC_monitor_network1_AutomaticGainControl_Update ( S , & _rtB ->
AutomaticGainControl_g , & _rtDW -> AutomaticGainControl_g , & _rtP ->
AutomaticGainControl_g , & ( ( X_dVOC_monitor_network1_T * ) ssGetContStates
( S ) ) -> AutomaticGainControl_g ) ; switch ( _rtDW -> Integrator_MODE_j ) {
case 3 : if ( _rtB -> B_136_439_3512 < 0.0 ) { _rtDW -> Integrator_MODE_j = 1
; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_439_3512 > 0.0 ) { _rtDW -> Integrator_MODE_j = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_i4 = ( ( _rtDW -> Integrator_MODE_j == 3 ) || ( _rtDW ->
Integrator_MODE_j == 4 ) ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT (
S ) ; _rtDW -> VariableTransportDelay_IWORK . Head = ( ( _rtDW ->
VariableTransportDelay_IWORK . Head < ( _rtDW -> VariableTransportDelay_IWORK
. CircularBufSize - 1 ) ) ? ( _rtDW -> VariableTransportDelay_IWORK . Head +
1 ) : 0 ) ; if ( _rtDW -> VariableTransportDelay_IWORK . Head == _rtDW ->
VariableTransportDelay_IWORK . Tail ) { if ( !
dVOC_monitor_network1_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
VariableTransportDelay_IWORK . CircularBufSize , & _rtDW ->
VariableTransportDelay_IWORK . Tail , & _rtDW -> VariableTransportDelay_IWORK
. Head , & _rtDW -> VariableTransportDelay_IWORK . Last , simTime - _rtP ->
P_357 , uBuffer , ( boolean_T ) 0 , ( boolean_T ) 1 , & _rtDW ->
VariableTransportDelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"vtdelay memory allocation error" ) ; return ; } } ( * uBuffer + _rtDW ->
VariableTransportDelay_IWORK . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK . Head ] = simTime ; ( * uBuffer + 2 * _rtDW ->
VariableTransportDelay_IWORK . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK . Head ] = ( ( X_dVOC_monitor_network1_T * )
ssGetContStates ( S ) ) -> VariableTransportDelay_CSTATE ; ( * uBuffer ) [
_rtDW -> VariableTransportDelay_IWORK . Head ] = _rtB -> B_136_434_3472 ; }
_rtDW -> PrevY = _rtB -> B_136_445_3560 ; _rtDW -> LastMajorTime =
ssGetTaskTime ( S , 0 ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) {
_rtDW -> Memory_PreviousInput_ap = _rtB -> B_136_503_4024 ; } _rtDW ->
Integrator_IWORK_l = 0 ; switch ( _rtDW -> Integrator_MODE_k ) { case 3 : if
( _rtB -> B_136_488_3904 < 0.0 ) { _rtDW -> Integrator_MODE_k = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_488_3904 > 0.0 ) { _rtDW -> Integrator_MODE_k = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_h = ( ( _rtDW -> Integrator_MODE_k == 3 ) || ( _rtDW ->
Integrator_MODE_k == 4 ) ) ;
dVOC_monitor_network1_AutomaticGainControl_Update ( S , & _rtB ->
AutomaticGainControl_k , & _rtDW -> AutomaticGainControl_k , & _rtP ->
AutomaticGainControl_k , & ( ( X_dVOC_monitor_network1_T * ) ssGetContStates
( S ) ) -> AutomaticGainControl_k ) ; switch ( _rtDW -> Integrator_MODE_e ) {
case 3 : if ( _rtB -> B_136_484_3872 < 0.0 ) { _rtDW -> Integrator_MODE_e = 1
; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_484_3872 > 0.0 ) { _rtDW -> Integrator_MODE_e = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_nh = ( ( _rtDW -> Integrator_MODE_e == 3 ) || ( _rtDW ->
Integrator_MODE_e == 4 ) ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_l . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; _rtDW -> VariableTransportDelay_IWORK_b . Head = ( ( _rtDW ->
VariableTransportDelay_IWORK_b . Head < ( _rtDW ->
VariableTransportDelay_IWORK_b . CircularBufSize - 1 ) ) ? ( _rtDW ->
VariableTransportDelay_IWORK_b . Head + 1 ) : 0 ) ; if ( _rtDW ->
VariableTransportDelay_IWORK_b . Head == _rtDW ->
VariableTransportDelay_IWORK_b . Tail ) { if ( !
dVOC_monitor_network1_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
VariableTransportDelay_IWORK_b . CircularBufSize , & _rtDW ->
VariableTransportDelay_IWORK_b . Tail , & _rtDW ->
VariableTransportDelay_IWORK_b . Head , & _rtDW ->
VariableTransportDelay_IWORK_b . Last , simTime - _rtP -> P_400 , uBuffer , (
boolean_T ) 0 , ( boolean_T ) 1 , & _rtDW -> VariableTransportDelay_IWORK_b .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "vtdelay memory allocation error"
) ; return ; } } ( * uBuffer + _rtDW -> VariableTransportDelay_IWORK_b .
CircularBufSize ) [ _rtDW -> VariableTransportDelay_IWORK_b . Head ] =
simTime ; ( * uBuffer + 2 * _rtDW -> VariableTransportDelay_IWORK_b .
CircularBufSize ) [ _rtDW -> VariableTransportDelay_IWORK_b . Head ] = ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_f ; ( * uBuffer ) [ _rtDW ->
VariableTransportDelay_IWORK_b . Head ] = _rtB -> B_136_479_3832 ; } _rtDW ->
PrevY_b = _rtB -> B_136_490_3920 ; _rtDW -> LastMajorTime_n = ssGetTaskTime (
S , 0 ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtDW ->
Memory_PreviousInput_j = _rtB -> B_136_548_4384 ; } _rtDW ->
Integrator_IWORK_f = 0 ; switch ( _rtDW -> Integrator_MODE_h ) { case 3 : if
( _rtB -> B_136_533_4264 < 0.0 ) { _rtDW -> Integrator_MODE_h = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_533_4264 > 0.0 ) { _rtDW -> Integrator_MODE_h = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_a = ( ( _rtDW -> Integrator_MODE_h == 3 ) || ( _rtDW ->
Integrator_MODE_h == 4 ) ) ;
dVOC_monitor_network1_AutomaticGainControl_Update ( S , & _rtB ->
AutomaticGainControl_c , & _rtDW -> AutomaticGainControl_c , & _rtP ->
AutomaticGainControl_c , & ( ( X_dVOC_monitor_network1_T * ) ssGetContStates
( S ) ) -> AutomaticGainControl_c ) ; switch ( _rtDW -> Integrator_MODE_n ) {
case 3 : if ( _rtB -> B_136_529_4232 < 0.0 ) { _rtDW -> Integrator_MODE_n = 1
; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_529_4232 > 0.0 ) { _rtDW -> Integrator_MODE_n = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_m = ( ( _rtDW -> Integrator_MODE_n == 3 ) || ( _rtDW ->
Integrator_MODE_n == 4 ) ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_m . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; _rtDW -> VariableTransportDelay_IWORK_k . Head = ( ( _rtDW ->
VariableTransportDelay_IWORK_k . Head < ( _rtDW ->
VariableTransportDelay_IWORK_k . CircularBufSize - 1 ) ) ? ( _rtDW ->
VariableTransportDelay_IWORK_k . Head + 1 ) : 0 ) ; if ( _rtDW ->
VariableTransportDelay_IWORK_k . Head == _rtDW ->
VariableTransportDelay_IWORK_k . Tail ) { if ( !
dVOC_monitor_network1_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
VariableTransportDelay_IWORK_k . CircularBufSize , & _rtDW ->
VariableTransportDelay_IWORK_k . Tail , & _rtDW ->
VariableTransportDelay_IWORK_k . Head , & _rtDW ->
VariableTransportDelay_IWORK_k . Last , simTime - _rtP -> P_443 , uBuffer , (
boolean_T ) 0 , ( boolean_T ) 1 , & _rtDW -> VariableTransportDelay_IWORK_k .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "vtdelay memory allocation error"
) ; return ; } } ( * uBuffer + _rtDW -> VariableTransportDelay_IWORK_k .
CircularBufSize ) [ _rtDW -> VariableTransportDelay_IWORK_k . Head ] =
simTime ; ( * uBuffer + 2 * _rtDW -> VariableTransportDelay_IWORK_k .
CircularBufSize ) [ _rtDW -> VariableTransportDelay_IWORK_k . Head ] = ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_j ; ( * uBuffer ) [ _rtDW ->
VariableTransportDelay_IWORK_k . Head ] = _rtB -> B_136_524_4192 ; } _rtDW ->
PrevY_n = _rtB -> B_136_535_4280 ; _rtDW -> LastMajorTime_d = ssGetTaskTime (
S , 0 ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtDW ->
Memory_PreviousInput_m = _rtB -> B_136_593_4744 ; } _rtDW ->
Integrator_IWORK_k = 0 ; switch ( _rtDW -> Integrator_MODE_k4 ) { case 3 : if
( _rtB -> B_136_578_4624 < 0.0 ) { _rtDW -> Integrator_MODE_k4 = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_578_4624 > 0.0 ) { _rtDW -> Integrator_MODE_k4 = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_c = ( ( _rtDW -> Integrator_MODE_k4 == 3 ) || ( _rtDW ->
Integrator_MODE_k4 == 4 ) ) ;
dVOC_monitor_network1_AutomaticGainControl_Update ( S , & _rtB ->
AutomaticGainControl_b , & _rtDW -> AutomaticGainControl_b , & _rtP ->
AutomaticGainControl_b , & ( ( X_dVOC_monitor_network1_T * ) ssGetContStates
( S ) ) -> AutomaticGainControl_b ) ; switch ( _rtDW -> Integrator_MODE_k5 )
{ case 3 : if ( _rtB -> B_136_574_4592 < 0.0 ) { _rtDW -> Integrator_MODE_k5
= 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 :
if ( _rtB -> B_136_574_4592 > 0.0 ) { _rtDW -> Integrator_MODE_k5 = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_f = ( ( _rtDW -> Integrator_MODE_k5 == 3 ) || ( _rtDW ->
Integrator_MODE_k5 == 4 ) ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> VariableTransportDelay_PWORK_p . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> VariableTransportDelay_IWORK_ka . Head = ( ( _rtDW ->
VariableTransportDelay_IWORK_ka . Head < ( _rtDW ->
VariableTransportDelay_IWORK_ka . CircularBufSize - 1 ) ) ? ( _rtDW ->
VariableTransportDelay_IWORK_ka . Head + 1 ) : 0 ) ; if ( _rtDW ->
VariableTransportDelay_IWORK_ka . Head == _rtDW ->
VariableTransportDelay_IWORK_ka . Tail ) { if ( !
dVOC_monitor_network1_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
VariableTransportDelay_IWORK_ka . CircularBufSize , & _rtDW ->
VariableTransportDelay_IWORK_ka . Tail , & _rtDW ->
VariableTransportDelay_IWORK_ka . Head , & _rtDW ->
VariableTransportDelay_IWORK_ka . Last , simTime - _rtP -> P_486 , uBuffer ,
( boolean_T ) 0 , ( boolean_T ) 1 , & _rtDW ->
VariableTransportDelay_IWORK_ka . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"vtdelay memory allocation error" ) ; return ; } } ( * uBuffer + _rtDW ->
VariableTransportDelay_IWORK_ka . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK_ka . Head ] = simTime ; ( * uBuffer + 2 * _rtDW
-> VariableTransportDelay_IWORK_ka . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK_ka . Head ] = ( ( X_dVOC_monitor_network1_T * )
ssGetContStates ( S ) ) -> VariableTransportDelay_CSTATE_g ; ( * uBuffer ) [
_rtDW -> VariableTransportDelay_IWORK_ka . Head ] = _rtB -> B_136_569_4552 ;
} _rtDW -> PrevY_e = _rtB -> B_136_580_4640 ; _rtDW -> LastMajorTime_k =
ssGetTaskTime ( S , 0 ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) {
_rtDW -> Memory_PreviousInput_g = _rtB -> B_136_638_5104 ; } _rtDW ->
Integrator_IWORK_b = 0 ; switch ( _rtDW -> Integrator_MODE_d ) { case 3 : if
( _rtB -> B_136_623_4984 < 0.0 ) { _rtDW -> Integrator_MODE_d = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_623_4984 > 0.0 ) { _rtDW -> Integrator_MODE_d = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_c0 = ( ( _rtDW -> Integrator_MODE_d == 3 ) || ( _rtDW ->
Integrator_MODE_d == 4 ) ) ;
dVOC_monitor_network1_AutomaticGainControl_Update ( S , & _rtB ->
AutomaticGainControl_l , & _rtDW -> AutomaticGainControl_l , & _rtP ->
AutomaticGainControl_l , & ( ( X_dVOC_monitor_network1_T * ) ssGetContStates
( S ) ) -> AutomaticGainControl_l ) ; switch ( _rtDW -> Integrator_MODE_i ) {
case 3 : if ( _rtB -> B_136_619_4952 < 0.0 ) { _rtDW -> Integrator_MODE_i = 1
; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_619_4952 > 0.0 ) { _rtDW -> Integrator_MODE_i = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_b = ( ( _rtDW -> Integrator_MODE_i == 3 ) || ( _rtDW ->
Integrator_MODE_i == 4 ) ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_f . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; _rtDW -> VariableTransportDelay_IWORK_i . Head = ( ( _rtDW ->
VariableTransportDelay_IWORK_i . Head < ( _rtDW ->
VariableTransportDelay_IWORK_i . CircularBufSize - 1 ) ) ? ( _rtDW ->
VariableTransportDelay_IWORK_i . Head + 1 ) : 0 ) ; if ( _rtDW ->
VariableTransportDelay_IWORK_i . Head == _rtDW ->
VariableTransportDelay_IWORK_i . Tail ) { if ( !
dVOC_monitor_network1_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
VariableTransportDelay_IWORK_i . CircularBufSize , & _rtDW ->
VariableTransportDelay_IWORK_i . Tail , & _rtDW ->
VariableTransportDelay_IWORK_i . Head , & _rtDW ->
VariableTransportDelay_IWORK_i . Last , simTime - _rtP -> P_529 , uBuffer , (
boolean_T ) 0 , ( boolean_T ) 1 , & _rtDW -> VariableTransportDelay_IWORK_i .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "vtdelay memory allocation error"
) ; return ; } } ( * uBuffer + _rtDW -> VariableTransportDelay_IWORK_i .
CircularBufSize ) [ _rtDW -> VariableTransportDelay_IWORK_i . Head ] =
simTime ; ( * uBuffer + 2 * _rtDW -> VariableTransportDelay_IWORK_i .
CircularBufSize ) [ _rtDW -> VariableTransportDelay_IWORK_i . Head ] = ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_o ; ( * uBuffer ) [ _rtDW ->
VariableTransportDelay_IWORK_i . Head ] = _rtB -> B_136_614_4912 ; } _rtDW ->
PrevY_nq = _rtB -> B_136_625_5000 ; _rtDW -> LastMajorTime_e = ssGetTaskTime
( S , 0 ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtDW ->
Memory_PreviousInput_n = _rtB -> B_136_683_5464 ; } _rtDW ->
Integrator_IWORK_c = 0 ; switch ( _rtDW -> Integrator_MODE_g ) { case 3 : if
( _rtB -> B_136_668_5344 < 0.0 ) { _rtDW -> Integrator_MODE_g = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_668_5344 > 0.0 ) { _rtDW -> Integrator_MODE_g = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_pq = ( ( _rtDW -> Integrator_MODE_g == 3 ) || ( _rtDW ->
Integrator_MODE_g == 4 ) ) ;
dVOC_monitor_network1_AutomaticGainControl_Update ( S , & _rtB ->
AutomaticGainControl_a , & _rtDW -> AutomaticGainControl_a , & _rtP ->
AutomaticGainControl_a , & ( ( X_dVOC_monitor_network1_T * ) ssGetContStates
( S ) ) -> AutomaticGainControl_a ) ; switch ( _rtDW -> Integrator_MODE_p ) {
case 3 : if ( _rtB -> B_136_664_5312 < 0.0 ) { _rtDW -> Integrator_MODE_p = 1
; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_664_5312 > 0.0 ) { _rtDW -> Integrator_MODE_p = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_jf = ( ( _rtDW -> Integrator_MODE_p == 3 ) || ( _rtDW ->
Integrator_MODE_p == 4 ) ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
VariableTransportDelay_PWORK_o . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; _rtDW -> VariableTransportDelay_IWORK_kh . Head = ( ( _rtDW ->
VariableTransportDelay_IWORK_kh . Head < ( _rtDW ->
VariableTransportDelay_IWORK_kh . CircularBufSize - 1 ) ) ? ( _rtDW ->
VariableTransportDelay_IWORK_kh . Head + 1 ) : 0 ) ; if ( _rtDW ->
VariableTransportDelay_IWORK_kh . Head == _rtDW ->
VariableTransportDelay_IWORK_kh . Tail ) { if ( !
dVOC_monitor_network1_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
VariableTransportDelay_IWORK_kh . CircularBufSize , & _rtDW ->
VariableTransportDelay_IWORK_kh . Tail , & _rtDW ->
VariableTransportDelay_IWORK_kh . Head , & _rtDW ->
VariableTransportDelay_IWORK_kh . Last , simTime - _rtP -> P_573 , uBuffer ,
( boolean_T ) 0 , ( boolean_T ) 1 , & _rtDW ->
VariableTransportDelay_IWORK_kh . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"vtdelay memory allocation error" ) ; return ; } } ( * uBuffer + _rtDW ->
VariableTransportDelay_IWORK_kh . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK_kh . Head ] = simTime ; ( * uBuffer + 2 * _rtDW
-> VariableTransportDelay_IWORK_kh . CircularBufSize ) [ _rtDW ->
VariableTransportDelay_IWORK_kh . Head ] = ( ( X_dVOC_monitor_network1_T * )
ssGetContStates ( S ) ) -> VariableTransportDelay_CSTATE_l ; ( * uBuffer ) [
_rtDW -> VariableTransportDelay_IWORK_kh . Head ] = _rtB -> B_136_659_5272 ;
} _rtDW -> PrevY_o = _rtB -> B_136_670_5360 ; _rtDW -> LastMajorTime_du =
ssGetTaskTime ( S , 0 ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) {
_rtDW -> Memory_PreviousInput_c4 = _rtB -> B_136_728_5824 ; } _rtDW ->
Integrator_IWORK_bu = 0 ; switch ( _rtDW -> Integrator_MODE_m ) { case 3 : if
( _rtB -> B_136_713_5704 < 0.0 ) { _rtDW -> Integrator_MODE_m = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_713_5704 > 0.0 ) { _rtDW -> Integrator_MODE_m = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_oo = ( ( _rtDW -> Integrator_MODE_m == 3 ) || ( _rtDW ->
Integrator_MODE_m == 4 ) ) ;
dVOC_monitor_network1_AutomaticGainControl_Update ( S , & _rtB ->
AutomaticGainControl , & _rtDW -> AutomaticGainControl , & _rtP ->
AutomaticGainControl , & ( ( X_dVOC_monitor_network1_T * ) ssGetContStates (
S ) ) -> AutomaticGainControl ) ; switch ( _rtDW -> Integrator_MODE_es ) {
case 3 : if ( _rtB -> B_136_709_5672 < 0.0 ) { _rtDW -> Integrator_MODE_es =
1 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if
( _rtB -> B_136_709_5672 > 0.0 ) { _rtDW -> Integrator_MODE_es = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_pf = ( ( _rtDW -> Integrator_MODE_es == 3 ) || ( _rtDW ->
Integrator_MODE_es == 4 ) ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> VariableTransportDelay_PWORK_e . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> VariableTransportDelay_IWORK_a . Head = ( ( _rtDW ->
VariableTransportDelay_IWORK_a . Head < ( _rtDW ->
VariableTransportDelay_IWORK_a . CircularBufSize - 1 ) ) ? ( _rtDW ->
VariableTransportDelay_IWORK_a . Head + 1 ) : 0 ) ; if ( _rtDW ->
VariableTransportDelay_IWORK_a . Head == _rtDW ->
VariableTransportDelay_IWORK_a . Tail ) { if ( !
dVOC_monitor_network1_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
VariableTransportDelay_IWORK_a . CircularBufSize , & _rtDW ->
VariableTransportDelay_IWORK_a . Tail , & _rtDW ->
VariableTransportDelay_IWORK_a . Head , & _rtDW ->
VariableTransportDelay_IWORK_a . Last , simTime - _rtP -> P_616 , uBuffer , (
boolean_T ) 0 , ( boolean_T ) 1 , & _rtDW -> VariableTransportDelay_IWORK_a .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "vtdelay memory allocation error"
) ; return ; } } ( * uBuffer + _rtDW -> VariableTransportDelay_IWORK_a .
CircularBufSize ) [ _rtDW -> VariableTransportDelay_IWORK_a . Head ] =
simTime ; ( * uBuffer + 2 * _rtDW -> VariableTransportDelay_IWORK_a .
CircularBufSize ) [ _rtDW -> VariableTransportDelay_IWORK_a . Head ] = ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_d ; ( * uBuffer ) [ _rtDW ->
VariableTransportDelay_IWORK_a . Head ] = _rtB -> B_136_704_5632 ; } _rtDW ->
PrevY_nc = _rtB -> B_136_715_5720 ; _rtDW -> LastMajorTime_o = ssGetTaskTime
( S , 0 ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtDW ->
Memory_PreviousInput_gc = _rtB -> B_136_773_6184 ; } _rtDW ->
Integrator_IWORK_d = 0 ; switch ( _rtDW -> Integrator_MODE_dx ) { case 3 : if
( _rtB -> B_136_758_6064 < 0.0 ) { _rtDW -> Integrator_MODE_dx = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_758_6064 > 0.0 ) { _rtDW -> Integrator_MODE_dx = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_d = ( ( _rtDW -> Integrator_MODE_dx == 3 ) || ( _rtDW ->
Integrator_MODE_dx == 4 ) ) ;
dVOC_monitor_network1_AutomaticGainControl_Update ( S , & _rtB ->
AutomaticGainControl_m , & _rtDW -> AutomaticGainControl_m , & _rtP ->
AutomaticGainControl_m , & ( ( X_dVOC_monitor_network1_T * ) ssGetContStates
( S ) ) -> AutomaticGainControl_m ) ; switch ( _rtDW -> Integrator_MODE_il )
{ case 3 : if ( _rtB -> B_136_754_6032 < 0.0 ) { _rtDW -> Integrator_MODE_il
= 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 :
if ( _rtB -> B_136_754_6032 > 0.0 ) { _rtDW -> Integrator_MODE_il = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_jn = ( ( _rtDW -> Integrator_MODE_il == 3 ) || ( _rtDW ->
Integrator_MODE_il == 4 ) ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> VariableTransportDelay_PWORK_lv . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> VariableTransportDelay_IWORK_l . Head = ( ( _rtDW ->
VariableTransportDelay_IWORK_l . Head < ( _rtDW ->
VariableTransportDelay_IWORK_l . CircularBufSize - 1 ) ) ? ( _rtDW ->
VariableTransportDelay_IWORK_l . Head + 1 ) : 0 ) ; if ( _rtDW ->
VariableTransportDelay_IWORK_l . Head == _rtDW ->
VariableTransportDelay_IWORK_l . Tail ) { if ( !
dVOC_monitor_network1_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
VariableTransportDelay_IWORK_l . CircularBufSize , & _rtDW ->
VariableTransportDelay_IWORK_l . Tail , & _rtDW ->
VariableTransportDelay_IWORK_l . Head , & _rtDW ->
VariableTransportDelay_IWORK_l . Last , simTime - _rtP -> P_659 , uBuffer , (
boolean_T ) 0 , ( boolean_T ) 1 , & _rtDW -> VariableTransportDelay_IWORK_l .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "vtdelay memory allocation error"
) ; return ; } } ( * uBuffer + _rtDW -> VariableTransportDelay_IWORK_l .
CircularBufSize ) [ _rtDW -> VariableTransportDelay_IWORK_l . Head ] =
simTime ; ( * uBuffer + 2 * _rtDW -> VariableTransportDelay_IWORK_l .
CircularBufSize ) [ _rtDW -> VariableTransportDelay_IWORK_l . Head ] = ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_jz ; ( * uBuffer ) [ _rtDW ->
VariableTransportDelay_IWORK_l . Head ] = _rtB -> B_136_749_5992 ; } _rtDW ->
PrevY_l = _rtB -> B_136_760_6080 ; _rtDW -> LastMajorTime_kb = ssGetTaskTime
( S , 0 ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtDW ->
Memory_PreviousInput_cp = _rtB -> B_136_818_6544 ; } _rtDW ->
Integrator_IWORK_m = 0 ; switch ( _rtDW -> Integrator_MODE_mo ) { case 3 : if
( _rtB -> B_136_803_6424 < 0.0 ) { _rtDW -> Integrator_MODE_mo = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_136_803_6424 > 0.0 ) { _rtDW -> Integrator_MODE_mo = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_nj = ( ( _rtDW -> Integrator_MODE_mo == 3 ) || ( _rtDW ->
Integrator_MODE_mo == 4 ) ) ;
dVOC_monitor_network1_AutomaticGainControl_Update ( S , & _rtB ->
AutomaticGainControl_b2 , & _rtDW -> AutomaticGainControl_b2 , & _rtP ->
AutomaticGainControl_b2 , & ( ( X_dVOC_monitor_network1_T * ) ssGetContStates
( S ) ) -> AutomaticGainControl_b2 ) ; switch ( _rtDW -> Integrator_MODE_h5 )
{ case 3 : if ( _rtB -> B_136_799_6392 < 0.0 ) { _rtDW -> Integrator_MODE_h5
= 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 :
if ( _rtB -> B_136_799_6392 > 0.0 ) { _rtDW -> Integrator_MODE_h5 = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE_fu = ( ( _rtDW -> Integrator_MODE_h5 == 3 ) || ( _rtDW ->
Integrator_MODE_h5 == 4 ) ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> VariableTransportDelay_PWORK_g . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> VariableTransportDelay_IWORK_p . Head = ( ( _rtDW ->
VariableTransportDelay_IWORK_p . Head < ( _rtDW ->
VariableTransportDelay_IWORK_p . CircularBufSize - 1 ) ) ? ( _rtDW ->
VariableTransportDelay_IWORK_p . Head + 1 ) : 0 ) ; if ( _rtDW ->
VariableTransportDelay_IWORK_p . Head == _rtDW ->
VariableTransportDelay_IWORK_p . Tail ) { if ( !
dVOC_monitor_network1_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
VariableTransportDelay_IWORK_p . CircularBufSize , & _rtDW ->
VariableTransportDelay_IWORK_p . Tail , & _rtDW ->
VariableTransportDelay_IWORK_p . Head , & _rtDW ->
VariableTransportDelay_IWORK_p . Last , simTime - _rtP -> P_702 , uBuffer , (
boolean_T ) 0 , ( boolean_T ) 1 , & _rtDW -> VariableTransportDelay_IWORK_p .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "vtdelay memory allocation error"
) ; return ; } } ( * uBuffer + _rtDW -> VariableTransportDelay_IWORK_p .
CircularBufSize ) [ _rtDW -> VariableTransportDelay_IWORK_p . Head ] =
simTime ; ( * uBuffer + 2 * _rtDW -> VariableTransportDelay_IWORK_p .
CircularBufSize ) [ _rtDW -> VariableTransportDelay_IWORK_p . Head ] = ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ->
VariableTransportDelay_CSTATE_b ; ( * uBuffer ) [ _rtDW ->
VariableTransportDelay_IWORK_p . Head ] = _rtB -> B_136_794_6352 ; } _rtDW ->
PrevY_ow = _rtB -> B_136_805_6440 ; _rtDW -> LastMajorTime_i = ssGetTaskTime
( S , 0 ) ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID4 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_dVOC_monitor_network1_T *
_rtB ; DW_dVOC_monitor_network1_T * _rtDW ; P_dVOC_monitor_network1_T * _rtP
; XDis_dVOC_monitor_network1_T * _rtXdis ; XDot_dVOC_monitor_network1_T *
_rtXdot ; X_dVOC_monitor_network1_T * _rtX ; uint32_T ri ; _rtDW = ( (
DW_dVOC_monitor_network1_T * ) ssGetRootDWork ( S ) ) ; _rtXdis = ( (
XDis_dVOC_monitor_network1_T * ) ssGetContStateDisabled ( S ) ) ; _rtXdot = (
( XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ; _rtX = ( (
X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_dVOC_monitor_network1_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
Integrator_CSTATE = _rtB -> B_136_295_2360 ; _rtXdot -> Integrator_CSTATE_i =
_rtB -> B_136_303_2424 ; _rtXdot -> Integrator1_CSTATE = _rtB ->
B_136_321_2568 ; _rtXdot -> Integrator3_CSTATE = _rtB -> B_136_26_208 ;
_rtXdot -> TransferFcn4_CSTATE = 0.0 ; _rtXdot -> TransferFcn4_CSTATE += _rtP
-> P_86 * _rtX -> TransferFcn4_CSTATE ; _rtXdot -> TransferFcn4_CSTATE +=
_rtB -> B_136_248_1984 ; _rtXdot -> Integrator1_CSTATE_m = _rtB ->
B_136_296_2368 ; _rtXdot -> Integrator1_CSTATE_f = _rtB -> B_136_304_2432 ;
_rtXdot -> Integrator_CSTATE_n = _rtB -> B_136_330_2640 ; _rtXdot ->
Integrator_CSTATE_p = _rtB -> B_136_338_2704 ; _rtXdot ->
Integrator1_CSTATE_i = _rtB -> B_136_356_2848 ; _rtXdot ->
Integrator3_CSTATE_o = _rtB -> B_136_77_616 ; _rtXdot ->
TransferFcn4_CSTATE_m = 0.0 ; _rtXdot -> TransferFcn4_CSTATE_m += _rtP ->
P_123 * _rtX -> TransferFcn4_CSTATE_m ; _rtXdot -> TransferFcn4_CSTATE_m +=
_rtB -> B_136_264_2112 ; _rtXdot -> Integrator1_CSTATE_g = _rtB ->
B_136_331_2648 ; _rtXdot -> Integrator1_CSTATE_b = _rtB -> B_136_339_2712 ;
_rtXdot -> Internal_CSTATE = 0.0 ; for ( ri = _rtP -> P_958 [ 0U ] ; ri <
_rtP -> P_958 [ 1U ] ; ri ++ ) { _rtXdot -> Internal_CSTATE += _rtP -> P_151
* _rtX -> Internal_CSTATE ; } for ( ri = _rtP -> P_960 [ 0U ] ; ri < _rtP ->
P_960 [ 1U ] ; ri ++ ) { _rtXdot -> Internal_CSTATE += _rtP -> P_152 * _rtB
-> B_136_294_2352 ; } _rtXdot -> Internal_CSTATE_n = 0.0 ; for ( ri = _rtP ->
P_964 [ 0U ] ; ri < _rtP -> P_964 [ 1U ] ; ri ++ ) { _rtXdot ->
Internal_CSTATE_n += _rtP -> P_158 * _rtX -> Internal_CSTATE_n ; } for ( ri =
_rtP -> P_966 [ 0U ] ; ri < _rtP -> P_966 [ 1U ] ; ri ++ ) { _rtXdot ->
Internal_CSTATE_n += _rtP -> P_159 * _rtB -> B_136_329_2632 ; } _rtXdot ->
TransferFcn2_CSTATE = 0.0 ; _rtXdot -> TransferFcn2_CSTATE += _rtP -> P_222 *
_rtX -> TransferFcn2_CSTATE ; _rtXdot -> TransferFcn2_CSTATE += _rtB ->
B_136_289_2312 ; _rtXdot -> TransferFcn4_CSTATE_l = 0.0 ; _rtXdot ->
TransferFcn4_CSTATE_l += _rtP -> P_242 * _rtX -> TransferFcn4_CSTATE_l ;
_rtXdot -> TransferFcn4_CSTATE_l += _rtB -> B_136_272_2176 ; _rtXdot ->
TransferFcn2_CSTATE_a = 0.0 ; _rtXdot -> TransferFcn2_CSTATE_a += _rtP ->
P_251 * _rtX -> TransferFcn2_CSTATE_a ; _rtXdot -> TransferFcn2_CSTATE_a +=
_rtB -> B_136_324_2592 ; _rtXdot -> TransferFcn4_CSTATE_n = 0.0 ; _rtXdot ->
TransferFcn4_CSTATE_n += _rtP -> P_272 * _rtX -> TransferFcn4_CSTATE_n ;
_rtXdot -> TransferFcn4_CSTATE_n += _rtB -> B_136_277_2216 ; _rtXdot ->
Internal_CSTATE_p = 0.0 ; for ( ri = _rtP -> P_970 [ 0U ] ; ri < _rtP ->
P_970 [ 1U ] ; ri ++ ) { _rtXdot -> Internal_CSTATE_p += _rtP -> P_275 * _rtX
-> Internal_CSTATE_p ; } for ( ri = _rtP -> P_972 [ 0U ] ; ri < _rtP -> P_972
[ 1U ] ; ri ++ ) { _rtXdot -> Internal_CSTATE_p += _rtP -> P_276 * _rtB ->
B_136_377_3016 ; } if ( _rtXdis -> Integrator_CSTATE_o ) { _rtXdot ->
Integrator_CSTATE_o = 0.0 ; } else { _rtXdot -> Integrator_CSTATE_o = _rtB ->
B_136_376_3008 ; } _rtXdot -> StateSpace_CSTATE = 0.0 ; for ( ri = _rtP ->
P_976 [ 0U ] ; ri < _rtP -> P_976 [ 1U ] ; ri ++ ) { _rtXdot ->
StateSpace_CSTATE += _rtP -> P_308 * _rtX -> StateSpace_CSTATE ; } for ( ri =
_rtP -> P_978 [ 0U ] ; ri < _rtP -> P_978 [ 1U ] ; ri ++ ) { _rtXdot ->
StateSpace_CSTATE += _rtP -> P_309 * _rtB -> B_136_365_2920 ; } _rtXdot ->
StateSpace_CSTATE_n = 0.0 ; for ( ri = _rtP -> P_984 [ 0U ] ; ri < _rtP ->
P_984 [ 1U ] ; ri ++ ) { _rtXdot -> StateSpace_CSTATE_n += _rtP -> P_313 *
_rtX -> StateSpace_CSTATE_n ; } for ( ri = _rtP -> P_986 [ 0U ] ; ri < _rtP
-> P_986 [ 1U ] ; ri ++ ) { _rtXdot -> StateSpace_CSTATE_n += _rtP -> P_314 *
_rtB -> B_136_362_2896 ; } if ( _rtXdis -> Integrator_CSTATE_j ) { _rtXdot ->
Integrator_CSTATE_j = 0.0 ; } else { _rtXdot -> Integrator_CSTATE_j = _rtB ->
B_136_443_3544 ; } dVOC_monitor_network1_AutomaticGainControl_Deriv ( S , &
_rtB -> AutomaticGainControl_g , & _rtDW -> AutomaticGainControl_g , & _rtP
-> AutomaticGainControl_g , & _rtXdot -> AutomaticGainControl_g ) ; if (
_rtXdis -> Integrator_CSTATE_i4 ) { _rtXdot -> Integrator_CSTATE_i4 = 0.0 ; }
else { _rtXdot -> Integrator_CSTATE_i4 = _rtB -> B_136_439_3512 ; } { real_T
instantDelay ; instantDelay = _rtB -> B_136_460_3680 ; if ( instantDelay >
_rtP -> P_357 ) { instantDelay = _rtP -> P_357 ; } if ( instantDelay < 0.0 )
{ ( ( XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE = 0 ; } else { ( ( XDot_dVOC_monitor_network1_T
* ) ssGetdX ( S ) ) -> VariableTransportDelay_CSTATE = 1.0 / instantDelay ; }
} _rtXdot -> integrator_CSTATE = _rtB -> B_136_467_3736 [ 1 ] ; _rtXdot ->
TransferFcn_CSTATE = 0.0 ; _rtXdot -> TransferFcn_CSTATE += _rtP -> P_363 *
_rtX -> TransferFcn_CSTATE ; _rtXdot -> TransferFcn_CSTATE += _rtB ->
B_136_440_3520 ; _rtXdot -> Integrator_x1_CSTATE = _rtB -> B_136_455_3640 ;
_rtXdot -> Integrator_x2_CSTATE = _rtB -> B_136_457_3656 ; if ( _rtXdis ->
Integrator_CSTATE_h ) { _rtXdot -> Integrator_CSTATE_h = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_h = _rtB -> B_136_488_3904 ; }
dVOC_monitor_network1_AutomaticGainControl_Deriv ( S , & _rtB ->
AutomaticGainControl_k , & _rtDW -> AutomaticGainControl_k , & _rtP ->
AutomaticGainControl_k , & _rtXdot -> AutomaticGainControl_k ) ; if ( _rtXdis
-> Integrator_CSTATE_nh ) { _rtXdot -> Integrator_CSTATE_nh = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_nh = _rtB -> B_136_484_3872 ; } { real_T
instantDelay ; instantDelay = _rtB -> B_136_505_4040 ; if ( instantDelay >
_rtP -> P_400 ) { instantDelay = _rtP -> P_400 ; } if ( instantDelay < 0.0 )
{ ( ( XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_f = 0 ; } else { ( (
XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_f = 1.0 / instantDelay ; } } _rtXdot ->
integrator_CSTATE_g = _rtB -> B_136_512_4096 [ 1 ] ; _rtXdot ->
TransferFcn_CSTATE_l = 0.0 ; _rtXdot -> TransferFcn_CSTATE_l += _rtP -> P_406
* _rtX -> TransferFcn_CSTATE_l ; _rtXdot -> TransferFcn_CSTATE_l += _rtB ->
B_136_485_3880 ; _rtXdot -> Integrator_x1_CSTATE_j = _rtB -> B_136_500_4000 ;
_rtXdot -> Integrator_x2_CSTATE_m = _rtB -> B_136_502_4016 ; if ( _rtXdis ->
Integrator_CSTATE_a ) { _rtXdot -> Integrator_CSTATE_a = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_a = _rtB -> B_136_533_4264 ; }
dVOC_monitor_network1_AutomaticGainControl_Deriv ( S , & _rtB ->
AutomaticGainControl_c , & _rtDW -> AutomaticGainControl_c , & _rtP ->
AutomaticGainControl_c , & _rtXdot -> AutomaticGainControl_c ) ; if ( _rtXdis
-> Integrator_CSTATE_m ) { _rtXdot -> Integrator_CSTATE_m = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_m = _rtB -> B_136_529_4232 ; } { real_T
instantDelay ; instantDelay = _rtB -> B_136_550_4400 ; if ( instantDelay >
_rtP -> P_443 ) { instantDelay = _rtP -> P_443 ; } if ( instantDelay < 0.0 )
{ ( ( XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_j = 0 ; } else { ( (
XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_j = 1.0 / instantDelay ; } } _rtXdot ->
integrator_CSTATE_d = _rtB -> B_136_557_4456 [ 1 ] ; _rtXdot ->
TransferFcn_CSTATE_f = 0.0 ; _rtXdot -> TransferFcn_CSTATE_f += _rtP -> P_449
* _rtX -> TransferFcn_CSTATE_f ; _rtXdot -> TransferFcn_CSTATE_f += _rtB ->
B_136_530_4240 ; _rtXdot -> Integrator_x1_CSTATE_m = _rtB -> B_136_545_4360 ;
_rtXdot -> Integrator_x2_CSTATE_g = _rtB -> B_136_547_4376 ; if ( _rtXdis ->
Integrator_CSTATE_c ) { _rtXdot -> Integrator_CSTATE_c = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_c = _rtB -> B_136_578_4624 ; }
dVOC_monitor_network1_AutomaticGainControl_Deriv ( S , & _rtB ->
AutomaticGainControl_b , & _rtDW -> AutomaticGainControl_b , & _rtP ->
AutomaticGainControl_b , & _rtXdot -> AutomaticGainControl_b ) ; if ( _rtXdis
-> Integrator_CSTATE_f ) { _rtXdot -> Integrator_CSTATE_f = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_f = _rtB -> B_136_574_4592 ; } { real_T
instantDelay ; instantDelay = _rtB -> B_136_595_4760 ; if ( instantDelay >
_rtP -> P_486 ) { instantDelay = _rtP -> P_486 ; } if ( instantDelay < 0.0 )
{ ( ( XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_g = 0 ; } else { ( (
XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_g = 1.0 / instantDelay ; } } _rtXdot ->
integrator_CSTATE_m = _rtB -> B_136_602_4816 [ 1 ] ; _rtXdot ->
TransferFcn_CSTATE_a = 0.0 ; _rtXdot -> TransferFcn_CSTATE_a += _rtP -> P_492
* _rtX -> TransferFcn_CSTATE_a ; _rtXdot -> TransferFcn_CSTATE_a += _rtB ->
B_136_575_4600 ; _rtXdot -> Integrator_x1_CSTATE_f = _rtB -> B_136_590_4720 ;
_rtXdot -> Integrator_x2_CSTATE_o = _rtB -> B_136_592_4736 ; if ( _rtXdis ->
Integrator_CSTATE_c0 ) { _rtXdot -> Integrator_CSTATE_c0 = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_c0 = _rtB -> B_136_623_4984 ; }
dVOC_monitor_network1_AutomaticGainControl_Deriv ( S , & _rtB ->
AutomaticGainControl_l , & _rtDW -> AutomaticGainControl_l , & _rtP ->
AutomaticGainControl_l , & _rtXdot -> AutomaticGainControl_l ) ; if ( _rtXdis
-> Integrator_CSTATE_b ) { _rtXdot -> Integrator_CSTATE_b = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_b = _rtB -> B_136_619_4952 ; } { real_T
instantDelay ; instantDelay = _rtB -> B_136_640_5120 ; if ( instantDelay >
_rtP -> P_529 ) { instantDelay = _rtP -> P_529 ; } if ( instantDelay < 0.0 )
{ ( ( XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_o = 0 ; } else { ( (
XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_o = 1.0 / instantDelay ; } } _rtXdot ->
integrator_CSTATE_o = _rtB -> B_136_647_5176 [ 1 ] ; _rtXdot ->
TransferFcn_CSTATE_ac = 0.0 ; _rtXdot -> TransferFcn_CSTATE_ac += _rtP ->
P_535 * _rtX -> TransferFcn_CSTATE_ac ; _rtXdot -> TransferFcn_CSTATE_ac +=
_rtB -> B_136_620_4960 ; _rtXdot -> Integrator_x1_CSTATE_k = _rtB ->
B_136_635_5080 ; _rtXdot -> Integrator_x2_CSTATE_f = _rtB -> B_136_637_5096 ;
if ( _rtXdis -> Integrator_CSTATE_pq ) { _rtXdot -> Integrator_CSTATE_pq =
0.0 ; } else { _rtXdot -> Integrator_CSTATE_pq = _rtB -> B_136_668_5344 ; }
dVOC_monitor_network1_AutomaticGainControl_Deriv ( S , & _rtB ->
AutomaticGainControl_a , & _rtDW -> AutomaticGainControl_a , & _rtP ->
AutomaticGainControl_a , & _rtXdot -> AutomaticGainControl_a ) ; if ( _rtXdis
-> Integrator_CSTATE_jf ) { _rtXdot -> Integrator_CSTATE_jf = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_jf = _rtB -> B_136_664_5312 ; } { real_T
instantDelay ; instantDelay = _rtB -> B_136_685_5480 ; if ( instantDelay >
_rtP -> P_573 ) { instantDelay = _rtP -> P_573 ; } if ( instantDelay < 0.0 )
{ ( ( XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_l = 0 ; } else { ( (
XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_l = 1.0 / instantDelay ; } } _rtXdot ->
integrator_CSTATE_a = _rtB -> B_136_692_5536 [ 1 ] ; _rtXdot ->
TransferFcn_CSTATE_k = 0.0 ; _rtXdot -> TransferFcn_CSTATE_k += _rtP -> P_579
* _rtX -> TransferFcn_CSTATE_k ; _rtXdot -> TransferFcn_CSTATE_k += _rtB ->
B_136_665_5320 ; _rtXdot -> Integrator_x1_CSTATE_ma = _rtB -> B_136_680_5440
; _rtXdot -> Integrator_x2_CSTATE_p = _rtB -> B_136_682_5456 ; if ( _rtXdis
-> Integrator_CSTATE_oo ) { _rtXdot -> Integrator_CSTATE_oo = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_oo = _rtB -> B_136_713_5704 ; }
dVOC_monitor_network1_AutomaticGainControl_Deriv ( S , & _rtB ->
AutomaticGainControl , & _rtDW -> AutomaticGainControl , & _rtP ->
AutomaticGainControl , & _rtXdot -> AutomaticGainControl ) ; if ( _rtXdis ->
Integrator_CSTATE_pf ) { _rtXdot -> Integrator_CSTATE_pf = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_pf = _rtB -> B_136_709_5672 ; } { real_T
instantDelay ; instantDelay = _rtB -> B_136_730_5840 ; if ( instantDelay >
_rtP -> P_616 ) { instantDelay = _rtP -> P_616 ; } if ( instantDelay < 0.0 )
{ ( ( XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_d = 0 ; } else { ( (
XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_d = 1.0 / instantDelay ; } } _rtXdot ->
integrator_CSTATE_p = _rtB -> B_136_737_5896 [ 1 ] ; _rtXdot ->
TransferFcn_CSTATE_m = 0.0 ; _rtXdot -> TransferFcn_CSTATE_m += _rtP -> P_622
* _rtX -> TransferFcn_CSTATE_m ; _rtXdot -> TransferFcn_CSTATE_m += _rtB ->
B_136_710_5680 ; _rtXdot -> Integrator_x1_CSTATE_a = _rtB -> B_136_725_5800 ;
_rtXdot -> Integrator_x2_CSTATE_a = _rtB -> B_136_727_5816 ; if ( _rtXdis ->
Integrator_CSTATE_d ) { _rtXdot -> Integrator_CSTATE_d = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_d = _rtB -> B_136_758_6064 ; }
dVOC_monitor_network1_AutomaticGainControl_Deriv ( S , & _rtB ->
AutomaticGainControl_m , & _rtDW -> AutomaticGainControl_m , & _rtP ->
AutomaticGainControl_m , & _rtXdot -> AutomaticGainControl_m ) ; if ( _rtXdis
-> Integrator_CSTATE_jn ) { _rtXdot -> Integrator_CSTATE_jn = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_jn = _rtB -> B_136_754_6032 ; } { real_T
instantDelay ; instantDelay = _rtB -> B_136_775_6200 ; if ( instantDelay >
_rtP -> P_659 ) { instantDelay = _rtP -> P_659 ; } if ( instantDelay < 0.0 )
{ ( ( XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_jz = 0 ; } else { ( (
XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_jz = 1.0 / instantDelay ; } } _rtXdot ->
integrator_CSTATE_j = _rtB -> B_136_782_6256 [ 1 ] ; _rtXdot ->
TransferFcn_CSTATE_e = 0.0 ; _rtXdot -> TransferFcn_CSTATE_e += _rtP -> P_665
* _rtX -> TransferFcn_CSTATE_e ; _rtXdot -> TransferFcn_CSTATE_e += _rtB ->
B_136_755_6040 ; _rtXdot -> Integrator_x1_CSTATE_c = _rtB -> B_136_770_6160 ;
_rtXdot -> Integrator_x2_CSTATE_oa = _rtB -> B_136_772_6176 ; if ( _rtXdis ->
Integrator_CSTATE_nj ) { _rtXdot -> Integrator_CSTATE_nj = 0.0 ; } else {
_rtXdot -> Integrator_CSTATE_nj = _rtB -> B_136_803_6424 ; }
dVOC_monitor_network1_AutomaticGainControl_Deriv ( S , & _rtB ->
AutomaticGainControl_b2 , & _rtDW -> AutomaticGainControl_b2 , & _rtP ->
AutomaticGainControl_b2 , & _rtXdot -> AutomaticGainControl_b2 ) ; if (
_rtXdis -> Integrator_CSTATE_fu ) { _rtXdot -> Integrator_CSTATE_fu = 0.0 ; }
else { _rtXdot -> Integrator_CSTATE_fu = _rtB -> B_136_799_6392 ; } { real_T
instantDelay ; instantDelay = _rtB -> B_136_820_6560 ; if ( instantDelay >
_rtP -> P_702 ) { instantDelay = _rtP -> P_702 ; } if ( instantDelay < 0.0 )
{ ( ( XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_b = 0 ; } else { ( (
XDot_dVOC_monitor_network1_T * ) ssGetdX ( S ) ) ->
VariableTransportDelay_CSTATE_b = 1.0 / instantDelay ; } } _rtXdot ->
integrator_CSTATE_mw = _rtB -> B_136_827_6616 [ 1 ] ; _rtXdot ->
TransferFcn_CSTATE_d = 0.0 ; _rtXdot -> TransferFcn_CSTATE_d += _rtP -> P_708
* _rtX -> TransferFcn_CSTATE_d ; _rtXdot -> TransferFcn_CSTATE_d += _rtB ->
B_136_800_6400 ; _rtXdot -> Integrator_x1_CSTATE_n = _rtB -> B_136_815_6520 ;
_rtXdot -> Integrator_x2_CSTATE_gi = _rtB -> B_136_817_6536 ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_dVOC_monitor_network1_T *
_rtB ; DW_dVOC_monitor_network1_T * _rtDW ; P_dVOC_monitor_network1_T * _rtP
; X_dVOC_monitor_network1_T * _rtX ; ZCV_dVOC_monitor_network1_T * _rtZCSV ;
_rtDW = ( ( DW_dVOC_monitor_network1_T * ) ssGetRootDWork ( S ) ) ; _rtZCSV =
( ( ZCV_dVOC_monitor_network1_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtX
= ( ( X_dVOC_monitor_network1_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_dVOC_monitor_network1_T * ) _ssGetModelBlockIO ( S ) ) ; _rtZCSV ->
Saturation_UprLim_ZC = _rtB -> B_136_110_880 - _rtP -> P_155 ; _rtZCSV ->
Saturation_LwrLim_ZC = _rtB -> B_136_110_880 - _rtP -> P_156 ; _rtZCSV ->
Switch_SwitchCond_ZC = _rtB -> B_136_112_896 - _rtP -> P_157 ; _rtZCSV ->
Saturation_UprLim_ZC_n = _rtB -> B_136_114_912 - _rtP -> P_162 ; _rtZCSV ->
Saturation_LwrLim_ZC_e = _rtB -> B_136_114_912 - _rtP -> P_163 ; _rtZCSV ->
Switch_SwitchCond_ZC_h = _rtB -> B_136_116_928 - _rtP -> P_164 ; switch (
_rtDW -> Integrator_MODE ) { case 1 : _rtZCSV -> Integrator_IntgUpLimit_ZC =
0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC = _rtP -> P_303 - _rtP -> P_304 ;
break ; case 2 : _rtZCSV -> Integrator_IntgUpLimit_ZC = _rtP -> P_304 - _rtP
-> P_303 ; _rtZCSV -> Integrator_IntgLoLimit_ZC = 0.0 ; break ; default :
_rtZCSV -> Integrator_IntgUpLimit_ZC = _rtX -> Integrator_CSTATE_o - _rtP ->
P_303 ; _rtZCSV -> Integrator_IntgLoLimit_ZC = _rtX -> Integrator_CSTATE_o -
_rtP -> P_304 ; break ; } if ( ( _rtDW -> Integrator_MODE == 3 ) || ( _rtDW
-> Integrator_MODE == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC = _rtB
-> B_136_376_3008 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC = 0.0 ; }
_rtZCSV -> LowerRelop1_RelopInput_ZC = _rtB -> B_136_365_2920 - _rtB ->
B_136_370_2960 ; _rtZCSV -> UpperRelop_RelopInput_ZC = _rtB -> B_136_365_2920
- _rtB -> B_136_369_2952 ; _rtZCSV -> VImin_UprLim_ZC = _rtB ->
B_136_371_2968 - _rtP -> P_320 ; _rtZCSV -> VImin_LwrLim_ZC = _rtB ->
B_136_371_2968 - _rtP -> P_321 ; _rtZCSV -> RelationalOperator_RelopInput_ZC
= _rtX -> Integrator_CSTATE_j - _rtB -> B_136_1000_8000 ; switch ( _rtDW ->
Integrator_MODE_f ) { case 1 : _rtZCSV -> Integrator_IntgUpLimit_ZC_e = 0.0 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_e = _rtP -> P_345 - _rtP -> P_346 ;
break ; case 2 : _rtZCSV -> Integrator_IntgUpLimit_ZC_e = _rtP -> P_346 -
_rtP -> P_345 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_e = 0.0 ; break ;
default : _rtZCSV -> Integrator_IntgUpLimit_ZC_e = _rtX ->
Integrator_CSTATE_j - _rtP -> P_345 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_e
= _rtX -> Integrator_CSTATE_j - _rtP -> P_346 ; break ; } if ( ( _rtDW ->
Integrator_MODE_f == 3 ) || ( _rtDW -> Integrator_MODE_f == 4 ) ) { _rtZCSV
-> Integrator_LeaveSaturate_ZC_j = _rtB -> B_136_443_3544 ; } else { _rtZCSV
-> Integrator_LeaveSaturate_ZC_j = 0.0 ; } _rtZCSV ->
HitCrossing_HitNoOutput_ZC = _rtB -> B_136_427_3416 - _rtP -> P_353 ;
dVOC_monitor_network1_AutomaticGainControl_ZC ( S , & _rtB ->
AutomaticGainControl_g , & _rtDW -> AutomaticGainControl_g , & _rtP ->
AutomaticGainControl_g , & _rtZCSV -> AutomaticGainControl_g ) ; switch (
_rtDW -> Integrator_MODE_j ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_h = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_f =
_rtP -> P_355 - _rtP -> P_356 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_h = _rtP -> P_356 - _rtP -> P_355 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_f = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_h = _rtX -> Integrator_CSTATE_i4 - _rtP -> P_355 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_f = _rtX -> Integrator_CSTATE_i4 - _rtP
-> P_356 ; break ; } if ( ( _rtDW -> Integrator_MODE_j == 3 ) || ( _rtDW ->
Integrator_MODE_j == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_g = _rtB
-> B_136_439_3512 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_g = 0.0 ;
} _rtZCSV -> RelationalOperator_RelopInput_ZC_g = _rtB -> B_136_435_3480 -
_rtB -> B_136_1001_8008 ; _rtZCSV -> Saturation2_UprLim_ZC = _rtB ->
B_136_442_3536 - _rtP -> P_366 ; _rtZCSV -> Saturation2_LwrLim_ZC = _rtB ->
B_136_442_3536 - _rtP -> P_367 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_h = _rtX -> Integrator_CSTATE_h - _rtB ->
B_136_1004_8032 ; switch ( _rtDW -> Integrator_MODE_k ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_d = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_k =
_rtP -> P_388 - _rtP -> P_389 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_d = _rtP -> P_389 - _rtP -> P_388 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_k = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_d = _rtX -> Integrator_CSTATE_h - _rtP -> P_388 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_k = _rtX -> Integrator_CSTATE_h - _rtP
-> P_389 ; break ; } if ( ( _rtDW -> Integrator_MODE_k == 3 ) || ( _rtDW ->
Integrator_MODE_k == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_c = _rtB
-> B_136_488_3904 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_c = 0.0 ;
} _rtZCSV -> HitCrossing_HitNoOutput_ZC_m = _rtB -> B_136_472_3776 - _rtP ->
P_396 ; dVOC_monitor_network1_AutomaticGainControl_ZC ( S , & _rtB ->
AutomaticGainControl_k , & _rtDW -> AutomaticGainControl_k , & _rtP ->
AutomaticGainControl_k , & _rtZCSV -> AutomaticGainControl_k ) ; switch (
_rtDW -> Integrator_MODE_e ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_i = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_l =
_rtP -> P_398 - _rtP -> P_399 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_i = _rtP -> P_399 - _rtP -> P_398 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_l = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_i = _rtX -> Integrator_CSTATE_nh - _rtP -> P_398 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_l = _rtX -> Integrator_CSTATE_nh - _rtP
-> P_399 ; break ; } if ( ( _rtDW -> Integrator_MODE_e == 3 ) || ( _rtDW ->
Integrator_MODE_e == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_k = _rtB
-> B_136_484_3872 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_k = 0.0 ;
} _rtZCSV -> RelationalOperator_RelopInput_ZC_go = _rtB -> B_136_480_3840 -
_rtB -> B_136_1005_8040 ; _rtZCSV -> Saturation2_UprLim_ZC_l = _rtB ->
B_136_487_3896 - _rtP -> P_409 ; _rtZCSV -> Saturation2_LwrLim_ZC_h = _rtB ->
B_136_487_3896 - _rtP -> P_410 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_hm = _rtX -> Integrator_CSTATE_a - _rtB ->
B_136_1008_8064 ; switch ( _rtDW -> Integrator_MODE_h ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_j = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_i =
_rtP -> P_431 - _rtP -> P_432 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_j = _rtP -> P_432 - _rtP -> P_431 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_i = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_j = _rtX -> Integrator_CSTATE_a - _rtP -> P_431 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_i = _rtX -> Integrator_CSTATE_a - _rtP
-> P_432 ; break ; } if ( ( _rtDW -> Integrator_MODE_h == 3 ) || ( _rtDW ->
Integrator_MODE_h == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_m = _rtB
-> B_136_533_4264 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_m = 0.0 ;
} _rtZCSV -> HitCrossing_HitNoOutput_ZC_f = _rtB -> B_136_517_4136 - _rtP ->
P_439 ; dVOC_monitor_network1_AutomaticGainControl_ZC ( S , & _rtB ->
AutomaticGainControl_c , & _rtDW -> AutomaticGainControl_c , & _rtP ->
AutomaticGainControl_c , & _rtZCSV -> AutomaticGainControl_c ) ; switch (
_rtDW -> Integrator_MODE_n ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_a = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_n =
_rtP -> P_441 - _rtP -> P_442 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_a = _rtP -> P_442 - _rtP -> P_441 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_n = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_a = _rtX -> Integrator_CSTATE_m - _rtP -> P_441 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_n = _rtX -> Integrator_CSTATE_m - _rtP
-> P_442 ; break ; } if ( ( _rtDW -> Integrator_MODE_n == 3 ) || ( _rtDW ->
Integrator_MODE_n == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_b = _rtB
-> B_136_529_4232 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_b = 0.0 ;
} _rtZCSV -> RelationalOperator_RelopInput_ZC_i = _rtB -> B_136_525_4200 -
_rtB -> B_136_1009_8072 ; _rtZCSV -> Saturation2_UprLim_ZC_o = _rtB ->
B_136_532_4256 - _rtP -> P_452 ; _rtZCSV -> Saturation2_LwrLim_ZC_o = _rtB ->
B_136_532_4256 - _rtP -> P_453 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_m = _rtX -> Integrator_CSTATE_c - _rtB ->
B_136_1012_8096 ; switch ( _rtDW -> Integrator_MODE_k4 ) { case 1 : _rtZCSV
-> Integrator_IntgUpLimit_ZC_e3 = 0.0 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_h = _rtP -> P_474 - _rtP -> P_475 ; break ; case 2
: _rtZCSV -> Integrator_IntgUpLimit_ZC_e3 = _rtP -> P_475 - _rtP -> P_474 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_h = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_e3 = _rtX -> Integrator_CSTATE_c - _rtP -> P_474 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_h = _rtX -> Integrator_CSTATE_c - _rtP
-> P_475 ; break ; } if ( ( _rtDW -> Integrator_MODE_k4 == 3 ) || ( _rtDW ->
Integrator_MODE_k4 == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_i = _rtB
-> B_136_578_4624 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_i = 0.0 ;
} _rtZCSV -> HitCrossing_HitNoOutput_ZC_b = _rtB -> B_136_562_4496 - _rtP ->
P_482 ; dVOC_monitor_network1_AutomaticGainControl_ZC ( S , & _rtB ->
AutomaticGainControl_b , & _rtDW -> AutomaticGainControl_b , & _rtP ->
AutomaticGainControl_b , & _rtZCSV -> AutomaticGainControl_b ) ; switch (
_rtDW -> Integrator_MODE_k5 ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_o = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_lf =
_rtP -> P_484 - _rtP -> P_485 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_o = _rtP -> P_485 - _rtP -> P_484 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_lf = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_o = _rtX -> Integrator_CSTATE_f - _rtP -> P_484 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_lf = _rtX -> Integrator_CSTATE_f - _rtP
-> P_485 ; break ; } if ( ( _rtDW -> Integrator_MODE_k5 == 3 ) || ( _rtDW ->
Integrator_MODE_k5 == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_cf =
_rtB -> B_136_574_4592 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_cf =
0.0 ; } _rtZCSV -> RelationalOperator_RelopInput_ZC_a = _rtB ->
B_136_570_4560 - _rtB -> B_136_1013_8104 ; _rtZCSV -> Saturation2_UprLim_ZC_i
= _rtB -> B_136_577_4616 - _rtP -> P_495 ; _rtZCSV -> Saturation2_LwrLim_ZC_e
= _rtB -> B_136_577_4616 - _rtP -> P_496 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_l = _rtX -> Integrator_CSTATE_c0 - _rtB ->
B_136_1016_8128 ; switch ( _rtDW -> Integrator_MODE_d ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_eb = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_g =
_rtP -> P_517 - _rtP -> P_518 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_eb = _rtP -> P_518 - _rtP -> P_517 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_g = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_eb = _rtX -> Integrator_CSTATE_c0 - _rtP -> P_517 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_g = _rtX -> Integrator_CSTATE_c0 - _rtP
-> P_518 ; break ; } if ( ( _rtDW -> Integrator_MODE_d == 3 ) || ( _rtDW ->
Integrator_MODE_d == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_a = _rtB
-> B_136_623_4984 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_a = 0.0 ;
} _rtZCSV -> HitCrossing_HitNoOutput_ZC_mb = _rtB -> B_136_607_4856 - _rtP ->
P_525 ; dVOC_monitor_network1_AutomaticGainControl_ZC ( S , & _rtB ->
AutomaticGainControl_l , & _rtDW -> AutomaticGainControl_l , & _rtP ->
AutomaticGainControl_l , & _rtZCSV -> AutomaticGainControl_l ) ; switch (
_rtDW -> Integrator_MODE_i ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_el = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_a =
_rtP -> P_527 - _rtP -> P_528 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_el = _rtP -> P_528 - _rtP -> P_527 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_a = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_el = _rtX -> Integrator_CSTATE_b - _rtP -> P_527 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_a = _rtX -> Integrator_CSTATE_b - _rtP
-> P_528 ; break ; } if ( ( _rtDW -> Integrator_MODE_i == 3 ) || ( _rtDW ->
Integrator_MODE_i == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_o = _rtB
-> B_136_619_4952 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_o = 0.0 ;
} _rtZCSV -> RelationalOperator_RelopInput_ZC_lg = _rtB -> B_136_615_4920 -
_rtB -> B_136_1017_8136 ; _rtZCSV -> Saturation2_UprLim_ZC_m = _rtB ->
B_136_622_4976 - _rtP -> P_538 ; _rtZCSV -> Saturation2_LwrLim_ZC_ek = _rtB
-> B_136_622_4976 - _rtP -> P_539 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_f = _rtX -> Integrator_CSTATE_pq - _rtB ->
B_136_1020_8160 ; switch ( _rtDW -> Integrator_MODE_g ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_g = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_k1 =
_rtP -> P_560 - _rtP -> P_561 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_g = _rtP -> P_561 - _rtP -> P_560 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_k1 = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_g = _rtX -> Integrator_CSTATE_pq - _rtP -> P_560 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_k1 = _rtX -> Integrator_CSTATE_pq - _rtP
-> P_561 ; break ; } if ( ( _rtDW -> Integrator_MODE_g == 3 ) || ( _rtDW ->
Integrator_MODE_g == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_l = _rtB
-> B_136_668_5344 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_l = 0.0 ;
} _rtZCSV -> HitCrossing_HitNoOutput_ZC_d = _rtB -> B_136_652_5216 - _rtP ->
P_569 ; dVOC_monitor_network1_AutomaticGainControl_ZC ( S , & _rtB ->
AutomaticGainControl_a , & _rtDW -> AutomaticGainControl_a , & _rtP ->
AutomaticGainControl_a , & _rtZCSV -> AutomaticGainControl_a ) ; switch (
_rtDW -> Integrator_MODE_p ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_df = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_d =
_rtP -> P_571 - _rtP -> P_572 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_df = _rtP -> P_572 - _rtP -> P_571 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_d = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_df = _rtX -> Integrator_CSTATE_jf - _rtP -> P_571 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_d = _rtX -> Integrator_CSTATE_jf - _rtP
-> P_572 ; break ; } if ( ( _rtDW -> Integrator_MODE_p == 3 ) || ( _rtDW ->
Integrator_MODE_p == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_n = _rtB
-> B_136_664_5312 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_n = 0.0 ;
} _rtZCSV -> RelationalOperator_RelopInput_ZC_j = _rtB -> B_136_660_5280 -
_rtB -> B_136_1021_8168 ; _rtZCSV -> Saturation2_UprLim_ZC_o5 = _rtB ->
B_136_667_5336 - _rtP -> P_582 ; _rtZCSV -> Saturation2_LwrLim_ZC_l = _rtB ->
B_136_667_5336 - _rtP -> P_583 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_ii = _rtX -> Integrator_CSTATE_oo - _rtB ->
B_136_1024_8192 ; switch ( _rtDW -> Integrator_MODE_m ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_p = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_h3 =
_rtP -> P_604 - _rtP -> P_605 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_p = _rtP -> P_605 - _rtP -> P_604 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_h3 = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_p = _rtX -> Integrator_CSTATE_oo - _rtP -> P_604 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_h3 = _rtX -> Integrator_CSTATE_oo - _rtP
-> P_605 ; break ; } if ( ( _rtDW -> Integrator_MODE_m == 3 ) || ( _rtDW ->
Integrator_MODE_m == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_p = _rtB
-> B_136_713_5704 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_p = 0.0 ;
} _rtZCSV -> HitCrossing_HitNoOutput_ZC_a = _rtB -> B_136_697_5576 - _rtP ->
P_612 ; dVOC_monitor_network1_AutomaticGainControl_ZC ( S , & _rtB ->
AutomaticGainControl , & _rtDW -> AutomaticGainControl , & _rtP ->
AutomaticGainControl , & _rtZCSV -> AutomaticGainControl ) ; switch ( _rtDW
-> Integrator_MODE_es ) { case 1 : _rtZCSV -> Integrator_IntgUpLimit_ZC_b =
0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_c = _rtP -> P_614 - _rtP -> P_615
; break ; case 2 : _rtZCSV -> Integrator_IntgUpLimit_ZC_b = _rtP -> P_615 -
_rtP -> P_614 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_c = 0.0 ; break ;
default : _rtZCSV -> Integrator_IntgUpLimit_ZC_b = _rtX ->
Integrator_CSTATE_pf - _rtP -> P_614 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_c
= _rtX -> Integrator_CSTATE_pf - _rtP -> P_615 ; break ; } if ( ( _rtDW ->
Integrator_MODE_es == 3 ) || ( _rtDW -> Integrator_MODE_es == 4 ) ) { _rtZCSV
-> Integrator_LeaveSaturate_ZC_oq = _rtB -> B_136_709_5672 ; } else { _rtZCSV
-> Integrator_LeaveSaturate_ZC_oq = 0.0 ; } _rtZCSV ->
RelationalOperator_RelopInput_ZC_b = _rtB -> B_136_705_5640 - _rtB ->
B_136_1025_8200 ; _rtZCSV -> Saturation2_UprLim_ZC_d = _rtB -> B_136_712_5696
- _rtP -> P_625 ; _rtZCSV -> Saturation2_LwrLim_ZC_p = _rtB -> B_136_712_5696
- _rtP -> P_626 ; _rtZCSV -> RelationalOperator_RelopInput_ZC_j1 = _rtX ->
Integrator_CSTATE_d - _rtB -> B_136_1028_8224 ; switch ( _rtDW ->
Integrator_MODE_dx ) { case 1 : _rtZCSV -> Integrator_IntgUpLimit_ZC_f = 0.0
; _rtZCSV -> Integrator_IntgLoLimit_ZC_c0 = _rtP -> P_647 - _rtP -> P_648 ;
break ; case 2 : _rtZCSV -> Integrator_IntgUpLimit_ZC_f = _rtP -> P_648 -
_rtP -> P_647 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_c0 = 0.0 ; break ;
default : _rtZCSV -> Integrator_IntgUpLimit_ZC_f = _rtX ->
Integrator_CSTATE_d - _rtP -> P_647 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_c0
= _rtX -> Integrator_CSTATE_d - _rtP -> P_648 ; break ; } if ( ( _rtDW ->
Integrator_MODE_dx == 3 ) || ( _rtDW -> Integrator_MODE_dx == 4 ) ) { _rtZCSV
-> Integrator_LeaveSaturate_ZC_oe = _rtB -> B_136_758_6064 ; } else { _rtZCSV
-> Integrator_LeaveSaturate_ZC_oe = 0.0 ; } _rtZCSV ->
HitCrossing_HitNoOutput_ZC_i = _rtB -> B_136_742_5936 - _rtP -> P_655 ;
dVOC_monitor_network1_AutomaticGainControl_ZC ( S , & _rtB ->
AutomaticGainControl_m , & _rtDW -> AutomaticGainControl_m , & _rtP ->
AutomaticGainControl_m , & _rtZCSV -> AutomaticGainControl_m ) ; switch (
_rtDW -> Integrator_MODE_il ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_iv = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_fj
= _rtP -> P_657 - _rtP -> P_658 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_iv = _rtP -> P_658 - _rtP -> P_657 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_fj = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_iv = _rtX -> Integrator_CSTATE_jn - _rtP -> P_657 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_fj = _rtX -> Integrator_CSTATE_jn - _rtP
-> P_658 ; break ; } if ( ( _rtDW -> Integrator_MODE_il == 3 ) || ( _rtDW ->
Integrator_MODE_il == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_km =
_rtB -> B_136_754_6032 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_km =
0.0 ; } _rtZCSV -> RelationalOperator_RelopInput_ZC_gi = _rtB ->
B_136_750_6000 - _rtB -> B_136_1029_8232 ; _rtZCSV -> Saturation2_UprLim_ZC_h
= _rtB -> B_136_757_6056 - _rtP -> P_668 ; _rtZCSV -> Saturation2_LwrLim_ZC_f
= _rtB -> B_136_757_6056 - _rtP -> P_669 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC_am = _rtX -> Integrator_CSTATE_nj - _rtB ->
B_136_1032_8256 ; switch ( _rtDW -> Integrator_MODE_mo ) { case 1 : _rtZCSV
-> Integrator_IntgUpLimit_ZC_fr = 0.0 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_nn = _rtP -> P_690 - _rtP -> P_691 ; break ; case 2
: _rtZCSV -> Integrator_IntgUpLimit_ZC_fr = _rtP -> P_691 - _rtP -> P_690 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_nn = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_fr = _rtX -> Integrator_CSTATE_nj - _rtP -> P_690 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_nn = _rtX -> Integrator_CSTATE_nj - _rtP
-> P_691 ; break ; } if ( ( _rtDW -> Integrator_MODE_mo == 3 ) || ( _rtDW ->
Integrator_MODE_mo == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_kf =
_rtB -> B_136_803_6424 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_kf =
0.0 ; } _rtZCSV -> HitCrossing_HitNoOutput_ZC_c = _rtB -> B_136_787_6296 -
_rtP -> P_698 ; dVOC_monitor_network1_AutomaticGainControl_ZC ( S , & _rtB ->
AutomaticGainControl_b2 , & _rtDW -> AutomaticGainControl_b2 , & _rtP ->
AutomaticGainControl_b2 , & _rtZCSV -> AutomaticGainControl_b2 ) ; switch (
_rtDW -> Integrator_MODE_h5 ) { case 1 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_d4 = 0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC_ia
= _rtP -> P_700 - _rtP -> P_701 ; break ; case 2 : _rtZCSV ->
Integrator_IntgUpLimit_ZC_d4 = _rtP -> P_701 - _rtP -> P_700 ; _rtZCSV ->
Integrator_IntgLoLimit_ZC_ia = 0.0 ; break ; default : _rtZCSV ->
Integrator_IntgUpLimit_ZC_d4 = _rtX -> Integrator_CSTATE_fu - _rtP -> P_700 ;
_rtZCSV -> Integrator_IntgLoLimit_ZC_ia = _rtX -> Integrator_CSTATE_fu - _rtP
-> P_701 ; break ; } if ( ( _rtDW -> Integrator_MODE_h5 == 3 ) || ( _rtDW ->
Integrator_MODE_h5 == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC_e = _rtB
-> B_136_799_6392 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC_e = 0.0 ;
} _rtZCSV -> RelationalOperator_RelopInput_ZC_ab = _rtB -> B_136_795_6360 -
_rtB -> B_136_1033_8264 ; _rtZCSV -> Saturation2_UprLim_ZC_f = _rtB ->
B_136_802_6416 - _rtP -> P_711 ; _rtZCSV -> Saturation2_LwrLim_ZC_i = _rtB ->
B_136_802_6416 - _rtP -> P_712 ; } static void mdlInitializeSizes ( SimStruct
* S ) { ssSetChecksumVal ( S , 0 , 521000689U ) ; ssSetChecksumVal ( S , 1 ,
2060064665U ) ; ssSetChecksumVal ( S , 2 , 127444357U ) ; ssSetChecksumVal (
S , 3 , 864382025U ) ; { mxArray * slVerStructMat = ( NULL ) ; mxArray *
slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status
= mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if (
status == 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 ,
"Version" ) ; if ( slVerMat == ( NULL ) ) { status = 1 ; } else { status =
mxGetString ( slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "23.2" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != ( SLSize )
sizeof ( DW_dVOC_monitor_network1_T ) ) { static char msg [ 256 ] ; snprintf
( msg , 256 , "Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofDWork ( S ) , ( unsigned long ) sizeof (
DW_dVOC_monitor_network1_T ) ) ; ssSetErrorStatus ( S , msg ) ; } if (
ssGetSizeofGlobalBlockIO ( S ) != ( SLSize ) sizeof (
B_dVOC_monitor_network1_T ) ) { static char msg [ 256 ] ; snprintf ( msg ,
256 , "Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofGlobalBlockIO ( S ) , ( unsigned long ) sizeof (
B_dVOC_monitor_network1_T ) ) ; ssSetErrorStatus ( S , msg ) ; } { int
ssSizeofParams ; ssGetSizeofParams ( S , & ssSizeofParams ) ; if (
ssSizeofParams != sizeof ( P_dVOC_monitor_network1_T ) ) { static char msg [
256 ] ; snprintf ( msg , 256 ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file (%d vs %lu)." , ssSizeofParams , (
unsigned long ) sizeof ( P_dVOC_monitor_network1_T ) ) ; ssSetErrorStatus ( S
, msg ) ; } } _ssSetModelRtp ( S , ( real_T * ) &
dVOC_monitor_network1_rtDefaultP ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ;
( ( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_306 = rtInf ; (
( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_345 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_346 = rtMinusInf ; (
( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_355 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_366 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_388 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_389 = rtMinusInf ; (
( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_398 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_409 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_431 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_432 = rtMinusInf ; (
( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_441 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_452 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_474 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_475 = rtMinusInf ; (
( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_484 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_495 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_517 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_518 = rtMinusInf ; (
( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_527 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_538 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_560 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_561 = rtMinusInf ; (
( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_571 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_582 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_604 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_605 = rtMinusInf ; (
( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_614 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_625 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_647 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_648 = rtMinusInf ; (
( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_657 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_668 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_690 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_691 = rtMinusInf ; (
( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_700 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> P_711 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> AutomaticGainControl_c
. P_7 = rtInf ; ( ( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) ->
AutomaticGainControl_k . P_7 = rtInf ; ( ( P_dVOC_monitor_network1_T * )
ssGetModelRtp ( S ) ) -> AutomaticGainControl_g . P_7 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) ->
AutomaticGainControl_b2 . P_7 = rtInf ; ( ( P_dVOC_monitor_network1_T * )
ssGetModelRtp ( S ) ) -> AutomaticGainControl_m . P_7 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> AutomaticGainControl_l
. P_7 = rtInf ; ( ( P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) ->
AutomaticGainControl_b . P_7 = rtInf ; ( ( P_dVOC_monitor_network1_T * )
ssGetModelRtp ( S ) ) -> AutomaticGainControl_a . P_7 = rtInf ; ( (
P_dVOC_monitor_network1_T * ) ssGetModelRtp ( S ) ) -> AutomaticGainControl .
P_7 = rtInf ; } static void mdlInitializeSampleTimes ( SimStruct * S ) {
slAccRegPrmChangeFcn ( S , mdlOutputsTID4 ) ; } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
