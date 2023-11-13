data segment
    inputFilePath db "Z:\GitHub\BSUIR-labs\3 term\assembly\lab5\input.txt", 0
    outputFilePath db 'Z:\GitHub\BSUIR-labs\3 term\assembly\lab5\output.txt', 0
    
    mOutputDelete db "Output file deleted", 0Dh, 0Ah, "$"
    mOutputCreate db "Output file recreated", 0Dh, 0Ah, "$"
    mInputOpen db "Input file opened", 0Dh, 0Ah, "$"
    mInputScanStart db "Input file start scanning", 0Dh, 0Ah, "$"
    mInputScanEnd db "Input file end scanning", 0Dh, 0Ah, "$"
    mOutputCheck db "Check output file!", 0Dh, 0Ah, "$"
    mError db "ERROR", 0Dh, 0Ah, "$"
    
    m\n db 0Dh, 0Ah, "$"   
ends
stack segment 
ends
code segment
    
;=== print ===================================================================================
print macro message
    mov ah, 9h
    lea dx, message
    int 21h
endm
;=== deleteOutputFile ===================================
deleteOutputFile:
    ;mov ah, 41h
    ;lea dx, outputFilePath
    ;int 21h
    ;jc error
    ;print mOutputDelete
    mov ah, 3Dh  ; функция 3Dh - открытие файла
    mov al, 0
    lea dx, outputFilePath  ; адрес строки с именем файла
    xor cx, cx  ; флаги файла (0 для удаления)
    int 21h  ; вызов прерывания 21h

    ; Проверка на ошибку открытия файла
    jc error

    ; Сохранение дескриптора файла
    mov bx, ax

    ; Закрытие файла
    mov ah, 3Eh  ; функция 3Eh - закрытие файла
    mov bx, ax  ; дескриптор файла
    int 21h  ; вызов прерывания 21h

    ; Проверка на ошибку закрытия файла
    jc error

    ; Удаление файла
    mov ah, 41h  ; функция 41h - удаление файла
    lea dx, outputFilePath  ; адрес строки с именем файла
    int 21h  ; вызов прерывания 21h

    ; Проверка на ошибку удаления файла
    jc error

    ; Файл успешно удален
    ; ...

    ; Завершение программы
    mov ah, 4Ch  ; функция 4Ch - выход из программы
    xor al, al  ; код возврата (0)
    int 21h  ; вызов прерывания 21h
    ret 
    
error:
    print mError
    ret    
    
start:
    mov ax, data
    mov ds, ax
     
    call deleteOutputFile 
     
    mov ax, 4c00h
    int 21h
    end start
    
ends     