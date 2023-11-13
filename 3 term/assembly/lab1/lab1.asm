.model small
    .stack 100h
    .data
    message db 'String with sound$'
    .code
    
    start:
       mov ax, @data
       mov ds, ax
       mov dx, offset message                  
       mov ah, 9                         
       int 21h
       mov ah, 2
       mov dl, 7
       int 21h
       mov ah, 4Ch
       int 21h

       end start