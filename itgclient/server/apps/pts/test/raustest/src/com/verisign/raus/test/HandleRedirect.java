package com.verisign.raus.test;

import java.io.*;
import java.net.*;
import java.util.*;
import java.security.KeyStore;
import java.security.cert.*;
import javax.servlet.*;
import javax.servlet.http.*;
import com.verisign.saml.*;
import com.verisign.saml.assertions.*;
import com.verisign.saml.authorities.*;
import com.verisign.xmlsig.*;
import org.xmltrustcenter.verifier.*;

public class HandleRedirect
    extends HttpServlet
{
    public void doPost(HttpServletRequest request,
		       HttpServletResponse response)
	throws ServletException
    {
	Config cfg = Config.getInstance(request);
	HttpSession session = request.getSession();
	String PTSbase = (String) session.getAttribute("PTSbase");
	String alias = (String) session.getAttribute("alias");

	try {
	    response.setContentType("text/html");
	    PrintWriter out = new PrintWriter(response.getWriter());

	    ByteArrayOutputStream baos = new ByteArrayOutputStream();
	    PrintStream ps = new PrintStream(baos);

	    Assertion[] aa = null;
	    try {
		SOAPAssertionProviderFactory apf = new SOAPAssertionProviderFactory(new URL(PTSbase + "/SamlResponder"));
		apf.setMessageLog(ps);
		apf.setTrustVerifier(new AllPermissiveTrustVerifier());
		apf.setVerifyingKey(cfg.getVerifyingKey(alias));
		apf.setSigningKey(cfg.getSigningKey(alias));
		AssertionProvider ap = apf.newAssertionProvider();
		aa = ap.provideAssertion(request.getParameterValues("SAMLResponse"));
	    } catch(Exception ex) { ex.printStackTrace(ps); }
	    ps.flush();

	    out.print("<html><head><title>Retrieved Assertion</title></head><body><pre>");
	    out.println(HTMLEncoder.encode(new String(baos.toByteArray())));

	    if(aa != null && aa.length > 0) {

		out.println("Assertion from " + request.getParameter("PTSbase"));
		out.println(HTMLEncoder.encode(aa[0].toString()));
	    }

	    out.println("</body></html>");
	} catch(Exception ex) {
	    throw new ServletException(ex);
	}
    }
}

