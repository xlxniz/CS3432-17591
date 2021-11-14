power:
bne x11, x0, recurse
addi x10, x0, 1
jalr x0, 0(x1)
recurse:
addi sp, sp, -8
sw x1, 4(sp)
sw x10, 0(sp)
addi x11, x11, -1
jal x1, power
lw x5, 0(sp)
mul x10, x5, x10
lw x1, 4(sp)
addi sp, sp, 8
jalr x0, 0(x1)
