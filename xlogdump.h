/*
 * xlogdump.h
 *
 * Common header file for the xlogdump utility.
 */
#ifndef __XLOGDUMP_H__
#define __XLOGDUMP_H__

typedef struct OrgXLogContRecord
{
	uint32		xl_rem_len;		/* total len of remaining data for record */

	/* ACTUAL LOG DATA FOLLOWS AT END OF STRUCT */

} OrgXLogContRecord;

typedef struct OrgXLogRecPtr
{
	uint32		xlogid;			/* log file #, 0 based */
	uint32		xrecoff;		/* byte offset of location in log file */
} OrgXLogRecPtr;

typedef struct OrgXLogRecord
{
	uint32		xl_tot_len;		/* total len of entire record */
	TransactionId xl_xid;		/* xact id */
	uint32		xl_len;			/* total len of rmgr data */
	uint8		xl_info;		/* flag bits, see below */
	RmgrId		xl_rmid;		/* resource manager for this record */
	/* 2 bytes of padding here, initialize to zero */
	OrgXLogRecPtr	xl_prev;		/* ptr to previous record in log */
	pg_crc32	xl_crc;			/* CRC for this record */

	/* If MAXALIGN==8, there are 4 wasted bytes here */

	/* ACTUAL LOG DATA FOLLOWS AT END OF STRUCT */

} OrgXLogRecord;


#define PRINT_XLOGRECORD_HEADER(X,Y) \
	printf("[cur:%X/%X, xid:%d, rmid:%d(%s), len/tot_len:%d/%d, info:%d, prev:%X/%X] ", \
	       (OrgXLogRecPtr)(X).xlogid, (OrgXLogRecPtr)(X).xrecoff, \
	       (Y)->xl_xid,		\
	       (Y)->xl_rmid,		\
	       RM_names[(Y)->xl_rmid],	\
	       (Y)->xl_len,		\
	       (Y)->xl_tot_len,		\
	       (Y)->xl_info,		\
	       (Y)->xl_prev.xlogid, (Y)->xl_prev.xrecoff)

struct transInfo
{
	TransactionId		xid;
	uint32			tot_len;
	int			status;
	struct transInfo	*next;
};

typedef struct transInfo transInfo;
typedef struct transInfo *transInfoPtr;

/* Transactions status used only with -t option */
static const char * const status_names[3] = {
	"NOT COMMITED",					/* 0 */
	"COMMITED    ",					/* 1 */
	"ABORTED     "
};

#endif /* __XLOGDUMP_H__ */
