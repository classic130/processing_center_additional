/*
** QESQLEXT.H - This is the include file for applications using
**              the DataDirect Technologies ODBC Extensions
**
** (C) Copyright 1993-2002 By DataDirect Technologies, Inc.
*/

#ifndef __QESQLEXT
#define __QESQLEXT

/* DataDirect Technologies' SQLColAttributes extensions (1900 to 1949) */

#define SQL_COLATTR_START			1901

#define SQL_COLUMN_FULL_NAME			(SQL_COLATTR_START+0)
/* SQLBase - get fully qualified column name */

#define SQL_COLUMN_SEARCHABLE_COFC		(SQL_COLATTR_START+1)
/* Is column usable in a where clause for emulating current of cursor */

#define SQL_COLATTR_END				(SQL_COLATTR_START+1)


/* DataDirect Technologies' SQLSetConnectOption extensions (1040 to 1139) */

#define SQL_CONOPT_START			1040

#define SQL_TXN_CURSOR_STABILITY		(SQL_CONOPT_START+0)
/* Set isolation level to SQL_TXN_READ_COMMITTED with the extra ability of
 * having a position lock on SELECTed rows.  In SQLBase, this is the
 * difference between RL and CS isolation levels.
 */

#define SQL_LIC_FILE_NAME			(SQL_CONOPT_START+1)
/* Pass the name of the License file to use. */

#define SQL_LIC_FILE_PASSWORD			(SQL_CONOPT_START+2)
/* Pass the password for the License file. */

#define SQL_MODIFY_SQL				(SQL_CONOPT_START+3)
/* Alter the value of the ModifySql connection option. */

#define SQL_PROMPT_SETUP_DIALOG			(SQL_CONOPT_START+4)
/* Prompt the driver's setup dialog box. */

#define SQL_CREATE_TYPE				(SQL_CONOPT_START+5)
/* Pass NULL terminated string with create type specified. */

#define SQL_LIC_FILE_INI			(SQL_CONOPT_START+6)
/* Get the license file password from ISODBC.INI
 * This avoids the thunking problem
 */

/* SequeLink-specific connection options */

#define	SQL_SQLNK_DATADICTIONARY		(SQL_CONOPT_START+7)
#define SQL_SQLNK_DATADICTIONARYSCHEMA		(SQL_CONOPT_START+8)
#define SQL_SQLNK_DATADICTIONARYCATALOG		(SQL_CONOPT_START+9)
#define SQL_SQLNK_SERVERCOREVERSION		(SQL_CONOPT_START+10)
#define SQL_SQLNK_SERVERSERVICEVERSION		(SQL_CONOPT_START+11)
#define SQL_SQLNK_OEMID				(SQL_CONOPT_START+12)
#define SQL_SQLNK_APPID				(SQL_CONOPT_START+13)
#define SQL_SQLNK_AUTOMATICAPPID		(SQL_CONOPT_START+14)

#define SQL_FMP_INDEX_EMULATION			(SQL_CONOPT_START+20)
/* Used to turn index eumulation on/off for FileMaker driver.
 * Set to 0 for off, 15 to turn emulation on for all types.
 */


/* DataDirect Proprietary Connection/Env Attributes. */
#define SQL_ATTR_APP_WCHAR_TYPE			(SQL_CONOPT_START+21)
#define SQL_ATTR_DBMS_CODE_PAGE			(SQL_CONOPT_START+22)
#define SQL_ATTR_IGNORE_UNICODE_FUNCTIONS       (SQL_CONOPT_START+23)
#define SQL_ATTR_APP_UNICODE_TYPE               (SQL_CONOPT_START+24)
#define SQL_ATTR_DRIVER_UNICODE_TYPE            (SQL_CONOPT_START+25)
#define SQL_DD_CP_ANSI				0
#define SQL_DD_CP_UCS2				1
#define SQL_DD_CP_UTF8				2
#define SQL_DD_CP_UTF16				SQL_DD_CP_UCS2
/* Determines whether the application/dbms is handling SQLWCHAR
 * as UCS2 or UTF8.
 */

/* EASY SCHEMA IS USING THE LAST 15 CONNECT OPTIONS (1124-1139)
 * DO NOT USE
 */

#define SQL_COPT_EZ_START			(SQL_CONOPT_START+84)
#define SQL_COPT_EZ_END				(SQL_CONOPT_START+99)

#define SQL_CONOPT_END				(SQL_CONOPT_START+22)

/* DataDirect Technologies' SQLSetStmtOption extensions (1040 to 1139) */

#define SQL_STMTOPT_START			1040

#define SQL_INSERT_A_RECORD			(SQL_STMTOPT_START+0)
/* Pass row number to insert as vParam to SQLSetStmtOption */

#define SQL_DELETE_A_RECORD			(SQL_STMTOPT_START+1)
/* Pass row number to delete as vParam to SQLSetStmtOption
 * should be positioned to row before using backdoor
 */

#define SQL_PREPARE_FOR_BACKDOOR		(SQL_STMTOPT_START+2)
/* Pass operation (SQL_UPDATE_RECORD or SQL_INSERT_RECORD)
 * as vParam to SQLSetStmtOption
 */

#define SQL_UPDATE_COLUMN			(SQL_STMTOPT_START+3)
/* Pass a pointer to backdoor_column_info structure defined below
 * as vParam to SQLSetStmtOption
 */

#define SQL_UPDATE_A_RECORD			(SQL_STMTOPT_START+4)
/* Pass row number to update as vParam to SQLSetStmtOption
 * should be positioned to row before using backdoor
 */

#define SQL_LOCK_A_RECORD			(SQL_STMTOPT_START+5)
/* Pass row number to lock as vParam to SQLSetStmtOption
 * should be positioned to row before using backdoor
 */

#define SQL_GET_ROWCOUNT			(SQL_STMTOPT_START+7)
/* The driver guesses the number of rows a SELECT will return. */

#define SQL_GET_ROWID				(SQL_STMTOPT_START+8)
/* Get the rowid for the last row inserted */

#define SQL_GET_SERIAL_VALUE			(SQL_STMTOPT_START+9)
/* Get the value for the serial column in the last row inserted  */

#define SQL_ABORT_BACKDOOR			(SQL_STMTOPT_START+10)
/* Abort the last backdoor call.  Do the necessary clean up (e.g., free up
 * semaphores)
 */

#define SQL_GET_SESSIONID			(SQL_STMTOPT_START+11)
/* Get the value of the current session id. */

#define SQL_OPT_PLAN				(SQL_STMTOPT_START+12)
/* Get the optimization debug information */

#define SQL_PERSIST_AS_XML			(SQL_STMTOPT_START+13)
/* Persist a result set as XML. */

#define SQL_PERSIST_XML_TYPE		(SQL_STMTOPT_START+14)
/* Set the XML Type to persist a result set as. */


/* EASY SCHEMA IS USING THE LAST 15 STATEMENT OPTIONS (1124-1139)
 * DO NOT USE
 */

#define SQL_STMTOPT_EZ_START			(SQL_CONOPT_START+84)
#define SQL_STMTOPT_EZ_END			(SQL_CONOPT_START+99)

#define SQL_STMTOPT_END				(SQL_STMTOPT_START+14)


/* DataDirect Technologies' SQLGetInfo extensions (1011 to 1110) */

#define SQL_GETINF_START			1011

#define SQL_RESERVED_WORDS			(SQL_GETINF_START+0)
/* Comma separated list of reserved words.  ANSI SQL reserved words
 * are not included in this list.
 */

#define SQL_PSEUDO_COLUMNS			(SQL_GETINF_START+1)
/* Comma separated list of pseudo columns.  Combinations, such as DB2's
 * CURRENT DATE and CURRENT TIME, appear as separate multiword entries.
 */

#define SQL_FROM_RESERVED_WORDS			(SQL_GETINF_START+2)
/* Comma separated list of reserved words that can only appear in
 * the FROM clause.  SQLServer's HOLDLOCK is such an example.
 */

#define SQL_WHERE_CLAUSE_TERMINATORS		(SQL_GETINF_START+3)
/* Comma separated list of reserved words that end a WHERE clause.
 * ANSI standard words (UNION, ORDER BY, etc.) are not included.
 * Examples include Oracle's INTERSECT and CONNECT BY.
 */

#define SQL_COLUMN_FIRST_CHARS			(SQL_GETINF_START+4)
/* List of characters (other than A-Z) that are valid as the first
 * character in an unquoted column name.
 */

#define SQL_COLUMN_MIDDLE_CHARS			(SQL_GETINF_START+5)
/* List of characters (other than A-Z) that are valid as middle
 * characters in an unquoted column name.
 */

#define SQL_TABLE_FIRST_CHARS			(SQL_GETINF_START+7)
/* List of characters (other than A-Z) that are valid as the first
 * character in an unquoted table name.
 */

#define SQL_TABLE_MIDDLE_CHARS			(SQL_GETINF_START+8)
/* List of characters (other than A-Z) that are valid as middle
 * characters in an unquoted table name.
 */

#define SQL_DATADICT_EXTENSIONS			(SQL_GETINF_START+9)
/* TRUE if the driver can handle file name extensions, FALSE if it cannot.
 * The TEXT driver is an example of a driver than can nadle file name
 * extensions in SQLColumns calls.
 */

#define SQL_FAST_SPECIAL_COLUMNS		(SQL_GETINF_START+10)
/* The maximum scope which SQLSpecialColumns can return a pseudo column
 * without querying the database.  For example, the Oracle driver returns
 * "ROWID" for scopes less than or equal to SQL_SCOPE_TRANSACTION.  This
 * option applies to SQL_BEST_ROWID SQLSpecialColumns only.
 */

#define SQL_ACCESS_CONFLICTS			(SQL_GETINF_START+11)
/* TRUE if a "SELECT * FROM table" statement that has not fetched all its rows
 * may cause an "UPDATE table SET..." to hang.  In other words, SELECT
 * statements may acquire locks that cause UPDATE statements to wait forever.
 */

#define SQL_LOCKING_SYNTAX			(SQL_GETINF_START+12)
/* The words an application needs to add to a SELECT statement to make a
 * driver lock records.  This is either "FOR UPDATE OF" or "HOLDLOCK".
 */

#define SQL_LOCKING_DURATION			(SQL_GETINF_START+13)
/* How long the driver holds a record lock.  The driver returns either
 * 0 - record-level locking not supported, 1 - record is locked only while
 * positioned on it, 2 - record is locked until transaction ends.
 */

#define SQL_RECORD_OPERATIONS			(SQL_GETINF_START+14)
/* Which of the SQLSetStmtOption backdoors are supported by this driver. */
#define SQL_RECORD_DELETE   0x80000000L	/* Backdoor record delete supported */
#define SQL_RECORD_INSERT   0x40000000L	/* Backdoor record insert supported */
#define SQL_RECORD_UPDATE   0x20000000L	/* Backdoor record update supported */
#define SQL_RECORD_LOCK     0x10000000L	/* Backdoor record locking supported */
#define SQL_ROWCOUNT	    0x08000000L	/* Backdoor for guessing the number of */
																			/* rows a SELECT will return supported */

#define SQL_QUALIFIER_SYNTAX			(SQL_GETINF_START+15)
/* Information needed to build a table name using table qualifier. */
#define SQL_QUALIFIER_LAST	0x0001	/* Qualifier appears after table name */
#define SQL_OWNER_OPTIONAL	0x0002	/* Owner name is optional */

#define SQL_MAC_FILE_TYPE			(SQL_GETINF_START+16)
/* Macintosh file type the driver operates on. */

#define SQL_THREADING_MODEL			(SQL_GETINF_START+17)
/* Describes the driver's threading model.  An application which exceeds
 * a driver's capability may have threads blocked inside the driver. 
 */

#define SQL_THREAD_PER_STMT	0x0000	/* Threaded per statement */
#define SQL_THREAD_PER_CON	0x0001	/* Threaded per connection */
#define SQL_THREAD_PER_DRIVER	0x0002	/* Threaded per driver */

/* EASY SCHEMA IS USING THE LAST 15 GETIFOS (1124-1139)
 * DO NOT USE
 */

#define SQL_GETINF_EZ_START			(SQL_GETINF_START+84)
#define SQL_GETINF_EZ_END			(SQL_GETINF_START+99)

#define SQL_GETINF_END				(SQL_GETINF_START+16)


/* DataDirect Technologies' packet for SQL_UPDATE_COLUMN */

struct BackdoorColumnInfo {
	SWORD	CType;				/* ODBC C data type of value */
	PTR	Value;					/* value */
	SDWORD	Length;			/* length of value */
											/*	(or SQL_NULL_DATA or SQL_NTS) */
	UWORD	ColNum;				/* which column (1, 2, 3, ...) */
};

/* DataDirect Technologies' packet for SQL_PREPARE_FOR_BACKDOOR */

struct BackdoorPrepareInfo {
	UWORD	BackdoorOp;	/* which operation (SQL_UPDATE_A_RECORD, */
										/*	SQL_INSERT_A_RECORD) */
	UWORD	ColNum;			/* which column (1, 2, 3, ...) */
										/*	ignored on inserts */
};

/* DataDirect Technologies' packet for SQL_PROMPT_SETUP_DIALOG */

struct BackdoorSetupDialogStruct {
	HWND		ParentWindowHandle;
	UCHAR FAR 	*FileName;	/* changed from PCU8 is an
													 * internal type.  Since this is
													 * an external file only
													 * ODBC types should be used 
													 */
};

#endif
