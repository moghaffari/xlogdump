/*
 * xlogdump_rmgr.h
 *
 * a collection of functions which print xlog records generated
 * by each resource manager.
 */
#ifndef __XLOGDUMP_RMGR_H__
#define __XLOGDUMP_RMGR_H__

#include "postgres.h"
#include "access/gist_private.h"
#include "access/xlog.h"
#include "storage/block.h"
#include "storage/relfilenode.h"

/* XXX these ought to be in smgr.h, but are not */
#define XLOG_SMGR_CREATE	0x10
#define XLOG_SMGR_TRUNCATE	0x20

typedef struct xl_smgr_create
{
	RelFileNode rnode;
} xl_smgr_create;

typedef struct xl_smgr_truncate
{
	BlockNumber blkno;
	RelFileNode rnode;
} xl_smgr_truncate;

typedef struct
{
    gistxlogPageUpdate *data;
    int         len;
    IndexTuple *itup;
    OffsetNumber *todelete;
} PageUpdateRecord;

/* copied from backend/access/gist/gistxlog.c */
typedef struct
{
    gistxlogPage *header;
    IndexTuple *itup;
} NewPage;

/* copied from backend/access/gist/gistxlog.c */
typedef struct
{
    gistxlogPageSplit *data;
    NewPage    *page;
} PageSplitRecord;


extern const char * const RM_names[RM_MAX_ID+1];

void print_xlog_rmgr_stats(int);

void enable_rmgr_dump(bool);
void print_rmgr_xlog(OrgXLogRecPtr, OrgXLogRecord *, uint8, bool);
void print_rmgr_xact(OrgXLogRecPtr, OrgXLogRecord *, uint8, bool);
void print_rmgr_smgr(OrgXLogRecPtr, OrgXLogRecord *, uint8);
void print_rmgr_clog(OrgXLogRecPtr, OrgXLogRecord *, uint8);
void print_rmgr_dbase(OrgXLogRecPtr, OrgXLogRecord *, uint8);
void print_rmgr_tblspc(OrgXLogRecPtr, OrgXLogRecord *, uint8);
void print_rmgr_multixact(OrgXLogRecPtr, OrgXLogRecord *, uint8);

#if PG_VERSION_NUM >= 90000
void print_rmgr_relmap(OrgXLogRecPtr, OrgXLogRecord *, uint8);
void print_rmgr_standby(OrgXLogRecPtr, OrgXLogRecord *, uint8);
#endif

void print_rmgr_heap2(OrgXLogRecPtr, OrgXLogRecord *, uint8);
void print_rmgr_heap(OrgXLogRecPtr, OrgXLogRecord *, uint8, bool);
void print_rmgr_btree(OrgXLogRecPtr, OrgXLogRecord *, uint8);
void print_rmgr_hash(OrgXLogRecPtr, OrgXLogRecord *, uint8);
void print_rmgr_gin(OrgXLogRecPtr, OrgXLogRecord *, uint8);
void print_rmgr_gist(OrgXLogRecPtr, OrgXLogRecord *, uint8);
void print_rmgr_seq(OrgXLogRecPtr, OrgXLogRecord *, uint8);

#endif /* __XLOGDUMP_RMGR_H__ */
