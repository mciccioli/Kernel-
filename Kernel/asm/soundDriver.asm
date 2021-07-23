GLOBAL beepasm
GLOBAL unbeepasm
GLOBAL init_sound
GLOBAL set_frequencyASM

init_sound:

    push rbp
    mov rbp, rsp

    mov rax,0;    seteo el registro de rax todo en 0.
    mov al, 182; preparo al speaker para realizar el beep.
    out 0x43, al
    mov ax, 4560; cargo la frecuencia.
    out 0x42, al; envio la parte baja del byte
    mov al, ah
    out 0x42, al; envio la parte alta

    mov rsp, rbp
    pop rbp
    ret

beepasm:
    push rbp
    mov rbp, rsp

    in al, 0x61
    or al, 0x03; prendo los bits para emitir el beep.
    out 61h, al

    mov rsp, rbp
    pop rbp
    ret

unbeepasm:
    push rbp
    mov rbp, rsp

    in al, 0x61
    and al, 0xFC; apago los bits para apagar el beep.
    out 0x61, al
    
    mov rsp, rbp
    pop rbp
    ret

set_frequencyASM:

    push rbp
    mov rbp, rsp

    mov ax, dx; cargo la frecuencia.
    out 0x42, al; envio la parte baja del byte
    mov al, ah
    out 0x42, al; envio la parte alta

    mov rsp, rbp
    pop rbp
    ret