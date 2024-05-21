.model small
.stack 100h
.data 
    message db 'A'   
    received db 0    
    \n db 0Ah, 0Dh, '$'
    messageSuccess db "Success!", 0ah, 0dh, "$"
    recivedStr db "Recived: $"
    buf db 100 dup ?
.code

COM1 equ 03F8h
COM2 equ 02F8h
PORT_NUM equ COM1

;=== getBit =========================================================================================
;получение бита из байта al
getBit macro bitNum
    push bx             
    mov bl, 01h
    shl bl, bitNum
    and al, bl
    shr al, bitNum
    pop bx
endm   

;=== print ===================================================================================
print macro message
    push ax
    push dx
    
    lea dx, message
    mov ax, 9h
    int 21h
    
    pop dx
    pop ax
endm

;=========== comSetup =======================================================================================
;Этот макрос служит для установки параметров последовательного порта,
; таких как скорость передачи данных, режим работы и другие характеристики
comSetup macro toSetup
    push ax
    push dx
    
    mov dx, toSetup + 03h; LCR ine control register
    mov al, 11011011b; DLAB = 1 установление делителя скорости передачи данных
    out dx, al
    
    mov dx, toSetup + 00h; DLL (DLAB = 1) установка младшего байта делителя скорости
    mov al, 00h
    out dx, al
    
    mov dx, toSetup + 01h; DIM (DLAB = 1) позволяет программе устанавливать делитель скорости
    mov al, 01h
    out dx, al
    
    mov dx, toSetup + 03h; LCR программе разрешается доступ к данным, а не к делителю скорости
    mov al, 01011011b; DLAB = 0
    out dx, al
    
    mov dx, toSetup + 01h; IER (DLAB = 0)
    mov al, 00000000b; отключение всех прерываний ком-порта
    out dx, al
    
    mov dx, toSetup + 02h; FCR
    mov al, 00000111b; сброс буферов fifo
    out dx, al
    
    mov dx, toSetup + 04h; MCR
    mov al, 00010000b; LOOP = 0
    out dx, al
    
    pop dx
    pop ax
endm
; ==== printByte ==================================================================================================
;вывод байта в двоичном виде
printByte proc 
    push ax
    push bx
    push cx
    push dx
    
    mov bh, ah
    mov cx, 8
    mov ah, 02h
    printByteLoop:
        shl bh, 1
        
        jnc printByteZero
        mov dl, "1"
        jmp printBytePrint
        printByteZero:
        mov dl, "0"
        printBytePrint:
        
        int 21h
    loop printByteLoop:
    
    print \n
    
    pop dx
    pop cx
    pop bx
    pop ax
    RET
printByte endp
;=== main ==============================================================================================================
main:
    
    mov ax, data
    mov ds, ax
    
    comSetup PORT_NUM
;===================================================    
;Этот код выполняет передачу данных через COM-порт    
    transmitCycle:
        mov dx, PORT_NUM + 05h ; LSR
        in al, dx
        
        mov ah, al
        
        getBit 5 
        cmp al, 1
        je transmitByte
        jmp transmitCycle
        transmitByte: 
        
        call printByte
        
        mov ah, 01h
        int 21h
        print \n
        
        cmp al, "$"
        je endTransmit
        
        mov dx, PORT_NUM + 00h ; RBR (DLAB = 0);перемещает порт ввода-вывода com-порта
        out dx, al
        jmp transmitCycle
    endTransmit:
    
    reciveCycle:
        mov ah, 01h
        int 21h
        print \n
        
        cmp al, '$'
        je reciveEnd
        
        mov dx, PORT_NUM + 05h ; LSR
        in  al, dx
        
        mov ah, al
        call printByte
        
        getBit 0
        
        cmp al, 1
        je reciveByte
        jmp reciveCycle
        reciveByte:
        
        mov dx, PORT_NUM + 00h ; THR (DLAB = 0)
        in  al, dx
        
        cmp al, '$'
        je reciveEnd
        
        print recivedStr
        
        mov dl, al
        mov ah, 02h
        int 21h
        print \n  
    jmp reciveCycle
    reciveEnd:
    
    print \n
    print messageSuccess    
  
    mov ah, 4Ch  
    mov al, 0   
    int 21h      


end main