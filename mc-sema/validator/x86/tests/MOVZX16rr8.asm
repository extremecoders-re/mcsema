BITS 32
;TEST_FILE_META_BEGIN
;TEST_TYPE=TEST_F
;TEST_IGNOREFLAGS=
;TEST_FILE_META_END
    ; MOVZX16rr8
    mov bx, 0x2
    mov bl, 0x3
    ;TEST_BEGIN_RECORDING
    movzx bx, bl
    ;TEST_END_RECORDING
