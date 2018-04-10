package com.dstc.security.provider;

import java.io.IOException;
import java.io.ByteArrayOutputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.ProviderException;

import com.dstc.security.asn1.Asn1;
import com.dstc.security.asn1.Asn1Exception;
import com.dstc.security.common.OID;
import com.dstc.security.asn1.Oid;
import com.dstc.security.asn1.Explicit;
import com.dstc.security.asn1.Sequence;
import com.dstc.security.asn1.OctetString;

class KEKGenerator
{
  private Asn1 otherInfo = null;
  private Asn1 keySpecificInfo = null;
  private Asn1 suppPubInfo = null;
  private Asn1 partyAInfo = null;
  private byte[] input = null;
  private String algOid;
  private int counter = 1;
  private int kekLength;
  private MessageDigest md;

  public KEKGenerator(byte[] input, String alg, int kekLength)
  {
    this.input = input;
    this.algOid = OID.getAlgOid(alg);
    this.kekLength = kekLength;
    this.suppPubInfo = new Explicit(Asn1.TAG_CLASS_CONTEXT, 2);
    this.suppPubInfo.add(new OctetString(intToBytes(kekLength)));

    try
    {
      md = MessageDigest.getInstance("SHA");
    }
    catch (NoSuchAlgorithmException e)
    {
      throw new ProviderException(e.getMessage());
    }
  }

  public void setPartyAInfo(byte[] rand)
  {
    this.partyAInfo = new Explicit(Asn1.TAG_CLASS_CONTEXT, 0);
    this.partyAInfo.add(new OctetString(rand));
  }

  public byte[] generateKeyMaterial() throws IOException
  {
    try
    {
      int loop = (int)Math.ceil((double)kekLength/(double)160);
  
      ByteArrayOutputStream baos = new ByteArrayOutputStream();
      
      for (int i = 0; i< loop; i++)
      {
        md.update(input);
        md.update(otherInfoDER());
  
        incrementCount();
        baos.write(md.digest());
      }

      return baos.toByteArray();
    }
    catch (Asn1Exception e)
    {
      throw new RuntimeException(e.getMessage());
    }
  }

  void incrementCount()
  {
    this.counter += 1;
  }

  private byte[] otherInfoDER() 
    throws Asn1Exception, IOException
  {
    keySpecificInfo = new Sequence();
    keySpecificInfo.add(new Oid(algOid));
    keySpecificInfo.add(new OctetString(intToBytes(counter)));

    otherInfo = new Sequence();
    otherInfo.add(keySpecificInfo);
    if (partyAInfo != null)
      otherInfo.add(partyAInfo);
    otherInfo.add(this.suppPubInfo);

    return otherInfo.getEncoded();
  }
  
  private byte[] intToBytes(int num)
  {
    byte[] ret = new byte[4];

    for (int i = 0; i < 4; i++)
    {
      ret[3-i] = (byte)(num & 0xff);
      num >>>= 8;
    }
    return ret;
  }
}
