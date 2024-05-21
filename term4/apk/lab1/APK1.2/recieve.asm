COM1 equ 03F8h
COM2 equ 02F8h
PORT_NUM equ 0               ;0 means COM1, 1 means COM2 etc.
portErrorBitMask equ 10001110b
;������ ��� (��� 0): �� ������������ � ��������� ����� ������ COM-�����, ������ �� ��������������.
;������ ��� (��� 1): ��� ����� 0, ��� ������ �������� ���������� ������.
;������ ��� (��� 2): ��� ����� 0, ��� ����� ������ �������� ���������� ������.
;��������� ��� (��� 3): ��� ����� 1, ��� ����� ��������, ��������, ������ ������������ ������ ���������.
;����� ��� (��� 4): ��� ����� 1, ��� ����� ��������� �� ������ ������� � �������� ������ ������.
;������ ��� (��� 5): ��� ����� 1, ��� ����� ��������� �� ������ � ����� ������, ����� ��� ������������ ��� �������� ��� ����-���.
;������� ��� (��� 6): ��� ����� 0, ��� ������ �������� ���������� ������.
;������� ��� (��� 7): ��� ����� 0, ��� ����� ������ �������� ���������� ������.
;�������� ������� ��������� ����� ������ � com-�����
data segment
    messageSuccess db "Success!", 0ah, 0dh, "$"
    receiveStarted db "Start", 0ah, 0dh, "$"
    errorMessage db "Error occured!", 0ah, 0dh, "$"
    \n db 0ah, 0dh, "$"
ends

stack segment
    dw   128  dup(0)
ends

;=== portErrorCheck ===============================================================================
;�������� �� ������ � om-�����. ���������� ��������� and � ������������ ������ ��� �������
portErrorCheck macro portNum
    push dx
    push ax
    
    mov ah, 03h
    mov dx, portNum
    int 14h
    
    and ah, portErrorBitMask
    cmp ah, 0
    jne errorDetected
    
    push ax
    pop dx
endm            

;=== getBit =========================================================================================
;��������� ���� �� ����� al
getBit macro bitNum
    push bx             
    mov bl, 01h
    shl bl, bitNum
    and al, bl
    shr al, bitNum
    pop bx
endm   

;=== print ======================================================================================================
print macro message
    push ax
    push dx
    
    lea dx, message
    mov ax, 9h
    int 21h
    
    pop dx
    pop ax
endm

code segment

; ==== printByte ==================================================================================================
;����� ����� � �������� ����    
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
;====== main ==================================================================================================================
main:
    mov ax, data
    mov ds, ax
    
    xor ax, ax
    
    mov dx, PORT_NUM
    mov al, 00000011b
    mov ah, 00h
    int 14h
    print receiveStarted
    portErrorCheck PORT_NUM
;===============================
;���� ��������� ����������. ��� ������� ���� �������������
    reciveLoop:   
        portErrorCheck PORT_NUM    
        
        mov ah, 02h
        int 14h
           
        call printByte
           
        mov bx, ax
        mov al, ah
        getBit 7
        cmp al, 1
        je reciveLoop
        
        mov ax, bx
        cmp al, "$"
        je  endRecive
        
        mov ah, 02h
        mov dl, al
        int 21h
        
        print \n
        
        jmp reciveLoop
        mov ah, 03h
        mov dx, PORT_NUM
        int 14h        
        
        call printByte
        
        jmp  reciveLoop
    endRecive:
    
    print \n
    print messageSuccess
    jmp exit
    
    errorDetected:
    
    call printByte
    print errorMessage
    
    exit:
    mov ax, 4c00h
    int 21h    
ends

end main
