
	#
	# SPDX-License-Identifier: BSD-3-Clause
	# Copyright (c) 2025 Rene W. Olsen
	# Target OS: AmigaOS
	#

	.section	".text"
	.align		2

	.globl		_generic_setjmp_setjmp

_generic_setjmp_setjmp:

	# r1 - Stack Pointer
	# r3 - ( Parm 1 ) struct AmyCLibPrivIFace *
	# r4 - ( Parm 2 ) jmp_buf *

	# Align to 8 byte boundary
	addi		r4,r4,7			# Add Immediate
	rlwinm		r4,r4,0,0,28		# Rotate Left Word Immediate, Then AND with Mask

	# Store Return Address at Offset 0
	mflr		r10			# Move from Link Register
	stw		r10,0(r4)		# 

	# Store Condition Code at Offset 4
	mfcr		r10			# Move from Condition Register
	stw		r10,4(r4)		# 

	# Store Stack Pointer at Offset 8
	stw		r1,8(r4)		# 

	# Store Integers (r13-r31) at Offset 12
	stmw		r13,12(r4)		# Store Multiple Word

	# Store Floating Pointer at Offset 88
	stfd		f14,88(r4)		# Store Floating Point Double ( D-form )
	stfd		f15,96(r4)		# Store Floating Point Double ( D-form )
	stfd		f16,104(r4)		# Store Floating Point Double ( D-form )
	stfd		f17,112(r4)		# Store Floating Point Double ( D-form )
	stfd		f18,120(r4)		# Store Floating Point Double ( D-form )
	stfd		f19,128(r4)		# Store Floating Point Double ( D-form )
	stfd		f20,136(r4)		# Store Floating Point Double ( D-form )
	stfd		f21,144(r4)		# Store Floating Point Double ( D-form )
	stfd		f22,152(r4)		# Store Floating Point Double ( D-form )
	stfd		f23,160(r4)		# Store Floating Point Double ( D-form )
	stfd		f24,168(r4)		# Store Floating Point Double ( D-form )
	stfd		f25,176(r4)		# Store Floating Point Double ( D-form )
	stfd		f26,184(r4)		# Store Floating Point Double ( D-form )
	stfd		f27,192(r4)		# Store Floating Point Double ( D-form )
	stfd		f28,200(r4)		# Store Floating Point Double ( D-form )
	stfd		f29,208(r4)		# Store Floating Point Double ( D-form )
	stfd		f30,216(r4)		# Store Floating Point Double ( D-form )
	stfd		f31,224(r4)		# Store Floating Point Double ( D-form )

	# Set Return Value in r3
	li		r3,0			# Load Immediate

	# Return
	blr					# Brance on Link Register
