/*
 * jopcodes.c - Opcode information tables for JVM opcodes.
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

#include "il_jopcodes.h"
#include "il_opcodes.h"

#ifdef	__cplusplus
extern	"C" {
#endif

ILOpcodeInfo const ILJavaOpcodeTable[256] = {
	{"nop",				0, 0, IL_OPCODE_ARGS_NONE, 1},

	{"aconst_null",		0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"iconst_m1",		0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"iconst_0",		0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"iconst_1",		0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"iconst_2",		0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"iconst_3",		0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"iconst_4",		0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"iconst_5",		0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"lconst_0",		0, 2, IL_OPCODE_ARGS_NONE, 1},
	{"lconst_1",		0, 2, IL_OPCODE_ARGS_NONE, 1},
	{"fconst_0",		0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"fconst_1",		0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"fconst_2",		0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"dconst_0",		0, 2, IL_OPCODE_ARGS_NONE, 1},
	{"dconst_1",		0, 2, IL_OPCODE_ARGS_NONE, 1},
	{"bipush",			0, 1, IL_OPCODE_ARGS_INT8, 2},
	{"sipush",			0, 1, IL_OPCODE_ARGS_INT16, 3},
	{"ldc",				0, 1, IL_OPCODE_ARGS_TOKEN, 2},
	{"ldc_w",			0, 1, IL_OPCODE_ARGS_TOKEN, 3},
	{"ldc2_w",			0, 2, IL_OPCODE_ARGS_TOKEN, 3},

	{"iload",			0, 1, IL_OPCODE_ARGS_SHORT_VAR, 2},
	{"lload",			0, 2, IL_OPCODE_ARGS_SHORT_VAR, 2},
	{"fload",			0, 1, IL_OPCODE_ARGS_SHORT_VAR, 2},
	{"dload",			0, 2, IL_OPCODE_ARGS_SHORT_VAR, 2},
	{"aload",			0, 1, IL_OPCODE_ARGS_SHORT_VAR, 2},
	{"iload_0",			0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"iload_1",			0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"iload_2",			0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"iload_3",			0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"lload_0",			0, 2, IL_OPCODE_ARGS_NONE, 1},
	{"lload_1",			0, 2, IL_OPCODE_ARGS_NONE, 1},
	{"lload_2",			0, 2, IL_OPCODE_ARGS_NONE, 1},
	{"lload_3",			0, 2, IL_OPCODE_ARGS_NONE, 1},
	{"fload_0",			0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"fload_1",			0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"fload_2",			0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"fload_3",			0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"dload_0",			0, 2, IL_OPCODE_ARGS_NONE, 1},
	{"dload_1",			0, 2, IL_OPCODE_ARGS_NONE, 1},
	{"dload_2",			0, 2, IL_OPCODE_ARGS_NONE, 1},
	{"dload_3",			0, 2, IL_OPCODE_ARGS_NONE, 1},
	{"aload_0",			0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"aload_1",			0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"aload_2",			0, 1, IL_OPCODE_ARGS_NONE, 1},
	{"aload_3",			0, 1, IL_OPCODE_ARGS_NONE, 1},

	{"iaload",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"laload",			2, 2, IL_OPCODE_ARGS_NONE, 1},
	{"faload",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"daload",			2, 2, IL_OPCODE_ARGS_NONE, 1},
	{"aaload",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"baload",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"caload",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"saload",			2, 1, IL_OPCODE_ARGS_NONE, 1},

	{"istore",			1, 0, IL_OPCODE_ARGS_SHORT_VAR, 2},
	{"lstore",			2, 0, IL_OPCODE_ARGS_SHORT_VAR, 2},
	{"fstore",			1, 0, IL_OPCODE_ARGS_SHORT_VAR, 2},
	{"dstore",			2, 0, IL_OPCODE_ARGS_SHORT_VAR, 2},
	{"astore",			1, 0, IL_OPCODE_ARGS_SHORT_VAR, 2},
	{"istore_0",		1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"istore_1",		1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"istore_2",		1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"istore_3",		1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"lstore_0",		2, 0, IL_OPCODE_ARGS_NONE, 1},
	{"lstore_1",		2, 0, IL_OPCODE_ARGS_NONE, 1},
	{"lstore_2",		2, 0, IL_OPCODE_ARGS_NONE, 1},
	{"lstore_3",		2, 0, IL_OPCODE_ARGS_NONE, 1},
	{"fstore_0",		1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"fstore_1",		1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"fstore_2",		1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"fstore_3",		1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"dstore_0",		2, 0, IL_OPCODE_ARGS_NONE, 1},
	{"dstore_1",		2, 0, IL_OPCODE_ARGS_NONE, 1},
	{"dstore_2",		2, 0, IL_OPCODE_ARGS_NONE, 1},
	{"dstore_3",		2, 0, IL_OPCODE_ARGS_NONE, 1},
	{"astore_0",		1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"astore_1",		1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"astore_2",		1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"astore_3",		1, 0, IL_OPCODE_ARGS_NONE, 1},

	{"iastore",			3, 0, IL_OPCODE_ARGS_NONE, 1},
	{"lastore",			4, 0, IL_OPCODE_ARGS_NONE, 1},
	{"fastore",			3, 0, IL_OPCODE_ARGS_NONE, 1},
	{"dastore",			4, 0, IL_OPCODE_ARGS_NONE, 1},
	{"aastore",			3, 0, IL_OPCODE_ARGS_NONE, 1},
	{"bastore",			3, 0, IL_OPCODE_ARGS_NONE, 1},
	{"castore",			3, 0, IL_OPCODE_ARGS_NONE, 1},
	{"sastore",			3, 0, IL_OPCODE_ARGS_NONE, 1},

	{"pop",				1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"pop2",			2, 0, IL_OPCODE_ARGS_NONE, 1},
	{"dup",				1, 2, IL_OPCODE_ARGS_NONE, 1},
	{"dup_x1",			2, 3, IL_OPCODE_ARGS_NONE, 1},
	{"dup_x2",			3, 4, IL_OPCODE_ARGS_NONE, 1},
	{"dup2",			2, 4, IL_OPCODE_ARGS_NONE, 1},
	{"dup2_x1",			3, 5, IL_OPCODE_ARGS_NONE, 1},
	{"dup2_x2",			4, 6, IL_OPCODE_ARGS_NONE, 1},
	{"swap",			2, 2, IL_OPCODE_ARGS_NONE, 1},

	{"iadd",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"ladd",			4, 2, IL_OPCODE_ARGS_NONE, 1},
	{"fadd",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"dadd",			4, 2, IL_OPCODE_ARGS_NONE, 1},
	{"isub",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"lsub",			4, 2, IL_OPCODE_ARGS_NONE, 1},
	{"fsub",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"dsub",			4, 2, IL_OPCODE_ARGS_NONE, 1},
	{"imul",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"lmul",			4, 2, IL_OPCODE_ARGS_NONE, 1},
	{"fmul",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"dmul",			4, 2, IL_OPCODE_ARGS_NONE, 1},
	{"idiv",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"ldiv",			4, 2, IL_OPCODE_ARGS_NONE, 1},
	{"fdiv",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"ddiv",			4, 2, IL_OPCODE_ARGS_NONE, 1},
	{"irem",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"lrem",			4, 2, IL_OPCODE_ARGS_NONE, 1},
	{"frem",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"drem",			4, 2, IL_OPCODE_ARGS_NONE, 1},
	{"ineg",			1, 1, IL_OPCODE_ARGS_NONE, 1},
	{"lneg",			2, 2, IL_OPCODE_ARGS_NONE, 1},
	{"fneg",			1, 1, IL_OPCODE_ARGS_NONE, 1},
	{"dneg",			2, 2, IL_OPCODE_ARGS_NONE, 1},
	{"ishl",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"lshl",			3, 2, IL_OPCODE_ARGS_NONE, 1},
	{"ishr",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"lshr",			3, 2, IL_OPCODE_ARGS_NONE, 1},
	{"iushr",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"lushr",			3, 2, IL_OPCODE_ARGS_NONE, 1},
	{"iand",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"land",			4, 2, IL_OPCODE_ARGS_NONE, 1},
	{"ior",				2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"lor",				4, 2, IL_OPCODE_ARGS_NONE, 1},
	{"ixor",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"lxor",			4, 2, IL_OPCODE_ARGS_NONE, 1},

	{"iinc",			0, 0, IL_OPCODE_ARGS_ANN_ARG, 3},

	{"i2l",				1, 2, IL_OPCODE_ARGS_NONE, 1},
	{"i2f",				1, 1, IL_OPCODE_ARGS_NONE, 1},
	{"i2d",				1, 2, IL_OPCODE_ARGS_NONE, 1},
	{"l2i",				2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"l2f",				2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"l2d",				2, 2, IL_OPCODE_ARGS_NONE, 1},
	{"f2i",				1, 1, IL_OPCODE_ARGS_NONE, 1},
	{"f2l",				1, 2, IL_OPCODE_ARGS_NONE, 1},
	{"f2d",				1, 2, IL_OPCODE_ARGS_NONE, 1},
	{"d2i",				2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"d2l",				2, 2, IL_OPCODE_ARGS_NONE, 1},
	{"d2f",				2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"i2b",				1, 1, IL_OPCODE_ARGS_NONE, 1},
	{"i2c",				1, 1, IL_OPCODE_ARGS_NONE, 1},
	{"i2s",				1, 1, IL_OPCODE_ARGS_NONE, 1},

	{"lcmp",			4, 1, IL_OPCODE_ARGS_NONE, 1},
	{"fcmpl",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"fcmpg",			2, 1, IL_OPCODE_ARGS_NONE, 1},
	{"dcmpl",			4, 1, IL_OPCODE_ARGS_NONE, 1},
	{"dcmpg",			4, 1, IL_OPCODE_ARGS_NONE, 1},

	{"ifeq",			1, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"ifne",			1, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"iflt",			1, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"ifge",			1, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"ifgt",			1, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"ifle",			1, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"if_icmpeq",		2, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"if_icmpne",		2, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"if_icmplt",		2, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"if_icmpge",		2, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"if_icmpgt",		2, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"if_icmple",		2, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"if_acmpeq",		2, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"if_acmpne",		2, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"goto",			0, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"jsr",				0, 1, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"ret",				0, 0, IL_OPCODE_ARGS_SHORT_VAR, 2},

	{"tableswitch",		1, 0, IL_OPCODE_ARGS_SWITCH, 0},
	{"lookupswitch",	1, 0, IL_OPCODE_ARGS_SWITCH, 0},

	{"ireturn",			1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"lreturn",			2, 0, IL_OPCODE_ARGS_NONE, 1},
	{"freturn",			1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"dreturn",			2, 0, IL_OPCODE_ARGS_NONE, 1},
	{"areturn",			1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"return",			0, 0, IL_OPCODE_ARGS_NONE, 1},

	{"getstatic",		0, 1, IL_OPCODE_ARGS_TOKEN, 3},
	{"putstatic",		1, 0, IL_OPCODE_ARGS_TOKEN, 3},
	{"getfield",		1, 1, IL_OPCODE_ARGS_TOKEN, 3},
	{"putfield",		2, 0, IL_OPCODE_ARGS_TOKEN, 3},

	{"invokevirtual",	0, 0, IL_OPCODE_ARGS_CALL, 3},
	{"invokespecial",	0, 0, IL_OPCODE_ARGS_CALL, 3},
	{"invokestatic",	0, 0, IL_OPCODE_ARGS_CALL, 3},
	{"invokeinterface",	0, 0, IL_OPCODE_ARGS_CALLI, 5},

	{"unused_BA",		0, 0, IL_OPCODE_ARGS_INVALID, 1},

	{"new",				0, 1, IL_OPCODE_ARGS_TOKEN, 3},
	{"newarray",		1, 1, IL_OPCODE_ARGS_NEW, 2},
	{"anewarray",		1, 1, IL_OPCODE_ARGS_TOKEN, 3},

	{"arraylength",		1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"athrow",			1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"checkcast",		1, 1, IL_OPCODE_ARGS_TOKEN, 3},
	{"instanceof",		1, 1, IL_OPCODE_ARGS_TOKEN, 3},
	{"monitorenter",	1, 0, IL_OPCODE_ARGS_NONE, 1},
	{"monitorexit",		1, 0, IL_OPCODE_ARGS_NONE, 1},

	{"wide",			0, 0, IL_OPCODE_ARGS_INVALID, 1},

	{"multianewarray",	0, 1, IL_OPCODE_ARGS_NEW, 4},

	{"ifnull",			1, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"ifnonnull",		1, 0, IL_OPCODE_ARGS_SHORT_JUMP, 3},
	{"goto_w",			0, 0, IL_OPCODE_ARGS_LONG_JUMP, 5},
	{"jsr_w",			0, 1, IL_OPCODE_ARGS_LONG_JUMP, 5},

	{"breakpoint",		0, 0, IL_OPCODE_ARGS_INVALID, 1},

	{"unused_CB",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_CC",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_CD",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_CE",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_CF",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_D0",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_D1",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_D2",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_D3",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_D4",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_D5",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_D6",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_D7",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_D8",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_D9",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_DA",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_DB",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_DC",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_DD",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_DE",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_DF",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_E0",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_E1",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_E2",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_E3",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_E4",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_E5",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_E6",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_E7",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_E8",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_E9",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_EA",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_EB",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_EC",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_ED",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_EE",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_EF",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_F0",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_F1",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_F2",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_F3",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_F4",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_F5",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_F6",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_F7",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_F8",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_F9",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_FA",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_FB",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_FC",		0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"unused_FD",		0, 0, IL_OPCODE_ARGS_INVALID, 1},

	{"impdep1",			0, 0, IL_OPCODE_ARGS_INVALID, 1},
	{"impdep2",			0, 0, IL_OPCODE_ARGS_INVALID, 1},
};

#ifdef	__cplusplus
};
#endif
