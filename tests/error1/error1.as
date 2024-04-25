
; Double definition of label
DUPLABEL: clr r1
DUPLABEL: inc r1

; Missing instruction/action after label
EMPTYLABEL: 
macro: clr r1 

; Entry on extern label
.extern EXTERNLABEL
.entry EXTERNLABEL

; Extern on entry label
.entry ENTRYLABEL
.extern ENTRYLABEL

; Missing operand
mov r1, 

; Unintended comma placements
B: .data 5,,6
C: .data ,7

FATHER: .string "abcdefgh femwiopfmewoi"

; Spaces between '#' and value
mov  r1, # -5

; Too many operands
D: add r1, r2, r3

