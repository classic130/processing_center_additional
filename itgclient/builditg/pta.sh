#!/bin/sh
#Usage()
{
    echo "USAGE:"
    echo "./pta.sh -t<cvs-tag> -b<build dir> -d<dest-dir> -m<make> -p<package>"
}
#----Check Options
while getopts m:p:b:t: opt
do
  case $opt in
      b) export BUILDBASEDIR=$OPTARG;;
      m) export BLDOPTION=$OPTARG;MAKE=1;;
      t) export CVSTAG=$OPTARG;;
      p) export INSTALLDIR=$OPTARG;PACKAGE=1;;
      \?)
      Usage
      exit 1
  esac
done
CURRDATE=`date +%m%d%y`
export BUILDDIR=$BUILDBASEDIR/pta-$CVSTAG-$CURRDATE
mkdir -p $BUILDDIR
cd $BUILDDIR
export CDINSTALL=$INSTALLDIR-$CVSTAG-$CURRDATE/Nt/sitekit 
export ECAS_CUSTOM_CFG=$BUILDDIR/build/make/custom/WinNT.cfg

#------Checking out the componetts and build them

if [ "$MAKE" = "1" ]
then
   cvs co build/make
   cvs co -r $CVSTAG itgclient/client/apps/fet
   cvs co -r $CVSTAG itgclient/client/apps/pta
   cvs co -r $CVSTAG itgclient/server/apps/pta
   cvs co -r $CVSTAG itgclient/server/apps/cpm
   cvs co -r $CVSTAG itgclient/client/apps/exchange/activex/vsimport
   cvs co -r $CVSTAG itgclient/client/modules
   cvs co -r $CVSTAG itgclient/common
   cvs co -r $CVSTAG itgclient/sitekit
   cvs co -r $CVSTAG itgclient/thirdparty
   cvs co -r $CVSTAG itgclient/builditg
   cd $BUILDDIR/itgclient/common; gnumake $BLDOPTION > $BUILDDIR/pta-$CVSTAG-$CURRDATE.log
   cd $BUILDDIR     
         #-----Sending ot E-mail if the build Fails
     
         ERROR=`grep "Failed directory" pta-$CVSTAG-$CURRDATE.log`
         if [ "$ERROR" != "" ]
         then
             cd itgclient/builditg
             c://winnt/system32/cscript.exe mailpta.vbs -t $CVSTAG -s $CVSTAG-$CURRDATE -l $CDINSTALL -a $BUILDDIR/pta-$CVSTAG-$CURRDATE.log -e fail
             exit
         fi 
   
  cd $BUILDDIR/itgclient/client/modules; gnumake $BLDOPTION >> $BUILDDIR/pta-$CVSTAG-$CURRDATE.log
  cd $BUILDIR     
         #-----Sending ot E-mail if the build Fails
     
         ERROR=`grep "Failed directory" pta-$CVSTAG-$CURRDATE.log`
         if [ "$ERROR" != "" ]
         then
             cd itgclient/builditg
             c://winnt/system32/cscript.exe mailpta.vbs -t $CVSTAG -s $CVSTAG-$CURRDATE -l $CDINSTALL -a $BUILDDIR/pta-$CVSTAG-$CURRDATE.log -e fail
             exit
         fi 
   
  cd $BUILDDIR/itgclient/client/apps/pta; gnumake $BLDOPTION >> $BUILDDIR/pta-$CVSTAG-$CURRDATE.log
  cd $BUILDDIR
     
         #-----Sending ot E-mail if the build Fails
     
         ERROR=`grep "Failed directory" pta-$CVSTAG-$CURRDATE.log`
         if [ "$ERROR" != "" ]
         then
             cd itgclient/builditg
             c://winnt/system32/cscript.exe mailpta.vbs -t $CVSTAG -s $CVSTAG-$CURRDATE -l $CDINSTALL -a $BUILDDIR/pta-$CVSTAG-$CURRDATE.log -e fail
             exit
         fi 
   
  cd $BUILDDIR/itgclient/client/apps/exchange/activex/vsimport; gnumake $BLDOPTION >> $BUILDDIR/pta-$CVSTAG-$CURRDATE.log
  cd $BUILDDIR
     
         #-----Sending ot E-mail if the build Fails
     
         ERROR=`grep "Failed directory" pta-$CVSTAG-$CURRDATE.log`
         if [ "$ERROR" != "" ]
         then
             cd itgclient/builditg
             c://winnt/system32/cscript.exe mailpta.vbs -t $CVSTAG -s $CVSTAG-$CURRDATE -l $CDINSTALL -a $BUILDDIR/pta-$CVSTAG-$CURRDATE.log -e fail
             exit
         fi 
   
  cd $BUILDDIR/itgclient/client/apps/fet; gnumake $BLDOPTION >> $BUILDDIR/pta-$CVSTAG-$CURRDATE.log
  cd $BUILDDIR
     
         #-----Sending ot E-mail if the build Fails
     
         ERROR=`grep "Failed directory" pta-$CVSTAG-$CURRDATE.log`
         if [ "$ERROR" != "" ]
         then
             cd itgclient/builditg
             c://winnt/system32/cscript.exe mailpta.vbs -t $CVSTAG -s $CVSTAG-$CURRDATE -l $CDINSTALL -a $BUILDDIR/pta-$CVSTAG-$CURRDATE.log -e fail
             exit
         fi 
   
  cd $BUILDDIR/itgclient/server/apps/cpm; gnumake $BLDOPTION >> $BUILDDIR/pta-$CVST-$CURRDATE.log
  cd $BUILDDIR
     
         #-----Sending ot E-mail if the build Fails
     
         ERROR=`grep "Failed directory" pta-$CVSTAG-$CURRDATE.log`
         if [ "$ERROR" != "" ]
         then
             cd itgclient/builditg
             c://winnt/system32/cscript.exe mailpta.vbs -t $CVSTAG -s $CVSTAG-$CURRDATE -l $CDINSTALL -a $BUILDDIR/pta-$CVSTAG-$CURRDATE.log -e fail
             exit
         fi 
   
  cd $BUILDDIR/itgclient/server/apps/pta; gnumake $BLDOPTION >> $BUILDDIR/pta-$CVST-$CURRDATE.log
  cd $BUILDDIR
     
         #-----Sending ot E-mail if the build Fails
     
         ERROR=`grep "Failed directory" pta-$CVSTAG-$CURRDATE.log`
         if [ "$ERROR" != "" ]
         then
             cd itgclient/builditg
             c://winnt/system32/cscript.exe mailpta.vbs -t $CVSTAG -s $CVSTAG-$CURRDATE -l $CDINSTALL -a $BUILDDIR/pta-$CVSTAG-$CURRDATE.log -e fail
             exit
         fi 
   
  cd $BUILDDIR/itgclient/sitekit; gnumake $BLDOPTION >> $BUILDDIR/pta-$CVSTAG-$CURRDATE.log
  cd $BUILDDIR
     
         #-----Sending ot E-mail if the build Fails
     
         ERROR=`grep "Failed directory" pta-$CVSTAG-$CURRDATE.log`
         if [ "$ERROR" != "" ]
         then
             cd itgclient/builditg
             c://winnt/system32/cscript.exe mailpta.vbs -t $CVSTAG -s $CVSTAG-$CURRDATE -l $CDINSTALL -a $BUILDDIR/pta-$CVSTAG-$CURRDATE.log -e fail
             exit
         fi 
   
fi

#-----Creating Packages for the above Components

if [ "$PACKAGE" = "1" ]
then
  cd $BUILDDIR
  cvs co -r $CVSTAG itgclient/packager
  cd $BUILDDIR/itgclient/packager/pta; gnumake $BLDOPTION >> $BUILDDIR/pta-$CVSTAG-$CURRDATE.log
  cd $BUILDDIR
       
           #-----Sending ot E-mail if the build Fails
       
           ERROR=`grep "Failed directory" pta-$CVSTAG-$CURRDATE.log`
           if [ "$ERROR" != "" ]
           then
               cd itgclient/builditg
               c://winnt/system32/cscript.exe mailpta.vbs -t $CVSTAG -s $CVSTAG-$CURRDATE -l $CDINSTALL -a $BUILDDIR/pta-$CVSTAG-$CURRDATE.log -e fail
               exit
         fi 
  cd $BUILDDIR/itgclient/packager/fet; gnumake $BLDOPTION >> $BUILDDIR/pta-$CVSTAG-$CURRDATE.log
  cd $BUILDDIR
       
           #-----Sending ot E-mail if the build Fails
       
           ERROR=`grep "Failed directory" pta-$CVSTAG-$CURRDATE.log`
           if [ "$ERROR" != "" ]
           then
               cd itgclient/builditg
               c://winnt/system32/cscript.exe mailpta.vbs -t $CVSTAG -s $CVSTAG-$CURRDATE -l $CDINSTALL -a $BUILDDIR/pta-$CVSTAG-$CURRDATE.log -e fail
               exit
         fi 
  cd $BUILDDIR/itgclient/packager/vsimport; gnumake $BLDOPTION >> $BUILDDIR/pta-$CVSTAG-$CURRDATE.log
  cd $BUILDDIR
       
           #-----Sending ot E-mail if the build Fails
       
           ERROR=`grep "Failed directory" pta-$CVSTAG-$CURRDATE.log`
           if [ "$ERROR" != "" ]
           then
               cd itgclient/builditg
               c://winnt/system32/cscript.exe mailpta.vbs -t $CVSTAG -s $CVSTAG-$CURRDATE -l $CDINSTALL -a $BUILDDIR/pta-$CVSTAG-$CURRDATE.log -e fail
               exit
         fi 
  cd $BUILDDIR/itgclient/packager/local-install
  cvs ci -m "new cab files for this build $CVSTAG-$CURRDATE" 
  cd $CDINSTALL
  cd ../..
  
  #----Creating WinNT Zip File
  
  wzzip -rp itgClientWinNT.zip Nt
  cd $BUILDDIR 
  cvs co -r $CVSTAG itgclient/cdimage
  cd $CDINSTALL
  cd ../..
  cp itgClientWinNT.zip $BUILDDIR/itgclient/cdimage
  cd $BUILDDIR/itgclient/cdimage
  cvs ci -m "new zip file for this build $CVSTAG-$CURRDATE"
  cd ../../
  
  #----Creating a Static Tag
  
  cvs tag -d $CVSTAG-$CURRDATE itgclient
  cvs tag $CVSTAG-$CURRDATE itgclient
  
  #----Sending E-mail once the build is successfully completed
  
  cd itgclient/builditg
  #c://winnt/system32/cscript.exe mailexternal.vbs -a $BUILDDIR/itgclient/client/apps/pta/activex/ptav3/ReleaseMinDependency/Ptav3.dll
  c://winnt/system32/cscript.exe mailpta.vbs -t $CVSTAG -s $CVSTAG-$CURRDATE -l $CDINSTALL -a $BUILDDIR/pta-$CVSTAG-$CURRDATE.log -e pass
fi
