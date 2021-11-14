start:
addi x5, x0, 3
sw x5,0(x0)
addi x5, x5, 2
sb x5, 1(x0)
lb x6, 0(x0)
lb x7, 1(x0)
addi x5, x0, 2
loop:
beq x5, x0, start
addi x5, x5, -1
beq x0, x0, loop
