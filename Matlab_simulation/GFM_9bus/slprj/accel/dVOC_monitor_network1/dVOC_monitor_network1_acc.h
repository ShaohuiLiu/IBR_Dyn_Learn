#ifndef RTW_HEADER_dVOC_monitor_network1_acc_h_
#define RTW_HEADER_dVOC_monitor_network1_acc_h_
#ifndef dVOC_monitor_network1_acc_COMMON_INCLUDES_
#define dVOC_monitor_network1_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn
#define S_FUNCTION_LEVEL 2
#ifndef RTW_GENERATED_S_FUNCTION
#define RTW_GENERATED_S_FUNCTION
#endif
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "dVOC_monitor_network1_acc_types.h"
#include <stddef.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rt_defines.h"
#include "simstruc_types.h"
typedef struct { real_T B_24_1752_13384 ; real_T B_24_1753_13392 ; }
B_Subsystempi2delay_dVOC_monitor_network1_T ; typedef struct { int32_T
Subsystempi2delay_sysIdxToRun ; int8_T Subsystempi2delay_SubsysRanBC ;
boolean_T Subsystempi2delay_MODE ; char_T pad_Subsystempi2delay_MODE [ 2 ] ;
} DW_Subsystempi2delay_dVOC_monitor_network1_T ; typedef struct { real_T
B_25_1750_13368 ; real_T B_25_1751_13376 ; }
B_Subsystem1_dVOC_monitor_network1_T ; typedef struct { int32_T
Subsystem1_sysIdxToRun ; int8_T Subsystem1_SubsysRanBC ; boolean_T
Subsystem1_MODE ; char_T pad_Subsystem1_MODE [ 2 ] ; }
DW_Subsystem1_dVOC_monitor_network1_T ; typedef struct { real_T
B_36_1728_13192 ; real_T B_36_1729_13200 ; }
B_Subsystempi2delay_dVOC_monitor_network1_b_T ; typedef struct { int32_T
Subsystempi2delay_sysIdxToRun ; int8_T Subsystempi2delay_SubsysRanBC ;
boolean_T Subsystempi2delay_MODE ; char_T pad_Subsystempi2delay_MODE [ 2 ] ;
} DW_Subsystempi2delay_dVOC_monitor_network1_d_T ; typedef struct { real_T
B_37_1726_13176 ; real_T B_37_1727_13184 ; }
B_Subsystem1_dVOC_monitor_network1_m_T ; typedef struct { int32_T
Subsystem1_sysIdxToRun ; int8_T Subsystem1_SubsysRanBC ; boolean_T
Subsystem1_MODE ; char_T pad_Subsystem1_MODE [ 2 ] ; }
DW_Subsystem1_dVOC_monitor_network1_k_T ; typedef struct { creal_T
B_56_1658_12648 ; real_T B_56_1659_12664 ; real_T B_56_1660_12672 ; real_T
B_56_1661_12680 ; real_T B_56_1662_12688 ; real_T B_56_1663_12696 ; real_T
B_56_1664_12704 ; real_T B_56_1665_12712 ; real_T B_56_1666_12720 ; real_T
B_56_1667_12728 ; real_T B_56_1668_12736 ; real_T B_56_1669_12744 ; real_T
B_56_1670_12752 ; real_T B_56_1671_12760 ; real_T B_56_1672_12768 ; real_T
B_56_1673_12776 ; real_T B_56_1674_12784 [ 3 ] ; real_T B_56_1677_12808 [ 3 ]
; real_T B_56_1680_12832 [ 2 ] ; real_T B_56_1682_12848 ; real_T
B_56_1683_12856 ; real_T B_56_1684_12864 ; real_T B_56_1685_12872 ; real_T
B_53_1686_12880 ; real_T B_53_1687_12888 ; real_T B_52_1688_12896 ; real_T
B_52_1689_12904 ; uint8_T B_56_1690_12912 ; uint8_T B_56_1691_12913 ;
boolean_T B_56_1692_12914 ; boolean_T B_56_1693_12915 ; char_T
pad_B_56_1693_12915 [ 4 ] ; B_Subsystem1_dVOC_monitor_network1_T Subsystem1 ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay ; }
B_AutomaticGainControl_dVOC_monitor_network1_T ; typedef struct { struct {
real_T modelTStart ; } VariableTransportDelay_RWORK ; struct { real_T
modelTStart ; } VariableTransportDelay_RWORK_i ; struct { void * TUbufferPtrs
[ 3 ] ; } VariableTransportDelay_PWORK ; struct { void * TUbufferPtrs [ 3 ] ;
} VariableTransportDelay_PWORK_e ; int32_T AutomaticGainControl_sysIdxToRun ;
int32_T TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_j ; struct { int_T Tail ; int_T
Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
VariableTransportDelay_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last
; int_T CircularBufSize ; int_T MaxNewBufSize ; }
VariableTransportDelay_IWORK_b ; int_T Saturation_MODE ; int8_T
AutomaticGainControl_SubsysRanBC ; boolean_T RelationalOperator_Mode ;
boolean_T RelationalOperator_Mode_n ; boolean_T AutomaticGainControl_MODE ;
char_T pad_AutomaticGainControl_MODE [ 4 ] ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1 ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay ; }
DW_AutomaticGainControl_dVOC_monitor_network1_T ; typedef struct { real_T
VariableTransportDelay_CSTATE_o3 ; real_T integrator_CSTATE_f ; real_T
VariableTransportDelay_CSTATE_k ; real_T integrator_CSTATE_ot ; }
X_AutomaticGainControl_dVOC_monitor_network1_T ; typedef struct { real_T
VariableTransportDelay_CSTATE_o3 ; real_T integrator_CSTATE_f ; real_T
VariableTransportDelay_CSTATE_k ; real_T integrator_CSTATE_ot ; }
XDot_AutomaticGainControl_dVOC_monitor_network1_T ; typedef struct {
boolean_T VariableTransportDelay_CSTATE_o3 ; boolean_T integrator_CSTATE_f ;
boolean_T VariableTransportDelay_CSTATE_k ; boolean_T integrator_CSTATE_ot ;
} XDis_AutomaticGainControl_dVOC_monitor_network1_T ; typedef struct { real_T
VariableTransportDelay_CSTATE_o3 ; real_T integrator_CSTATE_f ; real_T
VariableTransportDelay_CSTATE_k ; real_T integrator_CSTATE_ot ; }
XAbsTol_AutomaticGainControl_dVOC_monitor_network1_T ; typedef struct {
real_T VariableTransportDelay_CSTATE_o3 ; real_T integrator_CSTATE_f ; real_T
VariableTransportDelay_CSTATE_k ; real_T integrator_CSTATE_ot ; }
XPtMin_AutomaticGainControl_dVOC_monitor_network1_T ; typedef struct { real_T
VariableTransportDelay_CSTATE_o3 ; real_T integrator_CSTATE_f ; real_T
VariableTransportDelay_CSTATE_k ; real_T integrator_CSTATE_ot ; }
XPtMax_AutomaticGainControl_dVOC_monitor_network1_T ; typedef struct { real_T
RelationalOperator_RelopInput_ZC_jo ; real_T
RelationalOperator_RelopInput_ZC_k ; real_T Saturation_UprLim_ZC_a ; real_T
Saturation_LwrLim_ZC_o ; } ZCV_AutomaticGainControl_dVOC_monitor_network1_T ;
typedef struct { ZCSigState RelationalOperator_RelopInput_ZCE_m4 ; ZCSigState
RelationalOperator_RelopInput_ZCE_o ; ZCSigState Saturation_UprLim_ZCE_p ;
ZCSigState Saturation_LwrLim_ZCE_h ; }
ZCE_AutomaticGainControl_dVOC_monitor_network1_T ; typedef struct { real_T
B_136_0_0 [ 5 ] ; real_T B_136_5_40 [ 3 ] ; real_T B_136_8_64 ; real_T
B_136_9_72 ; real_T B_136_10_80 ; real_T B_136_11_88 [ 3 ] ; real_T
B_136_14_112 ; real_T B_136_15_120 [ 2 ] ; real_T B_136_17_136 ; real_T
B_136_18_144 ; real_T B_136_19_152 ; real_T B_136_20_160 ; real_T
B_136_21_168 ; real_T B_136_22_176 ; real_T B_136_23_184 ; real_T
B_136_24_192 ; real_T B_136_25_200 ; real_T B_136_26_208 ; real_T
B_136_27_216 ; real_T B_136_28_224 ; real_T B_136_29_232 ; real_T
B_136_30_240 [ 3 ] ; real_T B_136_33_264 [ 2 ] ; real_T B_136_35_280 ; real_T
B_136_36_288 ; real_T B_136_37_296 [ 3 ] ; real_T B_136_40_320 [ 2 ] ; real_T
B_136_42_336 ; real_T B_136_43_344 ; real_T B_136_44_352 ; real_T
B_136_45_360 ; real_T B_136_46_368 ; real_T B_136_47_376 ; real_T
B_136_48_384 ; real_T B_136_49_392 ; real_T B_136_50_400 ; real_T
B_136_51_408 ; real_T B_136_52_416 ; real_T B_136_53_424 ; real_T
B_136_54_432 ; real_T B_136_55_440 ; real_T B_136_56_448 ; real_T
B_136_57_456 ; real_T B_136_58_464 ; real_T B_136_59_472 ; real_T
B_136_60_480 ; real_T B_136_61_488 ; real_T B_136_62_496 [ 3 ] ; real_T
B_136_65_520 ; real_T B_136_66_528 [ 2 ] ; real_T B_136_68_544 ; real_T
B_136_69_552 ; real_T B_136_70_560 ; real_T B_136_71_568 ; real_T
B_136_72_576 ; real_T B_136_73_584 ; real_T B_136_74_592 ; real_T
B_136_75_600 ; real_T B_136_76_608 ; real_T B_136_77_616 ; real_T
B_136_78_624 ; real_T B_136_79_632 ; real_T B_136_80_640 ; real_T
B_136_81_648 [ 3 ] ; real_T B_136_84_672 [ 2 ] ; real_T B_136_86_688 ; real_T
B_136_87_696 ; real_T B_136_88_704 [ 3 ] ; real_T B_136_91_728 [ 2 ] ; real_T
B_136_93_744 ; real_T B_136_94_752 ; real_T B_136_95_760 ; real_T
B_136_96_768 ; real_T B_136_97_776 ; real_T B_136_98_784 ; real_T
B_136_99_792 ; real_T B_136_100_800 ; real_T B_136_101_808 ; real_T
B_136_102_816 ; real_T B_136_103_824 ; real_T B_136_104_832 ; real_T
B_136_105_840 ; real_T B_136_106_848 ; real_T B_136_107_856 ; real_T
B_136_108_864 ; real_T B_136_109_872 ; real_T B_136_110_880 ; real_T
B_136_111_888 ; real_T B_136_112_896 ; real_T B_136_113_904 ; real_T
B_136_114_912 ; real_T B_136_115_920 ; real_T B_136_116_928 ; real_T
B_136_117_936 ; real_T B_136_118_944 [ 76 ] ; real_T B_136_194_1552 [ 15 ] ;
real_T B_136_209_1672 ; real_T B_136_210_1680 ; real_T B_136_211_1688 ;
real_T B_136_212_1696 ; real_T B_136_213_1704 ; real_T B_136_214_1712 ;
real_T B_136_215_1720 ; real_T B_136_216_1728 [ 18 ] ; real_T B_136_234_1872
[ 3 ] ; real_T B_136_237_1896 [ 2 ] ; real_T B_136_239_1912 [ 3 ] ; real_T
B_136_242_1936 [ 2 ] ; real_T B_136_244_1952 ; real_T B_136_245_1960 ; real_T
B_136_246_1968 ; real_T B_136_247_1976 ; real_T B_136_248_1984 ; real_T
B_136_249_1992 ; real_T B_136_250_2000 [ 3 ] ; real_T B_136_253_2024 [ 2 ] ;
real_T B_136_255_2040 [ 3 ] ; real_T B_136_258_2064 [ 2 ] ; real_T
B_136_260_2080 ; real_T B_136_261_2088 ; real_T B_136_262_2096 ; real_T
B_136_263_2104 ; real_T B_136_264_2112 ; real_T B_136_265_2120 ; real_T
B_136_266_2128 ; real_T B_136_267_2136 ; real_T B_136_268_2144 ; real_T
B_136_269_2152 ; real_T B_136_270_2160 ; real_T B_136_271_2168 ; real_T
B_136_272_2176 ; real_T B_136_273_2184 ; real_T B_136_274_2192 ; real_T
B_136_275_2200 ; real_T B_136_276_2208 ; real_T B_136_277_2216 ; real_T
B_136_278_2224 ; real_T B_136_279_2232 [ 3 ] ; real_T B_136_282_2256 [ 2 ] ;
real_T B_136_284_2272 [ 3 ] ; real_T B_136_287_2296 ; real_T B_136_288_2304 ;
real_T B_136_289_2312 ; real_T B_136_290_2320 ; real_T B_136_291_2328 ;
real_T B_136_292_2336 ; real_T B_136_293_2344 ; real_T B_136_294_2352 ;
real_T B_136_295_2360 ; real_T B_136_296_2368 ; real_T B_136_297_2376 ;
real_T B_136_298_2384 ; real_T B_136_299_2392 ; real_T B_136_300_2400 ;
real_T B_136_301_2408 ; real_T B_136_302_2416 ; real_T B_136_303_2424 ;
real_T B_136_304_2432 ; real_T B_136_305_2440 ; real_T B_136_306_2448 ;
real_T B_136_307_2456 ; real_T B_136_308_2464 ; real_T B_136_309_2472 ;
real_T B_136_310_2480 ; real_T B_136_311_2488 ; real_T B_136_312_2496 ;
real_T B_136_313_2504 ; real_T B_136_314_2512 ; real_T B_136_315_2520 ;
real_T B_136_316_2528 ; real_T B_136_317_2536 ; real_T B_136_318_2544 ;
real_T B_136_319_2552 ; real_T B_136_320_2560 ; real_T B_136_321_2568 ;
real_T B_136_322_2576 ; real_T B_136_323_2584 ; real_T B_136_324_2592 ;
real_T B_136_325_2600 ; real_T B_136_326_2608 ; real_T B_136_327_2616 ;
real_T B_136_328_2624 ; real_T B_136_329_2632 ; real_T B_136_330_2640 ;
real_T B_136_331_2648 ; real_T B_136_332_2656 ; real_T B_136_333_2664 ;
real_T B_136_334_2672 ; real_T B_136_335_2680 ; real_T B_136_336_2688 ;
real_T B_136_337_2696 ; real_T B_136_338_2704 ; real_T B_136_339_2712 ;
real_T B_136_340_2720 ; real_T B_136_341_2728 ; real_T B_136_342_2736 ;
real_T B_136_343_2744 ; real_T B_136_344_2752 ; real_T B_136_345_2760 ;
real_T B_136_346_2768 ; real_T B_136_347_2776 ; real_T B_136_348_2784 ;
real_T B_136_349_2792 ; real_T B_136_350_2800 ; real_T B_136_351_2808 ;
real_T B_136_352_2816 ; real_T B_136_353_2824 ; real_T B_136_354_2832 ;
real_T B_136_355_2840 ; real_T B_136_356_2848 ; real_T B_136_357_2856 ;
real_T B_136_358_2864 ; real_T B_136_359_2872 ; real_T B_136_360_2880 ;
real_T B_136_361_2888 ; real_T B_136_362_2896 ; real_T B_136_363_2904 ;
real_T B_136_364_2912 ; real_T B_136_365_2920 ; real_T B_136_366_2928 ;
real_T B_136_367_2936 ; real_T B_136_368_2944 ; real_T B_136_369_2952 ;
real_T B_136_370_2960 ; real_T B_136_371_2968 ; real_T B_136_372_2976 ;
real_T B_136_373_2984 ; real_T B_136_374_2992 ; real_T B_136_375_3000 ;
real_T B_136_376_3008 ; real_T B_136_377_3016 ; real_T B_136_378_3024 ;
real_T B_136_379_3032 [ 5 ] ; real_T B_136_384_3072 [ 25 ] ; real_T
B_136_409_3272 [ 5 ] ; real_T B_136_414_3312 ; real_T B_136_415_3320 [ 5 ] ;
real_T B_136_420_3360 ; real_T B_136_421_3368 ; real_T B_136_422_3376 ;
real_T B_136_423_3384 ; real_T B_136_424_3392 ; real_T B_136_425_3400 ;
real_T B_136_426_3408 ; real_T B_136_427_3416 ; real_T B_136_428_3424 [ 3 ] ;
real_T B_136_431_3448 ; real_T B_136_432_3456 ; real_T B_136_433_3464 ;
real_T B_136_434_3472 ; real_T B_136_435_3480 ; real_T B_136_436_3488 ;
real_T B_136_437_3496 ; real_T B_136_438_3504 ; real_T B_136_439_3512 ;
real_T B_136_440_3520 ; real_T B_136_441_3528 ; real_T B_136_442_3536 ;
real_T B_136_443_3544 ; real_T B_136_444_3552 ; real_T B_136_445_3560 ;
real_T B_136_446_3568 ; real_T B_136_447_3576 ; real_T B_136_448_3584 ;
real_T B_136_449_3592 ; real_T B_136_450_3600 ; real_T B_136_451_3608 ;
real_T B_136_452_3616 ; real_T B_136_453_3624 ; real_T B_136_454_3632 ;
real_T B_136_455_3640 ; real_T B_136_456_3648 ; real_T B_136_457_3656 ;
real_T B_136_458_3664 ; real_T B_136_459_3672 ; real_T B_136_460_3680 ;
real_T B_136_461_3688 [ 3 ] ; real_T B_136_464_3712 [ 3 ] ; real_T
B_136_467_3736 [ 2 ] ; real_T B_136_469_3752 ; real_T B_136_470_3760 ; real_T
B_136_471_3768 ; real_T B_136_472_3776 ; real_T B_136_473_3784 [ 3 ] ; real_T
B_136_476_3808 ; real_T B_136_477_3816 ; real_T B_136_478_3824 ; real_T
B_136_479_3832 ; real_T B_136_480_3840 ; real_T B_136_481_3848 ; real_T
B_136_482_3856 ; real_T B_136_483_3864 ; real_T B_136_484_3872 ; real_T
B_136_485_3880 ; real_T B_136_486_3888 ; real_T B_136_487_3896 ; real_T
B_136_488_3904 ; real_T B_136_489_3912 ; real_T B_136_490_3920 ; real_T
B_136_491_3928 ; real_T B_136_492_3936 ; real_T B_136_493_3944 ; real_T
B_136_494_3952 ; real_T B_136_495_3960 ; real_T B_136_496_3968 ; real_T
B_136_497_3976 ; real_T B_136_498_3984 ; real_T B_136_499_3992 ; real_T
B_136_500_4000 ; real_T B_136_501_4008 ; real_T B_136_502_4016 ; real_T
B_136_503_4024 ; real_T B_136_504_4032 ; real_T B_136_505_4040 ; real_T
B_136_506_4048 [ 3 ] ; real_T B_136_509_4072 [ 3 ] ; real_T B_136_512_4096 [
2 ] ; real_T B_136_514_4112 ; real_T B_136_515_4120 ; real_T B_136_516_4128 ;
real_T B_136_517_4136 ; real_T B_136_518_4144 [ 3 ] ; real_T B_136_521_4168 ;
real_T B_136_522_4176 ; real_T B_136_523_4184 ; real_T B_136_524_4192 ;
real_T B_136_525_4200 ; real_T B_136_526_4208 ; real_T B_136_527_4216 ;
real_T B_136_528_4224 ; real_T B_136_529_4232 ; real_T B_136_530_4240 ;
real_T B_136_531_4248 ; real_T B_136_532_4256 ; real_T B_136_533_4264 ;
real_T B_136_534_4272 ; real_T B_136_535_4280 ; real_T B_136_536_4288 ;
real_T B_136_537_4296 ; real_T B_136_538_4304 ; real_T B_136_539_4312 ;
real_T B_136_540_4320 ; real_T B_136_541_4328 ; real_T B_136_542_4336 ;
real_T B_136_543_4344 ; real_T B_136_544_4352 ; real_T B_136_545_4360 ;
real_T B_136_546_4368 ; real_T B_136_547_4376 ; real_T B_136_548_4384 ;
real_T B_136_549_4392 ; real_T B_136_550_4400 ; real_T B_136_551_4408 [ 3 ] ;
real_T B_136_554_4432 [ 3 ] ; real_T B_136_557_4456 [ 2 ] ; real_T
B_136_559_4472 ; real_T B_136_560_4480 ; real_T B_136_561_4488 ; real_T
B_136_562_4496 ; real_T B_136_563_4504 [ 3 ] ; real_T B_136_566_4528 ; real_T
B_136_567_4536 ; real_T B_136_568_4544 ; real_T B_136_569_4552 ; real_T
B_136_570_4560 ; real_T B_136_571_4568 ; real_T B_136_572_4576 ; real_T
B_136_573_4584 ; real_T B_136_574_4592 ; real_T B_136_575_4600 ; real_T
B_136_576_4608 ; real_T B_136_577_4616 ; real_T B_136_578_4624 ; real_T
B_136_579_4632 ; real_T B_136_580_4640 ; real_T B_136_581_4648 ; real_T
B_136_582_4656 ; real_T B_136_583_4664 ; real_T B_136_584_4672 ; real_T
B_136_585_4680 ; real_T B_136_586_4688 ; real_T B_136_587_4696 ; real_T
B_136_588_4704 ; real_T B_136_589_4712 ; real_T B_136_590_4720 ; real_T
B_136_591_4728 ; real_T B_136_592_4736 ; real_T B_136_593_4744 ; real_T
B_136_594_4752 ; real_T B_136_595_4760 ; real_T B_136_596_4768 [ 3 ] ; real_T
B_136_599_4792 [ 3 ] ; real_T B_136_602_4816 [ 2 ] ; real_T B_136_604_4832 ;
real_T B_136_605_4840 ; real_T B_136_606_4848 ; real_T B_136_607_4856 ;
real_T B_136_608_4864 [ 3 ] ; real_T B_136_611_4888 ; real_T B_136_612_4896 ;
real_T B_136_613_4904 ; real_T B_136_614_4912 ; real_T B_136_615_4920 ;
real_T B_136_616_4928 ; real_T B_136_617_4936 ; real_T B_136_618_4944 ;
real_T B_136_619_4952 ; real_T B_136_620_4960 ; real_T B_136_621_4968 ;
real_T B_136_622_4976 ; real_T B_136_623_4984 ; real_T B_136_624_4992 ;
real_T B_136_625_5000 ; real_T B_136_626_5008 ; real_T B_136_627_5016 ;
real_T B_136_628_5024 ; real_T B_136_629_5032 ; real_T B_136_630_5040 ;
real_T B_136_631_5048 ; real_T B_136_632_5056 ; real_T B_136_633_5064 ;
real_T B_136_634_5072 ; real_T B_136_635_5080 ; real_T B_136_636_5088 ;
real_T B_136_637_5096 ; real_T B_136_638_5104 ; real_T B_136_639_5112 ;
real_T B_136_640_5120 ; real_T B_136_641_5128 [ 3 ] ; real_T B_136_644_5152 [
3 ] ; real_T B_136_647_5176 [ 2 ] ; real_T B_136_649_5192 ; real_T
B_136_650_5200 ; real_T B_136_651_5208 ; real_T B_136_652_5216 ; real_T
B_136_653_5224 [ 3 ] ; real_T B_136_656_5248 ; real_T B_136_657_5256 ; real_T
B_136_658_5264 ; real_T B_136_659_5272 ; real_T B_136_660_5280 ; real_T
B_136_661_5288 ; real_T B_136_662_5296 ; real_T B_136_663_5304 ; real_T
B_136_664_5312 ; real_T B_136_665_5320 ; real_T B_136_666_5328 ; real_T
B_136_667_5336 ; real_T B_136_668_5344 ; real_T B_136_669_5352 ; real_T
B_136_670_5360 ; real_T B_136_671_5368 ; real_T B_136_672_5376 ; real_T
B_136_673_5384 ; real_T B_136_674_5392 ; real_T B_136_675_5400 ; real_T
B_136_676_5408 ; real_T B_136_677_5416 ; real_T B_136_678_5424 ; real_T
B_136_679_5432 ; real_T B_136_680_5440 ; real_T B_136_681_5448 ; real_T
B_136_682_5456 ; real_T B_136_683_5464 ; real_T B_136_684_5472 ; real_T
B_136_685_5480 ; real_T B_136_686_5488 [ 3 ] ; real_T B_136_689_5512 [ 3 ] ;
real_T B_136_692_5536 [ 2 ] ; real_T B_136_694_5552 ; real_T B_136_695_5560 ;
real_T B_136_696_5568 ; real_T B_136_697_5576 ; real_T B_136_698_5584 [ 3 ] ;
real_T B_136_701_5608 ; real_T B_136_702_5616 ; real_T B_136_703_5624 ;
real_T B_136_704_5632 ; real_T B_136_705_5640 ; real_T B_136_706_5648 ;
real_T B_136_707_5656 ; real_T B_136_708_5664 ; real_T B_136_709_5672 ;
real_T B_136_710_5680 ; real_T B_136_711_5688 ; real_T B_136_712_5696 ;
real_T B_136_713_5704 ; real_T B_136_714_5712 ; real_T B_136_715_5720 ;
real_T B_136_716_5728 ; real_T B_136_717_5736 ; real_T B_136_718_5744 ;
real_T B_136_719_5752 ; real_T B_136_720_5760 ; real_T B_136_721_5768 ;
real_T B_136_722_5776 ; real_T B_136_723_5784 ; real_T B_136_724_5792 ;
real_T B_136_725_5800 ; real_T B_136_726_5808 ; real_T B_136_727_5816 ;
real_T B_136_728_5824 ; real_T B_136_729_5832 ; real_T B_136_730_5840 ;
real_T B_136_731_5848 [ 3 ] ; real_T B_136_734_5872 [ 3 ] ; real_T
B_136_737_5896 [ 2 ] ; real_T B_136_739_5912 ; real_T B_136_740_5920 ; real_T
B_136_741_5928 ; real_T B_136_742_5936 ; real_T B_136_743_5944 [ 3 ] ; real_T
B_136_746_5968 ; real_T B_136_747_5976 ; real_T B_136_748_5984 ; real_T
B_136_749_5992 ; real_T B_136_750_6000 ; real_T B_136_751_6008 ; real_T
B_136_752_6016 ; real_T B_136_753_6024 ; real_T B_136_754_6032 ; real_T
B_136_755_6040 ; real_T B_136_756_6048 ; real_T B_136_757_6056 ; real_T
B_136_758_6064 ; real_T B_136_759_6072 ; real_T B_136_760_6080 ; real_T
B_136_761_6088 ; real_T B_136_762_6096 ; real_T B_136_763_6104 ; real_T
B_136_764_6112 ; real_T B_136_765_6120 ; real_T B_136_766_6128 ; real_T
B_136_767_6136 ; real_T B_136_768_6144 ; real_T B_136_769_6152 ; real_T
B_136_770_6160 ; real_T B_136_771_6168 ; real_T B_136_772_6176 ; real_T
B_136_773_6184 ; real_T B_136_774_6192 ; real_T B_136_775_6200 ; real_T
B_136_776_6208 [ 3 ] ; real_T B_136_779_6232 [ 3 ] ; real_T B_136_782_6256 [
2 ] ; real_T B_136_784_6272 ; real_T B_136_785_6280 ; real_T B_136_786_6288 ;
real_T B_136_787_6296 ; real_T B_136_788_6304 [ 3 ] ; real_T B_136_791_6328 ;
real_T B_136_792_6336 ; real_T B_136_793_6344 ; real_T B_136_794_6352 ;
real_T B_136_795_6360 ; real_T B_136_796_6368 ; real_T B_136_797_6376 ;
real_T B_136_798_6384 ; real_T B_136_799_6392 ; real_T B_136_800_6400 ;
real_T B_136_801_6408 ; real_T B_136_802_6416 ; real_T B_136_803_6424 ;
real_T B_136_804_6432 ; real_T B_136_805_6440 ; real_T B_136_806_6448 ;
real_T B_136_807_6456 ; real_T B_136_808_6464 ; real_T B_136_809_6472 ;
real_T B_136_810_6480 ; real_T B_136_811_6488 ; real_T B_136_812_6496 ;
real_T B_136_813_6504 ; real_T B_136_814_6512 ; real_T B_136_815_6520 ;
real_T B_136_816_6528 ; real_T B_136_817_6536 ; real_T B_136_818_6544 ;
real_T B_136_819_6552 ; real_T B_136_820_6560 ; real_T B_136_821_6568 [ 3 ] ;
real_T B_136_824_6592 [ 3 ] ; real_T B_136_827_6616 [ 2 ] ; real_T
B_136_829_6632 ; real_T B_136_830_6640 ; real_T B_136_831_6648 ; real_T
B_136_832_6656 ; real_T B_136_833_6664 ; real_T B_136_834_6672 ; real_T
B_136_835_6680 ; real_T B_136_836_6688 ; real_T B_136_837_6696 ; real_T
B_136_838_6704 ; real_T B_136_839_6712 ; real_T B_136_840_6720 ; real_T
B_136_841_6728 ; real_T B_136_842_6736 ; real_T B_136_843_6744 ; real_T
B_136_844_6752 [ 15 ] ; real_T B_136_859_6872 ; real_T B_136_860_6880 ;
real_T B_136_861_6888 ; real_T B_136_862_6896 ; real_T B_136_863_6904 ;
real_T B_136_864_6912 ; real_T B_136_865_6920 ; real_T B_136_866_6928 ;
real_T B_136_867_6936 ; real_T B_136_868_6944 ; real_T B_136_869_6952 ;
real_T B_136_870_6960 ; real_T B_136_871_6968 ; real_T B_136_872_6976 ;
real_T B_136_873_6984 ; real_T B_136_874_6992 ; real_T B_136_875_7000 ;
real_T B_136_876_7008 ; real_T B_136_877_7016 ; real_T B_136_878_7024 ;
real_T B_136_879_7032 ; real_T B_136_880_7040 ; real_T B_136_881_7048 ;
real_T B_136_882_7056 ; real_T B_136_883_7064 ; real_T B_136_884_7072 ;
real_T B_136_885_7080 ; real_T B_136_886_7088 ; real_T B_136_887_7096 ;
real_T B_136_888_7104 [ 25 ] ; real_T B_136_913_7304 ; real_T B_136_914_7312
[ 25 ] ; real_T B_136_939_7512 ; real_T B_136_940_7520 [ 2 ] ; real_T
B_136_942_7536 [ 2 ] ; real_T B_136_944_7552 [ 25 ] ; real_T B_136_969_7752 [
25 ] ; real_T B_136_994_7952 [ 2 ] ; real_T B_136_996_7968 ; real_T
B_136_997_7976 ; real_T B_136_998_7984 ; real_T B_136_999_7992 ; real_T
B_136_1000_8000 ; real_T B_136_1001_8008 ; real_T B_136_1002_8016 ; real_T
B_136_1003_8024 ; real_T B_136_1004_8032 ; real_T B_136_1005_8040 ; real_T
B_136_1006_8048 ; real_T B_136_1007_8056 ; real_T B_136_1008_8064 ; real_T
B_136_1009_8072 ; real_T B_136_1010_8080 ; real_T B_136_1011_8088 ; real_T
B_136_1012_8096 ; real_T B_136_1013_8104 ; real_T B_136_1014_8112 ; real_T
B_136_1015_8120 ; real_T B_136_1016_8128 ; real_T B_136_1017_8136 ; real_T
B_136_1018_8144 ; real_T B_136_1019_8152 ; real_T B_136_1020_8160 ; real_T
B_136_1021_8168 ; real_T B_136_1022_8176 ; real_T B_136_1023_8184 ; real_T
B_136_1024_8192 ; real_T B_136_1025_8200 ; real_T B_136_1026_8208 ; real_T
B_136_1027_8216 ; real_T B_136_1028_8224 ; real_T B_136_1029_8232 ; real_T
B_136_1030_8240 ; real_T B_136_1031_8248 ; real_T B_136_1032_8256 ; real_T
B_136_1033_8264 ; real_T B_136_1034_8272 ; real_T B_136_1035_8280 ; real_T
B_136_1036_8288 ; real_T B_136_1037_8296 ; real_T B_136_1038_8304 ; real_T
B_136_1039_8312 ; real_T B_136_1040_8320 ; real_T B_136_1041_8328 ; real_T
B_136_1042_8336 ; real_T B_136_1043_8344 ; real_T B_136_1044_8352 ; real_T
B_136_1045_8360 ; real_T B_136_1046_8368 ; real_T B_136_1047_8376 ; real_T
B_136_1048_8384 ; real_T B_136_1049_8392 ; real_T B_136_1050_8400 ; real_T
B_136_1051_8408 ; real_T B_136_1052_8416 ; real_T B_136_1053_8424 ; real_T
B_136_1054_8432 ; real_T B_136_1055_8440 ; real_T B_136_1056_8448 ; real_T
B_136_1057_8456 ; real_T B_136_1058_8464 ; real_T B_136_1059_8472 ; real_T
B_136_1060_8480 ; real_T B_136_1061_8488 ; real_T B_136_1062_8496 ; real_T
B_136_1063_8504 ; real_T B_136_1064_8512 ; real_T B_128_1065_8520 ; real_T
B_128_1066_8528 ; real_T B_128_1067_8536 ; real_T B_128_1068_8544 [ 25 ] ;
real_T B_128_1093_8744 [ 25 ] ; real_T B_128_1118_8944 ; real_T
B_128_1119_8952 ; real_T B_128_1120_8960 [ 2 ] ; real_T B_128_1122_8976 [ 25
] ; real_T B_128_1147_9176 [ 25 ] ; real_T B_128_1172_9376 [ 25 ] ; real_T
B_128_1197_9576 ; real_T B_128_1198_9584 ; real_T B_127_1199_9592 ; real_T
B_127_1200_9600 ; real_T B_127_1201_9608 ; real_T B_127_1202_9616 [ 3 ] ;
real_T B_121_1205_9640 ; real_T B_121_1206_9648 ; real_T B_113_1207_9656 ;
real_T B_113_1208_9664 ; real_T B_105_1209_9672 ; real_T B_105_1210_9680 ;
real_T B_97_1211_9688 ; real_T B_97_1212_9696 ; real_T B_89_1213_9704 ;
real_T B_89_1214_9712 ; real_T B_81_1215_9720 ; real_T B_81_1216_9728 ;
real_T B_73_1217_9736 ; real_T B_73_1218_9744 ; real_T B_65_1219_9752 ;
real_T B_65_1220_9760 ; real_T B_57_1221_9768 ; real_T B_57_1222_9776 ;
real_T B_136_1223_9784 [ 3 ] ; real_T B_136_1226_9808 [ 3 ] ; real_T
B_136_1229_9832 [ 3 ] ; uint8_T B_136_1232_9856 ; uint8_T B_136_1233_9857 ;
uint8_T B_136_1234_9858 ; uint8_T B_136_1235_9859 ; uint8_T B_136_1236_9860 ;
uint8_T B_136_1237_9861 ; uint8_T B_136_1238_9862 ; uint8_T B_136_1239_9863 ;
uint8_T B_136_1240_9864 ; uint8_T B_136_1241_9865 ; uint8_T B_136_1242_9866 ;
uint8_T B_136_1243_9867 ; uint8_T B_136_1244_9868 ; uint8_T B_136_1245_9869 ;
uint8_T B_136_1246_9870 ; uint8_T B_136_1247_9871 ; uint8_T B_136_1248_9872 ;
uint8_T B_136_1249_9873 ; uint8_T B_136_1250_9874 ; uint8_T B_136_1251_9875 ;
uint8_T B_136_1252_9876 ; uint8_T B_136_1253_9877 ; uint8_T B_136_1254_9878 ;
uint8_T B_136_1255_9879 ; uint8_T B_136_1256_9880 ; uint8_T B_136_1257_9881 ;
uint8_T B_136_1258_9882 ; uint8_T B_136_1259_9883 ; uint8_T B_136_1260_9884 ;
uint8_T B_136_1261_9885 ; uint8_T B_136_1262_9886 ; uint8_T B_136_1263_9887 ;
uint8_T B_136_1264_9888 ; uint8_T B_136_1265_9889 ; uint8_T B_136_1266_9890 ;
uint8_T B_136_1267_9891 ; uint8_T B_136_1268_9892 ; uint8_T B_136_1269_9893 ;
uint8_T B_136_1270_9894 ; uint8_T B_136_1271_9895 ; uint8_T B_136_1272_9896 ;
uint8_T B_136_1273_9897 ; uint8_T B_136_1274_9898 ; uint8_T B_136_1275_9899 ;
uint8_T B_136_1276_9900 ; uint8_T B_136_1277_9901 ; boolean_T B_136_1278_9902
; boolean_T B_136_1279_9903 ; boolean_T B_136_1280_9904 ; boolean_T
B_136_1281_9905 ; boolean_T B_136_1282_9906 ; boolean_T B_136_1283_9907 ;
boolean_T B_136_1284_9908 ; boolean_T B_136_1285_9909 ; boolean_T
B_136_1286_9910 ; boolean_T B_136_1287_9911 ; boolean_T B_136_1288_9912 ;
boolean_T B_136_1289_9913 ; boolean_T B_136_1290_9914 ; boolean_T
B_136_1291_9915 ; boolean_T B_136_1292_9916 ; boolean_T B_136_1293_9917 ;
boolean_T B_136_1294_9918 ; boolean_T B_136_1295_9919 ; boolean_T
B_136_1296_9920 ; boolean_T B_136_1297_9921 ; boolean_T B_136_1298_9922 ;
boolean_T B_128_1299_9923 ; boolean_T B_128_1300_9924 ; boolean_T
B_128_1301_9925 ; char_T pad_B_128_1301_9925 [ 2 ] ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_p1 ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_lp ;
B_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_c ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_a ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_kj ;
B_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_k ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_cm ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_j ;
B_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_g ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_j ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_e ;
B_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b2 ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_bc ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_na ;
B_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_m ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_dt ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_n ;
B_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_l ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_e4 ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_p ;
B_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_n ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_ho ;
B_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_a ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_f ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_a ;
B_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl ;
B_Subsystem1_dVOC_monitor_network1_m_T Subsystem1_o ;
B_Subsystempi2delay_dVOC_monitor_network1_b_T Subsystempi2delay_dn ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_k ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_bp ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_gc ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_o4 ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_h ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_ct ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_c ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_g ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_d ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_d ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_pc ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_hz ;
B_Subsystem1_dVOC_monitor_network1_m_T Subsystem1_b ;
B_Subsystempi2delay_dVOC_monitor_network1_b_T Subsystempi2delay_o ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_p ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_h ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_ge ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_l ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_i ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_b ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_e ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_k ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1_g ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_c ;
B_Subsystem1_dVOC_monitor_network1_T Subsystem1 ;
B_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay ; }
B_dVOC_monitor_network1_T ; typedef struct { real_T Rotorangledthetae_DSTATE
; real_T fluxes_DSTATE [ 5 ] ; real_T Vdc_DSTATE ; real_T Idc_DSTATE ; real_T
Vdc_DSTATE_j ; real_T Idc_DSTATE_j ; real_T StateSpace_DSTATE [ 81 ] ; real_T
dw_delay_DSTATE ; real_T dw_predict_DSTATE ; real_T prediction_DSTATE ;
real_T prediction_DSTATE_e ; real_T DiscreteStateSpace_DSTATE ; real_T
DiscreteStateSpace_DSTATE_n ; real_T DiscreteStateSpace_DSTATE_d ; real_T
DiscreteStateSpace_DSTATE_g ; real_T voltages_DSTATE [ 5 ] ; real_T
Rotorspeeddeviationdw_DSTATE ; real_T theta_DSTATE ; real_T Lmd_sat_DSTATE ;
real_T Lmq_sat_DSTATE ; real_T Memory2_PreviousInput [ 3 ] ; real_T
Memory3_PreviousInput [ 3 ] ; real_T Memory1_PreviousInput [ 3 ] ; real_T
Memory2_PreviousInput_p [ 3 ] ; real_T Memory3_PreviousInput_b [ 3 ] ; real_T
Memory1_PreviousInput_m [ 3 ] ; real_T Memory_PreviousInput [ 3 ] ; real_T
Memory_PreviousInput_a [ 3 ] ; real_T RateTransition54_Buffer ; real_T
RateTransition12_Buffer ; real_T RateTransition53_Buffer ; real_T
RateTransition15_Buffer ; real_T RateTransition55_Buffer ; real_T
RateTransition52_Buffer ; real_T Memory4_PreviousInput ; real_T
Memory4_PreviousInput_c ; real_T inversion_DWORK1 [ 25 ] ; real_T
inversion_DWORK3 [ 25 ] ; real_T inversion_DWORK4 [ 25 ] ; real_T
RateTransition1_Buffer0 ; real_T Memory_PreviousInput_c ; real_T
Initial_FirstOutputTime ; real_T PrevY ; real_T LastMajorTime ; real_T
Memory_PreviousInput_ap ; real_T Initial_FirstOutputTime_g ; real_T PrevY_b ;
real_T LastMajorTime_n ; real_T Memory_PreviousInput_j ; real_T
Initial_FirstOutputTime_e ; real_T PrevY_n ; real_T LastMajorTime_d ; real_T
Memory_PreviousInput_m ; real_T Initial_FirstOutputTime_d ; real_T PrevY_e ;
real_T LastMajorTime_k ; real_T Memory_PreviousInput_g ; real_T
Initial_FirstOutputTime_du ; real_T PrevY_nq ; real_T LastMajorTime_e ;
real_T Memory_PreviousInput_n ; real_T Initial_FirstOutputTime_l ; real_T
PrevY_o ; real_T LastMajorTime_du ; real_T Memory_PreviousInput_c4 ; real_T
Initial_FirstOutputTime_lf ; real_T PrevY_nc ; real_T LastMajorTime_o ;
real_T Memory_PreviousInput_gc ; real_T Initial_FirstOutputTime_f ; real_T
PrevY_l ; real_T LastMajorTime_kb ; real_T Memory_PreviousInput_cp ; real_T
Initial_FirstOutputTime_gw ; real_T PrevY_ow ; real_T LastMajorTime_i ;
real_T inversion_DWORK4_i [ 25 ] ; struct { real_T modelTStart ; }
VariableTransportDelay_RWORK ; struct { real_T modelTStart ; }
VariableTransportDelay_RWORK_g ; struct { real_T modelTStart ; }
VariableTransportDelay_RWORK_n ; struct { real_T modelTStart ; }
VariableTransportDelay_RWORK_j ; struct { real_T modelTStart ; }
VariableTransportDelay_RWORK_n0 ; struct { real_T modelTStart ; }
VariableTransportDelay_RWORK_k ; struct { real_T modelTStart ; }
VariableTransportDelay_RWORK_km ; struct { real_T modelTStart ; }
VariableTransportDelay_RWORK_k4 ; struct { real_T modelTStart ; }
VariableTransportDelay_RWORK_d ; struct { void * AS ; void * BS ; void * CS ;
void * DS ; void * DX_COL ; void * BD_COL ; void * TMP1 ; void * TMP2 ; void
* XTMP ; void * SWITCH_STATUS ; void * SWITCH_STATUS_INIT ; void * SW_CHG ;
void * G_STATE ; void * USWLAST ; void * XKM12 ; void * XKP12 ; void * XLAST
; void * ULAST ; void * IDX_SW_CHG ; void * Y_SWITCH ; void * SWITCH_TYPES ;
void * IDX_OUT_SW ; void * SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; }
StateSpace_PWORK ; void * Power2_PWORK [ 4 ] ; void * Scope_PWORK [ 8 ] ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace1_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace10_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace11_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace12_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace2_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace3_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace5_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace50_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace51_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace55_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace6_PWORK ;
void * Scope_PWORK_p [ 2 ] ; void * Scope1_PWORK ; void * Scope_PWORK_c ;
void * Scope17_PWORK [ 3 ] ; struct { void * TUbufferPtrs [ 3 ] ; }
VariableTransportDelay_PWORK ; void * Scope18_PWORK [ 3 ] ; struct { void *
TUbufferPtrs [ 3 ] ; } VariableTransportDelay_PWORK_l ; void * Scope19_PWORK
[ 3 ] ; struct { void * TUbufferPtrs [ 3 ] ; } VariableTransportDelay_PWORK_m
; void * Scope14_PWORK [ 3 ] ; struct { void * TUbufferPtrs [ 3 ] ; }
VariableTransportDelay_PWORK_p ; void * Scope13_PWORK [ 3 ] ; struct { void *
TUbufferPtrs [ 3 ] ; } VariableTransportDelay_PWORK_f ; void * Scope15_PWORK
[ 3 ] ; struct { void * TUbufferPtrs [ 3 ] ; } VariableTransportDelay_PWORK_o
; void * Scope11_PWORK [ 3 ] ; struct { void * TUbufferPtrs [ 3 ] ; }
VariableTransportDelay_PWORK_e ; void * Scope12_PWORK [ 3 ] ; struct { void *
TUbufferPtrs [ 3 ] ; } VariableTransportDelay_PWORK_lv ; void * Scope16_PWORK
[ 3 ] ; struct { void * TUbufferPtrs [ 3 ] ; } VariableTransportDelay_PWORK_g
; int32_T inversion_DWORK2 [ 5 ] ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_f ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_m ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_o ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_a ; int32_T
TmpAtomicSubsysAtICInport1_sysIdxToRun ; int32_T Saturation_sysIdxToRun ;
int32_T Lmq_sat_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_j ; int32_T
TmpAtomicSubsysAtSwitch2Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_jp ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_a ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_e ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_p ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_m ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_d ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_b ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_g ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_bx ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_n ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_j ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_k ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_f ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_kq ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_p ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_m ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_l ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_o1 ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_e ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_om ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_jq ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_d ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_me ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_dt ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_b ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_g ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_fp ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_e ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_ej ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_l ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_n ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun_kf ; int32_T
TmpAtomicSubsysAtSwitch3Inport1_sysIdxToRun_fq ; uint32_T m_bpIndex ;
uint32_T m_bpIndex_b ; int_T StateSpace_IWORK [ 11 ] ; int_T Integrator_IWORK
; struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ;
int_T MaxNewBufSize ; } VariableTransportDelay_IWORK ; int_T
Integrator_IWORK_l ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } VariableTransportDelay_IWORK_b ;
int_T Integrator_IWORK_f ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; }
VariableTransportDelay_IWORK_k ; int_T Integrator_IWORK_k ; struct { int_T
Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize
; } VariableTransportDelay_IWORK_ka ; int_T Integrator_IWORK_b ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } VariableTransportDelay_IWORK_i ; int_T Integrator_IWORK_c ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } VariableTransportDelay_IWORK_kh ; int_T Integrator_IWORK_bu
; struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ;
int_T MaxNewBufSize ; } VariableTransportDelay_IWORK_a ; int_T
Integrator_IWORK_d ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } VariableTransportDelay_IWORK_l ;
int_T Integrator_IWORK_m ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; }
VariableTransportDelay_IWORK_p ; int_T Saturation_MODE ; int_T
Saturation_MODE_c ; int_T Integrator_MODE ; int_T VImin_MODE ; int_T
Integrator_MODE_f ; int_T Integrator_MODE_j ; int_T Saturation2_MODE ; int_T
Integrator_MODE_k ; int_T Integrator_MODE_e ; int_T Saturation2_MODE_c ;
int_T Integrator_MODE_h ; int_T Integrator_MODE_n ; int_T Saturation2_MODE_e
; int_T Integrator_MODE_k4 ; int_T Integrator_MODE_k5 ; int_T
Saturation2_MODE_l ; int_T Integrator_MODE_d ; int_T Integrator_MODE_i ;
int_T Saturation2_MODE_n ; int_T Integrator_MODE_g ; int_T Integrator_MODE_p
; int_T Saturation2_MODE_g ; int_T Integrator_MODE_m ; int_T
Integrator_MODE_es ; int_T Saturation2_MODE_cy ; int_T Integrator_MODE_dx ;
int_T Integrator_MODE_il ; int_T Saturation2_MODE_nj ; int_T
Integrator_MODE_mo ; int_T Integrator_MODE_h5 ; int_T Saturation2_MODE_cm ;
int8_T Sqrt2_DWORK1 ; int8_T Sqrt2_DWORK1_h ; int8_T
RateTransition1_semaphoreTaken ; int8_T Saturation_SubsysRanBC ; int8_T
Lmq_sat_SubsysRanBC ; uint8_T Rotorangledthetae_NumInitCond ; uint8_T
Rotorspeeddeviationdw_SYSTEM_ENABLE ; uint8_T
Rotorspeeddeviationdw_NumInitCond ; uint8_T theta_NumInitCond ; boolean_T
Switch_Mode ; boolean_T Switch_Mode_b ; boolean_T LowerRelop1_Mode ;
boolean_T UpperRelop_Mode ; boolean_T RelationalOperator_Mode ; boolean_T
RelationalOperator_Mode_l ; boolean_T PrevLimited ; boolean_T
RelationalOperator_Mode_n ; boolean_T RelationalOperator_Mode_d ; boolean_T
PrevLimited_p ; boolean_T RelationalOperator_Mode_g ; boolean_T
RelationalOperator_Mode_lj ; boolean_T PrevLimited_m ; boolean_T
RelationalOperator_Mode_k ; boolean_T RelationalOperator_Mode_j ; boolean_T
PrevLimited_a ; boolean_T RelationalOperator_Mode_je ; boolean_T
RelationalOperator_Mode_du ; boolean_T PrevLimited_k ; boolean_T
RelationalOperator_Mode_a ; boolean_T RelationalOperator_Mode_ak ; boolean_T
PrevLimited_n ; boolean_T RelationalOperator_Mode_o ; boolean_T
RelationalOperator_Mode_e ; boolean_T PrevLimited_b ; boolean_T
RelationalOperator_Mode_j1 ; boolean_T RelationalOperator_Mode_d4 ; boolean_T
PrevLimited_g ; boolean_T RelationalOperator_Mode_m ; boolean_T
RelationalOperator_Mode_m2 ; boolean_T PrevLimited_m0 ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_p1 ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_lp ;
DW_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_c ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_a ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_kj ;
DW_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_k ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_cm ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_j ;
DW_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_g ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_j ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_e ;
DW_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b2 ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_bc ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_na ;
DW_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_m ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_dt ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_n ;
DW_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_l ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_e4 ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_p ;
DW_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_n ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_ho ;
DW_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_a ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_f ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_a ;
DW_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl ;
DW_Subsystem1_dVOC_monitor_network1_k_T Subsystem1_o ;
DW_Subsystempi2delay_dVOC_monitor_network1_d_T Subsystempi2delay_dn ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_k ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_bp ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_gc ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_o4 ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_h ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_ct ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_c ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_g ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_d ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_d ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_pc ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_hz ;
DW_Subsystem1_dVOC_monitor_network1_k_T Subsystem1_b ;
DW_Subsystempi2delay_dVOC_monitor_network1_d_T Subsystempi2delay_o ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_p ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_h ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_ge ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_l ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_i ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_b ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_e ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_k ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1_g ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_c ;
DW_Subsystem1_dVOC_monitor_network1_T Subsystem1 ;
DW_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay ; }
DW_dVOC_monitor_network1_T ; typedef struct { real_T Integrator_CSTATE ;
real_T Integrator_CSTATE_i ; real_T Integrator1_CSTATE ; real_T
Integrator3_CSTATE ; real_T TransferFcn4_CSTATE ; real_T Integrator1_CSTATE_m
; real_T Integrator1_CSTATE_f ; real_T Integrator_CSTATE_n ; real_T
Integrator_CSTATE_p ; real_T Integrator1_CSTATE_i ; real_T
Integrator3_CSTATE_o ; real_T TransferFcn4_CSTATE_m ; real_T
Integrator1_CSTATE_g ; real_T Integrator1_CSTATE_b ; real_T Internal_CSTATE ;
real_T Internal_CSTATE_n ; real_T TransferFcn2_CSTATE ; real_T
TransferFcn4_CSTATE_l ; real_T TransferFcn2_CSTATE_a ; real_T
TransferFcn4_CSTATE_n ; real_T Internal_CSTATE_p ; real_T Integrator_CSTATE_o
; real_T StateSpace_CSTATE ; real_T StateSpace_CSTATE_n ; real_T
Integrator_CSTATE_j ; real_T Integrator_CSTATE_i4 ; real_T
VariableTransportDelay_CSTATE ; real_T integrator_CSTATE ; real_T
TransferFcn_CSTATE ; real_T Integrator_x1_CSTATE ; real_T
Integrator_x2_CSTATE ; real_T Integrator_CSTATE_h ; real_T
Integrator_CSTATE_nh ; real_T VariableTransportDelay_CSTATE_f ; real_T
integrator_CSTATE_g ; real_T TransferFcn_CSTATE_l ; real_T
Integrator_x1_CSTATE_j ; real_T Integrator_x2_CSTATE_m ; real_T
Integrator_CSTATE_a ; real_T Integrator_CSTATE_m ; real_T
VariableTransportDelay_CSTATE_j ; real_T integrator_CSTATE_d ; real_T
TransferFcn_CSTATE_f ; real_T Integrator_x1_CSTATE_m ; real_T
Integrator_x2_CSTATE_g ; real_T Integrator_CSTATE_c ; real_T
Integrator_CSTATE_f ; real_T VariableTransportDelay_CSTATE_g ; real_T
integrator_CSTATE_m ; real_T TransferFcn_CSTATE_a ; real_T
Integrator_x1_CSTATE_f ; real_T Integrator_x2_CSTATE_o ; real_T
Integrator_CSTATE_c0 ; real_T Integrator_CSTATE_b ; real_T
VariableTransportDelay_CSTATE_o ; real_T integrator_CSTATE_o ; real_T
TransferFcn_CSTATE_ac ; real_T Integrator_x1_CSTATE_k ; real_T
Integrator_x2_CSTATE_f ; real_T Integrator_CSTATE_pq ; real_T
Integrator_CSTATE_jf ; real_T VariableTransportDelay_CSTATE_l ; real_T
integrator_CSTATE_a ; real_T TransferFcn_CSTATE_k ; real_T
Integrator_x1_CSTATE_ma ; real_T Integrator_x2_CSTATE_p ; real_T
Integrator_CSTATE_oo ; real_T Integrator_CSTATE_pf ; real_T
VariableTransportDelay_CSTATE_d ; real_T integrator_CSTATE_p ; real_T
TransferFcn_CSTATE_m ; real_T Integrator_x1_CSTATE_a ; real_T
Integrator_x2_CSTATE_a ; real_T Integrator_CSTATE_d ; real_T
Integrator_CSTATE_jn ; real_T VariableTransportDelay_CSTATE_jz ; real_T
integrator_CSTATE_j ; real_T TransferFcn_CSTATE_e ; real_T
Integrator_x1_CSTATE_c ; real_T Integrator_x2_CSTATE_oa ; real_T
Integrator_CSTATE_nj ; real_T Integrator_CSTATE_fu ; real_T
VariableTransportDelay_CSTATE_b ; real_T integrator_CSTATE_mw ; real_T
TransferFcn_CSTATE_d ; real_T Integrator_x1_CSTATE_n ; real_T
Integrator_x2_CSTATE_gi ; X_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_c ; X_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_k ; X_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_g ; X_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_b2 ; X_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_m ; X_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_l ; X_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_b ; X_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_a ; X_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl ; } X_dVOC_monitor_network1_T ; typedef struct { real_T
Integrator_CSTATE ; real_T Integrator_CSTATE_i ; real_T Integrator1_CSTATE ;
real_T Integrator3_CSTATE ; real_T TransferFcn4_CSTATE ; real_T
Integrator1_CSTATE_m ; real_T Integrator1_CSTATE_f ; real_T
Integrator_CSTATE_n ; real_T Integrator_CSTATE_p ; real_T
Integrator1_CSTATE_i ; real_T Integrator3_CSTATE_o ; real_T
TransferFcn4_CSTATE_m ; real_T Integrator1_CSTATE_g ; real_T
Integrator1_CSTATE_b ; real_T Internal_CSTATE ; real_T Internal_CSTATE_n ;
real_T TransferFcn2_CSTATE ; real_T TransferFcn4_CSTATE_l ; real_T
TransferFcn2_CSTATE_a ; real_T TransferFcn4_CSTATE_n ; real_T
Internal_CSTATE_p ; real_T Integrator_CSTATE_o ; real_T StateSpace_CSTATE ;
real_T StateSpace_CSTATE_n ; real_T Integrator_CSTATE_j ; real_T
Integrator_CSTATE_i4 ; real_T VariableTransportDelay_CSTATE ; real_T
integrator_CSTATE ; real_T TransferFcn_CSTATE ; real_T Integrator_x1_CSTATE ;
real_T Integrator_x2_CSTATE ; real_T Integrator_CSTATE_h ; real_T
Integrator_CSTATE_nh ; real_T VariableTransportDelay_CSTATE_f ; real_T
integrator_CSTATE_g ; real_T TransferFcn_CSTATE_l ; real_T
Integrator_x1_CSTATE_j ; real_T Integrator_x2_CSTATE_m ; real_T
Integrator_CSTATE_a ; real_T Integrator_CSTATE_m ; real_T
VariableTransportDelay_CSTATE_j ; real_T integrator_CSTATE_d ; real_T
TransferFcn_CSTATE_f ; real_T Integrator_x1_CSTATE_m ; real_T
Integrator_x2_CSTATE_g ; real_T Integrator_CSTATE_c ; real_T
Integrator_CSTATE_f ; real_T VariableTransportDelay_CSTATE_g ; real_T
integrator_CSTATE_m ; real_T TransferFcn_CSTATE_a ; real_T
Integrator_x1_CSTATE_f ; real_T Integrator_x2_CSTATE_o ; real_T
Integrator_CSTATE_c0 ; real_T Integrator_CSTATE_b ; real_T
VariableTransportDelay_CSTATE_o ; real_T integrator_CSTATE_o ; real_T
TransferFcn_CSTATE_ac ; real_T Integrator_x1_CSTATE_k ; real_T
Integrator_x2_CSTATE_f ; real_T Integrator_CSTATE_pq ; real_T
Integrator_CSTATE_jf ; real_T VariableTransportDelay_CSTATE_l ; real_T
integrator_CSTATE_a ; real_T TransferFcn_CSTATE_k ; real_T
Integrator_x1_CSTATE_ma ; real_T Integrator_x2_CSTATE_p ; real_T
Integrator_CSTATE_oo ; real_T Integrator_CSTATE_pf ; real_T
VariableTransportDelay_CSTATE_d ; real_T integrator_CSTATE_p ; real_T
TransferFcn_CSTATE_m ; real_T Integrator_x1_CSTATE_a ; real_T
Integrator_x2_CSTATE_a ; real_T Integrator_CSTATE_d ; real_T
Integrator_CSTATE_jn ; real_T VariableTransportDelay_CSTATE_jz ; real_T
integrator_CSTATE_j ; real_T TransferFcn_CSTATE_e ; real_T
Integrator_x1_CSTATE_c ; real_T Integrator_x2_CSTATE_oa ; real_T
Integrator_CSTATE_nj ; real_T Integrator_CSTATE_fu ; real_T
VariableTransportDelay_CSTATE_b ; real_T integrator_CSTATE_mw ; real_T
TransferFcn_CSTATE_d ; real_T Integrator_x1_CSTATE_n ; real_T
Integrator_x2_CSTATE_gi ; XDot_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_c ; XDot_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_k ; XDot_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_g ; XDot_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_b2 ; XDot_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_m ; XDot_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_l ; XDot_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_b ; XDot_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_a ; XDot_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl ; } XDot_dVOC_monitor_network1_T ; typedef struct {
boolean_T Integrator_CSTATE ; boolean_T Integrator_CSTATE_i ; boolean_T
Integrator1_CSTATE ; boolean_T Integrator3_CSTATE ; boolean_T
TransferFcn4_CSTATE ; boolean_T Integrator1_CSTATE_m ; boolean_T
Integrator1_CSTATE_f ; boolean_T Integrator_CSTATE_n ; boolean_T
Integrator_CSTATE_p ; boolean_T Integrator1_CSTATE_i ; boolean_T
Integrator3_CSTATE_o ; boolean_T TransferFcn4_CSTATE_m ; boolean_T
Integrator1_CSTATE_g ; boolean_T Integrator1_CSTATE_b ; boolean_T
Internal_CSTATE ; boolean_T Internal_CSTATE_n ; boolean_T TransferFcn2_CSTATE
; boolean_T TransferFcn4_CSTATE_l ; boolean_T TransferFcn2_CSTATE_a ;
boolean_T TransferFcn4_CSTATE_n ; boolean_T Internal_CSTATE_p ; boolean_T
Integrator_CSTATE_o ; boolean_T StateSpace_CSTATE ; boolean_T
StateSpace_CSTATE_n ; boolean_T Integrator_CSTATE_j ; boolean_T
Integrator_CSTATE_i4 ; boolean_T VariableTransportDelay_CSTATE ; boolean_T
integrator_CSTATE ; boolean_T TransferFcn_CSTATE ; boolean_T
Integrator_x1_CSTATE ; boolean_T Integrator_x2_CSTATE ; boolean_T
Integrator_CSTATE_h ; boolean_T Integrator_CSTATE_nh ; boolean_T
VariableTransportDelay_CSTATE_f ; boolean_T integrator_CSTATE_g ; boolean_T
TransferFcn_CSTATE_l ; boolean_T Integrator_x1_CSTATE_j ; boolean_T
Integrator_x2_CSTATE_m ; boolean_T Integrator_CSTATE_a ; boolean_T
Integrator_CSTATE_m ; boolean_T VariableTransportDelay_CSTATE_j ; boolean_T
integrator_CSTATE_d ; boolean_T TransferFcn_CSTATE_f ; boolean_T
Integrator_x1_CSTATE_m ; boolean_T Integrator_x2_CSTATE_g ; boolean_T
Integrator_CSTATE_c ; boolean_T Integrator_CSTATE_f ; boolean_T
VariableTransportDelay_CSTATE_g ; boolean_T integrator_CSTATE_m ; boolean_T
TransferFcn_CSTATE_a ; boolean_T Integrator_x1_CSTATE_f ; boolean_T
Integrator_x2_CSTATE_o ; boolean_T Integrator_CSTATE_c0 ; boolean_T
Integrator_CSTATE_b ; boolean_T VariableTransportDelay_CSTATE_o ; boolean_T
integrator_CSTATE_o ; boolean_T TransferFcn_CSTATE_ac ; boolean_T
Integrator_x1_CSTATE_k ; boolean_T Integrator_x2_CSTATE_f ; boolean_T
Integrator_CSTATE_pq ; boolean_T Integrator_CSTATE_jf ; boolean_T
VariableTransportDelay_CSTATE_l ; boolean_T integrator_CSTATE_a ; boolean_T
TransferFcn_CSTATE_k ; boolean_T Integrator_x1_CSTATE_ma ; boolean_T
Integrator_x2_CSTATE_p ; boolean_T Integrator_CSTATE_oo ; boolean_T
Integrator_CSTATE_pf ; boolean_T VariableTransportDelay_CSTATE_d ; boolean_T
integrator_CSTATE_p ; boolean_T TransferFcn_CSTATE_m ; boolean_T
Integrator_x1_CSTATE_a ; boolean_T Integrator_x2_CSTATE_a ; boolean_T
Integrator_CSTATE_d ; boolean_T Integrator_CSTATE_jn ; boolean_T
VariableTransportDelay_CSTATE_jz ; boolean_T integrator_CSTATE_j ; boolean_T
TransferFcn_CSTATE_e ; boolean_T Integrator_x1_CSTATE_c ; boolean_T
Integrator_x2_CSTATE_oa ; boolean_T Integrator_CSTATE_nj ; boolean_T
Integrator_CSTATE_fu ; boolean_T VariableTransportDelay_CSTATE_b ; boolean_T
integrator_CSTATE_mw ; boolean_T TransferFcn_CSTATE_d ; boolean_T
Integrator_x1_CSTATE_n ; boolean_T Integrator_x2_CSTATE_gi ;
XDis_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_c ;
XDis_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_k ;
XDis_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_g ;
XDis_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b2 ;
XDis_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_m ;
XDis_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_l ;
XDis_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b ;
XDis_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_a ;
XDis_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl ; }
XDis_dVOC_monitor_network1_T ; typedef struct { real_T Integrator_CSTATE ;
real_T Integrator_CSTATE_i ; real_T Integrator1_CSTATE ; real_T
Integrator3_CSTATE ; real_T TransferFcn4_CSTATE ; real_T Integrator1_CSTATE_m
; real_T Integrator1_CSTATE_f ; real_T Integrator_CSTATE_n ; real_T
Integrator_CSTATE_p ; real_T Integrator1_CSTATE_i ; real_T
Integrator3_CSTATE_o ; real_T TransferFcn4_CSTATE_m ; real_T
Integrator1_CSTATE_g ; real_T Integrator1_CSTATE_b ; real_T Internal_CSTATE ;
real_T Internal_CSTATE_n ; real_T TransferFcn2_CSTATE ; real_T
TransferFcn4_CSTATE_l ; real_T TransferFcn2_CSTATE_a ; real_T
TransferFcn4_CSTATE_n ; real_T Internal_CSTATE_p ; real_T Integrator_CSTATE_o
; real_T StateSpace_CSTATE ; real_T StateSpace_CSTATE_n ; real_T
Integrator_CSTATE_j ; real_T Integrator_CSTATE_i4 ; real_T
VariableTransportDelay_CSTATE ; real_T integrator_CSTATE ; real_T
TransferFcn_CSTATE ; real_T Integrator_x1_CSTATE ; real_T
Integrator_x2_CSTATE ; real_T Integrator_CSTATE_h ; real_T
Integrator_CSTATE_nh ; real_T VariableTransportDelay_CSTATE_f ; real_T
integrator_CSTATE_g ; real_T TransferFcn_CSTATE_l ; real_T
Integrator_x1_CSTATE_j ; real_T Integrator_x2_CSTATE_m ; real_T
Integrator_CSTATE_a ; real_T Integrator_CSTATE_m ; real_T
VariableTransportDelay_CSTATE_j ; real_T integrator_CSTATE_d ; real_T
TransferFcn_CSTATE_f ; real_T Integrator_x1_CSTATE_m ; real_T
Integrator_x2_CSTATE_g ; real_T Integrator_CSTATE_c ; real_T
Integrator_CSTATE_f ; real_T VariableTransportDelay_CSTATE_g ; real_T
integrator_CSTATE_m ; real_T TransferFcn_CSTATE_a ; real_T
Integrator_x1_CSTATE_f ; real_T Integrator_x2_CSTATE_o ; real_T
Integrator_CSTATE_c0 ; real_T Integrator_CSTATE_b ; real_T
VariableTransportDelay_CSTATE_o ; real_T integrator_CSTATE_o ; real_T
TransferFcn_CSTATE_ac ; real_T Integrator_x1_CSTATE_k ; real_T
Integrator_x2_CSTATE_f ; real_T Integrator_CSTATE_pq ; real_T
Integrator_CSTATE_jf ; real_T VariableTransportDelay_CSTATE_l ; real_T
integrator_CSTATE_a ; real_T TransferFcn_CSTATE_k ; real_T
Integrator_x1_CSTATE_ma ; real_T Integrator_x2_CSTATE_p ; real_T
Integrator_CSTATE_oo ; real_T Integrator_CSTATE_pf ; real_T
VariableTransportDelay_CSTATE_d ; real_T integrator_CSTATE_p ; real_T
TransferFcn_CSTATE_m ; real_T Integrator_x1_CSTATE_a ; real_T
Integrator_x2_CSTATE_a ; real_T Integrator_CSTATE_d ; real_T
Integrator_CSTATE_jn ; real_T VariableTransportDelay_CSTATE_jz ; real_T
integrator_CSTATE_j ; real_T TransferFcn_CSTATE_e ; real_T
Integrator_x1_CSTATE_c ; real_T Integrator_x2_CSTATE_oa ; real_T
Integrator_CSTATE_nj ; real_T Integrator_CSTATE_fu ; real_T
VariableTransportDelay_CSTATE_b ; real_T integrator_CSTATE_mw ; real_T
TransferFcn_CSTATE_d ; real_T Integrator_x1_CSTATE_n ; real_T
Integrator_x2_CSTATE_gi ;
XAbsTol_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_c ;
XAbsTol_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_k ;
XAbsTol_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_g ;
XAbsTol_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b2
; XAbsTol_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_m
; XAbsTol_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_l
; XAbsTol_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b
; XAbsTol_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_a
; XAbsTol_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl ;
} CStateAbsTol_dVOC_monitor_network1_T ; typedef struct { real_T
Integrator_CSTATE ; real_T Integrator_CSTATE_i ; real_T Integrator1_CSTATE ;
real_T Integrator3_CSTATE ; real_T TransferFcn4_CSTATE ; real_T
Integrator1_CSTATE_m ; real_T Integrator1_CSTATE_f ; real_T
Integrator_CSTATE_n ; real_T Integrator_CSTATE_p ; real_T
Integrator1_CSTATE_i ; real_T Integrator3_CSTATE_o ; real_T
TransferFcn4_CSTATE_m ; real_T Integrator1_CSTATE_g ; real_T
Integrator1_CSTATE_b ; real_T Internal_CSTATE ; real_T Internal_CSTATE_n ;
real_T TransferFcn2_CSTATE ; real_T TransferFcn4_CSTATE_l ; real_T
TransferFcn2_CSTATE_a ; real_T TransferFcn4_CSTATE_n ; real_T
Internal_CSTATE_p ; real_T Integrator_CSTATE_o ; real_T StateSpace_CSTATE ;
real_T StateSpace_CSTATE_n ; real_T Integrator_CSTATE_j ; real_T
Integrator_CSTATE_i4 ; real_T VariableTransportDelay_CSTATE ; real_T
integrator_CSTATE ; real_T TransferFcn_CSTATE ; real_T Integrator_x1_CSTATE ;
real_T Integrator_x2_CSTATE ; real_T Integrator_CSTATE_h ; real_T
Integrator_CSTATE_nh ; real_T VariableTransportDelay_CSTATE_f ; real_T
integrator_CSTATE_g ; real_T TransferFcn_CSTATE_l ; real_T
Integrator_x1_CSTATE_j ; real_T Integrator_x2_CSTATE_m ; real_T
Integrator_CSTATE_a ; real_T Integrator_CSTATE_m ; real_T
VariableTransportDelay_CSTATE_j ; real_T integrator_CSTATE_d ; real_T
TransferFcn_CSTATE_f ; real_T Integrator_x1_CSTATE_m ; real_T
Integrator_x2_CSTATE_g ; real_T Integrator_CSTATE_c ; real_T
Integrator_CSTATE_f ; real_T VariableTransportDelay_CSTATE_g ; real_T
integrator_CSTATE_m ; real_T TransferFcn_CSTATE_a ; real_T
Integrator_x1_CSTATE_f ; real_T Integrator_x2_CSTATE_o ; real_T
Integrator_CSTATE_c0 ; real_T Integrator_CSTATE_b ; real_T
VariableTransportDelay_CSTATE_o ; real_T integrator_CSTATE_o ; real_T
TransferFcn_CSTATE_ac ; real_T Integrator_x1_CSTATE_k ; real_T
Integrator_x2_CSTATE_f ; real_T Integrator_CSTATE_pq ; real_T
Integrator_CSTATE_jf ; real_T VariableTransportDelay_CSTATE_l ; real_T
integrator_CSTATE_a ; real_T TransferFcn_CSTATE_k ; real_T
Integrator_x1_CSTATE_ma ; real_T Integrator_x2_CSTATE_p ; real_T
Integrator_CSTATE_oo ; real_T Integrator_CSTATE_pf ; real_T
VariableTransportDelay_CSTATE_d ; real_T integrator_CSTATE_p ; real_T
TransferFcn_CSTATE_m ; real_T Integrator_x1_CSTATE_a ; real_T
Integrator_x2_CSTATE_a ; real_T Integrator_CSTATE_d ; real_T
Integrator_CSTATE_jn ; real_T VariableTransportDelay_CSTATE_jz ; real_T
integrator_CSTATE_j ; real_T TransferFcn_CSTATE_e ; real_T
Integrator_x1_CSTATE_c ; real_T Integrator_x2_CSTATE_oa ; real_T
Integrator_CSTATE_nj ; real_T Integrator_CSTATE_fu ; real_T
VariableTransportDelay_CSTATE_b ; real_T integrator_CSTATE_mw ; real_T
TransferFcn_CSTATE_d ; real_T Integrator_x1_CSTATE_n ; real_T
Integrator_x2_CSTATE_gi ; XPtMin_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_c ; XPtMin_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_k ; XPtMin_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_g ; XPtMin_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_b2 ; XPtMin_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_m ; XPtMin_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_l ; XPtMin_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_b ; XPtMin_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_a ; XPtMin_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl ; } CXPtMin_dVOC_monitor_network1_T ; typedef struct {
real_T Integrator_CSTATE ; real_T Integrator_CSTATE_i ; real_T
Integrator1_CSTATE ; real_T Integrator3_CSTATE ; real_T TransferFcn4_CSTATE ;
real_T Integrator1_CSTATE_m ; real_T Integrator1_CSTATE_f ; real_T
Integrator_CSTATE_n ; real_T Integrator_CSTATE_p ; real_T
Integrator1_CSTATE_i ; real_T Integrator3_CSTATE_o ; real_T
TransferFcn4_CSTATE_m ; real_T Integrator1_CSTATE_g ; real_T
Integrator1_CSTATE_b ; real_T Internal_CSTATE ; real_T Internal_CSTATE_n ;
real_T TransferFcn2_CSTATE ; real_T TransferFcn4_CSTATE_l ; real_T
TransferFcn2_CSTATE_a ; real_T TransferFcn4_CSTATE_n ; real_T
Internal_CSTATE_p ; real_T Integrator_CSTATE_o ; real_T StateSpace_CSTATE ;
real_T StateSpace_CSTATE_n ; real_T Integrator_CSTATE_j ; real_T
Integrator_CSTATE_i4 ; real_T VariableTransportDelay_CSTATE ; real_T
integrator_CSTATE ; real_T TransferFcn_CSTATE ; real_T Integrator_x1_CSTATE ;
real_T Integrator_x2_CSTATE ; real_T Integrator_CSTATE_h ; real_T
Integrator_CSTATE_nh ; real_T VariableTransportDelay_CSTATE_f ; real_T
integrator_CSTATE_g ; real_T TransferFcn_CSTATE_l ; real_T
Integrator_x1_CSTATE_j ; real_T Integrator_x2_CSTATE_m ; real_T
Integrator_CSTATE_a ; real_T Integrator_CSTATE_m ; real_T
VariableTransportDelay_CSTATE_j ; real_T integrator_CSTATE_d ; real_T
TransferFcn_CSTATE_f ; real_T Integrator_x1_CSTATE_m ; real_T
Integrator_x2_CSTATE_g ; real_T Integrator_CSTATE_c ; real_T
Integrator_CSTATE_f ; real_T VariableTransportDelay_CSTATE_g ; real_T
integrator_CSTATE_m ; real_T TransferFcn_CSTATE_a ; real_T
Integrator_x1_CSTATE_f ; real_T Integrator_x2_CSTATE_o ; real_T
Integrator_CSTATE_c0 ; real_T Integrator_CSTATE_b ; real_T
VariableTransportDelay_CSTATE_o ; real_T integrator_CSTATE_o ; real_T
TransferFcn_CSTATE_ac ; real_T Integrator_x1_CSTATE_k ; real_T
Integrator_x2_CSTATE_f ; real_T Integrator_CSTATE_pq ; real_T
Integrator_CSTATE_jf ; real_T VariableTransportDelay_CSTATE_l ; real_T
integrator_CSTATE_a ; real_T TransferFcn_CSTATE_k ; real_T
Integrator_x1_CSTATE_ma ; real_T Integrator_x2_CSTATE_p ; real_T
Integrator_CSTATE_oo ; real_T Integrator_CSTATE_pf ; real_T
VariableTransportDelay_CSTATE_d ; real_T integrator_CSTATE_p ; real_T
TransferFcn_CSTATE_m ; real_T Integrator_x1_CSTATE_a ; real_T
Integrator_x2_CSTATE_a ; real_T Integrator_CSTATE_d ; real_T
Integrator_CSTATE_jn ; real_T VariableTransportDelay_CSTATE_jz ; real_T
integrator_CSTATE_j ; real_T TransferFcn_CSTATE_e ; real_T
Integrator_x1_CSTATE_c ; real_T Integrator_x2_CSTATE_oa ; real_T
Integrator_CSTATE_nj ; real_T Integrator_CSTATE_fu ; real_T
VariableTransportDelay_CSTATE_b ; real_T integrator_CSTATE_mw ; real_T
TransferFcn_CSTATE_d ; real_T Integrator_x1_CSTATE_n ; real_T
Integrator_x2_CSTATE_gi ; XPtMax_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_c ; XPtMax_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_k ; XPtMax_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_g ; XPtMax_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_b2 ; XPtMax_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_m ; XPtMax_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_l ; XPtMax_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_b ; XPtMax_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl_a ; XPtMax_AutomaticGainControl_dVOC_monitor_network1_T
AutomaticGainControl ; } CXPtMax_dVOC_monitor_network1_T ; typedef struct {
real_T Saturation_UprLim_ZC ; real_T Saturation_LwrLim_ZC ; real_T
Switch_SwitchCond_ZC ; real_T Saturation_UprLim_ZC_n ; real_T
Saturation_LwrLim_ZC_e ; real_T Switch_SwitchCond_ZC_h ; real_T
Integrator_IntgUpLimit_ZC ; real_T Integrator_IntgLoLimit_ZC ; real_T
Integrator_LeaveSaturate_ZC ; real_T LowerRelop1_RelopInput_ZC ; real_T
UpperRelop_RelopInput_ZC ; real_T VImin_UprLim_ZC ; real_T VImin_LwrLim_ZC ;
real_T RelationalOperator_RelopInput_ZC ; real_T Integrator_Reset_ZC ; real_T
Integrator_IntgUpLimit_ZC_e ; real_T Integrator_IntgLoLimit_ZC_e ; real_T
Integrator_LeaveSaturate_ZC_j ; real_T HitCrossing_HitNoOutput_ZC ; real_T
Integrator_IntgUpLimit_ZC_h ; real_T Integrator_IntgLoLimit_ZC_f ; real_T
Integrator_LeaveSaturate_ZC_g ; real_T RelationalOperator_RelopInput_ZC_g ;
real_T Saturation2_UprLim_ZC ; real_T Saturation2_LwrLim_ZC ; real_T
RelationalOperator_RelopInput_ZC_h ; real_T Integrator_Reset_ZC_d ; real_T
Integrator_IntgUpLimit_ZC_d ; real_T Integrator_IntgLoLimit_ZC_k ; real_T
Integrator_LeaveSaturate_ZC_c ; real_T HitCrossing_HitNoOutput_ZC_m ; real_T
Integrator_IntgUpLimit_ZC_i ; real_T Integrator_IntgLoLimit_ZC_l ; real_T
Integrator_LeaveSaturate_ZC_k ; real_T RelationalOperator_RelopInput_ZC_go ;
real_T Saturation2_UprLim_ZC_l ; real_T Saturation2_LwrLim_ZC_h ; real_T
RelationalOperator_RelopInput_ZC_hm ; real_T Integrator_Reset_ZC_l ; real_T
Integrator_IntgUpLimit_ZC_j ; real_T Integrator_IntgLoLimit_ZC_i ; real_T
Integrator_LeaveSaturate_ZC_m ; real_T HitCrossing_HitNoOutput_ZC_f ; real_T
Integrator_IntgUpLimit_ZC_a ; real_T Integrator_IntgLoLimit_ZC_n ; real_T
Integrator_LeaveSaturate_ZC_b ; real_T RelationalOperator_RelopInput_ZC_i ;
real_T Saturation2_UprLim_ZC_o ; real_T Saturation2_LwrLim_ZC_o ; real_T
RelationalOperator_RelopInput_ZC_m ; real_T Integrator_Reset_ZC_j ; real_T
Integrator_IntgUpLimit_ZC_e3 ; real_T Integrator_IntgLoLimit_ZC_h ; real_T
Integrator_LeaveSaturate_ZC_i ; real_T HitCrossing_HitNoOutput_ZC_b ; real_T
Integrator_IntgUpLimit_ZC_o ; real_T Integrator_IntgLoLimit_ZC_lf ; real_T
Integrator_LeaveSaturate_ZC_cf ; real_T RelationalOperator_RelopInput_ZC_a ;
real_T Saturation2_UprLim_ZC_i ; real_T Saturation2_LwrLim_ZC_e ; real_T
RelationalOperator_RelopInput_ZC_l ; real_T Integrator_Reset_ZC_b ; real_T
Integrator_IntgUpLimit_ZC_eb ; real_T Integrator_IntgLoLimit_ZC_g ; real_T
Integrator_LeaveSaturate_ZC_a ; real_T HitCrossing_HitNoOutput_ZC_mb ; real_T
Integrator_IntgUpLimit_ZC_el ; real_T Integrator_IntgLoLimit_ZC_a ; real_T
Integrator_LeaveSaturate_ZC_o ; real_T RelationalOperator_RelopInput_ZC_lg ;
real_T Saturation2_UprLim_ZC_m ; real_T Saturation2_LwrLim_ZC_ek ; real_T
RelationalOperator_RelopInput_ZC_f ; real_T Integrator_Reset_ZC_e ; real_T
Integrator_IntgUpLimit_ZC_g ; real_T Integrator_IntgLoLimit_ZC_k1 ; real_T
Integrator_LeaveSaturate_ZC_l ; real_T HitCrossing_HitNoOutput_ZC_d ; real_T
Integrator_IntgUpLimit_ZC_df ; real_T Integrator_IntgLoLimit_ZC_d ; real_T
Integrator_LeaveSaturate_ZC_n ; real_T RelationalOperator_RelopInput_ZC_j ;
real_T Saturation2_UprLim_ZC_o5 ; real_T Saturation2_LwrLim_ZC_l ; real_T
RelationalOperator_RelopInput_ZC_ii ; real_T Integrator_Reset_ZC_ec ; real_T
Integrator_IntgUpLimit_ZC_p ; real_T Integrator_IntgLoLimit_ZC_h3 ; real_T
Integrator_LeaveSaturate_ZC_p ; real_T HitCrossing_HitNoOutput_ZC_a ; real_T
Integrator_IntgUpLimit_ZC_b ; real_T Integrator_IntgLoLimit_ZC_c ; real_T
Integrator_LeaveSaturate_ZC_oq ; real_T RelationalOperator_RelopInput_ZC_b ;
real_T Saturation2_UprLim_ZC_d ; real_T Saturation2_LwrLim_ZC_p ; real_T
RelationalOperator_RelopInput_ZC_j1 ; real_T Integrator_Reset_ZC_i ; real_T
Integrator_IntgUpLimit_ZC_f ; real_T Integrator_IntgLoLimit_ZC_c0 ; real_T
Integrator_LeaveSaturate_ZC_oe ; real_T HitCrossing_HitNoOutput_ZC_i ; real_T
Integrator_IntgUpLimit_ZC_iv ; real_T Integrator_IntgLoLimit_ZC_fj ; real_T
Integrator_LeaveSaturate_ZC_km ; real_T RelationalOperator_RelopInput_ZC_gi ;
real_T Saturation2_UprLim_ZC_h ; real_T Saturation2_LwrLim_ZC_f ; real_T
RelationalOperator_RelopInput_ZC_am ; real_T Integrator_Reset_ZC_n ; real_T
Integrator_IntgUpLimit_ZC_fr ; real_T Integrator_IntgLoLimit_ZC_nn ; real_T
Integrator_LeaveSaturate_ZC_kf ; real_T HitCrossing_HitNoOutput_ZC_c ; real_T
Integrator_IntgUpLimit_ZC_d4 ; real_T Integrator_IntgLoLimit_ZC_ia ; real_T
Integrator_LeaveSaturate_ZC_e ; real_T RelationalOperator_RelopInput_ZC_ab ;
real_T Saturation2_UprLim_ZC_f ; real_T Saturation2_LwrLim_ZC_i ;
ZCV_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_c ;
ZCV_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_k ;
ZCV_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_g ;
ZCV_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b2 ;
ZCV_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_m ;
ZCV_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_l ;
ZCV_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b ;
ZCV_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_a ;
ZCV_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl ; }
ZCV_dVOC_monitor_network1_T ; typedef struct { ZCSigState
Saturation_UprLim_ZCE ; ZCSigState Saturation_LwrLim_ZCE ; ZCSigState
Switch_SwitchCond_ZCE ; ZCSigState Saturation_UprLim_ZCE_b ; ZCSigState
Saturation_LwrLim_ZCE_p ; ZCSigState Switch_SwitchCond_ZCE_n ; ZCSigState
Integrator_IntgUpLimit_ZCE ; ZCSigState Integrator_IntgLoLimit_ZCE ;
ZCSigState Integrator_LeaveSaturate_ZCE ; ZCSigState
LowerRelop1_RelopInput_ZCE ; ZCSigState UpperRelop_RelopInput_ZCE ;
ZCSigState VImin_UprLim_ZCE ; ZCSigState VImin_LwrLim_ZCE ; ZCSigState
RelationalOperator_RelopInput_ZCE ; ZCSigState Integrator_Reset_ZCE ;
ZCSigState Integrator_IntgUpLimit_ZCE_a ; ZCSigState
Integrator_IntgLoLimit_ZCE_p ; ZCSigState Integrator_LeaveSaturate_ZCE_h ;
ZCSigState HitCrossing_HitNoOutput_ZCE ; ZCSigState
Integrator_IntgUpLimit_ZCE_f ; ZCSigState Integrator_IntgLoLimit_ZCE_l ;
ZCSigState Integrator_LeaveSaturate_ZCE_k ; ZCSigState
RelationalOperator_RelopInput_ZCE_j ; ZCSigState Saturation2_UprLim_ZCE ;
ZCSigState Saturation2_LwrLim_ZCE ; ZCSigState
RelationalOperator_RelopInput_ZCE_i ; ZCSigState Integrator_Reset_ZCE_p ;
ZCSigState Integrator_IntgUpLimit_ZCE_c ; ZCSigState
Integrator_IntgLoLimit_ZCE_c ; ZCSigState Integrator_LeaveSaturate_ZCE_p ;
ZCSigState HitCrossing_HitNoOutput_ZCE_n ; ZCSigState
Integrator_IntgUpLimit_ZCE_m ; ZCSigState Integrator_IntgLoLimit_ZCE_o ;
ZCSigState Integrator_LeaveSaturate_ZCE_m ; ZCSigState
RelationalOperator_RelopInput_ZCE_p ; ZCSigState Saturation2_UprLim_ZCE_i ;
ZCSigState Saturation2_LwrLim_ZCE_k ; ZCSigState
RelationalOperator_RelopInput_ZCE_g ; ZCSigState Integrator_Reset_ZCE_i ;
ZCSigState Integrator_IntgUpLimit_ZCE_g ; ZCSigState
Integrator_IntgLoLimit_ZCE_f ; ZCSigState Integrator_LeaveSaturate_ZCE_me ;
ZCSigState HitCrossing_HitNoOutput_ZCE_f ; ZCSigState
Integrator_IntgUpLimit_ZCE_d ; ZCSigState Integrator_IntgLoLimit_ZCE_d ;
ZCSigState Integrator_LeaveSaturate_ZCE_o ; ZCSigState
RelationalOperator_RelopInput_ZCE_b ; ZCSigState Saturation2_UprLim_ZCE_g ;
ZCSigState Saturation2_LwrLim_ZCE_p ; ZCSigState
RelationalOperator_RelopInput_ZCE_m ; ZCSigState Integrator_Reset_ZCE_l ;
ZCSigState Integrator_IntgUpLimit_ZCE_af ; ZCSigState
Integrator_IntgLoLimit_ZCE_i ; ZCSigState Integrator_LeaveSaturate_ZCE_hw ;
ZCSigState HitCrossing_HitNoOutput_ZCE_p ; ZCSigState
Integrator_IntgUpLimit_ZCE_p ; ZCSigState Integrator_IntgLoLimit_ZCE_fn ;
ZCSigState Integrator_LeaveSaturate_ZCE_on ; ZCSigState
RelationalOperator_RelopInput_ZCE_pp ; ZCSigState Saturation2_UprLim_ZCE_f ;
ZCSigState Saturation2_LwrLim_ZCE_b ; ZCSigState
RelationalOperator_RelopInput_ZCE_pj ; ZCSigState Integrator_Reset_ZCE_o ;
ZCSigState Integrator_IntgUpLimit_ZCE_o ; ZCSigState
Integrator_IntgLoLimit_ZCE_n ; ZCSigState Integrator_LeaveSaturate_ZCE_f ;
ZCSigState HitCrossing_HitNoOutput_ZCE_j ; ZCSigState
Integrator_IntgUpLimit_ZCE_dh ; ZCSigState Integrator_IntgLoLimit_ZCE_m ;
ZCSigState Integrator_LeaveSaturate_ZCE_hl ; ZCSigState
RelationalOperator_RelopInput_ZCE_h ; ZCSigState Saturation2_UprLim_ZCE_fh ;
ZCSigState Saturation2_LwrLim_ZCE_c ; ZCSigState
RelationalOperator_RelopInput_ZCE_k ; ZCSigState Integrator_Reset_ZCE_op ;
ZCSigState Integrator_IntgUpLimit_ZCE_n ; ZCSigState
Integrator_IntgLoLimit_ZCE_h ; ZCSigState Integrator_LeaveSaturate_ZCE_fm ;
ZCSigState HitCrossing_HitNoOutput_ZCE_e ; ZCSigState
Integrator_IntgUpLimit_ZCE_h ; ZCSigState Integrator_IntgLoLimit_ZCE_e ;
ZCSigState Integrator_LeaveSaturate_ZCE_f0 ; ZCSigState
RelationalOperator_RelopInput_ZCE_e ; ZCSigState Saturation2_UprLim_ZCE_n ;
ZCSigState Saturation2_LwrLim_ZCE_i ; ZCSigState
RelationalOperator_RelopInput_ZCE_bn ; ZCSigState Integrator_Reset_ZCE_m ;
ZCSigState Integrator_IntgUpLimit_ZCE_j ; ZCSigState
Integrator_IntgLoLimit_ZCE_h3 ; ZCSigState Integrator_LeaveSaturate_ZCE_pv ;
ZCSigState HitCrossing_HitNoOutput_ZCE_eg ; ZCSigState
Integrator_IntgUpLimit_ZCE_je ; ZCSigState Integrator_IntgLoLimit_ZCE_k ;
ZCSigState Integrator_LeaveSaturate_ZCE_hlg ; ZCSigState
RelationalOperator_RelopInput_ZCE_c ; ZCSigState Saturation2_UprLim_ZCE_h ;
ZCSigState Saturation2_LwrLim_ZCE_d ; ZCSigState
RelationalOperator_RelopInput_ZCE_d ; ZCSigState Integrator_Reset_ZCE_os ;
ZCSigState Integrator_IntgUpLimit_ZCE_nh ; ZCSigState
Integrator_IntgLoLimit_ZCE_fnj ; ZCSigState Integrator_LeaveSaturate_ZCE_l ;
ZCSigState HitCrossing_HitNoOutput_ZCE_a ; ZCSigState
Integrator_IntgUpLimit_ZCE_os ; ZCSigState Integrator_IntgLoLimit_ZCE_a ;
ZCSigState Integrator_LeaveSaturate_ZCE_lq ; ZCSigState
RelationalOperator_RelopInput_ZCE_mo ; ZCSigState Saturation2_UprLim_ZCE_nk ;
ZCSigState Saturation2_LwrLim_ZCE_j ; ZCSigState
RelationalOperator_RelopInput_ZCE_dg ; ZCSigState Integrator_Reset_ZCE_c ;
ZCSigState Integrator_IntgUpLimit_ZCE_df ; ZCSigState
Integrator_IntgLoLimit_ZCE_j ; ZCSigState Integrator_LeaveSaturate_ZCE_a ;
ZCSigState HitCrossing_HitNoOutput_ZCE_pc ; ZCSigState
Integrator_IntgUpLimit_ZCE_cf ; ZCSigState Integrator_IntgLoLimit_ZCE_js ;
ZCSigState Integrator_LeaveSaturate_ZCE_mn ; ZCSigState
RelationalOperator_RelopInput_ZCE_a ; ZCSigState Saturation2_UprLim_ZCE_b ;
ZCSigState Saturation2_LwrLim_ZCE_f ;
ZCE_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_c ;
ZCE_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_k ;
ZCE_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_g ;
ZCE_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b2 ;
ZCE_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_m ;
ZCE_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_l ;
ZCE_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b ;
ZCE_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_a ;
ZCE_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl ; }
PrevZCX_dVOC_monitor_network1_T ; struct
P_Subsystempi2delay_dVOC_monitor_network1_T_ { real_T P_0 [ 2 ] ; } ; struct
P_Subsystem1_dVOC_monitor_network1_T_ { real_T P_0 [ 2 ] ; } ; struct
P_Subsystempi2delay_dVOC_monitor_network1_g_T_ { real_T P_0 [ 2 ] ; } ;
struct P_Subsystem1_dVOC_monitor_network1_a_T_ { real_T P_0 [ 2 ] ; } ;
struct P_AutomaticGainControl_dVOC_monitor_network1_T_ { real_T P_0 ; real_T
P_1 ; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T
P_7 ; real_T P_8 ; real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ;
real_T P_13 [ 9 ] ; real_T P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ;
real_T P_18 ; real_T P_19 ; real_T P_20 ; real_T P_21 ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1 ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay ; } ; struct
P_dVOC_monitor_network1_T_ { real_T P_0 ; real_T P_1 [ 5 ] ; real_T P_2 [ 5 ]
; real_T P_3 ; real_T P_4 [ 5 ] ; real_T P_5 [ 5 ] ; real_T P_6 ; real_T P_7
[ 5 ] ; real_T P_8 [ 5 ] ; real_T P_9 ; real_T P_10 [ 5 ] ; real_T P_11 [ 5 ]
; real_T P_12 ; real_T P_13 [ 5 ] ; real_T P_14 [ 5 ] ; real_T P_15 ; real_T
P_16 [ 5 ] ; real_T P_17 [ 5 ] ; real_T P_18 ; real_T P_19 [ 5 ] ; real_T
P_20 [ 5 ] ; real_T P_21 ; real_T P_22 [ 5 ] ; real_T P_23 [ 5 ] ; real_T
P_24 ; real_T P_25 [ 5 ] ; real_T P_26 [ 5 ] ; real_T P_27 ; real_T P_28 [ 5
] ; real_T P_29 [ 5 ] ; real_T P_30 ; real_T P_31 [ 5 ] ; real_T P_32 [ 5 ] ;
real_T P_33 ; real_T P_34 [ 5 ] ; real_T P_35 [ 5 ] ; real_T P_36 ; real_T
P_37 ; real_T P_38 [ 2 ] ; real_T P_39 ; real_T P_40 [ 2 ] ; real_T P_41 [ 2
] ; real_T P_42 ; real_T P_43 ; real_T P_44 [ 3 ] ; real_T P_45 ; real_T P_46
; real_T P_47 ; real_T P_48 ; real_T P_49 [ 3 ] ; real_T P_50 ; real_T P_51 [
2 ] ; real_T P_52 [ 2 ] ; real_T P_53 ; real_T P_54 ; real_T P_55 [ 2 ] ;
real_T P_56 [ 25 ] ; real_T P_57 [ 25 ] ; real_T P_58 [ 25 ] ; real_T P_59 ;
real_T P_60 ; real_T P_61 ; real_T P_62 [ 5 ] ; real_T P_63 [ 5 ] ; real_T
P_64 ; real_T P_65 [ 5 ] ; real_T P_66 [ 5 ] ; real_T P_67 ; real_T P_68 [ 5
] ; real_T P_69 [ 5 ] ; real_T P_70 ; real_T P_71 ; real_T P_72 ; real_T P_73
[ 5 ] ; real_T P_74 ; real_T P_75 [ 5 ] ; real_T P_76 ; real_T P_77 ; real_T
P_78 ; real_T P_79 ; real_T P_80 ; real_T P_81 [ 9 ] ; real_T P_82 ; real_T
P_83 ; real_T P_84 ; real_T P_85 ; real_T P_86 ; real_T P_87 ; real_T P_88 ;
real_T P_89 ; real_T P_90 ; real_T P_91 [ 9 ] ; real_T P_92 ; real_T P_93 ;
real_T P_94 ; real_T P_95 [ 9 ] ; real_T P_96 ; real_T P_97 ; real_T P_98 ;
real_T P_99 ; real_T P_100 ; real_T P_101 ; real_T P_102 ; real_T P_103 ;
real_T P_104 ; real_T P_105 ; real_T P_106 ; real_T P_107 ; real_T P_108 ;
real_T P_109 [ 9 ] ; real_T P_110 ; real_T P_111 ; real_T P_112 ; real_T
P_113 ; real_T P_114 ; real_T P_115 ; real_T P_116 ; real_T P_117 ; real_T
P_118 [ 9 ] ; real_T P_119 ; real_T P_120 ; real_T P_121 ; real_T P_122 ;
real_T P_123 ; real_T P_124 ; real_T P_125 ; real_T P_126 ; real_T P_127 ;
real_T P_128 [ 9 ] ; real_T P_129 ; real_T P_130 ; real_T P_131 ; real_T
P_132 [ 9 ] ; real_T P_133 ; real_T P_134 ; real_T P_135 ; real_T P_136 ;
real_T P_137 ; real_T P_138 ; real_T P_139 ; real_T P_140 ; real_T P_141 ;
real_T P_142 ; real_T P_143 ; real_T P_144 ; real_T P_145 ; real_T P_146 [ 9
] ; real_T P_147 ; real_T P_148 ; real_T P_149 ; real_T P_150 ; real_T P_151
; real_T P_152 ; real_T P_153 ; real_T P_154 ; real_T P_155 ; real_T P_156 ;
real_T P_157 ; real_T P_158 ; real_T P_159 ; real_T P_160 ; real_T P_161 ;
real_T P_162 ; real_T P_163 ; real_T P_164 ; real_T P_165 [ 2 ] ; real_T
P_166 [ 6561 ] ; real_T P_167 [ 2 ] ; real_T P_168 [ 2025 ] ; real_T P_169 [
2 ] ; real_T P_170 [ 6156 ] ; real_T P_171 [ 2 ] ; real_T P_172 [ 1900 ] ;
real_T P_173 [ 2 ] ; real_T P_174 [ 81 ] ; real_T P_175 ; real_T P_176 ;
real_T P_177 ; real_T P_178 ; real_T P_179 ; real_T P_180 ; real_T P_181 ;
real_T P_182 [ 2 ] ; real_T P_183 ; real_T P_184 [ 3 ] ; real_T P_185 ;
real_T P_186 ; real_T P_187 ; real_T P_188 ; real_T P_189 ; real_T P_190 [ 18
] ; real_T P_191 [ 9 ] ; real_T P_192 ; real_T P_193 [ 9 ] ; real_T P_194 ;
real_T P_195 ; real_T P_196 ; real_T P_197 ; real_T P_198 [ 9 ] ; real_T
P_199 ; real_T P_200 [ 9 ] ; real_T P_201 ; real_T P_202 ; real_T P_203 ;
real_T P_204 ; real_T P_205 ; real_T P_206 ; real_T P_207 ; real_T P_208 ;
real_T P_209 ; real_T P_210 ; real_T P_211 ; real_T P_212 [ 9 ] ; real_T
P_213 ; real_T P_214 ; real_T P_215 [ 9 ] ; real_T P_216 ; real_T P_217 ;
real_T P_218 ; real_T P_219 ; real_T P_220 ; real_T P_221 ; real_T P_222 ;
real_T P_223 ; real_T P_224 ; real_T P_225 ; real_T P_226 ; real_T P_227 ;
real_T P_228 ; real_T P_229 ; real_T P_230 ; real_T P_231 ; real_T P_232 ;
real_T P_233 ; real_T P_234 ; real_T P_235 ; real_T P_236 ; real_T P_237 ;
real_T P_238 ; real_T P_239 ; real_T P_240 ; real_T P_241 ; real_T P_242 ;
real_T P_243 ; real_T P_244 ; real_T P_245 ; real_T P_246 ; real_T P_247 ;
real_T P_248 ; real_T P_249 ; real_T P_250 ; real_T P_251 ; real_T P_252 ;
real_T P_253 ; real_T P_254 ; real_T P_255 ; real_T P_256 ; real_T P_257 ;
real_T P_258 ; real_T P_259 ; real_T P_260 ; real_T P_261 ; real_T P_262 ;
real_T P_263 ; real_T P_264 ; real_T P_265 ; real_T P_266 ; real_T P_267 ;
real_T P_268 ; real_T P_269 ; real_T P_270 ; real_T P_271 ; real_T P_272 ;
real_T P_273 ; real_T P_274 ; real_T P_275 ; real_T P_276 ; real_T P_277 ;
real_T P_278 ; real_T P_279 ; real_T P_280 ; real_T P_281 ; real_T P_282 ;
real_T P_283 ; real_T P_284 ; real_T P_285 ; real_T P_286 ; real_T P_287 ;
real_T P_288 ; real_T P_289 ; real_T P_290 ; real_T P_291 ; real_T P_292 ;
real_T P_293 ; real_T P_294 ; real_T P_295 ; real_T P_296 ; real_T P_297 ;
real_T P_298 ; real_T P_299 ; real_T P_300 ; real_T P_301 ; real_T P_302 ;
real_T P_303 ; real_T P_304 ; real_T P_305 ; real_T P_306 ; real_T P_307 ;
real_T P_308 ; real_T P_309 ; real_T P_310 ; real_T P_311 ; real_T P_312 ;
real_T P_313 ; real_T P_314 ; real_T P_315 ; real_T P_316 ; real_T P_317 ;
real_T P_318 ; real_T P_319 ; real_T P_320 ; real_T P_321 ; real_T P_322 ;
real_T P_323 ; real_T P_324 ; real_T P_325 ; real_T P_326 ; real_T P_327 [ 2
] ; real_T P_328 ; real_T P_329 ; real_T P_330 ; real_T P_331 ; real_T P_332
; real_T P_333 ; real_T P_334 ; real_T P_335 ; real_T P_336 ; real_T P_337 ;
real_T P_338 ; real_T P_339 ; real_T P_340 ; real_T P_341 ; real_T P_342 ;
real_T P_343 ; real_T P_344 ; real_T P_345 ; real_T P_346 ; real_T P_347 ;
real_T P_348 ; real_T P_349 ; real_T P_350 ; real_T P_351 [ 9 ] ; real_T
P_352 ; real_T P_353 ; real_T P_354 ; real_T P_355 ; real_T P_356 ; real_T
P_357 ; real_T P_358 ; real_T P_359 ; real_T P_360 ; real_T P_361 ; real_T
P_362 ; real_T P_363 ; real_T P_364 ; real_T P_365 ; real_T P_366 ; real_T
P_367 ; real_T P_368 ; real_T P_369 ; real_T P_370 ; real_T P_371 ; real_T
P_372 ; real_T P_373 ; real_T P_374 ; real_T P_375 ; real_T P_376 ; real_T
P_377 ; real_T P_378 ; real_T P_379 ; real_T P_380 ; real_T P_381 ; real_T
P_382 ; real_T P_383 ; real_T P_384 [ 9 ] ; real_T P_385 ; real_T P_386 ;
real_T P_387 ; real_T P_388 ; real_T P_389 ; real_T P_390 ; real_T P_391 ;
real_T P_392 ; real_T P_393 ; real_T P_394 [ 9 ] ; real_T P_395 ; real_T
P_396 ; real_T P_397 ; real_T P_398 ; real_T P_399 ; real_T P_400 ; real_T
P_401 ; real_T P_402 ; real_T P_403 ; real_T P_404 ; real_T P_405 ; real_T
P_406 ; real_T P_407 ; real_T P_408 ; real_T P_409 ; real_T P_410 ; real_T
P_411 ; real_T P_412 ; real_T P_413 ; real_T P_414 ; real_T P_415 ; real_T
P_416 ; real_T P_417 ; real_T P_418 ; real_T P_419 ; real_T P_420 ; real_T
P_421 ; real_T P_422 ; real_T P_423 ; real_T P_424 ; real_T P_425 ; real_T
P_426 ; real_T P_427 [ 9 ] ; real_T P_428 ; real_T P_429 ; real_T P_430 ;
real_T P_431 ; real_T P_432 ; real_T P_433 ; real_T P_434 ; real_T P_435 ;
real_T P_436 ; real_T P_437 [ 9 ] ; real_T P_438 ; real_T P_439 ; real_T
P_440 ; real_T P_441 ; real_T P_442 ; real_T P_443 ; real_T P_444 ; real_T
P_445 ; real_T P_446 ; real_T P_447 ; real_T P_448 ; real_T P_449 ; real_T
P_450 ; real_T P_451 ; real_T P_452 ; real_T P_453 ; real_T P_454 ; real_T
P_455 ; real_T P_456 ; real_T P_457 ; real_T P_458 ; real_T P_459 ; real_T
P_460 ; real_T P_461 ; real_T P_462 ; real_T P_463 ; real_T P_464 ; real_T
P_465 ; real_T P_466 ; real_T P_467 ; real_T P_468 ; real_T P_469 ; real_T
P_470 [ 9 ] ; real_T P_471 ; real_T P_472 ; real_T P_473 ; real_T P_474 ;
real_T P_475 ; real_T P_476 ; real_T P_477 ; real_T P_478 ; real_T P_479 ;
real_T P_480 [ 9 ] ; real_T P_481 ; real_T P_482 ; real_T P_483 ; real_T
P_484 ; real_T P_485 ; real_T P_486 ; real_T P_487 ; real_T P_488 ; real_T
P_489 ; real_T P_490 ; real_T P_491 ; real_T P_492 ; real_T P_493 ; real_T
P_494 ; real_T P_495 ; real_T P_496 ; real_T P_497 ; real_T P_498 ; real_T
P_499 ; real_T P_500 ; real_T P_501 ; real_T P_502 ; real_T P_503 ; real_T
P_504 ; real_T P_505 ; real_T P_506 ; real_T P_507 ; real_T P_508 ; real_T
P_509 ; real_T P_510 ; real_T P_511 ; real_T P_512 ; real_T P_513 [ 9 ] ;
real_T P_514 ; real_T P_515 ; real_T P_516 ; real_T P_517 ; real_T P_518 ;
real_T P_519 ; real_T P_520 ; real_T P_521 ; real_T P_522 ; real_T P_523 [ 9
] ; real_T P_524 ; real_T P_525 ; real_T P_526 ; real_T P_527 ; real_T P_528
; real_T P_529 ; real_T P_530 ; real_T P_531 ; real_T P_532 ; real_T P_533 ;
real_T P_534 ; real_T P_535 ; real_T P_536 ; real_T P_537 ; real_T P_538 ;
real_T P_539 ; real_T P_540 ; real_T P_541 ; real_T P_542 ; real_T P_543 ;
real_T P_544 ; real_T P_545 ; real_T P_546 ; real_T P_547 ; real_T P_548 ;
real_T P_549 ; real_T P_550 ; real_T P_551 ; real_T P_552 ; real_T P_553 ;
real_T P_554 ; real_T P_555 ; real_T P_556 [ 9 ] ; real_T P_557 ; real_T
P_558 ; real_T P_559 ; real_T P_560 ; real_T P_561 ; real_T P_562 ; real_T
P_563 ; real_T P_564 ; real_T P_565 ; real_T P_566 ; real_T P_567 [ 9 ] ;
real_T P_568 ; real_T P_569 ; real_T P_570 ; real_T P_571 ; real_T P_572 ;
real_T P_573 ; real_T P_574 ; real_T P_575 ; real_T P_576 ; real_T P_577 ;
real_T P_578 ; real_T P_579 ; real_T P_580 ; real_T P_581 ; real_T P_582 ;
real_T P_583 ; real_T P_584 ; real_T P_585 ; real_T P_586 ; real_T P_587 ;
real_T P_588 ; real_T P_589 ; real_T P_590 ; real_T P_591 ; real_T P_592 ;
real_T P_593 ; real_T P_594 ; real_T P_595 ; real_T P_596 ; real_T P_597 ;
real_T P_598 ; real_T P_599 ; real_T P_600 [ 9 ] ; real_T P_601 ; real_T
P_602 ; real_T P_603 ; real_T P_604 ; real_T P_605 ; real_T P_606 ; real_T
P_607 ; real_T P_608 ; real_T P_609 ; real_T P_610 [ 9 ] ; real_T P_611 ;
real_T P_612 ; real_T P_613 ; real_T P_614 ; real_T P_615 ; real_T P_616 ;
real_T P_617 ; real_T P_618 ; real_T P_619 ; real_T P_620 ; real_T P_621 ;
real_T P_622 ; real_T P_623 ; real_T P_624 ; real_T P_625 ; real_T P_626 ;
real_T P_627 ; real_T P_628 ; real_T P_629 ; real_T P_630 ; real_T P_631 ;
real_T P_632 ; real_T P_633 ; real_T P_634 ; real_T P_635 ; real_T P_636 ;
real_T P_637 ; real_T P_638 ; real_T P_639 ; real_T P_640 ; real_T P_641 ;
real_T P_642 ; real_T P_643 [ 9 ] ; real_T P_644 ; real_T P_645 ; real_T
P_646 ; real_T P_647 ; real_T P_648 ; real_T P_649 ; real_T P_650 ; real_T
P_651 ; real_T P_652 ; real_T P_653 [ 9 ] ; real_T P_654 ; real_T P_655 ;
real_T P_656 ; real_T P_657 ; real_T P_658 ; real_T P_659 ; real_T P_660 ;
real_T P_661 ; real_T P_662 ; real_T P_663 ; real_T P_664 ; real_T P_665 ;
real_T P_666 ; real_T P_667 ; real_T P_668 ; real_T P_669 ; real_T P_670 ;
real_T P_671 ; real_T P_672 ; real_T P_673 ; real_T P_674 ; real_T P_675 ;
real_T P_676 ; real_T P_677 ; real_T P_678 ; real_T P_679 ; real_T P_680 ;
real_T P_681 ; real_T P_682 ; real_T P_683 ; real_T P_684 ; real_T P_685 ;
real_T P_686 [ 9 ] ; real_T P_687 ; real_T P_688 ; real_T P_689 ; real_T
P_690 ; real_T P_691 ; real_T P_692 ; real_T P_693 ; real_T P_694 ; real_T
P_695 ; real_T P_696 [ 9 ] ; real_T P_697 ; real_T P_698 ; real_T P_699 ;
real_T P_700 ; real_T P_701 ; real_T P_702 ; real_T P_703 ; real_T P_704 ;
real_T P_705 ; real_T P_706 ; real_T P_707 ; real_T P_708 ; real_T P_709 ;
real_T P_710 ; real_T P_711 ; real_T P_712 ; real_T P_713 ; real_T P_714 ;
real_T P_715 ; real_T P_716 ; real_T P_717 ; real_T P_718 ; real_T P_719 ;
real_T P_720 ; real_T P_721 ; real_T P_722 ; real_T P_723 ; real_T P_724 ;
real_T P_725 ; real_T P_726 ; real_T P_727 ; real_T P_728 ; real_T P_729 [ 9
] ; real_T P_730 ; real_T P_731 ; real_T P_732 [ 6 ] ; real_T P_733 [ 6 ] ;
real_T P_734 ; real_T P_735 ; real_T P_736 ; real_T P_737 ; real_T P_738 ;
real_T P_739 ; real_T P_740 ; real_T P_741 [ 6 ] ; real_T P_742 [ 6 ] ;
real_T P_743 ; real_T P_744 ; real_T P_745 ; real_T P_746 ; real_T P_747 ;
real_T P_748 ; real_T P_749 ; real_T P_750 [ 6 ] ; real_T P_751 [ 6 ] ;
real_T P_752 ; real_T P_753 ; real_T P_754 ; real_T P_755 ; real_T P_756 ;
real_T P_757 ; real_T P_758 ; real_T P_759 [ 6 ] ; real_T P_760 [ 6 ] ;
real_T P_761 ; real_T P_762 ; real_T P_763 ; real_T P_764 ; real_T P_765 ;
real_T P_766 ; real_T P_767 ; real_T P_768 [ 4 ] ; real_T P_769 [ 4 ] ;
real_T P_770 ; real_T P_771 ; real_T P_772 ; real_T P_773 ; real_T P_774 ;
real_T P_775 ; real_T P_776 [ 15 ] ; real_T P_777 ; real_T P_778 ; real_T
P_779 ; real_T P_780 ; real_T P_781 ; real_T P_782 ; real_T P_783 ; real_T
P_784 ; real_T P_785 ; real_T P_786 ; real_T P_787 ; real_T P_788 ; real_T
P_789 ; real_T P_790 ; real_T P_791 ; real_T P_792 ; real_T P_793 ; real_T
P_794 ; real_T P_795 ; real_T P_796 ; real_T P_797 ; real_T P_798 ; real_T
P_799 ; real_T P_800 ; real_T P_801 ; real_T P_802 ; real_T P_803 ; real_T
P_804 ; real_T P_805 ; real_T P_806 ; real_T P_807 ; real_T P_808 ; real_T
P_809 ; real_T P_810 ; real_T P_811 ; real_T P_812 ; real_T P_813 ; real_T
P_814 ; real_T P_815 ; real_T P_816 ; real_T P_817 ; real_T P_818 ; real_T
P_819 ; real_T P_820 ; real_T P_821 ; real_T P_822 ; real_T P_823 ; real_T
P_824 ; real_T P_825 ; real_T P_826 ; real_T P_827 ; real_T P_828 ; real_T
P_829 ; real_T P_830 ; real_T P_831 ; real_T P_832 ; real_T P_833 ; real_T
P_834 ; real_T P_835 ; real_T P_836 ; real_T P_837 ; real_T P_838 ; real_T
P_839 ; real_T P_840 ; real_T P_841 ; real_T P_842 ; real_T P_843 ; real_T
P_844 ; real_T P_845 ; real_T P_846 ; real_T P_847 ; real_T P_848 ; real_T
P_849 ; real_T P_850 ; real_T P_851 ; real_T P_852 [ 25 ] ; real_T P_853 ;
real_T P_854 [ 25 ] ; real_T P_855 ; real_T P_856 [ 2 ] ; real_T P_857 [ 2 ]
; real_T P_858 [ 25 ] ; real_T P_859 [ 25 ] ; real_T P_860 [ 2 ] ; real_T
P_861 ; real_T P_862 ; real_T P_863 ; real_T P_864 ; real_T P_865 ; real_T
P_866 ; real_T P_867 ; real_T P_868 ; real_T P_869 ; real_T P_870 ; real_T
P_871 ; real_T P_872 ; real_T P_873 ; real_T P_874 ; real_T P_875 ; real_T
P_876 ; real_T P_877 ; real_T P_878 ; real_T P_879 ; real_T P_880 ; real_T
P_881 ; real_T P_882 ; real_T P_883 ; real_T P_884 ; real_T P_885 ; real_T
P_886 ; real_T P_887 ; real_T P_888 ; real_T P_889 ; real_T P_890 ; real_T
P_891 ; real_T P_892 ; real_T P_893 ; real_T P_894 ; real_T P_895 ; real_T
P_896 ; real_T P_897 ; real_T P_898 ; real_T P_899 ; real_T P_900 ; real_T
P_901 ; real_T P_902 ; real_T P_903 ; real_T P_904 ; real_T P_905 ; real_T
P_906 ; real_T P_907 ; real_T P_908 ; real_T P_909 ; real_T P_910 ; real_T
P_911 ; real_T P_912 ; real_T P_913 ; real_T P_914 ; real_T P_915 ; real_T
P_916 ; real_T P_917 ; real_T P_918 ; real_T P_919 ; real_T P_920 ; real_T
P_921 ; real_T P_922 ; real_T P_923 ; real_T P_924 ; real_T P_925 ; real_T
P_926 ; real_T P_927 ; real_T P_928 ; real_T P_929 ; real_T P_930 ; real_T
P_931 ; real_T P_932 ; real_T P_933 ; real_T P_934 ; real_T P_935 ; real_T
P_936 ; real_T P_937 ; real_T P_938 ; real_T P_939 ; real_T P_940 ; real_T
P_941 ; real_T P_942 ; real_T P_943 ; real_T P_944 ; real_T P_945 ; real_T
P_946 ; real_T P_947 ; real_T P_948 ; real_T P_949 ; real_T P_950 ; real_T
P_951 ; real_T P_952 ; real_T P_953 ; real_T P_954 ; real_T P_955 ; real_T
P_956 ; uint32_T P_957 ; uint32_T P_958 [ 2 ] ; uint32_T P_959 ; uint32_T
P_960 [ 2 ] ; uint32_T P_961 ; uint32_T P_962 [ 2 ] ; uint32_T P_963 ;
uint32_T P_964 [ 2 ] ; uint32_T P_965 ; uint32_T P_966 [ 2 ] ; uint32_T P_967
; uint32_T P_968 [ 2 ] ; uint32_T P_969 ; uint32_T P_970 [ 2 ] ; uint32_T
P_971 ; uint32_T P_972 [ 2 ] ; uint32_T P_973 ; uint32_T P_974 [ 2 ] ;
uint32_T P_975 ; uint32_T P_976 [ 2 ] ; uint32_T P_977 ; uint32_T P_978 [ 2 ]
; uint32_T P_979 ; uint32_T P_980 [ 2 ] ; uint32_T P_981 ; uint32_T P_982 [ 2
] ; uint32_T P_983 ; uint32_T P_984 [ 2 ] ; uint32_T P_985 ; uint32_T P_986 [
2 ] ; uint32_T P_987 ; uint32_T P_988 [ 2 ] ; uint32_T P_989 ; uint32_T P_990
[ 2 ] ; boolean_T P_991 ; boolean_T P_992 ; boolean_T P_993 ; boolean_T P_994
; P_Subsystem1_dVOC_monitor_network1_T Subsystem1_p1 ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_lp ;
P_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_c ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_a ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_kj ;
P_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_k ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_cm ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_j ;
P_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_g ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_j ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_e ;
P_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b2 ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_bc ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_na ;
P_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_m ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_dt ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_n ;
P_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_l ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_e4 ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_p ;
P_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_b ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_n ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_ho ;
P_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl_a ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_f ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_a ;
P_AutomaticGainControl_dVOC_monitor_network1_T AutomaticGainControl ;
P_Subsystem1_dVOC_monitor_network1_a_T Subsystem1_o ;
P_Subsystempi2delay_dVOC_monitor_network1_g_T Subsystempi2delay_dn ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_k ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_bp ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_gc ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_o4 ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_h ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_ct ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_c ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_g ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_d ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_d ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_pc ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_hz ;
P_Subsystem1_dVOC_monitor_network1_a_T Subsystem1_b ;
P_Subsystempi2delay_dVOC_monitor_network1_g_T Subsystempi2delay_o ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_p ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_h ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_ge ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_l ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_i ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_b ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_e ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_k ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1_g ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay_c ;
P_Subsystem1_dVOC_monitor_network1_T Subsystem1 ;
P_Subsystempi2delay_dVOC_monitor_network1_T Subsystempi2delay ; } ; extern
P_dVOC_monitor_network1_T dVOC_monitor_network1_rtDefaultP ;
#endif
