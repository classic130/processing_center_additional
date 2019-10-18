//////////////////////////////////////////////////////////////////////////// 
// 
// Copyright (C) DSTC Pty Ltd (ACN 052 372 577) 1993, 1994, 1995.
// Unpublished work.  All Rights Reserved.
// 
// The software contained on this media is the property of the
// DSTC Pty Ltd.  Use of this software is strictly in accordance
// with the license agreement in the accompanying LICENSE.DOC 
// file. If your distribution of this software does not contain 
// a LICENSE.DOC file then you have no rights to use this 
// software in any manner and should contact DSTC at the address 
// below to determine an appropriate licensing arrangement.
// 
//      DSTC Pty Ltd
//      Level 7, GP South
//      University of Queensland
//      St Lucia, 4072
//      Australia
//      Tel: +61 7 3365 4310
//      Fax: +61 7 3365 4311
//      Email: jcsi@dstc.qut.edu.au
// 
// This software is being provided "AS IS" without warranty of
// any kind.  In no event shall DSTC Pty Ltd be liable for
// damage of any kind arising out of or in connection with
// the use or performance of this software.
// 
//////////////////////////////////////////////////////////////////////////// 

package com.dstc.security.x509.extns;

//JDK1.2
import java.io.IOException;
import java.util.Iterator;

//JCSI
import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.asn1.BitString;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.Explicit;
import com.dstc.security.x509.GeneralNames;
import com.dstc.security.common.RDN;


/**
 * This is a Class representing -  DistributionPoint
 *
 * <pre>
 *     DistributionPoint ::= SEQUENCE {
 *       distributionPoint       [0]    DistributionPointName OPTIONAL,
 *       reasons                 [1]    ReasonFlags OPTIONAL,
 *       cRLIssuer               [2]    GeneralNames OPTIONAL
 *     }
 *
 *     DistributionPointName ::= CHOICE {
 *       fullName                [0]    GeneralNames,
 *       nameRelativeToCRLIssuer [1]    RelativeDistinguishedName
 *     }
 *
 *     ReasonFlags ::= BIT STRING {
 *       unused                  (0),
 *       keyCompromise           (1),
 *       cACompromise            (2),
 *       affiliationChanged      (3),
 *       superseded              (4),
 *       cessationOfOperation    (5),
 *       certificateHold         (6)
 *    }
 *
 * </pre> 
 *
 * @author Eddy Cheung
 */
public class DistributionPoint
{
  private Asn1 asn1 = null;

  //Reason Flags Constants
  public static final short UNUSED = (short) 0x8000;
  public static final short KEY_COMPROMISE = (short) 0x4000;
  public static final short CA_COMPROMISE = (short) 0x2000;
  public static final short AFFILIATION_CHANGED = (short) 0x1000;
  public static final short SUPERSEDED = (short) 0x0800;
  public static final short CESSATION_OF_OPERATION = (short) 0x0400;
  public static final short CERTIFICATE_HOLD = (short) 0x0200;

  //ASN1 tag constant for DistributionPoint
  private static final int DISTRIBUTION_POINT_NAME_TAG = 0;
  private static final int REASON_FLAGS_TAG = 1;
  private static final int CRL_ISSUER_TAG = 2;
  //ASN1 tag constant for DistributionPointName
  private static final int FULL_NAME_TAG = 0;
  private static final int NAME_REL_TO_CRL_ISSUER_TAG = 1;


  //Attributes of Dist. Pt.
  private GeneralNames fullName = null;
  private RDN nameRelativeToCRLIssuer = null;
  private short reasonFlags = (short) 0;
  private GeneralNames cRLIssuer = null;

  /**
   * Construct a DistributionPoint using,
   * FullName, ReasonFlag and CRLIssuer
   * if any value is null, it is assumed that it is absent
   **/
  /*public DistributionPoint(GeneralNames fullName, short reasonFlags, 
                           GeneralNames cRLIssuer) throws IOException
  {
    this.asn1 = new Sequence();
    Asn1 comp = null;

    //DistributionPointName
    if (fullName != null) {
      this.fullName = fullName;
      Asn1 innerComp = fullName.getAsn1();
      innerComp.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      innerComp.setTagNumber(FULL_NAME_TAG);
      comp = new Explicit(Asn1.TAG_CLASS_CONTEXT, DISTRIBUTION_POINT_NAME_TAG);
      comp.add(innerComp);
      asn1.add(comp);
    }

    //ReasonFlag
    if (reasonFlags != 0) {
      this.reasonFlags = reasonFlags;
      byte[] val = new byte[2];
      val[0] = (byte)((reasonFlags >>> 8) & 0xff);
      val[1] = (byte)(reasonFlags & 0xff);
      comp = new BitString(val);
      comp.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      comp.setTagNumber(REASON_FLAGS_TAG);
      asn1.add(comp);
    }

    //CRLIssuer
    if (cRLIssuer != null) {
      this.cRLIssuer = cRLIssuer;
      comp = cRLIssuer.getAsn1();
      comp.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      comp.setTagNumber(CRL_ISSUER_TAG);
      asn1.add(comp);    
    }
  }*/

  /**
   * Construct a DistributionPoint using,
   * nameRelative to CRLIssuer, ReasonFlag and CRLIssuer
   * if any value is null, it is assumed that it is absent
   **/
  /*public DistributionPoint(RDN relName, short reasonFlags, 
                           GeneralNames cRLIssuer) throws IOException
  {
    this.asn1 = new Sequence();
    Asn1 comp = null;

    //DistributionPointName
    if (relName != null) {
      this.nameRelativeToCRLIssuer = relName;
      Asn1 innerComp = nameRelativeToCRLIssuer.getAsn1();
      innerComp.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      innerComp.setTagNumber(NAME_REL_TO_CRL_ISSUER_TAG);
      comp = new Explicit(Asn1.TAG_CLASS_CONTEXT, DISTRIBUTION_POINT_NAME_TAG);
      comp.add(innerComp);
      asn1.add(comp);
    }
    
    //ReasonFlag
    if (reasonFlags != 0) {
      this.reasonFlags = reasonFlags;
      byte[] val = new byte[2];
      val[0] = (byte)((reasonFlags >>> 8) & 0xff);
      val[1] = (byte)(reasonFlags & 0xff);
      comp = new BitString(val);
      comp.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      comp.setTagNumber(REASON_FLAGS_TAG);
      asn1.add(comp);
    }

    //CRLIssuer
    if (cRLIssuer != null) {
      this.cRLIssuer = cRLIssuer;
      comp = cRLIssuer.getAsn1();
      comp.setTagClass(Asn1.TAG_CLASS_CONTEXT);
      comp.setTagNumber(CRL_ISSUER_TAG);
      asn1.add(comp);    
    }
  }*/

  /**
   * Construct DistributionPoint from DER encoding.
   **/
  public DistributionPoint(Asn1 asn1) throws Asn1Exception
  {
    this.asn1 = asn1;

    Iterator it = asn1.components();

    if (!it.hasNext()) {
      return;
    }
    
    Asn1 comp = (Asn1)it.next();

    //DistributionPointName
    if (comp.getTagNumber() == DISTRIBUTION_POINT_NAME_TAG) {
      Iterator innerIt = comp.components();
      if (!innerIt.hasNext()) {
        throw new Asn1Exception("Unknown DistributionPointName data structure");
      }
      Asn1 innerComp = (Asn1) innerIt.next();
      if (innerComp.getTagNumber() == FULL_NAME_TAG) {
        //Full Name
        this.fullName = new GeneralNames(innerComp);
      } else if (innerComp.getTagNumber() == NAME_REL_TO_CRL_ISSUER_TAG) {
        //Relative Name to CRL Issuer
        this.nameRelativeToCRLIssuer = new RDN(innerComp);
      } else {
        //Should never reached there!
        throw new Asn1Exception("Unknown DistributionPointName data structure");
      }
      //Assertion
      if (innerIt.hasNext()) {
        throw new Asn1Exception("Unknown DistributionPointName data structure");
      }      
      //Anymore major components?
      if (!it.hasNext()) {
        return;
      } else {
        comp = (Asn1)it.next();
      }
    }

    //Reason Flags
    if (comp.getTagNumber() == REASON_FLAGS_TAG) {
      comp.setTagClass(Asn1.TAG_CLASS_UNIVERSAL);
      comp.setTagNumber(Asn1.TAG_BITSTRING);
      comp.getEncoded();
      byte[] val = ((BitString)BitString.getAsn1(comp.getEncoded())).getBytes();
      this.reasonFlags = (short)((val[0] << 8) & 0xffff);
      if (val.length == 2) {
        this.reasonFlags |= (short)(val[1] & 0xffff);
      }

      //Anymore?
      if (!it.hasNext()) {
        return;
      } else {
        comp = (Asn1)it.next();
      }
    }
    
    //CRL Issuer
    if (comp.getTagNumber() == CRL_ISSUER_TAG) {
      this.cRLIssuer = new GeneralNames(comp);
    }      
    //Anymore?
    if (!it.hasNext()) {
      return;
    } else {
      comp = (Asn1)it.next();
    }

    //Should Never reached here
    throw new Asn1Exception("Unknown DistributionPoint data structure");

  }

  /**
   * Return the Asn1 encoding of this object
   **/
  public Asn1 getAsn1() 
  {
    return this.asn1;
  }
   
  /**
   * Return GeneralNames of the DistributionPointName
   * If this is not present, it will return null
   **/
  public GeneralNames getDistributionPointName() 
  {
    return this.fullName;
  }

  /**
   * Return Name relative to CRLIssuer of the DistributionPointName
   * If this is not present, then it will return null
   **/
  public RDN getRelativeNameToCRLIssuser() 
  {
    return this.nameRelativeToCRLIssuer;
  }

  /**
   * Return the Reason Flag 
   * if this is not present, zero will be return;
   **/
  public short getReasonFlags()
  {
    return this.reasonFlags;
  }

  /**
   * Return the CRLIssuer GeneralNames
   * If this is not present, then null will be returned
   **/
  public GeneralNames getCRLIssuer()
  {
    return this.cRLIssuer;
  }   

  /**
   * toString
   **/
  public String toString() 
  {
    StringBuffer sb = new StringBuffer();
    //DistinguishedPointName
    if (this.fullName != null) {
      sb.append("\n    Full Name: " + fullName.toString() + "\n");
    } else if (this.nameRelativeToCRLIssuer != null) {
      sb.append("\n    Name relative to CRL Issuer: " + 
                this.nameRelativeToCRLIssuer.toString() + "\n");
    }
    //Reasons Flags
    if (this.reasonFlags != 0) {
      sb.append("     Reason Flags: \n");
      if ((this.reasonFlags & UNUSED) != 0) {
        sb.append("        Unused\n");
      } 
      if ((this.reasonFlags & KEY_COMPROMISE) != 0) {
        sb.append("        Key Compromise\n");
      } 
      if ((this.reasonFlags & CA_COMPROMISE) != 0) {
        sb.append("        CA Compromise\n");
      }
      if ((this.reasonFlags & AFFILIATION_CHANGED) != 0) {
        sb.append("        Affiliation Changed\n");
      }
      if ((this.reasonFlags & SUPERSEDED) != 0) {
        sb.append("        SuperSeded\n");
      }
      if ((this.reasonFlags & CESSATION_OF_OPERATION) != 0) {
        sb.append("        Cessation of Operation\n");
      }
      if ((this.reasonFlags & CERTIFICATE_HOLD) != 0) {
        sb.append("         Certificate Hold\n");
      }
    }

    //CRL Issuer
    if (this.cRLIssuer != null) {
      sb.append("    CRL Issuer: " + cRLIssuer.toString());
    }

    return sb.toString();
  }
}
