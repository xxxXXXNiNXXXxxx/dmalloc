/*
 * defines for low level memory management routines
 *
 * Copyright 1995 by Gray Watson
 *
 * This file is part of the dmalloc package.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * NON-COMMERCIAL purpose and without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies, and that the name of Gray Watson not be used in
 * advertising or publicity pertaining to distribution of the document
 * or software without specific, written prior permission.
 *
 * Please see the PERMISSIONS file or contact the author for information
 * about commercial licenses.
 *
 * Gray Watson makes no representations about the suitability of the
 * software described herein for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * The author may be contacted at gray.watson@letters.com
 *
 * $Id: chunk.h,v 1.41 1995/08/13 20:02:57 gray Exp $
 */

#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "dmalloc_loc.h"			/* for IMPORT ... */

/* some argument defines */
#define CHUNK_PNT_EXACT		BIT_FLAG(0)	/* pointer must be on block */
#define CHUNK_PNT_LOOSE		BIT_FLAG(1)	/* looser checking */
#define CHUNK_PNT_NULL		BIT_FLAG(2)	/* watch for null char */

/*<<<<<<<<<<  The below prototypes are auto-generated by fillproto */

/*
 * the unknown file pointer.  did not use DMALLOC_UNKNOWN_FILE everywhere else
 * the pointers would be different.
 */
IMPORT	char		*_dmalloc_unknown_file;

IMPORT	long		_calloc_count;  /* # callocs, done in alloc */

/*
 * startup the low level malloc routines
 */
IMPORT	int	_chunk_startup(void);

/*
 * display a bad pointer with FILE and LINE information
 */
IMPORT	char	*_chunk_display_where(const char * file,
				      const unsigned int line);

/*
 * run extensive tests on the entire heap
 */
IMPORT	int	_chunk_check(void);

/*
 * run extensive tests on PNT from FUNC. test PNT HOW_MUCH of MIN_SIZE
 * (or 0 if unknown).  CHECK is flags for types of checking (see chunk.h).
 * returns [NO]ERROR
 */
IMPORT	int	_chunk_pnt_check(const char * func, const void * pnt,
				 const int check, const int min_size);

/*
 * note in the chunk-level admin structures that BLOCKN blocks were
 * sbrk'ed externally by someone else up to MEM
 * returns [NO]ERROR
 */
IMPORT	int	_chunk_note_external(const int blockn, const void * mem);

/*
 * return some information associated with PNT, returns [NO]ERROR
 */
IMPORT	int	_chunk_read_info(const void * pnt, unsigned int * size,
				 unsigned int * alloc_size, char ** file,
				 unsigned int * line, void ** ret_attr,
				 const char * where, int ** seencp);

/*
 * log the heap structure plus information on the blocks if necessary
 */
IMPORT	void	_chunk_log_heap_map(void);

/*
 * get a SIZE chunk of memory for FILE at LINE
 */
IMPORT	void	*_chunk_malloc(const char * file, const unsigned int line,
			       const unsigned int size);

/*
 * frees PNT from the heap, returns FREE_ERROR or FREE_NOERROR
 */
IMPORT	int	_chunk_free(const char * file, const unsigned int line,
			    void * pnt);

/*
 * reallocate a section of memory
 */
IMPORT	void	*_chunk_realloc(const char * file, const unsigned int line,
				void * oldp, unsigned int new_size);

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
IMPORT	void	_chunk_dump_unfreed(void);

/*<<<<<<<<<<   This is end of the auto-generated output from fillproto. */

#endif /* ! __CHUNK_H__ */
