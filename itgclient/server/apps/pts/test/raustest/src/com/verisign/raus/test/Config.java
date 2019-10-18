package com.verisign.raus.test;

import java.io.*;
import java.security.KeyStore;
import java.security.cert.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import com.verisign.xmlsig.*;

public class Config
{
    public static final String CONFIG = "com.verisign.raus.test.Config";
    public static final String RES_KEYSTORE = "KeyStore";
    public static final String NONE = "-none-";

    private KeyStore ks;

    private Config(HttpServletRequest request)
	throws ServletException
    {
	try {
	    InputStream kss = this.getClass().getResourceAsStream(RES_KEYSTORE);
	    if(kss == null)
		throw new ServletException("resource not found: " + RES_KEYSTORE);
	    ks = KeyStore.getInstance("JKS");
	    ks.load(kss, "password".toCharArray());
	} catch(Exception ex) {
	    throw new ServletException(ex);
	}
    }

    public static Config getInstance(HttpServletRequest request)
	throws ServletException
    {
	HttpSession session = request.getSession();
	Config cfg = (Config) session.getAttribute(CONFIG);
	if(cfg == null) {
	    synchronized(session) {
		cfg = (Config) session.getAttribute(CONFIG);
		if(cfg == null) {
		    cfg = new Config(request);
		    session.setAttribute(CONFIG, cfg);
		}
	    }
	}
	return cfg;
    }

    public String[] getKeyNames()
	throws ServletException
    {
	try {
	    Enumeration aliases = ks.aliases();
	    ArrayList l = new ArrayList();
	    l.add(NONE);
	    while(aliases.hasMoreElements()) l.add(aliases.nextElement());
	    return (String[]) l.toArray(new String[l.size()]);
	} catch(Exception ex) {
	    throw new ServletException(ex);
	}
    }

    public SigningKey getSigningKey(String alias)
	throws ServletException
    {
	if(alias.equals(NONE)) return null;
	try {
	    return SigningKeyFactory.makeSigningKey(ks.getKey(alias, "password".toCharArray()));
	} catch(Exception ex) {
	    throw new ServletException(ex);
	}
    }

    public VerifyingKey getVerifyingKey(String alias)
	throws ServletException
    {
	if(alias.equals(NONE)) return null;
	try {
	    Certificate[] chain = ks.getCertificateChain(alias);
	    X509Certificate xchain[] = new X509Certificate[chain.length];
	    System.arraycopy(chain, 0, xchain, 0, chain.length);
	    VerifyingKey vk = VerifyingKeyFactory.makeVerifyingKey(xchain);
	    return vk;
	} catch(Exception ex) {
	    throw new ServletException(ex);
	}
    }
}
