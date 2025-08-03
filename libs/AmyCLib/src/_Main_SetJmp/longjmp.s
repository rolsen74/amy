
	#
	# SPDX-License-Identifier: BSD-3-Clause
	# Copyright (c) 2025 Rene W. Olsen
	# Target OS: AmigaOS
	#

	.section	".text"
	.align		2

	.globl		_main_setjmp_longjmp

_main_setjmp_longjmp:

	# r1 - Stack Pointer
	# r3 - ( Parm 1 ) struct AmyCLibIFace *
	# r4 - ( Parm 2 ) jmp_buf *
	# r5 - ( Parm 3 ) int val

	# Align to 8 byte boundary
	addi		r4,r4,7			# Add Immediate
	rlwinm		r4,r4,0,0,28		# Rotate Left Word Immediate, Then AND with Mask

	# Restore Return Address from Offset 0
	lwz		r10,0(r4)		# Load Word
	mtlr		r10			# Move to Link Register

	# Restore Codition Coditionode from Offset 4
	lwz		r10,4(r4)		# Load Word
	mtcr		r10

	# Restore Stack Pointer from Offset 8
	lwz		r10,8(r4)		# Load Word
	mr		r1,r10			# Move to Register

	# Restore Integers from Offset 12
	lmw		r13,12(r4)		# Load Multiple Word
	lmw		r14,16(r4)		# Load Multiple Word
	lmw		r15,20(r4)		# Load Multiple Word
	lmw		r16,24(r4)		# Load Multiple Word
	lmw		r17,28(r4)		# Load Multiple Word
	lmw		r18,32(r4)		# Load Multiple Word
	lmw		r19,36(r4)		# Load Multiple Word
	lmw		r20,40(r4)		# Load Multiple Word
	lmw		r21,44(r4)		# Load Multiple Word
	lmw		r22,48(r4)		# Load Multiple Word
	lmw		r23,52(r4)		# Load Multiple Word
	lmw		r24,56(r4)		# Load Multiple Word
	lmw		r25,60(r4)		# Load Multiple Word
	lmw		r26,64(r4)		# Load Multiple Word
	lmw		r27,68(r4)		# Load Multiple Word
	lmw		r28,72(r4)		# Load Multiple Word
	lmw		r29,76(r4)		# Load Multiple Word
	lmw		r30,80(r4)		# Load Multiple Word
	lmw		r31,84(r4)		# Load Multiple Word

	# Restore Floating Points from Offset 88
	# Floating Points must be 8 byte alligned
	lfd		f14,88(r4)		# Load Floating Point Double
	lfd		f15,96(r4)		# Load Floating Point Double
	lfd		f16,104(r4)		# Load Floating Point Double
	lfd		f17,112(r4)		# Load Floating Point Double
	lfd		f18,120(r4)		# Load Floating Point Double
	lfd		f19,128(r4)		# Load Floating Point Double
	lfd		f20,136(r4)		# Load Floating Point Double
	lfd		f21,144(r4)		# Load Floating Point Double
	lfd		f22,152(r4)		# Load Floating Point Double
	lfd		f23,160(r4)		# Load Floating Point Double
	lfd		f24,168(r4)		# Load Floating Point Double
	lfd		f25,176(r4)		# Load Floating Point Double
	lfd		f26,184(r4)		# Load Floating Point Double
	lfd		f27,192(r4)		# Load Floating Point Double
	lfd		f28,200(r4)		# Load Floating Point Double
	lfd		f29,208(r4)		# Load Floating Point Double
	lfd		f30,216(r4)		# Load Floating Point Double
	lfd		f31,224(r4)		# Load Floating Point Double

	# Check Parm 3 for Zero Value
	cmpwi		r5,0			# Compare Word Immediate
	bne		lab			# Brance if not equal

	# Set Return Value in r3
	li		r3,1			# Load Immediate
	blr					# Brance on Link Register

lab:
	# Set Return Value in r3
	mr		r3, r5			# Move to Register
	blr					# Brance on Link Register

