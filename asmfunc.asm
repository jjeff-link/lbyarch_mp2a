section .data
kmh_to_ms dq 0.2777777777777778

section .text
bits 64
default rel ; to handle address relocation

global getAcc

getAcc:
push RBP
mov RBP, RSP

push RBX
push RSI
push RDI

mov RBX, RCX	;rbx = n
mov RSI, RDX	;rsi = pointer to velocities
mov RDI, R8		;rdi = pointer to results

movsd xmm3, [kmh_to_ms]

xor rcx, rcx	;rcx = 0 (loop counter)

.loop:
	cmp RCX, RBX
	jge .done

    ; Calculate offset: i * 3 * 8
    mov rax, rcx
    imul rax, 24      ; 3 doubles = 24 bytes

	movsd xmm0, [rsi+rax]	;xmm0 = initial velocity (Vi) in KM/H
	movsd xmm1, [rsi + rax + 8]	;xmm1 = final velocity (Vf) in KM/H
	movsd xmm2, [rsi + rax + 16] ;xmm2 = Time (T) in seconds

	
	;(Vf - Vi)
	subsd xmm1, xmm0

	;convert (Vf- Vi) to from KM/H to m/s
	mulsd xmm1, xmm3

	;Calculate xmm1 = (Vf - Vi) / T
	divsd xmm1, xmm2 

	cvtsd2si eax, xmm1 ;eax = (int) acceleration

	mov[rdi + rcx * 4], eax ;results[i] = acceleration (4 bytes per int)

	;increment counter
	inc rcx
	jmp .loop

.done:
	pop rdi
	pop rsi
	pop rbx
	pop rbp
	ret
