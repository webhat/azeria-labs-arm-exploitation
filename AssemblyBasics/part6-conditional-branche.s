.text
.global _start

_start:
   mov r0, #2
   mov r1, #2
   add r0, r0, r1
   cmp r0, #4
   beq func1
   add r1, #5
   b func2
func1:
   mov r1, r0
   bx  lr
func2:
   mov r0, r1
   bx  lr
