GLOBAL callSyscall
section .text

callSyscall:
    push rbp
    mov rbp,rsp
    
    int 80h

    mov rsp,rbp
    pop rbp
    ret
    
    

