
#PREKIDNA RUTINA
.extern _ZN5Riscv23interruptRoutineHandlerEv #uvozimo pomocnu fju u kojoj cemo da obradimo izuzetak

.align 4
.global _ZN5Riscv16interruptRoutineEv
.type _ZN5Riscv16interruptRoutineEv, @function
_ZN5Riscv16interruptRoutineEv:

    # stavlja sve vrednosti programskih registra na stek
    addi sp, sp, -256
    .irp index, 0,1,2,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd x\index, \index * 8(sp)
    .endr

     #obrada prekida -> necemo da pisemo u asemblerskom kodu
     # static void Riscv::handleSupervisorTrap
     call _ZN5Riscv23interruptRoutineHandlerEv

    # skini sve rigstre sa steka i upisi u registre te vrednosti
    .irp index, 0,1,2,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld x\index, \index * 8(sp)
    .endr
    addi sp, sp, 256

    sret
