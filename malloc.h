/*
 * defines for the Malloc module
 *
 * Copyright 1991 by the Antaire Corporation
 *
 * $Id: malloc.h,v 1.2 1992/10/22 04:46:28 gray Exp $
 */

#ifndef __MALLOC_H__
#define __MALLOC_H__

/*
 * malloc function return codes
 */
#define CALLOC_ERROR		0		/* error from calloc */
#define MALLOC_ERROR		0		/* error from malloc */
#define REALLOC_ERROR		0		/* error from realloc */

#define FREE_ERROR		0		/* error from free */
#define FREE_NOERROR		1		/* no error from free */

#define MALLOC_VERIFY_ERROR	0		/* checks failed, error */
#define MALLOC_VERIFY_NOERROR	1		/* checks passed, no error */

/*
 * useful defines for all modules
 */

/*
 * global variable and procedure scoping for code readability
 */
#undef	EXPORT
#define	EXPORT

#undef	IMPORT
#define	IMPORT		extern

#undef	LOCAL
#define	LOCAL		static

/*
 * standard int return codes
 */
#ifndef ERROR

#undef	ERROR
#define	ERROR		(-1)

#undef	NOERROR
#define	NOERROR		0

#endif /* ! ERROR */

/*
 * generic constants
 */
#undef	NULL
#define NULL		0

#ifndef NULLC

#undef	NULLC
#define NULLC		'\0'

#undef	FALSE
#define FALSE		0

#undef	TRUE
#define TRUE		(! FALSE)

#endif /* ! NULLC */

/*
 * min/max macros
 *
 * WARNING: these use their arguments multiple times which may be bad
 */
#ifndef MAX

#undef MAX
#define MAX(a,b)	(((a) > (b)) ? (a) : (b))
#undef MIN
#define MIN(a,b)	(((a) < (b)) ? (a) : (b))

#endif /* ! MAX */

/*
 * bitflag tools for Variable and a Flag
 */
#ifndef BIT_FLAG

#undef BIT_FLAG
#define BIT_FLAG(x)		(1 << (x))
#undef BIT_SET
#define BIT_SET(v,f)		(v) |= (f)
#undef BIT_CLEAR
#define BIT_CLEAR(v,f)		(v) &= ~(f)
#undef BIT_IS_SET
#define BIT_IS_SET(v,f)		((v) & (f))

#endif /* ! BIT_FLAG */

/*
 * RCS id define
 */
#ifndef RCS_ID

#undef RCS_ID
#define RCS_ID(x)	\
  static void _rcs_id_() { \
    char *r = x; \
    char *s = "Built on: '" __DATE__ ", " __TIME__ "'"; \
    r++; s++;\
    _rcs_id_(); \
  }

#endif /* ! RCS_ID */
  
/*****************************************************************************/

/*
 * system function prototypes
 */
IMPORT	char	*strcat(char * dest, char *str);

#ifdef USG
IMPORT	char	*memcpy(char * to, char * from, int length);
IMPORT	char	*memset(char * pnt, int length);
IMPORT	char	*strchr(char * str, char ch);
#else
IMPORT	void	bcopy(void * from, void * to, int length);
IMPORT	void	bzero(void * b, int length);
IMPORT	char	*index(char * str, char ch);
#endif

/*
 * memory copy: copy SIZE bytes from pointer FROM to pointer TO
 */
#ifdef USG
#  define MEMORY_COPY(from, to, size)		memcpy(to, from, size);
#else
#  define MEMORY_COPY(from, to, size)		bcopy(from, to, size)
#endif

/*
 * memory zero: clear or zero-out SIZE bytes in pointer PNT
 */
#ifdef USG
#  define MEMORY_ZERO(pnt, size)		memset(pnt, 0, size);
#else
#  define MEMORY_ZERO(pnt, size)		bzero(pnt, size)
#endif

/*
 * string search: search for char CH in string STR and return a pointer to it
 */
#ifdef USG
#  define STRING_SEARCH(str, ch)		strchr(str, ch)
#else
#  define STRING_SEARCH(str, ch)		index(str, ch)
#endif

/*
 * string concatenate: append string STR to the end of string DEST
 */
#define STRING_CONCAT(dest, str)		strcat(dest, str)

/*****************************************************************************/

/*
 * alloc macros to provide for memory debugging features.
 */
#undef ALLOC
#define ALLOC(type, count) \
  (type *)_malloc_info(__FILE__, __LINE__, \
		       (unsigned int)(sizeof(type) * (count)))

/* WARNING: notice that the arguments are REVERSED from normal calloc() */
#undef CALLOC
#define CALLOC(type, count) \
  (type *)_calloc_info(__FILE__, __LINE__, (unsigned int)(count), \
		       (unsigned int)sizeof(type))

#undef  FREE
#define FREE(ptr) \
  _free_info(__FILE__, __LINE__, (char *)(ptr))

#undef  MALLOC
#define MALLOC(size) \
  (char *)_malloc_info(__FILE__, __LINE__, (unsigned int)(size))

#undef REALLOC
#define REALLOC(ptr, type, count) \
  (type *)_realloc_info(__FILE__, __LINE__, (char *)(ptr), \
		       (unsigned int)(sizeof(type) * (count)))

#undef REMALLOC
#define REMALLOC(ptr, size) \
  (char *)_realloc_info(__FILE__, __LINE__, (char *)(ptr), \
			(unsigned int)(size))

/*
 * some small allocation macros
 */

#ifdef __GNUC__

/* duplicate BUF of SIZE bytes */
#define BDUP(buf, size)	({ \
			  char	*_ret; \
			  int	_size = (size); \
			   \
			  if ((_ret = MALLOC(_size)) != NULL) \
			    MEMORY_COPY((buf), _ret, _size); \
			   \
			  _ret; \
			})

/* the strdup() function in macro form.  duplicate string STR */
#define STRDUP(str)	({ \
			  char	*_strp = (str); \
			  char	*_ret; \
			  int	_len; \
			   \
			  _len = strlen(_strp); \
			  if ((_ret = MALLOC(_len + 1)) != NULL) \
			    MEMORY_COPY(_strp, _ret, _len + 1); \
			   \
			  _ret; \
			})

#else /* ! __GNUC__ */

/* duplicate BUF of SIZE and return the new address in OUT */
#define BDUP(buf, size, out)	do { \
				  char	*_ret; \
				  int	_size = (size); \
				   \
				  if ((_ret = MALLOC(_size)) != NULL) \
				    MEMORY_COPY((buf), _ret, _size); \
				   \
				  (out) = _ret; \
				} while(0)

/* strdup() in macro form.  duplicate string STR and return a copy in OUT */
#define STRDUP(str, out)	do { \
				  char	*_strp = (str); \
				  char	*_ret; \
				  int	_len; \
				   \
				  _len = strlen(_strp); \
				  if ((_ret = MALLOC(_len + 1)) != NULL) \
				    MEMORY_COPY(_strp, _ret, _len + 1); \
				   \
				  (out) = _ret; \
				} while(0)

#endif /* ! __GNUC__ */

/*<<<<<<<<<<  The below prototypes are auto-generated by fillproto */

/* logfile for dumping malloc info, MALLOC_LOGFILE env. var overrides this */
IMPORT	char		*malloc_logpath;

/*
 * shutdown alloc module, provide statistics
 */
IMPORT	void	malloc_shutdown(void);

/*
 * allocate ELEN of elements of SIZE, then zero's the block
 */
IMPORT	char	*_calloc_info(char * file, int line, unsigned int elen,
			      unsigned int size);

/*
 * non-debug version of calloc_info
 */
IMPORT	char	*calloc(unsigned int elen, unsigned int size);

/*
 * release PNT in the heap from FILE at LINE
 */
IMPORT	int	_free_info(char * file, int line, char * pnt);

/*
 * non-debug version of free_info
 */
IMPORT	int	free(char * pnt);

/*
 * another non-debug version of free_info
 */
IMPORT	int	cfree(char * pnt);

/*
 * allocate a SIZE block of bytes from FILE at LINE
 */
IMPORT	char	*_malloc_info(char * file, int line, unsigned int size);

/*
 * non-debug version of malloc_info
 */
IMPORT	char	*malloc(unsigned int size);

/*
 * resizes PNT to SIZE bytes either copying or truncating
 */
IMPORT	char	*_realloc_info(char * file, int line, char * oldp,
			       unsigned int new_size);

/*
 * non-debug version of realloc_info
 */
IMPORT	char	*realloc(char * old_pnt, unsigned int new_size);

/*
 * call through to _heap_map function, returns [NO]ERROR
 */
IMPORT	int	malloc_heap_map(void);

/*
 * verify pointer PNT or if it equals 0, the entire heap
 * returns MALLOC_VERIFY_[NO]ERROR
 */
IMPORT	int	malloc_verify(char * pnt);

/*
 * set the global debug functionality flags to DEBUG.
 * returns [NO]ERROR
 */
IMPORT	int	malloc_debug(long debug);

/*
 * examine pointer PNT and returns SIZE, and FILE / LINE info on it
 * returns NOERROR or ERROR depending on whether PNT is good or not
 */
IMPORT	int	malloc_examine(char * pnt, int * size, char ** file,
			       int * line);

/*
 * malloc version of strerror to return the string version of ERRNUM
 * returns the string for MALLOC_BAD_ERRNO if ERRNUM is out-of-range.
 */
IMPORT	char	*malloc_strerror(int errnum);

/*<<<<<<<<<<   This is end of the auto-generated output from fillproto. */

#endif /* ! __MALLOC_H__ */
