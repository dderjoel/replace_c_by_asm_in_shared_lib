SECTION .text
    GLOBAL foo

foo:
    mov rax, 0xB
    shl rax, 0x08
    or rax, 0xAD
    shl rax, 0x08
    or rax, 0xC0
    shl rax, 0x08
    or rax, 0xFF
    shl rax, 0x08
    or rax, 0xEE
    ret

