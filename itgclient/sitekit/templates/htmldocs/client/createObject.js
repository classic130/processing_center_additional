function createJavaPluginObject()
{

    var hostName;

<!-- VSSKBEGIN Global/Mode#121 -->
<!-- VSSKEND Global/Mode#121 -->

    document.write('<OBJECT');
    document.write('    classid="clsid:8AD9C840-044E-11D1-B3E9-00805F499D93"');
    document.write('    WIDTH = 0 HEIGHT = 0 NAME = "PtaApplet"');
    document.write('    STANDBY="Please wait as the applet is being loaded..."');
    document.write('    codebase="http://java.sun.com/products/plugin/autodl/jinstall-1_4_2-windows-i586.cab#Version=1,4,2,mn">');
    document.write('    <PARAM NAME = CODE VALUE = "com.verisign.pta.applet.PtaApplet" >');
    document.write('	<PARAM NAME = CODEBASE VALUE = "' + hostName + '/VSApps/" >');
    document.write('	<PARAM NAME = ARCHIVE VALUE = vsJavaPta.jar >');
    document.write('	<PARAM NAME = NAME VALUE = "PtaApplet" >');
    document.write('	<PARAM NAME = MAYSCRIPT VALUE = true >');
    document.write('        <PARAM NAME = browser VALUE = IE>');
    document.write('    	<PARAM NAME="type" VALUE="application/x-java-applet;version=1.4.2">');
    document.write('    	<PARAM NAME="scriptable" VALUE="true">');
    document.write('');
    document.write('    <COMMENT>');
    document.write('	<EMBED');
    document.write('            type="application/x-java-applet;version=1.4.2"');
    document.write('            CODE = "com.verisign.pta.applet.PtaApplet"');
    document.write('            CODEBASE = "' + hostName + '/VSApps/"');
    document.write('            ARCHIVE = vsJavaPta.jar');
    document.write('            NAME = "PtaApplet"');
    document.write('            WIDTH = 0');
    document.write('            HEIGHT = 0');
    document.write('	    MAYSCRIPT = true');
    document.write('	    scriptable = true');
    document.write('            browser = netscape');
    document.write('	    pluginspage="http://java.sun.com/j2se/1.4.2/download.html">');
    document.write('	        <noembed>');
    document.write('		No Java 2 SDK support available for applet');
    document.write('		</noembed>');
    document.write('	</EMBED>');
    document.write('    </COMMENT>');
    document.write('</OBJECT>');
}
