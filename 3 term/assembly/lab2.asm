.model small
    .stack 100h
    .data
    
    enterStringMessage db "Enter string: $"
    enterFirstWordMessage db 0Dh, 0Ah, "Enter first word: $"
    enterSecondWordMessage db 0Dh, 0Ah, "Enter second word: $"
    tryAgainMessage db 0Dh, 0Ah, "try again: $"
    checkMessage db "check $"
      
    space db " "  
    notFound db " is NOT found in string", 0Dh, 0Ah, "$" 
    found db " is found$"
    
    \n db 0Dh, 0Ah, "$"
    
    boolIsWordFounded db 0
     
    string db 200 dup("$")     
    wordFromString db 30 dup("$")
    ourWord db 30 dup("$")
    
    .code
    
;=== print ===============================================================================================================    
print macro outputMessage
    mov ah,9h
    lea dx, outputMessage
    int 21h
endm

;=== printPlus2 =============================================================================================================
printPlus2 macro outputMessage
    mov ah,9h
    lea dx, outputMessage + 2
    int 21h
endm

;=== scanfWithStringCheck ================================================================================================
scanfWithStringCheck macro                                   
    local scanf, takeFirstSymbolInString 
    local checkCharInStringIsLetterOrSpace, whenStringIsNotCorrect, endMacro
scanf:
    mov ah, 0Ah
    lea dx, string
    int 21h
    
takeFirstSymbolInString:                            
    lea si, string + 1 
    mov cl, ptr byte[si]
            
checkCharInStringIsLetterOrSpace:
    inc si    
    cmp cl, 0
    je endMacro
    dec cl
    
    cmp ptr byte[si], " "
    je checkCharInStringIsLetterOrSpace
    cmp ptr byte[si], "A"      
    jl whenStringIsNotCorrect        
    cmp ptr byte[si], "z"
    jg whenStringIsNotCorrect        
    cmp ptr byte[si], "Z"
    jle checkCharInStringIsLetterOrSpace
    cmp ptr byte[si], "a"
    jge checkCharInStringIsLetterOrSpace
    
whenStringIsNotCorrect:
    print tryAgainMessage
    jmp scanf
    
endMacro:                    
endm

;=== scanfWithWordCheck ==================================================================================================
scanfWithWordCheck macro string
    local scanf, takeFirstSymbolInString 
    local checkCharInStringIsLetter, whenStringIsNotCorrect, endMacro
scanf:
    mov ah, 0Ah
    lea dx, string
    int 21h
    
takeFirstSymbolInString:                            
    lea si, string + 1 
    mov cl, ptr byte[si]
            
checkCharInStringIsLetter:
    inc si    
    cmp cl, 0
    je endMacro
    dec cl
     
    cmp ptr byte[si], "A"      
    jl whenStringIsNotCorrect        
    cmp ptr byte[si], "z"
    jg whenStringIsNotCorrect        
    cmp ptr byte[si], "Z"
    jle checkCharInStringIsLetter
    cmp ptr byte[si], "a"
    jge checkCharInStringIsLetter
    
whenStringIsNotCorrect:
    print tryAgainMessage
    jmp scanf
    
endMacro:                    
endm

;=== ifTheWordExistsInString =============================================================================================
ifTheWordExistsInString macro string, wordFromString
    local takeSecondByteInString, takeSecondByteInWord, loopCheckEquality, endMacro
    local skipStringWord, wordFound, wordNotFound      
     
    xor bp,bp   
takeSecondByteInString:
    lea si, string + 1
    mov ch, ptr byte[si]
    
takeFirstCharInWord:    
    lea di, wordFromString + 1
    mov cl, ptr byte[di]
    
loopCheckEquality:
    inc si
    inc di
    inc bl
    dec ch
    dec cl
    
    cmp cl, 0
    je wordFound
    
    cmp ch, 0
    je wordNotFound
    
    mov bh, ptr byte[di]
    cmp ptr byte[si], bh
    jne skipStringWord
    
    jmp loopCheckEquality
    
      
skipStringWord:
    inc si
    dec ch
    inc bl
    cmp ch, 0
    je wordNotFound
    
    cmp ptr byte[si], " "
    je takeFirstCharInWord
    
    jmp skipStringWord    
    
             
wordFound:
    mov boolIsWordFounded, 1
    print found  
    lea si, wordFromString + 1
    mov cl, ptr byte[si]
    sub bl,cl 
    jmp endMacro
    
wordNotFound:
    print notFound
    mov boolIsWordFounded, 0
    jmp endMacro
        
endMacro:            
endm    
;=== stringOffset ========================================================================================================
stringOffset macro
    local takeLengthOfWord, offsetStringToEnd, endMacro

takeLengthOfWord:    
    lea si, ourWord + 1 
    mov cl, ptr byte[si]
    xor bh,bh  
    inc cl
offsetStringToEnd:
    lea si, string + 1
    mov ch, ptr byte[si] 
    inc si
    xor ah,ah
    mov bh,ch
toEndOfString:

    inc si
    dec ch  
    cmp ch,0
    je  loopOffset
    jmp toEndOfString
     
loopOffset: 
    xor ch,ch  
    xor dx,dx  
    
    mov bp, si
    mov dh, ptr byte[si] 
    add si, cx
    mov ptr byte[si], dh 
    mov si, bp
    


    dec si
    dec bh
    
    cmp bl, bh
    jg endMacro
      

                     
jmp loopOffset    
endMacro:    
endm

;=== enterOurWordInString ================================================================================================
enterOurWordInString macro
    local takeByteInWordAndString, takeCoordinates, enterBytesLoop, endLoop
    
takeByteInWordAndString:      
    lea si,string + 2
    lea di,ourWord + 1
    
takeCoordinates:        
    xor cx,cx
    
    mov cl, ptr byte[di]
    inc di 
    xor bh,bh 
    add si,bx
    xor bl,bl 
 
enterBytesLoop:
    cmp cl, 0    
    je endLoop
    mov bl,ptr byte[di]
    mov ptr byte[si], bl 
    inc si
    inc di
    dec cl 
    jmp enterBytesLoop
    
endLoop:
    mov bl, ' '
    mov ptr byte[si], bl 
endm    
;=== main ================================================================================================================    
main:
    mov ax,@data
    mov ds,ax
    
    print enterStringMessage
    scanfWithStringCheck
    
    loopIfWordWontFounded:
        print enterFirstWordMessage
        scanfWithWordCheck wordFromString
        
        ifTheWordExistsInString string, wordFromString
       
        cmp boolIsWordFounded, 0                   
    je loopIfWordWontFounded

   print enterSecondWordMessage
   scanfWithWordCheck ourWord
    
    
    print \n
    printPlus2 string
    
    stringOffset 
    enterOurWordInString


    print \n
    printPlus2 string
      
endProgram:  
    mov ah, 4Ch
    int 21h
end main
