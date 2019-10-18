1. Create .java file which will have one method for each
   method and potentially two methods for each property of the
   activex control
2. use javac to create the .class file 
   E.g. -
	H:\Projects\PTA2004\PersonalCertificateAgent\plugins\NPPref\Source>javac -classp
	ath .;d:\netscape\comm\program\java\classes\java40.jar vspref.java

3. use javah to create the .h and the .c file for the java object methods and the stubs
   E.g. -
	H:\Projects\PTA2004\PersonalCertificateAgent\plugins\NPPref\Source>d:\pluginsdk\
	bin\win32\javah -jri -classpath .;d:\pluginsdk\classes\java_30.zip;d:\netscape\comm\p
	rogram\java\classes\java40.jar VSPref
	
	H:\Projects\PTA2004\PersonalCertificateAgent\plugins\NPPref\Source>d:\pluginsdk\
	bin\win32\javah -jri -stubs -classpath .;d:\pluginsdk\classes\java_30.zip;d:\netscape\comm\p
	rogram\java\classes\java40.jar VSPref

	
   Note ... VSPref is the name of the class and not the file name

4. Implement the java object methods. Use JRI_GetString etc...

