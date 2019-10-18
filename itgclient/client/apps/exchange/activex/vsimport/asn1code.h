#ifndef _asn1code_header
#define _asn1code_header

// MessageId: CRYPT_E_OSS_ERROR
//
// MessageText:
//
//  OSS Certificate encode/decode error code base
//
//  See asn1code.h for a definition of the OSS runtime errors. The OSS
//  error values are offset by CRYPT_E_OSS_ERROR.
//
#define CRYPT_E_OSS_ERROR                _HRESULT_TYPEDEF_(0x80093000L)

//
// MessageId: OSS_MORE_BUF
//
// MessageText:
//
//  OSS ASN.1 Error: Output Buffer is too small.
//
#define OSS_MORE_BUF                     _HRESULT_TYPEDEF_(0x80093001L)

//
// MessageId: OSS_NEGATIVE_UINTEGER
//
// MessageText:
//
//  OSS ASN.1 Error: Signed integer is encoded as a unsigned integer.
//
#define OSS_NEGATIVE_UINTEGER            _HRESULT_TYPEDEF_(0x80093002L)

//
// MessageId: OSS_PDU_RANGE
//
// MessageText:
//
//  OSS ASN.1 Error: Unknown ASN.1 data type.
//
#define OSS_PDU_RANGE                    _HRESULT_TYPEDEF_(0x80093003L)

//
// MessageId: OSS_MORE_INPUT
//
// MessageText:
//
//  OSS ASN.1 Error: Output buffer is too small, the decoded data has been
truncated.
//
#define OSS_MORE_INPUT                   _HRESULT_TYPEDEF_(0x80093004L)

//
// MessageId: OSS_DATA_ERROR
//
// MessageText:
//
//  OSS ASN.1 Error: Invalid data.
//
#define OSS_DATA_ERROR                   _HRESULT_TYPEDEF_(0x80093005L)

//
// MessageId: OSS_BAD_ARG
//
// MessageText:
//
//  OSS ASN.1 Error: Invalid argument.
//
#define OSS_BAD_ARG                      _HRESULT_TYPEDEF_(0x80093006L)

//
// MessageId: OSS_BAD_VERSION
//
// MessageText:
//
//  OSS ASN.1 Error: Encode/Decode version mismatch.
//
#define OSS_BAD_VERSION                  _HRESULT_TYPEDEF_(0x80093007L)

//
// MessageId: OSS_OUT_MEMORY
//
// MessageText:
//
//  OSS ASN.1 Error: Out of memory.
//
#define OSS_OUT_MEMORY                   _HRESULT_TYPEDEF_(0x80093008L)

//
// MessageId: OSS_PDU_MISMATCH
//
// MessageText:
//
//  OSS ASN.1 Error: Encode/Decode Error.
//
#define OSS_PDU_MISMATCH                 _HRESULT_TYPEDEF_(0x80093009L)

//
// MessageId: OSS_LIMITED
//
// MessageText:
//
//  OSS ASN.1 Error: Internal Error.
//
#define OSS_LIMITED                      _HRESULT_TYPEDEF_(0x8009300AL)

//
// MessageId: OSS_BAD_PTR
//
// MessageText:
//
//  OSS ASN.1 Error: Invalid data.
//
#define OSS_BAD_PTR                      _HRESULT_TYPEDEF_(0x8009300BL)

//
// MessageId: OSS_BAD_TIME
//
// MessageText:
//
//  OSS ASN.1 Error: Invalid data.
//
#define OSS_BAD_TIME                     _HRESULT_TYPEDEF_(0x8009300CL)

//
// MessageId: OSS_INDEFINITE_NOT_SUPPORTED
//
// MessageText:
//
//  OSS ASN.1 Error: Unsupported BER indefinite-length encoding.
//
#define OSS_INDEFINITE_NOT_SUPPORTED     _HRESULT_TYPEDEF_(0x8009300DL)

//
// MessageId: OSS_MEM_ERROR
//
// MessageText:
//
//  OSS ASN.1 Error: Access violation.
//
#define OSS_MEM_ERROR                    _HRESULT_TYPEDEF_(0x8009300EL)

//
// MessageId: OSS_BAD_TABLE
//
// MessageText:
//
//  OSS ASN.1 Error: Invalid data.
//
#define OSS_BAD_TABLE                    _HRESULT_TYPEDEF_(0x8009300FL)

//
// MessageId: OSS_TOO_LONG
//
// MessageText:
//
//  OSS ASN.1 Error: Invalid data.
//
#define OSS_TOO_LONG                     _HRESULT_TYPEDEF_(0x80093010L)

//
// MessageId: OSS_CONSTRAINT_VIOLATED
//
// MessageText:
//
//  OSS ASN.1 Error: Invalid data.
//
#define OSS_CONSTRAINT_VIOLATED          _HRESULT_TYPEDEF_(0x80093011L)

//
// MessageId: OSS_FATAL_ERROR
//
// MessageText:
//
//  OSS ASN.1 Error: Internal Error.
//
#define OSS_FATAL_ERROR                  _HRESULT_TYPEDEF_(0x80093012L)

//
// MessageId: OSS_ACCESS_SERIALIZATION_ERROR
//
// MessageText:
//
//  OSS ASN.1 Error: Multi-threading conflict.
//
#define OSS_ACCESS_SERIALIZATION_ERROR   _HRESULT_TYPEDEF_(0x80093013L)

//
// MessageId: OSS_NULL_TBL
//
// MessageText:
//
//  OSS ASN.1 Error: Invalid data.
//
#define OSS_NULL_TBL                     _HRESULT_TYPEDEF_(0x80093014L)

//
// MessageId: OSS_NULL_FCN
//
// MessageText:
//
//  OSS ASN.1 Error: Invalid data.
//
#define OSS_NULL_FCN                     _HRESULT_TYPEDEF_(0x80093015L)

//
// MessageId: OSS_BAD_ENCRULES
//
// MessageText:
//
//  OSS ASN.1 Error: Invalid data.
//
#define OSS_BAD_ENCRULES                 _HRESULT_TYPEDEF_(0x80093016L)

//
// MessageId: OSS_UNAVAIL_ENCRULES
//
// MessageText:
//
//  OSS ASN.1 Error: Encode/Decode function not implemented.
//
#define OSS_UNAVAIL_ENCRULES             _HRESULT_TYPEDEF_(0x80093017L)

//
// MessageId: OSS_CANT_OPEN_TRACE_WINDOW
//
// MessageText:
//
//  OSS ASN.1 Error: Trace file error.
//
#define OSS_CANT_OPEN_TRACE_WINDOW       _HRESULT_TYPEDEF_(0x80093018L)

//
// MessageId: OSS_UNIMPLEMENTED
//
// MessageText:
//
//  OSS ASN.1 Error: Function not implemented.
//
#define OSS_UNIMPLEMENTED                _HRESULT_TYPEDEF_(0x80093019L)

//
// MessageId: OSS_OID_DLL_NOT_LINKED
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_OID_DLL_NOT_LINKED           _HRESULT_TYPEDEF_(0x8009301AL)

//
// MessageId: OSS_CANT_OPEN_TRACE_FILE
//
// MessageText:
//
//  OSS ASN.1 Error: Trace file error.
//
#define OSS_CANT_OPEN_TRACE_FILE         _HRESULT_TYPEDEF_(0x8009301BL)

//
// MessageId: OSS_TRACE_FILE_ALREADY_OPEN
//
// MessageText:
//
//  OSS ASN.1 Error: Trace file error.
//
#define OSS_TRACE_FILE_ALREADY_OPEN      _HRESULT_TYPEDEF_(0x8009301CL)

//
// MessageId: OSS_TABLE_MISMATCH
//
// MessageText:
//
//  OSS ASN.1 Error: Invalid data.
//
#define OSS_TABLE_MISMATCH               _HRESULT_TYPEDEF_(0x8009301DL)

//
// MessageId: OSS_TYPE_NOT_SUPPORTED
//
// MessageText:
//
//  OSS ASN.1 Error: Invalid data.
//
#define OSS_TYPE_NOT_SUPPORTED           _HRESULT_TYPEDEF_(0x8009301EL)

//
// MessageId: OSS_REAL_DLL_NOT_LINKED
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_REAL_DLL_NOT_LINKED          _HRESULT_TYPEDEF_(0x8009301FL)

//
// MessageId: OSS_REAL_CODE_NOT_LINKED
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_REAL_CODE_NOT_LINKED         _HRESULT_TYPEDEF_(0x80093020L)

//
// MessageId: OSS_OUT_OF_RANGE
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_OUT_OF_RANGE                 _HRESULT_TYPEDEF_(0x80093021L)

//
// MessageId: OSS_COPIER_DLL_NOT_LINKED
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_COPIER_DLL_NOT_LINKED        _HRESULT_TYPEDEF_(0x80093022L)

//
// MessageId: OSS_CONSTRAINT_DLL_NOT_LINKED
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_CONSTRAINT_DLL_NOT_LINKED    _HRESULT_TYPEDEF_(0x80093023L)

//
// MessageId: OSS_COMPARATOR_DLL_NOT_LINKED
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_COMPARATOR_DLL_NOT_LINKED    _HRESULT_TYPEDEF_(0x80093024L)

//
// MessageId: OSS_COMPARATOR_CODE_NOT_LINKED
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_COMPARATOR_CODE_NOT_LINKED   _HRESULT_TYPEDEF_(0x80093025L)

//
// MessageId: OSS_MEM_MGR_DLL_NOT_LINKED
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_MEM_MGR_DLL_NOT_LINKED       _HRESULT_TYPEDEF_(0x80093026L)

//
// MessageId: OSS_PDV_DLL_NOT_LINKED
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_PDV_DLL_NOT_LINKED           _HRESULT_TYPEDEF_(0x80093027L)

//
// MessageId: OSS_PDV_CODE_NOT_LINKED
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_PDV_CODE_NOT_LINKED          _HRESULT_TYPEDEF_(0x80093028L)

//
// MessageId: OSS_API_DLL_NOT_LINKED
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_API_DLL_NOT_LINKED           _HRESULT_TYPEDEF_(0x80093029L)

//
// MessageId: OSS_BERDER_DLL_NOT_LINKED
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_BERDER_DLL_NOT_LINKED        _HRESULT_TYPEDEF_(0x8009302AL)

//
// MessageId: OSS_PER_DLL_NOT_LINKED
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_PER_DLL_NOT_LINKED           _HRESULT_TYPEDEF_(0x8009302BL)

//
// MessageId: OSS_OPEN_TYPE_ERROR
//
// MessageText:
//
//  OSS ASN.1 Error: Program link error.
//
#define OSS_OPEN_TYPE_ERROR              _HRESULT_TYPEDEF_(0x8009302CL)

//
// MessageId: OSS_MUTEX_NOT_CREATED
//
// MessageText:
//
//  OSS ASN.1 Error: System resource error.
//
#define OSS_MUTEX_NOT_CREATED            _HRESULT_TYPEDEF_(0x8009302DL)

//
// MessageId: OSS_CANT_CLOSE_TRACE_FILE
//
// MessageText:
//
//  OSS ASN.1 Error: Trace file error.
//
#define OSS_CANT_CLOSE_TRACE_FILE        _HRESULT_TYPEDEF_(0x8009302EL)

//
// MessageId: CERTSRV_E_BAD_REQUESTSUBJECT
//
// MessageText:
//
//  The request subject name is invalid or too long.
//

#endif
