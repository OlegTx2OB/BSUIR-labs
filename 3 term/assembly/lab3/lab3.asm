.model small
;—Ã€—À: ¬¬≈—“» 30 ›À-“Œ¬ Ã¿——»¬¿ » œŒ—“–Œ»“‹ ƒ»¿√–¿ÃÃ” œŒ ◊¿—“Œ“≈ »’ œŒﬂ¬À≈Õ»ﬂ
    .stack 100h
    .data
    arraySize equ 30
    array db arraySize dup(0)
    enterArrayMessage db "Enter array elements (0-9)",0Dh, 0Ah, "$"
    yourArrayMessage db "Your Array: $"
    equalsString db "==========================================================", 0Dh, 0Ah, "$"
    \n db 0Dh, 0Ah, "$"
    O db "O$"
      
    .code
;=== print ===================================================================================
print macro message
    mov ah, 9h
    lea dx, message
    int 21h
endm

;=== enterArray ==============================================================================
enterArray macro
    mov si, 0    
inputLoop:    
    mov ah, 0
    int 16h
    
    cmp al, "0"
    jl inputLoop 
    cmp al, "9"
    jg inputLoop
    
    sub al, "0"
    
    mov [array + si], al
    
    inc si
    cmp si, arraySize
    jne inputLoop      
endm
;=== printArray =============================================================================
printArray macro    
    mov si, 0
printArrayLoop:
    
    mov ah, 2h
    mov dl, ptr byte[array + si]
    add dl, "0"
    int 21h
    
    mov dl, " "
    int 21h
    
    inc si
    cmp si, arraySize
    jne printArrayLoop   
endm
;=== printDiagrama ===========================================================================
printDiagrama macro
    mov si, 0
    mov di, 0
    
zeroToThirtyLoop:
    mov dl, [array + si]
    xor dh, dh
    cmp dx, di
    je founded
    inc si
    cmp si, arraySize 
    jg zeroToNineLoop
    jmp zeroToThirtyLoop
    ret

founded:
    mov ah, 2     
    mov dl, 254    
    int 21h
    inc si
    cmp si, arraySize 
    je zeroToNineLoop
    jmp zeroToThirtyLoop
    ret 
zeroToNineLoop:
    mov ah,9  
    lea dx, \n
    int 21h
     
    mov si, 0
    inc di 
    cmp di, 9
    jg endMacro 
    jmp zeroToThirtyLoop
    ret    
endMacro:       
endm    
;=== main =====================================================================================    
main:
    mov ax, @data
    mov ds, ax
    
    print enterArrayMessage
    enterArray
    
    print yourArrayMessage   
    printArray
    
    print \n
    print equalsString
    printDiagrama    
    print equalsString
    
    mov ah, 4Ch
    int 21h
end main