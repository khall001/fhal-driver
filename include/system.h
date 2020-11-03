/* SPDX-License-Identifier: MIT */
/*
 * Author: Andreas Werner <kernel@andy89.org>
 * Date: 2016
 */
#ifndef SYSTEM_H_
#define SYSTEM_H_
/**
 * \defgroup SYSTEM Useful Macros
 * \ingroup HAL
 * 
 * \code
 * #include <system.h>
 * \endcode
 * Useful Macros docu mostly copy from GCC Webpage
 * \{
 */

/**
 * The weak attribute causes the declaration to be emitted as a weak 
 * symbol rather than a global. This is primarily useful in defining 
 * library functions which can be overridden in user code, though it 
 * can also be used with non-function declarations. Weak symbols are 
 * supported for ELF targets, and also for a.out targets when using 
 * the GNU assembler and linker. 
 */
#define WEAK __attribute__ ((weak))
/**
 * The alias attribute causes the declaration to be emitted as an alias for another symbol, which must be specified. For instance,
 * \code
 * void __f () { / * do something * /; }
 * void f () WEAK ALIAS("__f");
 * \endcode
 * declares f to be a weak alias for __f. In C++, the mangled name for the target must be used.
 * Not all target machines support this attribute. 
 */
#define ALIAS(x) __attribute__ ((alias(#x)))
/**
 * Use this attribute on the ARM, AVR, M32R/D and Xstormy16 ports to indicate that the specified function is an interrupt handler. The compiler will generate function entry and exit sequences suitable for use in an interrupt handler when this attribute is present.
 * Note, interrupt handlers for the H8/300, H8/300H and SH processors can be specified via the interrupt_handler attribute.
 * 
 * Note, on the AVR interrupts will be enabled inside the function.
 *
 * Note, for the ARM you can specify the kind of interrupt to be handled by adding an optional parameter to the interrupt attribute like this:
 * \code
 * void f () INTERRUPT("IRQ");
 * \endcode
 * Permissible values for this parameter are: IRQ, FIQ, SWI, ABORT and UNDEF. 
 */
#define INTERRUPT(x) __attribute__ ((interrut(x)))
/**
 * Normally, the compiler places the code it generates in the text section. Sometimes, however, you need additional sections, or you need certain particular functions to appear in special sections. The section attribute specifies that a function lives in a particular section. For example, the declaration:
 * \code
 * extern void foobar (void) SECTION("bar");
 * \endcode
 * puts the function foobar in the bar section.
 * 
 * Some file formats do not support arbitrary sections so the section attribute is not available on all platforms. If you need to map the entire contents of a module to a particular section, consider using the facilities of the linker instead. 
 */
#define SECTION(x) __attribute__ ((section(x)))
/**
 * Use this attribute on the ARM or AVR ports to indicate that the specified function do not need prologue/epilogue sequences generated by the compiler. It is up to the programmer to provide these sequences. 
 */
#define NAKED __attribute__ ((naked))
/**
 * This attribute, attached to a function, means that code must be emitted for the function even if it appears that the function is not referenced. This is useful, for example, when the function is referenced only in inline assembly. 
 */
#define USED __attribute__ ((used))
/**
 * This attribute, attached to struct or union type definition, specifies that each member (other than zero-width bit-fields) of the structure or union is placed to minimize the memory required. When attached to an enum definition, it indicates that the smallest integral type should be used.
 * 
 * Specifying the packed attribute for struct and union types is equivalent to specifying the packed attribute on each of the structure or union members. Specifying the -fshort-enums flag on the command line is equivalent to specifying the packed attribute on all enum definitions.
 * 
 * In the following example struct my_packed_struct's members are packed closely together, but the internal layout of its s member is not packed—to do that, struct my_unpacked_struct needs to be packed too.
 *
 * \code
 * struct my_unpacked_struct {
 * 	char c;
 * 	int i;
 * };
 * struct PACKED my_packed_struct {
 * 	char c;
 * 	int  i;
 * 	struct my_unpacked_struct s;
 * };
 * \endcode
 * You may only specify the packed attribute attribute on the definition of an enum, struct or union, not on a typedef that does not also define the enumerated type, structure or union. 
 */
#define PACKED __attribute__ ((__packed__))
#if __GNUC__ >= 5 
#define NO_REORDER __attribute__ ((no_reorder))
#else
/* Not GCC or < GCC 5.0 has no no_reoder attribute */
/**
 * Do not reorder functions or variables marked no_reorder against each other or top level assembler statements the executable. The actual order in the program will depend on the linker command line. Static variables marked like this are also not removed. This has a similar effect as the -fno-toplevel-reorder option, but only applies to the marked symbols. 
 * 
 * Needed for Globale Device Instance Table
 * \warning in < GCC 5.0 not available -fno-toplevel-reorder automated activated in Makefile
 */
#define NO_REORDER
#endif
/**
 * This attribute specifies a minimum alignment for the variable or structure field, measured in bytes.
 */
#define ALGIN(x) __attribute__((aligned(x)))
/**
 * Nanosecond per Second 
 */
#define NSEC_PER_SEC 1000000000ULL
/**
 * Set a Bit on Value
 */
#define BIT(x) (1 << (x))
/**
 * Set a Bit on 64Bit Value 
 */
#define BIT64(x) (1ULL << (x))
/**
 * Get Array Size
 * \warning Waring only posibile with const arrays!
 * \param x const Variable
 * \return return Size
 */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
/**
 * Div Integer and round up
 * \param n Dividend
 * \param d Divisor
 */
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
/**
 * Maximum of two values
 * \param a first Parameter
 * \param b second Parameter
 * \return a or b
 */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
/**
 * Minimum of two values
 * \param a first Parameter
 * \param b second Parameter
 * \return a or b
 */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
/**
 * Swap 32 Bit
 * \param d 32 Bit data
 * \return swaped 32 Bit data
 */
#define swap32(d) ({ \
	union {uint32_t ret; uint8_t ret8[4];} tmp;\
	tmp.ret = (d); \
	/* swap 0 -> 3 and 1 -> 2 -> 0123 -> 3210 */ \
	/* use XOR Swap */ \
	tmp.ret8[0] ^= tmp.ret8[3]; \
	tmp.ret8[3] ^= tmp.ret8[0]; \
	tmp.ret8[0] ^= tmp.ret8[3]; \
	tmp.ret8[1] ^= tmp.ret8[2]; \
	tmp.ret8[2] ^= tmp.ret8[1]; \
	tmp.ret8[1] ^= tmp.ret8[2]; \
	tmp.ret; \
})
/**
 * Swap 16 Bit
 * \param d 16 Bit data
 * \return swaped 16 Bit data
 */
#define swap16(d) ({ \
	union {uint16_t ret; uint8_t ret8[2];} tmp;\
	tmp.ret = (d); \
	/* use XOR Swap */ \
	tmp.ret8[0] ^= tmp.ret8[1]; \
	tmp.ret8[1] ^= tmp.ret8[0]; \
	tmp.ret8[0] ^= tmp.ret8[1]; \
	tmp.ret; \
})
/**
 * CPU to Big Endian in 32 Bit
 * \param d 32 Bit data
 * \return swaped 32 Bit data
 */
#define cpu_to_be32(d) swap32(d)
/**
 * Big Endian to CPU in 32 Bit
 * \param d 32 Bit data
 * \return swaped 32 Bit data
 */
#define be32_to_cpu(d) swap32(d)
/**
 * CPU to Big Endian in 32 Bit
 * \param d 32 Bit data
 * \return swaped 32 Bit data
 */
#define cpu_to_be16(d) swap16(d)
/**
 * Big Endian to CPU in 32 Bit
 * \param d 32 Bit data
 * \return swaped 32 Bit data
 */
#define be16_to_cpu(d) swap16(d)
/**
 * CPU to Big Endian in 32 Bit
 * \param d 32 Bit data
 * \return swaped 32 Bit data
 */
#define cpu_to_le32(d) d
/**
 * Liddel Endian to CPU in 32 Bit
 * \param d 32 Bit data
 * \return swaped 32 Bit data
 */
#define le32_to_cpu(d) d
/**
 * Little Endian to CPU in 32 Bit
 * \param d 32 Bit data
 * \return swaped 32 Bit data
 */
#define cpu_to_le16(d) d
/**
 * Little Endian to CPU in 32 Bit
 * \param d 32 Bit data
 * \return swaped 32 Bit data
 */
#define le16_to_cpu(d) d

/**\}*/
#endif
