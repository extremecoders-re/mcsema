BITS 32
;TEST_FILE_META_BEGIN
;TEST_TYPE=TEST_F
;TEST_IGNOREFLAGS=FLAG_OF
;TEST_FILE_META_END
    ; RCR8rCL
    mov bh, 0x41
    mov cl, 0x4
    ;TEST_BEGIN_RECORDING
    rcr bh, cl
    ;TEST_END_RECORDING

