.assembly extern '.library'
{
	.ver 0:0:0:0
}
.assembly '<Assembly>'
{
	.ver 0:0:0:0
}
.module '<Module>'
.class private auto abstract ansi 'Test' extends ['.library']'System'.'Object'
{
.method public virtual hidebysig newslot abstract specialname instance int32 'get_x'() cil managed java 
{
} // method get_x
.method public virtual hidebysig newslot abstract specialname instance void 'set_x'(int32 'value') cil managed java 
{
} // method set_x
.property int32 'x'()
{
	.get instance int32 'Test'::'get_x'()
	.set instance void 'Test'::'set_x'(int32)
} // property x
.method private hidebysig instance int32 'm1'() cil managed java 
{
	aload_0
	invokevirtual	instance int32 'Test'::'get_x'()
	ireturn
	.locals 1
	.maxstack 1
} // method m1
.method private static hidebysig int32 'm2'(class 'Test' 't') cil managed java 
{
	aload_0
	invokevirtual	instance int32 'Test'::'get_x'()
	ireturn
	.locals 1
	.maxstack 1
} // method m2
.method private hidebysig instance int32 'm3'(class 'Test' 't') cil managed java 
{
	aload_1
	invokevirtual	instance int32 'Test'::'get_x'()
	ireturn
	.locals 2
	.maxstack 1
} // method m3
.method private hidebysig instance void 'm4'(int32 'value') cil managed java 
{
	aload_0
	iload_1
	invokevirtual	instance void 'Test'::'set_x'(int32)
	return
	.locals 2
	.maxstack 2
} // method m4
.method private static hidebysig void 'm5'(class 'Test' 't', int32 'value') cil managed java 
{
	aload_0
	iload_1
	invokevirtual	instance void 'Test'::'set_x'(int32)
	return
	.locals 2
	.maxstack 2
} // method m5
.method private hidebysig instance void 'm6'(class 'Test' 't', int32 'value') cil managed java 
{
	aload_1
	iload_2
	invokevirtual	instance void 'Test'::'set_x'(int32)
	return
	.locals 3
	.maxstack 2
} // method m6
.method family hidebysig specialname rtspecialname instance void '.ctor'() cil managed java 
{
	aload_0
	invokespecial	instance void ['.library']'System'.'Object'::'.ctor'()
	return
	.locals 1
	.maxstack 1
} // method .ctor
} // class Test
