/*************************************************************************/
/*                                                                       */
/* NameprepTest.java                                                     */
/*                                                                       */
/* (c) VeriSign Inc., 2000-2003, All rights reserved                     */
/*                                                                       */
/* @author: John Colosi                                                  */
/* @date: February, 2003                                                 */
/*                                                                       */
/*************************************************************************/

package com.vgrs.xcode.idna.test;

import java.io.*;
import java.util.*;
import com.vgrs.xcode.util.*;
import com.vgrs.xcode.idna.*;
import com.vgrs.xcode.common.*;


public class NameprepTest {

	static public Nameprep nameprep;

	static public void usage() {
		System.out.println("usage: java NameprepTest [-a] <file>");
		System.out.println(" -a => allow unassigned codepoints (disallowed by default)");
	}

	static public void main(String args[]) {
		if (args.length < 1) {usage();return;}

		int i = 0;
		try {
			if (args[0].equalsIgnoreCase("-a")) {nameprep = new Nameprep(true);i++;}
			else {nameprep = new Nameprep(false);}
		} catch (Exception x) {x.printStackTrace();}

		testExecute(new File(args[i]));
	}


	static public void testExecute(File input) {
		try {
			Iterator data = Datafile.getIterator(input);
			while (data.hasNext()) {testExecute((String)data.next());}
		} catch (Exception x) {x.printStackTrace();}
	}


	static public void testExecute(String input) throws XcodeException {
		int[] output = null;

		if (input == null) {
			Debug.pass("");
			return;
		}
		input = input.trim();

		if (input.length() == 0 || input.charAt(0) == '#') {
			Debug.pass(input);
			return;
		}

		try {output = nameprep.domainExecute(Hex.decodeInts(input));}
		catch (XcodeException x) {
			Debug.fail(input+"	ERROR:"+x.getCode()+"	"+x.getMessage());
			return;
		}

		Debug.pass(Hex.encode(output));
	}

}
