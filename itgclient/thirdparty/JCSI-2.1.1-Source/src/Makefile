JAVAC=CLASSPATH=$(CLASSPATH):.:../lib/classes \
	$(JAVA_HOME)/bin/javac $(DEBUG) -d ../lib/classes -sourcepath .

JAVAMAIL_JARS=../lib/jars/mail.jar:../lib/jars/activation.jar
JNDI_JARS=../lib/jars/jndi.jar
JAVAC_SMIME=CLASSPATH=$(CLASSPATH):.:../lib/classes:$(JAVAMAIL_JARS) \
	$(JAVA_HOME)/bin/javac $(DEBUG) -d ../lib/classes -sourcepath .
JAVAC_PKI=CLASSPATH=$(CLASSPATH):.:../lib/classes:$(JNDI_JARS) \
	$(JAVA_HOME)/bin/javac $(DEBUG) -d ../lib/classes -sourcepath .

## all: jce provider base ssl jsse pki kerberos certmanage cms smime
all: jce provider base

base: asn1 common util keymanage certpath x509

pki: x509gen pkiApi

jce:
	$(JAVAC) javax/crypto/*.java \
	javax/crypto/spec/*.java \
	javax/crypto/interfaces/*.java 

jsse:
	$(JAVAC) javax/net/*.java \
	javax/net/ssl/*.java \
	javax/security/cert/*.java

pmi: attrcert

attrcert:
	$(JAVAC) com/dstc/security/pmi/attrcert/extns/*.java \
	com/dstc/security/pmi/attrcert/atts/*.java \
	com/dstc/security/pmi/attrcert/*.java

certmanage: cmp crmf

cmp: 
	$(JAVAC) com/dstc/security/certmanage/cmp/*.java

crmf: 
	$(JAVAC) com/dstc/security/certmanage/crmf/atts/*.java \
	com/dstc/security/certmanage/crmf/*.java

x509:
	$(JAVAC) com/dstc/security/x509/*.java \
	com/dstc/security/x509/extns/*.java

x509gen:
	$(JAVAC) com/dstc/security/x509gen/*.java

pkiApi:
	$(JAVAC_PKI) com/dstc/security/pki/*.java

certpath:
	$(JAVAC) com/dstc/security/certpath/*.java

common:
	$(JAVAC) com/dstc/security/common/*.java

smime:
	$(JAVAC_SMIME) com/dstc/security/smime/*.java \
	com/dstc/security/smime/handlers/*.java

cms:
	$(JAVAC) com/dstc/security/cms/*.java \
	com/dstc/security/cms/crypto/*.java \
	com/dstc/security/cms/atts/*.java

keymanage:
	$(JAVAC) com/dstc/security/keymanage/debug/*.java \
	com/dstc/security/keymanage/util/*.java \
	com/dstc/security/keymanage/pkcs7/*.java \
	com/dstc/security/keymanage/pkcs12/bags/*.java \
	com/dstc/security/keymanage/pkcs12/*.java \
	com/dstc/security/keymanage/spi/*.java \
	com/dstc/security/keymanage/keystore/*.java \
	com/dstc/security/keymanage/*.java

util:
	$(JAVAC) com/dstc/security/util/*.java

asn1:
	$(JAVAC) com/dstc/security/asn1/*.java

provider:
	$(JAVAC) com/dstc/security/provider/*.java

ssl:
	$(JAVAC) com/dstc/security/ssl/*.java

kerberos:
	$(JAVAC) com/dstc/security/kerberos/crypto/*.java \
	com/dstc/security/kerberos/creds/*.java \
	com/dstc/security/kerberos/msg/*.java \
	com/dstc/security/kerberos/*.java \
	com/dstc/security/kerberos/gssapi/*.java \
	org/ietf/jgss/*.java
#	com/dstc/security/kerberos/provider/*.java


## STANDARD_PACKAGES =					\
## 		javax.crypto				\
## 		javax.crypto.interfaces			\
## 		javax.crypto.spec 			\
## 		javax.net				\
## 		javax.net.ssl				\
## 		javax.security.cert			\
## 		org.ietf.jgss

STANDARD_PACKAGES =					\
		javax.crypto				\
		javax.crypto.interfaces			\
		javax.crypto.spec

## DSTC_EXTERNAL_PACKAGES =						\
## 		com.dstc.security.cms			\
## 		com.dstc.security.cms.atts		\
## 		com.dstc.security.kerberos		\
## 		com.dstc.security.kerberos.creds	\
## 		com.dstc.security.kerberos.msg		\
## 		com.dstc.security.kerberos.gssapi		\
## 		com.dstc.security.keymanage 		\
## 		com.dstc.security.ssl			\
## 		com.dstc.security.pki			\
## 		com.dstc.security.smime			

# (no public APIs in JCSI provider or JCSI base)
DSTC_EXTERNAL_PACKAGES =

## DSTC_INTERNAL_PACKAGES =						\
## 		com.dstc.security.asn1			\
## 		com.dstc.security.certmanage.cmp	\
## 		com.dstc.security.certmanage.crmf	\
## 		com.dstc.security.certmanage.crmf.atts	\
## 		com.dstc.security.certpath		\
## 		com.dstc.security.cms.crypto		\
## 		com.dstc.security.common		\
## 		com.dstc.security.kerberos.crypto	\
## 		com.dstc.security.kerberos.provider	\
## 		com.dstc.security.keymanage.debug	\
## 		com.dstc.security.keymanage.keystore	\
## 		com.dstc.security.keymanage.pkcs12	\
## 		com.dstc.security.keymanage.pkcs12.bags	\
## 		com.dstc.security.keymanage.pkcs7	\
## 		com.dstc.security.keymanage.pkcs8	\
## 		com.dstc.security.keymanage.spi		\
## 		com.dstc.security.keymanage.util	\
## 		com.dstc.security.provider		\
## 		com.dstc.security.util			\
## 		com.dstc.security.x509			\
## 		com.dstc.security.x509.extns		\
## 		com.dstc.security.x509gen		\
## 		com.dstc.security.smime.handlers			

DSTC_INTERNAL_PACKAGES =						\
		com.dstc.security.asn1			\
		com.dstc.security.certpath		\
		com.dstc.security.common		\
		com.dstc.security.keymanage.debug	\
		com.dstc.security.keymanage.keystore	\
		com.dstc.security.keymanage.pkcs12	\
		com.dstc.security.keymanage.pkcs12.bags	\
		com.dstc.security.keymanage.pkcs7	\
		com.dstc.security.keymanage.spi		\
		com.dstc.security.keymanage.util	\
		com.dstc.security.provider		\
		com.dstc.security.util			\
		com.dstc.security.x509			\
		com.dstc.security.x509.extns

JAVASOFT = java.sun.com
JDK_VERSION = 1.2
JAVAMAIL_VERSION = 1.2

JAVADOC = CLASSPATH=$(CLASSPATH):$(JAVAMAIL_JARS):$(JNDI_JARS) $(JAVA_HOME)/bin/javadoc -sourcepath .		\
		-overview overview.html			\
		-use -splitindex			\
		-doctitle    "JCSI $(JCSI_VERSION) $(JCSI_RELEASE)"	\
		-windowtitle "JCSI $(JCSI_VERSION) $(JCSI_RELEASE)"	\
		-link http://$(JAVASOFT)/products/jdk/$(JDK_VERSION)/docs/api	\
##		-link http://$(JAVASOFT)/products/javamail/$(JAVAMAIL_VERSION)/docs/javadocs \
##		-link http://$(JAVASOFT)/products/javabeans/glasgow/javadocs \
##		-link http://$(JAVASOFT)/products/jndi/1.2/javadoc


javadocs_public:  
	$(JAVADOC) -d ../doc/apidocs 				\
		   -group 'Standard Packages' 'javax.*:org.*'	\
		   -group 'JCSI-Specific Packages' 'com.dstc.*'	\
		   $(STANDARD_PACKAGES) $(DSTC_EXTERNAL_PACKAGES)

javadocs:  javadocs_public

javadocs_bwos:
	$(JAVADOC) -d ../doc/apidocs 				\
		   -group 'Standard Packages' 'javax.*:org.*'	\
		   -group 'JCSI-Specific Packages' 'com.dstc.*'	\
		   $(STANDARD_PACKAGES) $(DSTC_INTERNAL_PACKAGES) $(DSTC_EXTERNAL_PACKAGES)

javadocs_old:
	$(JAVADOC) -d ../doc/apidocs javax.crypto \
	           javax.crypto.spec \
	           javax.crypto.interfaces \
	           com.dstc.security.asn1 \
	           com.dstc.security.common \
	           com.dstc.security.provider \

javadocs_w_krb:
	$(JAVADOC) -d ../doc/apidocs javax.crypto \
	           javax.crypto.spec \
	           javax.crypto.interfaces \
	           com.dstc.security.asn1 \
	           com.dstc.security.common \
	           com.dstc.security.provider \
	           com.dstc.security.kerberos \
	           com.dstc.security.kerberos.creds \
	           com.dstc.security.kerberos.crypto \
	           com.dstc.security.kerberos.msg \
	           org.ietf.jgss \
	           com.dstc.security.kerberos.gssapi \

javadocs_w_keymanage:
	$(JAVADOC) -d ../doc/apidocs javax.crypto \
	           javax.crypto.spec \
	           javax.crypto.interfaces \
	           com.dstc.security.asn1 \
	           com.dstc.security.common \
	           com.dstc.security.provider \
		   com.dstc.security.keymanage.util \
		   com.dstc.security.keymanage.pkcs7 \
		   com.dstc.security.keymanage.pkcs8 \
		   com.dstc.security.keymanage.pkcs12.bags \
		   com.dstc.security.keymanage.pkcs12 \
		   com.dstc.security.keymanage.spi \
		   com.dstc.security.keymanage.keystore \

clean: clean_classes clean_docs

clean_docs:
	rm -fr ../doc/apidocs/[a-z]*

clean_classes:
	rm -fr ../lib/classes/com
	rm -fr ../lib/classes/javax
	rm -fr ../lib/classes/org
