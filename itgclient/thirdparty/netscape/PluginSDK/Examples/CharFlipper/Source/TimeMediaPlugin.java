/*
	Trivial applet that displays a string - 4/96 PNL

	Important: Remember that the file name must match the public class name (eg
	public class "TrivialApplet" must be in file "TrivialApplet.java"
	(case is relevant!). 
*/
import netscape.plugin.Plugin;

class TimeMediaPlugin extends Plugin {
    public void SetSource(java.net.URL inSourceURL) {
    	SetSourceNative( inSourceURL.toString() );
    }
    public void SetSource(java.lang.String inSourceString) {
    	SetSourceNative( inSourceString );
    }
    public native void SetSourceNative( java.lang.String inSourceString );
    
    public native void Start();
//    public native void Start( int inAtFrame );    
    public native void Stop();
	public native boolean IsRunning();

	public native void Loop( boolean inLoop );
	public native boolean IsLooping();
	
	public native void SetSpeed( int inSpeed ); // speed is in 60ths of a second.
	public native int GetSpeed();
}
