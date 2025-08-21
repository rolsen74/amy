
	#
	# SPDX-License-Identifier: BSD-3-Clause
	# Copyright (c) 2025 Rene W. Olsen
	# Target OS: AmigaOS
	#

	.section	".text"
	.align		2

	.globl		_generic_setjmp_longjmp

_generic_setjmp_longjmp:

	# r1 - Stack Pointer
	# r3 - ( Parm 1 ) struct AmyCLibPrivIFace *
	# r4 - ( Parm 2 ) jmp_buf *
	# r5 - ( Parm 3 ) int val

	# Align to 8 byte boundary
	addi		r4,r4,7			# Add Immediate
	rlwinm		r4,r4,0,0,28		# Rotate Left Word Immediate, Then AND with Mask

	# Compute return value BEFORE restoring CR (cmpwi modifies CR0)
	cmpwi		r5, 0
	li		r3, 1
	beq		lab
	mr		r3, r5
lab:
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

	# Restore Integers (r13-r31) from Offset 12
	lmw		r13,12(r4)		# Load Multiple Word

	# Restore Stack Pointer from Offset 8
	lwz		r1,8(r4)		# 

	# Restore Codition Coditionode from Offset 4 (All fields)
	lwz		r10,4(r4)		# 
	mtcrf		0xFF,r10		# restore entire CR

	# Restore Return Address from Offset 0
	lwz		r10,0(r4)		# 
	mtlr		r10			# Move to Link Register

	blr					# Brance on Link Register

