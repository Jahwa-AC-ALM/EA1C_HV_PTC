#include "types.h"
#include "TCB.h"




//------------------------------------------------------------------------------------------------------------------
/// \brief  trap_set
///
/// \descr  
///
/// \param  void
///
/// \return 
//------------------------------------------------------------------------------------------------------------------
#pragma inline_asm trap_set
void trap_set(void)
{
    trap 0x00
}





//------------------------------------------------------------------------------------------------------------------
/// \brief  OsGetPSW
///
/// \descr  Get the program status register value
///
/// \param  void
///
/// \return boolean: TRUE -> Cpu in interrupt context, FALSE -> Cpu not in interrupt context
//------------------------------------------------------------------------------------------------------------------
#pragma inline_asm OsGetPSW
void OsGetPSW(volatile unsigned int* CurrentPsw)
{
	stsr    5, r10		;
	st.w    r10, 0[r6]	;
	jmp	[lp]		;
}
//------------------------------------------------------------------------------------------------------------------
/// \brief  OsGetCurrentSP
///
/// \descr  Get the current stack pointer register value
///
/// \param  volatile unsigned int* CurrentSpPtr (out): Current stack pointer register value
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
#pragma inline_asm OsGetCurrentSP
void OsGetCurrentSP(volatile unsigned int* CurrentSpPtr)
{
	st.w    r3, 0[r6]	;
	jmp	[lp]		;
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsDispatcher
///
/// \descr  
///
/// \param  void
///
/// \return 
//------------------------------------------------------------------------------------------------------------------
#pragma inline_asm OsDispatcher
void OsDispatcher(void)
{
	;di  
	
	mov     -0x10, r20
	add     r20,sp                        	; prepare stack to save necessary values
	st.w    r20,0[sp]                       ; store R20
	st.w    lp,12[sp]                       ; store LP to stack
	stsr    0,r20				; 
	st.w    r20,8[sp]                       ; store EIPC to stack
	stsr    1,r20				; 
	st.w    r20,4[sp]                       ; store EIPSW to stack
	
	jarl    _portSAVE_CONTEXT,lp            ; Save the context of the current task.
	
	mov 	r3, r6				; Stack Pointer Send	

	jarl 	_OS_Dispatcher, lp 		; Call the dispatcher to switch the context.
	        				; This saves the return address into LP (r31).

	mov 	r10, sp				; Stack Pointer Recivce												
	jarl    _portRESTORE_CONTEXT,lp         ; Restore the context of whichever task the ...
					
	ld.w    4[sp],r20                       ; restore EIPSW from stack
	ldsr    r20,1				;

	ld.w    8[sp],r20                       ; restore EIPC from stack
	ldsr    r20,0				;
	
	ld.w    0[sp],r20                       ; restore LP from stack
	ld.w    12[sp],lp                       ; 
	
	mov     0x10, r20			; restore SP from stack
	add     r20,sp                         	; 
	

;	ei                 			; Enable interrupts (unlock the dispatcher).
	       					; This clears the ID bit in PSW to 0.

	EIRET       	   			; Return from the routine.

}

//------------------------------------------------------------------------------------------------------------------
/// \brief  portSAVE_CONTEXT
///
/// \descr  
///
/// \param  void
///
/// \return 
//------------------------------------------------------------------------------------------------------------------
#pragma inline_asm portSAVE_CONTEXT
void portSAVE_CONTEXT(void)
{    
	mov     -120, r20
	add     r20, sp
	
	mov 	sp, ep
	sst.w 	r30, 112[ep]
	sst.w 	r29, 108[ep]
	sst.w 	r28, 104[ep]
	sst.w 	r27, 100[ep]
	sst.w 	r26, 96[ep]
	sst.w 	r25, 92[ep]
	sst.w 	r24, 88[ep]
	sst.w 	r23, 84[ep]
	sst.w 	r22, 80[ep]
	sst.w 	r21, 76[ep]
	
	sst.w   r19,72[ep]
	sst.w   r18,68[ep]
	sst.w   r17,64[ep]                                       
	sst.w   r16,60[ep]
	sst.w   r15,56[ep]
	sst.w   r14,52[ep]
	sst.w   r13,48[ep]
	sst.w   r12,44[ep]
	sst.w   r11,40[ep]
	sst.w   r10,36[ep]
	sst.w   r9,32[ep]
	sst.w   r8,28[ep]
	sst.w   r7,24[ep]
	sst.w   r6,20[ep]
	sst.w   r5,16[ep]
	sst.w   r4,12[ep]
	sst.w   r2,8[ep]
	sst.w   r1,4[ep]
	movhi   HIGHW1(#_usCriticalNesting),r0,r1    		;-- save usCriticalNesting value to stack
	ld.w    LOWW(#_usCriticalNesting)[r1],r2
	sst.w   r2,0[ep]
	
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  portRESTORE_CONTEXT
///
/// \descr  
///
/// \param  void
///
/// \return 
//------------------------------------------------------------------------------------------------------------------
#pragma inline_asm portRESTORE_CONTEXT
void portRESTORE_CONTEXT(void)
{
	MOV     sp,ep                           			;-- set stack pointer to element pointer
	sld.w   0[ep],r1                        			;-- load usCriticalNesting value from stack
	movhi   HIGHW1(#_usCriticalNesting),r0,r2
	st.w    r1,LOWW(#_usCriticalNesting)[r2]
	
	sld.w   4[ep],r1                        			;-- restore general purpose registers
	sld.w   8[ep],r2
	sld.w   12[ep],r4
	sld.w   16[ep],r5
	sld.w   20[ep],r6
	sld.w   24[ep],r7
	sld.w   28[ep],r8
	sld.w   32[ep],r9
	sld.w   36[ep],r10
	sld.w   40[ep],r11
	sld.w   44[ep],r12
	sld.w   48[ep],r13
	sld.w   52[ep],r14
	sld.w   56[ep],r15
	sld.w   60[ep],r16
	sld.w   64[ep],r17
	sld.w   68[ep],r18
	sld.w   72[ep],r19
	
	sld.w   76[ep],r21
	sld.w   80[ep],r22
	sld.w   84[ep],r23
	sld.w   88[ep],r24
	sld.w   92[ep],r25
	sld.w   96[ep],r26
	sld.w   100[ep],r27
	sld.w   104[ep],r28
	sld.w   108[ep],r29
	sld.w   112[ep],r30
	
	mov     120, r20
	add     r20, sp
	
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  vISRWrapper
///
/// \descr  
///
/// \param  void
///
/// \return 
//------------------------------------------------------------------------------------------------------------------
#pragma inline_asm vISRWrapper
void vISRWrapper(void)
{
	mov     -0x10, r20
	add     r20,sp                        ; prepare stack to save necessary values
	st.w    r20,0[sp]                       ; store R20
	st.w    lp,12[sp]                        ; store LP to stack
	stsr    0,r20				; 
	st.w    r20,8[sp]                        ; store EIPC to stack
	stsr    1,r20				; 
	st.w    r20,4[sp]                        ; store EIPSW to stack
	

	
	jarl    _portSAVE_CONTEXT,lp            ; Save the context of the current task.
	
	mov	r3, r6
	
	jarl	_OsStoreStackPointer,lp
	jarl    _OsRunCat2Isr,lp           			// Call the timer tick function.
	jarl    _OsGetSavedStackPointer,lp
	
	mov	r10, r6
	jarl	_OsIsrCallDispatch, lp					;  ISR CALL DISPATCHER!!!	
	
	mov 	r10, sp					;Stack Pointer Recivce	
	jarl    _portRESTORE_CONTEXT,lp                // Restore the context of whichever task the ...
	
	ld.w    4[sp],r20                        // restore EIPSW from stack
	ldsr    r20,1

	ld.w    8[sp],r20                        //restore EIPC from stack
	ldsr    r20,0
	
	ld.w    0[sp],r20                        // restore LP from stack
	ld.w    12[sp],lp                        // restore LP from stack
	
	
	mov     0x10, r20
	add     r20,sp                         // set SP to right position
	
	EIRET
}