section .text
    extern kernel_entry
    global enable_sse
    global _start


enable_sse:
    fninit
    mov  rax,  cr0
    and  ax,   0xFFFB
    or   ax,   0x2
    mov  cr0,  rax
    mov  rax,  cr4
    or   ax,   3 << 9
    mov  cr4,  rax
    ret


_start:
    call enable_sse
    call kernel_entry
    ret

