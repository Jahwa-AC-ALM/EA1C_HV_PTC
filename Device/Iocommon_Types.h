/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Iocommon_Types.h                                            */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015 - 2021 Renesas Electronics Corporation                   */
/*============================================================================*/
/* Purpose:   Declarations of I/O Registers                                   */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        F1KM                                          */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * V1.0.0:  18-Aug-2015    : Initial Version
 *
 * V1.0.1:  24-Sep-2015    : The following changes are made;
 *                           1. The CSC register is added in the structures
 *                           TAUDBChReg and TAUJChReg.
 *                           2. CTL and EMU registers are added in the OS
 *                           timer structure OSTMReg.
 *                           3. The name corrected to ucLiEST in the Lin2ChReg
 *                           Structure.
 *                           4. PPR register are defined for the support of
 *                           ICU module.
 * V1.0.2:  14-Oct-2015    : The following changes are made
 *                           1. FACI and ECC registers added for Fls module.
 *                           2. Address Space updated for SpiMainReg, SpiCSIHReg
 *                           and SpiCSIGReg structures in SPI module.
 *                           3. Register naming corrected for CAN module.
 * V1.0.3:  14-Jan-2016    : As part of F1K Ver4.00.01 release, following
 *                           changes are made:
 *                           1. Added support for global DMA registers.
 *                           2. Macro SELB_TAUD0I is added.
 *                           3. Structure element ucDFERINT in STag_Fcu_ECCReg
 *                              changed to ucDFERRINT.
 *                           4. Updated the type of DMACTL macro.
 *                           5. Added Structure STag_Spi_BRSReg to support the
 *                              address calculation of BRS registers of CSIHn.
 *                           6. Structure element usBRS of type unsigned short
 *                              in STag_Spi_CSIHReg changed to stBRS of type
 *                              SpiBRSReg.
 *                           7. Address for PROTCMD0 and PROTS0 are added.
 *                           8. Address for FEINTFC has been added.
 *                           9. Element ulDR[] changed to usDR[] in structure
 *                              'STag_Adc_VirtualChReg'.
 *                           10. Structures added and updated for CAN.
 * V1.0.4:  29-Nov-2016    : JIRA #ARDAABD-663 - Macro redefinitions in
 *                           register definitions header files
 * V1.0.5:  02-Feb-2017    : JIRA #ARDAABD-830 - Removed duplicate macro
 *                           PWGA30REG
 * V1.0.6:  24-Feb-2017    : Add the following change sets for Jira ticket
 *                           ARDAABC-1269:
 *                           1. As part of ARDAABC-875 defined FEINTFMSK
 *                           register address to be able to mask FE level
 *                           interrupts.
 *                           2. To avoid macro redefinition with device header
 *                           files(ARDAABC-793), added IO_COMMON prefix to
 *                           registers: IO_COMMON_FEINTF, IO_COMMON_FEINTFC,
 *                           IO_COMMON_DMACTL, IO_COMMON_OSTM0CMP,
 *                           IO_COMMON_OSTM1CMP, IO_COMMON_OSTM2CMP,
 *                           IO_COMMON_OSTM3CMP and IO_COMMON_OSTM4CMP
 *
 * V1.1.0  02-Mar-2017       #ARDAABD-1071
 *                           1. Added Can related defines.
 * V1.1.1  07-Mar-2017       Update ucdummy241 element from PWGAReg structure
 *                           to contain 3 dummy bytes instead of 2 bytes due to
 *                           the fact that ucRDT is a unsigned char(1 byte).
 * V1.2.0  31-May-2017       F1KM LIN registers added (Ref: JIRA #ARDAABD-1869)
 * V1.3.0  21-Jun-2017       Added ClkCntlReg_S1 for F1KM-S1 and ClkCntlReg_S4
 *                           for F1KM-S4 (Ref: JIRA #ARDAABD-1949)
 * V1.4.0  22-Jun-2017       Added WUF1 register address in order to support
 *                           F1KM devices (Ref: JIRA #ARDAABD-1960)
 * V1.4.1  23-Jun-2017       Following changes are made:
 *                           1. As part of ARDAABD-1725,
 *                           Support for DMA channels 16-31 is added
 * V1.4.2  30-Jun-2017       As part of ARDAABD-1726 following changes are made
 *                           1.Added TAUJ2CHmREG and TAUJ3CHmREG (where m=0to3)
 *                           2.Added ICTAUJ2Im and ICTAUJ3Im (where m=0to3)
 *                           3.Added PWGA72REG to PWGA95REG
 *                           4.Support of PISA register is added for Numeric
 *                             Port Group.
 *                           5.Added ICP16 to ICP23
 * V1.4.3  05-Jul-S017       As part of  ARDAABD-1959 CLMA3 register address
 *                           for F1KM-S1 and F1KM-S4 added
 * V1.4.4  10-Jul-2017       As part of ARDAABD-1726 following changes are made:
 *                           1. PWGAnTCR and PWGAnTCBR register informations
 *                              are added in 'PWGAReg' structure.
 *                           2. PWGAPRD, PWGAPRDSL0, PWGAPRDSL1 and PWGAPRDSL2
 *                              register informations are added in 'SLPWGAReg'
 *                              structure.
 * V1.4.5  11-Jul-2017       As part of ARDAABD-1725 following changes are made:
 *                           1. VCFR,ULLMTBR,MPXSTBTSELR, MPXSTBTR added in
 *                              STag_AdcConfigRegisters.
 * V1.4.6  11-Jul-2017       As part of ARDAABD-1373 following changes are made:
 *                           1. TAUJ2USERREG, TAUJ3USERREG, TAUJ2OSREG and
 *                              TAUJ3OSREG are added.
 *                           2. ulWUF1, ulWUFMSK1 and ulWUFC1 are added in
 *                              structure WUFReg.
 * V1.4.7  11-Jul-2017       As part of ARDAABD-1726 following changes are made:
 *                           1. Added structure 'PWGAINTFReg' for PWM
 *                           2. Added base address of registers PWGAINTF0mREG
 *                              (where m=0,1,2) and ICPWGAG0m(where m=0,1,2)
 * V1.4.8  12-Jul-2017       1. Renamed WUFREG10 to WUFREG1 for ICU
 * V1.4.9  20-Jul-2017       #ARDAABD-1139 - Corrected STag_Fls_ECCRegType
 *                           structure
 * V1.4.10 21-Jul-2017       1. ulWUF1, ulWUFMSK1 and ulWUFC1 are removed from
 *                           structure WUFReg.
 * V1.4.11 21-Jul-2017       Added ECC register for SPI
 * V1.4.12 26-Jul-2017       Added MUX register for ADC
 * V1.4.13 27-Jul-2017       Added CSIG2 and CSIG3 registers for SPI
 * V1.4.14 16-Aug-2017       Added SELB_TAUB0I and SELB_TAUB1I for ICU
 * V1.4.15 25-Sep-2017       As part of F1K_F1KM_Ver4.02.01_Ver42.02.01_ASILB
 *                           release, following changes are made:
 *                           1.As per ARDAABD-2160,Iocommon splitted as
 *                             Iocommon_Defines.h and Iocommon_Types.h
 *                           2.As per ARDAABD-2254,Native data types replaced
 *                             with Platform_Types.
 * V1.4.16 15-May-2018       Following changes are made:
 *                           1. As part of JIRA ARDAABD-2659, added RSF register
 *                              in TAUDBUnitUserReg and TAUJUnitUserReg
 *                              structures for PWM module.
 *                           2. Copyright information is updated.
 * V1.4.17 02-Sep-2020       Following changes are made:
 *                           1. As part of ARDAABD-4015, according to the coding
 *                              guidelines, modified the illegal variables name.
 * V1.4.18 02-Apr-2021       Following changes are made:
 *                           1. As part of ARDAABD-4973, added PWSAnPWDDIRz
 *                              register to struct of PWSAReg.
 * V1.4.19 13-Jul-2021       As part of ARDAABD-6342, added the structure
 *                           'Stag_ClkCntl_Registers_S2'.
 */
/******************************************************************************/
/*******************************************************************************
**                       MISRA C Rule Violations                              **
*******************************************************************************/
/* 1. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:0857)Number of macro definitions exceeds 1024 - program */
/*                 does not conform strictly to ISO:C99.                      */
/* Rule          : MISRA-C:2004 Rule 1.1                                      */
/* Justification : In order to ensure portability, it is advisable to avoid   */
/*                 writing code that assumes a level of compiler capability   */
/*                 which may not always be supported.                         */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:0857)-1 and                           */
/*                 END Msg(4:0857)-1 tags in the code.                        */
/******************************************************************************/
/* 2. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:0639)Number of members in 'struct' or 'union' exceeds   */
/*                 127 - program does not conform strictly to ISO:C99.        */
/* Rule          : MISRA-C:2004 Rule 1.1                                      */
/* Justification : In order to ensure portability, it is advisable to avoid   */
/*                 writing code that assumes a level of compiler capability   */
/*                 which may not always be supported.                         */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:0639)-2 and                           */
/*                 END Msg(4:0639)-2 tags in the code.                        */
/******************************************************************************/
#ifndef IOCOMMON_TYPES_H
#define IOCOMMON_TYPES_H

#include "Platform_Types.h"

typedef struct Stag_PortRegisters
{
    uint16 usP;                             /* P                */

    uint8 ucDummy1[254];                    /* Reserved         */

    uint32  ulPSR;                          /* PSR              */

    uint8 ucDummy2[252];                    /* Reserved         */

    uint16 usPPR;                           /* PPR              */

    uint8 ucDummy3[254];                    /* Reserved         */

    uint16 usPM;                            /* PM               */

    uint8 ucDummy4[254];                    /* Reserved         */

    uint16 usPMC;                           /* PMC              */

    uint8 ucDummy5[254];                    /* Reserved         */

    uint16 usPFC;                           /* PFC              */

    uint8 ucDummy6[254];                    /* Reserved         */

    uint16 usPFCE;                          /* PFCE             */

    uint8 ucDummy7[254];                    /* Reserved         */

    uint16 usPNOT;                          /* PNOT             */

    uint8 ucDummy8[254];                    /* Reserved         */

    uint32  ulPMSR;                         /* PMSR             */

    uint8 ucDummy9[252];                    /* Reserved         */

    uint32  ulPMCSR;                        /* PMCSR            */

    uint8 ucDummy10[252];                   /* Reserved         */

    uint16 usPFCAE;                         /* PFCAE            */

    uint8 ucDummy11[13822];                 /* Reserved         */

    uint16 usPIBC;                          /* PIBC             */

    uint8 ucDummy12[254];                   /* Reserved         */

    uint16 usPBDC;                          /* PBDC             */

    uint8 ucDummy13[254];                   /* Reserved         */

    uint16 usPIPC;                          /* PIPC             */

    uint8 ucDummy14[254];                   /* Reserved         */

    uint16 usPU;                            /* PU               */

    uint8 ucDummy15[254];                   /* Reserved         */

    uint16 usPD;                            /* PD               */

    uint8 ucDummy16[254];                   /* Reserved         */

    uint32  ulPODC;                         /* PODC             */

    uint8 ucDummy17[252];                   /* Reserved         */

    uint32  ulPDSC;                         /* PDSC             */

    uint8 ucDummy18[252];                   /* Reserved         */

    uint16 usPIS;                           /* PIS              */

    uint8 ucDummy19[766];                   /* Reserved         */

    uint16 usPISA;                          /* PISA            */

    uint8 ucDummy20[254];                   /* Reserved         */

    uint32 ulPPROTS;                        /* PPROTS           */

    uint8 ucDummy21[252];                   /* Reserved         */

    uint32 ulPPCMD;                         /* PPMCD            */
}PortReg;

typedef struct STag_IPortRegisters
{                                                         /* Input port reg   */
    uint16 usIPPR;                          /* PPR              */

    uint8 ucDummy21[15870];                 /* Reserved         */

    uint16 usIPIBC;                         /* PIBC             */
}IPortReg;

typedef struct STag_JPortRegisters
{
    uint8 ucJP;                             /* JP               */

    uint8 ucDummy22[15];                    /* Reserved         */

    uint32 ulJPSR;                          /* JPSR             */

    uint8 ucDummy23[12];                    /* Reserved         */

    uint8 ucJPPR;                           /* JPPR             */

    uint8 ucDummy24[15];                    /* Reserved         */

    uint8 ucJPM;                            /* JPM              */

    uint8 ucDummy25[15];                    /* Reserved         */

    uint8 ucJPMC;                           /* JPMC             */

    uint8 ucDummy26[15];                    /* Reserved         */

    uint8 ucJPFC;                           /* JPFC             */

    uint8 ucDummy27[15];                    /* Reserved         */

    uint8 ucJPFCE;                          /* JPFCE            */

    uint8 ucDummy28[15];                    /* Reserved         */

    uint8 ucJPNOT;                          /* JPNOT            */

    uint8 ucDummy29[15];                    /* Reserved         */

    uint32  ulJPMSR;                        /* JPMSR            */

    uint8 ucDummy30[9];                     /* Reserved         */

    uint32  ulJPMCSR;                       /* JPMCSR           */

    uint8 ucDummy31[876];                   /* Reserved         */

    uint8 ucJPIBC;                          /* JPIBC            */

    uint8 ucDummy32[15];                    /* Reserved         */

    uint8 ucJPBDC;                          /* JPBDC            */

    uint8 ucDummy33[31];                    /* Reserved         */

    uint8 ucJPU;                            /* JPU              */

    uint8 ucDummy34[15];                    /* Reserved         */

    uint8 ucJPD;                            /* JPD              */

    uint8 ucDummy35[15];                    /* Reserved         */

    uint32  ulJPODC;                        /* JPODC            */

    uint8 ucDummy36[12];                    /* Reserved         */

    uint32  ulJPDSC;                        /* JPDSC            */

    uint8 ucDummy37[12];                    /* Reserved         */

    uint8 ucJPIS;                           /* JPIS             */

    uint8 ucDummy38[47];                    /* Reserved         */

    uint8 ucJPISA;                          /* JPISA            */

    uint8 ucDummy39[15];                    /* Reserved         */

    uint32 ulJPPROTS;                       /* JPPROTS          */

    uint8 ucDummy40[12];                    /* Reserved         */

    uint32 ulJPPCMD;                        /* JPPMCD           */
}JPortReg;

typedef struct Stag_AnalogPortReg
{
    uint16 usAP;                            /* AP               */

    uint8 ucDummy41[254];                   /* Reserved         */

    uint32 ulAPSR;                          /* APSR             */

    uint8 ucDummy42[252];                   /* Reserved         */

    uint16 usAPPR;                          /* APPR             */

    uint8 ucDummy43[254];                   /* Reserved         */

    uint16 usAPM;                           /* APM              */

    uint8 ucDummy44[1022];                  /* Reserved         */

    uint16 usAPNOT;                         /* APNOT            */

    uint8 ucDummy45[254];                   /* Reserved         */

    uint32 ulAPMSR;                         /* APMSR            */

    uint8 ucDummy46[14332];                 /* Reserved         */

    uint16 usAPIBC;                         /* APIBC            */

    uint8 ucDummy47[254];                   /* Reserved         */

    uint16 usAPBDC;                         /* APBDC            */
}APortReg;

typedef struct Stag_FCLA0_Registers
{
    uint8         ucCTLn_SIG[137];
/* CTL0_NMI         - offset 0x00  */
/* CTL0_INTPL       - offset 0x20  */
/* CTL1_INTPL       - offset 0x24  */
/* CTL2_INTPL       - offset 0x28  */
/* CTL3_INTPL       - offset 0x2C  */
/* CTL4_INTPL       - offset 0x30  */
/* CTL5_INTPL       - offset 0x34  */
/* CTL6_INTPL       - offset 0x38  */
/* CTL7_INTPL       - offset 0x3C  */
/* CTL0_INTPH       - offset 0x40  */
/* CTL1_INTPH       - offset 0x44  */
/* CTL2_INTPH       - offset 0x48  */
/* CTL3_INTPH       - offset 0x4C  */
/* CTL4_INTPH       - offset 0x50  */
/* CTL5_INTPH       - offset 0x54  */
/* CTL6_INTPH       - offset 0x58  */
/* CTL7_INTPH       - offset 0x5C  */
/* CTL0_ADC0        - offset 0x60  */
/* CTL1_ADC0        - offset 0x64  */
/* CTL2_ADC0        - offset 0x68  */
/* CTL0_ADC1        - offset 0x80  */
/* CTL1_ADC1        - offset 0x84  */
/* CTL2_ADC1        - offset 0x88  */
}FCLAReg;

typedef struct Stag_DNFA_Registers
{
    uint8  ucCTL;                           /* DNFACTL         */

    uint8  ucDummy70[3];                    /* Reserved         */

    uint16 usEN;                            /* DNFAEN          */
}DNFAReg;

typedef struct Stag_RESF_Registers
{                                                         /* RESF registers   */
    const uint32 ulRESF;                    /* RESF             */

    uint8  ucDummy90[4];                    /* Reserved         */

    uint32 ulRESFC;                         /* RESFC            */

    uint8  ucDummy91[244];                  /* Reserved         */

    const uint32 ulRESFR;                   /* RESFR            */

    uint8  ucDummy92[4];                    /* Reserved         */

    uint32 ulRESFCR;                        /* RESFCR           */

    uint8  ucDummy93[408];                  /* Reserved         */

    uint32 ulSWRESA;                        /* SWRESA           */

    uint8  ucDummy94[11256];                /* Reserved         */

    uint32 ulCYCRBASE;                      /* CYCRBASE         */
} RESFReg;

typedef struct Stag_LVI_Registers
{                                                         /* LVI registers    */
    const uint32 ulVLVF;                    /* VLVF             */

    uint8  ucDummy95[4];                    /* Reserved         */

    uint32 ulVLVFC;                         /* VLVFC            */

    uint8  ucDummy96[116];                  /* Reserved         */

    uint32 ulLVICNT;                        /* LVICNT           */

    uint8  ucDummy97[9980];                 /* Reserved         */

    uint32 ulCVMF;                          /* CVMF             */

    const uint32 ulCVMDE;                   /* CVMDE            */

    uint8  ucDummy98[12];                   /* Reserved         */

    uint32 ulCVMDIAG;                       /* CVMDIAG          */

    uint8  ucDummy99[232];                  /* Reserved         */

    uint32 ulPROTCMDCVM;                    /* PROTCMDCVM       */

    const uint32 ulPROTSCVM;                /* PROTSCVM         */
} LVIReg;
/* START Msg(4:0639)-2 */
typedef struct Stag_ClkCntl_Registers
{                                                         /* Clk control      */

    uint32 ulROSCE;                         /* ROSCE            */

    const uint32 ulROSCS;                   /* ROSCS            */

    uint8  ucDummy100[16];                  /* Reserved         */

    uint32 ulROSCSTPM;                      /* ROSCSTPM         */

    uint32 ulROSCUT;                        /* ROSCUT           */

    uint8  ucDummy101[224];                 /* Reserved         */

    uint32 ulMOSCE;                         /* MOSCE            */

    const uint32 ulMOSCS;                   /* MOSCS            */

    uint32 ulMOSCC;                         /* MOSCC            */

    uint32 ulMOSCST;                        /* MOSCST           */

    uint8  ucDummy102[8];                   /* Reserved         */

    uint32 ulMOSCSTPM;                      /* MOSCSTPM         */

    uint32 ulMOSCM;                         /* MOSCM            */

    uint8  ucDummy103[224];                 /* Reserved         */

    uint32 ulSOSCE;                         /* SOSCE            */

    const uint32 ulSOSCS;                   /* SOSCS            */

    uint8  ucDummy104[4];                   /* Reserved         */

    uint32 ulSOSCST;                        /* SOSCST           */

    uint8  ucDummy105[3568];                /* Reserved         */

    uint32 ulCKSC_AWDTAD_CTL;               /* CKSC_AWDTAD_CTL  */

    uint8  ucDummy106[4];                   /* Reserved         */

    const uint32 ulCKSC_AWDTAD_ACT;         /* CKSC_AWDTAD_ACT  */

    uint8  ucDummy107[12];                  /* Reserved         */

    uint32 ulCKSC_AWDTAD_STPM;              /* CKSC_AWDTAD_STPM */

    uint8  ucDummy108[228];                 /* Reserved         */

    uint32 ulCKSC_ATAUJS_CTL;               /* CKSC_ATAUJS_CTL  */

    uint8  ucDummy109[4];                   /* Reserved         */

    const uint32 ulCKSC_ATAUJS_ACT;         /* CKSC_ATAUJS_ACT  */

    uint8  ucDummy110[244];                 /* Reserved         */

    uint32 ulCKSC_ATAUJD_CTL;               /* CKSC_ATAUJD_CTL  */

    uint8  ucDummy111[4];                   /* Reserved         */

    const uint32 ulCKSC_ATAUJD_ACT;         /* CKSC_ATAUJD_ACT  */

    uint8  ucDummy112[12];                  /* Reserved         */

    uint32 ulCKSC_ATAUJD_STPM;              /* CKSC_ATAUJD_STPM */

    uint8  ucDummy113[228];                 /* Reserved         */

    uint32 ulCKSC_ARTCAS_CTL;               /* CKSC_ARTCAS_CTL  */

    uint8  ucDummy114[4];                   /* Reserved         */

    const uint32 ulCKSC_ARTCAS_ACT;         /* CKSC_ARTCAS_ACT  */

    uint8  ucDummy115[244];                 /* Reserved         */

    uint32 ulCKSC_ARTCAD_CTL;               /* CKSC_ARTCAD_CTL  */

    uint8  ucDummy116[4];                   /* Reserved         */

    const uint32 ulCKSC_ARTCAD_ACT;         /* CKSC_ARTCAD_ACT  */

    uint8  ucDummy117[12];                  /* Reserved         */

    uint32 ulCKSC_ARTCAD_STPM;              /* CKSC_ARTCAD_STPM */

    uint8  ucDummy118[228];                 /* Reserved         */

    uint32 ulCKSC_AADCAS_CTL;               /* CKSC_AADCAS_CTL  */

    uint8  ucDummy119[4];                   /* Reserved         */

    const uint32 ulCKSC_AADCAS_ACT;         /* CKSC_AADCAS_ACT  */

    uint8  ucDummy120[244];                 /* Reserved         */

    uint32 ulCKSC_AADCAD_CTL;               /* CKSC_AADCAD_CTL  */

    uint8  ucDummy121[4];                   /* Reserved         */

    const uint32 ulCKSC_AADCAD_ACT;         /* CKSC_AADCAD_ACT  */

    uint8  ucDummy122[12];                  /* Reserved         */

    uint32 ulCKSC_AADCAD_STPM;              /* CKSC_AADCAD_STPM */

    uint8  ucDummy123[228];                 /* Reserved         */

    uint32 ulCKSC_AFOUTS_CTL;               /* CKSC_AFOUTS_CTL  */

    uint8  ucDummy124[4];                   /* Reserved         */

    const uint32 ulCKSC_AFOUTS_ACT;         /* CKSC_AFOUTS_ACT  */

    uint8  ucDummy125[12];                  /* Reserved         */

    uint32 ulCKSC_AFOUTS_STPM;              /* CKSC_AFOUTS_STPM */

    uint8  ucDummy126[228];                 /* Reserved         */

    uint32 ulFOUTDIV;                       /* FOUTDIV          */

    const uint32 ulFOUTSTAT;                /* FOUTSTAT         */

    uint8  ucDummy127[26616];               /* Reserved         */

    uint32 ulPLLE;                          /* PLLE             */

    const uint32 ulPLLS;                    /* PLLS             */

    uint32 ulPLLC;                          /* PLLC             */

    uint8  ucDummy128[4084];                /* Reserved         */

    uint32 ulCKSC_CPUCLKS_CTL;              /* CKSC_CPUCLKS_CTL */

    uint8  ucDummy129[4];                   /* Reserved         */

    const uint32 ulCKSC_CPUCLKS_ACT;        /* CKSC_CPUCLKS_ACT */

    uint8  ucDummy130[4];                   /* Reserved         */

    uint32 ulCKSC_PPLLCLKS_CTL;             /* CKSC_PPLLCLKS_CTL*/

    uint8  ucDummy131[4];                   /* Reserved         */

    const uint32 ulCKSC_PPLLCLKS_ACT;       /* CKSC_PPLLCLKS_ACT*/

    uint8  ucDummy132[228];                 /* Reserved         */

    uint32 ulCKSC_CPUCLKD_CTL;              /* CKSC_CPUCLKD_CTL */

    uint8  ucDummy133[4];                   /* Reserved         */

    const uint32 ulCKSC_CPUCLKD_ACT;        /* CKSC_CPUCLKD_ACT */

    uint8  ucDummy134[244];                 /* Reserved         */

    uint32 ulCKSC_IPERI1S_CTL;              /* CKSC_IPERI1S_CTL */

    uint8  ucDummy135[4];                   /* Reserved         */

    const uint32 ulCKSC_IPERI1S_ACT;        /* CKSC_IPERI1S_ACT */

    uint8  ucDummy136[244];                 /* Reserved         */

    uint32 ulCKSC_IPERI2S_CTL;              /* CKSC_IPERI2S_CTL */

    uint8  ucDummy137[4];                   /* Reserved         */

    const uint32 ulCKSC_IPERI2S_ACT;        /* CKSC_IPERI2S_ACT */

    uint8  ucDummy138[244];                 /* Reserved         */

    uint32 ulCKSC_ILINS_CTL;                /* CKSC_ILINS_CTL   */

    uint8  ucDummy139[4];                   /* Reserved         */

    const uint32 ulCKSC_ILINS_ACT;          /* CKSC_ILINS_ACT   */

    uint8  ucDummy140[244];                 /* Reserved         */

    uint32 ulCKSC_IADCAS_CTL;               /* CKSC_IADCAS_CTL  */

    uint8  ucDummy141[4];                   /* Reserved         */

    const uint32 ulCKSC_IADCAS_ACT;         /* CKSC_IADCAS_ACT  */

    uint8  ucDummy142[244];                 /* Reserved         */

    uint32 ulCKSC_IADCAD_CTL;               /* CKSC_IADCAD_CTL  */

    uint8  ucDummy143[4];                   /* Reserved         */

    const uint32 ulCKSC_IADCAD_ACT;         /* CKSC_IADCAD_ACT  */

    uint8  ucDummy144[244];                 /* Reserved         */

    uint32 ulCKSC_PLLIS_CTL;                /* CKSC_PLLIS_CTL   */

    uint8  ucDummy145[4];                   /* Reserved         */

    const uint32 ulCKSC_PLLIS_ACT;          /* CKSC_PLLIS_ACT   */

    uint8  ucDummy146[244];                 /* Reserved         */

    uint32 ulCKSC_ILIND_CTL;                /* CKSC_ILIND_CTL   */

    uint8  ucDummy147[4];                   /* Reserved         */

    const uint32 ulCKSC_ILIND_ACT;          /* CKSC_ILIND_ACT   */

    uint8  ucDummy148[12];                  /* Reserved         */

    uint32 ulCKSC_ILIND_STPM;               /* CKSC_ILIND_STPM  */

    uint8  ucDummy149[228];                 /* Reserved         */

    uint32 ulCKSC_ICANS_CTL;                /* CKSC_ICANS_CTL   */

    uint8  ucDummy150[4];                   /* Reserved         */

    const uint32 ulCKSC_ICANS_ACT;          /* CKSC_ICANS_ACT   */

    uint8  ucDummy151[12];                  /* Reserved         */

    uint32 ulCKSC_ICANS_STPM;               /* CKSC_ICANS_STPM  */

    uint8  ucDummy152[228];                 /* Reserved         */

    uint32 ulCKSC_ICANOSCD_CTL;             /* CKSC_ICANOSCD_CTL*/

    uint8  ucDummy153[4];                   /* Reserved         */

    const uint32 ulCKSC_ICANOSCD_ACT;       /* CKSC_ICANOSCD_ACT*/

    uint8  ucDummy154[12];                  /* Reserved         */

    uint32 ulCKSC_ICANOSCD_STPM;            /* CKSC_ICANOSCD_STPM*/

    uint8  ucDummy155[228];                 /* Reserved         */

    uint32 ulCKSC_ICSIS_CTL;                /* CKSC_ICSIS_CTL   */

    uint8  ucDummy156[4];                   /* Reserved         */

    const uint32 ulCKSC_ICSIS_ACT;          /* CKSC_ICSIS_ACT   */

    uint8  ucDummy157[244];                 /* Reserved         */

    uint32 ulCKSC_IIICS_CTL;                /* CKSC_IIICS_CTL   */

    uint8  ucDummy158[4];                   /* Reserved         */

    const uint32 ulCKSC_IIICS_ACT;          /* CKSC_IIICS_ACT   */
} ClkCntlReg;
/* End Msg(4:0639)-2 */
/* START Msg(4:0639)-2 */
typedef struct Stag_ClkCntl_Registers_S1
{                                                         /* Clk control      */

    uint32 ulROSCE;                         /* ROSCE            */

    const uint32 ulROSCS;                   /* ROSCS            */

    uint8  ucDummy100[16];                  /* Reserved         */

    uint32 ulROSCSTPM;                      /* ROSCSTPM         */

    uint32 ulROSCUT;                        /* ROSCUT           */

    uint8  ucDummy101[224];                 /* Reserved         */

    uint32 ulMOSCE;                         /* MOSCE            */

    const uint32 ulMOSCS;                   /* MOSCS            */

    uint32 ulMOSCC;                         /* MOSCC            */

    uint32 ulMOSCST;                        /* MOSCST           */

    uint8  ucDummy102[8];                   /* Reserved         */

    uint32 ulMOSCSTPM;                      /* MOSCSTPM         */

    uint32 ulMOSCM;                         /* MOSCM            */

    uint8  ucDummy105[3808];                /* Reserved         */

    uint32 ulCKSC_AWDTAD_CTL;               /* CKSC_AWDTAD_CTL  */

    uint8  ucDummy106[4];                   /* Reserved         */

    const uint32 ulCKSC_AWDTAD_ACT;         /* CKSC_AWDTAD_ACT  */

    uint8  ucDummy107[12];                  /* Reserved         */

    uint32 ulCKSC_AWDTAD_STPM;              /* CKSC_AWDTAD_STPM */

    uint8  ucDummy108[228];                 /* Reserved         */

    uint32 ulCKSC_ATAUJS_CTL;               /* CKSC_ATAUJS_CTL  */

    uint8  ucDummy109[4];                   /* Reserved         */

    const uint32 ulCKSC_ATAUJS_ACT;         /* CKSC_ATAUJS_ACT  */

    uint8  ucDummy110[244];                 /* Reserved         */

    uint32 ulCKSC_ATAUJD_CTL;               /* CKSC_ATAUJD_CTL  */

    uint8  ucDummy111[4];                   /* Reserved         */

    const uint32 ulCKSC_ATAUJD_ACT;         /* CKSC_ATAUJD_ACT  */

    uint8  ucDummy112[12];                  /* Reserved         */

    uint32 ulCKSC_ATAUJD_STPM;              /* CKSC_ATAUJD_STPM */

    uint8  ucDummy113[228];                 /* Reserved         */

    uint32 ulCKSC_ARTCAS_CTL;               /* CKSC_ARTCAS_CTL  */

    uint8  ucDummy114[4];                   /* Reserved         */

    const uint32 ulCKSC_ARTCAS_ACT;         /* CKSC_ARTCAS_ACT  */

    uint8  ucDummy115[244];                 /* Reserved         */

    uint32 ulCKSC_ARTCAD_CTL;               /* CKSC_ARTCAD_CTL  */

    uint8  ucDummy116[4];                   /* Reserved         */

    const uint32 ulCKSC_ARTCAD_ACT;         /* CKSC_ARTCAD_ACT  */

    uint8  ucDummy117[12];                  /* Reserved         */

    uint32 ulCKSC_ARTCAD_STPM;              /* CKSC_ARTCAD_STPM */

    uint8  ucDummy118[228];                 /* Reserved         */

    uint32 ulCKSC_AADCAS_CTL;               /* CKSC_AADCAS_CTL  */

    uint8  ucDummy119[4];                   /* Reserved         */

    const uint32 ulCKSC_AADCAS_ACT;         /* CKSC_AADCAS_ACT  */

    uint8  ucDummy120[244];                 /* Reserved         */

    uint32 ulCKSC_AADCAD_CTL;               /* CKSC_AADCAD_CTL  */

    uint8  ucDummy121[4];                   /* Reserved         */

    const uint32 ulCKSC_AADCAD_ACT;         /* CKSC_AADCAD_ACT  */

    uint8  ucDummy122[12];                  /* Reserved         */

    uint32 ulCKSC_AADCAD_STPM;              /* CKSC_AADCAD_STPM */

    uint8  ucDummy123[228];                 /* Reserved         */

    uint32 ulCKSC_AFOUTS_CTL;               /* CKSC_AFOUTS_CTL  */

    uint8  ucDummy124[4];                   /* Reserved         */

    const uint32 ulCKSC_AFOUTS_ACT;         /* CKSC_AFOUTS_ACT  */

    uint8  ucDummy125[12];                  /* Reserved         */

    uint32 ulCKSC_AFOUTS_STPM;              /* CKSC_AFOUTS_STPM */

    uint8  ucDummy126[228];                 /* Reserved         */

    uint32 ulFOUTDIV;                       /* FOUTDIV          */

    const uint32 ulFOUTSTAT;                /* FOUTSTAT         */

    uint8  ucDummy127[26616];               /* Reserved         */

    uint32 ulPLLE;                          /* PLLE             */

    const uint32 ulPLLS;                    /* PLLS             */

    uint32 ulPLLC;                          /* PLLC             */

    uint8  ucDummy128[4084];                /* Reserved         */

    uint32 ulCKSC_CPUCLKS_CTL;              /* CKSC_CPUCLKS_CTL */

    uint8  ucDummy129[4];                   /* Reserved         */

    const uint32 ulCKSC_CPUCLKS_ACT;        /* CKSC_CPUCLKS_ACT */

    uint8  ucDummy130[4];                   /* Reserved         */

    uint32 ulCKSC_PPLLCLKS_CTL;             /* CKSC_PPLLCLKS_CTL*/

    uint8  ucDummy131[4];                   /* Reserved         */

    const uint32 ulCKSC_PPLLCLKS_ACT;       /* CKSC_PPLLCLKS_ACT*/

    uint8  ucDummy132[228];                 /* Reserved         */

    uint32 ulCKSC_CPUCLKD_CTL;              /* CKSC_CPUCLKD_CTL */

    uint8  ucDummy133[4];                   /* Reserved         */

    const uint32 ulCKSC_CPUCLKD_ACT;        /* CKSC_CPUCLKD_ACT */

    uint8  ucDummy134[244];                 /* Reserved         */

    uint32 ulCKSC_IPERI1S_CTL;              /* CKSC_IPERI1S_CTL */

    uint8  ucDummy135[4];                   /* Reserved         */

    const uint32 ulCKSC_IPERI1S_ACT;        /* CKSC_IPERI1S_ACT */

    uint8  ucDummy136[244];                 /* Reserved         */

    uint32 ulCKSC_IPERI2S_CTL;              /* CKSC_IPERI2S_CTL */

    uint8  ucDummy137[4];                   /* Reserved         */

    const uint32 ulCKSC_IPERI2S_ACT;        /* CKSC_IPERI2S_ACT */

    uint8  ucDummy138[244];                 /* Reserved         */

    uint32 ulCKSC_ILINS_CTL;                /* CKSC_ILINS_CTL   */

    uint8  ucDummy139[4];                   /* Reserved         */

    const uint32 ulCKSC_ILINS_ACT;          /* CKSC_ILINS_ACT   */

    uint8  ucDummy144[756];                 /* Reserved         */

    uint32 ulCKSC_PLLIS_CTL;                /* CKSC_PLLIS_CTL   */

    uint8  ucDummy145[4];                   /* Reserved         */

    const uint32 ulCKSC_PLLIS_ACT;          /* CKSC_PLLIS_ACT   */

    uint8  ucDummy146[244];                 /* Reserved         */

    uint32 ulCKSC_ILIND_CTL;                /* CKSC_ILIND_CTL   */

    uint8  ucDummy147[4];                   /* Reserved         */

    const uint32 ulCKSC_ILIND_ACT;          /* CKSC_ILIND_ACT   */

    uint8  ucDummy148[12];                  /* Reserved         */

    uint32 ulCKSC_ILIND_STPM;               /* CKSC_ILIND_STPM  */

    uint8  ucDummy149[228];                 /* Reserved         */

    uint32 ulCKSC_ICANS_CTL;                /* CKSC_ICANS_CTL   */

    uint8  ucDummy150[4];                   /* Reserved         */

    const uint32 ulCKSC_ICANS_ACT;          /* CKSC_ICANS_ACT   */

    uint8  ucDummy151[12];                  /* Reserved         */

    uint32 ulCKSC_ICANS_STPM;               /* CKSC_ICANS_STPM  */

    uint8  ucDummy152[228];                 /* Reserved         */

    uint32 ulCKSC_ICANOSCD_CTL;             /* CKSC_ICANOSCD_CTL*/

    uint8  ucDummy153[4];                   /* Reserved         */

    const uint32 ulCKSC_ICANOSCD_ACT;       /* CKSC_ICANOSCD_ACT*/

    uint8  ucDummy154[12];                  /* Reserved         */

    uint32 ulCKSC_ICANOSCD_STPM;            /* CKSC_ICANOSCD_STPM*/

    uint8  ucDummy155[228];                 /* Reserved         */

    uint32 ulCKSC_ICSIS_CTL;                /* CKSC_ICSIS_CTL   */

    uint8  ucDummy156[4];                   /* Reserved         */

    const uint32 ulCKSC_ICSIS_ACT;          /* CKSC_ICSIS_ACT   */

    uint8  ucDummy157[244];                 /* Reserved         */

    uint32 ulCKSC_IIICS_CTL;                /* CKSC_IIICS_CTL   */

    uint8  ucDummy158[4];                   /* Reserved         */

    const uint32 ulCKSC_IIICS_ACT;          /* CKSC_IIICS_ACT   */
} ClkCntlReg_S1;
/* End Msg(4:0639)-2 */
/* START Msg(4:0639)-2 */
typedef struct Stag_ClkCntl_Registers_S4
{                                                         /* Clk control      */

    uint32 ulROSCE;                         /* ROSCE            */

    const uint32 ulROSCS;                   /* ROSCS            */

    uint8  ucDummy100[16];                  /* Reserved         */

    uint32 ulROSCSTPM;                      /* ROSCSTPM         */

    uint32 ulROSCUT;                        /* ROSCUT           */

    uint8  ucDummy101[224];                 /* Reserved         */

    uint32 ulMOSCE;                         /* MOSCE            */

    const uint32 ulMOSCS;                   /* MOSCS            */

    uint32 ulMOSCC;                         /* MOSCC            */

    uint32 ulMOSCST;                        /* MOSCST           */

    uint8  ucDummy102[8];                   /* Reserved         */

    uint32 ulMOSCSTPM;                      /* MOSCSTPM         */

    uint32 ulMOSCM;                         /* MOSCM            */

    uint8  ucDummy103[224];                 /* Reserved         */

    uint32 ulSOSCE;                         /* SOSCE            */

    const uint32 ulSOSCS;                   /* SOSCS            */

    uint8  ucDummy104[4];                   /* Reserved         */

    uint32 ulSOSCST;                        /* SOSCST           */

    uint8  ucDummy105[3568];                /* Reserved         */

    uint32 ulCKSC_AWDTAD_CTL;               /* CKSC_AWDTAD_CTL  */

    uint8  ucDummy106[4];                   /* Reserved         */

    const uint32 ulCKSC_AWDTAD_ACT;         /* CKSC_AWDTAD_ACT  */

    uint8  ucDummy107[12];                  /* Reserved         */

    uint32 ulCKSC_AWDTAD_STPM;              /* CKSC_AWDTAD_STPM */

    uint8  ucDummy108[228];                 /* Reserved         */

    uint32 ulCKSC_ATAUJS_CTL;               /* CKSC_ATAUJS_CTL  */

    uint8  ucDummy109[4];                   /* Reserved         */

    const uint32 ulCKSC_ATAUJS_ACT;         /* CKSC_ATAUJS_ACT  */

    uint8  ucDummy110[244];                 /* Reserved         */

    uint32 ulCKSC_ATAUJD_CTL;               /* CKSC_ATAUJD_CTL  */

    uint8  ucDummy111[4];                   /* Reserved         */

    const uint32 ulCKSC_ATAUJD_ACT;         /* CKSC_ATAUJD_ACT  */

    uint8  ucDummy112[12];                  /* Reserved         */

    uint32 ulCKSC_ATAUJD_STPM;              /* CKSC_ATAUJD_STPM */

    uint8  ucDummy113[228];                 /* Reserved         */

    uint32 ulCKSC_ARTCAS_CTL;               /* CKSC_ARTCAS_CTL  */

    uint8  ucDummy114[4];                   /* Reserved         */

    const uint32 ulCKSC_ARTCAS_ACT;         /* CKSC_ARTCAS_ACT  */

    uint8  ucDummy115[244];                 /* Reserved         */

    uint32 ulCKSC_ARTCAD_CTL;               /* CKSC_ARTCAD_CTL  */

    uint8  ucDummy116[4];                   /* Reserved         */

    const uint32 ulCKSC_ARTCAD_ACT;         /* CKSC_ARTCAD_ACT  */

    uint8  ucDummy117[12];                  /* Reserved         */

    uint32 ulCKSC_ARTCAD_STPM;              /* CKSC_ARTCAD_STPM */

    uint8  ucDummy118[228];                 /* Reserved         */

    uint32 ulCKSC_AADCAS_CTL;               /* CKSC_AADCAS_CTL  */

    uint8  ucDummy119[4];                   /* Reserved         */

    const uint32 ulCKSC_AADCAS_ACT;         /* CKSC_AADCAS_ACT  */

    uint8  ucDummy120[244];                 /* Reserved         */

    uint32 ulCKSC_AADCAD_CTL;               /* CKSC_AADCAD_CTL  */

    uint8  ucDummy121[4];                   /* Reserved         */

    const uint32 ulCKSC_AADCAD_ACT;         /* CKSC_AADCAD_ACT  */

    uint8  ucDummy122[12];                  /* Reserved         */

    uint32 ulCKSC_AADCAD_STPM;              /* CKSC_AADCAD_STPM */

    uint8  ucDummy123[228];                 /* Reserved         */

    uint32 ulCKSC_AFOUTS_CTL;               /* CKSC_AFOUTS_CTL  */

    uint8  ucDummy124[4];                   /* Reserved         */

    const uint32 ulCKSC_AFOUTS_ACT;         /* CKSC_AFOUTS_ACT  */

    uint8  ucDummy125[12];                  /* Reserved         */

    uint32 ulCKSC_AFOUTS_STPM;              /* CKSC_AFOUTS_STPM */

    uint8  ucDummy126[228];                 /* Reserved         */

    uint32 ulFOUTDIV;                       /* FOUTDIV          */

    const uint32 ulFOUTSTAT;                /* FOUTSTAT         */

    uint8  ucDummy127[26616];               /* Reserved         */

    uint32 ulPLL0E;                         /* PLL0E            */

    const uint32 ulPLL0S;                   /* PLL0S            */

    uint32 ulPLL0C;                         /* PLL0C            */

    uint32 ulPLL0ST;                        /* PLL0ST           */

    uint8  ucDummy128[240];                 /* Reserved         */

    uint32 ulPLLE;                          /* PLL0E            */

    const uint32 ulPLLS;                    /* PLL0S            */

    uint32 ulPLLC;                          /* PLL0C            */

    uint8  ucDummy300[3828];                /* Reserved         */

    uint32 ulCKSC_CPUCLKS_CTL;              /* CKSC_CPUCLKS_CTL */

    uint8  ucDummy129[4];                   /* Reserved         */

    const uint32 ulCKSC_CPUCLKS_ACT;        /* CKSC_CPUCLKS_ACT */

    uint8  ucDummy130[4];                   /* Reserved         */

    uint32 ulCKSC_PPLLCLKS_CTL;             /* CKSC_PPLLCLKS_CTL*/

    uint8  ucDummy131[4];                   /* Reserved         */

    const uint32 ulCKSC_PPLLCLKS_ACT;       /* CKSC_PPLLCLKS_ACT*/

    uint8  ucDummy132[228];                 /* Reserved         */

    uint32 ulCKSC_CPUCLKD_CTL;              /* CKSC_CPUCLKD_CTL */

    uint8  ucDummy133[4];                   /* Reserved         */

    const uint32 ulCKSC_CPUCLKD_ACT;        /* CKSC_CPUCLKD_ACT */

    uint8  ucDummy134[244];                 /* Reserved         */

    uint32 ulCKSC_IPERI1S_CTL;              /* CKSC_IPERI1S_CTL */

    uint8  ucDummy135[4];                   /* Reserved         */

    const uint32 ulCKSC_IPERI1S_ACT;        /* CKSC_IPERI1S_ACT */

    uint8  ucDummy136[244];                 /* Reserved         */

    uint32 ulCKSC_IPERI2S_CTL;              /* CKSC_IPERI2S_CTL */

    uint8  ucDummy137[4];                   /* Reserved         */

    const uint32 ulCKSC_IPERI2S_ACT;        /* CKSC_IPERI2S_ACT */

    uint8  ucDummy138[244];                 /* Reserved         */

    uint32 ulCKSC_ILINS_CTL;                /* CKSC_ILINS_CTL   */

    uint8  ucDummy139[4];                   /* Reserved         */

    const uint32 ulCKSC_ILINS_ACT;          /* CKSC_ILINS_ACT   */

    uint8  ucDummy140[244];                 /* Reserved         */

    uint32 ulCKSC_IADCAS_CTL;               /* CKSC_IADCAS_CTL  */

    uint8  ucDummy141[4];                   /* Reserved         */

    const uint32 ulCKSC_IADCAS_ACT;         /* CKSC_IADCAS_ACT  */

    uint8  ucDummy142[244];                 /* Reserved         */

    uint32 ulCKSC_IADCAD_CTL;               /* CKSC_IADCAD_CTL  */

    uint8  ucDummy143[4];                   /* Reserved         */

    const uint32 ulCKSC_IADCAD_ACT;         /* CKSC_IADCAD_ACT  */

    uint8  ucDummy144[244];                 /* Reserved         */

    uint32 ulCKSC_PLL0IS_CTL;               /* CKSC_PLL0IS_CTL  */

    uint8  ucDummy145[4];                   /* Reserved         */

    const uint32 ulCKSC_PLL0IS_ACT;         /* CKSC_PLL0IS_ACT  */

    uint8  ucDummy146[4];                   /* Reserved         */

    uint32 ulCKSC_PLLIS_CTL;                /* CKSC_PLL1IS_CTL  */

    uint8  ucDummy301[4];                   /* Reserved         */

    const uint32 ulCKSC_PLLIS_ACT;          /* CKSC_PLL1IS_ACT  */

    uint8  ucDummy302[228];                 /* Reserved         */

    uint32 ulCKSC_ILIND_CTL;                /* CKSC_ILIND_CTL   */

    uint8  ucDummy147[4];                   /* Reserved         */

    const uint32 ulCKSC_ILIND_ACT;          /* CKSC_ILIND_ACT   */

    uint8  ucDummy148[12];                  /* Reserved         */

    uint32 ulCKSC_ILIND_STPM;               /* CKSC_ILIND_STPM  */

    uint8  ucDummy149[228];                 /* Reserved         */

    uint32 ulCKSC_ICANS_CTL;                /* CKSC_ICANS_CTL   */

    uint8  ucDummy150[4];                   /* Reserved         */

    const uint32 ulCKSC_ICANS_ACT;          /* CKSC_ICANS_ACT   */

    uint8  ucDummy151[12];                  /* Reserved         */

    uint32 ulCKSC_ICANS_STPM;               /* CKSC_ICANS_STPM  */

    uint8  ucDummy152[228];                 /* Reserved         */

    uint32 ulCKSC_ICANOSCD_CTL;             /* CKSC_ICANOSCD_CTL*/

    uint8  ucDummy153[4];                   /* Reserved         */

    const uint32 ulCKSC_ICANOSCD_ACT;       /* CKSC_ICANOSCD_ACT*/

    uint8  ucDummy154[12];                  /* Reserved         */

    uint32 ulCKSC_ICANOSCD_STPM;            /* CKSC_ICANOSCD_STPM*/

    uint8  ucDummy155[228];                 /* Reserved         */

    uint32 ulCKSC_ICSIS_CTL;                /* CKSC_ICSIS_CTL   */

    uint8  ucDummy156[4];                   /* Reserved         */

    const uint32 ulCKSC_ICSIS_ACT;          /* CKSC_ICSIS_ACT   */

    uint8  ucDummy157[244];                 /* Reserved         */

    uint32 ulCKSC_IIICS_CTL;                /* CKSC_IIICS_CTL   */

    uint8  ucDummy158[4];                   /* Reserved         */

    const uint32 ulCKSC_IIICS_ACT;          /* CKSC_IIICS_ACT   */
} ClkCntlReg_S4;
/* End Msg(4:0639)-2 */
/* START Msg(4:0639)-2 */
typedef struct Stag_ClkCntl_Registers_S2
{                                                         /* Clk control      */

    uint32 ulROSCE;                         /* ROSCE            */

    const uint32 ulROSCS;                   /* ROSCS            */

    uint8  ucDummy100[16];                  /* Reserved         */

    uint32 ulROSCSTPM;                      /* ROSCSTPM         */

    uint32 ulROSCUT;                        /* ROSCUT           */

    uint8  ucDummy101[224];                 /* Reserved         */

    uint32 ulMOSCE;                         /* MOSCE            */

    const uint32 ulMOSCS;                   /* MOSCS            */

    uint32 ulMOSCC;                         /* MOSCC            */

    uint32 ulMOSCST;                        /* MOSCST           */

    uint8  ucDummy102[8];                   /* Reserved         */

    uint32 ulMOSCSTPM;                      /* MOSCSTPM         */

    uint32 ulMOSCM;                         /* MOSCM            */

    uint8  ucDummy103[224];                 /* Reserved         */

    uint32 ulSOSCE;                         /* SOSCE            */

    const uint32 ulSOSCS;                   /* SOSCS            */

    uint8  ucDummy104[4];                   /* Reserved         */

    uint32 ulSOSCST;                        /* SOSCST           */

    uint8  ucDummy105[3568];                /* Reserved         */

    uint32 ulCKSC_AWDTAD_CTL;               /* CKSC_AWDTAD_CTL  */

    uint8  ucDummy106[4];                   /* Reserved         */

    const uint32 ulCKSC_AWDTAD_ACT;         /* CKSC_AWDTAD_ACT  */

    uint8  ucDummy107[12];                  /* Reserved         */

    uint32 ulCKSC_AWDTAD_STPM;              /* CKSC_AWDTAD_STPM */

    uint8  ucDummy108[228];                 /* Reserved         */

    uint32 ulCKSC_ATAUJS_CTL;               /* CKSC_ATAUJS_CTL  */

    uint8  ucDummy109[4];                   /* Reserved         */

    const uint32 ulCKSC_ATAUJS_ACT;         /* CKSC_ATAUJS_ACT  */

    uint8  ucDummy110[244];                 /* Reserved         */

    uint32 ulCKSC_ATAUJD_CTL;               /* CKSC_ATAUJD_CTL  */

    uint8  ucDummy111[4];                   /* Reserved         */

    const uint32 ulCKSC_ATAUJD_ACT;         /* CKSC_ATAUJD_ACT  */

    uint8  ucDummy112[12];                  /* Reserved         */

    uint32 ulCKSC_ATAUJD_STPM;              /* CKSC_ATAUJD_STPM */

    uint8  ucDummy113[228];                 /* Reserved         */

    uint32 ulCKSC_ARTCAS_CTL;               /* CKSC_ARTCAS_CTL  */

    uint8  ucDummy114[4];                   /* Reserved         */

    const uint32 ulCKSC_ARTCAS_ACT;         /* CKSC_ARTCAS_ACT  */

    uint8  ucDummy115[244];                 /* Reserved         */

    uint32 ulCKSC_ARTCAD_CTL;               /* CKSC_ARTCAD_CTL  */

    uint8  ucDummy116[4];                   /* Reserved         */

    const uint32 ulCKSC_ARTCAD_ACT;         /* CKSC_ARTCAD_ACT  */

    uint8  ucDummy117[12];                  /* Reserved         */

    uint32 ulCKSC_ARTCAD_STPM;              /* CKSC_ARTCAD_STPM */

    uint8  ucDummy118[228];                 /* Reserved         */

    uint32 ulCKSC_AADCAS_CTL;               /* CKSC_AADCAS_CTL  */

    uint8  ucDummy119[4];                   /* Reserved         */

    const uint32 ulCKSC_AADCAS_ACT;         /* CKSC_AADCAS_ACT  */

    uint8  ucDummy120[244];                 /* Reserved         */

    uint32 ulCKSC_AADCAD_CTL;               /* CKSC_AADCAD_CTL  */

    uint8  ucDummy121[4];                   /* Reserved         */

    const uint32 ulCKSC_AADCAD_ACT;         /* CKSC_AADCAD_ACT  */

    uint8  ucDummy122[12];                  /* Reserved         */

    uint32 ulCKSC_AADCAD_STPM;              /* CKSC_AADCAD_STPM */

    uint8  ucDummy123[228];                 /* Reserved         */

    uint32 ulCKSC_AFOUTS_CTL;               /* CKSC_AFOUTS_CTL  */

    uint8  ucDummy124[4];                   /* Reserved         */

    const uint32 ulCKSC_AFOUTS_ACT;         /* CKSC_AFOUTS_ACT  */

    uint8  ucDummy125[12];                  /* Reserved         */

    uint32 ulCKSC_AFOUTS_STPM;              /* CKSC_AFOUTS_STPM */

    uint8  ucDummy126[228];                 /* Reserved         */

    uint32 ulFOUTDIV;                       /* FOUTDIV          */

    const uint32 ulFOUTSTAT;                /* FOUTSTAT         */

    uint8  ucDummy127[26616];               /* Reserved         */

    uint32 ulPLL0E;                         /* PLL0E            */

    const uint32 ulPLL0S;                   /* PLL0S            */

    uint32 ulPLL0C;                         /* PLL0C            */

    uint32 ulPLL0ST;                        /* PLL0ST           */

    uint8  ucDummy128[240];                 /* Reserved         */

    uint32 ulPLLE;                          /* PLL0E            */

    const uint32 ulPLLS;                    /* PLL0S            */

    uint32 ulPLLC;                          /* PLL0C            */

    uint8  ucDummy300[3828];                /* Reserved         */

    uint32 ulCKSC_CPUCLKS_CTL;              /* CKSC_CPUCLKS_CTL */

    uint8  ucDummy129[4];                   /* Reserved         */

    const uint32 ulCKSC_CPUCLKS_ACT;        /* CKSC_CPUCLKS_ACT */

    uint8  ucDummy130[4];                   /* Reserved         */

    uint32 ulCKSC_PPLLCLKS_CTL;             /* CKSC_PPLLCLKS_CTL*/

    uint8  ucDummy131[4];                   /* Reserved         */

    const uint32 ulCKSC_PPLLCLKS_ACT;       /* CKSC_PPLLCLKS_ACT*/

    uint8  ucDummy132[228];                 /* Reserved         */

    uint32 ulCKSC_CPUCLKD_CTL;              /* CKSC_CPUCLKD_CTL */

    uint8  ucDummy133[4];                   /* Reserved         */

    const uint32 ulCKSC_CPUCLKD_ACT;        /* CKSC_CPUCLKD_ACT */

    uint8  ucDummy134[244];                 /* Reserved         */

    uint32 ulCKSC_IPERI1S_CTL;              /* CKSC_IPERI1S_CTL */

    uint8  ucDummy135[4];                   /* Reserved         */

    const uint32 ulCKSC_IPERI1S_ACT;        /* CKSC_IPERI1S_ACT */

    uint8  ucDummy136[244];                 /* Reserved         */

    uint32 ulCKSC_IPERI2S_CTL;              /* CKSC_IPERI2S_CTL */

    uint8  ucDummy137[4];                   /* Reserved         */

    const uint32 ulCKSC_IPERI2S_ACT;        /* CKSC_IPERI2S_ACT */

    uint8  ucDummy138[244];                 /* Reserved         */

    uint32 ulCKSC_ILINS_CTL;                /* CKSC_ILINS_CTL   */

    uint8  ucDummy139[4];                   /* Reserved         */

    const uint32 ulCKSC_ILINS_ACT;          /* CKSC_ILINS_ACT   */

    uint8  ucDummy140[244];                 /* Reserved         */

    uint32 ulCKSC_IADCAS_CTL;               /* CKSC_IADCAS_CTL  */

    uint8  ucDummy141[4];                   /* Reserved         */

    const uint32 ulCKSC_IADCAS_ACT;         /* CKSC_IADCAS_ACT  */

    uint8  ucDummy142[244];                 /* Reserved         */

    uint32 ulCKSC_IADCAD_CTL;               /* CKSC_IADCAD_CTL  */

    uint8  ucDummy143[4];                   /* Reserved         */

    const uint32 ulCKSC_IADCAD_ACT;         /* CKSC_IADCAD_ACT  */

    uint8  ucDummy144[244];                 /* Reserved         */

    uint32 ulCKSC_PLL0IS_CTL;               /* CKSC_PLL0IS_CTL  */

    uint8  ucDummy145[4];                   /* Reserved         */

    const uint32 ulCKSC_PLL0IS_ACT;         /* CKSC_PLL0IS_ACT  */

    uint8  ucDummy146[4];                   /* Reserved         */

    uint32 ulCKSC_PLLIS_CTL;                /* CKSC_PLL1IS_CTL  */

    uint8  ucDummy301[4];                   /* Reserved         */

    const uint32 ulCKSC_PLLIS_ACT;          /* CKSC_PLL1IS_ACT  */

    uint8  ucDummy302[228];                 /* Reserved         */

    uint32 ulCKSC_ILIND_CTL;                /* CKSC_ILIND_CTL   */

    uint8  ucDummy147[4];                   /* Reserved         */

    const uint32 ulCKSC_ILIND_ACT;          /* CKSC_ILIND_ACT   */

    uint8  ucDummy148[12];                  /* Reserved         */

    uint32 ulCKSC_ILIND_STPM;               /* CKSC_ILIND_STPM  */

    uint8  ucDummy149[228];                 /* Reserved         */

    uint32 ulCKSC_ICANS_CTL;                /* CKSC_ICANS_CTL   */

    uint8  ucDummy150[4];                   /* Reserved         */

    const uint32 ulCKSC_ICANS_ACT;          /* CKSC_ICANS_ACT   */

    uint8  ucDummy151[12];                  /* Reserved         */

    uint32 ulCKSC_ICANS_STPM;               /* CKSC_ICANS_STPM  */

    uint8  ucDummy152[228];                 /* Reserved         */

    uint32 ulCKSC_ICANOSCD_CTL;             /* CKSC_ICANOSCD_CTL*/

    uint8  ucDummy153[4];                   /* Reserved         */

    const uint32 ulCKSC_ICANOSCD_ACT;       /* CKSC_ICANOSCD_ACT*/

    uint8  ucDummy154[12];                  /* Reserved         */

    uint32 ulCKSC_ICANOSCD_STPM;            /* CKSC_ICANOSCD_STPM*/

    uint8  ucDummy155[228];                 /* Reserved         */

    uint32 ulCKSC_ICSIS_CTL;                /* CKSC_ICSIS_CTL   */

    uint8  ucDummy156[4];                   /* Reserved         */

    const uint32 ulCKSC_ICSIS_ACT;          /* CKSC_ICSIS_ACT   */

    uint8  ucDummy157[244];                 /* Reserved         */

    uint32 ulCKSC_IIICS_CTL;                /* CKSC_IIICS_CTL   */

    uint8  ucDummy158[4];                   /* Reserved         */

    const uint32 ulCKSC_IIICS_ACT;          /* CKSC_IIICS_ACT   */
} ClkCntlReg_S2;
/* End Msg(4:0639)-2 */
typedef struct Stag_ClkMntr_Register
{                                                         /* CLMA registers   */
    uint8  ucCTL0;                          /* CTL0             */

    uint8  ucDummy159[7];                   /* Reserved         */

    uint16 usCMPL;                          /* CMPL             */

    uint8  ucDummy160[2];                   /* Reserved         */

    uint16 usCMPH;                          /* CMPH             */

    uint8  ucDummy161[2];                   /* Reserved         */

    uint8  ucPCMD;                          /* PCMD             */

    uint8  ucDummy162[3];                   /* Reserved         */

    const uint8  ucPS;                      /* PS               */

    uint8  ucDummy163[3];                   /* Reserved         */

    uint8  ucEMU0;                          /* EMU0             */
} ClkMntrReg;

typedef struct Stag_CmnClkMntr_Register
{                                                         /* Common CLM regs  */
    uint32 ulTEST;                          /* TEST             */

    const uint32 ulTESTS;                   /* TESTS            */

    uint8  ucDummy164[248];                 /* Reserved         */

    uint32 ulPROTCMDCLMA;                   /* PROTCMDCLMA      */

    const uint32 ulPROTSCLMA;               /* PROTSCLMA        */
} CmnClkMntrReg;

typedef struct Stag_STBC0_Registers
{                                                         /* STBC0 Registers  */
    uint32 ulPSC;                           /* PSC              */

    uint8  ucDummy165[12];                  /* Reserved         */

    uint32 ulSTPT;                          /* STPT             */
} STBC0Reg;

typedef struct Stag_WUF_Registers
{                                                         /* WUF registers    */
    const uint32 ulWUF0;                    /* WUF0             */

    uint32 ulWUFMSK0;                       /* WUFMSK0          */

    uint32 ulWUFC0;                         /* WUFC0            */
} WUFReg;

typedef struct Stag_LPS_Registers                         /* LPS registers    */
{
    uint32 ulSCTLR;                         /* SCTLR            */

    uint32 ulEVFR;                          /* EVFR             */

    uint32 ulDPSELR0;                       /* DPSELR0          */

    uint32 ulDPSELRM;                       /* DPSELRM          */

    uint32 ulDPSELRH;                       /* DPSELRH          */

    uint32 ulDPDSR0;                        /* DPDSR0           */

    uint32 ulDPDSRM;                        /* DPDSRM           */

    uint32 ulDPDSRH;                        /* DPDSRH           */

    const uint32 ulDPDIMR0;                 /* DPDIMR0          */

    const uint8  ucDPDIMR1;                 /* DPDIMR1          */

    uint8  ucDummy166[3];                   /* Reserved         */

    const uint8  ucDPDIMR2;                 /* DPDIMR2          */

    uint8  ucDummy167[3];                   /* Reserved         */

    const uint8  ucDPDIMR3;                 /* DPDIMR3          */

    uint8  ucDummy168[3];                   /* Reserved         */

    const uint8  ucDPDIMR4;                 /* DPDIMR4          */

    uint8  ucDummy169[3];                   /* Reserved         */

    const uint8  ucDPDIMR5;                 /* DPDIMR5          */

    uint8  ucDummy170[3];                   /* Reserved         */

    const uint8  ucDPDIMR6;                 /* DPDIMR6          */

    uint8  ucDummy171[3];                   /* Reserved         */

    const uint8  ucDPDIMR7;                 /* DPDIMR7          */

    uint8  ucDummy172[3];                   /* Reserved         */

    uint16 usCNTVAL;                        /* CNTVAL           */

    uint8  ucDummy173[2];                   /* Reserved         */

    const uint8  ucSOSTR;                   /* SOSTR            */
} LPSReg;

typedef struct Stag_WriteProt_Registers
{                                                         /* Write protect    */
    uint32 ulPROTCMD0;                      /* PROTCMD0         */

    const uint32 ulPROTS0;                  /* PROTS0           */

    uint8  ucDummy174[32760];               /* Reserved         */

    uint32 ulPROTCMD1;                      /* PROTCMD1         */

    const uint32 ulPROTS1;                  /* PROTS1           */
} WPROTReg;

typedef struct Stag_CANController_Registers
{
    uint32 ulGCFG;                          /* GCFG             */

    uint32 ulGCTR;                          /* GCTR             */

    uint32 ulGSTS;                          /* GSTS             */

    uint32 ulGERFL;                         /* GERFL            */

    uint32 ulGTSC;                          /* GTSC             */

    uint32 ulGAFLECTR;                      /* GAFLECTR         */

    uint32 ulGAFLCFG0;                      /* GAFLCFG0         */

    uint32 ulGAFLCFG1;                      /* GAFLCFG1         */

    uint32 ulRMNB;                          /* RMNB             */

    uint8  ucdummy175[952];                 /* Reserved         */

    uint32 ulGTINTSTS0;                     /* GTINTSTS0          */

    uint32 ulGTINTSTS1;                     /* GTINTSTS0         */

    uint32 ulGTSTCFG;                       /* GTSTCFG          */

    uint32 ulGTSTCTR;                       /* GTSTCTR          */

    uint8  ucdummy289[4];                   /* Reserved         */

    uint32 ulGFDCFG;                        /*GFDCFG */

    uint8  ucdummy290[4];                   /* Reserved          */

    uint32 ulGLOCKK;                        /* GLOCKK           */

    uint8  ucdummy291[124];                 /* Reserved         */

    uint32 ulGRMCFG;                        /* GRMCFG            */

}CANGblReg;

typedef struct Stag_CANChannel_Registers
{
    uint32 ulCFG;                           /* C0CFG            */

    uint32 ulCTR;                           /* C0CTR            */

    uint32 ulSTS;                           /* C0STS            */

    uint32 ulERFL;                          /* ERFL             */
}CANChReg;

typedef struct Stag_CANTXQ_Registers
{
    uint32 ulTXQCC;                         /* TXQCC0           */

    uint8  ucdummy178[28];                  /* Reserved        */

    uint32 ulTXQSTS;                        /* TXQSTS0          */

    uint8  ucdummy179[28];                  /* Reserved        */

    uint32 ulTXQPCTR;                       /* TXQPCTR0         */
}CANTxqReg;

typedef struct Stag_CANTHL_Registers
{
    uint32 ulTHLCC;                         /* THLCC0            */

    uint8  ucdummy181[28];                  /* Reserved         */

    uint32 ulTHLSTS;                        /* THLCC0           */

    uint8  ucdummy182[28];                  /* Reserved         */

    uint32 ulTHLPCTR;                       /* THLCC0           */

    uint8  ucdummy183[5052];                /* Reserved         */

    uint32 ulTHLACC;                        /* THLACC0          */

    uint8  ucdummy184[18428];               /* Reserved         */

    uint32 ulFDTHLACC;                      /* THLACC0          */
}CANThlReg;


typedef struct Stag_CAN_ReceiveRule
{
    uint32 ulGAFLID;                        /* GAFLID0          */

    uint32 ulGAFLM;                         /* GAFLM0           */

    uint32 ulGAFLP0;                        /* GAFLP0_0         */

    uint32 ulGAFLP1;                        /* GAFLP1_0         */
}CANRRuleReg;

typedef struct Stag_CAN_ComFIFO1
{
    uint32 ulCFCC;                          /* CFCC0            */

    uint8  ucdummy184[92];                  /* Reserved         */

    uint32 ulCFSTS;                         /* CFSTS0           */

    uint8  ucdummy185[92];                  /* Reserved         */

    uint32 ulCFPCTR;                        /* CFPCTR0          */
}CANCFIFOReg1;

typedef struct Stag_CAN_ComFIFO2
{
    uint32 ulCFID;                          /* CFID0            */

    uint32 ulCFPTR;                         /* CFPTR0           */

    uint32 ulCFDF0;                         /* CFDF0_0          */

    uint32 ulCFDF1;                         /* CFDF1_0          */
}CANCFIFOReg2;

/* FIFO status-related registers */
typedef struct Stag_CAN_FIFOStatus
{
    uint32 ulFESTS;                         /* FESTS           */

    uint32 ulFFSTS;                         /* FFSTS           */

    uint32 ulFMSTS;                         /* FMSTS           */

    uint32 ulRFISTS;                        /* RFISTS          */

    uint32 ulCFRISTS;                       /* CFRISTS         */

    uint32 ulCFTISTS;                       /* CFTISTS         */
}CANFIFOStatusReg;

typedef struct Stag_CAN_HrhFIFO
{
    uint32 ulRFCC;                          /* RFCC0            */

    uint8  ucdummy287[28];                  /* Reserved         */

    uint32 ulRFSTS;                         /* RFSTS0           */

    uint8  ucdummy288[28];                  /* Reserved         */

    uint32 ulRFPCTR;                        /* RFPCTR0          */


}CANHRTFIFOReg1;

typedef struct Stag_CAN_HrhFIFO2
{
    uint32 ulRFID;                          /* RFID0           */

    uint32 ulRFPTR;                         /* RFPTR0           */

    uint32 ulRFDF0;                         /* RFDF0_0          */

    uint32 ulRFDF1;                         /* RFDF1_0          */

}CANHRTFIFOReg2;


typedef struct Stag_CAN_FIFODMA
{
    uint32 ulCDTCT;                         /* CDTCT           */
    uint32 ulCDTSTS;                        /* CDTSTS          */
}CANFIFIODMAReg;

typedef struct Stag_CAN_TransmitBuffControl
{
    uint32 TMTRSTS;                         /* TMTRSTS_0          */

    uint32 TMTARSTS;                        /* TMTARSTS_0         */

    uint32 TMTCSTS;                         /* TMTCSTS_0          */

    uint32 TMTASTS;                         /* TMTASTS_0          */
}CANTransmitBuffControlReg;

typedef struct STag_CAN_Hrh
{
    uint32 ulRMID;                          /* RMID0            */

    uint32 ulRMPTR;                         /* RMPTR0           */

    uint32 ulRMDF0;                         /* RMDF0_0          */

    uint32 ulRMDF1;                         /* RMDF1_0          */
}CANHrhReg;

typedef struct STag_CAN_Hth1
{
    uint8 ucTMC;                            /* TMC0             */

    uint8 ucdummy190[127];                  /* Reserved         */

    uint8 ucTMSTS;                          /* TMSTS0           */
}CANHthReg1;

typedef struct STag_CAN_Hth2
{
    uint32 ulTMID;                          /* TMID0            */

    uint32 ulTMPTR;                         /* TMPTR0           */

    uint32 ulTMDF0;                         /* TMDF0_0          */
}CANHthReg2;

/*Channel-related registers */

typedef struct STag_CAN_FDChannel
{
    uint32        ulDCFG;

    uint32        ulFDCFG;

    uint32        ulFDCTR;

    uint32        ulFDSTS;

    uint32        ulFDCRC;
}CANFDChReg;

typedef struct STag_CANRamTstReg
{
    uint32 ulRPGACC[64];                    /* RPGACC           */
}CANRamTstReg;

typedef struct Stag_CANFD_ReceiveRule
{
    uint32 ulFDGAFLID;                      /* GAFLID0          */

    uint32 ulFDGAFLM;                       /* GAFLM0           */

    uint32 ulFDGAFLP0;                      /* GAFLP0_0         */

    uint32 ulFDGAFLP1;                      /* GAFLP1_0         */
}CANFDRRuleReg;

typedef struct STag_CANFD_Hrh
{
    uint32 ulFDRMID;                        /* FDRMID    */

    uint32 ulFDRMPTR;                       /* FDRMPTR   */

    uint32 ulFDRMSTS;                       /* FDRMSTS    */

    uint32 ulFDRMDF0;                       /* FDRMDF0_0   */

    uint32 ulFDRMDF1;                       /* FDRMDF1_0   */

    uint32 ulFDRMDF2;                       /* FDRMDF2_0   */

    uint32 ulFDRMDF3;                       /* FDRMDF3_0   */

    uint32 ulFDRMDF4;                       /* FDRMDF4_0   */
}CANFDHrhReg;

typedef struct Stag_CANFD_HrhFIFO
{
    uint32 ulFDRFID;                        /* RFID0       */

    uint32 ulFDRFPTR;                       /* RFPTR0      */

    uint32 ulRFFDSTS;                       /* RFFDSTS     */

    uint32 ulFDRFDF0;                       /* RFDF0_0     */

    uint32 ulFDRFDF1;                       /* RFDF1_0     */

    uint32 ulFDRFDF2;                       /* RFDF2_0     */

    uint32 ulFDRFDF3;                       /* RFDF3_0     */

    uint32 ulFDRFDF4;                       /* RFDF4_0     */

    uint32 ulFDRFDF5;                       /* RFDF5_0     */

    uint32 ulFDRFDF6;                       /* RFDF6_0     */

    uint32 ulFDRFDF7;                       /* RFDF7_0     */

    uint32 ulFDRFDF8;                       /* RFDF8_0     */

    uint32 ulFDRFDF9;                       /* RFDF9_0     */

    uint32 ulFDRFDF10;                      /* RFDF10_0     */

    uint32 ulFDRFDF11;                      /* RFDF11_0     */

    uint32 ulFDRFDF12;                      /* RFDF12_0     */

    uint32 ulFDRFDF13;                      /* RFDF13_0     */

    uint32 ulFDRFDF14;                      /* RFDF14_0     */

    uint32 ulFDRFDF15;                      /* RFDF15_0     */
}CANFDHRTFIFOReg;

typedef struct Stag_CANFD_ComFIFO
{
    uint32 ulFDCFID;                        /* CFID0         */

    uint32 ulFDCFPTR;                       /* CFPTR0        */

    uint32 ulFDCSTS;                        /* FDCFFDCST        */

    uint32 ulFDCFDF0;                       /* CFDF0_0         */

    uint32 ulFDCFDF1;                       /* CFDF1_0         */

    uint32 ulFDCFDF2;                       /* CFDF2_0         */

    uint32 ulFDCFDF3;                       /* CFDF3_0         */

    uint32 ulFDCFDF4;                       /* CFDF4_0         */

    uint32 ulFDCFDF5;                       /* CFDF5_0         */

    uint32 ulFDCFDF6;                       /* CFDF6_0         */

    uint32 ulFDCFDF7;                       /* CFDF7_0         */

    uint32 ulFDCFDF8;                       /* CFDF8_0         */

    uint32 ulFDCFDF9;                       /* CFDF9_0         */

    uint32 ulFDCFDF10;                      /* CFDF10_0      */

    uint32 ulFDCFDF11;                      /* CFDF11_0      */

    uint32 ulFDCFDF12;                      /* CFDF12_0      */

    uint32 ulFDCFDF13;                      /* CFDF13_0      */

    uint32 ulFDCFDF14;                      /* CFDF14_0      */

    uint32 ulFDCFDF15;                      /* CFDF15_0      */
}CANFDCFIFOReg;

typedef struct STag_CANFD_Hth
{
    uint32 ulFDTMID;                        /* TMID0       */

    uint32 ulFDTMPTR;                       /* TMPTR0      */

    uint32 ulTMFDCTR;                       /* FDTMFDCTR0   */

    uint32 ulFDTMDF0;                       /* FDTMDF0_0 */

    uint32 ulFDTMDF1;                       /* FDTMDF1_0 */

    uint32 ulFDTMDF2;                       /* FDTMDF2_0 */

    uint32 ulFDTMDF3;                       /* FDTMDF3_0 */

    uint32 ulFDTMDF4;                       /* FDTMDF4_0 */
}CANFDHthReg;

typedef struct STag_TAUDBUnitUserReg
{
    uint16 usTOL;                           /* TOL              */

    uint8 ucdummy192[2];                    /* Reserved         */

    uint16 usRDT;                           /* RDT              */

    uint8 ucdummy193[2];                    /* Reserved         */

    uint16 usRSF;                           /* RSF              */

    uint8 ucdummy272[2];                    /* Reserved         */

    uint16 usTRO;                           /* TRO              */

    uint8 ucdummy194[2];                    /* Reserved         */

    uint16 usTME;                           /* TME              */

    uint8 ucdummy195[2];                    /* Reserved         */

    uint16 usTDL;                           /* TDL              */

    uint8 ucdummy196[2];                    /* Reserved         */

    uint16 usTO;                            /* TO               */

    uint8 ucdummy197[2];                    /* Reserved         */

    uint16 usTOE;                           /* TOE              */

    uint8 ucdummy198[354];                  /* Reserved         */

    uint16 usTE;                            /* TE               */

    uint8 ucdummy199[2];                    /* Reserved         */

    uint16 usTS;                            /* TS               */

    uint8 ucdummy200[2];                    /* Reserved         */

    uint16 usTT;                            /* TT               */
}TAUDBUserReg;

typedef struct STag_TAUDBUnitOsReg
{
    uint16 usTPS;                           /* TPS              */

    uint8 ucdummy201[2];                    /* Reserved         */

    uint8  ucBRS;                           /* BRS              */

    uint8  ucdummy202[3];                   /* Reserved         */

    uint16 usTOM;                           /* TOM              */

    uint8 ucdummy203[2];                    /* Reserved         */

    uint16 usTOC;                           /* TOC              */

    uint8 ucdummy204[2];                    /* Reserved         */

    uint16 usTDE;                           /* TDE              */

    uint8 ucdummy205[2];                    /* Reserved         */

    uint16 usTDM;                           /* TDM              */

    uint8 ucdummy206[2];                    /* Reserved         */

    uint16 usTRE;                           /* TRE              */

    uint8 ucdummy207[2];                    /* Reserved         */

    uint16 usTRC;                           /* TRC              */

    uint8 ucdummy208[2];                    /* Reserved         */

    uint16 usRDE;                           /* RDE              */

    uint8 ucdummy209[2];                    /* Reserved         */

    uint16 usRDM;                           /* RDM              */

    uint8 ucdummy210[2];                    /* Reserved         */

    uint16 usRDS;                           /* RDS              */

    uint8 ucdummy211[2];                    /* Reserved         */

    uint16 usRDC;                           /* RDC              */
}TAUDBOsReg;

typedef struct STag_TAUJUnitUserReg
{
    uint8 ucTE;                             /* TE               */

    uint8 ucdummy212[3];                    /* Reserved         */

    uint8 ucTS;                             /* TS               */

    uint8 ucdummy213[3];                    /* Reserved         */

    uint8 ucTT;                             /* TT               */

    uint8 ucdummy214[3];                    /* Reserved         */

    uint8 ucTO;                             /* TO               */

    uint8 ucdummy215[3];                    /* Reserved         */

    uint8 ucTOE;                            /* TOE              */

    uint8 ucdummy216[3];                    /* Reserved         */

    uint8 ucTOL;                            /* TOL              */

    uint8 ucdummy217[3];                    /* Reserved         */

    uint8 ucRDT;                            /* RDT              */

    uint8 ucdummy267[3];                    /* Reserved          */

    uint8 ucRSF;                            /* RSF              */

    uint8 ucdummy275[16];                   /* Reserved          */

}TAUJUserReg;

typedef struct STag_TAUJUnitOsRegs
{
    uint16 usTPS;                           /* TPS              */

    uint8 ucdummy218[2];                    /* Reserved         */

    uint8 ucBRS;                            /* BRS              */

    uint8 ucdummy219[3];                    /* Reserved         */

    uint8 ucTOM;                            /* TOM              */

    uint8 ucdummy220[3];                    /* Reserved         */

    uint8 ucTOC;                            /* TOC              */

    uint8 ucdummy221[3];                    /* Reserved         */

    uint8 ucRDE;                            /* RDE              */

    uint8 ucdummy222[3];                    /* Reserved         */

    uint8 ucRDM;                            /* RDM              */
}TAUJOsReg;

typedef struct STag_TAUDBUserReg
{
    uint16 usCDR;                           /* CDR              */

    uint16 usDummy223[63];                  /* Reserved         */

    uint16 usCNT;                           /* CNT              */

    uint16 usDummy224[31];                  /* Reserved         */

    uint8  ucCMUR;                          /* CMUR             */

    uint8 ucdummy225[127];                  /* Reserved         */

    uint8  ucCSR;                           /* CSR              */

    uint8 ucdummy270[63];                   /* Reserved         */

    uint8  ucCSC;                           /* CSC              */

    uint8 ucdummy268[127];                  /* Reserved         */

    uint16 usCMOR;                          /* CMOR             */
}TAUDBChReg;

typedef struct STag_TAUJUserReg
{
    uint32 ulCDR;                           /* CDR              */

    uint8 ucdummy226[12];                   /* Reserved         */

    uint32 ulCNT;                           /* CNT             */

    uint8 ucdummy227[12];                   /* Reserved         */

    uint8 ucCMUR;                           /* CMUR             */

    uint8 ucdummy269[15];                   /* Reserved         */

    uint8 ucCSR;                            /* CSR              */

    uint8 ucdummy271[15];                   /* Reserved         */

    uint8 ucCSC;                            /* CSC              */

    uint8 ucdummy228[63];                   /* Reserved         */

    uint16 usCMOR;                          /* CMOR             */
}TAUJChReg;

typedef struct STag_OSTMUnitUserRegs
{
    uint32 ulCMP;                           /* CMP              */

    uint32 ulCNT;                           /* CNT              */

    uint8 ucdummy229[8];                    /* Reserved         */

    uint8 ucTE;                             /* TE               */

    uint8 ucdummy230[3];                    /* Reserved         */

    uint8 ucTS;                             /* TS               */

    uint8 ucdummy231[3];                    /* Reserved         */

    uint8 ucTT;                             /* TT               */

    uint8 ucdummy232[7];                    /* Reserved         */

    uint8 ucCTL;                            /* CTL              */

    uint8 ucdummy233[3];                    /* Reserved         */

    uint8 ucEMU;                            /* EMU              */
} OSTMReg;

typedef struct STag_Pwm_DiagClockDivRegs
{
    uint16 usBRS0;                          /* BRS0             */

    uint8  ucdummy232[2];                   /* Reserved         */

    uint16 usBRS1;                          /* BRS1             */

    uint8  ucdummy233[2];                   /* Reserved         */

    uint16 usBRS2;                          /* BRS2             */

    uint8  ucdummy234[2];                   /* Reserved         */

    uint16 usBRS3;                          /* BRS3             */

    uint8  ucdummy235[2];                   /* Reserved         */

    uint8  ucTE;                            /* TE               */

    uint8  ucdummy236[3];                   /* Reserved         */

    uint8  ucTS;                            /* TS               */

    uint8  ucdummy237[3];                   /* Reserved         */

    uint8  ucTT;                            /* TT               */
}PWBAReg;

typedef struct STag_Pwm_DiagGeneratorRegs
{
    uint16 usCSDR;                          /* CSDR             */

    uint8  ucdummy238[2];                   /* Reserved         */

    uint16 usCRDR;                          /* CRDR             */

    uint8  ucdummy239[2];                   /* Reserved         */

    uint16 usCTDR;                          /* CTDR             */

    uint8  ucdummy240[2];                   /* Reserved         */

    uint8  ucRDT;                           /* RDT              */

    uint8  ucdummy241[3];                   /* Reserved         */

    uint8  ucRSF;                           /* RSF              */

    uint8  ucdummy242[3];                   /* Reserved         */

    uint16 usCNT;                           /* CNT              */

    uint8  ucdummy243[2];                   /* Reserved         */

    uint8  ucTCR;                           /* TCR              */

    uint8  ucdummy303[3];                   /* Reserved         */

    uint8  ucTCBR;                          /* TCBR             */

    uint8  ucdummy304[3];                   /* Reserved         */

    uint8  ucCTL;                           /* CTL              */

    uint8  ucdummy244[3];                   /* Reserved         */

    uint16 usCSBR;                          /* CSBR             */

    uint8  ucdummy245[2];                   /* Reserved         */

    uint16 usCRBR;                          /* CRBR             */

    uint8  ucdummy246[2];                   /* Reserved         */

    uint16 usCTBR;                          /* CTBR             */
}PWGAReg;

typedef struct STag_Pwm_PWSAReg
{
    uint8 ucCTL;                            /* CTL              */

    uint8 ucdummy268[3];                    /* Reserved         */

    uint8 ucSTR;                            /* STR              */

    uint8 ucdummy269[59];                   /* Reserved         */

    uint32 ulPVCR[48];                      /* PVCR             */

    uint8 ucdummy305[256];                  /* Reserved         */

    uint32 ulPWDDIR[96];                    /* PWSAnPWDDIRz     */
}PWSAReg;

typedef struct STag_Pwm_SLPWGAReg
{
    uint32 ulSLPWGA0;                       /* SLPWGA0         */

    uint32 ulSLPWGA1;                       /* SLPWGA1         */

    uint32 ulSLPWGA2;                       /* SLPWGA2         */

    uint32 ulPWGAPRD;                       /* PWGAPRD         */

    uint32 ulPWGAPRDSL0;                    /* PWGAPRDSL0      */

    uint32 ulPWGAPRDSL1;                    /* PWGAPRDSL1      */

    uint32 ulPWGAPRDSL2;                    /* PWGAPRDSL2      */
}SLPWGAReg;

typedef struct STag_RLin2_GblRegs
{
    uint8 ucGLWBR;                          /* WBR              */

    uint8 ucGLBRP0;                         /* BRP0             */

    uint8 ucGLBRP1;                         /* BRP1             */

    uint8 ucGLSTC;                          /* STC              */
} Lin2GblReg;

typedef struct STag_RLin2_ChannelRegs
{
    uint8 ucLiMD;                           /* MD               */

    uint8 ucLiBFC;                          /* BFC              */

    uint8 ucLiSC;                           /* SC               */

    uint8 ucLiWUP;                          /* WUP              */

    uint8 ucLiIE;                           /* IE               */

    uint8 ucLiEDE;                          /* EDE              */

    uint8 ucLiCUC;                          /* CUC              */

    uint8 ucdummy247[1];                    /* Reserved         */

    uint8 ucLiTRC;                          /* TRC              */

    uint8 ucLiMST;                          /* MST              */

    uint8 ucLiST;                           /* ST               */

    uint8 ucLiEST;                          /*EST               */

    uint8 ucLiDFC;                          /* DFC              */

    uint8 ucLiIDB;                          /* IDB              */

    uint8 ucLiCBR;                          /* CBR              */

    uint8 ucdummy248[1];                    /* Reserved         */

    uint8 ucLiDBR[8];                       /* DBR              */
} Lin2ChReg;

typedef struct STag_RLin3_UartRegs
{
    uint8 ucLWBR;                           /* WBR              */

    uint8 ucLBRP0;                          /* BRP0             */

    uint8 ucLBRP1;                          /* BRP1             */

    uint8 ucLSTC;                           /* STC              */

    uint8 ucdummy249[3];                    /* Reserved         */

    uint8 ucLMD;                            /* LMD              */

    uint8 ucLBFC;                           /* BFC              */

    uint8 ucLSC;                            /* SC               */

    uint8 ucLWUP;                           /* WUP              */

    uint8 ucLIE;                            /* IE               */

    uint8 ucLEDE;                           /* EDE              */

    uint8 ucLCUC;                           /* CUC              */

    uint8 ucdummy250[1];                    /* Reserved         */

    uint8 ucLTRC;                           /* TRC              */

    uint8 ucLMST;                           /* MST              */

    uint8 ucLST;                            /* ST               */

    uint8 ucLEST;                           /* EST              */

    uint8 ucLDFC;                           /* DFC              */

    uint8 ucLDB;                            /* DB               */

    uint8 ucLCBR;                           /* CBR              */

    uint8 ucdummy251[1];                    /* Reserved         */

    uint8 ucLDBR[8];                        /* DBR              */
} Lin3UartReg;


typedef struct Stag_WDTA_Registers
{
    uint8 ucWDTE;                           /* WDTE             */

    uint8 ucdummy252[3];                    /* Reserved         */

    uint8 ucEVAC;                           /* EVAC             */

    uint8 ucdummy253[3];                    /* Reserved         */

    uint8 ucREF;                            /* REF              */

    uint8 ucdummy254[3];                    /* Reserved         */

    uint8 ucMD;                             /* MD               */
}WDTAReg;

typedef struct STag_AdcConfigRegisters
{
    uint32 ulPWDVCR;                        /* PWDVCR           */

    uint8 ucdummy255[508];                  /* Reserved         */

    uint32 ulPWDDIR;                        /* PWDDIR           */

    uint8 ucdummy256[8];                    /* Reserved         */

    uint32 ulADHALTR;                       /* ADHALTR          */

    uint32 ulADCR;                          /* ADCR             */

    uint32 ulSGSTR;                         /* SGSTR            */

    uint32 ulMPXCURR;                       /* MPXCURR          */

    uint8 ucdummy257[4];                    /* Reserved         */

    uint32 ulTHSMPSTCR;                     /* THSMPSTCR        */

    uint32 ulTHCR;                          /* THCR             */

    uint32 ulTHAHLDSTCR;                    /* THAHLDSTCR       */

    uint32 ulTHBHLDSTCR;                    /* THBHLDSTCR       */

    uint32 ulTHACR;                         /* THACR            */

    uint32 ulTHBCR;                         /* THBCR            */

    uint32 ulTHER;                          /* THER             */

    uint32 ulTHGSR;                         /* THGSR            */

    uint32 ulSFTCR;                         /* SFTCR            */

    uint32 ulULLMTBR[3];                    /* Reserved         */

    uint32 ulECR;                           /* ECR              */

    uint32 ulULER;                          /* ULER             */

    uint32 ulOWER;                          /* OWER             */

    uint32 ulDGCTL0;                        /* DGCTL0           */

    uint32 ulDGCTL1;                        /* DGCTL1           */

    uint32 ulPDCTL1;                        /* PDCTL1           */

    uint32 ulPDCTL2;                        /* PDCTL2           */

    uint8 ucdummy258[32];                   /* Reserved         */

    uint32 ulSMPCR;                         /* SMPCR            */

    uint8 ucdummy259[384];                  /* Reserved         */

    uint32 ulPWDSGSTPCR;                    /* PWDSGSTPCR       */

    uint32 ulPWDSGCR;                       /* PWDSGCR          */

    uint8 ucdummy260[12];                   /* Reserved         */

    uint32 ulPWDSGSEFCR;                    /* PWDSGSEFCR       */

    uint8 ucdummy287[34];                   /* Reserved         */

    uint32 ulULEVCFR[2];                    /* ULEVCFR         */

    uint8 ucdummy288[26];                   /* Reserved         */

    uint32 ulULLMTBR2[5];                   /* Reserved         */

    uint8 ucdummy289[120];                  /* Reserved        */

    uint32 ulMPXSTBTSELR[5];                /* MPXSTBTSELR(0-4) */

    uint8 ucdummy290[12];                   /* Reserved         */

    uint32 ulMPXSTBTR[8];                   /* MPXSTBTR(0-7)    */

}AdcConfReg;

typedef struct STag_DmaAddrRegs
{
    uint32 ulDSA;                           /* DSA              */

    uint32 ulDDA;                           /* DDA              */

    uint32 ulDTC;                           /* DTC              */

    uint32 ulDTCT;                          /* DTCT             */

    uint32 ulDRSA;                          /* DRSA             */

    uint32 ulDRDA;                          /* DRDA             */

    uint32 ulDRTC;                          /* DRTC             */

    uint8 ucdummy261[4];                    /* Reserved         */

    uint32 ulDCEN;                          /* DCEN             */

    uint32 ulDCST;                          /* DCST             */

    uint32 ulDCSTS;                         /* DCSTS            */

    uint32 ulDCSTC;                         /* DCSTC            */

    uint32 ulDTFR;                          /* DTFR             */

    uint32 ulDTFRRQ;                        /* DTFRRQ           */

    uint32 ulDTFRRQC;                       /* DTFRRQC          */
}DmaReg;

typedef struct STag_DmaGlobalRegs
{

    uint32 ulDMACTL;                   /*DMA control register*/

    uint8 ucdummy287[28];              /* Reserved         */

    uint32 ulDMACER;                   /*DMAC error register*/

    uint8 ucdummy288[12];              /* Reserved         */

    uint32 ulDM0CMV;                   /*DMAC0 register access protection */
/*violation register*/
    uint32 ulDM1CMV;                   /* DMAC1 register access protection*/
/* violation register*/

    uint8 ucdummy289[4];               /* Reserved         */

    uint32 ulCMVC;                     /*Register access protection violation*/
/* clear register*/

    uint8 ucdummy290[192];            /* Reserved         */

    uint32 ulDM00CM;                  /*DMAC0 channel 0 channel master setting*/

    uint32 ulDM01CM;                  /*DMAC0 channel1 channel  master setting*/

    uint32 ulDM02CM;                  /*DMAC0 channel2 channel  master setting*/

    uint32 ulDM03CM;                  /*DMAC0 channel3 channel  master setting*/

    uint32 ulDM04CM;                  /*DMAC0 channel4 channel  master setting*/

    uint32 ulDM05CM;                  /*DMAC0 channel5 channel  master setting*/

    uint32 ulDM06CM;                  /*DMAC0 channel6 channel  master setting*/

    uint32 ulDM07CM;                  /*DMAC0 channel7 channel  master setting*/

    uint32 ulDM10CM;                  /*DMAC1 channel0 channel  master setting*/

    uint32 ulDM11CM;                  /*DMAC1 channel1 channel  master setting*/

    uint32 ulDM12CM;                  /*DMAC1 channel2 channel  master setting*/

    uint32 ulDM13CM;                  /*DMAC1 channel3 channel  master setting*/

    uint32 ulDM14CM;                  /*DMAC1 channel4 channel  master setting*/

    uint32 ulDM15CM;                  /*DMAC1 channel5 channel  master setting*/

    uint32 ulDM16CM;                  /*DMAC1 channel6 channel  master setting*/

    uint32 ulDM17CM;                  /*DMAC1 channel7 channel  master setting*/

}DmaGlobalReg;
typedef struct STag_Adc_VirtualChReg
{
    uint32 ulVCR[50];                       /* VCR              */

    uint8 ucdummy262[56];                   /* Reserved         */

    uint16 usDR[50];                        /* DR               */

    uint8 ucdummy263[154];                  /* Reserved         */

    uint32 ulDIR[50];                       /* DIR              */
}AdcVirChReg;

typedef struct STag_Adc_ScanGroupReg
{
    uint32 ulSGSTCR;                        /* SGSTCR           */

    uint32 ulSGSTPCR;                       /* SGSTPCR          */

    uint32 ulSGCR;                          /* SGCR;            */

    uint32 ulSGVCSP;                        /* SGVCSP           */

    uint32 ulSGVCEP;                        /* SGVCEP           */

    uint32 ulSGMCYCR;                       /* SGMCYCR          */

    uint32 ulSGSEFCR;                       /* SGSEFCR          */

    uint32 ulSGTSEL;                        /* SGTSEL           */

}AdcSGReg;

typedef struct STag_Spi_MainReg
{
    uint8  ucCTL0;                          /* CTL0             */

    uint8  ucdummy280[3];                   /* Reserved         */

    uint32  ulSTR0;                         /* STR0             */

    uint16 usSTCR0;                         /* STCR0            */

    uint8  ucdummy265[6];                   /* Reserved         */

    uint32  ulCTL1;                         /* CTL1             */

    uint16 usCTL2;                          /* CTL2             */
}SpiMainReg;

typedef struct STag_Spi_BRSReg
{
    uint16 usBRS;                           /* BRS              */

    uint8  ucdummy[2];                      /* Reserved         */
}SpiBRSReg;

typedef struct STag_Spi_CSIHReg
{
    uint32  ulMCTL1;                        /* MCTL1            */

    uint32  ulMCTL2;                        /* MCTL2            */

    uint32  ulTX0W;                         /* TX0W             */

    uint16 usTX0H;                          /* TX0H             */

    uint8  ucdummy281[2];                   /* Reserved         */

    uint32  ulRX0W;                         /* RX0W             */

    uint16 usRX0H;                          /* RX0H             */

    uint8  ucdummy282[2];                   /* Reserved         */

    uint32  ulMRWP0;                        /* MRWP0            */

    uint8  ucdummy266[36];                  /* Reserved         */

    uint16 usMCTL0;                         /* MCTL0            */

    uint8  ucdummy283[2];                   /* Reserved         */

    uint32  ulCFG[8];                       /* CFG              */

    uint8  ucdummy267[4];                   /* Reserved         */

    SpiBRSReg stBRS[4];                     /* BRS              */
}SpiCSIHReg;

typedef struct STag_Spi_ECCCSIHnTRC
{
    uint8         ucErdb;


    uint8         ucEcrd;

    uint8         ucHord;

    uint8         ucSynd;

}Spi_EccTrcReg;

typedef struct STag_Spi_CSIHECCReg
{
    uint16        usEccCTL;

    uint8         ucdummy[2];

    uint16        usEccTmc;

Spi_EccTrcReg stEccTrc;

    uint32        ulEccTed;

}SpiCSIHECCReg;

typedef struct STag_Spi_SELBREADTEST
{
    uint16        usSelfReadTest;

}SpiSelfReadTestReg;

typedef struct STag_Spi_CSIGReg
{
    uint8  ucBCTL0;                         /* BCTL0            */

    uint8  ucdummy284[3];                   /* Reserved         */

    uint32  ulTX0W;                         /* TX0W             */

    uint16 usTX0H;                          /* TX0H             */

    uint8  ucdummy285[2];                   /* Reserved         */

    uint16 usRX0;                           /* RX0              */

    uint8  ucdummy286[2];                   /* Reserved         */

    uint32  ulCFG0;                         /* CFG0             */
}SpiCSIGReg;

typedef struct STag_Fls_Reg
{
    uint32  DCNT;                           /* DCNT             */

    uint32  DPCMD;                          /* DPCMD            */

    uint32  DPS;                            /* DPS              */
}FlsReg;

typedef struct STag_FEINTReg
{                                                         /* Module           */
    const uint32 F;                         /* F                */
    uint32 FMSK;                            /* FMSK             */
    uint32 FC;                              /* FC               */
} FEINTReg;

typedef uint16 CANnTMIECReg;
typedef uint32  CANnRMNDReg;

typedef struct STag_Fcu_Registers
{
    uint8         ucReserved1[16];

    uint8         ucFASTAT;

    uint8         ucReserved2[31];

    uint32        ulFSADDR;

    uint32        ulFEADDR;

    uint8         ucReserved3[28];

    uint16        usFCURAME;

    uint8         ucReserved4[42];

    uint32        ulFSTATR;

    uint16        usFENTRYR;

    uint8         ucReserved5[78];

    uint8         ucFBCSTAT;

    uint8         ucReserved6[3];

    uint32        ulFPSADDR;

    uint8         ucReserved7[8];

    uint16        usFPCKAR;

}FlsFACIReg;


typedef struct STag_Fcu_ECCReg
{
    uint16        usDFECCCTL;

    uint8         ucReserved8[2];

    uint8         ucDFERSTR;

    uint8         ucReserved9[3];

    uint8         ucDFERSTC;

    uint8         ucReserved10[11];

    uint8         ucDFERRINT;

    uint8         ucReserved11[7];

    uint16        usDFTSTCTL;
}FlsECCReg;


typedef struct STag_Pwm_DiagPWGAINTFRegs
{
    uint32        ulPWGAINTF;
    uint32        ulPWGAINTMSK;
    uint32        ulPWGAINTFC;
}PWGAINTFReg;

#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
