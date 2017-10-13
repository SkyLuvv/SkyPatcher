

;refers to a memory addressing paradigm in which "memory appears to the program as a single contiguous address space.
;https://en.wikipedia.org/wiki/Flat_memory_model


.model flat, c
.code

.data
 extern obj_LCharaAddr:dword
 extern obj_RevBoxAddr:dword

  GrabThirdArg proc
     
	 	push edx
		mov edx, [obj_RevBoxAddr]
		mov eax, dword ptr[ebp - 34h]
		mov [edx  + 08h] , eax
		pop edx
		call edx
		sub eax, 00h
		mov edx, [obj_RevBoxAddr]
		jmp dword ptr[edx + 0Ch]

 GrabThirdArg endp
        

LCharaGrabBase proc

		mov edx, obj_LCharaAddr
		mov [edx], ecx
		mov ax, [ecx + 000001C4h]
		jmp dword ptr[edx + 04h]

LCharaGrabBase  endp
        end

