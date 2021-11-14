start:
addi x5, x5, 3
sw x5,0(x0)
addi x6, x6, 2
sw x6, 4(x0)
blt x6, x5, loop
add x5, x5, x6
loop:
beq x5, x0, start
addi x5, x5, -1
beq x0, x0, loop
