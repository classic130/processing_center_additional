     ' Get the IIsWebService Admin Object
     Set WebServObj = GetObject("IIS://LocalHost/W3svc")

     ' Enable the AspAllowOutOfProcComponents Parameter
     WebServObj.Put "AspAllowOutOfProcComponents", True

     ' Save the changed value to the metabase
     WebServObj.SetInfo