/*
 * il_utils.h - Utility functions.
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

#ifndef	_IL_UTILS_H
#define	_IL_UTILS_H

#ifdef	__cplusplus
extern	"C" {
#endif

/*
 * Structure of an intern'ed string.
 */
typedef struct
{
	char   *string;
	int		len;

} ILIntString;

/*
 * Hash a string value.
 */
unsigned long ILHashString(unsigned long start, const char *str, int len);

/*
 * Internalise a string.  The return value is guaranteed to be
 * unique for a string.  Comparing interned values with "==" is
 * identical to comparing them with "strcmp".
 */
ILIntString ILInternString(char *str, int len);

/*
 * Append two internalised strings and internalise the result.
 */
ILIntString ILInternAppendedString(ILIntString str1, ILIntString str2);

/*
 * Generate a GUID value.  The "guid" buffer must be at
 * least 16 bytes in length.
 */
void ILGUIDGenerate(unsigned char *guid);

/*
 * Structure of a memory pool allocation context.
 * This should be treated as opaque.
 */
typedef struct _tagILMemPool
{
	unsigned		size;			/* Size of items in the pool */
	unsigned		nitems;			/* Number of items in each block */
	unsigned		index;			/* Index of the next item to allocate */
	void           *blocks;			/* List of blocks in the memory pool */
	void		   *freeItems;		/* List of free items */

} ILMemPool;

/*
 * Initialize a memory pool.  The "nitems" value is a
 * hint, and the function is free to ignore it.  Setting
 * it to zero will always cause the function to choose
 * the best possible value.
 */
void ILMemPoolInit(ILMemPool *pool, unsigned size, unsigned nitems);

/*
 * Helper macro that initializes a memory pool for a specific type.
 */
#define	ILMemPoolInitType(pool,type,nitems)	\
			ILMemPoolInit((pool), sizeof(type), (nitems))

/*
 * Destroy a memory pool and all blocks within it.
 * Use this when the pool is no longer required.
 */
void ILMemPoolDestroy(ILMemPool *pool);

/*
 * Clear a memory pool.  This will automatically free all
 * of the allocated items, but it will attempt to keep
 * some of the system-allocated memory.  This can improve
 * performance when abandoning a pool's contents, but then
 * immediately starting to allocate from the pool again.
 */
void ILMemPoolClear(ILMemPool *pool);

/*
 * Allocate a new item from a memory pool.  Returns NULL
 * if out of memory.
 */
void *ILMemPoolAllocItem(ILMemPool *pool);

/*
 * Allocate a new item from a memory pool and clear it.
 * Returns NULL if out of memory.
 */
void *ILMemPoolCallocItem(ILMemPool *pool);

/*
 * Helper macros that allocate items of a specific type.
 */
#define	ILMemPoolAlloc(pool,type)	((type *)(ILMemPoolAllocItem((pool))))
#define	ILMemPoolCalloc(pool,type)	((type *)(ILMemPoolCallocItem((pool))))

/*
 * Free an item back to a memory pool.
 */
void ILMemPoolFree(ILMemPool *pool, void *item);

/*
 * Structure of a memory stack allocation context.
 * This should be treated as opaque.  A memory stack
 * differs from a memory pool in that it allocates
 * any size of structure from the same set of blocks,
 * and data can only be freed by freeing the stack.
 */
typedef struct _tagILMemStack
{
	unsigned		posn;			/* Position within the current block */
	unsigned		size;			/* Size of individual blocks */
	void		   *blocks;			/* List of blocks in the stack */
	unsigned long	currSize;		/* Current size of the stack */
	unsigned long	maxSize;		/* Maximum size of the stack */

} ILMemStack;

/*
 * Initialize a memory stack.  If "maxSize" is not zero,
 * then "ILMemStackAllocItem" will return NULL when the
 * stack grows too big.  This allows memory usage for the
 * stack to be restricted on low-memory devices.
 */
void ILMemStackInit(ILMemStack *stack, unsigned long maxSize);

/*
 * Destroy a memory stack.
 */
void ILMemStackDestroy(ILMemStack *stack);

/*
 * Allocate a data item from a memory stack.  Returns
 * NULL if out of memory.  The return value is guaranteed
 * to be cleared to all-zeroes.
 */
void *ILMemStackAllocItem(ILMemStack *stack, unsigned size);

/*
 * Helper macro that allocates items of a specific type.
 */
#define	ILMemStackAlloc(stack,type)	\
			((type *)(ILMemStackAllocItem((stack), sizeof(type))))

/*
 * Read a UTF-8 character from a string position.
 */
unsigned long ILUTF8ReadChar(const void *str, int len, int *posn);

/*
 * Write a UTF-8 character to a buffer.  Returns the
 * number of bytes used.  If the buffer is NULL, then
 * return the number of bytes needed.
 */
int ILUTF8WriteChar(char *str, unsigned long ch);

/*
 * Read a UTF-16 character from a 16-bit string position.
 * "len" and "posn" are indexes into a 16-bit array.
 */
unsigned long ILUTF16ReadChar(const unsigned short *str, int len, int *posn);

/*
 * Read a UTF-16 character from a string as little-endian values.
 * "len" and "posn" are indexes into a byte array.
 */
unsigned long ILUTF16ReadCharAsBytes(const void *str, int len, int *posn);

/*
 * Convert a 32-bit Unicode character into UTF-16.  Returns the
 * number of 16-bit characters required (1 or 2), or zero if
 * the character cannot be represented using UTF-16.  If "buf"
 * is NULL, then return the number of characters required.
 */
int ILUTF16WriteChar(unsigned short *buf, unsigned long ch);

/*
 * Convert a 32-bit Unicode character into UTF-16, and store it
 * using little-endian bytes at "buf".  Returns the number of
 * bytes (2 or 4), or zero if the character cannot be represented.
 * If "buf" is NULL, then return the number of bytes required.
 */
int ILUTF16WriteCharAsBytes(void *buf, unsigned long ch);

/*
 * Unicode character categories.
 */
typedef enum
{
	ILUnicode_UppercaseLetter				= 0,
	ILUnicode_LowercaseLetter				= 1,
	ILUnicode_TitlecaseLetter				= 2,
	ILUnicode_ModifierLetter				= 3,
	ILUnicode_OtherLetter					= 4,
	ILUnicode_NonSpacingMark				= 5,
	ILUnicode_SpaceCombiningMark			= 6,
	ILUnicode_EnclosingMark					= 7,
	ILUnicode_DecimalDigitNumber			= 8,
	ILUnicode_LetterNumber					= 9,
	ILUnicode_OtherNumber					= 10,
	ILUnicode_SpaceSeparator				= 11,
	ILUnicode_LineSeparator					= 12,
	ILUnicode_ParagraphSeparator			= 13,
	ILUnicode_Control						= 14,
	ILUnicode_Format						= 15,
	ILUnicode_Surrogate						= 16,
	ILUnicode_PrivateUse					= 17,
	ILUnicode_ConnectorPunctuation			= 18,
	ILUnicode_DashPunctuation				= 19,
	ILUnicode_OpenPunctuation				= 20,
	ILUnicode_ClosePunctuation				= 21,
	ILUnicode_InitialQuotePunctuation		= 22,
	ILUnicode_FinalQuotePunctuation			= 23,
	ILUnicode_OtherPunctuation				= 24,
	ILUnicode_MathSymbol					= 25,
	ILUnicode_CurrencySymbol				= 26,
	ILUnicode_ModifierSymbol				= 27,
	ILUnicode_OtherSymbol					= 28,
	ILUnicode_OtherNotAssigned				= 29,

} ILUnicodeCategory;

/*
 * Get the Unicode category associated with a character.
 */
ILUnicodeCategory ILGetUnicodeCategory(unsigned ch);

/*
 * Get the numeric value associated with a Unicode character.
 * Returns -1 if no value.
 */
double ILGetUnicodeValue(unsigned ch);

/*
 * Determine if a Unicode character is white space.
 */
int ILIsWhitespaceUnicode(unsigned ch);

/*
 * Option descriptors for command-line parsing support.
 */
typedef struct
{
	const char *name;
	short		value;
	short		hasParam;
	const char *helpString1;
	const char *helpString2;

} ILCmdLineOption;

/*
 * Get the next option from a command-line.
 */
int ILCmdLineNextOption(int *argc, char ***argv, int *state,
						const ILCmdLineOption *options, char **param);

/*
 * Print help data to "stderr".
 */
void ILCmdLineHelp(const ILCmdLineOption *options);

/*
 * Expand response files that are referenced by a command-line.
 */
void ILCmdLineExpand(int *argc, char ***argv);

/*
 * Spawn a child process and wait for it to exit.
 * Returns the exit status, or -1 on error.
 */
int ILSpawnProcess(char *argv[]);

/*
 * Opaque definition of the hash table type.
 */
typedef struct _tagILHashTable ILHashTable;

/*
 * Opaque definition of the hash entry type.
 */
typedef struct _tagILHashEntry ILHashEntry;

/*
 * Structure that is used to iterate over an entire hash table.
 */
typedef struct
{
	ILHashTable	   *hashtab;
	int				index;
	ILHashEntry	   *entry;

} ILHashIter;

/*
 * Compute the hash value for a particular element.
 */
typedef unsigned long (*ILHashComputeFunc)(const void *elem);

/*
 * Compute the hash value for a particular key.
 */
typedef unsigned long (*ILHashKeyComputeFunc)(const void *key);

/*
 * Determine if we have a match between an element
 * in the hash table and a particular key.
 */
typedef int (*ILHashMatchFunc)(const void *elem, const void *key);

/*
 * Free an element.
 */
typedef void (*ILHashFreeFunc)(void *elem);

/*
 * Create a hash table.  If "size" is zero, then use a
 * builtin default size.  All functions must be supplied,
 * except "freeFunc", which can be NULL if the elements
 * do not need to be free'd.  Returns NULL if out of memory.
 */
ILHashTable *ILHashCreate(int size, ILHashComputeFunc computeFunc,
						  ILHashKeyComputeFunc keyComputeFunc,
						  ILHashMatchFunc matchFunc,
						  ILHashFreeFunc freeFunc);

/*
 * Destroy a hash table.  If "freeFunc" is not NULL, then
 * also free all of the elements in the hash table.
 */
void ILHashDestroy(ILHashTable *hashtab);

/*
 * Add a new element to a hash table.  Returns zero if
 * out of memory.
 */
int ILHashAdd(ILHashTable *hashtab, void *elem);

/*
 * Find an element within a hash table by key.  Returns
 * the element, or NULL if not present.
 */
void *ILHashFind(ILHashTable *hashtab, const void *key);

/*
 * Find an element within a hash table using an alternative
 * key matching algorithm.  Returns the element, or NULL
 * if not present.
 */
void *ILHashFindAlt(ILHashTable *hashtab, const void *key,
					ILHashKeyComputeFunc keyComputeFunc,
					ILHashMatchFunc matchFunc);

/*
 * Helper macros for finding an element and then casting
 * the result to a particular structure type.
 */
#define	ILHashFindType(hashtab,key,type)	\
			((type *)ILHashFind((hashtab), (key)))
#define	ILHashFindAltType(hashtab,key,type,keyCompute,match)	\
			((type *)ILHashFindAlt((hashtab), (key), (keyCompute), (match)))

/*
 * Remove an element from the hash table.  The element will be
 * free'd if "freeElem" is non-zero, and "freeFunc" is not NULL.
 */
void ILHashRemove(ILHashTable *hashtab, void *elem, int freeElem);

/*
 * Remove a subset of the elements from the hash table.  The
 * elements will be free'd if "freeElem" is non-zero, and
 * "freeFunc" is not NULL.
 */
void ILHashRemoveSubset(ILHashTable *hashtab, ILHashMatchFunc matchFunc,
						const void *key, int freeElem);

/*
 * Initialize an iterator for scanning all elements
 * within a hash table.
 */
void ILHashIterInit(ILHashIter *iter, ILHashTable *hashtab);

/*
 * Get the next element within a hash table.  Returns NULL
 * at the end of the table.
 */
void *ILHashIterNext(ILHashIter *iter);

/*
 * Helper macro for getting the next element within a hash
 * table and casting the result to a particular structure type.
 */
#define	ILHashIterNextType(iter,type)	\
				((type *)ILHashIterNext((iter), (type)))

#ifdef	__cplusplus
};
#endif

#endif	/* _IL_UTILS_H */