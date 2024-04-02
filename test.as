.define sz = 2
MAIN:   mov r3, LIST[sz] 
LOOP:   jmp L1
        prn #-5
        mov STR[5], STR[2] 
        sub r1, r4
