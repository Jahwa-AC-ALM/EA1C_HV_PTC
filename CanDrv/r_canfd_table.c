/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_canfd_table.c                                                 */
/* Version:  V1.00                                                           */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2016 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/* In case of any question please do not hesitate to contact:                */
/*                                                                           */
/*        ABG Software Tool Support                                          */
/*                                                                           */
/*        Renesas Electronics Europe GmbH                                    */
/*        Arcadiastrasse 10                                                  */
/*        D-40472 Duesseldorf, Germany                                       */
/*                                                                           */
/*        e-mail: software_support-eu@lm.renesas.com                         */
/*        FAX:   +49 - (0)211 / 65 03 - 11 31                                */
/*                                                                           */
/*===========================================================================*/
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/
/* History:                                                                  */
/*              V1.00: Initial version                                       */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/* CAN Rx rule table                                                         */
/*                                                                           */
/*===========================================================================*/


/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_canfd_table.h"

/*===========================================================================*/
/* Rx Rule Table */
/*===========================================================================*/

/*
Receive Rule ID Register: For the standard ID, set the ID in bits b10 to b0, ext ID: b28 to b0

Receive Rule Mask Register: set to 1--The corresponding bit is compared

Receive Rule Pointer 0 Register: 31to28 Receive Rule DLC check, receive buffer assignment

Receive Rule Pointer 1 Register: FIFO buffer assignment
*/
 canfd_cre_type CANFD_RX_RULE_TABLE_LIST[8] = 
 {
    {{0x00000111UL, 0xDFFFFFFFUL, 0x00000000UL, 0x00000001UL}},
    {{0x00000115UL, 0xDFFFFFFFUL, 0x00000000UL, 0x00000003UL}},
    {{0x80000800UL, 0xDFFFFFFFUL, 0x00000000UL, 0x00000005UL}},
    {{0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL}},
    {{0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL}},
    {{0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL}},
    {{0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL}},
    {{0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL}},

};

    /* NO.007 : std data frm ID = H'10~1F will be accepted, 64 data length destination RX FIFO buffer0 */
    /* NO.001 : std data frm ID = H'20~2F will be accepted, destination Rx Buffer 9 */
    /* NO.002 : std data frm ID = H'30~3F will be accepted, destination Rx Buffer 10 */
    /* NO.003 : std data frm ID = H'40~4F will be accepted, destination Rx Buffer 11 */
    /* NO.004 : std data frm ID = H'50 will be accepted, destination Rx Buffer 12 */
    /* NO.005 : std data frm ID = H'60 will be accepted, destination Rx Buffer 13 */
    /* NO.006 : std data frm ID = H'70 will be accepted, destination Rx Buffer 14 */
    /* NO.007 : std data frm ID = H'80 will be accepted, destination Rx Buffer 15 */