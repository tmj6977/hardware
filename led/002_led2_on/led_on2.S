.text
.global _start
_start:
ldr r1, =0x56000050
ldr r0, =0x400
str r0, [r1]

ldr r1, =0x56000054
ldr r0, =0
str r0, [r1]



halt:
 b halt 

 