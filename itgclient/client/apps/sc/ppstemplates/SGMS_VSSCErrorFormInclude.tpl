<!-- Copyright (c) 1993-2001 Tumbleweed Communications Corp. All Rights Reserved. -->
<!-- File name: SGMS_VSSCErrorFormInclude.tpl -->
<%@include file="SGMS_OnSiteHostConfig.tpl" %>
<%@include file="TW_HelperSession.tpl" %>

	  <FORM NAME=ErrorForm ACTION="<%=tw.httpGateway.getUrl("SGMS_VSSCErrorPages.tpl");%>" METHOD=POST>
	
		 <INPUT type=hidden NAME=operation VALUE="">
		 <INPUT type=hidden NAME=errortype VALUE="">
		 <INPUT type=hidden NAME=errorcode VALUE="">
	     <INPUT type=hidden NAME=appstatus VALUE="">
	     <INPUT type=hidden NAME=msgobjid VALUE=0>

	 </FORM>

	 <% if( tw.request.userAgentVendor == "microsoft" ) { %>
		<SCRIPT LANGUAGE=JavaScript>
		<!--
		  // This is a global variable that determines if 
		  // an error occured while exeuting a Method or
		  // property of an ActiveX control. It MUST be set
		  // to a non-zero value when an error is to be reported
		  // through a post/get to softbounce.exe.
		  var bErrorPresent = 0 ;

		  function SetOldHander() 
		  {
			WebBrowser1.outerHTML = "";
			window.onerror = oldHandler;
			alert("Could not stop the browser using ExecWB method of the Web Browser object...\n") ;
			return true;
		  }

		  function StopHtmlRendering() 
		  {
			var OLECMDID_STOP = 23;
			var OLECMDEXECOPT_DONTPROMPTUSER = 2;
			var OLECMDEXECOPT_PROMPTUSER = 1;
			var WebBrowser = '<OBJECT ID="WebBrowser1" WIDTH=0 HEIGHT=0 CLASSID="CLSID:8856F961-340A-11D0-A96B-00C04FD705A2"></OBJECT>';
			document.body.insertAdjacentHTML('beforeEnd', WebBrowser);
			oldHandler = window.onerror;
			window.onerror = SetOldHander;

			WebBrowser1.ExecWB(OLECMDID_STOP, OLECMDEXECOPT_DONTPROMPTUSER);

			WebBrowser1.outerHTML = "";
			window.onerror = oldHandler;
		  }

		  function SetErrorInfoMS(operation, errortype, errorcode,appstatus,msgobjid )
		  {
			
			document.ErrorForm.operation.value = operation ;
			document.ErrorForm.errortype.value = errortype ;
			document.ErrorForm.errorcode.value = errorcode ;
			document.ErrorForm.appstatus.value = appstatus ;
			document.ErrorForm.msgobjid.value = msgobjid  ;
			// Now stop the browser rendering.
			//StopHtmlRendering() ;
			

			document.ErrorForm.submit() ;
			bErrorPresent = 1 ;
		  }
		//-->
		</SCRIPT>


	 <% } else { %>
		<SCRIPT LANGUAGE=JavaScript>
		 <!--

		  // This is a global variable that determines if 
		  // an error occured while exeuting a Method or
		  // property of an ActiveX control. It MUST be set
		  // to a non-zero value when an error is to be reported
		  // through a post/get to softbounce.exe.
		  var bErrorPresent = 0 ;


			function SetErrorInfoNS(operation, errortype, errorcode,appstatus,msgobjid)
			{
				
				document.ErrorForm.operation.value = operation ;
				document.ErrorForm.errortype.value = errortype ;
				document.ErrorForm.errorcode.value = errorcode ;
				document.ErrorForm.appstatus.value = appstatus ;
				document.ErrorForm.msgobjid.value =	 msgobjid ;
				bErrorPresent = 1 ;
				document.ErrorForm.submit() ;
			}

		//-->
		</SCRIPT>

	 <% } %>

