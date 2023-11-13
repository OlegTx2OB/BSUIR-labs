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
    mov ah, 3Dh  ; ������� 3Dh - �������� �����
    mov al, 0
    lea dx, outputFilePath  ; ����� ������ � ������ �����
    xor cx, cx  ; ����� ����� (0 ��� ��������)
    int 21h  ; ����� ���������� 21h

    ; �������� �� ������ �������� �����
    jc error

    ; ���������� ����������� �����
    mov bx, ax

    ; �������� �����
    mov ah, 3Eh  ; ������� 3Eh - �������� �����
    mov bx, ax  ; ���������� �����
    int 21h  ; ����� ���������� 21h

    ; �������� �� ������ �������� �����
    jc error

    ; �������� �����
    mov ah, 41h  ; ������� 41h - �������� �����
    lea dx, outputFilePath  ; ����� ������ � ������ �����
    int 21h  ; ����� ���������� 21h

    ; �������� �� ������ �������� �����
    jc error

    ; ���� ������� ������
    ; ...

    ; ���������� ���������
    mov ah, 4Ch  ; ������� 4Ch - ����� �� ���������
    xor al, al  ; ��� �������� (0)
    int 21h  ; ����� ���������� 21h
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