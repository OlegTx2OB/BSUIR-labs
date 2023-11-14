data segment
    inputFilePath db "input.txt", 0
    outputFilePath db "output.txt", 0
    inputFileIdentifier dw ?
    outputFileIdentifier dw ?
    symbolsString db 20 dup("$")
    buffer db 100 dup("$")
    
    mOutputDelete db "Output file deleted", 0Dh, 0Ah, "$"
    mOutputCreateAndOpen db "Output file recreated and opened", 0Dh, 0Ah, "$"
    mInputOpen db "Input file opened", 0Dh, 0Ah, "$"
    mInputSymbolsString db "Input symbols string: $"
    mInputScanStart db "Input file start scanning", 0Dh, 0Ah, "$"
    mInputScanEnd db "Input file end scanning", 0Dh, 0Ah, "$"
    mOutputCheck db "Check output file!", 0Dh, 0Ah, "$"
    mError db "ERROR", 0Dh, 0Ah, "$"
    
    m\n db 0Dh, 0Ah, "$"   
ends
stack segment 
ends
code segment
    
;=== print ================================================================================================================
print macro message
    mov ah, 9h
    lea dx, message
    int 21h
endm
;=== deleteOutputFile =====================================================================================================
deleteOutputFile:
    mov ah, 41h
    lea dx, outputFilePath
    int 21h
    jc error
    print mOutputDelete
    ret
    
;=== createAndOpenOutputFile ==============================================================================================
createOutputFile:
    mov ah, 5Bh
    mov cx, 7  ;���� ����� ��������� ������ ���������
    lea dx, outputFilePath
    int 21h
    jc error
    print mOutputCreateAndOpen
    mov [outputFileIdentifier], ax
    ret     
;=== openInputFile ========================================================================================================
openInputFile:
   mov ah, 3Dh
   mov al, 0 ;0 ��� ������, 1 ��� ������
   lea dx, inputFilePath
   int 21h
   jc error
   print mInputOpen
   mov [inputFileIdentifier], ax
   ret
;=== scanfSymbols =========================================================================================================
scanfSymbols:
    print mInputSymbolsString
    mov ah, 0Ah
    lea dx, symbolsString
    int 21h
    ret
;=== checkAndWriteInOutput ================================================================================================
checkAndWriteInOutput:
;//����� �������� ��� �������. ���������� input.txt �������� � [inputFileIdentifier], output.txt � [outputFileIdentifier]
;//����� � output.exe ��������� ������ � ���������, ������� ��� � ������ symbolsString

    mov ah, 3Fh  ; ������� ������ �� �����
    mov bx, [inputFileIdentifier]  ; ���������� �����
    lea dx, buffer  ; ����� ������ ��� ������
    mov cx, 7  ; ���������� ���� ��� ������
    mov di, 01
    int 21h  ; ����� ���������� 21h
    
    ; ����� ������ 5 ��������
    ;mov ah, 40h  ; ������� ������ � ����
    ;mov bx, outputFileIdentifier  ; �������� ���������� (stdout)
    ;lea dx, buffer  ; ����� ������
    ;mov cx, 5  ; ���������� ���� ��� ������
    ;int 21h
    
    ret          
;=== error ================================================================================================================       
error:
    print mError
    ret      
;=== main =================================================================================================================    
start:
    mov ax, data
    mov ds, ax
     
    call deleteOutputFile
    call createOutputFile
    call openInputFile
    call scanfSymbols
    call checkAndWriteInOutput 
     
    mov ax, 4c00h
    int 21h
    end start
    
ends     