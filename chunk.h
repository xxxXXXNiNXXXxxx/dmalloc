/*
 * defines for low level memory management routines
 *
 * Copyright 1991 by the Antaire Corporation
 *
 * $Id: chunk.h,v 1.8 1992/10/22 04:46:23 gray Exp $
 */

#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "malloc.h"			/* for IMPORT */

/*<<<<<<<<<<  The below prototypes are auto-generated by fillproto */

/* global debug level number */
IMPORT	int		_malloc_debug;

IMPORT	int		_malloc_errno;  /* error number */

IMPORT	int		_calloc_count;  /* # callocs, done in alloc */

/*
 * startup the low level malloc routines
 */
IMPORT	int	_chunk_startup(void);

/*
 * run extensive tests on the entire heap depending on TYPE
 */
IMPORT	int	_chunk_heap_check(void);

/*
 * run extensive tests on PNT
 */
IMPORT	int	_chunk_pnt_check(char * pnt);

/*
 * return some information associated with PNT, returns [NO]ERROR
 */
IMPORT	int	chunk_read_info(char * pnt, unsigned int * size, char ** file,
				unsigned int * line);

/*
 * get a SIZE chunk of memory for FILE at LINE
 */
IMPORT	char	*_chunk_malloc(char * file, unsigned int line,
			       unsigned int size);

/*
 * frees PNT from the heap, returns FREE_ERROR or FREE_NOERROR
 */
IMPORT	int	_chunk_free(char * file, unsigned int line, char * pnt);

/*
 * reallocate a section of memory
 */
IMPORT	char	*_chunk_realloc(char * file, unsigned int line, char * oldp,
				unsigned int new_size);

/*
 * log present free and used lists
 */
IMPORT	void	_chunk_list_count(void);

/*
 * log statistics on the heap
 */
IMPORT	void	_chunk_stats(void);

/*
 * dump the unfreed memory, logs the unfreed information to logger
 */
IMPORT	void	_chunk_dump_not_freed(void);

/*
 * log an entry for the heap structure
 */
IMPORT	void	_chunk_log_heap_map(void);

/*<<<<<<<<<<   This is end of the auto-generated output from fillproto. */

#endif /* ! __CHUNK_H__ */
