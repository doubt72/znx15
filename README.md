# ZNX5 Instruction Set

## Basic Parameters

* Load/store architecture
* 32-bit CPU
* 32-bit address space (in 32-bit words; 16GB byte equivalent)
* 3-level pipeline: fetch, decode, execute
* 32-bit instructions only, all instructions take single clock to
  decode/execute (fetch varies)
* Dual mode operation (user, supervisor/interrupt)
* 32 32-bit integer registers: %i0-%if (indirect) and %d0-%df (data)
* 16 64-bit floating point registers: %f0-%ff
* 4 256-bit SIMD registers: %m0-%m3
* 256-deep interrupt buffer
* No data need be stored on interrupt; supervisor has own %i0-%if,
  %d0-%de (data) registers (%df/%pc shared, %if/%lr contains last %pc on
  interrupt)
* %de = %sp = user stack pointer (USP) or supervisor stack pointer (SSP),
  depending on mode
* %df = %pc (program counter)
* %if = %lr (link register), no data stored/retrieved on jsr/rts, %pc
  and %lr swapped
* Status register %st: Z, N, V, C, S [zero, negative, overflow/divide
  by zero, carry, supervisor mode]; separate status registers for each
  mode (user/supervisor)
* %d0-%d8 stored to SSP on call, popped off SSP on ret, %st cleared
* MMU on-die 64kW tagged (ASN) TLB using 64k-word pages (pre-cache
  translation)

## Modules

# Processor

All cache is L1/L2/L3 2-way associative write through cache in
256-word blocks. L1 per core, L2/L3 shared among all cores. L1 = 1
cycle latency, L2 = 4 cycles, L3 = 16 cycles.

* ZN15C4 = 1 Core, 16kW/256kW/4MW cache
* ZN15C8 = 1 Core, 32kW/512kW/8MW cache
* ZN25C8 = 2 Core, 16kW/512kW/8MW cache
* ZN45C8 = 4 Core, 8kW/512kW/8MW cache
* ZN45C16 = 4 Core, 16kW/1MW/16MW cache
* ZN85C16 = 8 Core, 8kW/1MW/16MW cache

# Memory

* MM64M = 64MW/256kB Memory Module
* MM128M = 128MW/512kB Memory Module
* MM256M = 256MW/1GB Memory Module

Max 4MM/bus.  200 cycle latency.

# Attached Storage

* SSSM10G = 2.5GW/10GB Solid State Storage Module
* SSSM20G = 5GW/20GB Solid State Storage Module
* SSSM50G = 12.5GW/50GB Solid State Storage Module

1000 cycle latency.

# Other

* Keyboard
* Monitor

## 3 Operand Integer Instructions [15/16]

```
  op   x     y                 z
1 2345 6789A BCDEF0123456789AB CDEF0
1 xxxx xxxxx xyyyyyyyyyyyzzzzz xxxxx

op = { 0=and, 1=or, 2=xor, 3=add, 4=addc, 5=sub, 6=subc, 7=mullo,
       8=mulhi, 9=mulslo, A=mulshi, B=div, C=divs, D=mod, E=mods }
x, z = %r
y = zzzzz = %r                          if x = 0 ( yyyyyyyyyyy = ignored )
    yyyyyyyyyyyzzzzz = -2^15,2^15-1     if x = 1
```

X and Z are registers, Y is either a register or a literal number
ranging from -2^15 to 2^15-1.  Result is stored in Z.

```
operation      flags  	description

and X, Y, Z    Z,N      ;bitwise and (1100 x 1010 = 1000)
or X, Y, Z     Z,N      ;bitwise or (1100 x 1010 = 1110)
xor X, Y, Z    Z,N      ;exclusive or (1100 x 1010 = 0110)
add X, Y, Z    Z,N,V,C  ;addition (overflow > 2^9, carry > 2^10)
sub X, Y, Z    Z,N,V,C  ;subtraction (X - Y => Z)
addc X, Y, Z   Z,N,V,C  ;addition with carry (X + Y + C -> Z)
subc X, Y, Z   Z,N,V,C  ;subtraction with carry (X - Y - (1-C) -> Z)
mullo X, Y, Z  Z,N      ;multiplication, stores low
mulhi X, Y, Z  Z,N      ;multiplication, stores high
mulslo X, Y, Z Z,N      ;signed multiplication, stores low
mulshi X, Y, Z Z,N      ;signed multiplication, stores high
div X, Y, Z    Z,N,V    ;division (X / Y => Z, V,Z=0 if divide by zero)
divs X, Y, Z   Z,N,V    ;signed division (V,Z=0 if divide by zero)
mod X, Y, Z    Z,N,V    ;modulo (X % Y => Z, V,Z=0 if divide by zero)
mods X, Y, Z   Z,N,V    ;signed modulo (V,Z=0 if divide by zero)
```

## 2 Operand Integer Instructions [11/16]

```
   op   x     y      fill
12 3456 789AB CDEF01 23456789ABCDEF0
01 xxxx xxxxx xyyyyy xxxxxxxxxxxxxxx

op = { 0=ld, 1=st, 2=cp, 3=cmp, 4=bit, 5=asl, 6=asr, 7=shl,
       8=shr, 9=rol, A=ror }
fill = ignored
x = %r
y = yyyyy = %r          if x = 0
    yyyyy = 0,31        if x = 1
```

X is a register, Y is either a register or a literal number ranging
from 0,31 (for shifts or rotations).  V is set if any positive bits
overflow, C is the final bit.  X is modified in place for shifts or
rotations.

```
operation      flags  	description

ld X, Y        Z,N      ;load register X with value at address in register Y
st X, Y                 ;store register X value at address in register Y
cp X, Y                 ;copy register X value to register Y
cmp X, Y       Z,N      ;compare (Z if equal, N if Y > X)
bit X, Y       Z,N      ;bitwise test (same flags as and)
asl X, Y       Z,N,V,C  ;arithmetic shift left (0 fill, Y bits)
asr X, Y       Z,N,V,C  ;arithmetic shift right (MSB fill, Y bits)
shl X, Y       Z,N,V,C  ;logical shift left (0 fill, Y bits)
shr X, Y       Z,N,V,C  ;logical shift right (0 fill, Y bits)
rol X, Y       Z,N,V,C  ;rotate left (Y bits)
ror X, Y       Z,N,V,C  ;rotate right (Y bits)
```

## 1 Operand (Integer) Instructions [20/32]

```
    op    x
123 45678 9ABCDEF0123456789ABCDEF0
001 xxxxx xyyyyyyyyyyyyyyyzzzzzzzz

op = { 00=push, 01=pop, 02=nor, 03=clr, 04=set, 05=inc, 06=dec, 07=beq,
       08=bne, 09=blt, 0A=bgt, 0B=bmi, 0C=bpl, 0D=bvc, 0E=bvs, 0F=bcc,
       10=bcs, 11=bge, 12=jmp, 13=call }
x = zzzzz = %r                                  if x = 0 ( yyy... = ignored)
    yyyyyyyyyyyyyyyyyyzzzzz = -2^22,2^22-1      if x = 1
```

X is a register, or for jumps/branches can be a literal ranging from
-2^22,2^22-1, in which case the jump/branch is relative.  For calls,
%d0-%d7 and %st are stored on the supervisor stack (SSP) and zeroed
out.

```
operation      flags  	description

push X                  ;store register on data stack
pop X          Z,N      ;pop register off data stack
nor X          Z,N      ;inverts bit value
clr X                   ;clears register (all 0's)
set X                   ;sets register (all 1's)
inc X          Z,N,V    ;increment value
dec X          Z,N,V    ;decrement value
beq X                   ;branch when zero set to register address
bne X                   ;branch when zero clear to register address
bmi X                   ;branch when negative set to register address
bpl X                   ;branch when negative clear to register address
bvc X                   ;branch when overflow clear to register address
bvs X                   ;branch when overflow set to register address
bcc X                   ;branch when carry clear to register address
bcs X                   ;branch when carry set to register address
bgt X                   ;branch when zero clear to negative set (greater than)
blt X                   ;branch when zero clear and negative clear (less than)
bge X                   ;branch when zero set or negative set (greater or equal)
jmp X                   ;jump to register address
call X                  ;call function at register address

ble X                   ;alias for bpl, not a distinct instruction (<=)
```

## 3 Operand Floating Point Instructions
## 2 Operand Floating Point Instructions
## 1 Operand Floating Point Instructions
## 3 Operand SIMD Instructions
## 2 Operand SIMD Instructions
## 1 Operand SIMD Instructions

## 0 Operand Instructions [20/32]

```
     op    n        fill
1234 56789 ABCDEF01 23456789ABCDEF0
0000 xxxxx xxxxxxxx xxxxxxxxxxxxxxx

op = { 00=nop, 01=pushs, 02=pops, 03=clrz, 04=clrn, 05=clrc, 06=clrv,
       07=setz, 08=setn, 09=setc, 0A=setv, 0B=rts, 0C=ret, 0D=rti,
       0E=jsr, 0F=stop, 10=int, 11=pushu, 12=popu, 13=user }
n = x = 0,255
fill = ignored
```

Interrupts will store %pc in %lr, so the rti instruction will copy %lr
back to %pc.  The ret instruction will pop %d0-%d7 and %st.  The S bit
is set during interrupts and reset during rti instructions and cannot
be set or cleared.

```
operation      flags  	description

nop                     ;no operation
pushs                   ;store status on stack
pops           [all]    ;pop status off stack
clrz           Z        ;clear zero bit
clrn           N        ;clear negative bit
clrc           C        ;clear carry bit
clrv           V        ;clear overflow bit
setz           Z        ;set zero bit
setn           N        ;set negative bit
setc           C        ;set carry bit
setv           V        ;set overflow bit
rts                     ;return from subroutine, loads %lr in %pc
ret                     ;return from call, pop program stack
rti                     ;return from interrupt, pop program stack
jsr                     ;jump to subroutine, swaps %pc and %lr
stop                    ;wait until next interrupt
int N          S        ;trigger interrupt N, copies %i0-%i7 to supervisor

supervisor only:

pushu                   ;push user registers/status to supervisor stack
popu                    ;pop user registers/status to supervisor stack
user           S        ;jump to %lr, switch to user mode
```
