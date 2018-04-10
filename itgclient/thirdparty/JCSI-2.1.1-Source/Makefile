################################################################################
#
# File: $Id: Makefile,v 1.33.2.1 2001/12/03 07:45:05 maslen Exp $
#
# Description: Master makefile for JCSI
#
# Targets:
#   all      - makes the following targets
#     classes  - java classes
#     jars     - jar files
#     docs     - javadoc documentation
#
################################################################################

# JCSI_VERSION
#   Holds the version number, which is inserted into jcsi_*.jar
#   This must be in the three digit format x.x.x
#   It should be updated for each release.
#
JCSI_VERSION = 2.1.1

# JCSI_RELEASE
#   A convenience variable which allows the addition of a release
#   tag such as beta1.  This simply changes the directory, filenames and
#   the Javadoc titles.  It should be left commented out for a standard
#   release
#
JCSI_RELEASE = VeriSign-source

# JCSI_DEBUG
#  The debugging option for the javac compiler.  Uncomment the
#  next line to enable debugging information in the compiled
#  java classes and jars.  This is necessary when using debuggers
#  such as jdb or ddd.
#JCSI_DEBUG = -g


SUBDIR_MAKE_ARGS	= JAVA_HOME=$(JAVA_HOME) JCSI_VERSION=$(JCSI_VERSION) JCSI_RELEASE=$(JCSI_RELEASE) DEBUG=$(JCSI_DEBUG)

CLASSES			= lib/classes

all: classes jars docs

docs:
	cd src; $(MAKE) $(SUBDIR_MAKE_ARGS) javadocs

classes:
	cd src; $(MAKE) $(SUBDIR_MAKE_ARGS)

## jars: provider_jar jce_jar base_jar ssl_jar pki_jar krb_jar smime_jar
jars: provider_jar jce_jar base_jar

DO_TEMPL		= sed -e 's/@JCSI_VERSION@/$(JCSI_VERSION)/g'

TEMPLATE_DIR		= templates
END_ATTRIBUTES		= $(TEMPLATE_DIR)/blank_line

# Enable package sealing
# (disabled for now because it's not worthwhile until we're also doing signing).
#
#SEAL			= $(TEMPLATE_DIR)/seal_true

IMPORT_JCSI_BASE	= $(TEMPLATE_DIR)/import.jcsi_base $(END_ATTRIBUTES)
#
# jcsi_base has no dependencies;  everything else depends on jcsi_base
#
EXPORT_BASE	= $(TEMPLATE_DIR)/export.jcsi_base $(SEAL) $(END_ATTRIBUTES)
EXPORT_PROVIDER	= $(TEMPLATE_DIR)/export.jcsi_provider \
						   $(SEAL) $(IMPORT_JCSI_BASE)
EXPORT_JCE	= $(TEMPLATE_DIR)/export.jcsi_jce  $(SEAL) $(IMPORT_JCSI_BASE)
EXPORT_SSL	= $(TEMPLATE_DIR)/export.jcsi_ssl  $(SEAL) $(IMPORT_JCSI_BASE)
EXPORT_PKI	= $(TEMPLATE_DIR)/export.jcsi_pki  $(SEAL) $(IMPORT_JCSI_BASE)
EXPORT_KRB	= $(TEMPLATE_DIR)/export.jcsi_krb  $(SEAL) $(IMPORT_JCSI_BASE)
EXPORT_SMIME	= $(TEMPLATE_DIR)/export.jcsi_smime $(SEAL) $(IMPORT_JCSI_BASE)

JAR			= $(JAVA_HOME)/bin/jar

provider_jar:
	$(DO_TEMPL) $(EXPORT_PROVIDER) > $(CLASSES)/jcsi_provider.mf
	cd $(CLASSES); $(JAR) cfm ../jars/jcsi_provider.jar jcsi_provider.mf \
		com/dstc/security/provider

jce_jar:
	$(DO_TEMPL) $(EXPORT_JCE) > $(CLASSES)/jcsi_jce.mf
	cd $(CLASSES); $(JAR) cfm ../jars/jcsi_jce.jar jcsi_jce.mf \
		javax/crypto

base_jar:
	$(DO_TEMPL) $(EXPORT_BASE) > $(CLASSES)/jcsi_base.mf
	cd $(CLASSES); $(JAR) cfm ../jars/jcsi_base.jar jcsi_base.mf \
		com/dstc/security/common \
	  	com/dstc/security/util \
	  	com/dstc/security/x509 \
	  	com/dstc/security/asn1 \
		com/dstc/security/keymanage \
		com/dstc/security/certpath

ssl_jar:
	$(DO_TEMPL) $(EXPORT_SSL) > $(CLASSES)/jcsi_ssl.mf
	cd $(CLASSES); $(JAR) cfm ../jars/jcsi_ssl.jar jcsi_ssl.mf \
		com/dstc/security/ssl \
		javax/net \
		javax/security

smime_jar:
	$(DO_TEMPL) $(EXPORT_SMIME) > $(CLASSES)/jcsi_smime.mf
	cd $(CLASSES); $(JAR) cfm ../jars/jcsi_smime.jar jcsi_smime.mf \
	  	com/dstc/security/smime \
		com/dstc/security/cms

pki_jar:
	$(DO_TEMPL) $(EXPORT_PKI) > $(CLASSES)/jcsi_pki.mf
	cd $(CLASSES); $(JAR) cfm ../jars/jcsi_pki.jar jcsi_pki.mf \
	  	com/dstc/security/x509gen \
	  	com/dstc/security/pki

krb_jar:
	$(DO_TEMPL) $(EXPORT_KRB) > $(CLASSES)/jcsi_krb.mf
	cd $(CLASSES); $(JAR) cfm ../jars/jcsi_krb.jar jcsi_krb.mf \
		com/dstc/security/kerberos \
		org/ietf/jgss

clean:
	cd src;   $(MAKE) $(SUBDIR_MAKE_ARGS) clean
	rm  -f $(CLASSES)/*.mf
	rm  -f lib/jars/jcsi_*.jar
	rm  -f lib/jars/s_jcsi_*.jar

