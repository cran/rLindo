/*  rLindo.c
    The R interface to LINDO API 8.0.
    This file includes all C wrapper functions for LINDO API C functions.
    Copyright (C) 2013 LINDO Systems.
*/


#include "rLindo.h"

#define INI_ERR_CODE \
PROTECT(spnErrorCode = NEW_INTEGER(1));\
nProtect += 1;\
pnErrorCode = INTEGER_POINTER(spnErrorCode);\
*pnErrorCode = LSERR_NO_ERROR;\

#define CHECK_MODEL_ERROR \
if(sModel != R_NilValue && R_ExternalPtrTag(sModel) == tagLSprob)\
{\
    prModel = (prLSmodel)R_ExternalPtrAddr(sModel);\
    if(prModel == NULL)\
    {\
        *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;\
        goto ErrorReturn;\
    }\
    pModel = prModel->pModel;\
}\
else\
{\
    *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;\
    goto ErrorReturn;\
}\

#define CHECK_ENV_ERROR \
if(sEnv != R_NilValue && R_ExternalPtrTag(sEnv) == tagLSenv)\
{\
    prEnv = (prLSenv)R_ExternalPtrAddr(sEnv);\
    if(prEnv == NULL)\
    {\
        *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;\
        goto ErrorReturn;\
    }\
    pEnv = prEnv->pEnv;\
}\
else\
{\
    *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;\
    goto ErrorReturn;\
}\

#define CHECK_SAMPLE_ERROR \
if(sSample != R_NilValue && R_ExternalPtrTag(sSample) == tagLSsample)\
{\
    prSample = (prLSsample)R_ExternalPtrAddr(sSample);\
    if(prSample == NULL)\
    {\
        *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;\
        goto ErrorReturn;\
    }\
    pSample = prSample->pSample;\
}\
else\
{\
    *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;\
    goto ErrorReturn;\
}\

#define CHECK_RG_ERROR \
if(sRG != R_NilValue && R_ExternalPtrTag(sRG) == tagLSrandGen)\
{\
    prRG = (prLSrandGen)R_ExternalPtrAddr(sRG);\
    if(prRG == NULL)\
    {\
        *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;\
        goto ErrorReturn;\
    }\
    pRG = prRG->pRG;\
}\
else\
{\
    *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;\
    goto ErrorReturn;\
}\

#define CHECK_ERRCODE \
if(*pnErrorCode != LSERR_NO_ERROR)\
{\
    goto ErrorReturn;\
}\

#define MAKE_CHAR_ARRAY(carrayname, scarrayname)\
if(scarrayname == R_NilValue)\
{\
    carrayname = NULL;\
}\
else\
{\
    carrayname = (char *) CHAR(STRING_ELT(scarrayname,0));\
}\

#define MAKE_CHAR_CHAR_ARRAY(ccarrayname,sccarrayname)\
if (sccarrayname == R_NilValue) \
{\
    ccarrayname = NULL;\
}\
else\
{\
    int k;\
    int numcn = Rf_length(sccarrayname);\
    ccarrayname = R_Calloc(numcn, char *);\
    for(k = 0; k < numcn; k++)\
    {\
        ccarrayname[k] = (char *) CHAR(STRING_ELT(sccarrayname, k));\
    }\
}\

#define MAKE_REAL_ARRAY(carrayname, scarrayname)\
if(scarrayname == R_NilValue)\
{\
    carrayname = NULL;\
}\
else\
{\
    carrayname = REAL(scarrayname);\
}\

#define MAKE_INT_ARRAY(carrayname, scarrayname)\
if(scarrayname == R_NilValue)\
{\
    carrayname = NULL;\
}\
else\
{\
    carrayname = INTEGER(scarrayname);\
}\

#define SET_UP_LIST \
PROTECT(rList = allocVector(VECSXP, nNumItems));\
PROTECT(ListNames = allocVector(STRSXP,nNumItems));\
for(nIdx = 0; nIdx < nNumItems; nIdx++)\
    SET_STRING_ELT(ListNames,nIdx,mkChar(Names[nIdx]));\
setAttrib(rList, R_NamesSymbol, ListNames);\

#define SET_PRINT_LOG(pModel,nErrorCode)\
nErrorCode = LSsetModelLogfunc(pModel,(printLOG_t)rPrintLog,NULL);\
if(nErrorCode)\
{\
    Rprintf("Failed to set printing log (error %d)\n",nErrorCode);\
    R_FlushConsole();\
}\

#define SET_PRINT_LOG_NULL(pModel,nErrorCode)\
nErrorCode = LSsetModelLogfunc(pModel,NULL,NULL);\
if(nErrorCode)\
{\
    Rprintf("Failed to set printing log (error %d)\n",nErrorCode);\
    R_FlushConsole();\
}\

#define SET_MODEL_CALLBACK(pModel,nErrorCode)\
nErrorCode = LSsetCallback(pModel,(cbFunc_t)rCallBack,NULL);\
if(nErrorCode != LSERR_NO_ERROR)\
{\
    Rprintf("Failed to set callback (error %d)\n",nErrorCode);\
    R_FlushConsole();\
}\

SEXP tagLSprob;
SEXP tagLSenv;
SEXP tagLSsample;
SEXP tagLSrandGen;

static void LS_CALLTYPE rPrintLog(pLSmodel model,
                                  char     *line,
                                  void     *notting)
{
    Rprintf("%s",line);
    R_FlushConsole();
}

int CALLBACKTYPE rCallBack(pLSmodel model,
                           int      nLocation,
                           void     *pData)
{
    R_ProcessEvents();
    return 0;
}

int  CALLBACKTYPE rMipCallBack(pLSmodel model,
                               void     *pvUserData,
                               double   dObjval,
                               double   *padPrimal)
{
    return 0;
}

/******************************************************
 * Structure Creation and Deletion Routines (5)       *
 ******************************************************/
SEXP rcLScreateEnv()
{
    int      nErrorCode = LSERR_NO_ERROR;
    char     MY_LICENSE_KEY[1024];
    pLSenv   pEnv;
    prLSenv  prEnv = NULL;
    char     pachLicPath[256];
    SEXP     sEnv = R_NilValue;

    tagLSprob = Rf_install("TYPE_LSPROB");
    tagLSenv = Rf_install("TYPE_LSENV");
    tagLSsample = Rf_install("TYPE_LSSAMP");
    tagLSrandGen = Rf_install("TYPE_LSRG");

    prEnv = (prLSenv)malloc(sizeof(rLSenv)*1);
    if(prEnv == NULL)
    {
        return R_NilValue;
    }
#ifdef __unix__
    sprintf(pachLicPath,"%s//license//lndapi80.lic",getenv("LINDOAPI_HOME"));
#else
    sprintf(pachLicPath,"%s\\license\\lndapi80.lic",getenv("LINDOAPI_HOME"));
#endif
    nErrorCode = LSloadLicenseString(pachLicPath,MY_LICENSE_KEY);

    if(nErrorCode != LSERR_NO_ERROR)
    {
        Rprintf("Failed to load license key (error %d)\n",nErrorCode);
        R_FlushConsole();
        return R_NilValue;
    }

    pEnv = LScreateEnv(&nErrorCode, MY_LICENSE_KEY);
    if(nErrorCode)
    {
        Rprintf("Failed to create enviroment object (error %d)\n",nErrorCode);
        R_FlushConsole();
        return R_NilValue;
    }

    prEnv->pEnv = pEnv;

    sEnv = R_MakeExternalPtr(prEnv,R_NilValue,R_NilValue);

    R_SetExternalPtrTag(sEnv,tagLSenv);

    return sEnv;
}

SEXP rcLScreateModel(SEXP sEnv)
{
    int       nErrorCode = LSERR_NO_ERROR;
    prLSenv   prEnv = NULL;
    pLSenv    pEnv = NULL;
    prLSmodel prModel = NULL;
    pLSmodel  pModel = NULL;
    SEXP      sModel = R_NilValue;

    if(sEnv != R_NilValue && R_ExternalPtrTag(sEnv) == tagLSenv)
    {
        prEnv = (prLSenv)R_ExternalPtrAddr(sEnv);
        if(prEnv == NULL)
        {
            nErrorCode = LSERR_ILLEGAL_NULL_POINTER;
            Rprintf("Failed to create model object (error %d)\n",nErrorCode);
            R_FlushConsole();
            return R_NilValue;
        }
        pEnv = prEnv->pEnv;
    }
    else
    {
        nErrorCode = LSERR_ILLEGAL_NULL_POINTER;
        Rprintf("Failed to create model object (error %d)\n",nErrorCode);
        R_FlushConsole();
        return R_NilValue;
    }

    prModel = (prLSmodel)malloc(sizeof(rLSmodel)*1);
    if(prModel == NULL)
    {
        return R_NilValue;
    }

    pModel = LScreateModel(pEnv,&nErrorCode);
    if(nErrorCode)
    {
        Rprintf("Failed to create model object (error %d)\n",nErrorCode);
        R_FlushConsole();
        return R_NilValue;
    }

    SET_PRINT_LOG(pModel,nErrorCode);
    if(nErrorCode)
    {
        return R_NilValue;
    }

    SET_MODEL_CALLBACK(pModel,nErrorCode);
    if(nErrorCode)
    {
        return R_NilValue;
    }

    prModel->pModel = pModel;

    sModel = R_MakeExternalPtr(prModel,R_NilValue,R_NilValue);

    R_SetExternalPtrTag(sModel,tagLSprob);

    return sModel;
}

SEXP rcLSdeleteEnv(SEXP sEnv)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    *pnErrorCode = LSdeleteEnv(&pEnv);

    prEnv->pEnv = NULL;

    R_ClearExternalPtr(sEnv);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSdeleteModel(SEXP sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSdeleteModel(&pModel);

    prModel->pModel = NULL;

    R_ClearExternalPtr(sModel);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLScopyParam(SEXP ssourceModel,
                   SEXP stargetModel,
                   SEXP smSolverType)
{
    prLSmodel prsourceModel;
    pLSmodel  sourceModel;
    prLSmodel prtargetModel;
    pLSmodel  targetModel;
    int       mSolverType = Rf_asInteger(smSolverType);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    if(ssourceModel != R_NilValue && stargetModel != R_NilValue &&
        R_ExternalPtrTag(ssourceModel) == tagLSprob && 
        R_ExternalPtrTag(stargetModel) == tagLSprob)
    {
        prsourceModel = (prLSmodel)R_ExternalPtrAddr(ssourceModel);
        prtargetModel = (prLSmodel)R_ExternalPtrAddr(stargetModel);
        sourceModel = prsourceModel->pModel;
        targetModel = prtargetModel->pModel;
    }
    else
    {
        *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;
        goto ErrorReturn;
    }

    *pnErrorCode = LScopyParam(sourceModel,targetModel,mSolverType);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

/********************************************************
 * Model I-O Routines (18)                              *
 ********************************************************/
SEXP rcLSreadMPSFile(SEXP sModel,
                     SEXP spszFname,
                     SEXP snFormat)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));
    int       nFormat = Rf_asInteger(snFormat);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSreadMPSFile(pModel,pszFname,nFormat);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteMPSFile(SEXP sModel,
                      SEXP spszFname,
                      SEXP snFormat)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));
    int       nFormat = Rf_asInteger(snFormat);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteMPSFile(pModel,pszFname,nFormat);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSreadLINDOFile(SEXP sModel,
                       SEXP spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSreadLINDOFile(pModel,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteLINDOFile(SEXP sModel,
                        SEXP spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteLINDOFile(pModel,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSreadLINDOStream(SEXP sModel,
                         SEXP spszStream,
                         SEXP snStreamLen)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszStream = (char *) CHAR(STRING_ELT(spszStream,0));
    int       nStreamLen = Rf_asInteger(snStreamLen);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSreadLINDOStream(pModel,pszStream,nStreamLen);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteLINGOFile(SEXP sModel,
                        SEXP spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteLINGOFile(pModel,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteDualMPSFile(SEXP sModel,
                          SEXP spszFname,
                          SEXP snFormat,
                          SEXP snObjSense)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));
    int       nFormat = Rf_asInteger(snFormat);
    int       nObjSense = Rf_asInteger(snObjSense);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteDualMPSFile(pModel,pszFname,nFormat,nObjSense);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteSolution(SEXP sModel,
                       SEXP spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteSolution(pModel,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteSolutionOfType(SEXP sModel,
                             SEXP spszFname,
                             SEXP snFormat)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));
    int       nFormat = Rf_asInteger(snFormat);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteSolutionOfType(pModel,pszFname,nFormat);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteIIS(SEXP sModel,
                  SEXP spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteIIS(pModel,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteIUS(SEXP sModel,
                  SEXP spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteIUS(pModel,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSreadMPIFile(SEXP sModel,
                     SEXP spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSreadMPIFile(pModel,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteMPIFile(SEXP sModel,
                      SEXP spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteMPIFile(pModel,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteWithSetsAndSC(SEXP sModel,
                            SEXP spszFname,
                            SEXP snFormat)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));
    int       nFormat = Rf_asInteger(snFormat);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteWithSetsAndSC(pModel,pszFname,nFormat);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSreadBasis(SEXP sModel,
                   SEXP spszFname,
                   SEXP snFormat)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));
    int       nFormat = Rf_asInteger(snFormat);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSreadBasis(pModel,pszFname,nFormat);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode);    
    UNPROTECT(nProtect + 2);


    return rList;
}

SEXP rcLSwriteBasis(SEXP sModel,
                    SEXP spszFname,
                    SEXP snFormat)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));
    int       nFormat = Rf_asInteger(snFormat);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteBasis(pModel,pszFname,nFormat);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode);    
    UNPROTECT(nProtect + 2);


    return rList;
}

SEXP rcLSreadLPFile(SEXP sModel,
                    SEXP spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSreadLPFile(pModel,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    
    UNPROTECT(nProtect + 2);


    return rList;
}

SEXP rcLSreadLPStream(SEXP sModel,
                      SEXP spszStream,
                      SEXP snStreamLen)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszStream = (char *) CHAR(STRING_ELT(spszStream,0));
    int       nStreamLen = Rf_asInteger(snStreamLen);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSreadLPStream(pModel,pszStream,nStreamLen);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    
    UNPROTECT(nProtect + 2);


    return rList;
}

SEXP rcLSsetPrintLogNull(SEXP sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    SET_PRINT_LOG_NULL(pModel,*pnErrorCode);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    
    UNPROTECT(nProtect + 2);


    return rList;
}

/********************************************************
 * Error Handling Routines (3)                          *
 ********************************************************/
SEXP rcLSgetErrorMessage(SEXP   sEnv,
                         SEXP   snErrorCode)
{
    prLSenv       prEnv;
    pLSenv        pEnv;
    int           nErrorCode = Rf_asInteger(snErrorCode);

    int           *pnErrorCode;
    SEXP          spnErrorCode = R_NilValue;
    char          pachMessage[LS_MAX_ERROR_MESSAGE_LENGTH];
    SEXP          spachMessage = R_NilValue;
    SEXP          rList = R_NilValue;
    char          *Names[2] = {"ErrorCode", "pachMessage"};
    SEXP          ListNames = R_NilValue;
    int           nNumItems = 2;
    int           nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    //description item
    PROTECT(spachMessage = NEW_CHARACTER(1));
    nProtect += 1;

    *pnErrorCode = LSgetErrorMessage(pEnv,nErrorCode,pachMessage);

    CHECK_ERRCODE;

    SET_STRING_ELT(spachMessage,0,mkChar(pachMessage)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spachMessage);
    }

    UNPROTECT(nProtect + 2);


    return rList;
}

SEXP rcLSgetFileError(SEXP sModel)
{
    prLSmodel     prModel;
    pLSmodel      pModel;

    int           *pnErrorCode;
    SEXP          spnErrorCode = R_NilValue;
    char          pachLinetxt[256];
    SEXP          spachLinetxt = R_NilValue;
    int           *pnLinenum;
    SEXP          spnLinenum = R_NilValue;
    SEXP          rList = R_NilValue;
    char          *Names[3] = {"ErrorCode", "pnLinenum", "pachLinetxt"};
    SEXP          ListNames = R_NilValue;
    int           nNumItems = 3;
    int           nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnLinenum = NEW_INTEGER(1));
    nProtect += 1;
    pnLinenum = INTEGER_POINTER(spnLinenum);

    //description item
    PROTECT(spachLinetxt = NEW_CHARACTER(1));
    nProtect += 1;

    *pnErrorCode = LSgetFileError(pModel,pnLinenum,pachLinetxt);

    CHECK_ERRCODE;

    SET_STRING_ELT(spachLinetxt,0,mkChar(pachLinetxt)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnLinenum);
        SET_VECTOR_ELT(rList, 2, spachLinetxt);
    }
    
    UNPROTECT(nProtect + 2);


    return rList;
}

SEXP rcLSgetErrorRowIndex(SEXP sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *piRow;
    SEXP      spiRow = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "piRow"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spiRow = NEW_INTEGER(1));
    nProtect += 1;
    piRow = INTEGER_POINTER(spiRow);

    *pnErrorCode = LSgetErrorRowIndex(pModel,piRow);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spiRow);
    }  

    UNPROTECT(nProtect + 2);

    return rList;
}

/***********************************************************
 * Routines for Setting and Retrieving Parameter Values(17)*
 ***********************************************************/
SEXP rcLSsetModelDouParameter(SEXP sModel,
                              SEXP snParameter,
                              SEXP sdValue)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nParameter = Rf_asInteger(snParameter);
    double    dValue = Rf_asReal(sdValue);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;
    
    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSsetModelDouParameter(pModel,nParameter,dValue);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetModelDouParameter(SEXP sModel,
                              SEXP snParameter)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nParameter = Rf_asInteger(snParameter);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdValue;
    SEXP      spdValue = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pdValue"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    
    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spdValue = NEW_NUMERIC(1));
    nProtect += 1;
    pdValue = NUMERIC_POINTER(spdValue);

    *pnErrorCode = LSgetModelDouParameter(pModel,nParameter,pdValue);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdValue);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetModelIntParameter(SEXP sModel,
                              SEXP snParameter,
                              SEXP snValue)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nParameter = Rf_asInteger(snParameter);
    int       nValue = Rf_asInteger(snValue);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSsetModelIntParameter(pModel,nParameter,nValue);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetModelIntParameter(SEXP sModel,
                              SEXP snParameter)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nParameter = Rf_asInteger(snParameter);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnValue;
    SEXP      spnValue = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pnValue"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnValue = NEW_INTEGER(1));
    nProtect += 1;
    pnValue = INTEGER_POINTER(spnValue);

    *pnErrorCode = LSgetModelIntParameter(pModel,nParameter,pnValue);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnValue);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSsetEnvDouParameter(SEXP sEnv,
                            SEXP snParameter,
                            SEXP sdValue)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       nParameter = Rf_asInteger(snParameter);
    double    dValue = Rf_asReal(sdValue);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;
    
    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    *pnErrorCode = LSsetEnvDouParameter(pEnv,nParameter,dValue);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetEnvDouParameter(SEXP sEnv,
                            SEXP snParameter)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       nParameter = Rf_asInteger(snParameter);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdValue;
    SEXP      spdValue = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pdValue"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    
    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    PROTECT(spdValue = NEW_NUMERIC(1));
    nProtect += 1;
    pdValue = NUMERIC_POINTER(spdValue);

    *pnErrorCode = LSgetEnvDouParameter(pEnv,nParameter,pdValue);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdValue);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetEnvIntParameter(SEXP sEnv,
                            SEXP snParameter,
                            SEXP snValue)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       nParameter = Rf_asInteger(snParameter);
    int       nValue = Rf_asInteger(snValue);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;
    
    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    *pnErrorCode = LSsetEnvIntParameter(pEnv,nParameter,nValue);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetEnvIntParameter(SEXP sEnv,
                            SEXP snParameter)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       nParameter = Rf_asInteger(snParameter);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnValue;
    SEXP      spnValue = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pnValue"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    PROTECT(spnValue = NEW_INTEGER(1));
    nProtect += 1;
    pnValue = INTEGER_POINTER(spnValue);

    *pnErrorCode = LSgetEnvIntParameter(pEnv,nParameter,pnValue);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnValue);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSreadModelParameter(SEXP sModel,
                            SEXP spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;
    
    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSreadModelParameter(pModel,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSreadEnvParameter(SEXP sEnv,
                          SEXP spszFname)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;
    
    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    *pnErrorCode = LSreadEnvParameter(pEnv,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteModelParameter(SEXP sModel,
                             SEXP spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;
    
    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteModelParameter(pModel,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetIntParameterRange(SEXP sModel,
                              SEXP snParameter)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nParameter = Rf_asInteger(snParameter);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnValMIN;
    SEXP      spnValMIN = R_NilValue;
    int       *pnValMAX;
    SEXP      spnValMAX = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode", "pnValMIN", "pnValMAX"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;
    
    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnValMIN = NEW_INTEGER(1));
    nProtect += 1;
    pnValMIN = INTEGER_POINTER(spnValMIN);

    PROTECT(spnValMAX = NEW_INTEGER(1));
    nProtect += 1;
    pnValMAX = INTEGER_POINTER(spnValMAX);

    *pnErrorCode = LSgetIntParameterRange(pModel,nParameter,pnValMIN,pnValMAX);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnValMIN);
        SET_VECTOR_ELT(rList, 2, spnValMAX);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetDouParameterRange(SEXP sModel,
                              SEXP snParameter)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nParameter = Rf_asInteger(snParameter);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdValMIN;
    SEXP      spdValMIN = R_NilValue;
    double    *pdValMAX;
    SEXP      spdValMAX = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode", "pdValMIN", "pdValMAX"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;
    
    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spdValMIN = NEW_NUMERIC(1));
    nProtect += 1;
    pdValMIN = NUMERIC_POINTER(spdValMIN);

    PROTECT(spdValMAX = NEW_NUMERIC(1));
    nProtect += 1;
    pdValMAX = NUMERIC_POINTER(spdValMAX);

    *pnErrorCode = LSgetDouParameterRange(pModel,nParameter,pdValMIN,pdValMAX);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdValMIN);
        SET_VECTOR_ELT(rList, 2, spdValMAX);
    }

    UNPROTECT(nProtect + 2);
   
    return rList;
}

SEXP rcLSgetParamShortDesc(SEXP sEnv,
                           SEXP snParam)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       nParam = Rf_asInteger(snParam);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      szDescription[256];
    SEXP      sszDescription = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "szDescription"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    //description item
    PROTECT(sszDescription = NEW_CHARACTER(1));
    nProtect += 1;

    *pnErrorCode = LSgetParamShortDesc(pEnv,nParam,szDescription);

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        strcpy(szDescription,"");
    }

    CHECK_ERRCODE;

    SET_STRING_ELT(sszDescription,0,mkChar(szDescription)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, sszDescription);
    }

    UNPROTECT(nProtect + 2);
     
    return rList;
}

SEXP rcLSgetParamLongDesc(SEXP sEnv,
                          SEXP snParam)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       nParam = Rf_asInteger(snParam);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      szDescription[1024];
    SEXP      sszDescription = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "szDescription"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    //description item
    PROTECT(sszDescription = NEW_CHARACTER(1));
    nProtect += 1;

    *pnErrorCode = LSgetParamLongDesc(pEnv,nParam,szDescription);
    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        strcpy(szDescription,"");
    }

    CHECK_ERRCODE;

    SET_STRING_ELT(sszDescription,0,mkChar(szDescription)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, sszDescription);
    }

    UNPROTECT(nProtect + 2);
     
    return rList;
}

SEXP rcLSgetParamMacroName(SEXP sEnv,
                           SEXP snParam)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       nParam = Rf_asInteger(snParam);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      szParam[256];
    SEXP      sszParam = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "szParam"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    //description item
    PROTECT(sszParam = NEW_CHARACTER(1));
    nProtect += 1;

    *pnErrorCode = LSgetParamMacroName(pEnv,nParam,szParam);
    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        strcpy(szParam,"");
    }

    CHECK_ERRCODE;

    SET_STRING_ELT(sszParam,0,mkChar(szParam)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, sszParam);
    }

    UNPROTECT(nProtect + 2);
     
    return rList;
}

SEXP rcLSgetParamMacroID(SEXP sEnv,
                         SEXP sszParam)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    char      *szParam = (char *) CHAR(STRING_ELT(sszParam,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnParamType;
    SEXP      spnParamType = R_NilValue;
    int       *pnParam;
    SEXP      spnParam = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode", "pnParamType", "pnParam"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    PROTECT(spnParamType = NEW_INTEGER(1));
    nProtect += 1;
    pnParamType = INTEGER_POINTER(spnParamType);

    PROTECT(spnParam = NEW_INTEGER(1));
    nProtect += 1;
    pnParam = INTEGER_POINTER(spnParam);

    *pnErrorCode = LSgetParamMacroID(pEnv,szParam,pnParamType,pnParam);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnParamType);
        SET_VECTOR_ELT(rList, 1, spnParam);
    }

    UNPROTECT(nProtect + 2);
   
    return rList;
}


/********************************************************
* Model Loading Routines (19)                           *
*********************************************************/
SEXP rcLSloadLPData(SEXP      sModel,
                    SEXP      snCons,
                    SEXP      snVars,
                    SEXP      snObjSense,
                    SEXP      sdObjConst,
                    SEXP      spadC,
                    SEXP      spadB,
                    SEXP      spszConTypes,
                    SEXP      snAnnz,
                    SEXP      spaiAcols,
                    SEXP      spanAcols,
                    SEXP      spadAcoef,
                    SEXP      spaiArows,
                    SEXP      spadL,
                    SEXP      spadU)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       nCons = Rf_asInteger(snCons);
    int       nVars = Rf_asInteger(snVars);
    int       nObjSense = Rf_asInteger(snObjSense);
    double    dObjConst = Rf_asReal(sdObjConst);
    double    *padC = REAL(spadC);
    double    *padB = REAL(spadB);
    char      *pszConTypes = (char *) CHAR(STRING_ELT(spszConTypes,0));
    int       nAnnz = Rf_asInteger(snAnnz);
    int       *paiAcols = INTEGER(spaiAcols);
    int       *panAcols;
    double    *padAcoef = REAL(spadAcoef);
    int       *paiArows = INTEGER(spaiArows);
    double    *padL;
    double    *padU;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    MAKE_INT_ARRAY(panAcols,spanAcols);
    MAKE_REAL_ARRAY(padL,spadL);
    MAKE_REAL_ARRAY(padU,spadU);

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadLPData(pModel,
                                nCons,
                                nVars,
                                nObjSense,
                                dObjConst,
                                padC,
                                padB,
                                pszConTypes,
                                nAnnz,
                                paiAcols,
                                panAcols,
                                padAcoef,
                                paiArows,
                                padL,
                                padU);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadQCData(SEXP      sModel,
                    SEXP      snQCnnz,
                    SEXP      spaiQCrows,
                    SEXP      spaiQCcols1,
                    SEXP      spaiQCcols2,
                    SEXP      spadQCcoef)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQCnnz = Rf_asInteger(snQCnnz);
    int       *paiQCrows = INTEGER(spaiQCrows);
    int       *paiQCcols1 = INTEGER(spaiQCcols1);
    int       *paiQCcols2 = INTEGER(spaiQCcols2);
    double    *padQCcoef = REAL(spadQCcoef);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadQCData(pModel,
                                nQCnnz,
                                paiQCrows,
                                paiQCcols1,
                                paiQCcols2,
                                padQCcoef);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadConeData(SEXP      sModel,
                      SEXP      snCone,
                      SEXP      spszConeTypes,
                      SEXP      spaiConebegcone,
                      SEXP      spaiConecols)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nCone = Rf_asInteger(snCone);
    char      *pszConeTypes = (char *) CHAR(STRING_ELT(spszConeTypes,0));
    int       *paiConebegcone = INTEGER(spaiConebegcone);
    int       *paiConecols = INTEGER(spaiConecols);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadConeData(pModel,
                                  nCone,
                                  pszConeTypes,
                                  paiConebegcone,
                                  paiConecols);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadSETSData(SEXP      sModel,
                      SEXP      snSETS,
                      SEXP      spszSETStype,
                      SEXP      spaiCARDnum,
                      SEXP      spaiSETSbegcol,
                      SEXP      spaiSETScols)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nSETS = Rf_asInteger(snSETS);
    char      *pszSETStype = (char *) CHAR(STRING_ELT(spszSETStype,0));
    int       *paiCARDnum = INTEGER(spaiCARDnum);
    int       *paiSETSbegcol = INTEGER(spaiSETSbegcol);
    int       *paiSETScols = INTEGER(spaiSETScols);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadSETSData(pModel,
                                  nSETS,
                                  pszSETStype,
                                  paiCARDnum,
                                  paiSETSbegcol,
                                  paiSETScols);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadSemiContData(SEXP      sModel,
                          SEXP      snSCVars,
                          SEXP      spaiVars,
                          SEXP      spadL,
                          SEXP      spadU)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nSCVars = Rf_asInteger(snSCVars);
    int       *paiVars = INTEGER(spaiVars);
    double    *padL = REAL(spadL);
    double    *padU = REAL(spadU);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadSemiContData(pModel,
                                      nSCVars,
                                      paiVars,
                                      padL,
                                      padU);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadVarType(SEXP      sModel,
                     SEXP      spszVarTypes)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszVarTypes = (char *) CHAR(STRING_ELT(spszVarTypes,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadVarType(pModel,
                                 pszVarTypes);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode);    
    UNPROTECT(nProtect + 2);


    return rList;
}

SEXP rcLSloadNameData(SEXP      sModel,
                      SEXP      spszTitle,
                      SEXP      spszObjName,
                      SEXP      spszRhsName,
                      SEXP      spszRngName,
                      SEXP      spszBndname,
                      SEXP      spaszConNames,
                      SEXP      spaszVarNames,
                      SEXP      spaszConeNames)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszTitle = NULL;
    char      *pszObjName = NULL;
    char      *pszRhsName = NULL;
    char      *pszRngName = NULL;
    char      *pszBndname = NULL;
    char      **paszConNames = NULL;
    char      **paszVarNames = NULL;
    char      **paszConeNames = NULL;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    MAKE_CHAR_ARRAY(pszTitle,spszTitle);
    MAKE_CHAR_ARRAY(pszObjName,spszObjName);
    MAKE_CHAR_ARRAY(pszRhsName,spszRhsName);
    MAKE_CHAR_ARRAY(pszRngName,spszRngName);
    MAKE_CHAR_ARRAY(pszBndname,spszBndname);
    MAKE_CHAR_CHAR_ARRAY(paszConNames,spaszConNames);
    MAKE_CHAR_CHAR_ARRAY(paszVarNames,spaszVarNames);
    MAKE_CHAR_CHAR_ARRAY(paszConeNames,spaszConeNames);
    
    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadNameData(pModel,
                                  pszTitle,
                                  pszObjName,
                                  pszRhsName,
                                  pszRngName,
                                  pszBndname,
                                  paszConNames,
                                  paszVarNames,
                                  paszConeNames);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);


    return rList;
}

SEXP rcLSloadNLPData(SEXP      sModel,
                     SEXP      spaiNLPcols,
                     SEXP      spanNLPcols,
                     SEXP      spadNLPcoef,
                     SEXP      spaiNLProws,
                     SEXP      snNLPobj,
                     SEXP      spaiNLPobj,
                     SEXP      spadNLPobj)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       *paiNLPcols = INTEGER(spaiNLPcols);
    int       *panNLPcols = INTEGER(spanNLPcols);
    double    *padNLPcoef = NULL;
    int       *paiNLProws = INTEGER(spaiNLProws);
    int       nNLPobj = Rf_asInteger(snNLPobj);
    int       *paiNLPobj = INTEGER(spaiNLPobj);
    double    *padNLPobj = NULL;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    MAKE_REAL_ARRAY(padNLPcoef,spadNLPcoef);
    MAKE_REAL_ARRAY(padNLPobj,spadNLPobj);

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadNLPData(pModel,
                                 paiNLPcols,
                                 panNLPcols,
                                 padNLPcoef,
                                 paiNLProws,
                                 nNLPobj,
                                 paiNLPobj,
                                 padNLPobj);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode);   
    UNPROTECT(nProtect + 2);


    return rList;
}

SEXP rcLSloadInstruct(SEXP      sModel,
                      SEXP      snCons,
                      SEXP      snObjs,
                      SEXP      snVars,
                      SEXP      snNumbers,
                      SEXP      spanObjSense,
                      SEXP      spszConType,
                      SEXP      spszVarType,
                      SEXP      spanInstruct,
                      SEXP      snInstruct,
                      SEXP      spaiVars,
                      SEXP      spadNumVal,
                      SEXP      spadVarVal,
                      SEXP      spaiObjBeg,
                      SEXP      spanObjLen,
                      SEXP      spaiConBeg,
                      SEXP      spanConLen,
                      SEXP      spadLB,
                      SEXP      spadUB)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nCons = Rf_asInteger(snCons);
    int       nObjs = Rf_asInteger(snObjs);
    int       nVars = Rf_asInteger(snVars);
    int       nNumbers = Rf_asInteger(snNumbers);
    int       *panObjSense = INTEGER(spanObjSense);
    char      *pszConType = (char *) CHAR(STRING_ELT(spszConType,0));
    char      *pszVarType = NULL;
    int       *panInstruct = INTEGER(spanInstruct);
    int       nInstruct = Rf_asInteger(snInstruct);
    int       *paiVars = NULL;
    double    *padNumVal = REAL(spadNumVal);
    double    *padVarVal = REAL(spadVarVal);
    int       *paiObjBeg = INTEGER(spaiObjBeg);
    int       *panObjLen = INTEGER(spanObjLen);
    int       *paiConBeg = INTEGER(spaiConBeg);
    int       *panConLen = INTEGER(spanConLen);
    double    *padLB = NULL;
    double    *padUB = NULL;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    MAKE_CHAR_ARRAY(pszVarType,spszVarType);
    MAKE_INT_ARRAY(paiVars,spaiVars);
    MAKE_REAL_ARRAY(padLB,spadLB);
    MAKE_REAL_ARRAY(padUB,spadUB);

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadInstruct(pModel,
                                  nCons,
                                  nObjs,
                                  nVars,
                                  nNumbers,
                                  panObjSense,
                                  pszConType,
                                  pszVarType,
                                  panInstruct,
                                  nInstruct,
                                  paiVars,
                                  padNumVal,
                                  padVarVal,
                                  paiObjBeg,
                                  panObjLen,
                                  paiConBeg,
                                  panConLen,
                                  padLB,
                                  padUB);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSaddInstruct(SEXP      sModel,
                     SEXP      snCons,
                     SEXP      snObjs,
                     SEXP      snVars,
                     SEXP      snNumbers,
                     SEXP      spanObjSense,
                     SEXP      spszConType,
                     SEXP      spszVarType,
                     SEXP      spanInstruct,
                     SEXP      snInstruct,
                     SEXP      spaiCons,
                     SEXP      spadNumVal,
                     SEXP      spadVarVal,
                     SEXP      spaiObjBeg,
                     SEXP      spanObjLen,
                     SEXP      spaiConBeg,
                     SEXP      spanConLen,
                     SEXP      spadLB,
                     SEXP      spadUB)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nCons = Rf_asInteger(snCons);
    int       nObjs = Rf_asInteger(snObjs);
    int       nVars = Rf_asInteger(snVars);
    int       nNumbers = Rf_asInteger(snNumbers);
    int       *panObjSense = INTEGER(spanObjSense);
    char      *pszConType = (char *) CHAR(STRING_ELT(spszConType,0));
    char      *pszVarType = NULL;
    int       *panInstruct = INTEGER(spanInstruct);
    int       nInstruct = Rf_asInteger(snInstruct);
    int       *paiCons = NULL;
    double    *padNumVal = REAL(spadNumVal);
    double    *padVarVal = REAL(spadVarVal);
    int       *paiObjBeg = INTEGER(spaiObjBeg);
    int       *panObjLen = INTEGER(spanObjLen);
    int       *paiConBeg = INTEGER(spaiConBeg);
    int       *panConLen = INTEGER(spanConLen);
    double    *padLB = NULL;
    double    *padUB = NULL;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    MAKE_CHAR_ARRAY(pszVarType,spszVarType);
    MAKE_INT_ARRAY(paiCons,spaiCons);
    MAKE_REAL_ARRAY(padLB,spadLB);
    MAKE_REAL_ARRAY(padUB,spadUB);

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddInstruct(pModel,
                                 nCons,
                                 nObjs,
                                 nVars,
                                 nNumbers,
                                 panObjSense,
                                 pszConType,
                                 pszVarType,
                                 panInstruct,
                                 nInstruct,
                                 paiCons,
                                 padNumVal,
                                 padVarVal,
                                 paiObjBeg,
                                 panObjLen,
                                 paiConBeg,
                                 panConLen,
                                 padLB,
                                 padUB);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadStringData(SEXP      sModel,
                        SEXP      snStrings,
                        SEXP      spaszStringData)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nStrings = Rf_asInteger(snStrings);
    char      **paszStringData = NULL;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    MAKE_CHAR_CHAR_ARRAY(paszStringData,spaszStringData);

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadStringData(pModel,
                                    nStrings,
                                    paszStringData);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadString(SEXP      sModel,
                    SEXP      spszString)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszString = (char *) CHAR(STRING_ELT(spszString,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadString(pModel,
                                pszString);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSdeleteStringData(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSdeleteStringData(pModel);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSdeleteString(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSdeleteString(pModel);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStringValue(SEXP      sModel,
                        SEXP      siString)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iString = Rf_asInteger(siString);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdValue;
    SEXP      spdValue = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pdValue"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    
    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spdValue = NEW_NUMERIC(1));
    nProtect += 1;
    pdValue = NUMERIC_POINTER(spdValue);

    *pnErrorCode = LSgetStringValue(pModel,iString,pdValue);

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        *pdValue = 0;
    }

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdValue);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetConstraintProperty(SEXP      sModel,
                               SEXP      sndxCons)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       ndxCons = Rf_asInteger(sndxCons);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnConptype;
    SEXP      spnConptype = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pnConptype"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    
    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnConptype = NEW_NUMERIC(1));
    nProtect += 1;
    pnConptype = INTEGER_POINTER(spnConptype);

    *pnErrorCode = LSgetConstraintProperty(pModel,ndxCons,pnConptype);

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        *pnConptype = 0;
    }

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnConptype);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSsetConstraintProperty(SEXP      sModel,
                               SEXP      sndxCons,
                               SEXP      snConptype)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       ndxCons = Rf_asInteger(sndxCons);
    int       nConptype = Rf_asInteger(snConptype);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSsetConstraintProperty(pModel,ndxCons,nConptype);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode);  
    UNPROTECT(nProtect + 2);


    return rList;
}

SEXP rcLSloadMultiStartSolution(SEXP      sModel,
                                SEXP      snIndex)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nIndex = Rf_asInteger(snIndex);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadMultiStartSolution(pModel,nIndex);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadGASolution(SEXP      sModel,
                        SEXP      snIndex)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nIndex = Rf_asInteger(snIndex);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadGASolution(pModel,nIndex);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

/********************************************************
* Solver Initialization Routines (9)                    *
*********************************************************/
SEXP rcLSloadBasis(SEXP      sModel,
                   SEXP      spanCstatus,
                   SEXP      spanRstatus)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       *panCstatus = INTEGER(spanCstatus);
    int       *panRstatus = INTEGER(spanRstatus);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadBasis(pModel,panCstatus,panRstatus);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadVarPriorities(SEXP      sModel,
                           SEXP      spanCprior)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       *panCprior = INTEGER(spanCprior);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadVarPriorities(pModel,panCprior);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSreadVarPriorities(SEXP      sModel,
                           SEXP      spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSreadVarPriorities(pModel,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadVarStartPoint(SEXP      sModel,
                           SEXP      spadPrimal)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    double    *padPrimal = REAL(spadPrimal);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadVarStartPoint(pModel,padPrimal);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadVarStartPointPartial(SEXP      sModel,
                                  SEXP      snCols,
                                  SEXP      spaiCols,
                                  SEXP      spadPrimal)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nCols = Rf_asInteger(snCols);
    int       *paiCols = INTEGER(spaiCols);
    double    *padPrimal = REAL(spadPrimal);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadVarStartPointPartial(pModel,nCols,paiCols,padPrimal);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadMIPVarStartPoint(SEXP      sModel,
                              SEXP      spadPrimal)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    double    *padPrimal = REAL(spadPrimal);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadMIPVarStartPoint(pModel,padPrimal);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadMIPVarStartPointPartial(SEXP      sModel,
                                     SEXP      snCols,
                                     SEXP      spaiCols,
                                     SEXP      spaiPrimal)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nCols = Rf_asInteger(snCols);
    int       *paiCols = INTEGER(spaiCols);
    int       *paiPrimal = INTEGER(spaiPrimal);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadMIPVarStartPointPartial(pModel,nCols,paiCols,paiPrimal);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSreadVarStartPoint(SEXP      sModel,
                           SEXP      spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszFname = (char *) CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSreadVarStartPoint(pModel,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);


    return rList;
}

SEXP rcLSloadBlockStructure(SEXP      sModel,
                            SEXP      snBlock,
                            SEXP      spanRblock,
                            SEXP      spanCblock,
                            SEXP      snType)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nBlock = Rf_asInteger(snBlock);
    int       *panRblock = INTEGER(spanRblock);
    int       *panCblock = INTEGER(spanCblock);
    int       nType = Rf_asInteger(snType);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadBlockStructure(pModel,
                                        nBlock,
                                        panRblock,
                                        panCblock,
                                        nType);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);


    return rList;
}

/********************************************************
 * Optimization Routines (6)                            *
 ********************************************************/
SEXP rcLSoptimize(SEXP  sModel,
                  SEXP  snMethod)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       nMethod = Rf_asInteger(snMethod);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnStatus;
    SEXP      spnStatus = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pnStatus"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnStatus = NEW_INTEGER(1));
    nProtect += 1;
    pnStatus = INTEGER_POINTER(spnStatus);

    *pnErrorCode = LSoptimize(pModel,nMethod,pnStatus);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnStatus);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsolveMIP(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnStatus;
    SEXP      spnStatus = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pnStatus"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSsetMIPCallback(pModel,rMipCallBack,NULL);
    CHECK_ERRCODE;

    PROTECT(spnStatus = NEW_INTEGER(1));
    nProtect += 1;
    pnStatus = INTEGER_POINTER(spnStatus);

    *pnErrorCode = LSsolveMIP(pModel,pnStatus);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnStatus);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsolveGOP(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnStatus;
    SEXP      spnStatus = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pnStatus"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnStatus = NEW_INTEGER(1));
    nProtect += 1;
    pnStatus = INTEGER_POINTER(spnStatus);

    *pnErrorCode = LSsolveGOP(pModel,pnStatus);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnStatus);
    }

    UNPROTECT(nProtect + 2);
   
    return rList;
}

SEXP rcLSoptimizeQP(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnStatus;
    SEXP      spnStatus = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pnStatus"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnStatus = NEW_INTEGER(1));
    nProtect += 1;
    pnStatus = INTEGER_POINTER(spnStatus);

    *pnErrorCode = LSoptimizeQP(pModel,pnStatus);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnStatus);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLScheckConvexity(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LScheckConvexity(pModel);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsolveSBD(SEXP  sModel,
                  SEXP  snStages,
                  SEXP  spanRowStage,
                  SEXP  spanColStage)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nStages = Rf_asInteger(snStages);
    int       *panRowStage = INTEGER(spanRowStage);
    int       *panColStage = INTEGER(spanColStage);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnStatus;
    SEXP      spnStatus = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pnStatus"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnStatus = NEW_INTEGER(1));
    nProtect += 1;
    pnStatus = INTEGER_POINTER(spnStatus);

    *pnErrorCode = LSsolveSBD(pModel,
                              nStages,
                              panRowStage,
                              panColStage,
                              pnStatus);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnStatus);
    }

    UNPROTECT(nProtect + 2);
   
    return rList;
}

/********************************************************
* Solution Query Routines (15)                          *
*********************************************************/
SEXP rcLSgetIInfo(SEXP  sModel,
                  SEXP  snQuery)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnResult;
    SEXP      spnResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pnResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnResult = NEW_INTEGER(1));
    nProtect += 1;
    pnResult = INTEGER_POINTER(spnResult);

    *pnErrorCode = LSgetInfo(pModel,nQuery,pnResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnResult);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetDInfo(SEXP  sModel,
                  SEXP  snQuery)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdResult;
    SEXP      spnResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pdResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnResult = NEW_NUMERIC(1));
    nProtect += 1;
    pdResult = NUMERIC_POINTER(spnResult);

    *pnErrorCode = LSgetInfo(pModel,nQuery,pdResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnResult);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetPrimalSolution(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padPrimal;
    SEXP      spadPrimal = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "padPrimal"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadPrimal = NEW_NUMERIC(nVars));
    nProtect += 1;
    padPrimal = NUMERIC_POINTER(spadPrimal);

    *pnErrorCode = LSgetPrimalSolution(pModel,padPrimal);


ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadPrimal);
    }
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetDualSolution(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padDual;
    SEXP      spadDual = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "padDual"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_CONS,&nCons);
    CHECK_ERRCODE;

    PROTECT(spadDual = NEW_NUMERIC(nCons));
    nProtect += 1;
    padDual = NUMERIC_POINTER(spadDual);

    *pnErrorCode = LSgetDualSolution(pModel,padDual);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadDual);
    }
            
    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetReducedCosts(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padReducedCost;
    SEXP      spadReducedCost = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "padReducedCost"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadReducedCost = NEW_NUMERIC(nVars));
    nProtect += 1;
    padReducedCost = NUMERIC_POINTER(spadReducedCost);

    *pnErrorCode = LSgetReducedCosts(pModel,padReducedCost);


ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadReducedCost);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetReducedCostsCone(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padReducedCost;
    SEXP      spadReducedCost = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "padReducedCost"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadReducedCost = NEW_NUMERIC(nVars));
    nProtect += 1;
    padReducedCost = NUMERIC_POINTER(spadReducedCost);

    *pnErrorCode = LSgetReducedCostsCone(pModel,padReducedCost);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadReducedCost);
    }

    UNPROTECT(nProtect + 2);
       
    return rList;
}

SEXP rcLSgetSlacks(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padSlack;
    SEXP      spadSlack = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "padSlack"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_CONS,&nCons);
    CHECK_ERRCODE;

    PROTECT(spadSlack = NEW_NUMERIC(nCons));
    nProtect += 1;
    padSlack = NUMERIC_POINTER(spadSlack);

    *pnErrorCode = LSgetDualSolution(pModel,padSlack);
    

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadSlack);
    }

    UNPROTECT(nProtect + 2);
        
    return rList;
}

SEXP rcLSgetBasis(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *panCstatus;
    SEXP      spanCstatus = R_NilValue;
    int       *panRstatus;
    SEXP      spanRstatus = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode", "panCstatus", "panRstatus"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;
    int       nCons, nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_CONS,&nCons);
    CHECK_ERRCODE;
    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spanCstatus = NEW_INTEGER(nVars));
    nProtect += 1;
    panCstatus = INTEGER_POINTER(spanCstatus);

    PROTECT(spanRstatus = NEW_INTEGER(nCons));
    nProtect += 1;
    panRstatus = INTEGER_POINTER(spanRstatus);

    *pnErrorCode = LSgetBasis(pModel,panCstatus,panRstatus);
    
ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spanCstatus);
        SET_VECTOR_ELT(rList, 2, spanRstatus);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetSolution(SEXP  sModel,
                     SEXP  snWhich)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nWhich = Rf_asInteger(snWhich);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padResult;
    SEXP      spadResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "padResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadResult = NEW_NUMERIC(nVars));
    nProtect += 1;
    padResult = NUMERIC_POINTER(spadResult);

    *pnErrorCode = LSgetSolution(pModel,nWhich,padResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadResult);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetMIPPrimalSolution(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padPrimal;
    SEXP      spadPrimal = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "padPrimal"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadPrimal = NEW_NUMERIC(nVars));
    nProtect += 1;
    padPrimal = NUMERIC_POINTER(spadPrimal);

    *pnErrorCode = LSgetMIPPrimalSolution(pModel,padPrimal);
  
ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadPrimal);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetMIPDualSolution(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padDual;
    SEXP      spadDual = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "padDual"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;
        
    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_CONS,&nCons);
    CHECK_ERRCODE;

    PROTECT(spadDual = NEW_NUMERIC(nCons));
    nProtect += 1;
    padDual = NUMERIC_POINTER(spadDual);

    *pnErrorCode = LSgetMIPDualSolution(pModel,padDual);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadDual);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetMIPReducedCosts(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padReducedCost;
    SEXP      spadReducedCost = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "padReducedCost"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadReducedCost = NEW_NUMERIC(nVars));
    nProtect += 1;
    padReducedCost = NUMERIC_POINTER(spadReducedCost);

    *pnErrorCode = LSgetMIPReducedCosts(pModel,padReducedCost);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadReducedCost);
    }

    UNPROTECT(nProtect + 2);
   
    return rList;
}

SEXP rcLSgetMIPSlacks(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padSlack;
    SEXP      spadSlack = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "padSlack"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_CONS,&nCons);
    CHECK_ERRCODE;

    PROTECT(spadSlack = NEW_NUMERIC(nCons));
    nProtect += 1;
    padSlack = NUMERIC_POINTER(spadSlack);

    *pnErrorCode = LSgetMIPSlacks(pModel,padSlack);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadSlack);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetMIPBasis(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *panCstatus;
    SEXP      spanCstatus = R_NilValue;
    int       *panRstatus;
    SEXP      spanRstatus = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode", "panCstatus", "panRstatus"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;
    int       nCons, nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_CONS,&nCons);
    CHECK_ERRCODE;
    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spanCstatus = NEW_INTEGER(nVars));
    nProtect += 1;
    panCstatus = INTEGER_POINTER(spanCstatus);

    PROTECT(spanRstatus = NEW_INTEGER(nCons));
    nProtect += 1;
    panRstatus = INTEGER_POINTER(spanRstatus);

    *pnErrorCode = LSgetMIPBasis(pModel,panCstatus,panRstatus);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spanCstatus);
        SET_VECTOR_ELT(rList, 2, spanRstatus);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetNextBestMIPSol(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnStatus;
    SEXP      spnStatus = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pnStatus"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnStatus = NEW_INTEGER(1));
    nProtect += 1;
    pnStatus = INTEGER_POINTER(spnStatus);

    *pnErrorCode = LSgetNextBestMIPSol(pModel,pnStatus);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnStatus);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

/********************************************************
* Model Query Routines    (44)                          *
*********************************************************/
SEXP rcLSgetLPData(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnObjSense;
    SEXP      spnObjSense = R_NilValue;
    double    *pdObjConst;
    SEXP      spdObjConst = R_NilValue;
    double    *padC;
    SEXP      spadC = R_NilValue;
    double    *padB;
    SEXP      spadB = R_NilValue;
    char      *pachConTypes = NULL;
    SEXP      spachConTypes = R_NilValue;
    int       *paiAcols;
    SEXP      spaiAcols = R_NilValue;
    int       *panAcols;
    SEXP      spanAcols = R_NilValue;
    double    *padAcoef;
    SEXP      spadAcoef = R_NilValue;
    int       *paiArows;
    SEXP      spaiArows = R_NilValue;
    double    *padL;
    SEXP      spadL = R_NilValue;
    double    *padU;
    SEXP      spadU = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[12] = {"ErrorCode", "pnObjSense","pdObjConst","padC","padB",
                            "pachConTypes", "paiAcols", "panAcols", "padAcoef", 
                            "paiArows", "padL", "padU"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 11;
    int       nIdx, nProtect = 0;
    int       nCons, nVars, nNnz;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_CONS,&nCons);
    CHECK_ERRCODE;
    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;
    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_NONZ,&nNnz);
    CHECK_ERRCODE;

    PROTECT(spnObjSense = NEW_INTEGER(1));
    nProtect += 1;
    pnObjSense = INTEGER_POINTER(spnObjSense);

    PROTECT(spdObjConst = NEW_NUMERIC(1));
    nProtect += 1;
    pdObjConst = NUMERIC_POINTER(spdObjConst);

    PROTECT(spadC = NEW_NUMERIC(nVars));
    nProtect += 1;
    padC = NUMERIC_POINTER(spadC);

    PROTECT(spadB = NEW_NUMERIC(nCons));
    nProtect += 1;
    padB = NUMERIC_POINTER(spadB);

    PROTECT(spachConTypes = NEW_CHARACTER(1));
    nProtect += 1;
    pachConTypes = (char *)malloc(sizeof(char)*(nCons+1));
    pachConTypes[nCons] = '\0';

    PROTECT(spaiAcols = NEW_INTEGER(nVars));
    nProtect += 1;
    paiAcols = INTEGER_POINTER(spaiAcols);

    PROTECT(spanAcols = NEW_INTEGER(nVars));
    nProtect += 1;
    panAcols = INTEGER_POINTER(spanAcols);

    PROTECT(spadAcoef = NEW_NUMERIC(nNnz));
    nProtect += 1;
    padAcoef = NUMERIC_POINTER(spadAcoef);

    PROTECT(spaiArows = NEW_INTEGER(nNnz));
    nProtect += 1;
    paiArows = INTEGER_POINTER(spaiArows);

    PROTECT(spadL = NEW_NUMERIC(nVars));
    nProtect += 1;
    padL = NUMERIC_POINTER(spadL);

    PROTECT(spadU = NEW_NUMERIC(nVars));
    nProtect += 1;
    padU = NUMERIC_POINTER(spadU);

    *pnErrorCode = LSgetLPData(pModel,
                               pnObjSense,
                               pdObjConst,
                               padC,
                               padB,
                               pachConTypes,
                               paiAcols,
                               panAcols,
                               padAcoef,
                               paiArows,
                               padL,
                               padU);

    CHECK_ERRCODE;

    SET_STRING_ELT(spachConTypes,0,mkChar(pachConTypes)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnObjSense);
        SET_VECTOR_ELT(rList, 2, spdObjConst);
        SET_VECTOR_ELT(rList, 3, spadC);
        SET_VECTOR_ELT(rList, 4, spadB);
        SET_VECTOR_ELT(rList, 5, spachConTypes);
        SET_VECTOR_ELT(rList, 6, spaiAcols);
        SET_VECTOR_ELT(rList, 6, spanAcols);
        SET_VECTOR_ELT(rList, 7, spadAcoef);
        SET_VECTOR_ELT(rList, 8, spaiArows);
        SET_VECTOR_ELT(rList, 9, spadL);
        SET_VECTOR_ELT(rList, 10, spadU);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetQCData(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *paiQCrows;
    SEXP      spaiQCrows = R_NilValue;
    int       *paiQCcols1;
    SEXP      spaiQCcols1 = R_NilValue;
    int       *paiQCcols2;
    SEXP      spaiQCcols2 = R_NilValue;
    double    *padQCcoef;
    SEXP      spadQCcoef = R_NilValue;

    SEXP      rList = R_NilValue;
    char      *Names[5] = {"ErrorCode", "paiQCrows","paiQCcols1","paiQCcols2","padQCcoef"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 5;
    int       nIdx, nProtect = 0;
    int       nNnz;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_NONZ,&nNnz);
    CHECK_ERRCODE;

    PROTECT(spaiQCrows = NEW_INTEGER(nNnz));
    nProtect += 1;
    paiQCrows = INTEGER_POINTER(spaiQCrows);

    PROTECT(spaiQCcols1 = NEW_INTEGER(nNnz));
    nProtect += 1;
    paiQCcols1 = INTEGER_POINTER(spaiQCcols1);

    PROTECT(spaiQCcols2 = NEW_INTEGER(nNnz));
    nProtect += 1;
    paiQCcols2 = INTEGER_POINTER(spaiQCcols2);

    PROTECT(spadQCcoef = NEW_NUMERIC(nNnz));
    nProtect += 1;
    padQCcoef = NUMERIC_POINTER(spadQCcoef);

    *pnErrorCode = LSgetQCData(pModel,
                               paiQCrows,
                               paiQCcols1,
                               paiQCcols2,
                               padQCcoef);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spaiQCrows);
        SET_VECTOR_ELT(rList, 2, spaiQCcols1);
        SET_VECTOR_ELT(rList, 3, spaiQCcols2);
        SET_VECTOR_ELT(rList, 4, spadQCcoef);
    }

    UNPROTECT(nProtect + 2);
   
    return rList;
}

SEXP rcLSgetQCDatai(SEXP  sModel,
                    SEXP  siCon)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iCon = Rf_asInteger(siCon);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnQCnnz;
    SEXP      spnQCnnz = R_NilValue;
    int       *paiQCcols1;
    SEXP      spaiQCcols1 = R_NilValue;
    int       *paiQCcols2;
    SEXP      spaiQCcols2 = R_NilValue;
    double    *padQCcoef;
    SEXP      spadQCcoef = R_NilValue;

    SEXP      rList = R_NilValue;
    char      *Names[5] = {"ErrorCode", "pnQCnnz","paiQCcols1","paiQCcols2","padQCcoef"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 5;
    int       nIdx, nProtect = 0;
    int       nNnz;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_NONZ,&nNnz);
    CHECK_ERRCODE;

    PROTECT(spnQCnnz = NEW_INTEGER(1));
    nProtect += 1;
    pnQCnnz = INTEGER_POINTER(spnQCnnz);

    PROTECT(spaiQCcols1 = NEW_INTEGER(nNnz));
    nProtect += 1;
    paiQCcols1 = INTEGER_POINTER(spaiQCcols1);

    PROTECT(spaiQCcols2 = NEW_INTEGER(nNnz));
    nProtect += 1;
    paiQCcols2 = INTEGER_POINTER(spaiQCcols2);

    PROTECT(spadQCcoef = NEW_NUMERIC(nNnz));
    nProtect += 1;
    padQCcoef = NUMERIC_POINTER(spadQCcoef);

    *pnErrorCode = LSgetQCDatai(pModel,
                                iCon,
                                pnQCnnz,
                                paiQCcols1,
                                paiQCcols2,
                                padQCcoef);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnQCnnz);
        SET_VECTOR_ELT(rList, 2, spaiQCcols1);
        SET_VECTOR_ELT(rList, 3, spaiQCcols2);
        SET_VECTOR_ELT(rList, 4, spadQCcoef);
    }

    UNPROTECT(nProtect + 2);
   
    return rList;
}

SEXP rcLSgetVarType(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pachVarTypes = NULL;
    SEXP      spachVarTypes = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pachVarTypes"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spachVarTypes = NEW_CHARACTER(1));
    nProtect += 1;
    pachVarTypes = (char *)malloc(sizeof(char)*(nVars+1));
    pachVarTypes[nVars] = '\0';

    *pnErrorCode = LSgetVarType(pModel,pachVarTypes);

    CHECK_ERRCODE;

    SET_STRING_ELT(spachVarTypes,0,mkChar(pachVarTypes)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spachVarTypes);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetVarStartPoint(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padPrimal;
    SEXP      spadPrimal = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "padPrimal"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadPrimal = NEW_NUMERIC(nVars));
    nProtect += 1;
    padPrimal = NUMERIC_POINTER(spadPrimal);

    *pnErrorCode = LSgetVarStartPoint(pModel,padPrimal);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadPrimal);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetVarStartPointPartial(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnCols;
    SEXP      spnCols = R_NilValue;
    int       *paiCols;
    SEXP      spaiCols = R_NilValue;
    double    *padPrimal;
    SEXP      spadPrimal = R_NilValue;
    int       *paiCols2;
    SEXP      spaiCols2 = R_NilValue;
    double    *padPrimal2;
    SEXP      spadPrimal2 = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[4] = {"ErrorCode", "pnCols", "paiCols", "padPrimal"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 4;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spnCols = NEW_INTEGER(1));
    nProtect += 1;
    pnCols = INTEGER_POINTER(spnCols);

    PROTECT(spaiCols = NEW_INTEGER(nVars));
    nProtect += 1;
    paiCols = INTEGER_POINTER(spaiCols);

    PROTECT(spadPrimal = NEW_NUMERIC(nVars));
    nProtect += 1;
    padPrimal = NUMERIC_POINTER(spadPrimal);

    *pnErrorCode = LSgetVarStartPointPartial(pModel,pnCols,paiCols,padPrimal);
    CHECK_ERRCODE;

    PROTECT(spaiCols2 = NEW_INTEGER(*pnCols));
    nProtect += 1;
    paiCols2 = INTEGER_POINTER(spaiCols2);
    memcpy(paiCols2,paiCols,sizeof(int)*(*pnCols));

    PROTECT(spadPrimal2 = NEW_NUMERIC(*pnCols));
    nProtect += 1;
    padPrimal2 = NUMERIC_POINTER(spadPrimal2);
    memcpy(padPrimal2,padPrimal,sizeof(double)*(*pnCols));

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnCols);
        SET_VECTOR_ELT(rList, 2, spaiCols2);
        SET_VECTOR_ELT(rList, 3, spadPrimal2);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetMIPVarStartPointPartial(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnCols;
    SEXP      spnCols = R_NilValue;
    int       *paiCols;
    SEXP      spaiCols = R_NilValue;
    int       *panPrimal;
    SEXP      spanPrimal = R_NilValue;
    int       *paiCols2;
    SEXP      spaiCols2 = R_NilValue;
    int       *panPrimal2;
    SEXP      spanPrimal2 = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[4] = {"ErrorCode", "pnCols", "paiCols", "panPrimal"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 4;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spnCols = NEW_INTEGER(1));
    nProtect += 1;
    pnCols = INTEGER_POINTER(spnCols);

    PROTECT(spaiCols = NEW_INTEGER(nVars));
    nProtect += 1;
    paiCols = INTEGER_POINTER(spaiCols);

    PROTECT(spanPrimal = NEW_INTEGER(nVars));
    nProtect += 1;
    panPrimal = INTEGER_POINTER(spanPrimal);

    *pnErrorCode = LSgetMIPVarStartPointPartial(pModel,pnCols,paiCols,panPrimal);
    CHECK_ERRCODE;

    PROTECT(spaiCols2 = NEW_INTEGER(*pnCols));
    nProtect += 1;
    paiCols2 = INTEGER_POINTER(spaiCols2);
    memcpy(paiCols2,paiCols,sizeof(int)*(*pnCols));

    PROTECT(spanPrimal2 = NEW_NUMERIC(*pnCols));
    nProtect += 1;
    panPrimal2 = INTEGER_POINTER(spanPrimal2);
    memcpy(panPrimal2,panPrimal,sizeof(int)*(*pnCols));

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnCols);
        SET_VECTOR_ELT(rList, 2, spaiCols2);
        SET_VECTOR_ELT(rList, 3, spanPrimal2);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetMIPVarStartPoint(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padPrimal;
    SEXP      spadPrimal = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "padPrimal"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadPrimal = NEW_NUMERIC(nVars));
    nProtect += 1;
    padPrimal = NUMERIC_POINTER(spadPrimal);

    *pnErrorCode = LSgetMIPVarStartPoint(pModel,padPrimal);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadPrimal);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetSETSData(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *piNsets;
    SEXP      spiNsets = R_NilValue;
    int       *piNtnz;
    SEXP      spiNtnz = R_NilValue;
    char      *pachSETtype, *pachSETtype2;
    SEXP      spachSETtype = R_NilValue;
    int       *piCardnum, *piCardnum2;
    SEXP      spiCardnum = R_NilValue, spiCardnum2 = R_NilValue;
    int       *piNnz, *piNnz2;
    SEXP      spiNnz = R_NilValue, spiNnz2 = R_NilValue;
    int       *piBegset, *piBegset2;
    SEXP      spiBegset = R_NilValue, spiBegset2 = R_NilValue;
    int       *piVarndx, *piVarndx2;
    SEXP      spiVarndx = R_NilValue, spiVarndx2 = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[8] = {"ErrorCode", "piNsets", "piNtnz", "pachSETtype", 
                           "piCardnum", "piNnz", "piBegset", "piVarndx"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 8;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spiNsets = NEW_INTEGER(1));
    nProtect += 1;
    piNsets = INTEGER_POINTER(spiNsets);

    PROTECT(spiNtnz = NEW_INTEGER(1));
    nProtect += 1;
    piNtnz = INTEGER_POINTER(spiNtnz);

    PROTECT(spachSETtype = NEW_CHARACTER(1));
    nProtect += 1;
    pachSETtype = (char *)malloc(sizeof(char)*(nVars+1));

    PROTECT(spiCardnum = NEW_INTEGER(nVars));
    nProtect += 1;
    piCardnum = INTEGER_POINTER(spiCardnum);

    PROTECT(spiNnz = NEW_INTEGER(nVars));
    nProtect += 1;
    piNnz = INTEGER_POINTER(spiNnz);

    PROTECT(spiBegset = NEW_INTEGER(nVars));
    nProtect += 1;
    piBegset = INTEGER_POINTER(spiBegset);

    PROTECT(spiVarndx = NEW_INTEGER(nVars));
    nProtect += 1;
    piVarndx = INTEGER_POINTER(spiVarndx);

    *pnErrorCode = LSgetSETSData(pModel,
                                 piNsets,
                                 piNtnz,
                                 pachSETtype,
                                 piCardnum,
                                 piNnz,
                                 piBegset,
                                 piVarndx);
    CHECK_ERRCODE;

    pachSETtype2 = (char *)malloc(sizeof(char)*(*piNsets+1));
    memcpy(pachSETtype2,pachSETtype,sizeof(char)*(*piNsets));
    pachSETtype2[*piNsets] = '\0';
    SET_STRING_ELT(spachSETtype,0,mkChar(pachSETtype2)); 

    PROTECT(spiCardnum2 = NEW_INTEGER(*piNsets));
    nProtect += 1;
    piCardnum2 = INTEGER_POINTER(spiCardnum2);
    memcpy(piCardnum2,piCardnum,sizeof(int)*(*piNsets));

    PROTECT(spiNnz2 = NEW_INTEGER(*piNsets));
    nProtect += 1;
    piNnz2 = INTEGER_POINTER(spiNnz2);
    memcpy(piNnz2,piNnz,sizeof(int)*(*piNsets));

    PROTECT(spiBegset2 = NEW_INTEGER(*piNsets+1));
    nProtect += 1;
    piBegset2 = INTEGER_POINTER(spiBegset2);
    memcpy(piBegset2,piBegset,sizeof(int)*(*piNsets+1));

    PROTECT(spiVarndx2 = NEW_INTEGER(*piNtnz));
    nProtect += 1;
    piVarndx2 = INTEGER_POINTER(spiVarndx2);
    memcpy(piVarndx2,piVarndx,sizeof(int)*(*piNtnz));

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spiNsets);
        SET_VECTOR_ELT(rList, 2, spiNtnz);
        SET_VECTOR_ELT(rList, 3, spachSETtype);
        SET_VECTOR_ELT(rList, 4, spiCardnum2);
        SET_VECTOR_ELT(rList, 5, spiNnz2);
        SET_VECTOR_ELT(rList, 6, spiBegset2);
        SET_VECTOR_ELT(rList, 7, spiVarndx2);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetSETSDatai(SEXP  sModel, 
                      SEXP  siSet)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iSet = Rf_asInteger(siSet);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pachSETtype;
    SEXP      spachSETtype = R_NilValue;
    int       *piCardnum;
    SEXP      spiCardnum = R_NilValue;
    int       *piNnz;
    SEXP      spiNnz = R_NilValue;
    int       *piVarndx, *piVarndx2;
    SEXP      spiVarndx = R_NilValue, spiVarndx2 = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[5] = {"ErrorCode", "pachSETtype", "piCardnum", "piNnz", "piVarndx"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 5;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spachSETtype = NEW_CHARACTER(1));
    nProtect += 1;
    pachSETtype = (char *)malloc(sizeof(char)*(2));
    pachSETtype[1] = '\0';

    PROTECT(spiCardnum = NEW_INTEGER(1));
    nProtect += 1;
    piCardnum = INTEGER_POINTER(spiCardnum);

    PROTECT(spiNnz = NEW_INTEGER(1));
    nProtect += 1;
    piNnz = INTEGER_POINTER(spiNnz);

    PROTECT(spiVarndx = NEW_INTEGER(nVars));
    nProtect += 1;
    piVarndx = INTEGER_POINTER(spiVarndx);

    *pnErrorCode = LSgetSETSDatai(pModel,
                                  iSet,
                                  pachSETtype,
                                  piCardnum,
                                  piNnz,
                                  piVarndx);
    CHECK_ERRCODE;

    SET_STRING_ELT(spachSETtype,0,mkChar(pachSETtype)); 

    PROTECT(spiVarndx2 = NEW_INTEGER(*piNnz));
    nProtect += 1;
    piVarndx2 = INTEGER_POINTER(spiVarndx2);
    memcpy(piVarndx2,piVarndx,sizeof(int)*(*piNnz));

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spachSETtype);
        SET_VECTOR_ELT(rList, 2, spiCardnum);
        SET_VECTOR_ELT(rList, 3, spiNnz);
        SET_VECTOR_ELT(rList, 4, spiVarndx2);

    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetSemiContData(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *piNvars;
    SEXP      spiNvars = R_NilValue;
    int       *panVarndx, *panVarndx2;
    SEXP      spanVarndx = R_NilValue, spanVarndx2 = R_NilValue;
    double    *padL, *padL2, *padU, *padU2;
    SEXP      spadL = R_NilValue, spadL2 = R_NilValue;
    SEXP      spadU = R_NilValue, spadU2 = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[5] = {"ErrorCode", "piNvars", "panVarndx", "padL", "padU"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 5;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spiNvars = NEW_INTEGER(1));
    nProtect += 1;
    piNvars = INTEGER_POINTER(spiNvars);

    PROTECT(spanVarndx = NEW_INTEGER(nVars));
    nProtect += 1;
    panVarndx = INTEGER_POINTER(spanVarndx);

    PROTECT(spadL = NEW_NUMERIC(nVars));
    nProtect += 1;
    padL = NUMERIC_POINTER(spadL);

    PROTECT(spadU = NEW_NUMERIC(nVars));
    nProtect += 1;
    padU = NUMERIC_POINTER(spadU);

    *pnErrorCode = LSgetSemiContData(pModel,
                                     piNvars,
                                     panVarndx,
                                     padL,
                                     padU);
    CHECK_ERRCODE;

    PROTECT(spanVarndx2 = NEW_INTEGER(*piNvars));
    nProtect += 1;
    panVarndx2 = INTEGER_POINTER(spanVarndx2);
    memcpy(panVarndx2,panVarndx,sizeof(int)*(*piNvars));

    PROTECT(spadL2 = NEW_NUMERIC(*piNvars));
    nProtect += 1;
    padL2 = NUMERIC_POINTER(spadL2);
    memcpy(padL2,padL,sizeof(double)*(*piNvars));

    PROTECT(spadU2 = NEW_NUMERIC(*piNvars));
    nProtect += 1;
    padU2 = NUMERIC_POINTER(spadU2);
    memcpy(padU2,padU,sizeof(double)*(*piNvars));

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spiNvars);
        SET_VECTOR_ELT(rList, 2, spanVarndx2);
        SET_VECTOR_ELT(rList, 3, spadL2);
        SET_VECTOR_ELT(rList, 4, spadU2);

    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetLPVariableDataj(SEXP  sModel,
                            SEXP  siVar)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iVar = Rf_asInteger(siVar);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pchVartype;
    SEXP      spchVartype = R_NilValue;
    double    *pdC;
    SEXP      spdC = R_NilValue;
    double    *pdL;
    SEXP      spdL = R_NilValue;
    double    *pdU;
    SEXP      spdU = R_NilValue;
    int       *pnAnnz;
    SEXP      spnAnnz = R_NilValue;
    int       *paiArows, *paiArows2;
    SEXP      spaiArows = R_NilValue, spaiArows2 = R_NilValue;
    double    *padAcoef, *padAcoef2;
    SEXP      spadAcoef = R_NilValue, spadAcoef2 = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[8] = {"ErrorCode", "pchVartype", "pdC", "pdL", "pdU", 
                           "pnAnnz","paiArows", "padAcoef"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 8;
    int       nIdx, nProtect = 0;
    int       nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_CONS,&nCons);
    CHECK_ERRCODE;

    PROTECT(spchVartype = NEW_CHARACTER(1));
    nProtect += 1;
    pchVartype = (char *)malloc(sizeof(char)*(2));
    pchVartype[1] = '\0';

    PROTECT(spdC = NEW_NUMERIC(1));
    nProtect += 1;
    pdC = NUMERIC_POINTER(spdC);

    PROTECT(spdL = NEW_NUMERIC(1));
    nProtect += 1;
    pdL = NUMERIC_POINTER(spdL);

    PROTECT(spdU = NEW_NUMERIC(1));
    nProtect += 1;
    pdU = NUMERIC_POINTER(spdU);

    PROTECT(spnAnnz = NEW_INTEGER(1));
    nProtect += 1;
    pnAnnz = INTEGER_POINTER(spnAnnz);

    PROTECT(spaiArows = NEW_INTEGER(nCons));
    nProtect += 1;
    paiArows = INTEGER_POINTER(spaiArows);

    PROTECT(spadAcoef = NEW_NUMERIC(nCons));
    nProtect += 1;
    padAcoef = NUMERIC_POINTER(spadAcoef);

    *pnErrorCode = LSgetLPVariableDataj(pModel,
                                        iVar,
                                        pchVartype,
                                        pdC,
                                        pdL,
                                        pdU,
                                        pnAnnz,
                                        paiArows,
                                        padAcoef);

    CHECK_ERRCODE;

    SET_STRING_ELT(spchVartype,0,mkChar(pchVartype)); 

    PROTECT(spaiArows2 = NEW_INTEGER(*pnAnnz));
    nProtect += 1;
    paiArows2 = INTEGER_POINTER(spaiArows2);
    memcpy(paiArows2,paiArows,sizeof(int)*(*pnAnnz));

    PROTECT(spadAcoef2 = NEW_NUMERIC(*pnAnnz));
    nProtect += 1;
    padAcoef2 = NUMERIC_POINTER(spadAcoef2);
    memcpy(padAcoef2,padAcoef,sizeof(double)*(*pnAnnz));

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spchVartype);
        SET_VECTOR_ELT(rList, 2, spdC);
        SET_VECTOR_ELT(rList, 3, spdL);
        SET_VECTOR_ELT(rList, 4, spdU);
        SET_VECTOR_ELT(rList, 5, spnAnnz);
        SET_VECTOR_ELT(rList, 6, spaiArows2);
        SET_VECTOR_ELT(rList, 7, spadAcoef2);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetVariableNamej(SEXP  sModel,
                          SEXP  siVar)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iVar = Rf_asInteger(siVar);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pachVarName;
    SEXP      spachVarName = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pachVarName"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spachVarName = NEW_CHARACTER(1));
    nProtect += 1;
    pachVarName = (char *)malloc(sizeof(char)*(256));

    *pnErrorCode = LSgetVariableNamej(pModel,
                                      iVar,
                                      pachVarName);
    CHECK_ERRCODE;

    SET_STRING_ELT(spachVarName,0,mkChar(pachVarName)); 
    
ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spachVarName);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetVariableIndex(SEXP  sModel,
                          SEXP  spszVarName)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszVarName = (char *) CHAR(STRING_ELT(spszVarName,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *piVar;
    SEXP      spiVar = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "piVar"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spiVar = NEW_INTEGER(1));
    nProtect += 1;
    piVar = INTEGER_POINTER(spiVar);

    *pnErrorCode = LSgetVariableIndex(pModel,pszVarName,piVar);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spiVar);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetConstraintNamei(SEXP     sModel,
                            SEXP     siCon)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iCon = Rf_asInteger(siCon);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pachConName;
    SEXP      spachConName = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pachConName"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spachConName = NEW_CHARACTER(1));
    nProtect += 1;
    pachConName = (char *)malloc(sizeof(char)*(256));

    *pnErrorCode = LSgetConstraintNamei(pModel,
                                        iCon,
                                        pachConName);
    CHECK_ERRCODE;

    SET_STRING_ELT(spachConName,0,mkChar(pachConName)); 
    
ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spachConName);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetConstraintIndex(SEXP  sModel,
                            SEXP  spszConName)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszConName = (char *) CHAR(STRING_ELT(spszConName,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *piCon;
    SEXP      spiCon = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "piCon"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spiCon = NEW_INTEGER(1));
    nProtect += 1;
    piCon = INTEGER_POINTER(spiCon);

    *pnErrorCode = LSgetConstraintIndex(pModel,pszConName,piCon);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spiCon);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetConstraintDatai(SEXP      sModel,
                            SEXP      siCon)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iCon = Rf_asInteger(siCon);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pchConType;
    SEXP      spchConType = R_NilValue;
    char      *pchIsNlp;
    SEXP      spchIsNlp = R_NilValue;
    double    *pdB;
    SEXP      spdB = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[4] = {"ErrorCode", "pchConType", "pchIsNlp", "pdB"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 4;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spchConType = NEW_CHARACTER(1));
    nProtect += 1;
    pchConType = (char *)malloc(sizeof(char)*(1));

    PROTECT(spchIsNlp = NEW_CHARACTER(1));
    nProtect += 1;
    pchIsNlp = (char *)malloc(sizeof(char)*(1));

    PROTECT(spdB = NEW_NUMERIC(1));
    nProtect += 1;
    pdB = NUMERIC_POINTER(spdB);

    *pnErrorCode = LSgetConstraintDatai(pModel,
                                        iCon,
                                        pchConType,
                                        pchIsNlp,
                                        pdB);
    CHECK_ERRCODE;

    SET_STRING_ELT(spchConType,0,mkChar(pchConType)); 
    SET_STRING_ELT(spchIsNlp,0,mkChar(pchIsNlp));

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spchConType);
        SET_VECTOR_ELT(rList, 2, spchIsNlp);
        SET_VECTOR_ELT(rList, 3, spdB);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetLPConstraintDatai(SEXP      sModel,
                              SEXP      siCon)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iCon = Rf_asInteger(siCon);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pchConType;
    SEXP      spchConType = R_NilValue;
    double    *pdB;
    SEXP      spdB = R_NilValue;
    int       *pnNnz;
    SEXP      spnNnz = R_NilValue;
    int       *paiVar;
    SEXP      spaiVar = R_NilValue;
    double    *padAcoef;
    SEXP      spadAcoef = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[6] = {"ErrorCode", "pchConType", "pdB", "pnNnz", "paiVar", "padAcoef"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 6;
    int       nIdx, nProtect = 0;
    int       nNnz;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spchConType = NEW_CHARACTER(1));
    nProtect += 1;
    pchConType = (char *)malloc(sizeof(char)*(1));

    PROTECT(spdB = NEW_NUMERIC(1));
    nProtect += 1;
    pdB = NUMERIC_POINTER(spdB);

    PROTECT(spnNnz = NEW_INTEGER(1));
    nProtect += 1;
    pnNnz = INTEGER_POINTER(spnNnz);

    *pnErrorCode = LSgetLPConstraintDatai(pModel,iCon,NULL,NULL,&nNnz,NULL,NULL);
    CHECK_ERRCODE;

    PROTECT(spaiVar = NEW_INTEGER(nNnz));
    nProtect += 1;
    paiVar = INTEGER_POINTER(spaiVar);

    PROTECT(spadAcoef = NEW_NUMERIC(nNnz));
    nProtect += 1;
    padAcoef = NUMERIC_POINTER(spadAcoef);

    *pnErrorCode = LSgetLPConstraintDatai(pModel,
                                          iCon,
                                          pchConType,
                                          pdB,
                                          pnNnz,
                                          paiVar,
                                          padAcoef);
    CHECK_ERRCODE;

    SET_STRING_ELT(spchConType,0,mkChar(pchConType)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spchConType);
        SET_VECTOR_ELT(rList, 2, spdB);
        SET_VECTOR_ELT(rList, 3, spnNnz);
        SET_VECTOR_ELT(rList, 4, spaiVar);
        SET_VECTOR_ELT(rList, 5, spadAcoef);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetConeNamei(SEXP     sModel,
                      SEXP     siCone)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iCone = Rf_asInteger(siCone);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pachConeName;
    SEXP      spachConeName = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pachConeName"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spachConeName = NEW_CHARACTER(1));
    nProtect += 1;
    pachConeName = (char *)malloc(sizeof(char)*(256));

    *pnErrorCode = LSgetConeNamei(pModel,
                                  iCone,
                                  pachConeName);
    CHECK_ERRCODE;

    SET_STRING_ELT(spachConeName,0,mkChar(pachConeName)); 
    
ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spachConeName);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetConeIndex(SEXP  sModel,
                      SEXP  spszConeName)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszConeName = (char *) CHAR(STRING_ELT(spszConeName,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *piCone;
    SEXP      spiCone = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "piCone"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spiCone = NEW_INTEGER(1));
    nProtect += 1;
    piCone = INTEGER_POINTER(spiCone);

    *pnErrorCode = LSgetConeIndex(pModel,pszConeName,piCone);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spiCone);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetConeDatai(SEXP      sModel,
                      SEXP      siCone)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iCone = Rf_asInteger(siCone);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pchConeType;
    SEXP      spchConeType = R_NilValue;
    int       *piNnz;
    SEXP      spiNnz = R_NilValue;
    int       *paiCols;
    SEXP      spaiCols = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[4] = {"ErrorCode", "pchConeType", "piNnz", "paiCols"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 4;
    int       nIdx, nProtect = 0;
    int       nNnz;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spchConeType = NEW_CHARACTER(1));
    nProtect += 1;
    pchConeType = (char *)malloc(sizeof(char)*(1));

    PROTECT(spiNnz = NEW_INTEGER(1));
    nProtect += 1;
    piNnz = INTEGER_POINTER(spiNnz);

    *pnErrorCode = LSgetConeDatai(pModel,iCone,NULL,&nNnz,NULL);
    CHECK_ERRCODE;

    PROTECT(spaiCols = NEW_INTEGER(1));
    nProtect += 1;
    paiCols = INTEGER_POINTER(spaiCols);

    *pnErrorCode = LSgetConeDatai(pModel,iCone,pchConeType,piNnz,paiCols);
    CHECK_ERRCODE;

    SET_STRING_ELT(spchConeType,0,mkChar(pchConeType)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spchConeType);
        SET_VECTOR_ELT(rList, 2, spiNnz);
        SET_VECTOR_ELT(rList, 3, spaiCols);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetNLPData(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *paiNLPcols;
    SEXP      spaiNLPcols = R_NilValue;
    int       *panNLPcols;
    SEXP      spanNLPcols = R_NilValue;
    double    *padNLPcoef;
    SEXP      spadNLPcoef = R_NilValue;
    int       *paiNLProws;
    SEXP      spaiNLProws = R_NilValue;
    int       *pnNLPobj;
    SEXP      spnNLPobj = R_NilValue;
    int       *paiNLPobj;
    SEXP      spaiNLPobj = R_NilValue;
    double    *padNLPobj;
    SEXP      spadNLPobj = R_NilValue;
    char      *pachNLPConTypes;
    SEXP      spachNLPConTypes = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[9] = {"ErrorCode", "paiNLPcols", "panNLPcols", "padNLPcoef", 
                           "paiNLProws", "pnNLPobj",
                           "paiNLPobj","padNLPobj", "pachNLPConTypes"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 9;
    int       nIdx, nProtect = 0;
    int       nVars, nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_CONS,&nCons);
    CHECK_ERRCODE;

    PROTECT(spaiNLPcols = NEW_INTEGER(nVars + 1));
    nProtect += 1;
    paiNLPcols = INTEGER_POINTER(spaiNLPcols);

    PROTECT(spanNLPcols = NEW_INTEGER(nVars + 1));
    nProtect += 1;
    panNLPcols = INTEGER_POINTER(spanNLPcols);

    PROTECT(spnNLPobj = NEW_INTEGER(1));
    nProtect += 1;
    pnNLPobj = INTEGER_POINTER(spnNLPobj);

    PROTECT(spachNLPConTypes = NEW_CHARACTER(1));
    nProtect += 1;
    pachNLPConTypes = (char *)malloc(sizeof(char)*(nCons));

    *pnErrorCode = LSgetNLPData(pModel,paiNLPcols,panNLPcols,NULL,
                                NULL,pnNLPobj,NULL,NULL,pachNLPConTypes);
    CHECK_ERRCODE;

    if(paiNLPcols[nVars] == 0 || *pnNLPobj == 0)
    {
        goto ErrorReturn;
    }

    SET_STRING_ELT(spachNLPConTypes,0,mkChar(pachNLPConTypes));

    PROTECT(spadNLPcoef = NEW_NUMERIC(paiNLPcols[nVars]));
    nProtect += 1;
    padNLPcoef = NUMERIC_POINTER(spadNLPcoef);

    PROTECT(spaiNLProws = NEW_INTEGER(paiNLPcols[nVars]));
    nProtect += 1;
    paiNLProws = INTEGER_POINTER(spaiNLProws);

    PROTECT(spaiNLPobj = NEW_INTEGER(*pnNLPobj));
    nProtect += 1;
    paiNLPobj = INTEGER_POINTER(spaiNLPobj);

    PROTECT(spadNLPobj = NEW_NUMERIC(*pnNLPobj));
    nProtect += 1;
    padNLPobj = NUMERIC_POINTER(spadNLPobj);

    *pnErrorCode = LSgetNLPData(pModel,NULL,NULL,padNLPcoef,
                                paiNLProws,NULL,paiNLPobj,padNLPobj,NULL);
    CHECK_ERRCODE;

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spaiNLPcols);
        SET_VECTOR_ELT(rList, 2, spanNLPcols);
        SET_VECTOR_ELT(rList, 3, spadNLPcoef);
        SET_VECTOR_ELT(rList, 4, spaiNLProws);
        SET_VECTOR_ELT(rList, 5, spnNLPobj);
        SET_VECTOR_ELT(rList, 6, spaiNLPobj);
        SET_VECTOR_ELT(rList, 7, spadNLPobj);
        SET_VECTOR_ELT(rList, 8, spachNLPConTypes);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetNLPConstraintDatai(SEXP  sModel,
                               SEXP  siCon)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iCon = Rf_asInteger(siCon);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnNnz;
    SEXP      spnNnz = R_NilValue;
    int       *paiNLPcols;
    SEXP      spaiNLPcols = R_NilValue;
    double    *padNLPcoef;
    SEXP      spadNLPcoef = R_NilValue;

    SEXP      rList = R_NilValue;
    char      *Names[4] = {"ErrorCode", "pnNnz","paiNLPcols","padNLPcoef"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 4;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnNnz = NEW_INTEGER(1));
    nProtect += 1;
    pnNnz = INTEGER_POINTER(spnNnz);

    *pnErrorCode = LSgetNLPConstraintDatai(pModel,iCon,pnNnz,NULL,NULL);
    CHECK_ERRCODE;

    if(*pnNnz == 0)
    {
        goto ErrorReturn;
    }

    PROTECT(spaiNLPcols = NEW_INTEGER(*pnNnz));
    nProtect += 1;
    paiNLPcols = INTEGER_POINTER(spaiNLPcols);

    PROTECT(spadNLPcoef = NEW_NUMERIC(*pnNnz));
    nProtect += 1;
    padNLPcoef = NUMERIC_POINTER(spadNLPcoef);

    *pnErrorCode = LSgetNLPConstraintDatai(pModel,iCon,NULL,paiNLPcols,padNLPcoef);
    CHECK_ERRCODE;

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnNnz);
        SET_VECTOR_ELT(rList, 2, spaiNLPcols);
        SET_VECTOR_ELT(rList, 3, spadNLPcoef);
    }

    UNPROTECT(nProtect + 2);
   
    return rList;
}

SEXP rcLSgetNLPVariableDataj(SEXP  sModel,
                             SEXP  siVar)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iVar = Rf_asInteger(siVar);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnNnz;
    SEXP      spnNnz = R_NilValue;
    int       *panNLProws;
    SEXP      spanNLProws = R_NilValue;
    double    *padNLPcoef;
    SEXP      spadNLPcoef = R_NilValue;

    SEXP      rList = R_NilValue;
    char      *Names[4] = {"ErrorCode", "pnNnz","panNLProws","padNLPcoef"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 4;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnNnz = NEW_INTEGER(1));
    nProtect += 1;
    pnNnz = INTEGER_POINTER(spnNnz);

    *pnErrorCode = LSgetNLPVariableDataj(pModel,iVar,pnNnz,NULL,NULL);
    CHECK_ERRCODE;

    if(*pnNnz == 0)
    {
        goto ErrorReturn;
    }

    PROTECT(spanNLProws = NEW_INTEGER(*pnNnz));
    nProtect += 1;
    panNLProws = INTEGER_POINTER(spanNLProws);

    PROTECT(spadNLPcoef = NEW_NUMERIC(*pnNnz));
    nProtect += 1;
    padNLPcoef = NUMERIC_POINTER(spadNLPcoef);

    *pnErrorCode = LSgetNLPVariableDataj(pModel,iVar,NULL,panNLProws,padNLPcoef);
    CHECK_ERRCODE;

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnNnz);
        SET_VECTOR_ELT(rList, 2, spanNLProws);
        SET_VECTOR_ELT(rList, 3, spadNLPcoef);
    }

    UNPROTECT(nProtect + 2);
   
    return rList;
}

SEXP rcLSgetNLPObjectiveData(SEXP  sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnNLPobjnnz;
    SEXP      spnNLPobjnnz = R_NilValue;
    int       *paiNLPobj;
    SEXP      spaiNLPobj = R_NilValue;
    double    *padNLPobj;
    SEXP      spadNLPobj = R_NilValue;

    SEXP      rList = R_NilValue;
    char      *Names[4] = {"ErrorCode", "pnNLPobjnnz","paiNLPobj","padNLPobj"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 4;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnNLPobjnnz = NEW_INTEGER(1));
    nProtect += 1;
    pnNLPobjnnz = INTEGER_POINTER(spnNLPobjnnz);

    *pnErrorCode = LSgetNLPObjectiveData(pModel,pnNLPobjnnz,NULL,NULL);
    CHECK_ERRCODE;

    if(*pnNLPobjnnz == 0)
    {
        goto ErrorReturn;
    }

    PROTECT(spaiNLPobj = NEW_INTEGER(*pnNLPobjnnz));
    nProtect += 1;
    paiNLPobj = INTEGER_POINTER(spaiNLPobj);

    PROTECT(spadNLPobj = NEW_NUMERIC(*pnNLPobjnnz));
    nProtect += 1;
    padNLPobj = NUMERIC_POINTER(spadNLPobj);

    *pnErrorCode = LSgetNLPObjectiveData(pModel,NULL,paiNLPobj,padNLPobj);
    CHECK_ERRCODE;

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnNLPobjnnz);
        SET_VECTOR_ELT(rList, 2, spaiNLPobj);
        SET_VECTOR_ELT(rList, 3, spadNLPobj);
    }

    UNPROTECT(nProtect + 2);
   
    return rList;
}

SEXP rcLSgetDualModel(SEXP sModel,
                      SEXP sDualModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    prLSmodel prDualModel;
    pLSmodel  pDualModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    if(sDualModel != R_NilValue && R_ExternalPtrTag(sDualModel) == tagLSprob)
    {
        prDualModel = (prLSmodel)R_ExternalPtrAddr(sDualModel);
        pDualModel = prDualModel->pModel;
    }
    else
    {
        *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;
        goto ErrorReturn;
    }

    *pnErrorCode = LSgetDualModel(pModel,pDualModel);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLScalinfeasMIPsolution(SEXP sModel,
                              SEXP spadPrimalMipsol)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    double    *padPrimalMipsol = REAL(spadPrimalMipsol);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdIntPfeas;
    SEXP      spdIntPfeas = R_NilValue;
    double    *pbConsPfeas;
    SEXP      spbConsPfeas = R_NilValue;

    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode", "pdIntPfeas", "pbConsPfeas"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    MAKE_REAL_ARRAY(padPrimalMipsol,spadPrimalMipsol);

    PROTECT(spdIntPfeas = NEW_NUMERIC(1));
    nProtect += 1;
    pdIntPfeas = NUMERIC_POINTER(spdIntPfeas);

    PROTECT(spbConsPfeas = NEW_NUMERIC(1));
    nProtect += 1;
    pbConsPfeas = NUMERIC_POINTER(spbConsPfeas);

    *pnErrorCode = LScalinfeasMIPsolution(pModel,pdIntPfeas,
                                          pbConsPfeas,padPrimalMipsol);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdIntPfeas);
        SET_VECTOR_ELT(rList, 2, spbConsPfeas);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetRoundMIPsolution(SEXP      sModel,
                             SEXP      spadPrimal,
                             SEXP      siUseOpti)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    double    *padPrimal;
    int       iUseOpti = Rf_asInteger(siUseOpti);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padPrimalRound;
    SEXP      spadPrimalRound = R_NilValue;
    double    *pdObjRound;
    SEXP      spdObjRound = R_NilValue;
    double    *pdPfeasRound;
    SEXP      spdPfeasRound = R_NilValue;
    int       *pnstatus;
    SEXP      spnstatus = R_NilValue;

    SEXP      rList = R_NilValue;
    char      *Names[5] = {"ErrorCode", "padPrimalRound", "pdObjRound", "pdPfeasRound", "pnstatus"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 5;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    MAKE_REAL_ARRAY(padPrimal,spadPrimal);

    PROTECT(spadPrimalRound = NEW_NUMERIC(nVars));
    nProtect += 1;
    padPrimalRound = NUMERIC_POINTER(spadPrimalRound);

    PROTECT(spdObjRound = NEW_NUMERIC(1));
    nProtect += 1;
    pdObjRound = NUMERIC_POINTER(spdObjRound);

    PROTECT(spdPfeasRound = NEW_NUMERIC(1));
    nProtect += 1;
    pdPfeasRound = NUMERIC_POINTER(spdPfeasRound);

    PROTECT(spnstatus = NEW_INTEGER(1));
    nProtect += 1;
    pnstatus = INTEGER_POINTER(spnstatus);

    *pnErrorCode = LSgetRoundMIPsolution(pModel,
                                         padPrimal,
                                         padPrimalRound,
                                         pdObjRound,
                                         pdPfeasRound,
                                         pnstatus,
                                         iUseOpti);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadPrimalRound);
        SET_VECTOR_ELT(rList, 2, spdObjRound);
        SET_VECTOR_ELT(rList, 3, spdPfeasRound);
        SET_VECTOR_ELT(rList, 4, spnstatus);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetRangeData(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padR;
    SEXP      spadR = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "padR"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_CONS,&nCons);
    CHECK_ERRCODE;

    PROTECT(spadR = NEW_NUMERIC(nCons));
    nProtect += 1;
    padR = NUMERIC_POINTER(spadR);

    *pnErrorCode = LSgetRangeData(pModel,padR);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadR);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

/********************************************************
* Model Modification Routines (25)                      *
*********************************************************/
SEXP rcLSaddConstraints(SEXP      sModel,
                        SEXP      snNumaddcons,
                        SEXP      spszConTypes,
                        SEXP      spaszConNames,
                        SEXP      spaiArows,
                        SEXP      spadAcoef,
                        SEXP      spaiAcols,
                        SEXP      spadB)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nNumaddcons = Rf_asInteger(snNumaddcons);
    char      *pszConTypes = (char *) CHAR(STRING_ELT(spszConTypes,0));
    char      **paszConNames;
    int       *paiArows = INTEGER(spaiArows);
    double    *padAcoef = REAL(spadAcoef);
    int       *paiAcols = INTEGER(spaiAcols);
    double    *padB = REAL(spadB);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    MAKE_CHAR_CHAR_ARRAY(paszConNames,spaszConNames);

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;
    
    *pnErrorCode = LSaddConstraints(pModel,
                                    nNumaddcons,
                                    pszConTypes,
                                    paszConNames,
                                    paiArows,
                                    padAcoef,
                                    paiAcols,
                                    padB);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSaddVariables(SEXP      sModel,
                      SEXP      snNumaddvars,
                      SEXP      spszVarTypes,
                      SEXP      spaszVarNames,
                      SEXP      spaiAcols,
                      SEXP      spanAcols,
                      SEXP      spadAcoef,
                      SEXP      spaiArows,
                      SEXP      spadC,
                      SEXP      spadL,
                      SEXP      spadU)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nNumaddvars = Rf_asInteger(snNumaddvars);
    char      *pszVarTypes = (char *) CHAR(STRING_ELT(spszVarTypes,0));
    char      **paszVarNames;
    int       *paiAcols = INTEGER(spaiAcols);
    int       *panAcols;
    double    *padAcoef = REAL(spadAcoef);
    int       *paiArows = INTEGER(spaiArows);
    double    *padC = REAL(spadC);
    double    *padL;
    double    *padU;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    MAKE_CHAR_CHAR_ARRAY(paszVarNames,spaszVarNames);
    MAKE_INT_ARRAY(panAcols,spanAcols);
    MAKE_REAL_ARRAY(padL,spadL);
    MAKE_REAL_ARRAY(padU,spadU);

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddVariables(pModel,
                                  nNumaddvars,
                                  pszVarTypes,
                                  paszVarNames,
                                  paiAcols,
                                  panAcols,
                                  padAcoef,
                                  paiArows,
                                  padC,
                                  padL,
                                  padU);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSaddCones(SEXP      sModel,
                  SEXP      snCone,
                  SEXP      spszConeTypes,
                  SEXP      spaszConenames,
                  SEXP      spaiConebegcol,
                  SEXP      spaiConecols)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nCone = Rf_asInteger(snCone);
    char      *pszConeTypes = (char *) CHAR(STRING_ELT(spszConeTypes,0));
    char      **paszConenames;
    int       *paiConebegcol = INTEGER(spaiConebegcol);
    int       *paiConecols = INTEGER(spaiConecols);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    MAKE_CHAR_CHAR_ARRAY(paszConenames,spaszConenames);

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddCones(pModel,
                              nCone,
                              pszConeTypes,
                              paszConenames,
                              paiConebegcol,
                              paiConecols);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSaddSETS(SEXP      sModel,
                 SEXP      snSETS,
                 SEXP      spszSETStype,
                 SEXP      spaiCARDnum,
                 SEXP      spaiSETSbegcol,
                 SEXP      spaiSETScols)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nSETS = Rf_asInteger(snSETS);
    char      *pszSETStype = (char *) CHAR(STRING_ELT(spszSETStype,0));
    int       *paiCARDnum = INTEGER(spaiCARDnum);
    int       *paiSETSbegcol = INTEGER(spaiSETSbegcol);
    int       *paiSETScols = INTEGER(spaiSETScols);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddSETS(pModel,
                             nSETS,
                             pszSETStype,
                             paiCARDnum,
                             paiSETSbegcol,
                             paiSETScols);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSaddQCterms(SEXP      sModel,
                    SEXP      snQCnonzeros,
                    SEXP      spaiQCconndx,
                    SEXP      spaiQCvarndx1,
                    SEXP      spaiQCvarndx2,
                    SEXP      spadQCcoef)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQCnonzeros = Rf_asInteger(snQCnonzeros);
    int       *paiQCconndx = INTEGER(spaiQCconndx);
    int       *paiQCvarndx1 = INTEGER(spaiQCvarndx1);
    int       *paiQCvarndx2 = INTEGER(spaiQCvarndx2);
    double    *padQCcoef = REAL(spadQCcoef);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddQCterms(pModel,
                                nQCnonzeros,
                                paiQCconndx,
                                paiQCvarndx1,
                                paiQCvarndx2,
                                padQCcoef);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSdeleteConstraints(SEXP      sModel,
                           SEXP      snCons,
                           SEXP      spaiCons)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nCons = Rf_asInteger(snCons);
    int       *paiCons = INTEGER(spaiCons);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSdeleteConstraints(pModel,nCons,paiCons);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSdeleteSETS(SEXP      sModel,
                    SEXP      snSETS,
                    SEXP      spaiSETS)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nSETS = Rf_asInteger(snSETS);
    int       *paiSETS = INTEGER(spaiSETS);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSdeleteSETS(pModel,nSETS,paiSETS);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSdeleteCones(SEXP      sModel,
                     SEXP      snCones,
                     SEXP      spaiCones)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nCones = Rf_asInteger(snCones);
    int       *paiCones = INTEGER(spaiCones);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSdeleteCones(pModel,nCones,paiCones);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSdeleteSemiContVars(SEXP      sModel,
                            SEXP      snSCVars,
                            SEXP      spaiSCVars)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nSCVars = Rf_asInteger(snSCVars);
    int       *paiSCVars = INTEGER(spaiSCVars);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSdeleteSemiContVars(pModel,nSCVars,paiSCVars);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSdeleteVariables(SEXP      sModel,
                         SEXP      snVars,
                         SEXP      spaiVars)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nVars = Rf_asInteger(snVars);
    int       *paiVars = INTEGER(spaiVars);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSdeleteVariables(pModel,nVars,paiVars);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSdeleteQCterms(SEXP      sModel,
                       SEXP      snCons,
                       SEXP      spaiCons)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nCons = Rf_asInteger(snCons);
    int       *paiCons = INTEGER(spaiCons);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSdeleteQCterms(pModel,nCons,paiCons);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSdeleteAj(SEXP      sModel,
                  SEXP      siVar1,
                  SEXP      snRows,
                  SEXP      spaiRows)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iVar1 = Rf_asInteger(siVar1);
    int       nRows = Rf_asInteger(snRows);
    int       *paiRows = INTEGER(spaiRows);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSdeleteAj(pModel,iVar1,nRows,paiRows);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSmodifyLowerBounds(SEXP      sModel,
                           SEXP      snVars,
                           SEXP      spaiVars,
                           SEXP      spadL)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nVars = Rf_asInteger(snVars);
    int       *paiVars = INTEGER(spaiVars);
    double    *padL = REAL(spadL);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSmodifyLowerBounds(pModel,nVars,paiVars,padL);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSmodifyUpperBounds(SEXP      sModel,
                           SEXP      snVars,
                           SEXP      spaiVars,
                           SEXP      spadU)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nVars = Rf_asInteger(snVars);
    int       *paiVars = INTEGER(spaiVars);
    double    *padU = REAL(spadU);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSmodifyUpperBounds(pModel,nVars,paiVars,padU);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSmodifyRHS(SEXP      sModel,
                   SEXP      snCons,
                   SEXP      spaiCons,
                   SEXP      spadB)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nCons = Rf_asInteger(snCons);
    int       *paiCons = INTEGER(spaiCons);
    double    *padB = REAL(spadB);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSmodifyRHS(pModel,nCons,paiCons,padB);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSmodifyObjective(SEXP      sModel,
                         SEXP      snVars,
                         SEXP      spaiVars,
                         SEXP      spadC)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nVars = Rf_asInteger(snVars);
    int       *paiVars = INTEGER(spaiVars);
    double    *padC = REAL(spadC);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSmodifyObjective(pModel,nVars,paiVars,padC);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSmodifyAj(SEXP     sModel,
                  SEXP     siVar1,
                  SEXP     snRows,
                  SEXP     spaiRows,
                  SEXP     spadAj)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iVar1 = Rf_asInteger(siVar1);
    int       nRows = Rf_asInteger(snRows);
    int       *paiRows = INTEGER(spaiRows);
    double    *padAj = REAL(spadAj);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSmodifyAj(pModel,iVar1,nRows,paiRows,padAj);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSmodifyCone(SEXP     sModel,
                    SEXP     scConeType,
                    SEXP     siConeNum,
                    SEXP     siConeNnz,
                    SEXP     spaiConeCols)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      cConeType = *((char *)CHAR(STRING_ELT(scConeType,0)));
    int       iConeNum = Rf_asInteger(siConeNum);
    int       iConeNnz = Rf_asInteger(siConeNnz);
    int       *paiConeCols = INTEGER(spaiConeCols);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSmodifyCone(pModel,cConeType,iConeNum,iConeNnz,paiConeCols);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSmodifySET(SEXP     sModel,
                   SEXP     scSETtype,
                   SEXP     siSETnum,
                   SEXP     siSETnnz,
                   SEXP     spaiSETcols)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      cSETtype = *((char *)CHAR(STRING_ELT(scSETtype,0)));
    int       iSETnum = Rf_asInteger(siSETnum);
    int       iSETnnz = Rf_asInteger(siSETnnz);
    int       *paiSETcols = INTEGER(spaiSETcols);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSmodifySET(pModel,cSETtype,iSETnum,iSETnnz,paiSETcols);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSmodifySemiContVars(SEXP     sModel,
                            SEXP     snSCVars,
                            SEXP     spaiSCVars,
                            SEXP     spadL,
                            SEXP     spadU)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nSCVars = Rf_asInteger(snSCVars);
    int       *paiSCVars = INTEGER(spaiSCVars);
    double    *padL = REAL(spadL);
    double    *padU = REAL(spadU);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSmodifySemiContVars(pModel,nSCVars,paiSCVars,padL,padU);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSmodifyConstraintType(SEXP     sModel,
                              SEXP     snCons,
                              SEXP     spaiCons,
                              SEXP     spszConTypes)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       nCons = Rf_asInteger(snCons);
    int       *paiCons = INTEGER(spaiCons);
    char      *pszConTypes = (char *)CHAR(STRING_ELT(spszConTypes,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSmodifyConstraintType(pModel,nCons,paiCons,pszConTypes);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSmodifyVariableType(SEXP     sModel,
                            SEXP     snVars,
                            SEXP     spaiVars,
                            SEXP     spszVarTypes)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       nVars = Rf_asInteger(snVars);
    int       *paiVars = INTEGER(spaiVars);
    char      *pszVarTypes = (char *)CHAR(STRING_ELT(spszVarTypes,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSmodifyVariableType(pModel,nVars,paiVars,pszVarTypes);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSaddNLPAj(SEXP     sModel,
                  SEXP     siVar1,
                  SEXP     snRows,
                  SEXP     spaiRows,
                  SEXP     spadAj)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iVar1 = Rf_asInteger(siVar1);
    int       nRows = Rf_asInteger(snRows);
    int       *paiRows = INTEGER(spaiRows);
    double    *padAj = REAL(spadAj);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddNLPAj(pModel,iVar1,nRows,paiRows,padAj);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSaddNLPobj(SEXP      sModel,
                   SEXP      snCols,
                   SEXP      spaiCols,
                   SEXP      spadColj)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nCols = Rf_asInteger(snCols);
    int       *paiCols = INTEGER(spaiCols);
    double    *padColj = REAL(spadColj);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddNLPobj(pModel,nCols,paiCols,padColj);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSdeleteNLPobj(SEXP      sModel,
                      SEXP      snCols,
                      SEXP      spaiCols)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nCols = Rf_asInteger(snCols);
    int       *paiCols = INTEGER(spaiCols);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSdeleteNLPobj(pModel,nCols,paiCols);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

/********************************************************
* Model & Solution Analysis Routines (10)               *
*********************************************************/
SEXP rcLSgetConstraintRanges(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padDec;
    SEXP      spadDec = R_NilValue;
    double    *padInc;
    SEXP      spadInc = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode", "padDec", "padInc"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;
    int       nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_CONS,&nCons);
    CHECK_ERRCODE;

    PROTECT(spadDec = NEW_NUMERIC(nCons));
    nProtect += 1;
    padDec = NUMERIC_POINTER(spadDec);

    PROTECT(spadInc = NEW_NUMERIC(nCons));
    nProtect += 1;
    padInc = NUMERIC_POINTER(spadInc);

    *pnErrorCode = LSgetConstraintRanges(pModel,padDec,padInc);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadDec);
        SET_VECTOR_ELT(rList, 2, spadInc);
    }
            
    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetObjectiveRanges(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padDec;
    SEXP      spadDec = R_NilValue;
    double    *padInc;
    SEXP      spadInc = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode", "padDec", "padInc"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadDec = NEW_NUMERIC(nVars));
    nProtect += 1;
    padDec = NUMERIC_POINTER(spadDec);

    PROTECT(spadInc = NEW_NUMERIC(nVars));
    nProtect += 1;
    padInc = NUMERIC_POINTER(spadInc);

    *pnErrorCode = LSgetObjectiveRanges(pModel,padDec,padInc);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadDec);
        SET_VECTOR_ELT(rList, 2, spadInc);
    }
            
    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetBoundRanges(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padDec;
    SEXP      spadDec = R_NilValue;
    double    *padInc;
    SEXP      spadInc = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode", "padDec", "padInc"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadDec = NEW_NUMERIC(nVars));
    nProtect += 1;
    padDec = NUMERIC_POINTER(spadDec);

    PROTECT(spadInc = NEW_NUMERIC(nVars));
    nProtect += 1;
    padInc = NUMERIC_POINTER(spadInc);

    *pnErrorCode = LSgetBoundRanges(pModel,padDec,padInc);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadDec);
        SET_VECTOR_ELT(rList, 2, spadInc);
    }
            
    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetBestBounds(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padBestL;
    SEXP      spadBestL = R_NilValue;
    double    *padBestU;
    SEXP      spadBestU = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode", "padBestL", "padBestU"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadBestL = NEW_NUMERIC(nVars));
    nProtect += 1;
    padBestL = NUMERIC_POINTER(spadBestL);

    PROTECT(spadBestU = NEW_NUMERIC(nVars));
    nProtect += 1;
    padBestU = NUMERIC_POINTER(spadBestU);

    *pnErrorCode = LSgetBestBounds(pModel,padBestL,padBestU);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadBestL);
        SET_VECTOR_ELT(rList, 2, spadBestU);
    }
            
    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSfindIIS(SEXP      sModel,
                 SEXP      snLevel)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nLevel = Rf_asInteger(snLevel);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSfindIIS(pModel,nLevel);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSfindIUS(SEXP      sModel,
                 SEXP      snLevel)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nLevel = Rf_asInteger(snLevel);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSfindIUS(pModel,nLevel);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSfindBlockStructure(SEXP      sModel,
                            SEXP      snBlock,
                            SEXP      snType)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nBlock = Rf_asInteger(snBlock);
    int       nType = Rf_asInteger(snType);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSfindBlockStructure(pModel,nBlock,nType);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetIIS(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnSuf_r;
    SEXP      spnSuf_r = R_NilValue;
    int       *pnIIS_r;
    SEXP      spnIIS_r = R_NilValue;
    int       *paiCons;
    SEXP      spaiCons = R_NilValue;
    int       *pnSuf_c;
    SEXP      spnSuf_c = R_NilValue;
    int       *pnIIS_c;
    SEXP      spnIIS_c = R_NilValue;
    int       *paiVars;
    SEXP      spaiVars = R_NilValue;
    int       *panBnds;
    SEXP      spanBnds = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[8] = {"ErrorCode","pnSuf_r","pnIIS_r","paiCons",
                           "pnSuf_c","pnIIS_c","paiVars", "panBnds"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 8;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnSuf_r = NEW_INTEGER(1));
    nProtect += 1;
    pnSuf_r = INTEGER_POINTER(spnSuf_r);

    PROTECT(spnIIS_r = NEW_INTEGER(1));
    nProtect += 1;
    pnIIS_r = INTEGER_POINTER(spnIIS_r);

    PROTECT(spnSuf_c = NEW_INTEGER(1));
    nProtect += 1;
    pnSuf_c = INTEGER_POINTER(spnSuf_c);

    PROTECT(spnIIS_c = NEW_INTEGER(1));
    nProtect += 1;
    pnIIS_c = INTEGER_POINTER(spnIIS_c);

    *pnErrorCode = LSgetIIS(pModel,pnSuf_r,pnIIS_r,NULL,pnSuf_c,pnIIS_c,NULL,NULL);
    CHECK_ERRCODE;

    PROTECT(spaiCons = NEW_INTEGER(*pnIIS_r));
    nProtect += 1;
    paiCons = INTEGER_POINTER(spaiCons);

    PROTECT(spaiVars = NEW_INTEGER(*pnIIS_c));
    nProtect += 1;
    paiVars = INTEGER_POINTER(spaiVars);

    PROTECT(spanBnds = NEW_INTEGER(*pnIIS_c));
    nProtect += 1;
    panBnds = INTEGER_POINTER(spanBnds);

    *pnErrorCode = LSgetIIS(pModel,NULL,NULL,paiCons,NULL,NULL,paiVars,panBnds);
    CHECK_ERRCODE;

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnSuf_r);
        SET_VECTOR_ELT(rList, 2, spnIIS_r);
        SET_VECTOR_ELT(rList, 3, spaiCons);
        SET_VECTOR_ELT(rList, 4, spnSuf_c);
        SET_VECTOR_ELT(rList, 5, spnIIS_c);
        SET_VECTOR_ELT(rList, 6, spaiVars);
        SET_VECTOR_ELT(rList, 7, spanBnds);
    }
            
    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetIUS(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnSuf;
    SEXP      spnSuf = R_NilValue;
    int       *pnIUS;
    SEXP      spnIUS = R_NilValue;
    int       *paiVars;
    SEXP      spaiVars = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[4] = {"ErrorCode","pnSuf","pnIUS","paiVars"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 4;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnSuf = NEW_INTEGER(1));
    nProtect += 1;
    pnSuf = INTEGER_POINTER(spnSuf);

    PROTECT(spnIUS = NEW_INTEGER(1));
    nProtect += 1;
    pnIUS = INTEGER_POINTER(spnIUS);

    *pnErrorCode = LSgetIUS(pModel,pnSuf,pnIUS,NULL);
    CHECK_ERRCODE;

    PROTECT(spaiVars = NEW_INTEGER(*pnIUS));
    nProtect += 1;
    paiVars = INTEGER_POINTER(spaiVars);

    *pnErrorCode = LSgetIUS(pModel,NULL,NULL,paiVars);
    CHECK_ERRCODE;

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnSuf);
        SET_VECTOR_ELT(rList, 2, spnIUS);
        SET_VECTOR_ELT(rList, 3, spaiVars);
    }
            
    UNPROTECT(nProtect + 2);
    
    return rList;
}

SEXP rcLSgetBlockStructure(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnBlock;
    SEXP      spnBlock = R_NilValue;
    int       *panRblock;
    SEXP      spanRblock = R_NilValue;
    int       *panCblock;
    SEXP      spanCblock = R_NilValue;
    int       *pnType;
    SEXP      spnType = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[5] = {"ErrorCode","pnBlock","panRblock","panCblock","pnType"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 5;
    int       nIdx, nProtect = 0;
    int       nVars, nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;
    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_CONS,&nCons);
    CHECK_ERRCODE;

    PROTECT(spnBlock = NEW_INTEGER(1));
    nProtect += 1;
    pnBlock = INTEGER_POINTER(spnBlock);

    PROTECT(spanRblock = NEW_INTEGER(nCons));
    nProtect += 1;
    panRblock = INTEGER_POINTER(spanRblock);

    PROTECT(spanCblock = NEW_INTEGER(nVars));
    nProtect += 1;
    panCblock = INTEGER_POINTER(spanCblock);

    PROTECT(spnType = NEW_INTEGER(1));
    nProtect += 1;
    pnType = INTEGER_POINTER(spnType);

    *pnErrorCode = LSgetBlockStructure(pModel,pnBlock,panRblock,panCblock,pnType);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnBlock);
        SET_VECTOR_ELT(rList, 2, spanRblock);
        SET_VECTOR_ELT(rList, 3, spanCblock);
        SET_VECTOR_ELT(rList, 4, spnType);
    }
            
    UNPROTECT(nProtect + 2);
    
    return rList;
}

/********************************************************
* Advanced Routines (0)                                 *
*********************************************************/

/********************************************************
* Callback Management Routines(0)                       *
*********************************************************/

/********************************************************
* Memory Related Routines(9)                            *
*********************************************************/
SEXP rcLSfreeSolverMemory(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    LSfreeSolverMemory(pModel);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSfreeHashMemory(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    LSfreeHashMemory(pModel);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSfreeSolutionMemory(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    LSfreeSolutionMemory(pModel);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSfreeMIPSolutionMemory(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    LSfreeMIPSolutionMemory(pModel);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSfreeGOPSolutionMemory(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    LSfreeGOPSolutionMemory(pModel);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetProbAllocSizes(SEXP      sModel,
                           SEXP      sn_vars_alloc,
                           SEXP      sn_cons_alloc,
                           SEXP      sn_QC_alloc,
                           SEXP      sn_Annz_alloc,
                           SEXP      sn_Qnnz_alloc,
                           SEXP      sn_NLPnnz_alloc)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       n_vars_alloc = Rf_asInteger(sn_vars_alloc);
    int       n_cons_alloc = Rf_asInteger(sn_cons_alloc);
    int       n_QC_alloc = Rf_asInteger(sn_QC_alloc);
    int       n_Annz_alloc = Rf_asInteger(sn_Annz_alloc);
    int       n_Qnnz_alloc = Rf_asInteger(sn_Qnnz_alloc);
    int       n_NLPnnz_alloc = Rf_asInteger(sn_NLPnnz_alloc);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSsetProbAllocSizes(pModel,
                                       n_vars_alloc,
                                       n_cons_alloc,
                                       n_QC_alloc,
                                       n_Annz_alloc,
                                       n_Qnnz_alloc,
                                       n_NLPnnz_alloc);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetProbNameAllocSizes(SEXP      sModel,
                               SEXP      sn_varname_alloc,
                               SEXP      sn_rowname_alloc)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       n_varname_alloc = Rf_asInteger(sn_varname_alloc);
    int       n_rowname_alloc = Rf_asInteger(sn_rowname_alloc);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSsetProbNameAllocSizes(pModel,
                                           n_varname_alloc,
                                           n_rowname_alloc);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSaddEmptySpacesAcolumns(SEXP      sModel,
                                SEXP      spaiColnnz)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       *paiColnnz = INTEGER(spaiColnnz);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddEmptySpacesAcolumns(pModel,
                                            paiColnnz);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSaddEmptySpacesNLPAcolumns(SEXP      sModel,
                                   SEXP      spaiColnnz)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       *paiColnnz = INTEGER(spaiColnnz);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddEmptySpacesNLPAcolumns(pModel,
                                               paiColnnz);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

/********************************************************
* new  callback functions from version 5.+ (0)          *
*********************************************************/

/********************************************************
* new  functions from version 5.+ (0)                   *
*********************************************************/

/********************************************************
* Stochastic Programming Interface (88)                 *
*********************************************************/
SEXP rcLSwriteDeteqMPSFile(SEXP      sModel,
                           SEXP      spszFilename,
                           SEXP      snFormat,
                           SEXP      siType)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pszFilename = (char *)CHAR(STRING_ELT(spszFilename,0));
    int       nFormat = Rf_asInteger(snFormat);
    int       iType = Rf_asInteger(siType);
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteDeteqMPSFile(pModel,pszFilename,nFormat,iType);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteDeteqLINDOFile(SEXP      sModel,
                             SEXP      spszFilename,
                             SEXP      siType)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pszFilename = (char *)CHAR(STRING_ELT(spszFilename,0));
    int       iType = Rf_asInteger(siType);
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteDeteqLINDOFile(pModel,pszFilename,iType);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteSMPSFile(SEXP      sModel,
                       SEXP      spszCorefile,
                       SEXP      spszTimefile,
                       SEXP      spszStocfile,
                       SEXP      snMPStype)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszCorefile = (char *)CHAR(STRING_ELT(spszCorefile,0));
    char      *pszTimefile = (char *)CHAR(STRING_ELT(spszTimefile,0));
    char      *pszStocfile = (char *)CHAR(STRING_ELT(spszStocfile,0));
    int       nMPStype = Rf_asInteger(snMPStype);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteSMPSFile(pModel,pszCorefile,pszTimefile,pszStocfile,nMPStype);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSreadSMPSFile(SEXP      sModel,
                      SEXP      spszCorefile,
                      SEXP      spszTimefile,
                      SEXP      spszStocfile,
                      SEXP      snMPStype)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszCorefile = (char *)CHAR(STRING_ELT(spszCorefile,0));
    char      *pszTimefile = (char *)CHAR(STRING_ELT(spszTimefile,0));
    char      *pszStocfile = (char *)CHAR(STRING_ELT(spszStocfile,0));
    int       nMPStype = Rf_asInteger(snMPStype);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSreadSMPSFile(pModel,pszCorefile,pszTimefile,pszStocfile,nMPStype);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteSMPIFile(SEXP      sModel,
                       SEXP      spszCorefile,
                       SEXP      spszTimefile,
                       SEXP      spszStocfile)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszCorefile = (char *)CHAR(STRING_ELT(spszCorefile,0));
    char      *pszTimefile = (char *)CHAR(STRING_ELT(spszTimefile,0));
    char      *pszStocfile = (char *)CHAR(STRING_ELT(spszStocfile,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteSMPIFile(pModel,pszCorefile,pszTimefile,pszStocfile);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSreadSMPIFile(SEXP      sModel,
                      SEXP      spszCorefile,
                      SEXP      spszTimefile,
                      SEXP      spszStocfile)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszCorefile = (char *)CHAR(STRING_ELT(spszCorefile,0));
    char      *pszTimefile = (char *)CHAR(STRING_ELT(spszTimefile,0));
    char      *pszStocfile = (char *)CHAR(STRING_ELT(spszStocfile,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSreadSMPIFile(pModel,pszCorefile,pszTimefile,pszStocfile);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteScenarioSolutionFile(SEXP      sModel,
                                   SEXP      sjScenario,
                                   SEXP      spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);
    char      *pszFname = (char *)CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteScenarioSolutionFile(pModel,jScenario,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteNodeSolutionFile(SEXP      sModel,
                               SEXP      sjScenario,
                               SEXP      siStage,
                               SEXP      spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);
    int       iStage = Rf_asInteger(siStage);
    char      *pszFname = (char *)CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteNodeSolutionFile(pModel,jScenario,iStage,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteScenarioMPIFile(SEXP      sModel,
                              SEXP      sjScenario,
                              SEXP      spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);
    char      *pszFname = (char *)CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteScenarioMPIFile(pModel,jScenario,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteScenarioMPSFile(SEXP      sModel,
                              SEXP      sjScenario,
                              SEXP      spszFname,
                              SEXP      snFormat)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);
    char      *pszFname = (char *)CHAR(STRING_ELT(spszFname,0));
    int       nFormat = Rf_asInteger(snFormat);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteScenarioMPSFile(pModel,jScenario,pszFname,nFormat);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSwriteScenarioLINDOFile(SEXP      sModel,
                                SEXP      sjScenario,
                                SEXP      spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);
    char      *pszFname = (char *)CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSwriteScenarioLINDOFile(pModel,jScenario,pszFname);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetModelStocDouParameter(SEXP      sModel,
                                  SEXP      siPar,
                                  SEXP      sdVal)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iPar = Rf_asInteger(siPar);
    double    dVal = Rf_asReal(sdVal);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSsetModelStocDouParameter(pModel,iPar,dVal);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetModelStocDouParameter(SEXP      sModel,
                                  SEXP      siPar)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iPar = Rf_asInteger(siPar);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdValue;
    SEXP      spdValue = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdValue"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spdValue = NEW_NUMERIC(1));
    nProtect += 1;
    pdValue = NUMERIC_POINTER(spdValue);

    *pnErrorCode = LSgetModelStocDouParameter(pModel,iPar,pdValue);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdValue);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetModelStocIntParameter(SEXP      sModel,
                                  SEXP      siPar,
                                  SEXP      siVal)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iPar = Rf_asInteger(siPar);
    int       iVal = Rf_asInteger(siVal);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSsetModelStocIntParameter(pModel,iPar,iVal);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetModelStocIntParameter(SEXP      sModel,
                                  SEXP      siPar)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iPar = Rf_asInteger(siPar);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *piValue;
    SEXP      spiValue = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","piValue"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spiValue = NEW_INTEGER(1));
    nProtect += 1;
    piValue = INTEGER_POINTER(spiValue);

    *pnErrorCode = LSgetModelStocIntParameter(pModel,iPar,piValue);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spiValue);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetScenarioIndex(SEXP      sModel,
                          SEXP      spszName)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszName = (char *)CHAR(STRING_ELT(spszName,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnIndex;
    SEXP      spnIndex = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pnIndex"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnIndex = NEW_INTEGER(1));
    nProtect += 1;
    pnIndex = INTEGER_POINTER(spnIndex);

    *pnErrorCode = LSgetScenarioIndex(pModel,pszName,pnIndex);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnIndex);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStageIndex(SEXP      sModel,
                       SEXP      spszName)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszName = (char *)CHAR(STRING_ELT(spszName,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnIndex;
    SEXP      spnIndex = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pnIndex"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnIndex = NEW_INTEGER(1));
    nProtect += 1;
    pnIndex = INTEGER_POINTER(spnIndex);

    *pnErrorCode = LSgetStageIndex(pModel,pszName,pnIndex);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnIndex);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStocParIndex(SEXP      sModel,
                         SEXP      spszName)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *pszName = (char *)CHAR(STRING_ELT(spszName,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnIndex;
    SEXP      spnIndex = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pnIndex"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnIndex = NEW_INTEGER(1));
    nProtect += 1;
    pnIndex = INTEGER_POINTER(spnIndex);

    *pnErrorCode = LSgetStocParIndex(pModel,pszName,pnIndex);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnIndex);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStocParName(SEXP      sModel,
                        SEXP      snIndex)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nIndex = Rf_asInteger(snIndex);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pachName;
    SEXP      spachName = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pachName"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spachName = NEW_CHARACTER(1));
    nProtect += 1;
    pachName = (char *)malloc(sizeof(char)*(256));

    *pnErrorCode = LSgetStocParName(pModel,nIndex,pachName);

    CHECK_ERRCODE;

    SET_STRING_ELT(spachName,0,mkChar(pachName)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spachName);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetScenarioName(SEXP      sModel,
                         SEXP      snIndex)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nIndex = Rf_asInteger(snIndex);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pachName;
    SEXP      spachName = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pachName"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spachName = NEW_CHARACTER(1));
    nProtect += 1;
    pachName = (char *)malloc(sizeof(char)*(256));

    *pnErrorCode = LSgetScenarioName(pModel,nIndex,pachName);

    CHECK_ERRCODE;

    SET_STRING_ELT(spachName,0,mkChar(pachName)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spachName);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStageName(SEXP      sModel,
                      SEXP      snIndex)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nIndex = Rf_asInteger(snIndex);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pachName;
    SEXP      spachName = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pachName"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spachName = NEW_CHARACTER(1));
    nProtect += 1;
    pachName = (char *)malloc(sizeof(char)*(256));

    *pnErrorCode = LSgetStageName(pModel,nIndex,pachName);

    CHECK_ERRCODE;

    SET_STRING_ELT(spachName,0,mkChar(pachName)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spachName);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStocIInfo(SEXP      sModel,
                      SEXP      snQuery,
                      SEXP      snParam)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);
    int       nParam = Rf_asInteger(snParam);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnResult;
    SEXP      spnResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pnResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnResult = NEW_INTEGER(1));
    nProtect += 1;
    pnResult = INTEGER_POINTER(spnResult);

    *pnErrorCode = LSgetStocInfo(pModel,nQuery,nParam,pnResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStocDInfo(SEXP      sModel,
                      SEXP      snQuery,
                      SEXP      snParam)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);
    int       nParam = Rf_asInteger(snParam);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdResult;
    SEXP      spdResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spdResult = NEW_NUMERIC(1));
    nProtect += 1;
    pdResult = NUMERIC_POINTER(spdResult);

    *pnErrorCode = LSgetStocInfo(pModel,nQuery,nParam,pdResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStocSInfo(SEXP      sModel,
                      SEXP      snQuery,
                      SEXP      snParam)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);
    int       nParam = Rf_asInteger(snParam);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pszResult;
    SEXP      spszResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pszResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spszResult = NEW_CHARACTER(1));
    nProtect += 1;
    pszResult = (char *)malloc(sizeof(char)*(256));

    *pnErrorCode = LSgetStocInfo(pModel,nQuery,nParam,pszResult);

    CHECK_ERRCODE;

    SET_STRING_ELT(spszResult,0,mkChar(pszResult)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spszResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStocCCPIInfo(SEXP      sModel,
                         SEXP      snQuery,
                         SEXP      snScenarioIndex,
                         SEXP      snCPPIndex)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);
    int       nScenarioIndex = Rf_asInteger(snScenarioIndex);
    int       nCPPIndex = Rf_asInteger(snCPPIndex);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnResult;
    SEXP      spnResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pnResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnResult = NEW_INTEGER(1));
    nProtect += 1;
    pnResult = INTEGER_POINTER(spnResult);

    *pnErrorCode = LSgetStocCCPInfo(pModel,nQuery,nScenarioIndex,nCPPIndex,pnResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStocCCPDInfo(SEXP      sModel,
                         SEXP      snQuery,
                         SEXP      snScenarioIndex,
                         SEXP      snCPPIndex)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);
    int       nScenarioIndex = Rf_asInteger(snScenarioIndex);
    int       nCPPIndex = Rf_asInteger(snCPPIndex);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdResult;
    SEXP      spdResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spdResult = NEW_NUMERIC(1));
    nProtect += 1;
    pdResult = NUMERIC_POINTER(spdResult);

    *pnErrorCode = LSgetStocCCPInfo(pModel,nQuery,nScenarioIndex,nCPPIndex,pdResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStocCCPSInfo(SEXP      sModel,
                         SEXP      snQuery,
                         SEXP      snScenarioIndex,
                         SEXP      snCPPIndex)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);
    int       nScenarioIndex = Rf_asInteger(snScenarioIndex);
    int       nCPPIndex = Rf_asInteger(snCPPIndex);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      *pszResult;
    SEXP      spszResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pszResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spszResult = NEW_CHARACTER(1));
    nProtect += 1;
    pszResult = (char *)malloc(sizeof(char)*(256));

    *pnErrorCode = LSgetStocCCPInfo(pModel,nQuery,nScenarioIndex,nCPPIndex,pszResult);

    CHECK_ERRCODE;

    SET_STRING_ELT(spszResult,0,mkChar(pszResult)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spszResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadSampleSizes(SEXP      sModel,
                         SEXP      spanSampleSize)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       *panSampleSize = INTEGER(spanSampleSize);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadSampleSizes(pModel,panSampleSize);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadConstraintStages(SEXP      sModel,
                              SEXP      spanStage)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       *panStage = INTEGER(spanStage);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadConstraintStages(pModel,panStage);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadVariableStages(SEXP      sModel,
                            SEXP      spanStage)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       *panStage = INTEGER(spanStage);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadVariableStages(pModel,panStage);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadStageData(SEXP      sModel,
                       SEXP      snumStages,
                       SEXP      spanRstage,
                       SEXP      spanCstage)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       numStages = Rf_asInteger(snumStages);
    int       *panRstage = INTEGER(spanRstage);
    int       *panCstage = INTEGER(spanCstage);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadStageData(pModel,numStages,panRstage,panCstage);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadStocParData(SEXP      sModel,
                         SEXP      spanSparStage,
                         SEXP      spadSparValue)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       *panSparStage = INTEGER(spanSparStage);
    double    *padSparValue = REAL(spadSparValue);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadStocParData(pModel,panSparStage,padSparValue);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadStocParNames(SEXP      sModel,
                          SEXP      snSvars,
                          SEXP      spaszSVarNames)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nSvars = Rf_asInteger(snSvars);
    char      **paszSVarNames;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    MAKE_CHAR_CHAR_ARRAY(paszSVarNames,spaszSVarNames);

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadStocParNames(pModel,nSvars,paszSVarNames);

ErrorReturn:
    //allocate list
    SET_UP_LIST;

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetDeteqModel(SEXP      sModel,
                       SEXP      siDeqType)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iDeqType = Rf_asInteger(siDeqType);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    prLSmodel prdModel = NULL;
    SEXP      sprdModel = R_NilValue;
    int       nProtect = 0;
   
    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    prdModel = (prLSmodel)malloc(sizeof(rLSmodel)*1);
    if(prdModel == NULL)
    {
        return R_NilValue;
    }

    prdModel->pModel = LSgetDeteqModel(pModel,iDeqType,pnErrorCode);
    CHECK_ERRCODE;

    SET_PRINT_LOG(prdModel->pModel,*pnErrorCode);
    CHECK_ERRCODE;

    SET_MODEL_CALLBACK(prdModel->pModel,*pnErrorCode);
    CHECK_ERRCODE;

    sprdModel = R_MakeExternalPtr(prdModel,R_NilValue,R_NilValue);

    R_SetExternalPtrTag(sprdModel,tagLSprob);

ErrorReturn:

    UNPROTECT(nProtect);

    if(*pnErrorCode)
    {
        Rprintf("\nFail to get DeteqModel (error %d)\n",*pnErrorCode);
        R_FlushConsole();
        return R_NilValue;
    }
    else
    {
        return sprdModel;
    }
}

SEXP rcLSaggregateStages(SEXP      sModel,
                         SEXP      spanScheme,
                         SEXP      snLength)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       *panScheme = INTEGER(spanScheme);
    int       nLength = Rf_asInteger(snLength);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaggregateStages(pModel,panScheme,nLength);

    prModel->pModel = NULL;

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStageAggScheme(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *panScheme;
    SEXP      spanScheme = R_NilValue;
    int       *pnLength;
    SEXP      spnLength = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode","panScheme","pnLength"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnLength = NEW_INTEGER(1));
    nProtect += 1;
    pnLength = INTEGER_POINTER(spnLength);

    *pnErrorCode = LSgetStageAggScheme(pModel,NULL,pnLength);
    CHECK_ERRCODE;

    PROTECT(spanScheme = NEW_INTEGER(*pnLength));
    nProtect += 1;
    panScheme = INTEGER_POINTER(spanScheme);

    *pnErrorCode = LSgetStageAggScheme(pModel,panScheme,NULL);
    CHECK_ERRCODE;

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spanScheme);
        SET_VECTOR_ELT(rList, 2, spnLength);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSdeduceStages(SEXP      sModel,
                      SEXP      snMaxStage,
                      SEXP      spanRowStagesIn,
                      SEXP      spanColStagesIn,
                      SEXP      spanSparStage)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nMaxStage = Rf_asInteger(snMaxStage);
    int       *panRowStagesIn = INTEGER(spanRowStagesIn);
    int       *panColStagesIn = INTEGER(spanColStagesIn);
    int       *panSparStage = INTEGER(spanSparStage);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *panRowStagesOut;
    SEXP      spanRowStagesOut = R_NilValue;
    int       *panColStagesOut;
    SEXP      spanColStagesOut = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode","panRowStagseOut","panColStagesOut"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;
    int       nVars, nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_VARS,&nVars);
    CHECK_ERRCODE;
    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_CONS,&nCons);
    CHECK_ERRCODE;

    *pnErrorCode = LSdeduceStages(pModel,nMaxStage,panRowStagesIn,panColStagesIn,panSparStage);
    CHECK_ERRCODE;

    PROTECT(spanRowStagesOut = NEW_INTEGER(nCons));
    nProtect += 1;
    panRowStagesOut = INTEGER_POINTER(spanRowStagesOut);
    memcpy(panRowStagesOut,panRowStagesIn,sizeof(int)*nCons);

    PROTECT(spanColStagesOut = NEW_INTEGER(nCons));
    nProtect += 1;
    panColStagesOut = INTEGER_POINTER(spanColStagesOut);
    memcpy(panColStagesOut,panColStagesIn,sizeof(int)*nVars);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spanRowStagesOut);
        SET_VECTOR_ELT(rList, 2, spanColStagesOut);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsolveSP(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnStatus;
    SEXP      spnStatus = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pnStatus"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnStatus = NEW_INTEGER(1));
    nProtect += 1;
    pnStatus = INTEGER_POINTER(spnStatus);

    *pnErrorCode = LSsolveSP(pModel,pnStatus);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnStatus);
    }

    UNPROTECT(nProtect + 2);

    return rList;

}

SEXP rcLSsolveHS(SEXP      sModel,
                 SEXP      snSearchMethod)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nSearchMethod = Rf_asInteger(snSearchMethod);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnStatus;
    SEXP      spnStatus = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pnStatus"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnStatus = NEW_INTEGER(1));
    nProtect += 1;
    pnStatus = INTEGER_POINTER(spnStatus);

    *pnErrorCode = LSsolveHS(pModel,nSearchMethod,pnStatus);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnStatus);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetScenarioObjective(SEXP      sModel,
                              SEXP      sjScenario)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdObj;
    SEXP      spdObj = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdObj"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spdObj = NEW_NUMERIC(1));
    nProtect += 1;
    pdObj = NUMERIC_POINTER(spdObj);

    *pnErrorCode = LSgetScenarioObjective(pModel,jScenario,pdObj);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdObj);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetNodePrimalSolution(SEXP      sModel,
                               SEXP      sjScenario,
                               SEXP      siStage)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);
    int       iStage = Rf_asInteger(siStage);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padX;
    SEXP      spadX = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","padX"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetStocInfo(pModel,LS_IINFO_STOC_NUM_COLS_STAGE,iStage,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadX = NEW_NUMERIC(nVars));
    nProtect += 1;
    padX = NUMERIC_POINTER(spadX);

    *pnErrorCode = LSgetNodePrimalSolution(pModel,jScenario,iStage,padX);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadX);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetNodeDualSolution(SEXP      sModel,
                             SEXP      sjScenario,
                             SEXP      siStage)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);
    int       iStage = Rf_asInteger(siStage);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padY;
    SEXP      spadY = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","padY"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetStocInfo(pModel,LS_IINFO_STOC_NUM_ROWS_STAGE,iStage,&nCons);
    CHECK_ERRCODE;

    PROTECT(spadY = NEW_NUMERIC(nCons));
    nProtect += 1;
    padY = NUMERIC_POINTER(spadY);

    *pnErrorCode = LSgetNodeDualSolution(pModel,jScenario,iStage,padY);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadY);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetNodeReducedCost(SEXP      sModel,
                            SEXP      sjScenario,
                            SEXP      siStage)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);
    int       iStage = Rf_asInteger(siStage);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padX;
    SEXP      spadX = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","padX"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetStocInfo(pModel,LS_IINFO_STOC_NUM_COLS_STAGE,iStage,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadX = NEW_NUMERIC(nVars));
    nProtect += 1;
    padX = NUMERIC_POINTER(spadX);

    *pnErrorCode = LSgetNodeReducedCost(pModel,jScenario,iStage,padX);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadX);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetNodeSlacks(SEXP      sModel,
                       SEXP      sjScenario,
                       SEXP      siStage)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);
    int       iStage = Rf_asInteger(siStage);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padY;
    SEXP      spadY = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","padY"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetStocInfo(pModel,LS_IINFO_STOC_NUM_ROWS_STAGE,iStage,&nCons);
    CHECK_ERRCODE;

    PROTECT(spadY = NEW_NUMERIC(nCons));
    nProtect += 1;
    padY = NUMERIC_POINTER(spadY);

    *pnErrorCode = LSgetNodeSlacks(pModel,jScenario,iStage,padY);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadY);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetScenarioPrimalSolution(SEXP      sModel,
                                   SEXP      sjScenario)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padX;
    SEXP      spadX = R_NilValue;
    double    *pdObj;
    SEXP      spdObj = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode","padX","pdObj"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetStocInfo(pModel,LS_IINFO_STOC_NUM_COLS_CORE,jScenario,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadX = NEW_NUMERIC(nVars));
    nProtect += 1;
    padX = NUMERIC_POINTER(spadX);

    PROTECT(spdObj = NEW_NUMERIC(1));
    nProtect += 1;
    pdObj = NUMERIC_POINTER(spdObj);

    *pnErrorCode = LSgetScenarioPrimalSolution(pModel,jScenario,padX,pdObj);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadX);
        SET_VECTOR_ELT(rList, 2, spdObj);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetScenarioReducedCost(SEXP      sModel,
                                SEXP      sjScenario)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padX;
    SEXP      spadX = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","padX"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nVars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetStocInfo(pModel,LS_IINFO_STOC_NUM_COLS_CORE,jScenario,&nVars);
    CHECK_ERRCODE;

    PROTECT(spadX = NEW_NUMERIC(nVars));
    nProtect += 1;
    padX = NUMERIC_POINTER(spadX);

    *pnErrorCode = LSgetScenarioReducedCost(pModel,jScenario,padX);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadX);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetScenarioDualSolution(SEXP      sModel,
                                 SEXP      sjScenario)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padY;
    SEXP      spadY = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","padY"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetStocInfo(pModel,LS_IINFO_STOC_NUM_ROWS_CORE,jScenario,&nCons);
    CHECK_ERRCODE;

    PROTECT(spadY = NEW_NUMERIC(nCons));
    nProtect += 1;
    padY = NUMERIC_POINTER(spadY);

    *pnErrorCode = LSgetScenarioDualSolution(pModel,jScenario,padY);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadY);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetScenarioSlacks(SEXP      sModel,
                           SEXP      sjScenario)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padY;
    SEXP      spadY = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","padY"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;
    int       nCons;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetStocInfo(pModel,LS_IINFO_STOC_NUM_ROWS_CORE,jScenario,&nCons);
    CHECK_ERRCODE;

    PROTECT(spadY = NEW_NUMERIC(nCons));
    nProtect += 1;
    padY = NUMERIC_POINTER(spadY);

    *pnErrorCode = LSgetScenarioSlacks(pModel,jScenario,padY);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadY);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetNodeListByScenario(SEXP      sModel,
                               SEXP      sjScenario)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *paiNodes;
    SEXP      spaiNodes = R_NilValue;
    int       *pnNodes;
    SEXP      spnNodes = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode","paiNodes","pnNodes"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnNodes = NEW_INTEGER(1));
    nProtect += 1;
    pnNodes = INTEGER_POINTER(spnNodes);

    *pnErrorCode = LSgetNodeListByScenario(pModel,jScenario,NULL,pnNodes);
    CHECK_ERRCODE;

    PROTECT(spaiNodes = NEW_INTEGER(*pnNodes));
    nProtect += 1;
    paiNodes = INTEGER_POINTER(spaiNodes);

    *pnErrorCode = LSgetNodeListByScenario(pModel,jScenario,paiNodes,NULL);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spaiNodes);
        SET_VECTOR_ELT(rList, 2, spnNodes);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetProbabilityByScenario(SEXP      sModel,
                                  SEXP      sjScenario)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdProb;
    SEXP      spdProb = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdProb"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spdProb = NEW_NUMERIC(1));
    nProtect += 1;
    pdProb = NUMERIC_POINTER(spdProb);

    *pnErrorCode = LSgetProbabilityByScenario(pModel,jScenario,pdProb);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdProb);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetProbabilityByNode(SEXP      sModel,
                              SEXP      siNode)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iNode = Rf_asInteger(siNode);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdProb;
    SEXP      spdProb = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdProb"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spdProb = NEW_NUMERIC(1));
    nProtect += 1;
    pdProb = NUMERIC_POINTER(spdProb);

    *pnErrorCode = LSgetProbabilityByNode(pModel,iNode,pdProb);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdProb);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStocParData(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *paiStages;
    SEXP      spaiStages = R_NilValue;
    double    *padVals;
    SEXP      spadVals = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode","paiStages", "padVals"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;
    int       nSpars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_SPARS,&nSpars);
    CHECK_ERRCODE;

    PROTECT(spaiStages = NEW_INTEGER(nSpars));
    nProtect += 1;
    paiStages = INTEGER_POINTER(spaiStages);

    PROTECT(spadVals = NEW_NUMERIC(nSpars));
    nProtect += 1;
    padVals = NUMERIC_POINTER(spadVals);

    *pnErrorCode = LSgetStocParData(pModel,paiStages,padVals);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spaiStages);
        SET_VECTOR_ELT(rList, 2, spadVals);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSaddDiscreteBlocks(SEXP      sModel,
                           SEXP      siStage,
                           SEXP      snRealzBlock,
                           SEXP      spadProb,
                           SEXP      spakStart,
                           SEXP      spaiRows,
                           SEXP      spaiCols,
                           SEXP      spaiStvs,
                           SEXP      spadVals,
                           SEXP      snModifyRule)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iStage = Rf_asInteger(siStage);
    int       nRealzBlock = Rf_asInteger(snRealzBlock);
    double    *padProb = REAL(spadProb);
    int       *pakStart = INTEGER(spakStart);
    int       *paiRows = INTEGER(spaiRows);
    int       *paiCols = INTEGER(spaiCols);
    int       *paiStvs = INTEGER(spaiStvs);
    double    *padVals = REAL(spadVals);
    int       nModifyRule = Rf_asInteger(snModifyRule);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddDiscreteBlocks(pModel,
                                       iStage,
                                       nRealzBlock,
                                       padProb,
                                       pakStart,
                                       paiRows,
                                       paiCols,
                                       paiStvs,
                                       padVals,
                                       nModifyRule);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);


    return rList;
}

SEXP rcLSaddScenario(SEXP      sModel,
                     SEXP      sjScenario,
                     SEXP      siParentScen,
                     SEXP      siStage,
                     SEXP      sdProb,
                     SEXP      snElems,
                     SEXP      spaiRows,
                     SEXP      spaiCols,
                     SEXP      spaiStvs,
                     SEXP      spadVals,
                     SEXP      snModifyRule)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);
    int       iParentScen = Rf_asInteger(siParentScen);
    int       iStage = Rf_asInteger(siStage);
    double    dProb = Rf_asReal(sdProb);
    int       nElems = Rf_asInteger(snElems);
    int       *paiRows = INTEGER(spaiRows);
    int       *paiCols = INTEGER(spaiCols);
    int       *paiStvs = INTEGER(spaiStvs);
    double    *padVals = REAL(spadVals);
    int       nModifyRule = Rf_asInteger(snModifyRule);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddScenario(pModel,
                                 jScenario,
                                 iParentScen,
                                 iStage,
                                 dProb,
                                 nElems,
                                 paiRows,
                                 paiCols,
                                 paiStvs,
                                 padVals,
                                 nModifyRule);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSaddDiscreteIndep(SEXP      sModel,
                          SEXP      siRow,
                          SEXP      sjCol,
                          SEXP      siStv,
                          SEXP      snRealizations,
                          SEXP      spadProbs,
                          SEXP      spadVals,
                          SEXP      snModifyRule)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iRow = Rf_asInteger(siRow);
    int       jCol = Rf_asInteger(sjCol);
    int       iStv = Rf_asInteger(siStv);
    int       nRealizations = Rf_asInteger(snRealizations);
    double    *padProbs = REAL(spadProbs);
    double    *padVals = REAL(spadVals);
    int       nModifyRule = Rf_asInteger(snModifyRule);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddDiscreteIndep(pModel,
                                      iRow,
                                      jCol,
                                      iStv,
                                      nRealizations,
                                      padProbs,
                                      padVals,
                                      nModifyRule);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSaddParamDistIndep(SEXP      sModel,
                           SEXP      siRow,
                           SEXP      sjCol,
                           SEXP      siStv,
                           SEXP      snDistType,
                           SEXP      snParams,
                           SEXP      spadParams,
                           SEXP      siModifyRule)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iRow = Rf_asInteger(siRow);
    int       jCol = Rf_asInteger(sjCol);
    int       iStv = Rf_asInteger(siStv);
    int       nDistType = Rf_asInteger(snDistType);
    int       nParams = Rf_asInteger(snParams);
    double    *padParams = REAL(spadParams);
    int       iModifyRule = Rf_asInteger(siModifyRule);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddParamDistIndep(pModel,
                                       iRow,
                                       jCol,
                                       iStv,
                                       nDistType,
                                       nParams,
                                       padParams,
                                       iModifyRule);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSaddChanceConstraint(SEXP      sModel,
                             SEXP      siSense,
                             SEXP      snCons,
                             SEXP      spaiCons,
                             SEXP      sdPrLevel,
                             SEXP      sdObjWeight)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iSense = Rf_asInteger(siSense);
    int       nCons = Rf_asInteger(snCons);
    int       *paiCons = INTEGER(spaiCons);
    double    dPrLevel = Rf_asReal(sdPrLevel);
    double    dObjWeight = Rf_asReal(sdObjWeight);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSaddChanceConstraint(pModel,
                                         iSense,
                                         nCons,
                                         paiCons,
                                         dPrLevel,
                                         dObjWeight);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetNumStages(SEXP      sModel,
                      SEXP      snumStages)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       numStages = Rf_asInteger(snumStages);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSsetNumStages(pModel,
                                  numStages);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStocParOutcomes(SEXP      sModel,
                            SEXP      sjScenario)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *padVals;
    SEXP      spadVals = R_NilValue;
    double    *pdProb;
    SEXP      spdProb = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode","padVals", "pdProb"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;
    int       nSpars;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSgetInfo(pModel,LS_IINFO_NUM_SPARS,&nSpars);
    CHECK_ERRCODE;

    PROTECT(spadVals = NEW_NUMERIC(nSpars));
    nProtect += 1;
    padVals = NUMERIC_POINTER(spadVals);

    PROTECT(spdProb = NEW_NUMERIC(1));
    nProtect += 1;
    pdProb = NUMERIC_POINTER(spdProb);

    *pnErrorCode = LSgetStocParOutcomes(pModel,jScenario,padVals,pdProb);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spadVals);
        SET_VECTOR_ELT(rList, 2, spdProb);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSloadCorrelationMatrix(SEXP      sModel,
                               SEXP      snDim,
                               SEXP      snCorrType,
                               SEXP      snQCnnz,
                               SEXP      spaiQCcols1,
                               SEXP      spaiQCcols2,
                               SEXP      spadQCcoef)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nDim = Rf_asInteger(snDim);
    int       nCorrType = Rf_asInteger(snCorrType);
    int       nQCnnz = Rf_asInteger(snQCnnz);
    int       *paiQCcols1 = INTEGER(spaiQCcols1);
    int       *paiQCcols2 = INTEGER(spaiQCcols2);
    double    *padQCcoef = REAL(spadQCcoef);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSloadCorrelationMatrix(pModel,
                                           nDim,
                                           nCorrType,
                                           nQCnnz,
                                           paiQCcols1,
                                           paiQCcols2,
                                           padQCcoef);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetCorrelationMatrix(SEXP      sModel,
                              SEXP      siFlag,
                              SEXP      snCorrType)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iFlag = Rf_asInteger(siFlag);
    int       nCorrType = Rf_asInteger(snCorrType);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnQCnnz;
    SEXP      spnQCnnz = R_NilValue;
    int       *paiQCcols1;
    SEXP      spaiQCcols1 = R_NilValue;
    int       *paiQCcols2;
    SEXP      spaiQCcols2 = R_NilValue;
    double    *padQCcoef;
    SEXP      spadQCcoef = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[5] = {"ErrorCode","pnQCnnz","paiQCcols1","paiQCcols2","padQCcoef"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 5;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnQCnnz = NEW_INTEGER(1));
    nProtect += 1;
    pnQCnnz = INTEGER_POINTER(spnQCnnz);

    *pnErrorCode = LSgetCorrelationMatrix(pModel,iFlag,nCorrType,pnQCnnz,NULL,NULL,NULL);
    CHECK_ERRCODE;

    PROTECT(spaiQCcols1 = NEW_INTEGER(*pnQCnnz));
    nProtect += 1;
    paiQCcols1 = INTEGER_POINTER(spaiQCcols1);

    PROTECT(spaiQCcols2 = NEW_INTEGER(*pnQCnnz));
    nProtect += 1;
    paiQCcols2 = INTEGER_POINTER(spaiQCcols2);

    PROTECT(spadQCcoef = NEW_NUMERIC(*pnQCnnz));
    nProtect += 1;
    padQCcoef = NUMERIC_POINTER(spadQCcoef);

    *pnErrorCode = LSgetCorrelationMatrix(pModel,iFlag,nCorrType,NULL,
                                          paiQCcols1,paiQCcols2,padQCcoef);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnQCnnz);
        SET_VECTOR_ELT(rList, 2, spaiQCcols1);
        SET_VECTOR_ELT(rList, 3, spaiQCcols2);
        SET_VECTOR_ELT(rList, 4, spadQCcoef);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStocParSample(SEXP      sModel,
                          SEXP      siStv,
                          SEXP      siRow,
                          SEXP      sjCol)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iStv = Rf_asInteger(siStv);
    int       iRow = Rf_asInteger(siRow);
    int       jCol = Rf_asInteger(sjCol);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    prLSsample prSample = NULL;
    SEXP       sprSample = R_NilValue;

    //errorcode item
    PROTECT(spnErrorCode = NEW_INTEGER(1));
    pnErrorCode = INTEGER_POINTER(spnErrorCode);

    CHECK_MODEL_ERROR;

    prSample = (prLSsample)malloc(sizeof(rLSsample)*1);
    if(prSample == NULL)
    {
        return R_NilValue;
    }

    prSample->pSample = LSgetStocParSample(pModel,iStv,iRow,jCol,pnErrorCode);
    CHECK_ERRCODE;

    sprSample = R_MakeExternalPtr(prSample,R_NilValue,R_NilValue);

    R_SetExternalPtrTag(sprSample,tagLSsample);

ErrorReturn:

    UNPROTECT(1);

    if(*pnErrorCode)
    {
        Rprintf("\nFail to get Sample object (error %d)\n",*pnErrorCode);
        R_FlushConsole();
        return R_NilValue;
    }
    else
    {
        return sprSample;
    }
}

SEXP rcLSgetDiscreteBlocks(SEXP      sModel,
                           SEXP      siEvent)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iEvent = Rf_asInteger(siEvent);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *nDistType;
    SEXP      snDistType = R_NilValue;
    int       *iStage;
    SEXP      siStage = R_NilValue;
    int       *nRealzBlock;
    SEXP      snRealzBlock = R_NilValue;
    double    *padProbs;
    SEXP      spadProbs = R_NilValue;
    int       *iModifyRule;
    SEXP      siModifyRule = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[6] = {"ErrorCode","nDistType","iStage",
                           "nRealzBlock","padProbs","iModifyRule"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 6;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(snDistType = NEW_INTEGER(1));
    nProtect += 1;
    nDistType = INTEGER_POINTER(snDistType);

    PROTECT(siStage = NEW_INTEGER(1));
    nProtect += 1;
    iStage = INTEGER_POINTER(siStage);

    PROTECT(snRealzBlock = NEW_INTEGER(1));
    nProtect += 1;
    nRealzBlock = INTEGER_POINTER(snRealzBlock);

    PROTECT(siModifyRule = NEW_INTEGER(1));
    nProtect += 1;
    iModifyRule = INTEGER_POINTER(siModifyRule);

    *pnErrorCode = LSgetDiscreteBlocks(pModel,iEvent,nDistType,iStage,
                                       nRealzBlock,NULL,iModifyRule);
    CHECK_ERRCODE;

    PROTECT(spadProbs = NEW_NUMERIC(*nRealzBlock));
    nProtect += 1;
    padProbs = NUMERIC_POINTER(spadProbs);

    *pnErrorCode = LSgetDiscreteBlocks(pModel,iEvent,NULL,NULL,NULL,padProbs,NULL);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, snDistType);
        SET_VECTOR_ELT(rList, 2, siStage);
        SET_VECTOR_ELT(rList, 3, snRealzBlock);
        SET_VECTOR_ELT(rList, 4, spadProbs);
        SET_VECTOR_ELT(rList, 5, siModifyRule);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetDiscreteBlockOutcomes(SEXP      sModel,
                                  SEXP      siEvent,
                                  SEXP      siRealz)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iEvent = Rf_asInteger(siEvent);
    int       iRealz = Rf_asInteger(siRealz);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *nRealz;
    SEXP      snRealz = R_NilValue;
    int       *paiArows;
    SEXP      spaiArows = R_NilValue;
    int       *paiAcols;
    SEXP      spaiAcols = R_NilValue;
    int       *paiStvs;
    SEXP      spaiStvs = R_NilValue;
    double    *padVals;
    SEXP      spadVals = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[6] = {"ErrorCode","nRealz","paiArows",
                           "paiAcols","paiStvs","padVals"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 6;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(snRealz = NEW_INTEGER(1));
    nProtect += 1;
    nRealz = INTEGER_POINTER(snRealz);

    *pnErrorCode = LSgetDiscreteBlockOutcomes(pModel,iEvent,iRealz,
                                              nRealz,NULL,NULL,NULL,NULL);
    CHECK_ERRCODE;

    PROTECT(spaiArows = NEW_INTEGER(*nRealz));
    nProtect += 1;
    paiArows = INTEGER_POINTER(spaiArows);

    PROTECT(spaiAcols = NEW_INTEGER(*nRealz));
    nProtect += 1;
    paiAcols = INTEGER_POINTER(spaiAcols);

    PROTECT(spaiStvs = NEW_INTEGER(*nRealz));
    nProtect += 1;
    paiStvs = INTEGER_POINTER(spaiStvs);

    PROTECT(spadVals = NEW_NUMERIC(*nRealz));
    nProtect += 1;
    padVals = NUMERIC_POINTER(spadVals);

    *pnErrorCode = LSgetDiscreteBlockOutcomes(pModel,iEvent,iRealz,NULL,
                                              paiArows,paiAcols,paiStvs,padVals);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, snRealz);
        SET_VECTOR_ELT(rList, 2, spaiArows);
        SET_VECTOR_ELT(rList, 3, spaiAcols);
        SET_VECTOR_ELT(rList, 4, spaiStvs);
        SET_VECTOR_ELT(rList, 5, spadVals);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetDiscreteIndep(SEXP      sModel,
                          SEXP      siEvent)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iEvent = Rf_asInteger(siEvent);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *nDistType;
    SEXP      snDistType = R_NilValue;
    int       *iStage;
    SEXP      siStage = R_NilValue;
    int       *iRow;
    SEXP      siRow = R_NilValue;
    int       *jCol;
    SEXP      sjCol = R_NilValue;
    int       *iStv;
    SEXP      siStv = R_NilValue;
    int       *nRealizations;
    SEXP      snRealizations = R_NilValue;
    double    *padProbs;
    SEXP      spadProbs = R_NilValue;
    double    *padVals;
    SEXP      spadVals = R_NilValue;
    int       *iModifyRule;
    SEXP      siModifyRule = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[10] = {"ErrorCode","nDistType","iStage",
                            "iRow","jCol","iStv","nRealizations",
                            "padProbs","padVals","iModifyRule"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 10;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(snDistType = NEW_INTEGER(1));
    nProtect += 1;
    nDistType = INTEGER_POINTER(snDistType);

    PROTECT(siStage = NEW_INTEGER(1));
    nProtect += 1;
    iStage = INTEGER_POINTER(siStage);

    PROTECT(siRow = NEW_INTEGER(1));
    nProtect += 1;
    iRow = INTEGER_POINTER(siRow);

    PROTECT(sjCol = NEW_INTEGER(1));
    nProtect += 1;
    jCol = INTEGER_POINTER(sjCol);

    PROTECT(siStv = NEW_INTEGER(1));
    nProtect += 1;
    iStv = INTEGER_POINTER(siStv);

    PROTECT(snRealizations = NEW_INTEGER(1));
    nProtect += 1;
    nRealizations = INTEGER_POINTER(snRealizations);

    PROTECT(siModifyRule = NEW_INTEGER(1));
    nProtect += 1;
    iModifyRule = INTEGER_POINTER(siModifyRule);

    *pnErrorCode = LSgetDiscreteIndep(pModel,iEvent,nDistType,iStage,
                                      iRow,jCol,iStv,nRealizations,NULL,NULL,iModifyRule);
    CHECK_ERRCODE;

    PROTECT(spadProbs = NEW_NUMERIC(*nRealizations));
    nProtect += 1;
    padProbs = NUMERIC_POINTER(spadProbs);

    PROTECT(spadVals = NEW_NUMERIC(*nRealizations));
    nProtect += 1;
    padVals = NUMERIC_POINTER(spadVals);

    *pnErrorCode = LSgetDiscreteIndep(pModel,iEvent,NULL,NULL,NULL,NULL,NULL,NULL,
                                      padProbs,padVals,NULL);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, snDistType);
        SET_VECTOR_ELT(rList, 2, siStage);
        SET_VECTOR_ELT(rList, 3, siRow);
        SET_VECTOR_ELT(rList, 4, sjCol);
        SET_VECTOR_ELT(rList, 5, siStv);
        SET_VECTOR_ELT(rList, 6, snRealizations);
        SET_VECTOR_ELT(rList, 7, spadProbs);
        SET_VECTOR_ELT(rList, 8, spadVals);
        SET_VECTOR_ELT(rList, 9, siModifyRule);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetParamDistIndep(SEXP      sModel,
                           SEXP      siEvent)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iEvent = Rf_asInteger(siEvent);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *nDistType;
    SEXP      snDistType = R_NilValue;
    int       *iStage;
    SEXP      siStage = R_NilValue;
    int       *iRow;
    SEXP      siRow = R_NilValue;
    int       *jCol;
    SEXP      sjCol = R_NilValue;
    int       *iStv;
    SEXP      siStv = R_NilValue;
    int       *nParams;
    SEXP      snParams = R_NilValue;
    double    *padParams;
    SEXP      spadParams = R_NilValue;
    int       *iModifyRule;
    SEXP      siModifyRule = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[9] = {"ErrorCode","nDistType","iStage",
                            "iRow","jCol","iStv","nParams",
                            "padParams","iModifyRule"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 9;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(snDistType = NEW_INTEGER(1));
    nProtect += 1;
    nDistType = INTEGER_POINTER(snDistType);

    PROTECT(siStage = NEW_INTEGER(1));
    nProtect += 1;
    iStage = INTEGER_POINTER(siStage);

    PROTECT(siRow = NEW_INTEGER(1));
    nProtect += 1;
    iRow = INTEGER_POINTER(siRow);

    PROTECT(sjCol = NEW_INTEGER(1));
    nProtect += 1;
    jCol = INTEGER_POINTER(sjCol);

    PROTECT(siStv = NEW_INTEGER(1));
    nProtect += 1;
    iStv = INTEGER_POINTER(siStv);

    PROTECT(snParams = NEW_INTEGER(1));
    nProtect += 1;
    nParams = INTEGER_POINTER(snParams);

    PROTECT(siModifyRule = NEW_INTEGER(1));
    nProtect += 1;
    iModifyRule = INTEGER_POINTER(siModifyRule);

    *pnErrorCode = LSgetParamDistIndep(pModel,iEvent,nDistType,iStage,
                                       iRow,jCol,iStv,nParams,NULL,iModifyRule);
    CHECK_ERRCODE;

    PROTECT(spadParams = NEW_NUMERIC(*nParams));
    nProtect += 1;
    padParams = NUMERIC_POINTER(spadParams);

    *pnErrorCode = LSgetParamDistIndep(pModel,iEvent,NULL,NULL,
                                       NULL,NULL,NULL,NULL,padParams,NULL);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, snDistType);
        SET_VECTOR_ELT(rList, 2, siStage);
        SET_VECTOR_ELT(rList, 3, siRow);
        SET_VECTOR_ELT(rList, 4, sjCol);
        SET_VECTOR_ELT(rList, 5, siStv);
        SET_VECTOR_ELT(rList, 6, snParams);
        SET_VECTOR_ELT(rList, 7, spadParams);
        SET_VECTOR_ELT(rList, 8, siModifyRule);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetScenario(SEXP      sModel,
                     SEXP      sjScenario)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *iParentScen;
    SEXP      siParentScen = R_NilValue;
    int       *iBranchStage;
    SEXP      siBranchStage = R_NilValue;
    double    *pdProb;
    SEXP      spdProb = R_NilValue;
    int       *nRealz;
    SEXP      snRealz = R_NilValue;
    int       *paiArows;
    SEXP      spaiArows = R_NilValue;
    int       *paiAcols;
    SEXP      spaiAcols = R_NilValue;
    int       *paiStvs;
    SEXP      spaiStvs = R_NilValue;
    double    *padVals;
    SEXP      spadVals = R_NilValue;
    int       *iModifyRule;
    SEXP      siModifyRule = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[10] = {"ErrorCode","iParentScen","iBranchStage",
                            "pdProb","nRealz","paiArows","paiAcols",
                            "paiStvs","padVals","iModifyRule"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 10;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(siParentScen = NEW_INTEGER(1));
    nProtect += 1;
    iParentScen = INTEGER_POINTER(siParentScen);

    PROTECT(siBranchStage = NEW_INTEGER(1));
    nProtect += 1;
    iBranchStage = INTEGER_POINTER(siBranchStage);

    PROTECT(spdProb = NEW_NUMERIC(1));
    nProtect += 1;
    pdProb = NUMERIC_POINTER(spdProb);

    PROTECT(snRealz = NEW_INTEGER(1));
    nProtect += 1;
    nRealz = INTEGER_POINTER(snRealz);

    PROTECT(siModifyRule = NEW_INTEGER(1));
    nProtect += 1;
    iModifyRule = INTEGER_POINTER(siModifyRule);

    *pnErrorCode = LSgetScenario(pModel,jScenario,iParentScen,iBranchStage,pdProb,nRealz,
                                 NULL,NULL,NULL,NULL,iModifyRule);
    CHECK_ERRCODE;

    PROTECT(spaiArows = NEW_INTEGER(*nRealz));
    nProtect += 1;
    paiArows = INTEGER_POINTER(spaiArows);

    PROTECT(spaiAcols = NEW_INTEGER(*nRealz));
    nProtect += 1;
    paiAcols = INTEGER_POINTER(spaiAcols);

    PROTECT(spaiStvs = NEW_INTEGER(*nRealz));
    nProtect += 1;
    paiStvs = INTEGER_POINTER(spaiStvs);

    PROTECT(spadVals = NEW_NUMERIC(*nRealz));
    nProtect += 1;
    padVals = NUMERIC_POINTER(spadVals);

    *pnErrorCode = LSgetScenario(pModel,jScenario,NULL,NULL,NULL,NULL,
                                 paiArows,paiAcols,paiStvs,padVals,NULL);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, siParentScen);
        SET_VECTOR_ELT(rList, 2, siBranchStage);
        SET_VECTOR_ELT(rList, 3, spdProb);
        SET_VECTOR_ELT(rList, 4, snRealz);
        SET_VECTOR_ELT(rList, 5, spaiArows);
        SET_VECTOR_ELT(rList, 6, spaiAcols);
        SET_VECTOR_ELT(rList, 7, spaiStvs);
        SET_VECTOR_ELT(rList, 8, spadVals);
        SET_VECTOR_ELT(rList, 9, siModifyRule);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetChanceConstraint(SEXP      sModel,
                             SEXP      siChance)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       iChance = Rf_asInteger(siChance);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *piSense;
    SEXP      spiSense = R_NilValue;
    int       *pnCons;
    SEXP      spnCons = R_NilValue;
    int       *paiCons;
    SEXP      spaiCons = R_NilValue;
    double    *pdProb;
    SEXP      spdProb = R_NilValue;
    double    *pdObjWeight;
    SEXP      spdObjWeight = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[6] = {"ErrorCode","piSense","pnCons",
                            "paiCons","pdProb","pdObjWeight"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 6;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spiSense = NEW_INTEGER(1));
    nProtect += 1;
    piSense = INTEGER_POINTER(spiSense);

    PROTECT(spnCons = NEW_INTEGER(1));
    nProtect += 1;
    pnCons = INTEGER_POINTER(spnCons);

    PROTECT(spdProb = NEW_NUMERIC(1));
    nProtect += 1;
    pdProb = NUMERIC_POINTER(spdProb);

    PROTECT(spdObjWeight = NEW_NUMERIC(1));
    nProtect += 1;
    pdObjWeight = NUMERIC_POINTER(spdObjWeight);

    *pnErrorCode = LSgetChanceConstraint(pModel,iChance,
                                         piSense,pnCons,NULL,
                                         pdProb,pdObjWeight);
    CHECK_ERRCODE;

    PROTECT(spaiCons = NEW_INTEGER(*pnCons));
    nProtect += 1;
    paiCons = INTEGER_POINTER(spaiCons);

    *pnErrorCode = LSgetChanceConstraint(pModel,iChance,
                                         NULL,NULL,paiCons,
                                         NULL,NULL);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spiSense);
        SET_VECTOR_ELT(rList, 2, spnCons);
        SET_VECTOR_ELT(rList, 3, spaiCons);
        SET_VECTOR_ELT(rList, 4, spdProb);
        SET_VECTOR_ELT(rList, 5, spdObjWeight);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetSampleSizes(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *panSampleSize;
    SEXP      spanSampleSize = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","panSampleSize"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spanSampleSize = NEW_INTEGER(1));
    nProtect += 1;
    panSampleSize = INTEGER_POINTER(spanSampleSize);

    *pnErrorCode = LSgetSampleSizes(pModel,panSampleSize);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spanSampleSize);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetConstraintStages(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *panStage;
    SEXP      spanStage = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","panStage"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spanStage = NEW_INTEGER(1));
    nProtect += 1;
    panStage = INTEGER_POINTER(spanStage);

    *pnErrorCode = LSgetConstraintStages(pModel,panStage);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spanStage);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetVariableStages(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *panStage;
    SEXP      spanStage = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","panStage"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spanStage = NEW_INTEGER(1));
    nProtect += 1;
    panStage = INTEGER_POINTER(spanStage);

    *pnErrorCode = LSgetVariableStages(pModel,panStage);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spanStage);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetStocRowIndices(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *paiSrows;
    SEXP      spaiSrows = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","paiSrows"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spaiSrows = NEW_INTEGER(1));
    nProtect += 1;
    paiSrows = INTEGER_POINTER(spaiSrows);

    *pnErrorCode = LSgetStocRowIndices(pModel,paiSrows);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spaiSrows);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetStocParRG(SEXP      sModel,
                      SEXP      siStv,
                      SEXP      siRow,
                      SEXP      sjCol,
                      SEXP      sRG)
{
    prLSmodel   prModel;
    pLSmodel    pModel;
    prLSrandGen prRG;
    pLSrandGen  pRG;
    int         iStv = Rf_asInteger(siStv);
    int         iRow = Rf_asInteger(siRow);
    int         jCol = Rf_asInteger(sjCol);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    if(sRG != R_NilValue && R_ExternalPtrTag(sRG) == tagLSrandGen)
    {
        prRG = (prLSrandGen)R_ExternalPtrAddr(sRG);
        pRG = prRG->pRG;
    }
    else
    {
        *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;
        goto ErrorReturn;
    }

    *pnErrorCode = LSsetStocParRG(pModel,iStv,iRow,jCol,pRG);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetScenarioModel(SEXP      sModel,
                          SEXP      sjScenario)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       jScenario = Rf_asInteger(sjScenario);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    prLSmodel prdModel = NULL;
    SEXP      sprdModel = R_NilValue;
    int       nProtect = 0;
   
    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    prdModel = (prLSmodel)malloc(sizeof(rLSmodel)*1);
    if(prdModel == NULL)
    {
        return R_NilValue;
    }

    prdModel->pModel = LSgetScenarioModel(pModel,jScenario,pnErrorCode);
    CHECK_ERRCODE;

    SET_PRINT_LOG(prdModel->pModel,*pnErrorCode);
    CHECK_ERRCODE;

    SET_MODEL_CALLBACK(prdModel->pModel,*pnErrorCode);
    CHECK_ERRCODE;

    sprdModel = R_MakeExternalPtr(prdModel,R_NilValue,R_NilValue);

    R_SetExternalPtrTag(sprdModel,tagLSprob);

ErrorReturn:

    UNPROTECT(nProtect);

    if(*pnErrorCode)
    {
        Rprintf("\nFail to get ScenarioModel (error %d)\n",*pnErrorCode);
        R_FlushConsole();
        return R_NilValue;
    }
    else
    {
        return sprdModel;
    }
}

SEXP rcLSfreeStocMemory(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    LSfreeStocMemory(pModel);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSfreeStocHashMemory(SEXP      sModel)
{
    prLSmodel prModel;
    pLSmodel  pModel;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    LSfreeStocHashMemory(pModel);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetModelStocParameterInt(SEXP      sModel,
                                  SEXP      snQuery)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnResult;
    SEXP      spnResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pnResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnResult = NEW_INTEGER(1));
    nProtect += 1;
    pnResult = INTEGER_POINTER(spnResult);

    *pnErrorCode = LSgetModelStocParameter(pModel,nQuery,pnResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetModelStocParameterDou(SEXP      sModel,
                                  SEXP      snQuery)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdResult;
    SEXP      spdResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spdResult = NEW_NUMERIC(1));
    nProtect += 1;
    pdResult = NUMERIC_POINTER(spdResult);

    *pnErrorCode = LSgetModelStocParameter(pModel,nQuery,pdResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetModelStocParameterChar(SEXP      sModel,
                                   SEXP      snQuery)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      pachResult[256];
    SEXP      spachResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pachResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spachResult = NEW_CHARACTER(1));
    nProtect += 1;

    *pnErrorCode = LSgetModelStocParameter(pModel,nQuery,pachResult);

    CHECK_ERRCODE;

    SET_STRING_ELT(spachResult,0,mkChar(pachResult)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spachResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetModelStocParameterInt(SEXP       sModel,
                                  SEXP       snQuery,
                                  SEXP       spnResult)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);
    int       *pnResult = INTEGER(spnResult);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSsetModelStocParameter(pModel,
                                           nQuery,
                                           pnResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetModelStocParameterDou(SEXP       sModel,
                                  SEXP       snQuery,
                                  SEXP       spdResult)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);
    double    *pdResult = REAL(spdResult);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSsetModelStocParameter(pModel,
                                           nQuery,
                                           pdResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetModelStocParameterChar(SEXP       sModel,
                                   SEXP       snQuery,
                                   SEXP       spacResult)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nQuery = Rf_asInteger(snQuery);
    char      *pacResult = (char *)CHAR(STRING_ELT(spacResult,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    *pnErrorCode = LSsetModelStocParameter(pModel,
                                           nQuery,
                                           pacResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetEnvStocParameterInt(SEXP      sEnv,
                                SEXP      snQuery)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       nQuery = Rf_asInteger(snQuery);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnResult;
    SEXP      spnResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pnResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    PROTECT(spnResult = NEW_INTEGER(1));
    nProtect += 1;
    pnResult = INTEGER_POINTER(spnResult);

    *pnErrorCode = LSgetEnvStocParameter(pEnv,nQuery,pnResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetEnvStocParameterDou(SEXP      sEnv,
                                SEXP      snQuery)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       nQuery = Rf_asInteger(snQuery);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdResult;
    SEXP      spdResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    PROTECT(spdResult = NEW_NUMERIC(1));
    nProtect += 1;
    pdResult = NUMERIC_POINTER(spdResult);

    *pnErrorCode = LSgetEnvStocParameter(pEnv,nQuery,pdResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetEnvStocParameterChar(SEXP      sEnv,
                                 SEXP      snQuery)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       nQuery = Rf_asInteger(snQuery);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    char      pachResult[256];
    SEXP      spachResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pachResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    PROTECT(spachResult = NEW_CHARACTER(1));
    nProtect += 1;

    *pnErrorCode = LSgetEnvStocParameter(pEnv,nQuery,pachResult);

    CHECK_ERRCODE;

    SET_STRING_ELT(spachResult,0,mkChar(pachResult)); 

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spachResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetEnvStocParameterInt(SEXP      sEnv,
                                SEXP      snQuery,
                                SEXP      spnResult)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       nQuery = Rf_asInteger(snQuery);
    int       *pnResult = INTEGER(spnResult);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    *pnErrorCode = LSsetEnvStocParameter(pEnv,
                                         nQuery,
                                         pnResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetEnvStocParameterDou(SEXP      sEnv,
                                SEXP      snQuery,
                                SEXP      spdResult)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       nQuery = Rf_asInteger(snQuery);
    double    *pdResult = REAL(spdResult);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    *pnErrorCode = LSsetEnvStocParameter(pEnv,
                                         nQuery,
                                         pdResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetEnvStocParameterChar(SEXP      sEnv,
                                 SEXP      snQuery,
                                 SEXP      spacResult)
{
    prLSenv   prEnv;
    pLSenv    pEnv;
    int       nQuery = Rf_asInteger(snQuery);
    char      *pacResult = (char *)CHAR(STRING_ELT(spacResult,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_ENV_ERROR;

    *pnErrorCode = LSsetEnvStocParameter(pEnv,
                                         nQuery,
                                         pacResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST;  

    SET_VECTOR_ELT(rList, 0, spnErrorCode);     
    UNPROTECT(nProtect + 2);

    return rList;
}

/********************************************************
* Statistical Calculations Interface (15)               *
*********************************************************/
SEXP rcLSsampCreate(SEXP sEnv,
                    SEXP snDistType)
{
    int         nErrorCode = LSERR_NO_ERROR;
    prLSenv     prEnv = NULL;
    pLSenv      pEnv = NULL;
    prLSsample  prSample = NULL;
    pLSsample   pSample = NULL;
    SEXP        sSample = R_NilValue;
    int         nDistType = Rf_asInteger(snDistType);

    if(sEnv != R_NilValue && R_ExternalPtrTag(sEnv) == tagLSenv)
    {
        prEnv = (prLSenv)R_ExternalPtrAddr(sEnv);
        pEnv = prEnv->pEnv;
    }
    else
    {
        nErrorCode = LSERR_ILLEGAL_NULL_POINTER;
        Rprintf("Failed to create Sample object (error %d)\n",nErrorCode);
        R_FlushConsole();
        return R_NilValue;
    }

    prSample = (prLSsample)malloc(sizeof(rLSsample)*1);
    if(prSample == NULL)
    {
        return R_NilValue;
    }

    pSample = LSsampCreate(pEnv,nDistType,&nErrorCode);
    if(nErrorCode)
    {
        Rprintf("Failed to create Sample object (error %d)\n",nErrorCode);
        R_FlushConsole();
        return R_NilValue;
    }

    prSample->pSample = pSample;

    sSample = R_MakeExternalPtr(prSample,R_NilValue,R_NilValue);

    R_SetExternalPtrTag(sSample,tagLSsample);

    return sSample;
}

SEXP rcLSsampDelete(SEXP  sSample)
{
    prLSsample   prSample;
    pLSsample    pSample;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;

    *pnErrorCode = LSsampDelete(&pSample);
    CHECK_ERRCODE;

    prSample->pSample = NULL;

    R_ClearExternalPtr(sSample);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsampSetDistrParam(SEXP  sSample,
                           SEXP  snIndex,
                           SEXP  sdValue)
{
    prLSsample   prSample;
    pLSsample    pSample;
    int          nIndex = Rf_asInteger(snIndex);
    double       dValue = Rf_asReal(sdValue);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;

    *pnErrorCode = LSsampSetDistrParam(pSample,nIndex,dValue);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsampGetDistrParam(SEXP  sSample,
                           SEXP  snIndex)
{
    prLSsample   prSample;
    pLSsample    pSample;
    int          nIndex = Rf_asInteger(snIndex);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdValue;
    SEXP      spdValue = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdValue"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;

    PROTECT(spdValue = NEW_NUMERIC(1));
    nProtect += 1;
    pdValue = NUMERIC_POINTER(spdValue);

    *pnErrorCode = LSsampGetDistrParam(pSample,nIndex,pdValue);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdValue);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsampEvalDistr(SEXP  sSample,
                       SEXP  snFuncType,
                       SEXP  sdXval)
{
    prLSsample   prSample;
    pLSsample    pSample;
    int          nFuncType = Rf_asInteger(snFuncType);
    double       dXval = Rf_asReal(sdXval);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdResult;
    SEXP      spdResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;

    PROTECT(spdResult = NEW_NUMERIC(1));
    nProtect += 1;
    pdResult = NUMERIC_POINTER(spdResult);

    *pnErrorCode = LSsampEvalDistr(pSample,nFuncType,dXval,pdResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsampEvalUserDistr(SEXP  sSample,
                           SEXP  snFuncType,
                           SEXP  spadXval,
                           SEXP  snDim)
{
    prLSsample   prSample;
    pLSsample    pSample;
    int          nFuncType = Rf_asInteger(snFuncType);
    double       *padXval = REAL(spadXval);
    int          nDim = Rf_asInteger(snDim);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdResult;
    SEXP      spdResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;

    PROTECT(spdResult = NEW_NUMERIC(1));
    nProtect += 1;
    pdResult = NUMERIC_POINTER(spdResult);

    *pnErrorCode = LSsampEvalUserDistr(pSample,nFuncType,padXval,nDim,pdResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsampSetRG(SEXP  sSample,
                   SEXP  sRG)
{
    prLSsample    prSample;
    pLSsample     pSample;
    prLSrandGen   prRG;
    pLSrandGen    pRG;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;
    CHECK_RG_ERROR;

    *pnErrorCode = LSsampSetRG(pSample,pRG);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsampGenerate(SEXP  sSample,
                      SEXP  snMethod,
                      SEXP  snSize)
{
    prLSsample   prSample;
    pLSsample    pSample;
    int          nMethod = Rf_asInteger(snMethod);
    int          nSize = Rf_asInteger(snSize);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;

    *pnErrorCode = LSsampGenerate(pSample,nMethod,nSize);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsampGetPoints(SEXP  sSample)
{
    prLSsample   prSample;
    pLSsample    pSample;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnSampSize;
    SEXP      spnSampSize = R_NilValue;
    double    *padXval;
    SEXP      spadXval = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode","pnSampSize","padXval"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;

    PROTECT(spnSampSize = NEW_INTEGER(1));
    nProtect += 1;
    pnSampSize = INTEGER_POINTER(spnSampSize);

    *pnErrorCode = LSsampGetPoints(pSample,pnSampSize,NULL);
    CHECK_ERRCODE;

    PROTECT(spadXval = NEW_NUMERIC(*pnSampSize));
    nProtect += 1;
    padXval = NUMERIC_POINTER(spadXval);

    *pnErrorCode = LSsampGetPoints(pSample,NULL,padXval);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnSampSize);
        SET_VECTOR_ELT(rList, 2, spadXval);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsampLoadPoints(SEXP  sSample,
                        SEXP  snSampSize,
                        SEXP  spadXval)
{
    prLSsample   prSample;
    pLSsample    pSample;
    int          nSampSize = Rf_asInteger(snSampSize);
    double       *padXval = REAL(spadXval);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;

    *pnErrorCode = LSsampLoadPoints(pSample,nSampSize,padXval);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsampGetCIPoints(SEXP  sSample)
{
    prLSsample   prSample;
    pLSsample    pSample;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnSampSize;
    SEXP      spnSampSize = R_NilValue;
    double    *padXval;
    SEXP      spadXval = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[3] = {"ErrorCode","pnSampSize","padXval"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 3;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;

    PROTECT(spnSampSize = NEW_INTEGER(1));
    nProtect += 1;
    pnSampSize = INTEGER_POINTER(spnSampSize);

    *pnErrorCode = LSsampGetCIPoints(pSample,pnSampSize,NULL);
    CHECK_ERRCODE;

    PROTECT(spadXval = NEW_NUMERIC(*pnSampSize));
    nProtect += 1;
    padXval = NUMERIC_POINTER(spadXval);

    *pnErrorCode = LSsampGetCIPoints(pSample,NULL,padXval);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnSampSize);
        SET_VECTOR_ELT(rList, 2, spadXval);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsampLoadDiscretePdfTable(SEXP  sSample,
                                  SEXP  snLen,
                                  SEXP  spadProb,
                                  SEXP  spadVals)
{
    prLSsample   prSample;
    pLSsample    pSample;
    int          nLen = Rf_asInteger(snLen);
    double       *padProb = REAL(spadProb);
    double       *padVals = REAL(spadVals);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;

    *pnErrorCode = LSsampLoadDiscretePdfTable(pSample,nLen,padProb,padVals);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsampGetDiscretePdfTable(SEXP  sSample)
{
    prLSsample   prSample;
    pLSsample    pSample;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnLen;
    SEXP      spnLen = R_NilValue;
    double    *padProb;
    SEXP      spadProb = R_NilValue;
    double    *padVals;
    SEXP      spadVals = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[4] = {"ErrorCode","pnLen", "padProb","padVals"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 4;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;

    PROTECT(spnLen = NEW_INTEGER(1));
    nProtect += 1;
    pnLen = INTEGER_POINTER(spnLen);

    *pnErrorCode = LSsampGetDiscretePdfTable(pSample,pnLen,NULL,NULL);
    CHECK_ERRCODE;

    PROTECT(spadProb = NEW_NUMERIC(*pnLen));
    nProtect += 1;
    padProb = NUMERIC_POINTER(spadProb);

    
    PROTECT(spadVals = NEW_NUMERIC(*pnLen));
    nProtect += 1;
    padVals = NUMERIC_POINTER(spadVals);

    *pnErrorCode = LSsampGetDiscretePdfTable(pSample,NULL,padProb,padVals);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnLen);
        SET_VECTOR_ELT(rList, 2, spadProb);
        SET_VECTOR_ELT(rList, 3, spadVals);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsampGetIInfo(SEXP      sSample,
                      SEXP      snQuery)
{
    prLSsample   prSample;
    pLSsample    pSample;
    int          nQuery = Rf_asInteger(snQuery);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnResult;
    SEXP      spnResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pnResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;

    PROTECT(spnResult = NEW_INTEGER(1));
    nProtect += 1;
    pnResult = INTEGER_POINTER(spnResult);

    *pnErrorCode = LSsampGetInfo(pSample,nQuery,pnResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsampGetDInfo(SEXP      sSample,
                      SEXP      snQuery)
{
    prLSsample   prSample;
    pLSsample    pSample;
    int          nQuery = Rf_asInteger(snQuery);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdResult;
    SEXP      spdResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_SAMPLE_ERROR;

    PROTECT(spdResult = NEW_NUMERIC(1));
    nProtect += 1;
    pdResult = NUMERIC_POINTER(spdResult);

    *pnErrorCode = LSsampGetInfo(pSample,nQuery,pdResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

/********************************************************
* Random Number Generation Interface (12)               *
*********************************************************/
SEXP rcLScreateRG(SEXP sEnv,
                  SEXP snMethod)
{
    int          nErrorCode = LSERR_NO_ERROR;
    prLSenv      prEnv = NULL;
    pLSenv       pEnv = NULL;
    prLSrandGen  prRG = NULL;
    pLSrandGen   pRG = NULL;
    SEXP         sRG = R_NilValue;
    int          nMethod = Rf_asInteger(snMethod);

    if(sEnv != R_NilValue && R_ExternalPtrTag(sEnv) == tagLSenv)
    {
        prEnv = (prLSenv)R_ExternalPtrAddr(sEnv);
        pEnv = prEnv->pEnv;
    }
    else
    {
        nErrorCode = LSERR_ILLEGAL_NULL_POINTER;
        Rprintf("Failed to create Random Generator object (error %d)\n",nErrorCode);
        R_FlushConsole();
        return R_NilValue;
    }

    prRG = (prLSrandGen)malloc(sizeof(rLSrandGen)*1);
    if(prRG == NULL)
    {
        return R_NilValue;
    }

    pRG = LScreateRG(pEnv,nMethod);

    prRG->pRG = pRG;

    sRG = R_MakeExternalPtr(prRG,R_NilValue,R_NilValue);

    R_SetExternalPtrTag(sRG,tagLSrandGen);

    return sRG;
}

SEXP rcLScreateRGMT(SEXP sEnv,
                    SEXP snMethod)
{
    int          nErrorCode = LSERR_NO_ERROR;
    prLSenv      prEnv = NULL;
    pLSenv       pEnv = NULL;
    prLSrandGen  prRG = NULL;
    pLSrandGen   pRG = NULL;
    SEXP         sRG = R_NilValue;
    int          nMethod = Rf_asInteger(snMethod);

    if(sEnv != R_NilValue && R_ExternalPtrTag(sEnv) == tagLSenv)
    {
        prEnv = (prLSenv)R_ExternalPtrAddr(sEnv);
        pEnv = prEnv->pEnv;
    }
    else
    {
        nErrorCode = LSERR_ILLEGAL_NULL_POINTER;
        Rprintf("Failed to create Random Generator object (error %d)\n",nErrorCode);
        R_FlushConsole();
        return R_NilValue;
    }

    prRG = (prLSrandGen)malloc(sizeof(rLSrandGen)*1);
    if(prRG == NULL)
    {
        return R_NilValue;
    }

    pRG = LScreateRGMT(pEnv,nMethod);

    prRG->pRG = pRG;

    sRG = R_MakeExternalPtr(prRG,R_NilValue,R_NilValue);

    R_SetExternalPtrTag(sRG,tagLSrandGen);

    return sRG;
}

SEXP rcLSgetDoubleRV(SEXP   sRG)
{
    prLSrandGen   prRG;
    pLSrandGen    pRG;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdResult;
    SEXP      spdResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_RG_ERROR;

    PROTECT(spdResult = NEW_NUMERIC(1));
    nProtect += 1;
    pdResult = NUMERIC_POINTER(spdResult);

    *pdResult = LSgetDoubleRV(pRG);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetInt32RV(SEXP   sRG,
                    SEXP   siLow,
                    SEXP   siHigh)
{
    prLSrandGen   prRG;
    pLSrandGen    pRG;
    int           iLow = Rf_asInteger(siLow);
    int           iHigh = Rf_asInteger(siHigh);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnResult;
    SEXP      spnResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pnResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_RG_ERROR;

    PROTECT(spnResult = NEW_INTEGER(1));
    nProtect += 1;
    pnResult = INTEGER_POINTER(spnResult);

    *pnResult = LSgetInt32RV(pRG,iLow,iHigh);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetRGSeed(SEXP   sRG,
                   SEXP   snSeed)
{
    prLSrandGen   prRG;
    pLSrandGen    pRG;
    int           nSeed = Rf_asInteger(snSeed);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_RG_ERROR;

    LSsetRGSeed(pRG,nSeed);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSdisposeRG(SEXP   sRG)
{
    prLSrandGen   prRG;
    pLSrandGen    pRG;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_RG_ERROR;

    LSdisposeRG(&pRG);

    prRG->pRG = NULL;

    R_ClearExternalPtr(sRG);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetDistrParamRG(SEXP   sRG,
                         SEXP   siParam,
                         SEXP   sdParam)
{
    prLSrandGen   prRG;
    pLSrandGen    pRG;
    int           iParam = Rf_asInteger(siParam);
    double        dParam = Rf_asReal(sdParam);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_RG_ERROR;

    *pnErrorCode = LSsetDistrParamRG(pRG,iParam,dParam);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSsetDistrRG(SEXP   sRG,
                    SEXP   snDistType)
{
    prLSrandGen   prRG;
    pLSrandGen    pRG;
    int           nDistType = Rf_asInteger(snDistType);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_RG_ERROR;

    *pnErrorCode = LSsetDistrRG(pRG,nDistType);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetDistrRV(SEXP   sRG)
{
    prLSrandGen   prRG;
    pLSrandGen    pRG;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    double    *pdResult;
    SEXP      spdResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pdResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_RG_ERROR;

    PROTECT(spdResult = NEW_NUMERIC(1));
    nProtect += 1;
    pdResult = NUMERIC_POINTER(spdResult);

    *pnErrorCode = LSgetDistrRV(pRG,pdResult);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spdResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetInitSeed(SEXP   sRG)
{
    prLSrandGen   prRG;
    pLSrandGen    pRG;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnResult;
    SEXP      spnResult = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pnResult"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_RG_ERROR;

    PROTECT(spnResult = NEW_INTEGER(1));
    nProtect += 1;
    pnResult = INTEGER_POINTER(spnResult);

    *pnResult = LSgetInitSeed(pRG);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnResult);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSgetRGNumThreads(SEXP   sRG)
{
    prLSrandGen   prRG;
    pLSrandGen    pRG;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnThreads;
    SEXP      spnThreads = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode","pnThreads"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_RG_ERROR;

    PROTECT(spnThreads = NEW_INTEGER(1));
    nProtect += 1;
    pnThreads = INTEGER_POINTER(spnThreads);

    *pnErrorCode = LSgetRGNumThreads(pRG,pnThreads);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnThreads);
    }

    UNPROTECT(nProtect + 2);

    return rList;
}

SEXP rcLSfillRGBuffer(SEXP   sRG)
{
    prLSrandGen   prRG;
    pLSrandGen    pRG;

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[1] = {"ErrorCode"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 1;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_RG_ERROR;

    *pnErrorCode = LSfillRGBuffer(pRG);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    SET_VECTOR_ELT(rList, 0, spnErrorCode); 
    UNPROTECT(nProtect + 2);

    return rList;
}

/********************************************************
* Sprint Interface (1)                                  *
*********************************************************/
SEXP rcLSsolveFileLP(SEXP      sModel,
                     SEXP      sszFileNameMPS,
                     SEXP      sszFileNameSol,
                     SEXP      snNoOfColsEvaluatedPerSet,
                     SEXP      snNoOfColsSelectedPerSet,
                     SEXP      snTimeLimitSec)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    char      *szFileNameMPS = (char *)CHAR(STRING_ELT(sszFileNameMPS,0));
    char      *szFileNameSol = (char *)CHAR(STRING_ELT(sszFileNameSol,0));
    int       nNoOfColsEvaluatedPerSet = Rf_asInteger(snNoOfColsEvaluatedPerSet);
    int       nNoOfColsSelectedPerSet = Rf_asInteger(snNoOfColsSelectedPerSet);
    int       nTimeLimitSec = Rf_asInteger(snTimeLimitSec);

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnSolStatusParam;
    SEXP      spnSolStatusParam = R_NilValue;
    int       *pnNoOfConsMps;
    SEXP      spnNoOfConsMps = R_NilValue;
    long long *pnNoOfColsMps;
    SEXP      spnNoOfColsMps = R_NilValue;
    long long *pnErrorLine;
    SEXP      spnErrorLine = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[5] = {"ErrorCode", "pnSolStatusParam", "pnNoOfConsMps", 
                           "pnNoOfColsMps","pnErrorLine"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 5;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnSolStatusParam = NEW_INTEGER(1));
    nProtect += 1;
    pnSolStatusParam = INTEGER_POINTER(spnSolStatusParam);

    PROTECT(spnNoOfConsMps = NEW_INTEGER(1));
    nProtect += 1;
    pnNoOfConsMps = INTEGER_POINTER(spnNoOfConsMps);

    PROTECT(spnNoOfColsMps = NEW_INTEGER(1));
    nProtect += 1;
    pnNoOfColsMps = (long long *)INTEGER_POINTER(spnNoOfColsMps);

    PROTECT(spnErrorLine = NEW_INTEGER(1));
    nProtect += 1;
    pnErrorLine = (long long *)INTEGER_POINTER(spnErrorLine);

    *pnErrorCode = LSsolveFileLP(pModel,
                                 szFileNameMPS,
                                 szFileNameSol,
                                 nNoOfColsEvaluatedPerSet,
                                 nNoOfColsSelectedPerSet,
                                 nTimeLimitSec,
                                 pnSolStatusParam,
                                 pnNoOfConsMps,
                                 pnNoOfColsMps,
                                 pnErrorLine);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnSolStatusParam);
        SET_VECTOR_ELT(rList, 2, spnNoOfConsMps);
        SET_VECTOR_ELT(rList, 3, spnNoOfColsMps);
        SET_VECTOR_ELT(rList, 4, spnErrorLine);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}

/********************************************************
* Branch and price (1)                                  *
*********************************************************/
SEXP rcLSsolveMipBnp(SEXP      sModel,
                     SEXP      snBlock,
                     SEXP      spszFname)
{
    prLSmodel prModel;
    pLSmodel  pModel;
    int       nBlock = Rf_asInteger(snBlock);
    char      *pszFname = (char *)CHAR(STRING_ELT(spszFname,0));

    int       *pnErrorCode;
    SEXP      spnErrorCode = R_NilValue;
    int       *pnStatus;
    SEXP      spnStatus = R_NilValue;
    SEXP      rList = R_NilValue;
    char      *Names[2] = {"ErrorCode", "pnStatus"};
    SEXP      ListNames = R_NilValue;
    int       nNumItems = 2;
    int       nIdx, nProtect = 0;

    //errorcode item
    INI_ERR_CODE;

    CHECK_MODEL_ERROR;

    PROTECT(spnStatus = NEW_INTEGER(1));
    nProtect += 1;
    pnStatus = INTEGER_POINTER(spnStatus);

    *pnErrorCode = LSsolveMipBnp(pModel,nBlock,pszFname,pnStatus);

ErrorReturn:
    //allocate list
    SET_UP_LIST; 

    if(*pnErrorCode != LSERR_NO_ERROR)
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode);
    }
    else
    {
        SET_VECTOR_ELT(rList, 0, spnErrorCode); 
        SET_VECTOR_ELT(rList, 1, spnStatus);
    }

    UNPROTECT(nProtect + 2);
    
    return rList;
}
