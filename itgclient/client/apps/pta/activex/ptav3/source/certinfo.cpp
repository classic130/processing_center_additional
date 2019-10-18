#include "stdafx.h"

#include "certinfo.h"
#include "utils.h"


CCertInfo::CCertInfo(BYTE* pbCertDerBlob, DWORD dwCertDerBlobLen)
{
	//Fill in the CERT_INFO data structure by breaking up the der encoded cert
	CBaseDERCollection cbdcCert(dwCertDerBlobLen, pbCertDerBlob);
	CBaseDERHierarchy cbdhCert(cbdcCert);
	boolInitOk = true;

	//Now start filling in the CERT_INFO by traversing the tree corresponding to the
	//cert
	DERTree* dtCertInfo = cbdhCert.m_DERTree.rightDERTree;

	//Confirm that the CertInfo is a sequence
	if(!dtCertInfo || dtCertInfo->currentBaseDER->Type != SEQUENCE)
	{
		boolInitOk = false;
	}
	else
	{
		//Obtain the version of the cert if available
		DERTree* dtVersionTag = dtCertInfo->rightDERTree;
		DERTree* dtSerNum = dtVersionTag->nextDERTree;
		if(!dtVersionTag || (dtVersionTag->currentBaseDER->Class != CONTEXT_SPECIFIC || dtVersionTag->currentBaseDER->Encoding != CONSTRUCTED
			|| dtVersionTag->currentBaseDER->TagNumber != 0))
		{
			//The version tag is absent so we fill default values
			certInfo.dwVersion = 2; //version 2
			dtSerNum = dtVersionTag;;
		}
		else
		{
			DERTree* dtVersion = dtVersionTag->rightDERTree;

			//Make sure that the derblob in the dtVersion is of type UniversalInteger
			if(!dtVersion || dtVersion->currentBaseDER->Type != UNIVERSAL_INTEGER)
			{
				boolInitOk = false;
			}
			else
			{
				CUniversalInteger* pcuiVersion = (CUniversalInteger*)dtVersion->currentBaseDER;

				//We limit this implementation to assume that the version information can fit in a DWORD
				if(!pcuiVersion || (pcuiVersion->cbData > sizeof(_DWORD)))
				{
					boolInitOk = false;
				}
				else
				{
					//Obtain the version bytes
					BYTE byteVersion[4];
					for(unsigned int i=0;i<pcuiVersion->cbData;++i)
						byteVersion[i] = pcuiVersion->pbData[i];
					for(unsigned int j=i;j<4; ++j)
						byteVersion[j] = 0x00;
					
					//Store the version in the certinfo
					certInfo.dwVersion = *((_DWORD*)byteVersion);
					dtSerNum = dtVersionTag->nextDERTree;
					
				}
			}
		}
				
	
	//Obtain the serial number of the cert

	//Make sure that the blob corresponding to dtSerNum is of type UniversalInteger
	if(!boolInitOk || !dtSerNum || dtSerNum->currentBaseDER->Type != UNIVERSAL_INTEGER)
	{
		boolInitOk = false;
	}
	else
	{
		//Store the serial number in the cert info.
		CUniversalInteger* pcuiSerNum = (CUniversalInteger*)dtSerNum->currentBaseDER;
		if(!pcuiSerNum)
		{
			boolInitOk = false;
		}
		else
			{
				certInfo.SerialNumber.cbData = pcuiSerNum->cbData;
				certInfo.SerialNumber.pbData = (_PBYTE)malloc(sizeof(BYTE) * pcuiSerNum->cbData);
				memcpy(certInfo.SerialNumber.pbData, pcuiSerNum->pbData, pcuiSerNum->cbData);

				//Obtain the signature algorithm
				DERTree* dtSigAlg = dtSerNum->nextDERTree;
				if(!dtSigAlg || dtSigAlg->currentBaseDER->Type != SEQUENCE)
				{
					boolInitOk = false;
				}
				else
				{
					//Obtain the object identifier of the signature algorithm identifier
					DERTree* dtSigAlgObjId = dtSigAlg->rightDERTree;
					if(!dtSigAlgObjId || dtSigAlgObjId->currentBaseDER->Type != OBJECT_IDENTIFIER)
					{
						boolInitOk = false;
					}
					else
					{
						//Store the object identifier in the cert info block
						CObjectIdentifier* pcobjidSigAlgObjId = (CObjectIdentifier*)dtSigAlgObjId->currentBaseDER;
						certInfo.SignatureAlgorithm.pszObjId = (LPSTR)malloc(pcobjidSigAlgObjId->cbData + 1);
						memcpy(certInfo.SignatureAlgorithm.pszObjId,pcobjidSigAlgObjId->pbData, pcobjidSigAlgObjId->cbData );
						certInfo.SignatureAlgorithm.pszObjId[pcobjidSigAlgObjId->cbData] = '\0';

						//Obtain the parameters block and store it
						DERTree* dtSigAlgParam = dtSigAlgObjId->nextDERTree;
						if(!dtSigAlgParam)
						{
							boolInitOk = false;
						}
						else
						{
							//Now store the parameter blob in the cert info
							certInfo.SignatureAlgorithm.Parameters.cbData = dtSigAlgParam->currentBaseDER->cbData + dtSigAlgParam->currentBaseDER->NumberOfLengthBytes+1;
							if(dtSigAlgParam->currentBaseDER->cbUnusedBits)
								certInfo.SignatureAlgorithm.Parameters.cbData++;
							if(!dtSigAlgParam->currentBaseDER->NumberOfLengthBytes) //In case this a null object
								certInfo.SignatureAlgorithm.Parameters.cbData++;
							certInfo.SignatureAlgorithm.Parameters.pbData = (BYTE*)malloc(certInfo.SignatureAlgorithm.Parameters.cbData);
							memcpy(certInfo.SignatureAlgorithm.Parameters.pbData, dtSigAlgParam->currentBaseDER->BaseDERBlob->pbData, certInfo.SignatureAlgorithm.Parameters.cbData);
							

							//Obtain the issuer blob
							DERTree* dtIssuerDN = dtSigAlg->nextDERTree ;
							if(!dtIssuerDN || (dtIssuerDN->currentBaseDER->Type != SEQUENCE && dtIssuerDN->currentBaseDER->Type != SET))
							{
								boolInitOk = false;
							}
							else
							{
								//Now store the issuer dn blob
								certInfo.Issuer.cbData = dtIssuerDN->currentBaseDER->cbData + dtIssuerDN->currentBaseDER->NumberOfLengthBytes + 1;
								certInfo.Issuer.pbData = (BYTE*)malloc(sizeof(BYTE)*certInfo.Issuer.cbData);
								memcpy(certInfo.Issuer.pbData, dtIssuerDN->currentBaseDER->BaseDERBlob->pbData, certInfo.Issuer.cbData);
							

								//Obtain the issue and expiration dates sequence
								DERTree* dtDates = dtIssuerDN->nextDERTree;
								if(!dtDates || dtDates->currentBaseDER->Type != SEQUENCE)
								{
									boolInitOk = false;
								}
								else
								{
									//Obtain the not before utc data
									DERTree* dtNotBefore = dtDates->rightDERTree;
									if(!dtNotBefore || dtNotBefore->currentBaseDER->Type != UTC_TIME)
									{
										boolInitOk = false;
									}
									else
									{
										//Now store the utc date in the cert info blob
										if(_UTCToFiletime(dtNotBefore->currentBaseDER->pbData,&certInfo.NotBefore)!= S_OK)
										{
											boolInitOk = false;
										}
										else
										{
											//Obtain the not after utc data
											DERTree* dtNotAfter = dtNotBefore->nextDERTree;
											if(!dtNotAfter || dtNotAfter->currentBaseDER->Type !=UTC_TIME)
											{
												boolInitOk = false;
											}
											else
											{
												//Now store the utc date in the cert info blob
												if(_UTCToFiletime(dtNotAfter->currentBaseDER->pbData,&certInfo.NotAfter)!= S_OK)
												{
													boolInitOk = false;
												}
												else
												{
													//Obtain the subject DN
													DERTree* dtSubjectDN = dtDates->nextDERTree;
													if(!dtSubjectDN || dtSubjectDN->currentBaseDER->Type != SEQUENCE)
													{
														boolInitOk = false;
													}
													else
													{
														
														certInfo.Subject.cbData = dtSubjectDN->currentBaseDER->cbData + dtSubjectDN->currentBaseDER->NumberOfLengthBytes + 1;
														certInfo.Subject.pbData = (BYTE*)malloc(sizeof(BYTE)*certInfo.Subject.cbData );
														memcpy(certInfo.Subject.pbData,dtSubjectDN->currentBaseDER->BaseDERBlob->pbData,certInfo.Subject.cbData );
													

														//Obtain the public key info
														DERTree* dtPubKeyInfo = dtSubjectDN->nextDERTree;
														if(!dtPubKeyInfo || dtPubKeyInfo->currentBaseDER->Type != SEQUENCE)
														{
															boolInitOk = false;
														}
														else
														{
															//Obtain the public key algorithm identifier and store it in certinfo
															DERTree* dtPubKeyAlgId = dtPubKeyInfo->rightDERTree;
															if(!dtPubKeyAlgId || dtPubKeyInfo->currentBaseDER->Type != SEQUENCE)
															{
																boolInitOk = false;
															}
															else
															{
																//Obtain the object identifier of the signature algorithm identifier
																DERTree* dtPubKeyAlgObjId = dtPubKeyAlgId->rightDERTree;
																if(!dtPubKeyAlgObjId || dtPubKeyAlgObjId->currentBaseDER->Type != OBJECT_IDENTIFIER)
																{
																	boolInitOk = false;
																}
																else
																{
																	//Store the object identifier in the cert info block
																	CObjectIdentifier* pcobjidPubKeyAlgObjId = (CObjectIdentifier*)dtPubKeyAlgObjId->currentBaseDER;
																	certInfo.SubjectPublicKeyInfo.Algorithm.pszObjId = (LPSTR)malloc(pcobjidPubKeyAlgObjId->cbData + 1);
																	memcpy(certInfo.SubjectPublicKeyInfo.Algorithm.pszObjId,pcobjidPubKeyAlgObjId->pbData, pcobjidPubKeyAlgObjId->cbData );
																	certInfo.SubjectPublicKeyInfo.Algorithm.pszObjId[pcobjidPubKeyAlgObjId->cbData] = '\0';

																	//Obtain the parameters block and store it
																	DERTree* dtPubKeyAlgParam = dtPubKeyAlgObjId->nextDERTree;
																	
																	if(!dtPubKeyAlgParam)
																	{
																		boolInitOk = false;
																	}
																	else
																	{	
																		certInfo.SubjectPublicKeyInfo.Algorithm.Parameters.cbData = dtPubKeyAlgParam->currentBaseDER->cbData + dtPubKeyAlgParam->currentBaseDER->NumberOfLengthBytes + 1;
																		if(dtPubKeyAlgParam->currentBaseDER->cbUnusedBits)
																			certInfo.SubjectPublicKeyInfo.Algorithm.Parameters.cbData ++;
																		if(!dtPubKeyAlgParam->currentBaseDER->NumberOfLengthBytes)  //In case this a null object
																			certInfo.SubjectPublicKeyInfo.Algorithm.Parameters.cbData ++;
																		certInfo.SubjectPublicKeyInfo.Algorithm.Parameters.pbData = (BYTE*)malloc(certInfo.SubjectPublicKeyInfo.Algorithm.Parameters.cbData);
																		memcpy(certInfo.SubjectPublicKeyInfo.Algorithm.Parameters.pbData, dtPubKeyAlgParam->currentBaseDER->BaseDERBlob->pbData, certInfo.SubjectPublicKeyInfo.Algorithm.Parameters.cbData);
									

																		//Obtain the bit string for the public key
																		DERTree* dtPubKeyBits = dtPubKeyAlgId->nextDERTree;
																		if(!dtPubKeyBits || dtPubKeyBits->currentBaseDER->Type != BIT_STRING)
																		{
																			boolInitOk = false;
																		}
																		else
																		{
																			//Store the public key bit string
																			if(dtPubKeyBits->currentBaseDER->cbData)
																			{
																				certInfo.SubjectPublicKeyInfo.PublicKey.cbData = dtPubKeyBits->currentBaseDER->cbData;
																				certInfo.SubjectPublicKeyInfo.PublicKey.cUnusedBits  = dtPubKeyBits->currentBaseDER->cbUnusedBits;
																				certInfo.SubjectPublicKeyInfo.PublicKey.pbData = (BYTE*)malloc(sizeof(BYTE)*dtPubKeyBits->currentBaseDER->cbData);
																				memcpy(certInfo.SubjectPublicKeyInfo.PublicKey.pbData, 
																					dtPubKeyBits->currentBaseDER->BaseDERBlob->pbData+(dtPubKeyBits->currentBaseDER->BaseDERBlob->cbData - certInfo.SubjectPublicKeyInfo.PublicKey.cbData), 
																					dtPubKeyBits->currentBaseDER->cbData);
																			}
																			else
																			{
																				certInfo.SubjectPublicKeyInfo.PublicKey.cbData = 0;
																				certInfo.SubjectPublicKeyInfo.PublicKey.cUnusedBits = 0;
																				certInfo.SubjectPublicKeyInfo.PublicKey.pbData  = 0;
																			}

																			certInfo.IssuerUniqueId.cbData = 0;
																			certInfo.IssuerUniqueId.cUnusedBits = 0;
																			certInfo.IssuerUniqueId.pbData = 0;

																			certInfo.SubjectUniqueId.cbData = 0;
																			certInfo.SubjectUniqueId.cUnusedBits = 0;
																			certInfo.SubjectUniqueId.pbData = 0;

																			certInfo.rgExtension = 0;
																			certInfo.cExtension = 0;

																			//Obtain the issuer unique id, subject uniqueid and extensions if available
																			
																			DERTree* dtCurrTree = dtPubKeyInfo->nextDERTree;
																			
																			while(dtCurrTree)
																			{
																				if(dtCurrTree->currentBaseDER->Class != CONTEXT_SPECIFIC
																					||dtCurrTree->currentBaseDER ->Encoding != CONSTRUCTED)
																				{
																					boolInitOk = false;
																					dtCurrTree = 0;
																				}
																				else
																				{
																					DERTree* dtExtSeq;

																					switch(dtCurrTree->currentBaseDER->TagNumber)
																					{
																					case 1 :
																						//The current tree points to an issuer unique id
																						certInfo.IssuerUniqueId.cbData = dtCurrTree->currentBaseDER->cbData 
																															+ dtCurrTree->currentBaseDER->NumberOfLengthBytes +1;
																						certInfo.IssuerUniqueId.cUnusedBits = dtCurrTree->currentBaseDER->cbUnusedBits;
																						if(certInfo.IssuerUniqueId.cUnusedBits)
																							certInfo.IssuerUniqueId.cbData ++;
																						if(!dtCurrTree->currentBaseDER->NumberOfLengthBytes) //In case of a null object
																							certInfo.IssuerUniqueId.cbData ++;
																						certInfo.IssuerUniqueId.pbData = (BYTE*)malloc(sizeof(BYTE)*certInfo.IssuerUniqueId.cbData);
																						memcpy(certInfo.IssuerUniqueId.pbData, dtCurrTree->currentBaseDER->BaseDERBlob->pbData,certInfo.IssuerUniqueId.cbData);
																						dtCurrTree=dtCurrTree->nextDERTree;
																						break;
																					case 2:
																						//The current tree points to an subject unique id
																						certInfo.SubjectUniqueId.cbData = dtCurrTree->currentBaseDER->cbData 
																															+ dtCurrTree->currentBaseDER->NumberOfLengthBytes +1;
																						certInfo.SubjectUniqueId.cUnusedBits = dtCurrTree->currentBaseDER->cbUnusedBits;
																						if(certInfo.SubjectUniqueId.cUnusedBits)
																							certInfo.SubjectUniqueId.cbData ++;
																						if(!dtCurrTree->currentBaseDER->NumberOfLengthBytes) //In case of a null object
																							certInfo.SubjectUniqueId.cbData ++;
																						certInfo.SubjectUniqueId.pbData = (BYTE*)malloc(sizeof(BYTE)*certInfo.SubjectUniqueId.cbData);
																						memcpy(certInfo.SubjectUniqueId.pbData, dtCurrTree->currentBaseDER->BaseDERBlob->pbData,certInfo.SubjectUniqueId.cbData);
																						dtCurrTree=dtCurrTree->nextDERTree;
																						break;
																					case 3:
																						//The current tree points to an extension sequence
																						dtExtSeq = dtCurrTree->rightDERTree;
																						if(!dtExtSeq || dtExtSeq->currentBaseDER->Type != SEQUENCE)
																						{
																							boolInitOk = false;
																							dtCurrTree = 0;
																						}
																						else
																						{
																							//Count the number of extension blobs
																							dtCurrTree = dtExtSeq->rightDERTree;
																							while(dtCurrTree)
																							{
																								certInfo.cExtension ++;
																								dtCurrTree=dtCurrTree->nextDERTree;
																							}

																							//allocate memory for each cert extension blob
																							certInfo.rgExtension = (PCERT_EXTENSION)malloc(sizeof(CERT_EXTENSION)*certInfo.cExtension);

																							//Fill in each extension blob
																							dtCurrTree = dtExtSeq->rightDERTree;
																							DERTree* dtExtObjId;
																							DERTree* dtExtVal;
																							int tmp;
																							for(unsigned int i=0;i<certInfo.cExtension;++i)
																							{
																								dtExtObjId = dtCurrTree->rightDERTree;

																								if(!dtExtObjId || dtExtObjId->currentBaseDER->Type != OBJECT_IDENTIFIER)
																								{
																									boolInitOk = false;
																									i = certInfo.cExtension;
																									dtCurrTree = 0;
																								}
																								else
																								{

																									//Store the object identifier in the cert info block
																									CObjectIdentifier* pcobjidExt = (CObjectIdentifier*)dtExtObjId->currentBaseDER;
																									certInfo.rgExtension[i].pszObjId = (LPSTR)malloc(pcobjidExt->cbData + 1);
																									memcpy(certInfo.rgExtension[i].pszObjId ,pcobjidExt->pbData, pcobjidExt->cbData );
																									certInfo.rgExtension[i].pszObjId[pcobjidExt->cbData] = '\0';

																									//Store the value of the extension
																									dtExtVal = dtExtObjId->nextDERTree;
																									if(!dtExtVal)
																									{
																										boolInitOk = false;
																										i = certInfo.cExtension;
																										dtCurrTree = 0;
																									}
																									else
																									{

																										certInfo.rgExtension[i].Value.cbData = dtExtVal->currentBaseDER->cbData;
																										//Calculate the number of bytes required to store the type info, the lenght info and any
																										//unused bits info - this will be used later to determine the offset into the actual data
																										//in the BaseDERBlob's pbData
																										tmp = 1 + dtExtVal->currentBaseDER->NumberOfLengthBytes; 
																										if(dtExtVal->currentBaseDER->cbUnusedBits)
																											tmp ++;
																										if(certInfo.rgExtension[i].Value.cbData)
																										{
																											certInfo.rgExtension[i].Value.pbData = (BYTE*)malloc(sizeof(BYTE)*certInfo.rgExtension[i].Value.cbData);
																											memcpy(certInfo.rgExtension[i].Value.pbData, dtExtVal->currentBaseDER->BaseDERBlob->pbData + tmp, certInfo.rgExtension[i].Value.cbData);
																										}
																										else
																										{
																											certInfo.rgExtension[i].Value.pbData = 0;
																										}

																										certInfo.rgExtension[i].fCritical = FALSE;


																										dtCurrTree = dtCurrTree->nextDERTree;
																									}
																								}

																							}
																						}
																						dtCurrTree = 0;
																						break;
																					default:
																						boolInitOk = false;
																						dtCurrTree = 0;
																						break;
																					}
																				}

																			}
																				
																			


																		}
																	}
																}
															}
														}
												
													}//This
												}
											}
										}
									}
								}

							}
						}									
						
					} //SigAlgObjId
					
				}
			}

		}
	}
	return;
}

CCertInfo::~CCertInfo()
{
	freecertinfo(&certInfo);
	return;
}

PCERT_INFO CCertInfo::GetCertInfo()
{
	PCERT_INFO pCertInfoRet;

	pCertInfoRet = (PCERT_INFO)malloc(sizeof(CERT_INFO));
	memset(pCertInfoRet,0,sizeof(CERT_INFO));

	pCertInfoRet->dwVersion = certInfo.dwVersion;
	
	pCertInfoRet->SerialNumber.cbData = certInfo.SerialNumber.cbData;
	mallocandcpy(pCertInfoRet->SerialNumber.pbData, certInfo.SerialNumber.pbData, certInfo.SerialNumber.cbData);

	mallocandcpy((BYTE*&)pCertInfoRet->SignatureAlgorithm.pszObjId, (BYTE*)certInfo.SignatureAlgorithm.pszObjId, strlen(certInfo.SignatureAlgorithm.pszObjId)+1);
	
	pCertInfoRet->SignatureAlgorithm.Parameters.cbData = certInfo.SignatureAlgorithm.Parameters.cbData;
	mallocandcpy(pCertInfoRet->SignatureAlgorithm.Parameters.pbData,certInfo.SignatureAlgorithm.Parameters.pbData, certInfo.SignatureAlgorithm.Parameters.cbData);

	pCertInfoRet->Issuer.cbData = certInfo.Issuer.cbData;
	mallocandcpy(pCertInfoRet->Issuer.pbData, certInfo.Issuer.pbData, certInfo.Issuer.cbData);
	

	pCertInfoRet->NotBefore.dwHighDateTime = certInfo.NotBefore.dwHighDateTime;
	pCertInfoRet->NotBefore.dwLowDateTime = certInfo.NotBefore.dwLowDateTime;

	pCertInfoRet->NotAfter.dwHighDateTime = certInfo.NotAfter.dwHighDateTime;
	pCertInfoRet->NotAfter.dwLowDateTime = certInfo.NotAfter.dwLowDateTime;

	pCertInfoRet->Subject.cbData = certInfo.Subject.cbData;
	mallocandcpy(pCertInfoRet->Subject.pbData,certInfo.Subject.pbData,certInfo.Subject.cbData);
	

	mallocandcpy((BYTE*&)pCertInfoRet->SubjectPublicKeyInfo.Algorithm.pszObjId,
				 (BYTE*)certInfo.SubjectPublicKeyInfo.Algorithm.pszObjId,
				 strlen(certInfo.SubjectPublicKeyInfo.Algorithm.pszObjId)+1);
	
	pCertInfoRet->SubjectPublicKeyInfo.Algorithm.Parameters.cbData = certInfo.SubjectPublicKeyInfo.Algorithm.Parameters.cbData;
	mallocandcpy(pCertInfoRet->SubjectPublicKeyInfo.Algorithm.Parameters.pbData,
				 certInfo.SubjectPublicKeyInfo.Algorithm.Parameters.pbData,
				 certInfo.SubjectPublicKeyInfo.Algorithm.Parameters.cbData);
	
	pCertInfoRet->SubjectPublicKeyInfo.PublicKey.cbData = certInfo.SubjectPublicKeyInfo.PublicKey.cbData; 
	pCertInfoRet->SubjectPublicKeyInfo.PublicKey.cUnusedBits = certInfo.SubjectPublicKeyInfo.PublicKey.cUnusedBits ;
	mallocandcpy(pCertInfoRet->SubjectPublicKeyInfo.PublicKey.pbData,
				 certInfo.SubjectPublicKeyInfo.PublicKey.pbData,
				 certInfo.SubjectPublicKeyInfo.PublicKey.cbData);
	
	pCertInfoRet->IssuerUniqueId.cbData = certInfo.IssuerUniqueId.cbData; 
	pCertInfoRet->IssuerUniqueId.cUnusedBits = certInfo.IssuerUniqueId.cUnusedBits; 
	mallocandcpy(pCertInfoRet->IssuerUniqueId.pbData,certInfo.IssuerUniqueId.pbData,
				 certInfo.IssuerUniqueId.cbData);
	

	pCertInfoRet->SubjectUniqueId.cbData = certInfo.SubjectUniqueId.cbData; 
	pCertInfoRet->SubjectUniqueId.cUnusedBits = certInfo.SubjectUniqueId.cUnusedBits; 
	mallocandcpy(pCertInfoRet->SubjectUniqueId.pbData,certInfo.SubjectUniqueId.pbData,
				 certInfo.SubjectUniqueId.cbData);
	
	pCertInfoRet->cExtension = certInfo.cExtension;
	pCertInfoRet->rgExtension = (PCERT_EXTENSION)malloc(sizeof(CERT_EXTENSION) * certInfo.cExtension );
	for(unsigned int i = 0; i<pCertInfoRet->cExtension; ++i)
	{
		pCertInfoRet->rgExtension[i].fCritical = certInfo.rgExtension[i].fCritical;
		mallocandcpy((BYTE*&)pCertInfoRet->rgExtension[i].pszObjId,
					 (BYTE*)certInfo.rgExtension[i].pszObjId,
					 strlen(certInfo.rgExtension[i].pszObjId) + 1);
		pCertInfoRet->rgExtension[i].Value.cbData = certInfo.rgExtension[i].Value.cbData;
		mallocandcpy(pCertInfoRet->rgExtension[i].Value.pbData ,
					 certInfo.rgExtension[i].Value.pbData,
					 certInfo.rgExtension[i].Value.cbData);
	}

	return (pCertInfoRet);
}

