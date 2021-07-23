GLOBAL invalidOpCode
GLOBAL divisionByZero

divisionByZero:
	mov rdx, 5
	mov al,1
	mov bl,0
	div bl
	ret

invalidOpCode:
	ud2
	ret