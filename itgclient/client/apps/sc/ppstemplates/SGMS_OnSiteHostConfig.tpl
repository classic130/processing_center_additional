<%
// TODO: change
var OnSiteHost = "http://jburstein-sun.verisign.com";
var VSSCErrorHost="https://jburstein-sun.verisign.com";
var HostNameSSL = "https://jburstein-sun.verisign.com";
var HostName = "http://jburstein-sun.verisign.com";
var PTALogoUrl="http://npaul-pc2.verisign.com/SGMSAppLogo.bmp";
//var CertResolveURL = "http://build.verisign.com/cgi-bin/certres.exe";
var CertResolveURL = "http://jburstein-sun.verisign.com:8080/cgi-bin/certres.new";
var PRCServer = " http://rpandrangi-test/ssc/cgi-bin/vsprs.exe";
var strClientInfo = "AAAAAAkACQByb2FtMV91cmwiAAAAaHR0cDovL3BpbG90cm9hbS52ZXJpc2lnbi5jb20vdnNybQkAcm9hbTJfdXJsIgAAAGh0dHA6Ly9waWxvdHN0b3IudmVyaXNpZ24uY29tL3Zzcm0JAHN0b3JlX3VybCIAAABodHRwOi8vcGlsb3RzdG9yLnZlcmlzaWduLmNvbS92c3JtDAByb2FtMV9wdWJrZXnAAAAAQUFBQWdLdHlFVDhoU2hqUU81VUZLSGNrRmJNTHltVXVjMnJ2UVVGaUxtZHI0WnBKY2hYTEM3VzVRaDhMWXVWUTU2OG11SW1sDQpFd3cyWUVvTFZZNXdRNUtRRTFNRlRZUlJpd1pERmpPTkVwcDdBL3JpTm1tZWdWWFhUZzAvWUgzNGZxd3hnV0dWZmo3YXpiVU4NClYvTjRQRmlIaW9YbiticXljWUxlOXpwZXloLzNtZlBOQUFBQUF3RUFBUT09DAByb2FtMl9wdWJrZXnAAAAAQUFBQWdQVXdRMVM0OWMzOVI1d0h0RnlRQVBva1pVVFdibHhGdGxIQkROb1V5L1ZWcjh1MWJCdVZ2TmFlb0VuZGt3U2ZDajBRDQppZnZBVHJEVUNiU2g5T3JQc25XaFRQK2hQTHVwMkxvR2lqNVkvTnpZektNK0NobG0xTk54R21IQjg0MEpVcTlkY2w2QmlBU1gNCjFMLyt3UHNtME1ickxrZlV1LzV5SjQ5My9LQVlwWlF2QUFBQUF3RUFBUT09BwBjb21wYW55BAAAAFNHTVMEAGRlcHQHAAAAVGVzdGluZxEAanVyaXNkaWN0aW9uX2hhc2ggAAAAZTM5NjcwMjc4NGMxMzZhODFlNzc0ZGQ4MWYxNGRkZmYMAHNpZ25pbmdfY2VydPQCAABNSUlDTVRDQ0FacWdBd0lCQWdJUUdIMjRDeVpBWWhlRWR4QWg4c2ZVZnpBTkJna3Foa2lHOXcwQkFRVUZBREE4TVJjd0ZRWURWUVFLRXc1V1pYSnBVMmxuYml3Z1NXNWpMakVoTUI4R0ExVUVBeE1ZVm1WeWFWTnBaMjRnVW05aGJXbHVaeUJTYjI5MElFTkJNQjRYRFRBd01EVXlOVEF3TURBd01Gb1hEVEExTURVeU5USXpOVGsxT1Zvd056RVhNQlVHQTFVRUNoTU9WbVZ5YVZOcFoyNHNJRWx1WXk0eEhEQWFCZ05WQkFNVEUxWmxjbWxUYVdkdUlGSnZZVzFwYm1jZ1EwRXdnWjh3RFFZSktvWklodmNOQVFFQkJRQURnWTBBTUlHSkFvR0JBSmU1QnFVdm9Fa0JnN0RJNzhGcnR5TUQyOGwyTXJ4b3piVXdLKzJBeitHNnp2YXdjL0NINmNCdGRVL1AzbDZ6R1RXbElUSVZzbDNUaGp0aEdHSGZsODc3cW1JNzhFOUdya3RDUG1kS0Q2cXR4QzdpZVFCL2NPMTl3ckUvZ3ZuZmVacC9Rek9nbzd6dUNvbmRQQ21mY29vVzlLalhUbndpdjhmeWxEVkRTdDJIQWdNQkFBR2pPVEEzTUJFR0NXQ0dTQUdHK0VJQkFRUUVBd0lCQmpBU0JnTlZIUk1CQWY4RUNEQUdBUUgvQWdFQU1BNEdBMVVkRHdFQi93UUVBd0lCQmpBTkJna3Foa2lHOXcwQkFRVUZBQU9CZ1FCUU11U0l6RnZoQ0t1WDBzbks1WmV6TVIrMzMyMEtuTzYwUFdHdm5yWkJCcnh6T2Zib0ZZQVQxQ1Z0aVVKd3BrYnZ5dlFmeTgwYW41WWdrR1N1clZtZUxGbm81dHNKaDc2RWxQcWtYdk0xeHA4Z1NyM0N0UjRpOWM3ZzZ2K3JjQUtEOGxJaTM1N3NMVzdnRmhqYTRyKzg4bFJiaEpJbUJnZUpqbmlVblNKa0NRPT0=";
var strClientInfoSig ="lMRgJHkS0iM6khDAtTNqSnziwCc0ZCkABT22N2jRBGm6AldaGur+1Ocg7juaLQO+Y52goB9XFf7CE//Ilm43t8ZT0WS9v62hAQLjxRH2qID7HcunwsePcSgbIVS9SLELKZrmrblQapB/yLEIBUQyMJHXztvqVhU5VNCWIxb+8Hw=";
var SCType = "SCTYPE - VeriSignSGMS";
var SupportFAQURL = "https://llama.slamdunknetworks.com/support/faq/";
var PRCEMailAddr = "rpandrangi23@stargazer.verisign.com";
var ComposeAppStatus = "80006001";
var DecomposeAppStatus = "80006002";
var LoginAppStatus = "80006003";
var EnrollAppStatus = "80006004";
var RevocationStatus = "80006005";
var ExpirationStatus = "80006006";
var LogoutStatus = "80006007";
var ChangePasswordStatus = "80006008";
var BrowserStatus = "80006009";
var LoginChooseTitle = "Log In";
var LoginChooseText= "Enter your password.";
var PTASupportedVer= "1025";

var AppContextName = "SGMS Demo";

var NewPasswordTitle = "Enter PrivatePath profile information";
var NewPasswordText = "Enter and confirm a password. For security reasons, VeriSign does not have any record of your password and cannot recover or change it.";
var IntroDlgText="The VeriSign Personal Trust Agent will help you create a new profile for your PrivatePath Digital ID. You use your PrivatePath ID to access the VeriSign PrivatePath service. Your profile stores and protects your PrivatePath ID and other personal information. You protect your profile with a password.";
var VSSCCertificateTimeout= "30";
var VSSCMessageTimeout= "30";
/////in MB
// maximum allowed message size (account capabilities) in MB
var MaxUploadBlobSize = "1";
if( tw.session.isLoggedIn ){
	var maxKbytePerDelivery;
	var effective = tw.session.account.effectiveCapabilities;
	var inherited = tw.session.account.inheritedCapabilities;

	if ( effective.maxKbytePerDelivery == null ) {
		maxKbytePerDelivery = (inherited.maxKbytePerDelivery != null) ? inherited.maxKbytePerDelivery : 0;
	} else if ( inherited.maxKbytePerDelivery == null ) {
		maxKbytePerDelivery = (effective.maxKbytePerDelivery != null) ? effective.maxKbytePerDelivery : 0;
	} else {
		maxKbytePerDelivery = Math.min( effective.maxKbytePerDelivery, inherited.maxKbytePerDelivery);
	}
	maxKbytePerDelivery = maxKbytePerDelivery/1024;
	if( maxKbytePerDelivery < 1 ){
		maxKbytePerDelivery = 1;
	}

	MaxUploadBlobSize = "" + maxKbytePerDelivery;
}
var MaxLimitMsg = "This message has exceeded the "+MaxUploadBlobSize +" MB limit.  To send this message, remove one or more attached files.";

var PTAWriteOkDomains = "http://jburstein-sun.verisign.com";
// TODO: change
// read some parameters from SGMS.conf
//var cfg = new SGMSConfigurator();
//var OnSiteHost = cfg.getValue("OnSiteHost");
//var CertResolveURL = cfg.getValue("CertResolveURL");
//var PRCEMailAddr = cfg.getValue("PRCEMailAddr");
//var PRCServer = cfg.getValue("PRCServer");
//var SupportFAQURL = cfg.getValue("SupportFAQURL");


%>
