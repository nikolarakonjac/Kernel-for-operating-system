.global _ZN3TCB13contextSwitchEPNS_7ContextES1_
.type _ZN3TCB13contextSwitchEPNS_7ContextES1_, @function
_ZN3TCB13contextSwitchEPNS_7ContextES1_:
#fja ima dva parametra u a0 i a1 (contextSwitch(&old->context, *running->context))
    #u memoriju na adresu a0 upisuje vrednost registra procesora ra
    sd ra, 0 * 8(a0)
    #u memoriju na adresu 8*a0 upisuje vrednost registra procesora sp
    sd sp, 1 * 8(a0)

    # u registre procesora upisuje vrednosti iz promenljivih ra i sp iz klase TCB
    #vraca vrednosti tamo gde proces treba da nastavi svoje izvrsavanje gde je prekinut
    #ili ako se izvrsava prvi put krenuce da izvrsava fje nad kojom je pokrenut
    ld ra, 0 * 8(a1)
    ld sp, 1 * 8(a1)

ret