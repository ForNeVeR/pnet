/*
 * cvm.h - Definitions for the "Converted Virtual Machine".
 *
 * Copyright (C) 2001  Southern Storm Software, Pty Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef	_ENGINE_CVM_H
#define	_ENGINE_CVM_H

#ifdef	__cplusplus
extern	"C" {
#endif

/*
 * Simple opcodes.
 */
#define	COP_NOP						0x00

/*
 * Local variable opcodes.
 */
#define	COP_ILOAD_0					0x01
#define	COP_ILOAD_1					0x02
#define	COP_ILOAD_2					0x03
#define	COP_ILOAD_3					0x04
#define	COP_ILOAD					0x05
#define	COP_PLOAD_0					0x06
#define	COP_PLOAD_1					0x07
#define	COP_PLOAD_2					0x08
#define	COP_PLOAD_3					0x09
#define	COP_PLOAD					0x0A
#define	COP_ISTORE_0				0x0B
#define	COP_ISTORE_1				0x0C
#define	COP_ISTORE_2				0x0D
#define	COP_ISTORE_3				0x0E
#define	COP_ISTORE					0x0F
#define	COP_PSTORE_0				0x10
#define	COP_PSTORE_1				0x11
#define	COP_PSTORE_2				0x12
#define	COP_PSTORE_3				0x13
#define	COP_PSTORE					0x14
#define	COP_MLOAD					0x15
#define	COP_MSTORE					0x16
#define	COP_WADDR					0x17
#define	COP_MADDR					0x18

/*
 * Argument fixups.
 */
#define	COP_BFIXUP					0x19
#define	COP_SFIXUP					0x1A
#define	COP_FFIXUP					0x1B
#define	COP_DFIXUP					0x1C

/*
 * Local variable allocation.
 */
#define	COP_MK_LOCAL_1				0x1D
#define	COP_MK_LOCAL_2				0x1E
#define	COP_MK_LOCAL_3				0x1F
#define	COP_MK_LOCAL_N				0x20

/*
 * Pointer reads and writes.
 */
#define	COP_BREAD					0x21
#define	COP_UBREAD					0x22
#define	COP_SREAD					0x23
#define	COP_USREAD					0x24
#define	COP_IREAD					0x25
#define	COP_FREAD					0x26
#define	COP_DREAD					0x27
#define	COP_PREAD					0x28
#define	COP_MREAD					0x29
#define	COP_BWRITE					0x2A
#define	COP_SWRITE					0x2B
#define	COP_IWRITE					0x2C
#define	COP_FWRITE					0x2D
#define	COP_DWRITE					0x2E
#define	COP_PWRITE					0x2F
#define	COP_MWRITE					0x30
#define	COP_BWRITE_R				0x31
#define	COP_SWRITE_R				0x32
#define	COP_IWRITE_R				0x33
#define	COP_FWRITE_R				0x34
#define	COP_DWRITE_R				0x35
#define	COP_PWRITE_R				0x36
#define	COP_MWRITE_R				0x37

/*
 * Stack handling.
 */
#define	COP_DUP						0x38
#define	COP_DUP2					0x39
#define	COP_DUP_N					0x3A
#define	COP_DUP_WORD_N				0x3B
#define	COP_POP						0x3C
#define	COP_POP2					0x3D
#define	COP_POP_N					0x3E
#define	COP_SQUASH					0x3F
#define	COP_CKHEIGHT				0x40
#define	COP_CKHEIGHT_N				0x41
#define	COP_SET_NUM_ARGS			0x42

/*
 * Arithmetic operators.
 */
#define	COP_IADD					0x43
#define	COP_IADD_OVF				0x44
#define	COP_IADD_OVF_UN				0x45
#define	COP_ISUB					0x46
#define	COP_ISUB_OVF				0x47
#define	COP_ISUB_OVF_UN				0x48
#define	COP_IMUL					0x49
#define	COP_IMUL_OVF				0x4A
#define	COP_IMUL_OVF_UN				0x4B
#define	COP_IDIV					0x4C
#define	COP_IDIV_UN					0x4D
#define	COP_IREM					0x4E
#define	COP_IREM_UN					0x4F
#define	COP_INEG					0x50
#define	COP_LADD					0x51
#define	COP_LADD_OVF				0x52
#define	COP_LADD_OVF_UN				0x53
#define	COP_LSUB					0x54
#define	COP_LSUB_OVF				0x55
#define	COP_LSUB_OVF_UN				0x56
#define	COP_LMUL					0x57
#define	COP_LMUL_OVF				0x58
#define	COP_LMUL_OVF_UN				0x59
#define	COP_LDIV					0x5A
#define	COP_LDIV_UN					0x5B
#define	COP_LREM					0x5C
#define	COP_LREM_UN					0x5D
#define	COP_LNEG					0x5E
#define	COP_FADD					0x5F
#define	COP_FSUB					0x60
#define	COP_FMUL					0x61
#define	COP_FDIV					0x62
#define	COP_FREM					0x63
#define	COP_FNEG					0x64

/*
 * Bitwise operators.
 */
#define	COP_IAND					0x65
#define	COP_IOR						0x66
#define	COP_IXOR					0x67
#define	COP_INOT					0x68
#define	COP_ISHL					0x69
#define	COP_ISHR					0x6A
#define	COP_ISHR_UN					0x6B
#define	COP_LAND					0x6C
#define	COP_LOR						0x6D
#define	COP_LXOR					0x6E
#define	COP_LNOT					0x6F
#define	COP_LSHL					0x70
#define	COP_LSHR					0x71
#define	COP_LSHR_UN					0x72

/*
 * Conversion operators.
 */
#define	COP_I2B						0x73
#define	COP_I2UB					0x74
#define	COP_I2S						0x75
#define	COP_I2US					0x76
#define	COP_I2L						0x77
#define	COP_IU2L					0x78
#define	COP_I2F						0x79
#define	COP_IU2F					0x7A
#define	COP_L2I						0x7B
#define	COP_L2F						0x7C
#define	COP_LU2F					0x7D
#define	COP_F2I						0x7E
#define	COP_F2IU					0x7F
#define	COP_F2L						0x80
#define	COP_F2LU					0x81
#define	COP_F2F						0x82
#define	COP_F2D						0x83
#define	COP_I2P_LOWER				0x84

/*
 * Binary value fixups.
 */
#define	COP_FIX_I4_I				0x85
#define	COP_FIX_I4_U				0x86

/*
 * Pointer arithmetic and manipulation.
 */
#define	COP_PADD_OFFSET				0x87
#define	COP_PADD_OFFSET_N			0x88
#define	COP_PADD_I4					0x89
#define	COP_PADD_I4_R				0x8A
#define	COP_PADD_I8					0x8B
#define	COP_PADD_I8_R				0x8C
#define	COP_PSUB					0x8D
#define	COP_PSUB_I4					0x8E
#define	COP_PSUB_I8					0x8F
#define	COP_CKNULL					0x90
#define	COP_CKNULL_N				0x91
#define	COP_LDRVA					0x92

/*
 * Constant opcodes.
 */
#define	COP_LDNULL					0x93
#define	COP_LDC_I4_M1				0x94
#define	COP_LDC_I4_0				0x95
#define	COP_LDC_I4_1				0x96
#define	COP_LDC_I4_2				0x97
#define	COP_LDC_I4_3				0x98
#define	COP_LDC_I4_4				0x99
#define	COP_LDC_I4_5				0x9A
#define	COP_LDC_I4_6				0x9B
#define	COP_LDC_I4_7				0x9C
#define	COP_LDC_I4_8				0x9D
#define	COP_LDC_I4_S				0x9E
#define	COP_LDC_I4					0x9F
#define	COP_LDC_I8					0xA0
#define	COP_LDC_R4					0xA1
#define	COP_LDC_R8					0xA2

/*
 * Branch opcodes.
 */
#define	COP_BR						0xA3
#define	COP_BEQ						0xA4
#define	COP_BNE						0xA5
#define	COP_BLT						0xA6
#define	COP_BLT_UN					0xA7
#define	COP_BLE						0xA8
#define	COP_BLE_UN					0xA9
#define	COP_BGT						0xAA
#define	COP_BGT_UN					0xAB
#define	COP_BGE						0xAC
#define	COP_BGE_UN					0xAD
#define	COP_BRTRUE					0xAE
#define	COP_BRFALSE					0xAF
#define	COP_BRNULL					0xB0
#define	COP_BRNONNULL				0xB1
#define	COP_BR_PEQ					0xB2
#define	COP_BR_PNE					0xB3
#define	COP_BR_LONG					0xB4
#define	COP_SWITCH					0xB5

/*
 * Array opcodes.
 */
#define	COP_BREAD_ELEM				0xB6
#define	COP_UBREAD_ELEM				0xB7
#define	COP_SREAD_ELEM				0xB8
#define	COP_USREAD_ELEM				0xB9
#define	COP_IREAD_ELEM				0xBA
#define	COP_PREAD_ELEM				0xBB
#define	COP_BWRITE_ELEM				0xBC
#define	COP_SWRITE_ELEM				0xBD
#define	COP_IWRITE_ELEM				0xBE
#define	COP_PWRITE_ELEM				0xBF
#define	COP_CKARRAY_LOAD_I4			0xC0
#define	COP_CKARRAY_LOAD_I8			0xC1
#define	COP_CKARRAY_STORE_I8		0xC2
#define	COP_ARRAY_LEN				0xC3

/*
 * Field opcodes.
 */
#define	COP_BREAD_FIELD				0xC4
#define	COP_UBREAD_FIELD			0xC5
#define	COP_SREAD_FIELD				0xC6
#define	COP_USREAD_FIELD			0xC7
#define	COP_IREAD_FIELD				0xC8
#define	COP_PREAD_FIELD				0xC9
#define	COP_BWRITE_FIELD			0xCA
#define	COP_SWRITE_FIELD			0xCB
#define	COP_IWRITE_FIELD			0xCC
#define	COP_PWRITE_FIELD			0xCD

/*
 * Call management opcodes.
 */
#define	COP_CALL					0xCE
#define	COP_CALL_EXTERN				0xCF
#define	COP_CALL_CTOR				0xD0
#define	COP_CALL_NATIVE				0xD1
#define	COP_CALL_NATIVE_VOID		0xD2
#define	COP_CALL_VIRTUAL			0xD3
#define	COP_CALL_INTERFACE			0xD4
#define	COP_RETURN					0xD5
#define	COP_RETURN_1				0xD6
#define	COP_RETURN_2				0xD7
#define	COP_RETURN_N				0xD8
#define	COP_JSR						0xD9
#define	COP_RET_JSR					0xDA
#define	COP_PUSH_THREAD				0xDB
#define	COP_PUSHDOWN				0xDC
#define	COP_CCTOR_ONCE				0xDD
#define	COP_CALLI					0xDE
#define	COP_JMPI					0xDF

/*
 * Class-related opcodes.
 */
#define	COP_CASTCLASS				0xE0
#define	COP_ISINST					0xE1
#define	COP_CASTINTERFACE			0xE2
#define	COP_ISINTERFACE				0xE3
#define	COP_GET_STATIC				0xE4
#define	COP_NEW						0xE5
#define	COP_NEW_VALUE				0xE6
#define	COP_LDSTR					0xE7
#define	COP_LDTOKEN					0xE8
#define	COP_BOX						0xE9
#define	COP_BOX_PTR					0xEA

/*
 * Memory-related opcodes.
 */
#define	COP_MEMCPY					0xEB
#define	COP_MEMMOVE					0xEC
#define	COP_MEMZERO					0xED
#define	COP_MEMSET					0xEE

/*
 * Argument packing for native calls.
 */
#define	COP_WADDR_NATIVE_M1			0xEF
#define	COP_WADDR_NATIVE_0			0xF0
#define	COP_WADDR_NATIVE_1			0xF1
#define	COP_WADDR_NATIVE_2			0xF2
#define	COP_WADDR_NATIVE_3			0xF3
#define	COP_WADDR_NATIVE_4			0xF4
#define	COP_WADDR_NATIVE_5			0xF5
#define	COP_WADDR_NATIVE_6			0xF6
#define	COP_WADDR_NATIVE_7			0xF7

/*
 * Make the next instruction wider.
 */
#define	COP_WIDE					0xFD

/*
 * Prefix for two-byte instruction opcodes.
 */
#define	COP_PREFIX					0xFF

/*
 * Prefixed comparison opcodes.
 */
#define	COP_PREFIX_ICMP				0x01
#define	COP_PREFIX_ICMP_UN			0x02
#define	COP_PREFIX_LCMP				0x03
#define	COP_PREFIX_LCMP_UN			0x04
#define	COP_PREFIX_FCMPL			0x05
#define	COP_PREFIX_FCMPG			0x06
#define	COP_PREFIX_PCMP				0x07
#define	COP_PREFIX_SETEQ			0x08
#define	COP_PREFIX_SETNE			0x09
#define	COP_PREFIX_SETLT			0x0A
#define	COP_PREFIX_SETLE			0x0B
#define	COP_PREFIX_SETGT			0x0C
#define	COP_PREFIX_SETGE			0x0D

/*
 * Prefixed array opcodes.
 */
#define	COP_PREFIX_LREAD_ELEM		0x0E
#define	COP_PREFIX_FREAD_ELEM		0x0F
#define	COP_PREFIX_DREAD_ELEM		0x10
#define	COP_PREFIX_LWRITE_ELEM		0x11
#define	COP_PREFIX_FWRITE_ELEM		0x12
#define	COP_PREFIX_DWRITE_ELEM		0x13

/*
 * Prefixed call management opcodes.
 */
#define	COP_PREFIX_TAIL				0x14
#define	COP_PREFIX_LDFTN			0x15
#define	COP_PREFIX_LDVIRTFTN		0x16
#define	COP_PREFIX_LDINTERFFTN		0x17

/*
 * Prefixed exception handling opcodes.
 */
#define	COP_PREFIX_ENTER_TRY		0x18
#define	COP_PREFIX_THROW			0x19
#define	COP_PREFIX_THROW_CALLER		0x1A

/*
 * Prefixed typedref handling opcodes.
 */
#define	COP_PREFIX_MKREFANY			0x1F
#define	COP_PREFIX_REFANYVAL		0x20
#define	COP_PREFIX_REFANYTYPE		0x21

/*
 * Prefixed conversion opcodes.
 */
#define	COP_PREFIX_I2B_OVF			0x22
#define	COP_PREFIX_I2UB_OVF			0x23
#define	COP_PREFIX_IU2B_OVF			0x24
#define	COP_PREFIX_IU2UB_OVF		0x25
#define	COP_PREFIX_I2S_OVF			0x26
#define	COP_PREFIX_I2US_OVF			0x27
#define	COP_PREFIX_IU2S_OVF			0x28
#define	COP_PREFIX_IU2US_OVF		0x29
#define	COP_PREFIX_I2IU_OVF			0x2A
#define	COP_PREFIX_IU2I_OVF			0x2B
#define	COP_PREFIX_I2UL_OVF			0x2C
#define	COP_PREFIX_L2I_OVF			0x2D
#define	COP_PREFIX_L2UI_OVF			0x2E
#define	COP_PREFIX_LU2I_OVF			0x2F
#define	COP_PREFIX_LU2IU_OVF		0x30
#define	COP_PREFIX_L2UL_OVF			0x31
#define	COP_PREFIX_LU2L_OVF			0x32
#define	COP_PREFIX_F2I_OVF			0x33
#define	COP_PREFIX_F2IU_OVF			0x34
#define	COP_PREFIX_F2L_OVF			0x35
#define	COP_PREFIX_F2LU_OVF			0x36
#define	COP_PREFIX_I2B_ALIGNED		0x37
#define	COP_PREFIX_I2S_ALIGNED		0x38
#define	COP_PREFIX_F2F_ALIGNED		0x39
#define	COP_PREFIX_F2D_ALIGNED		0x3A

/*
 * Prefixed arithmetic opcodes.
 */
#define	COP_PREFIX_CKFINITE			0x3B

/*
 * String conversion opcodes.
 */
#define	COP_PREFIX_STR2ANSI			0x3C
#define	COP_PREFIX_STR2UTF8			0x3D

/*
 * Inline method replacements.
 */
#define	COP_PREFIX_STRING_CONCAT_2	0x40
#define	COP_PREFIX_STRING_CONCAT_3	0x41
#define	COP_PREFIX_STRING_CONCAT_4	0x42
#define	COP_PREFIX_STRING_EQ		0x43
#define	COP_PREFIX_STRING_NE		0x44
#define	COP_PREFIX_STRING_GET_CHAR	0x45

/*
 * Definition of a CVM stack word which can hold
 * either 32-bit quantities or pointers.
 */
typedef union
{
	ILInt32		intValue;
	ILUInt32	uintValue;
	void       *ptrValue;

	/* Pad this structure to the best alignment on the underlying platform.
	   This is usually needed on 64-bit platforms to ensure that stack
	   words are always aligned on the best boundary.  On 32-bit platforms,
	   the size of this array will normally evaluate to zero.  We only do
	   this for gcc because other compilers may not support zero-size arrays */
#if defined(__GNUC__) && !defined(_WIN32)
	char		padding[IL_BEST_ALIGNMENT -
					    _IL_ALIGN_MAX(sizeof(ILInt32), sizeof(void *))];
#endif

} CVMWord;

/*
 * The number of stack words occupied by various types.
 */
#define	CVM_WORDS_PER_LONG	\
			((sizeof(ILInt64) + sizeof(CVMWord) - 1) / sizeof(CVMWord))
#define	CVM_WORDS_PER_FLOAT	\
			((sizeof(ILFloat) + sizeof(CVMWord) - 1) / sizeof(CVMWord))
#define	CVM_WORDS_PER_DOUBLE	\
			((sizeof(ILDouble) + sizeof(CVMWord) - 1) / sizeof(CVMWord))
#define	CVM_WORDS_PER_NATIVE_FLOAT	\
			((sizeof(ILNativeFloat) + sizeof(CVMWord) - 1) / sizeof(CVMWord))
#ifdef IL_NATIVE_INT64
#define	CVM_WORDS_PER_NATIVE_INT	CVM_WORDS_PER_LONG
#else
#define	CVM_WORDS_PER_NATIVE_INT	1
#endif
#define	CVM_WORDS_PER_TYPED_REF	\
			((sizeof(ILTypedRef) + sizeof(CVMWord) - 1) / sizeof(CVMWord))

/*
 * Maximum number of arguments that can be packed for a native call.
 */
#define	CVM_MAX_NATIVE_ARGS		8

#ifdef	__cplusplus
};
#endif

#endif	/* _ENGINE_CVM_H */