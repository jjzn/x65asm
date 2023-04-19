	.org	0000

	lda	#00
	ldx	#00
	sta	00

loop:
	inx

	cpx	00
	beq	loop
	bne	end

end:	jmp	end
