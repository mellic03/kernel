section .data

section .text
    global enable_sse
    ; global enable_avx
    global _start
    extern main


enable_sse:

    mov  rax,  cr0
    and  ax,   0xFFFB
    or   ax,   0x2
    mov  cr0,  rax
    mov  rax,  cr4
    or   ax,   3 << 9
    mov  cr4,  rax

    ret


; enable_avx:
;     ;--------------------------------;
;     push    rax
;     push    rcx
;     push    rdx
;     ;--------------------------------;
 
;     xor     rcx,  rcx
;     xgetbv                  ; Load XCR0 register
;     or      eax, 7          ; Set AVX, SSE, X87 bits
;     xsetbv                  ; Save back to XCR0
 
;     ;--------------------------------;
;     pop     rdx
;     pop     rcx
;     pop     rax
;     ret
;     ;--------------------------------;


_start:
    call enable_sse
    call main
    ret

