BITS 64
;TEST_FILE_META_BEGIN
;TEST_TYPE=TEST_F
;TEST_IGNOREFLAGS=FLAG_CF|FLAG_OF|FLAG_SF|FLAG_ZF|FLAG_AF|FLAG_PF
;TEST_FILE_META_END
    ; DIV64r
    ;TEST_BEGIN_RECORDING
    mov rdx, 0x0
    mov rax, 0x100
    mov rbx, 10
    div rbx
    ;TEST_END_RECORDING
