; tasm syntax assambler
; will compile .exe
; executable files
; in small model
; -------------------
; hello world example
.model small ; exe file
.stack 100h ; stack segment
.data ; data segment
	text db "Hello$", 0dh, 0ah ; text string
.code ; starting code segment
start:  ; a main label
	mov dx, @data ; load data segment 
	mov ds, dx ; address to ds

	lea dx, text ; load text address

	mov ah, 9 ; string print function
	int 21h ; write string
	
	mov ax, 4C00h ; exit code
	int 21h ; exit 
end start ; end start label
