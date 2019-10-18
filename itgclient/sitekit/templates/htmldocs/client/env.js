function isIEHigherVersion(){

        var browserName=navigator.appName;
        var name = navigator.userAgent;
        if(browserName == "Netscape")
        {
          if(name.indexOf("Trident") > 1)
            return true;
          else
            return false;        
        }
        else
        {
           return false;
        } 
}

function CheckIESupportedVersion1(url)
{
 if (navigator.userAgent.indexOf("NT") >= 0 && navigator.userAgent.substr(navigator.userAgent.indexOf("NT")+3, 1) >=5)
     {document.write(url)}
 else
 {
  if(url.indexOf("../client") > 1)            
     {document.write("<A HREF='../error/invalidBrowser.html'>")}
  else
     {document.write("<A HREF='error/invalidBrowser.html'>")}
 }
}

function CheckIESupportedVersion2(url)
{
 if (navigator.userAgent.indexOf("NT") >= 0 && navigator.userAgent.substr(navigator.userAgent.indexOf("NT")+3, 1) >=5)
     { self.location = url;}
 else
 {
  if(url.indexOf("../client") > 1)            
     {self.location = "../error/invalidBrowser.html";}
  else
     {self.location = "error/invalidBrowser.html";}
 }
}

