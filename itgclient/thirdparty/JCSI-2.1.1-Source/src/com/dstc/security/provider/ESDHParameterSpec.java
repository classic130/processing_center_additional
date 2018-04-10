package com.dstc.security.provider;

import java.security.spec.AlgorithmParameterSpec;

public class ESDHParameterSpec implements AlgorithmParameterSpec
{

    private byte[] partyAInfo;

    public ESDHParameterSpec(byte[] pai) {

        this.partyAInfo = pai;
    }

    public byte[] getPartyAInfo() {
        
        return this.partyAInfo;
    }

    private static final boolean DUMMY = Licensed.VALID;
}

