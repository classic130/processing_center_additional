//Function to check whether the activex control is already installed
function checkComponent()
{
		<!-- VSSKBEGIN Apps/PTAv2/GSWAClientType#53 -->
		<!-- VSSKEND Apps/PTAv2/GSWAClientType#53 -->
		<!-- VSSKBEGIN Enrollment/CertStore#38 -->
		<!-- VSSKEND Enrollment/CertStore#38 -->
		<!-- VSSKBEGIN Global/Mode#124 -->
		<!-- VSSKEND Global/Mode#124 -->
		<!-- VSSKBEGIN Apps/GSE#76 -->
		<!-- VSSKEND Apps/GSE#76 -->
		<!-- VSSKBEGIN Apps/GSE#77 -->
		<!-- VSSKEND Apps/GSE#77 -->

		return(temp);
}

//Function to redirect the flow after checking for the presence of activex control
function check(){
	var _flag=checkComponent();
	if (_flag == 1){
		window.open("../vsapps/digitalidcenter.htm","_self");
	}
	else{	
		<!-- VSSKBEGIN Global/Mode#125 -->
		<!-- VSSKEND Global/Mode#125 -->
		
		<!-- VSSKBEGIN Enrollment/CertStore#39 -->
		<!-- VSSKEND Enrollment/CertStore#39 -->
		
		<!-- VSSKBEGIN Global/Mode#126 -->
		<!-- VSSKEND Global/Mode#126 -->
		
		<!-- VSSKBEGIN Apps/GSE#78 -->
		<!-- VSSKEND Apps/GSE#78 -->
		
		<!-- VSSKBEGIN Apps/GSE#79 -->
		<!-- VSSKEND Apps/GSE#79 -->
	}
}

