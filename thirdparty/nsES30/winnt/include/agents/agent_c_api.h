#ifndef _AGENT_C_API_H_
#define _AGENT_C_API_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <stddef.h>
#include <time.h>

#include <netsite.h>

typedef struct {
    void*  data;
    size_t size;
} dataBlock_t ;

enum EAgentState { eEnabled, eDisabled, eDeleted };

/*
 * Even though the event types are used to distinguish agents, in some cases
 * the event type isn't very granular. For exampple, a timer agent could also
 * mean a search agent. The subtype clearly identifies the type of the agent
 */

enum eAgentSubType {eDocSubType, eDirSubType, eTimerSubType, eSearchSubType};

enum EAgentActionClass { 

    eDoNothing = 0,      /* just a null action */
    eCompositeAction,     /* Does the universe. USE THIS ONE  */
	eMailMsg,			/* Reserved for future use */
	eMailURL,			/* Reserved for future use */
	eHTTPPost,			/* Reserved for future use */
	eHTTPPostMail,		/* Reserved for future use */
	eHTTPGetPostMail,	/* Reserved for future use */
	eNNTPPost,			/* Reserved for future use */
	eGetUpdatedURLs,	/* Reserved for future use */
	eHTTPPut,			/* Reserved for future use */
    eLogToFile,          /* write to a file corresponding to a given URL */
    eRunJS,              /* run a JavaScript program */
    eRunProgram,         /* run any program */
    eCustom				/* plugin defined custom action, NOT SUPPORTED YET */

};

typedef enum { eSearch_by_Mdate, eSearch_All } ESearchQueryType;
typedef unsigned int InstanceId;
typedef unsigned int VersionNumber;
typedef short MessageId;

typedef int ns_agentEventClass_t;
const int NS_AGENT_DOCUMENT_EVENT =  0x1;
const int NS_AGENT_TIMER_EVENT    =   0x2;


typedef void* ns_agent_t;
typedef void* ns_agentId_t;
typedef void* ns_agentEvent_t;
typedef void* ns_agentAction_t;
typedef void* ns_agentActionList_t;

#define NS_AGENT_ERROR_BASE  0x0000ffff

typedef enum {
    NS_AGENT_SUCCESS = 0,
    NS_AGENT_STORE_INIT_FAILED = NS_AGENT_ERROR_BASE + 1,
    NS_AGENT_STORE_CORRUPTED,
    NS_AGENT_STORE_INCONSISTENT,
    NS_AGENT_ENTRY_NOT_FOUND,
    NS_AGENT_ENTRY_ALREADY_EXISTS,
    NS_AGENT_CALLER_NOT_AUTHORIZED,
    NS_AGENT_USER_LIMIT_REACHED,
    NS_AGENT_INVALID_EVENT,
    NS_AGENT_INTERNAL_ERROR,
    NS_AGENT_ACTION_PARSE_ERROR,
    NS_AGENT_MAX_LIMIT_REACHED
} ns_status_t;

enum ns_agent_timer_type{
    eTimerSpecific,
    eTimerPeriodicMinutes,
    eTimerPeriodicHours,
    eTimerPeriodicDays,
    eTimerPeriodicWeeks,
    eTimerPeriodicMonths,
    eTimerPeriodicYears,
    eTimerSelective,
    eUnknown=-1
};

/*
 * Returns the current stateof an agent (see enum EAgentState above)
 * as a character string.
 * DO NOT FREE THE RETURNED STRING
 */
NSAPI_PUBLIC const char *ns_AgentStatusToString(ns_status_t status);

NSAPI_PUBLIC ns_agent_t ns_AgentCreateAgentObject(
				     const char userName[], 
				     const char userAddr[], 
				     time_t expiryDate, 
				     size_t triggerLimit, 
				     const char creationNotificationAddr[], 
				     ns_agentEvent_t event, 
				     ns_agentActionList_t actionList, 
				     void* userData, 
				     size_t userDataSize,
				     const char *description /* agent name */
				    ); 

NSAPI_PUBLIC void ns_AgentDeleteAgentObject(ns_agent_t agent);

/* Various functions to get the fields of an agent object */
NSAPI_PUBLIC EAgentState ns_AgentGetState(const ns_agent_t agent);
NSAPI_PUBLIC time_t ns_AgentGetExpiryDate(const ns_agent_t agent); 
NSAPI_PUBLIC time_t ns_AgentGetLastModifiedDate(const ns_agent_t agent); 
NSAPI_PUBLIC size_t ns_AgentGetTriggerCount(const ns_agent_t agent);
NSAPI_PUBLIC size_t ns_AgentGetTriggerLimit(const ns_agent_t agent); 

/* DO NOT FREE THE RETURNED POINTER */
NSAPI_PUBLIC const char *ns_AgentGetNotificationAddr(const ns_agent_t agent);
NSAPI_PUBLIC const char *ns_AgentGetDescription(const ns_agent_t agent);

NSAPI_PUBLIC time_t ns_AgentGetLastTriggerDate(const ns_agent_t agent);
NSAPI_PUBLIC time_t ns_AgentGetCreationDate(const ns_agent_t agent);
NSAPI_PUBLIC size_t ns_AgentGetActionCount(const ns_agent_t agent);
NSAPI_PUBLIC const ns_agentId_t ns_AgentGetId(const ns_agent_t agent);

/* DO NOT FREE THE RETURNED POINTER */
NSAPI_PUBLIC const char* ns_AgentGetUserName(const ns_agent_t agent);

NSAPI_PUBLIC ns_agentEvent_t ns_AgentGetEventInfo(const ns_agent_t agent);
NSAPI_PUBLIC ns_agentActionList_t ns_AgentGetActionList(const ns_agent_t agent);

NSAPI_PUBLIC void ns_AgentSetExpiryDate(const ns_agent_t agent, 
										time_t expiryDate); 
NSAPI_PUBLIC void ns_AgentSetTriggerCount(const ns_agent_t agent);
NSAPI_PUBLIC void ns_AgentSetTriggerLimit(const ns_agent_t agent, int triggerLimit); 
NSAPI_PUBLIC void ns_AgentSetNotificationAddr(ns_agent_t agent, const char* address);
NSAPI_PUBLIC void ns_AgentSetDescription(ns_agent_t agent, const char* description);
NSAPI_PUBLIC void ns_AgentSetEventInfo(ns_agent_t agent, ns_agentEvent_t event);
NSAPI_PUBLIC void ns_AgentSetActionList(ns_agent_t agent, ns_agentActionList_t actionList);

/*
 * Routines to manipulate the opaque type ns_agentId_t 
 */

/*
 * Check if an agent id string is a valid id for an agent.
 * Performs synatx check of the string and return 1 if it is valid
 * otherwise returns 0
 */

NSAPI_PUBLIC int
ns_AgentIdStringIsValid(const char* agentIdStr);

/*
 * Caller owns the retunned ns_agentId_t object. Use  ns_AgentIdDelete
 * to free it when no longer needed.
 * WARNING: The agetIdStr cannot have trailing spaces or any other extraneous
 * characters. It should have been a id which was retrived from the agent
 * store.
 */
NSAPI_PUBLIC ns_agentId_t ns_AgentIdFromString(const char* agentIdStr);

/* Use ns_AgentIdDelete to free a ns_agentId_t object returned from 
	ns_AgentIdFromString 
*/
NSAPI_PUBLIC void ns_AgentIdDelete(ns_agentId_t agentId);
NSAPI_PUBLIC const char* ns_AgentIdToString(ns_agentId_t agentId);

/*
 * Routines to manipulate the opaque type ns_agentAction_t 
 * ns_AgentActionCreate:
 * Caller owns the returned object. Use ns_AgentActionDelete to get rid of it
 * (or pass it to ns_AgentCreate function shown above).
 * Most users would pass ECompositeAction as the argument. 
 * EAgentActionClass argument is really meant for future extensions.
 */
NSAPI_PUBLIC ns_agentAction_t ns_AgentActionCreate(EAgentActionClass type);

/* 
 Delete an ns_agentAction_t object, probably  created from 
 ns_AgentActionCreate function
*/
NSAPI_PUBLIC void ns_AgentActionDelete(ns_agentAction_t action);


/* Set the user associated with an action object. The action is executed 
   on behalf of this user.
 */
NSAPI_PUBLIC 
void ns_AgentActionSetUser(ns_agentAction_t action, const char user[],
							const char userAddr[]);


/* Retrieve a read-only copy of the user name and user address associated
   with this action object. DO NOT FREE THE ADDRESS IN THE POINTERS
 */

NSAPI_PUBLIC 
void ns_AgentActionGetUser(ns_agentAction_t action, const char** user,
							const char** userAddr);

/*
 * This returns one of 
		eDoNothing 
		eCompositeAction
		eLogToFile
		eRunJS
		eRunProgram
		eCustom
 * At this time, almost all actions are eComposite actions.
 * Also note that you cannot change the class of an action once it has been
 * created. 
 */
NSAPI_PUBLIC 
EAgentActionClass ns_AgentActionGetClass(const ns_agentAction_t action);


/*
 * Routines to manipulate the opaque type ns_agentActionList_t objects
 *
 * ns_AgentActionListCreate: Creates an actions list. Returns a dynamically
 * allocated object that must be freed using ns_AgentActionListDelete
 * function.
 */
NSAPI_PUBLIC 
ns_agentActionList_t ns_AgentActionListCreate(int numActions);

NSAPI_PUBLIC 
void ns_AgentActionListDelete(ns_agentActionList_t actionList);

/*
* The "action" argument passed in is adopted (takes over responsibility)
  by the list; dont free it
  The actionList object will take care of managing the action.
*/
NSAPI_PUBLIC 
void ns_AgentActionListAdd(const ns_agentActionList_t actionList, 
			   ns_agentAction_t action);

/*
 * Return the "action" object stored at the specified index in the 
 * actionList argument. You can use the returned action but do not free it.
 */
NSAPI_PUBLIC 
const ns_agentAction_t ns_AgentActionListGet(
							   const ns_agentActionList_t actionList, 
	              		       int index);

/* How many actions are stored in the actionList? */
NSAPI_PUBLIC 
size_t ns_AgentActionListCount(const ns_agentActionList_t actionList);


/*
* Routines to manipulate the opaque type ns_agentAction_t objects
* ns_AgentActionGetEMailMessage: returns a pointer to the message
* contained in the action object. If this action does not send email messages
* (for example, if it only does a HTTP GET), the returned pointer will be
* 0 (NUL). DO NOT FREE THE RETURNED POINTER
*/
NSAPI_PUBLIC 
const char* ns_AgentActionGetEMailMessage(ns_agentAction_t action);

/*
* ns_AgentActionGetEMailAddress: returns a pointer to the recipient address
* contained in the action object. If this action does not send email messages
* (for example, if it only does a HTTP GET), the returned pointer will be
* 0 (NUL). DO NOT FREE THE RETURNED POINTER
*/
NSAPI_PUBLIC 
const char* ns_AgentActionGetEmailAddress(ns_agentAction_t action);

/*
 * Routines to manipulate the opaque type ns_agentEvent_t objects
 * ns_AgentEventCreate: Creates a new event object and returns it. Caller
 * owns the returned object. It must either deleted (using ns_AgentEventDelete)
 * or it must be handed over to an agent object 
 * (using ns_AgentCreateAgentObject, which is the normal procedure).
 */
NSAPI_PUBLIC 
ns_agentEvent_t ns_AgentEventCreate();

/*
 * Delets an event object created by ns_AgentEventCreate
 */
NSAPI_PUBLIC 
void ns_AgentEventDelete(ns_agentEvent_t event);


/*
 * set the class of the event: eventClass is one of
	 NS_AGENT_DOCUMENT_EVENT
	 NS_AGENT_TIMER_EVENT
 */
NSAPI_PUBLIC 
void ns_AgentEventSetClass(ns_agentEvent_t event, 
							ns_agentEventClass_t eventClass);

NSAPI_PUBLIC 
ns_agentEventClass_t ns_AgentEventGetClass(const ns_agentEvent_t event);

/*
 * Set the event number (message id) for this event. msgId is a number
 * (NS_TIMER_MSG, NS_VIEW_MSG, etc. ) as shown in message.h. 
 * The event identifies the trigger that activates the
 * agent
 */

NSAPI_PUBLIC 
void ns_AgentEventSetMessageId(ns_agentEvent_t event, MessageId msgId);

NSAPI_PUBLIC 
MessageId ns_AgentEventGetMessageId(const ns_agentEvent_t event);

/* Return a text description of the event.
 * DO NOT FREE THE RETURNED POINTER
 */
NSAPI_PUBLIC 
const char* ns_AgentEventGetMessageIdAsText(const ns_agentEvent_t event);

/*
 * For a document event, specify the document to watch, the event to watch,
 * and the absolute path name of the document
 */
NSAPI_PUBLIC 
void ns_AgentEventSetDocumentContext(ns_agentEvent_t event,
				     MessageId messageId, 
				     const char url[], const char absolutePathName[]);

/*
 * Retrieve the corresponding components from a document event.
 * The returned pointer url must be freed when no longer needed. It is owned
 * by the caller.
 */
NSAPI_PUBLIC 
void ns_AgentGetDocumentContext(const ns_agentEvent_t event,
                                MessageId* messageId, char** url);

/*
 * For a timer event, specify the details of operation.
 * timer_type:  One of 
		eTimerSpecific (activates on a specific date and time)
		eTimerPeriodicMinutes
		eTimerPeriodicHours
		eTimerPeriodicDays
		eTimerPeriodicWeeks
		eTimerPeriodicMonths
		eTimerPeriodicYears
		eTimerSelective

 * startTime - this is a time_t based on local time
 * daysVector:  Activation days of the timer (for eTimerSeletive)
				Monday is 0 and Tuesday is 1... Sunday is 7
                daysVector[0] = 1 (activate on Monday)
                daysVector[1] = 1 (activate on Tuesday)
				...
                daysVector[6] = 0 (do not activate on Sunday)

	If the corresponding entry is not zero, the timer is 
	activated for that day.

 * period: The repetition frequency for eTimerPeriodicXXX timers
			periond in minutes if eTimerPeriodicMinutes
			periond in days if eTimerPeriodicDays
			periond in weeks if eTimerPeriodicWeeks
			periond in months if eTimerPeriodicMonths
			periond in years if eTimerPeriodicYears
 */
NSAPI_PUBLIC 
int ns_AgentEventSetTimerContext(ns_agentEvent_t event,
				 ns_agent_timer_type timer_type,
				 time_t startTime,
				 short  daysVector[7], 
				 unsigned long period);

NSAPI_PUBLIC
void ns_AgentEventGetTimerContext(const ns_agentEvent_t event,
                             ns_agent_timer_type *tmrType,
                             time_t* startTime,
                             time_t* prevTrigger, 
							 time_t* nextTrigger,
                             short daysVec[7],
                             unsigned long* period);


/*
 * Routines manipulate the agents in the subsystem
 * ns_AgentSubmit: Submit an agent for activation on the server. If this
				function succeeds, then the agent is ready for triggering
 */


NSAPI_PUBLIC 
ns_status_t ns_AgentSubmit(ns_agent_t agent);


/*
 * Set the subtype of an agent. This is required in cases where the agent 
 * event is a timer but its actions are somewhat more complicated
 * See enum eAgentSubType above
 * myAgent is the agent object whose subtype is being set.
 */

NSAPI_PUBLIC void ns_AgentSetSubType(ns_agent_t myAgent, eAgentSubType type);

/* The counter part: Get the subtype for the agent */
NSAPI_PUBLIC eAgentSubType ns_AgentGetSubType(const ns_agent_t myAgent);

/*
 * Enable an agent that has been previously disabled. 
 */
NSAPI_PUBLIC 
ns_status_t ns_AgentEnable(const ns_agentId_t agentId);

/*
 * Disable an agent that has been previously enabled. 
 */
NSAPI_PUBLIC 
ns_status_t ns_AgentDisable(const ns_agentId_t agentId);

/*
 * Modify (update) the "agent" with its new contents. The argument must
 * have proper values for all the fields, in particular the agent_id.
 * Usually, this operation is performed on an existing agent. One can 
 * retrieve an existing agent on the server (using one of the many functions
 * descrbed below), modify its attributes and 
 * call ns_AgentModify to update the agent store
 */
NSAPI_PUBLIC 
ns_status_t ns_AgentModify(const ns_agent_t agent);

/*
 * Look up the agent in the server. If an agent with the id agentId is in
 * the server, a pointer to it is returned.
 * The pointer agentP points to a dynamically allocated agent object. 
 * **** Call ns_AgentDeleteAgentObject on it when you are done with it.
 */

NSAPI_PUBLIC 
ns_status_t ns_AgentLookup(const ns_agentId_t agentId, ns_agent_t *agentP);

/*
 * Delete the agent with the id agentId from the server. Doing this will remove
 * the agent object from the agent store and also unsubscribes its event
 * registration. After this function completes, the agent no longer exists on
 * the server
 */

NSAPI_PUBLIC 
ns_status_t ns_AgentDelete(const ns_agentId_t agentId);

/*
 * Routine to get the agent ids of all agents waiting on the "event" 
 * The array agentListPP is an array of pointers to dynamically allocated
 * ns_agentId_t objects. Caller owns the objects contained in it. 
 * Invoke ns_AgentDeleteAgentIdList (see below) on it when you are done with it.
 */
NSAPI_PUBLIC 
ns_status_t ns_AgentGetAgentListByEvent(const ns_agentEvent_t event, 
				      int *count, ns_agentId_t **agentIdListPP);

/*
 * Routine to get the agent ids of all agents created for this user.
 * The array agentListPP is an array of ns_agentId_t objects. Caller owns
 * the objects contained in it. Invoke ns_AgentDeleteAgentIdList (see below)
 * on it when you are done with it.
 */
NSAPI_PUBLIC 
ns_status_t ns_AgentGetAgentListByUser(const char *user, 
				     int *countP, ns_agentId_t **agentListPP);
/*
 * Delete the agent id objects contained in the array pointed by agentListPP
 * Then delete the storage allocated for the array itself
 * count - # of elements in the array agentListPP
 * This function is the counterpart of  ns_AgentGetAgentListByUser and also
 * ns_AgentGetAgentListByEvent
 * Just pass in the results of that function to this function for clean-up.
 */
NSAPI_PUBLIC 
void ns_AgentDeleteAgentIdList(ns_agentId_t *agentIdListPP, int count);

/*
 * How many agents have been created for this user?
 * The count is written to the integer pointed by countP
 */
NSAPI_PUBLIC 
ns_status_t ns_AgentGetUserAgentCount(const char *user, int *countP);


/*
 * How many agents have been created for in the system
 */
NSAPI_PUBLIC 
ns_status_t ns_AgentGetAgentCount(int *countP);

/***********************************************************************

  THE FOLLOWING FUNCTIONS ARE HEKPER FUNCTIONS TO MANAGE ACTIONS. 
  THEY INTERNALLY USE A COMPOSITE ACTION TO MANAGER ALL THE DETAILS. THESE 
  FUNCTIONS ARE PROVIDED FOR THE CONVENIENCE OF THE DEVELOPER. 
  THE FUNCTION THAT CREATES A COMPOSITE ACTION REQUIRES 13 ARGUMENTS AND
  IT CAN BE IMPOSING FOR MOST DEVELOPERS. THESE HELPER FUNCTION MITIGATE
  THIS PROBLEM. ALL THESE HELPER FUNCTION ACCEPT ONLY THE ESSENTIAL 
  ARGUMENTS NEEDED FOR THAT ACTION AND THEN CREATE A COMPOSITE ACTION 
  IF YOUR NEEDS ARE NOT MET BY THESE HELPER FUNCTIONS, FEEL FREE TO USE
  THE FUNCTION THAT CREATES A COMPOSITE ACTION.

  Function : ns_AgentActionMailerCreate
  Returns  : an action object of correct type
  Input Parameters :  userAddress  - email address of agent owner
                      userName - name of agent owner for whom this action
                                 is being created
                      actionEmailAddr - send message to this address when
                                        agent is triggered
                      retAddr - Return address for the mail message
                      mailContents - contents of the mail message

  Create an action object which can send e-mail to userAddress with body being
  mailContents
 **********************************************************************/
NSAPI_PUBLIC ns_agentAction_t ns_AgentActionMailerCreate(
                        const char userName[],
                        const char userAddr[],
                        const char actionEmailAddr[],
                        const char retAddr[],
                        const char mailContents[]);

/***********************************************************************
  Function : ns_AgentActionPostAndMailCreate
  Returns  : an action object of correct type
  Input Parameters :  userAddress  - email address of agent owner
                      userName - name of agent owner for whom this action
                                 is being created
                      actionEmailAddr - send message to this address
                            (with the result of the POST) when agent is
                            triggered
                      retAddr - Return address for the mail message
                      postURL - URL to which HTTP POST is done
                      postData - contents of the HTTP POST message
                      mailContents - contents of the mail message


  Create an action object which can post to postURL and mail the result
    of the post to actionEmailAddr

 **********************************************************************/
NSAPI_PUBLIC ns_agentAction_t ns_AgentActionPostAndMailCreate(
                            const char userName[],
                            const char userAddr[],
                            const char actionEmailAddr[],
                            const char mailContents[],
                            const char retAddr[],
                            const char postURL[],
                            const char postData[]);
						


/***********************************************************************
  Function : ns_AgentActionGetAndMailCreate
  Returns  : an action object of correct type
  Input Parameters :  userAddress  - email address of agent owner
                      userName - name of agent owner for whom this action
                                 is being created
                      actionEmailAddr - send message to this address
                            (with the result of the GET) when agent is
                            triggered
                      retAddr - Return address for the mail message
                      mailContents - addtional contents for the mail message
                      getURL - URL from which HTTP GET is done

 The contents of the GET operation is sent to actionEmailAddr when agent is
 triggered

 **********************************************************************/
NSAPI_PUBLIC ns_agentAction_t ns_AgentActionGetAndMailCreate(
                            const char userName[],
                            const char userAddr[],
                            const char actionEmailAddr[],
                            const char retAddr[],
                            const char mailContents[],
                            const char getURL[]);

/***********************************************************************
  Function : ns_AgentActionMailerParse
  Returns  : ns_status_t which would be NS_AGENT_SUCCESS if the action was
             successfully parsed; otherwise it would be
            NS_AGENT_ACTION_PARSE_ERROR
             if the action was successfully parsed then, the return
             parameters would indicate :
             actionEmailAddr  - address to which mail would be sent
							 	when agent is triggered
              retAddr      - return email address
              emailMsg     - Contents of the mail message

  Input Parameters : const ns_agentAction_t action - action to be parsed

  Note that the user should not delete or change the conents of any of the
  parsed data
 **********************************************************************/

NSAPI_PUBLIC ns_status_t
ns_AgentActionMailerParse(const ns_agentAction_t action,
                          const char** actionEmailAddr,
                          const char** retAddr,
                          const char** emailMsg);						


/***********************************************************************
  Function : ns_AgentActionPostAndMailerParse
  Returns  : ns_status_t which would be NS_AGENT_SUCCESS if the action was
             successfully parsed; otherwise it would be
            NS_AGENT_ACTION_PARSE_ERROR
             if the action was successfully parsed then, the return
             parameters would indicate :

             actionEmailAddr  - address to which mail would be sent
							 	when agent is triggered
             retAddr      - return email address
             postURL      - URL of the HTTP POST operation
             postData     - actual HTTP POST message
             usrMesg     - additional contents supplied by user
							(if any)

  Input Parameters : const ns_agentAction_t action - action to be parsed

  Note that the user should not delete or change the conents of any of the
  parsed data
 **********************************************************************/
NSAPI_PUBLIC ns_status_t
ns_AgentActionPostAndMailerParse(const ns_agentAction_t action,
                  const char** actionEmailAddr,
                  const char** retAddr,
                  const char** postURL,
                  const char** postData,
                  const char** usrMesg);


/***********************************************************************
  Function : ns_AgentActionGetAndMailerParse
  Returns  : ns_status_t which would be NS_AGENT_SUCCESS if the action was
             successfully parsed; otherwise it would be
            NS_AGENT_ACTION_PARSE_ERROR
             if the action was successfully parsed then, the return
             parameters would indicate :
             actionEmailAddr  - email address of GET result recipient
             retAddr      - return email address
             getURL      - URL that was specified for the GET operation
			 usrMesg -   additional contents for the email

  Input Parameters : const ns_agentAction_t action - action to be parsed

  Note that the user should not delete or change the conents of any of the
  parsed data
 **********************************************************************/
NSAPI_PUBLIC ns_status_t
ns_AgentActionGetAndMailParse(const ns_agentAction_t action,
                  const char** actionEmailAddr,
                  const char** retAddr,
                  const char** usrMesg,
                  const char** getURL);


/***********************************************************************

  Function : ns_AgentActionNNTPPostCreate(
  Create an action object which can post to a newsgroup
  Returns  : an action object of correct type
  Input Parameters :  userAddress  - email address of agent owner
                      userName - name of agent owner for whom this action
                                 is being created
                      actionEmailAddr - send message to this address when
                                        agent is triggered
                     retAddr -   another required field in the news message
                                 Replies to the news message are sent to this
                                 address
                     newsGroup - to which a message is posted
                     newsSubject - subject field of the news message
                     newsMesg - contents of the news message
                     organization - This is a field in the news message
                                    usually this is the company name
 **********************************************************************/
NSAPI_PUBLIC ns_agentAction_t
ns_AgentActionNNTPPostCreate(
                        const char userName[],
                        const char userAddr[],
                        const char retAddr[],
                        const char newsGroup[],
                        const char newsSubject[],
                        const char newsMesg[],
                        const char organization[]);

/***********************************************************************
  Function : ns_AgentActionNNTPPostParse
  Returns  : ns_status_t which would be NS_AGENT_SUCCESS if the action was
             successfully parsed; otherwise it would be
            NS_AGENT_ACTION_PARSE_ERROR
             if the action was successfully parsed then, the return
             parameters would indicate :
                 newsgroup   - name of newsgroup specified
                 newsSubject - Subject of the news message
                 newsMesg    - body of the mesg
                 organization - as specified in the action
                 replyAddr - as specified in the action

  Input Parameters : const ns_agentAction_t action - action to be parsed

  Note that the user should not delete or change the conents of any of the
  parsed data
 **********************************************************************/

NSAPI_PUBLIC ns_status_t
ns_AgentActionNNTPPostParse(const ns_agentAction_t action,
                           const char** newsGroup,
                           const char** newsSubject,
                           const char** newsMesg,
                           const char** organization,
                           const char** replyAddr);

/***********************************************************************
  Function : ns_AgentActionSearchCreate
   Returns  : an action object of correct type
  Input Parameters :  userAddress  - email address of agent owner
                      userName - name of agent owner for whom this action
                      usrMesg[]   - messsage to be sent in email (optional)
                      newsGroup[] - newsgroup to post to (optional)
                      newsSubject[] - subject of the posting (optional)
                      newsMsg[]   - news messsage to be posted (optional)
                      toAddr - Address to which mail will be sent
                      organization[] - name of the organiztion
                                                 (both for news and mail)
                      replyAddr - The address to which replies will be sent
                                    (used in the newsgroup message)
                      retAddr - The address to which replies will be sent
                                    (used in mail messages)
                      searchPattern - what you want to search. 
									This can be as complex as you like
                      collection - This is the collection to in which to
								  search.  All documents under this
                                  collection will be searched.
                      updatedDocsOnly -  Search all documents or
										documents modified since last
										trigger
 **********************************************************************/
NSAPI_PUBLIC ns_agentAction_t
ns_AgentActionSearchCreate(const char username[],
							const char userAddr[],
                            const char toAddr[],
                            const char retAddr[],
                            const char usrMesg[],
                            const char  newsGroup[],
                            const char  newsSubject[],
                            const char organization[],
                            const char replyAddr[],
							const char collection[],
                            ESearchQueryType searchType,
                            const char searchPattern[]);

NSAPI_PUBLIC ns_status_t
ns_AgentActionSearchParse(const ns_agentAction_t myAction,
              const char** toAddr,
              const char** retAddr,
              const char** usrMesg,
              const char** newsGroup,
              const char** newsSubject,
              const char** organization,
              const char** collection,
              ESearchQueryType* searchType,
              const char** searchPattern);


/*
 * Create a "all-in-one" action. This is the backbone for all actions.
 * userAddr: Email Address of the agent user for this action
   userName - Name of the agent user for this action

   === Parts of the action for sending a mail message ===
   eMailTo - Address to which mail is to be sent on agent triggering
   retAddr - reply address for this mail message (optional)
   mailAndNewsMessage - Contents of the email message and/or the message to be
						psoted to a newsgroup

   === Parts of the action for sending a newsgroup message ===
   newsGroup - name of the newsgroup to send message to (e.g., rec.humor)
   subject   - subject of the newsgroup message

   === Parts of the action for a HTTP GET action ===
   getFromUrl - the URL from which to do a HTTP GET (contents of this 
				URL will be included in the message sent to the user). 
				This is like a read from a file.

   === Parts of the action for a HTTP POST action ===
   postToUrl - The URL to which the postMsg will be posted when agent is 
				triggered
   postMsg - Body of the message to be posted

   === Parts of the action for a Content Store Search action ===
   queryString - The properly formatted query to be sent to the collection
   urlToScan - This is the name of the collection to search for queryString
   searchType - An enum member (eSearch_by_Mdate, eSearch_All 
                eSearch_by_MDate - Searches documents based on modification date
                eSearch_All - Searches all documents in the collection

   organization - When email is sent, this identifies the "organization" field.
                 This is usually your company name (optional)
 */


NSAPI_PUBLIC 
ns_agentAction_t ns_AgentCreateCompositeAction( 
			const char userName[],
                        const char userAddr[],
                        const char emailTo[],
                        const char returnAddr[],
                        const char mailAndNewsMessage[],
                        const char newsGroup[],
                        const char subject[],
                        const char getFromUrl[],
                        const char postToUrl[],
                        const char postMessage[],
                        const char queryString[],
                        const char collectionName[],
                        ESearchQueryType   searchType,
                        const char organization[]);



NSAPI_PUBLIC 
ns_status_t ns_AgentActionCompositeParse(const ns_agentAction_t myAction,
                             const char** emailTo,
                             const char** retAddr,
                             const char** usrMesg,
                             const char** newsGroup,
                             const char** subject,
                             const char** organization,
                             const char** getUrl,
                             const char** postUrl,
                             const char** postMsg,
                             const char** queryString,
                             const char** collectionName,
                             ESearchQueryType*   searchType);
                             
			       

/*
 * Create a composite action but leave it empty. It is expected that
 * the user will add the necessary components using the helper functions 
 * shown below
 */

NSAPI_PUBLIC 
ns_agentAction_t ns_AgentCreateEmptyCompositeAction();

NSAPI_PUBLIC 
void ns_AgentActionSetEmailAddress(ns_agentAction_t action,
									const char* emailAddr);

/*
 * utility function: Send a mail message using the MTA host of the server
 */
NSAPI_PUBLIC void SendMailMessage(
        char* const to_addr[], /* array of pointers to recipients */
        int to_count,           /* how many entries in to_addr */
        char* const cc_addr[], /* send copy of message to these addresses */
        int  cc_count,  /* how many entries in cc_addr */
        char* const bcc_addr[], /* blind carbon copy address list */
        int  bcc_count,  /* how many entries in bcc_addr */
        const char *subject,
        const char *from,       /* use this as the sender address */
        const char *reply_addr, /*  use this as the reply address */
        const char *org,        /* the originating orgranization */
        const char *err,        /* the error header, usually left empty */
        const char *x_mailer,   /* the mailer's id */
        const char *content_type, /* usually text/html */
        const char *prolog,     /* anything you want, usually left empty */
        const char *body);       /* the contents of the message */


#if defined(__cplusplus)
}
#endif

#endif /* _AGENT_C_API_H_ */
