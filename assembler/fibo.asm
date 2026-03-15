; fibonacci number for 03-10
; written by Meyan
MVI A, 1
MVI B,            1
MVI C, a ; counter
; loop: 
MOV D,A
ADD A,B
MOV B,D
PRINT
DEC C
JNZ 0006
EXIT
