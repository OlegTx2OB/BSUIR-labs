.model small
.data

    mProgramStart db "Start Program!", 13, 10, "$"
    mFileNameWasReceived db "(File name was received)$"
    mEnterNumber db 13, 10, "Enter number (1-255): $"
    mError      db 'Error!',13,10,'$'
      
    filename    db 80 dup(0)
    arguments   db 120 dup(0)
    numberTen   dw 000Ah
    
    ;EXEC Parameter Block
    EPB         dw 0                     ;������� ���������
                dw offset commandline, 0  ;����� ��������� ������
                dw 005Ch, 0, 006Ch, 0    ;����� FCB ���������      
    commandline db 125
                db " /?"
    commandtext db 122 dup (?)          
    
    numberString db 20 dup ('$')
    size        dw ?
    dsize       dw $-filename
 
.stack 256
.code
         
;����� ������     
;=== print ===============================================
print macro message
    mov ah, 9h
    lea dx, message
    int 21h
endm

;=== sizeInput =================================================  
sizeInput proc
    lea di, size
    mov cx, 0001h
    call inputNumbers
    cmp ax, 255
    jg error
    cmp ax, 1
    jl error
    mov [di], ax ;load number
    add di, 2 
ret
sizeInput endp      
  
;���������� ����� ����� �� ��������� ������
;=== getFileNameInCommandLine =====================================
getFileNameInCommandLine proc
    push ax  ;��������� ��������
    push cx
    push di
    push si
    
    xor cx, cx
    mov cl, es:[80h]  ;���������� �������� � ��������� ������
    cmp cl, 0
    je endParse
    mov di, 82h       ;�������� ��������� ������ � ����� PSP
    lea si, filename
cicle1:
    mov al, es:[di]   ;������� � al ����������� �������� ��������� ������
    cmp al, ' '       ;���� ������ ����� ���������       
    je end_get_name
    cmp al, 0Dh
    je endParse
    mov [si], al      ;������� ������ �� ���.������ � filename 
    inc di            ;�� ��������� ������
    inc si            
    jmp cicle1 

end_get_name: 
    lea si, arguments
    mov [si], 0
    inc si
    inc di 
    xor cl, cl
cycle2: 
    mov al, es:[di]
    cmp al, 0Dh
    je endParse
    mov [si], al
    inc di
    inc si
    inc cl
    jmp cycle2:

endParse:
    dec si       
    lea si, arguments
    dec cl
    mov [si], cl
    
    pop si            ;��������������� ��������
    pop di
    pop cx
    pop ax   
ret
getFileNameInCommandLine endp

;���� �����
;=== inputNumber =========================================  
inputNumbers proc  
repeatElementInput:
    print mEnterNumber
    lea dx, numberString
    mov ah, 0Ah
    int 21h
              
    lea si, numberString[2]
    call parseString
    jc invalidInput
    mov [di], ax  ;load number
    add di, 2  
    loop inputNumbers
ret

invalidInput:
    jno tryAgainOutput
tryAgainOutput:
    jmp repeatElementInput
inputNumbers endp
           
;������� ������ � �����
;�������� dx, bx, ax ������������ � ��������, si - ����� ������
;ax �������� ���������, cf - ���� ��������
;=== parseString =====================================    
parseString proc 
    xor dx, dx
    xor bx, bx
    xor ax, ax  
    jmp inHaveSign  
parseStringLoop:
    mov bl, [si]  ;1 ����� = 1 ���� 
    jmp isNumber
validString:
    sub bl, '0'
    imul numberTen ;ax * 10
    jo invalidString           ;����� > 16 ���
    js invalidString           ;����� > 15 ���
    add ax, bx
    js invalidString           ;������ ������������� ����� �� ��������� ����� 
checkInvalid:
    inc si
    jmp parseStringLoop             
             
isNumber:
    cmp bl, 0Dh          ;enter
    je endParsing        ;���� ����� ������, ���������� �������
    cmp bl, '0'                               
    jl invalidString     ;���� ASCII < '0'
    cmp bl, '9'
    jg invalidString     ;���� ASCII > '9'      
    jmp validString      ;�����
  
inHaveSign:
    cmp [si], '-'
    je invalidString
    cmp [si], '+'
    jne isNullString
    inc si     
    jmp isNullString
    
negative: 
    mov ch, 1
    inc si
    jmp isNullString

isNullString:
    cmp [si], 0Dh
    je invalidString
    jmp parseStringLoop
        
invalidString:
    xor ch, ch         
    stc   ;CF = 1
ret

endParsing:
    cmp ax, 255 
    jg invalidString
    cmp ax, 1
    jl invalidString
    
    clc  ;CF = 0
    mov size, ax
ret
parseString endp

;=== openProgram ==============================================
openProgram proc
    mov ax, 03
    int 10h
    
    ;����������� ��� ������ ����� ����� ��������� � �����    
    mov sp, csize + 100h + 200h            
    mov ah, 4ah   ;��������� ������ �� ��������
    mov bx, (csize/16)+256/16+(dsize/16)+20
    int 21h           ;�������� ������ ����������� ����� ������      
    jc error
    
    mov ax, cs  
    ;���� ���������� ������� �������� �����
    mov word ptr EPB+4, ax   ;������� ��������� ������
    ;file control block
    mov word ptr EPB+8, ax   ;������� ������� FCB
    mov word ptr EPB+0Ch, ax ;������� ������� FCB
    
    mov cx, size
     
openProgramLoop:     
    mov ax, 4B00h       ;4B00h - ��������� � ���������
    lea dx, filename    ;��� �����
    lea bx, epb         ;���� EPB 
    int 21h
    jc  error
    loop openProgramLoop
    ret
openProgram endp

;=== main =============================================== 
main:
    mov ax, @data            
    mov ds, ax  
    
    print mProgramStart
    call getFileNameInCommandLine
    print mFileNameWasReceived
    call sizeInput
    call openProgram

endProgram:
    mov ax, 4c00h
    int 21h
    
error: 
    print mError
    jmp endProgram
        
csize dw $-start 
end main