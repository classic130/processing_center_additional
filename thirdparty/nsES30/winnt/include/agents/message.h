/*  ES3.0 messages */
#ifndef _H_MESSAGES
#define _H_MESSAGES


#ifdef __cplusplus
extern "C" {
#endif

#define NUM_NS_MESSAGES 40


typedef enum _t_NS_Messages {
	/* Document Object Messages */
	NS_DELETE_MSG           = 0,
	NS_ACCESS_MSG           = 1,
	NS_PUT_MSG              = 2,
	NS_EDIT_MSG             = 3,
	NS_SAVE_MSG             = 4,
	NS_MODIFY_MSG           = 5,
	NS_VIEW_MSG             = 6,
	NS_HEAD_MSG             = 7,
	NS_POST_MSG             = 8,
	NS_OPEN_MSG             = 9,
	NS_CLOSE_MSG            = 10,
	NS_READ_MSG             = 11,
	NS_WRITE_MSG            = 12,
	NS_MOVE_MSG             = 13,
	NS_QUERY_ATTR_MSG       = 14,
	NS_SET_ATTR_MSG         = 15,
	NS_GET_PROPERTIES_MSG   = 16, 
	NS_SET_PROPERTIES_MSG   = 17, 
	NS_COPY_MSG             = 18,
	NS_UNLOCK_MSG           = 19,
	NS_LOCK_MSG             = 20,

	/* Revision Control Messages */
	NS_RC_CHECKIN_MSG       = 21,
	NS_RC_CHECKOUT_MSG      = 22,
	NS_RC_GET_LOG_MSG       = 23,
	NS_RC_LABEL_MSG         = 24,
	NS_RC_GET_REV_MSG       = 25,
	NS_RC_DIFF_MSG          = 26,
	NS_RC_STOP_VER_MSG      = 27,
	NS_RC_UNCHECKOUT_MSG    = 28,

	/* Directory Object Messages */
	NS_DELETE_DIR_MSG       = 29,
	NS_MAKE_DIR_MSG         = 30,
	NS_INDEX_MSG            = 31,
	NS_MOVE_DIR_MSG         = 32,
	NS_RM_ALL_DIR_MSG       = 33,
	NS_QUERY_DIR_ATTR_MSG   = 34,
	NS_SET_DIR_ATTR_MSG     = 35,
	NS_COPY_DIRMSG          = 36,

	/* Timer message */
	NS_TIMER_MSG            = 37,

	/* Link management */
	NS_VERIFY_LINK          = 38,

	/* Acl's */
	NS_GETACL_MSG           = 39,
	NS_SETACL_MSG           = 40
} NS_Messages;

#ifdef __cplusplus
  }
#endif

#endif /* _H_MESSAGES */



