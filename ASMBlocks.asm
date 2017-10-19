

;refers to a memory addressing paradigm in which "memory appears to the program as a single contiguous address space.
;https://en.wikipedia.org/wiki/Flat_memory_model



.model flat, c

.data
 extern LCharaAddr:dword
 extern RevBoxAddr:dword
 extern obj_DeadLockAddr:dword

 ;variables
 DeadLockTemp dword 0

.code














;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LChara_GrabBase proc

        push ebx
        mov ebx , [LCharaAddr]
		mov [ebx], ecx
		pop ebx
		mov ax, [ecx + 000001C4h]
		mov ecx , [LCharaAddr]

;ecx is overwritten right after the jump so we can do this
		jmp dword ptr[ecx + 04h]

LChara_GrabBase  endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;















;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ReviveBox_Pos proc

;pos X
        sar ebx, 2
;posY
		mov eax, [RevBoxAddr]
        sub edi, [eax + 14h]
		jmp dword ptr[eax + 0Ch]

ReviveBox_Pos endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;









;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ReviveBox_DimAndTransl proc

;transluscency
   
		 mov eax, [RevBoxAddr]
         push [eax + 08h]
;height
         push [eax]
;width
         push [eax + 04h]

;ecx is overwritten right after the jump so we can do this
		 jmp dword ptr[eax + 10h]

ReviveBox_DimAndTransl endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;












;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Mod_DeadLock proc

     lea ecx,[ebp+08h]
     push edx
     mov edx, [LCharaAddr]

;if the currently passed object is our local player object, then execute the normal instructions
;[esi + 90] at this point is our player object

     push eax
	 mov eax, [esi+90h]
     cmp eax, [edx]
	 pop eax
     pop edx
     jz  original

;otherwise just compare with 0 which will never be equal and return, so when it compares it with the death value it wont be true
;making the game think players are still alive
     cmp eax, 0
	 push ebx
     mov ebx, [obj_DeadLockAddr]
	 mov ebx, [ebx]
	 mov [DeadLockTemp], ebx
	 pop ebx
     jmp dword ptr[DeadLockTemp]

original:
 
;we can't use the functions address directly so put it in a register instead
     mov [DeadLockTemp], 02B2E290h
     call [DeadLockTemp]
     cmp eax, 53FCh
	 push ebx
     mov ebx, [obj_DeadLockAddr]
	 mov ebx, [ebx]
	 mov [DeadLockTemp], ebx
	 pop ebx
     jmp dword ptr[DeadLockTemp]

Mod_DeadLock endp
          end
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;