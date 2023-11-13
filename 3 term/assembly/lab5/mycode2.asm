data segment

    handleInput          dw 0
    handleOutput          dw 0 
    stringBuffer db 52 dup('$') 
    
    compulsoryChars db 50 dup("$") 
    
    
    inputCharsToFindMessage db "Input chars that would be in file string: $"
    pkey db "New info in file...$"
    cmdSize db ?
    cmdPath db 50 dup('$')
    fileName db 50 dup('$')
    inputFilePath db 'INPUT.txt', 0
    outputFilePath db 'OUTPUT.txt', 0
    
    openFileError   db "Error of open!$"  
    errorMessage     db "Error!$"  
    errorMessageWithString     db "String doesn't have all symbols!$"
    finalMessage db "Check OUTPUT.txt file$"
    endl db "", 0Dh, 0Ah, "$"
    
    
 
          
    
ends

stack segment
    dw   128  dup(0)
ends

code segment
strLength proc
    xor cx,cx
    q:
        cmp ptr byte[si], '$'
        je exits
        inc cx
        inc si
        jmp q
    exits:
        ret
        
        
strLength endp
deleteFile proc
   
    mov ah, 41h        
    mov al, 00h          
    lea dx,  outputFilePath   
    int 21h             
    jc openError  

deleteFile endp  
printToFileConst macro handle, string 
    push bx
    xor ch,ch
    
    mov  ah, 40h  ;Record File
    mov  bx, handle
    lea  dx, string
    int   21h 
    
 
    pop bx
endm
printToFile macro handle, string 
    push bx
    xor ax,ax
    lea si, string + 2
    call strLength
    
    mov ah, 40h  ;Record File
    mov bx, handle
   
    lea dx, string + 2
    int 21h 
    
 
    pop bx
endm
print macro string
    push ax
    push dx
    
    mov ah, 09h
    lea dx, string
    int 21h
    
    pop dx
    pop ax
endm
input macro string
    push ax
    push dx
    
    mov ah, 0Ah
    lea dx, string
    int 21h 
    
    xor cx,cx
    lea di, string + 1
    mov cl, ptr byte[di]
    inc di
    add di, cx
    inc di
    mov ptr byte[di], 0Ah
    
    pop dx
    pop ax    
endm

createForWrite proc
   mov ah, 3Ch             
   lea dx, outputFilePath   
   int 21h                   
      
ret
createForWrite endp 

fopenForWrite proc
   mov ah, 3dh         
   mov al, 1      
   lea dx,  outputFilePath   
   int 21h             
   jc openError        
   mov handleOutput, ax      
ret
fopenForWrite endp  

fopenForRead proc
   mov ah, 3dh         
   mov al, 00h          
   lea dx,  fileName + 2 
   int 21h             
   jc openError        
   mov handleInput, ax      
ret
fopenForRead endp  

fclose proc
   mov ah, 3eh         
   mov bx, handleInput     
   int 21h                        
ret
endp
error:
    print errorMessage
    print endl
    jmp exit 
openError:
    print openFileError
    print endl
    jmp exit

start:
    mov ax, data
    mov ds, ax
     
    call deleteFile
    call createForWrite
    call fopenForWrite
    
    call cmdPathGet  
    call parseCmdString
    mov ah, 09h
    lea dx, compulsoryChars + 2
    int 21h
 
    
    call fopenForRead  
     
    xor si,si
     xor cx,cx
     lea si,stringBuffer + 2   
stringLoop: 

     mov ah, 3Fh
     mov dx, si
     mov cx, 1
     mov bx, handleInput
     int 21h
      
     cmp ptr byte[si], 0Ah
     je callinFunc
     cmp ax, cx
     jne finalWord
     

     inc si
     
     jmp stringLoop    
    


callinFunc:
    inc si
    xor dx,dx
    mov ptr byte[si], '$' 
    xor cx, cx  
    call compareCompulsChars
    xor ax,ax

    lea si,stringBuffer + 2
    jmp stringLoop
    
    

finalWord:
    inc si
    mov ptr byte[si], '$' 
    call compareCompulsChars
    jmp exit
;qrtqwetwertwetwetrewertrewertrewertrewertytrewertytrewertytrewertrewertrewertrewert     
compareCompulsChars proc
xor bx,bx
 
lea si,stringBuffer + 1
mov bl,ptr byte[si] ; string length
inc si
lea di,compulsoryChars + 1
mov bh,ptr byte[di]; chars amount  
inc di
mov cl, bl
charCompare:
mov ch,ptr byte[di]
cmp ptr byte[si],ch
je errorInString
cmp ch, 'Z'
jle higherCaseCharsAndLowerCaseString
    lowerCaseCharsAndHigherCaseString:
    sub ch, 32
    cmp ptr byte[si], ch
    je errorInString
    jmp charIsNotEqual
higherCaseCharsAndLowerCaseString:
    add ch, 32
    cmp ptr byte[si], ch
    je errorInString    

charIsNotEqual:
dec bl
inc si
cmp bl, 0
je nextCharToCheck
jmp charCompare


nextCharToCheck:
dec bh
cmp bh, 0
je final
inc di
xor si,si
lea si,stringBuffer + 1
mov bl,ptr byte[si] ; string length
inc si
jmp charCompare


final:
xor si,si
printToFile handleOutput,stringBuffer   
print endl
    mov ah, 09h
    lea dx, stringBuffer +2
    int 21h
print endl
jmp ENDPP

errorInString:
ENDPP:
ret 
compareCompulsChars endp
;dfghjhgfdfghjkjhgfdfghjklkjhgfghjklkjhgfdfghjklkjhgfghjklkjhgfdfghjklkjhg


cmdPathGet proc
    lea si, cmdPath
    push ax
    push cx
    xor cx,cx
    mov cl, es:[80h]
     
    cld
    mov di, 82h     
fillInDataFromCmd:
    mov ax, es:[di]
    cmp al, 0Dh
    je endProc__
    mov ptr byte[si], al 
    inc si  
    inc di
    jmp fillInDataFromCmd
endProc__:
    mov ptr byte[si],0
     
    pop cx
    pop ax
    ret
cmdPathGet endp   
parseCmdString proc   
    
   xor cx,cx 
   xor ax,ax
   lea si, cmdPath 
   mov cl, ptr byte[si]
   lea di, fileName + 2
firstLoop:
 
    dec cl
    
    cmp ptr byte[si], ' '
    je cont
    mov al, ptr byte[si]
    mov ptr byte[di], al
    inc si
    inc di
    jmp firstLoop
cont:
    mov ptr byte[di], 0
    lea di, compulsoryChars + 1
secondLoop:
    inc di
    inc si
    dec cl
    cmp ptr byte[si], 0
    je exitProc
    mov al, ptr byte[si]
    mov ptr byte[di], al
    jmp secondLoop
exitProc:  ;
ret    
parseCmdString endp

exit:    
    print endl
    print finalMessage 
    call fclose
              
    mov ax, 4c00h
    int 21h   
ends
end start ; set entry point and stop the assembler.



;Cae?uoea oaeea
  