#data
a1 1
a2 2
b1 3
b2 4
c1 4
c2 4
d1 8
d2 4
#code
LOAD R1, a1
LOAD R2, a2
ADD R3, R1, R2
STORE a1, R3
LOAD R1, b1
LOAD R2, b2
SUB R3, R1, R2
STORE b1, R3
LOAD R1, c1
LOAD R2, c2
MUL R3, R1, R2
STORE c1, R3
LOAD R1, d1
LOAD R2, d2
DIV R3, R1, R2
STORE d1, R3
#output
CPU_printf(a1)
CPU_printf(b1)
CPU_printf(c1)
CPU_printf(d1)
