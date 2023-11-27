	.model tiny
	org 100h
	.data
	flag db "Grabber"
	
	returnOldInteruptFlag db 0
	originalIRQ0 dd ?
	originalIRQ1 dd ?
	
	keyCode db 0
	saveFlag db 0
	screenWidth equ 80
	rawBufer db screenWidth dup (?)
	superThing db 0Ah
	screenHeight equ 25
	
	fileName db 125 dup (?),0
	fileDescriptor dw ?
	
	
    cmdError db "cmd params error", 0Dh, 0Ah, "format : executable name file name", '$'
	fileCreationError db "file was not created.", 0Dh, 0Ah, '$'
	pressKeyString db "Enter any key, but not 'Q', cause 'Q' is reserved", 0Dh, 0Ah, '$'
	keyPressedString db "'ctrl' + entered key to grab screen", 0Dh, 0Ah, "ctrl + 'Q' quit resident program.", 0Dh, 0Ah, '$'
	QKeyPressedString db "'Q' is reserved for exiting the program.", 0Dh, 0Ah, '$'
	programAlreadyInMemoryString db "program is already in memory.", 0Dh, 0Ah, '$'
	fileOpenErrorString db 0Dh, 0Ah, "error in save proccess!", 0Dh, 0Ah,"$"
	grabString db 0Dh, 0Ah, "grab!", 0Dh, 0Ah,"$"
	
	
	.code
	
main:
	jmp handlerInstall
	
;=== print ==========================================================================================================	
print macro string 
	mov ah, 09h
	lea dx, string
	int 21h
endm
	
	IRQ0 proc far               ;timer interruption
	pusha                       ;push all general purpose registers
	push ds
	push es
	
	mov ax, cs
	mov ds, ax                  ;cs -> ds
	
	cmp saveFlag, 1
	je saveCMD
	
	cmp returnOldInteruptFlag, 1                  ;if 1 -> return old interruption
	je returnInteruptions
	
	jmp IRQ0End
	
saveCMD:
	mov cs:saveFlag, 0                            ;set save flasg to zero
openFile:
	mov ah, 3dh                  ;open file
	mov al, 1                   ;write mode
	lea dx, fileName
	cli                          ;block interruptions
	int 21h
	sti                          ;enable interruptions
	jc fileOpenError
	
	mov fileDescriptor, ax
	jmp grabConsole
;=== fileOpenError ======================================================================================================	
fileOpenError:         ;file error
	print fileOpenErrorString
	mov cs:returnOldInteruptFlag, 1    ;set busy-flag
	jmp IRQ0End
	
	
grabConsole:
	mov ax, 0B800h               	;segment-address of video memory, exactly text mode
	mov es, ax
	
	mov di, 0
	mov cx, screenHeight         	;height of window
getCLLoop:                              ;loop iterated by height
	push cx
	lea si, rawBufer
	lea dx, rawBufer
	mov cx, screenWidth          	;width
getRawLoop:                          ;rewriting in file by byte
	mov al, es:di
	mov [si], al                 ;video memory byte -> rawbufer
	inc si                       ;iteration
	add di, 2                    ;2 bytes added - character and attribute
	loop getRawLoop
	mov ah, 40h                  ;write in file
	mov bx, fileDescriptor
	mov cx, screenWidth
	inc cx
	lea dx, rawBufer
	int 21h
	
	pop cx
	loop getCLLoop               ;if cx != 0
	
closeFile:
	mov ah, 3Eh
	mov bx, fileDescriptor
	cli
	int 21h
	sti
	
	print grabString
	
	jmp IRQ0End
	
returnInteruptions:           			; setting old interrupt addresses
installOldInteruptionsAddressed:
	mov ah, 25h
	mov al, 08h                  		; IRQ0
mov dx, word ptr cs:originalIRQ0
mov ds, word ptr cs:originalIRQ0 + 2
	int 21h                      		; set old interrupt addresses
	mov ah, 25h
	mov al, 09h                  		; IRQ1
mov dx, word ptr cs:originalIRQ1
mov ds, word ptr cs:originalIRQ1 + 2 	; set old interrupt addresses
	int 21h
	
IRQ0End:
	pushf
call cs:dword ptr originalIRQ0 		; call old handler
	pop es
	pop ds
	popa
	iret
	IRQ0 endp
	
	IRQ1 proc far					; keyboard interuption
	pusha
	pushf
call cs:dword ptr originalIRQ1		; call old handler
	
	mov ah, 01h
	int 16h                      	; wait for input
	jz IRQ1end                   	; if nothing
	
	
	mov dh, ah                   	; save scan-code
	
	mov ah, 02h
	int 16h
	and al, 4                    	; check for CTRL
	cmp al, 0
	jne checkExecuteKey
	jmp IRQ1end                  	; if not CTRL
	
checkExecuteKey:
cmp dh, cs:keyCode            		; if scan code is Q
	jne checkQ
	
mov cs:saveFlag, 1
	mov ah, 00h
	int 16h
	
	jmp IRQ1end
	
checkQ:
	cmp dh, 10h                  	; if Q is pressed, shut down our programm
	jne IRQ1end
mov cs:returnOldInteruptFlag, 1 	; flag of busy set in 1
	
	mov ah, 00h
	int 16h
IRQ1end:
	popa
	iret
	IRQ1 endp
	
	
handlerInstall:
; === getCommandLineParameters =========================================================================================	
getCommandLineParameters:
	mov ch, 0
	mov cl, es:[80h]              ; size of command line
	
	cmp cl, 1
	jbe noParamError
	
	mov si, 81h                  ; parameters start on space
	lea di, fileName
getInfoLoop:
spaceCheck:                   	 ; find space
	mov bl, es:[si]
	cmp bl, ' '
	je spaceFound                ; find
	movsb
	jmp endGetInfoLoop
spaceFound:                   	 ; skip space
	inc si
	
endGetInfoLoop:
	loop getInfoLoop

;=== createFile =========================================================================================================	
createFile:
	mov ah, 3Ch                  ; create file
	mov cx, 0
	lea dx, fileName             ; name
	int 21h
	jc cantCreateFile            ; check for creating
	
	mov fileDescriptor, ax
	
closeNewFile:
	mov ah, 3Eh                  ; close file 
	mov bx, fileDescriptor       ; file descriptor
	int 21h
	
	print pressKeyString

;=== getExecute Key Code ==============================================================================================	
getExecuteKeyCode:
	mov ah, 00h                  ; waiting for keyboard input
	int 16h						 ; ah - scan code, al - symba
	
	cmp ah, 10h                  ; if Q pressed
	je Qpressed
	jmp gotKey
Qpressed:
	print QKeyPressedString 	; print message
	jmp handlerInstall           		; and waiting for input again
;=== gotKey ===========================================================================================================	
gotKey:
	mov keyCode, ah              		; save scan-code of key
	print keyPressedString
	

;====getOriginalInterruptionsAddresses ==================================================================================	
getOriginalInterruptionsAddresses: 		; get address of original interrupt-handler
	mov ah, 35h           
	mov al, 09h                  		; IRQ1
	int 21h
	mov word ptr originalIRQ1, bx 		; offset of handler
	mov word ptr originalIRQ1 + 2, es 	; segment of handler
	
	mov ah, 35h              
	mov al, 08h							; IRQ0
	int 21h
	
	mov word ptr originalIRQ0, bx 
	mov word ptr originalIRQ0 + 2, es
	
checkAlreadyLoaded:
	lea di, flag
	lea si, flag
	mov cx, 7
	repe cmpsb
	je loaded

;=== setOwnInterruptions ================================================================================================	
setOwnInterruptions:
	mov ah, 25h                  					; set address of interruption handler
	mov al, 09h                  					; IRQ1 interruption number
	mov dx, offset IRQ1          					; offset of handler in segment
	int 21h
	
	mov ah, 25h                  					; the same for IRQ0
	mov al, 08h
	mov dx, offset IRQ0			
	int 21h
	
stayResident:
	mov ah, 31h                  					; stay programm resident
	mov dx, (handlerInstall - main + 10Fh) / 16 	; size of resident programm in 16-byte paragraph
	int 21h
	
noParamError:                 						; error message
	print cmdError
	jmp programEnd
cantCreateFile:
	print fileCreationError
	jmp programEnd
loaded:
	print programAlreadyInMemoryString
	jmp programEnd
	
programEnd:
	mov ax, 4Ch
	int 21h
	end main