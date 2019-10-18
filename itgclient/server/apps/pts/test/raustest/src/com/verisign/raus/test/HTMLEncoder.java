package com.verisign.raus.test;

public class HTMLEncoder
{
    public static String encode(String text)
    {
	StringBuffer sb = new StringBuffer((int)(text.length() * 1.1f));
	int l = text.length();
	for(int i = 0; i < l; i++) {
	    char ch = text.charAt(i);
	    switch(ch) {
	    case '<':
		sb.append("&lt;");
		break;
	    case '>':
		sb.append("&gt;");
		break;
	    case '&':
		sb.append("&amp;");
		break;
	    case '\"':
		sb.append("&quot;");
		break;
	    case '\'':
		sb.append("&apos;");
		break;
	    default:
		sb.append(ch);
	    }
	}
	return sb.toString();
    }
}
