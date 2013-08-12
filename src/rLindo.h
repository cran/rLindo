/*  rLindo.h
    The R interface to LINDO API 8.0.
    This file includes all C wrapper functions for LINDO API C functions.
    Copyright (C) 2013 LINDO Systems.
*/

#include "stdlib.h"
#include "stdio.h"
#include "lindo.h"
#include "string.h"
#include "R.h"
#include "Rinternals.h"
#include "Rdefines.h"

typedef struct rLSenv
{
    pLSenv pEnv;
}rLSenv;

typedef rLSenv *prLSenv; 

typedef struct rLSmodel
{
    pLSmodel pModel;
}rLSmodel;

typedef rLSmodel *prLSmodel; 

typedef struct rLSsample
{
    pLSsample pSample;
}rLSsample;

typedef rLSsample *prLSsample; 

typedef struct rLSrandGen
{
    pLSrandGen pRG;
}rLSrandGen;

typedef rLSrandGen *prLSrandGen; 

extern SEXP tagLSprob;
extern SEXP tagLSenv;
extern SEXP tagLSsample;
extern SEXP tagLSrandGen;

/******************************************************
 * Structure Creation and Deletion Routines (5)       *
 ******************************************************/
SEXP rcLScreateEnv();

SEXP rcLScreateModel(SEXP sEnv);

SEXP rcLSdeleteEnv(SEXP sEnv);

SEXP rcLSdeleteModel(SEXP sModel);

SEXP rcLScopyParam(SEXP srsourceModel,
                   SEXP srtargetModel,
                   SEXP smSolverType);

/********************************************************
 * Model I-O Routines (18)                              *
 ********************************************************/
SEXP rcLSreadMPSFile(SEXP sModel,
                     SEXP spszFname,
                     SEXP snFormat);

SEXP rcLSwriteMPSFile(SEXP sModel,
                      SEXP spszFname,
                      SEXP snFormat);

SEXP rcLSreadLINDOFile(SEXP sModel,
                       SEXP spszFname);

SEXP rcLSwriteLINDOFile(SEXP sModel,
                        SEXP spszFname);

SEXP rcLSreadLINDOStream(SEXP sModel,
                         SEXP spszStream,
                         SEXP snStreamLen);

SEXP rcLSwriteLINGOFile(SEXP sModel,
                        SEXP spszFname);

SEXP rcLSwriteDualMPSFile(SEXP sModel,
                          SEXP spszFname,
                          SEXP snFormat,
                          SEXP snObjSense);

SEXP rcLSwriteSolution(SEXP sModel,
                       SEXP spszFname);

SEXP rcLSwriteSolutionOfType(SEXP sModel,
                             SEXP spszFname,
                             SEXP snFormat);

SEXP rcLSwriteIIS(SEXP sModel,
                  SEXP spszFname);

SEXP rcLSwriteIUS(SEXP sModel,
                  SEXP spszFname);

SEXP rcLSreadMPIFile(SEXP sModel,
                     SEXP spszFname);

SEXP rcLSwriteMPIFile(SEXP sModel,
                      SEXP spszFname);

SEXP rcLSwriteWithSetsAndSC(SEXP sModel,
                            SEXP spszFname,
                            SEXP snFormat);

SEXP rcLSreadBasis(SEXP sModel,
                   SEXP spszFname,
                   SEXP snFormat);

SEXP rcLSwriteBasis(SEXP sModel,
                    SEXP spszFname,
                    SEXP snFormat);

SEXP rcLSreadLPFile(SEXP sModel,
                    SEXP spszFname);

SEXP rcLSreadLPStream(SEXP sModel,
                      SEXP spszStream,
                      SEXP snStreamLen);

SEXP rcLSsetPrintLogNull(SEXP sModel);

/********************************************************
 * Error Handling Routines (3)                          *
 ********************************************************/
SEXP rcLSgetErrorMessage(SEXP   sEnv,
                         SEXP   snErrorCode);

SEXP rcLSgetFileError(SEXP sModel);

SEXP rcLSgetErrorRowIndex(SEXP sModel);

/***********************************************************
 * Routines for Setting and Retrieving Parameter Values(17)*
 ***********************************************************/
//no LSsetModelParameter and LSgetModelParameter
//no LSsetEnvParameter and LSgetEnvParameter,
//because an not deal with void *
SEXP rcLSsetModelDouParameter(SEXP sModel,
                              SEXP snParameter,
                              SEXP sdValue);

SEXP rcLSgetModelDouParameter(SEXP sModel,
                              SEXP snParameter);

SEXP rcLSsetModelIntParameter(SEXP sModel,
                              SEXP snParameter,
                              SEXP snValue);

SEXP rcLSgetModelIntParameter(SEXP sModel,
                              SEXP snParameter);

SEXP rcLSsetEnvDouParameter(SEXP sEnv,
                            SEXP snParameter,
                            SEXP sdValue);

SEXP rcLSgetEnvDouParameter(SEXP sEnv,
                            SEXP snParameter);

SEXP rcLSsetEnvIntParameter(SEXP sEnv,
                            SEXP snParameter,
                            SEXP snValue);

SEXP rcLSgetEnvIntParameter(SEXP sEnv,
                            SEXP snParameter);

SEXP rcLSreadModelParameter(SEXP sModel,
                            SEXP spszFname);

SEXP rcLSreadEnvParameter(SEXP sEnv,
                          SEXP spszFname);

SEXP rcLSwriteModelParameter(SEXP sModel,
                             SEXP spszFname);

SEXP rcLSgetIntParameterRange(SEXP sModel,
                              SEXP snParameter);

SEXP rcLSgetDouParameterRange(SEXP sModel,
                              SEXP snParameter);

//to be tested
SEXP rcLSgetParamShortDesc(SEXP sEnv,
                           SEXP snParam);

//to be tested
SEXP rcLSgetParamLongDesc(SEXP sEnv,
                          SEXP snParam);

//to be tested
SEXP rcLSgetParamMacroName(SEXP sEnv,
                           SEXP snParam);

//to be tested
SEXP rcLSgetParamMacroID(SEXP sEnv,
                         SEXP sszParam);

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
                    SEXP      spadU);

SEXP rcLSloadQCData(SEXP      sModel,
                    SEXP      snQCnnz,
                    SEXP      spaiQCrows,
                    SEXP      spaiQCcols1,
                    SEXP      spaiQCcols2,
                    SEXP      spadQCcoef);

SEXP rcLSloadConeData(SEXP      sModel,
                      SEXP      snCone,
                      SEXP      spszConeTypes,
                      SEXP      spaiConebegcone,
                      SEXP      spaiConecols);

SEXP rcLSloadSETSData(SEXP      sModel,
                      SEXP      snSETS,
                      SEXP      spszSETStype,
                      SEXP      spaiCARDnum,
                      SEXP      spaiSETSbegcol,
                      SEXP      spaiSETScols);

SEXP rcLSloadSemiContData(SEXP      sModel,
                          SEXP      snSCVars,
                          SEXP      spaiVars,
                          SEXP      spadL,
                          SEXP      spadU);

SEXP rcLSloadVarType(SEXP      sModel,
                     SEXP      spszVarTypes);

SEXP rcLSloadNameData(SEXP      sModel,
                      SEXP      spszTitle,
                      SEXP      spszObjName,
                      SEXP      spszRhsName,
                      SEXP      spszRngName,
                      SEXP      spszBndname,
                      SEXP      spaszConNames,
                      SEXP      spaszVarNames,
                      SEXP      spaszConeNames);

SEXP rcLSloadNLPData(SEXP      sModel,
                     SEXP      spaiNLPcols,
                     SEXP      spanNLPcols,
                     SEXP      spadNLPcoef,
                     SEXP      spaiNLProws,
                     SEXP      snNLPobj,
                     SEXP      spaiNLPobj,
                     SEXP      spadNLPobj);

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
                      SEXP      spadUB);

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
                     SEXP      spadUB);

SEXP rcLSloadStringData(SEXP      sModel,
                        SEXP      snStrings,
                        SEXP      spaszStringData);

SEXP rcLSloadString(SEXP      sModel,
                    SEXP      spszString);

SEXP rcLSdeleteStringData(SEXP      sModel);

SEXP rcLSdeleteString(SEXP      sModel);

SEXP rcLSgetStringValue(SEXP      sModel,
                        SEXP      siString);

SEXP rcLSgetConstraintProperty(SEXP      sModel,
                               SEXP      sndxCons);

SEXP rcLSsetConstraintProperty(SEXP      sModel,
                               SEXP      sndxCons,
                               SEXP      snConptype);

SEXP rcLSloadMultiStartSolution(SEXP      sModel,
                                SEXP      snIndex);

SEXP rcLSloadGASolution(SEXP      sModel,
                        SEXP      snIndex);


/********************************************************
* Solver Initialization Routines (9)                    *
*********************************************************/
SEXP rcLSloadBasis(SEXP      sModel,
                   SEXP      spanCstatus,
                   SEXP      spanRstatus);

SEXP rcLSloadVarPriorities(SEXP      sModel,
                           SEXP      spanCprior);

SEXP rcLSreadVarPriorities(SEXP      sModel,
                           SEXP      spszFname);

SEXP rcLSloadVarStartPoint(SEXP      sModel,
                           SEXP      spadPrimal);

SEXP rcLSloadVarStartPointPartial(SEXP      sModel,
                                  SEXP      snCols,
                                  SEXP      spaiCols,
                                  SEXP      spadPrimal);

SEXP rcLSloadMIPVarStartPoint(SEXP      sModel,
                              SEXP      spadPrimal);

SEXP rcLSloadMIPVarStartPointPartial(SEXP      sModel,
                                     SEXP      snCols,
                                     SEXP      spaiCols,
                                     SEXP      spaiPrimal);

SEXP rcLSreadVarStartPoint(SEXP      sModel,
                           SEXP      spszFname);

SEXP rcLSloadBlockStructure(SEXP      sModel,
                            SEXP      snBlock,
                            SEXP      spanRblock,
                            SEXP      spanCblock,
                            SEXP      snType);

/********************************************************
 * Optimization Routines (6)                            *
 ********************************************************/
SEXP rcLSoptimize(SEXP  sModel,
                  SEXP  snMethod);

SEXP rcLSsolveMIP(SEXP  sModel);

SEXP rcLSsolveGOP(SEXP  sModel);

SEXP rcLSoptimizeQP(SEXP  sModel);

SEXP rcLScheckConvexity(SEXP  sModel);

SEXP rcLSsolveSBD(SEXP  sModel,
                  SEXP  snStages,
                  SEXP  spanRowStage,
                  SEXP  spanColStage);

/********************************************************
* Solution Query Routines (15)                          *
*********************************************************/
//no LSgetInfo because can not deal with void *

SEXP rcLSgetIInfo(SEXP  sModel,
                  SEXP  snQuery);

SEXP rcLSgetDInfo(SEXP  sModel,
                  SEXP  snQuery);

SEXP rcLSgetPrimalSolution(SEXP  sModel);

SEXP rcLSgetDualSolution(SEXP  sModel);

SEXP rcLSgetReducedCosts(SEXP  sModel);

SEXP rcLSgetReducedCostsCone(SEXP  sModel);

SEXP rcLSgetSlacks(SEXP  sModel);

SEXP rcLSgetBasis(SEXP  sModel);

SEXP rcLSgetSolution(SEXP  sModel,
                     SEXP  snWhich);

SEXP rcLSgetMIPPrimalSolution(SEXP  sModel);

SEXP rcLSgetMIPDualSolution(SEXP  sModel);

SEXP rcLSgetMIPReducedCosts(SEXP  sModel);

SEXP rcLSgetMIPSlacks(SEXP  sModel);

SEXP rcLSgetMIPBasis(SEXP  sModel);

SEXP rcLSgetNextBestMIPSol(SEXP  sModel);

/********************************************************
* Model Query Routines    (29)                          *
*********************************************************/
SEXP rcLSgetLPData(SEXP  sModel);

SEXP rcLSgetQCData(SEXP  sModel);

SEXP rcLSgetQCDatai(SEXP  sModel,
                    SEXP  siCon);

SEXP rcLSgetVarType(SEXP  sModel);

SEXP rcLSgetVarStartPoint(SEXP  sModel);

SEXP rcLSgetVarStartPointPartial(SEXP  sModel);

SEXP rcLSgetMIPVarStartPointPartial(SEXP  sModel);

SEXP rcLSgetMIPVarStartPoint(SEXP  sModel);

SEXP rcLSgetSETSData(SEXP  sModel);

SEXP rcLSgetSETSDatai(SEXP  sModel, 
                      SEXP  siSet);

SEXP rcLSgetSemiContData(SEXP  sModel);

SEXP rcLSgetLPVariableDataj(SEXP  sModel,
                            SEXP  siVar);

SEXP rcLSgetVariableNamej(SEXP  sModel,
                          SEXP  siVar);

SEXP rcLSgetVariableIndex(SEXP  sModel,
                          SEXP  spszVarName);

SEXP rcLSgetConstraintNamei(SEXP     sModel,
                            SEXP     siCon);

SEXP rcLSgetConstraintIndex(SEXP  sModel,
                            SEXP  spszConName);

SEXP rcLSgetConstraintDatai(SEXP      sModel,
                            SEXP      siCon);

SEXP rcLSgetLPConstraintDatai(SEXP      sModel,
                              SEXP      siCon);

SEXP rcLSgetConeNamei(SEXP     sModel,
                      SEXP     siCone);

SEXP rcLSgetConeIndex(SEXP  sModel,
                      SEXP  spszConeName);

SEXP rcLSgetConeDatai(SEXP      sModel,
                      SEXP      siCone);

SEXP rcLSgetNLPData(SEXP      sModel);

SEXP rcLSgetNLPConstraintDatai(SEXP  sModel,
                               SEXP  siCon);

SEXP rcLSgetNLPVariableDataj(SEXP  sModel,
                             SEXP  siVar);

SEXP rcLSgetNLPObjectiveData(SEXP  sModel);

SEXP rcLSgetDualModel(SEXP sModel,
                      SEXP sDualModel);

//no SEXP rcLSgetInstruct(SEXP sModel);

SEXP rcLScalinfeasMIPsolution(SEXP sModel,
                              SEXP spadPrimalMipsol);

SEXP rcLSgetRoundMIPsolution(SEXP      sModel,
                             SEXP      spadPrimal,
                             SEXP      siUseOpti);

//no SEXP rcLSgetDuplicateColumns(SEXP  sModel,SEXP  snCheckVals);

SEXP rcLSgetRangeData(SEXP      sModel);

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
                        SEXP      spadB);

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
                      SEXP      spadU);

SEXP rcLSaddCones(SEXP      sModel,
                  SEXP      snCone,
                  SEXP      spszConeTypes,
                  SEXP      spaszConenames,
                  SEXP      spaiConebegcol,
                  SEXP      spaiConecols);

SEXP rcLSaddSETS(SEXP      sModel,
                 SEXP      snSETS,
                 SEXP      spszSETStype,
                 SEXP      spaiCARDnum,
                 SEXP      spaiSETSbegcol,
                 SEXP      spaiSETScols);

SEXP rcLSaddQCterms(SEXP      sModel,
                    SEXP      snQCnonzeros,
                    SEXP      spaiQCconndx,
                    SEXP      spaiQCvarndx1,
                    SEXP      spaiQCvarndx2,
                    SEXP      spadQCcoef);

SEXP rcLSdeleteConstraints(SEXP      sModel,
                           SEXP      snCons,
                           SEXP      spaiCons);

SEXP rcLSdeleteCones(SEXP      sModel,
                     SEXP      snCones,
                     SEXP      spaiCones);

SEXP rcLSdeleteSETS(SEXP      sModel,
                    SEXP      snSETS,
                    SEXP      spaiSETS);

SEXP rcLSdeleteSemiContVars(SEXP      sModel,
                            SEXP      snSCVars,
                            SEXP      spaiSCVars);

SEXP rcLSdeleteVariables(SEXP      sModel,
                         SEXP      snVars,
                         SEXP      spaiVars);

SEXP rcLSdeleteQCterms(SEXP      sModel,
                       SEXP      snCons,
                       SEXP      spaiCons);

SEXP rcLSdeleteAj(SEXP      sModel,
                  SEXP      siVar1,
                  SEXP      snRows,
                  SEXP      spaiRows);

SEXP rcLSmodifyLowerBounds(SEXP      sModel,
                           SEXP      snVars,
                           SEXP      spaiVars,
                           SEXP      spadL);

SEXP rcLSmodifyUpperBounds(SEXP      sModel,
                           SEXP      snVars,
                           SEXP      spaiVars,
                           SEXP      spadU);

SEXP rcLSmodifyRHS(SEXP      sModel,
                   SEXP      snCons,
                   SEXP      spaiCons,
                   SEXP      spadB);

SEXP rcLSmodifyObjective(SEXP      sModel,
                         SEXP      snVars,
                         SEXP      spaiVars,
                         SEXP      spadC);

SEXP rcLSmodifyAj(SEXP     sModel,
                  SEXP     siVar1,
                  SEXP     snRows,
                  SEXP     spaiRows,
                  SEXP     spadAj);

SEXP rcLSmodifyCone(SEXP     sModel,
                    SEXP     scConeType,
                    SEXP     siConeNum,
                    SEXP     siConeNnz,
                    SEXP     spaiConeCols);

SEXP rcLSmodifySET(SEXP     sModel,
                   SEXP     scSETtype,
                   SEXP     siSETnum,
                   SEXP     siSETnnz,
                   SEXP     spaiSETcols);

SEXP rcLSmodifySemiContVars(SEXP     sModel,
                            SEXP     snSCVars,
                            SEXP     spaiSCVars,
                            SEXP     spadL,
                            SEXP     spadU);

SEXP rcLSmodifyConstraintType(SEXP     sModel,
                              SEXP     snCons,
                              SEXP     spaiCons,
                              SEXP     spszConTypes);

SEXP rcLSmodifyVariableType(SEXP     sModel,
                            SEXP     snVars,
                            SEXP     spaiVars,
                            SEXP     spszVarTypes);

SEXP rcLSaddNLPAj(SEXP     sModel,
                  SEXP     siVar1,
                  SEXP     snRows,
                  SEXP     spaiRows,
                  SEXP     spadAj);

SEXP rcLSaddNLPobj(SEXP      sModel,
                   SEXP      snCols,
                   SEXP      spaiCols,
                   SEXP      spadColj);

SEXP rcLSdeleteNLPobj(SEXP      sModel,
                      SEXP      snCols,
                      SEXP      spaiCols);

/********************************************************
* Model & Solution Analysis Routines (10)               *
*********************************************************/
SEXP rcLSgetConstraintRanges(SEXP      sModel);

SEXP rcLSgetObjectiveRanges(SEXP      sModel);

SEXP rcLSgetBoundRanges(SEXP      sModel);

SEXP rcLSgetBestBounds(SEXP      sModel);

SEXP rcLSfindIIS(SEXP      sModel,
                 SEXP      snLevel);

SEXP rcLSfindIUS(SEXP      sModel,
                 SEXP      snLevel);

SEXP rcLSfindBlockStructure(SEXP      sModel,
                            SEXP      snBlock,
                            SEXP      snType);

SEXP rcLSgetIIS(SEXP      sModel);

SEXP rcLSgetIUS(SEXP      sModel);

SEXP rcLSgetBlockStructure(SEXP      sModel);

/********************************************************
* Advanced Routines (0)                                 *
*********************************************************/

/********************************************************
* Callback Management Routines(0)                       *
*********************************************************/

/********************************************************
* Memory Related Routines(9)                            *
*********************************************************/
SEXP rcLSfreeSolverMemory(SEXP      sModel);

SEXP rcLSfreeHashMemory(SEXP      sModel);

SEXP rcLSfreeSolutionMemory(SEXP      sModel);

SEXP rcLSfreeMIPSolutionMemory(SEXP      sModel);

SEXP rcLSfreeGOPSolutionMemory(SEXP      sModel);

SEXP rcLSsetProbAllocSizes(SEXP      sModel,
                           SEXP      sn_vars_alloc,
                           SEXP      sn_cons_alloc,
                           SEXP      sn_QC_alloc,
                           SEXP      sn_Annz_alloc,
                           SEXP      sn_Qnnz_alloc,
                           SEXP      sn_NLPnnz_alloc);

SEXP rcLSsetProbNameAllocSizes(SEXP      sModel,
                               SEXP      sn_varname_alloc,
                               SEXP      sn_rowname_alloc);

SEXP rcLSaddEmptySpacesAcolumns(SEXP      sModel,
                                SEXP      spaiColnnz);

SEXP rcLSaddEmptySpacesNLPAcolumns(SEXP      sModel,
                                   SEXP      spaiColnnz);

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
                           SEXP      siType);

SEXP rcLSwriteDeteqLINDOFile(SEXP      sModel,
                             SEXP      spszFilename,
                             SEXP      siType);

SEXP rcLSwriteSMPSFile(SEXP      sModel,
                       SEXP      spszCorefile,
                       SEXP      spszTimefile,
                       SEXP      spszStocfile,
                       SEXP      snMPStype);

SEXP rcLSreadSMPSFile(SEXP      sModel,
                      SEXP      spszCorefile,
                      SEXP      spszTimefile,
                      SEXP      spszStocfile,
                      SEXP      snMPStype);

SEXP rcLSwriteSMPIFile(SEXP      sModel,
                       SEXP      spszCorefile,
                       SEXP      spszTimefile,
                       SEXP      spszStocfile);

SEXP rcLSreadSMPIFile(SEXP      sModel,
                      SEXP      spszCorefile,
                      SEXP      spszTimefile,
                      SEXP      spszStocfile);

SEXP rcLSwriteScenarioSolutionFile(SEXP      sModel,
                                   SEXP      sjScenario,
                                   SEXP      spszFname);

SEXP rcLSwriteNodeSolutionFile(SEXP      sModel,
                               SEXP      sjScenario,
                               SEXP      siStage,
                               SEXP      spszFname);

SEXP rcLSwriteScenarioMPIFile(SEXP      sModel,
                              SEXP      sjScenario,
                              SEXP      spszFname);

SEXP rcLSwriteScenarioMPSFile(SEXP      sModel,
                              SEXP      sjScenario,
                              SEXP      spszFname,
                              SEXP      snFormat);

SEXP rcLSwriteScenarioLINDOFile(SEXP      sModel,
                                SEXP      sjScenario,
                                SEXP      spszFname);

SEXP rcLSsetModelStocDouParameter(SEXP      sModel,
                                  SEXP      siPar,
                                  SEXP      sdVal);

SEXP rcLSgetModelStocDouParameter(SEXP      sModel,
                                  SEXP      siPar);

SEXP rcLSsetModelStocIntParameter(SEXP      sModel,
                                  SEXP      siPar,
                                  SEXP      siVal);

SEXP rcLSgetModelStocIntParameter(SEXP      sModel,
                                  SEXP      siPar);

SEXP rcLSgetScenarioIndex(SEXP      sModel,
                          SEXP      spszName);

SEXP rcLSgetStageIndex(SEXP      sModel,
                       SEXP      spszName);

SEXP rcLSgetStocParIndex(SEXP      sModel,
                         SEXP      spszName);

SEXP rcLSgetStocParName(SEXP      sModel,
                        SEXP      snIndex);

SEXP rcLSgetScenarioName(SEXP      sModel,
                         SEXP      snIndex);

SEXP rcLSgetStageName(SEXP      sModel,
                      SEXP      snIndex);

//no LSgetStocInfo because can not deal with void *

SEXP rcLSgetStocIInfo(SEXP      sModel,
                      SEXP      snQuery,
                      SEXP      snParam);

SEXP rcLSgetStocDInfo(SEXP      sModel,
                      SEXP      snQuery,
                      SEXP      snParam);

SEXP rcLSgetStocSInfo(SEXP      sModel,
                      SEXP      snQuery,
                      SEXP      snParam);

//no LSgetStocCCPInfo because can not deal with void *

SEXP rcLSgetStocCCPIInfo(SEXP      sModel,
                         SEXP      snQuery,
                         SEXP      snScenarioIndex,
                         SEXP      snCPPIndex);

SEXP rcLSgetStocCCPDInfo(SEXP      sModel,
                         SEXP      snQuery,
                         SEXP      snScenarioIndex,
                         SEXP      snCPPIndex);

SEXP rcLSgetStocCCPSInfo(SEXP      sModel,
                         SEXP      snQuery,
                         SEXP      snScenarioIndex,
                         SEXP      snCPPIndex);

SEXP rcLSloadSampleSizes(SEXP      sModel,
                         SEXP      spanSampleSize);

SEXP rcLSloadConstraintStages(SEXP      sModel,
                              SEXP      spanStage);

SEXP rcLSloadVariableStages(SEXP      sModel,
                            SEXP      spanStage);

SEXP rcLSloadStageData(SEXP      sModel,
                       SEXP      snumStages,
                       SEXP      spanRstage,
                       SEXP      spanCstage);

SEXP rcLSloadStocParData(SEXP      sModel,
                         SEXP      spanSparStage,
                         SEXP      spadSparValue);

SEXP rcLSloadStocParNames(SEXP      sModel,
                          SEXP      snSvars,
                          SEXP      spaszSVarNames);

SEXP rcLSgetDeteqModel(SEXP      sModel,
                       SEXP      siDeqType);

SEXP rcLSaggregateStages(SEXP      sModel,
                         SEXP      spanScheme,
                         SEXP      snLength);

SEXP rcLSgetStageAggScheme(SEXP      sModel);

SEXP rcLSdeduceStages(SEXP      sModel,
                      SEXP      snMaxStage,
                      SEXP      spanRowStagesIn,
                      SEXP      spanColStagesIn,
                      SEXP      spanSparStage);

SEXP rcLSsolveSP(SEXP      sModel);

SEXP rcLSsolveHS(SEXP      sModel,
                 SEXP      snSearchMethod);

SEXP rcLSgetScenarioObjective(SEXP      sModel,
                              SEXP      sjScenario);

SEXP rcLSgetNodePrimalSolution(SEXP      sModel,
                               SEXP      sjScenario,
                               SEXP      siStage);

SEXP rcLSgetNodeDualSolution(SEXP      sModel,
                             SEXP      sjScenario,
                             SEXP      siStage);

SEXP rcLSgetNodeReducedCost(SEXP      sModel,
                            SEXP      sjScenario,
                            SEXP      siStage);

SEXP rcLSgetNodeSlacks(SEXP      sModel,
                       SEXP      sjScenario,
                       SEXP      siStage);

SEXP rcLSgetScenarioPrimalSolution(SEXP      sModel,
                                   SEXP      sjScenario);

SEXP rcLSgetScenarioReducedCost(SEXP      sModel,
                                SEXP      sjScenario);

SEXP rcLSgetScenarioDualSolution(SEXP      sModel,
                                 SEXP      sjScenario);

SEXP rcLSgetScenarioSlacks(SEXP      sModel,
                           SEXP      sjScenario);

SEXP rcLSgetNodeListByScenario(SEXP      sModel,
                               SEXP      sjScenario);

SEXP rcLSgetProbabilityByScenario(SEXP      sModel,
                                  SEXP      sjScenario);

SEXP rcLSgetProbabilityByNode(SEXP      sModel,
                              SEXP      siNode);

SEXP rcLSgetStocParData(SEXP      sModel);

SEXP rcLSaddDiscreteBlocks(SEXP      sModel,
                           SEXP      siStage,
                           SEXP      snRealzBlock,
                           SEXP      spadProb,
                           SEXP      spakStart,
                           SEXP      spaiRows,
                           SEXP      spaiCols,
                           SEXP      spaiStvs,
                           SEXP      spadVals,
                           SEXP      snModifyRule);

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
                     SEXP      snModifyRule);

SEXP rcLSaddDiscreteIndep(SEXP      sModel,
                          SEXP      siRow,
                          SEXP      sjCol,
                          SEXP      siStv,
                          SEXP      snRealizations,
                          SEXP      spadProbs,
                          SEXP      spadVals,
                          SEXP      snModifyRule);

SEXP rcLSaddParamDistIndep(SEXP      sModel,
                           SEXP      siRow,
                           SEXP      sjCol,
                           SEXP      siStv,
                           SEXP      snDistType,
                           SEXP      snParams,
                           SEXP      spadParams,
                           SEXP      siModifyRule);

//no LSaddUserDist

SEXP rcLSaddChanceConstraint(SEXP      sModel,
                             SEXP      siSense,
                             SEXP      snCons,
                             SEXP      spaiCons,
                             SEXP      sdPrLevel,
                             SEXP      sdObjWeight);

SEXP rcLSsetNumStages(SEXP      sModel,
                      SEXP      snumStages);

SEXP rcLSgetStocParOutcomes(SEXP      sModel,
                            SEXP      sjScenario);

SEXP rcLSloadCorrelationMatrix(SEXP      sModel,
                               SEXP      snDim,
                               SEXP      snCorrType,
                               SEXP      snQCnnz,
                               SEXP      spaiQCcols1,
                               SEXP      spaiQCcols2,
                               SEXP      spadQCcoef);

SEXP rcLSgetCorrelationMatrix(SEXP      sModel,
                              SEXP      siFlag,
                              SEXP      snCorrType);

SEXP rcLSgetStocParSample(SEXP      sModel,
                          SEXP      siStv,
                          SEXP      siRow,
                          SEXP      sjCol);

SEXP rcLSgetDiscreteBlocks(SEXP      sModel,
                           SEXP      siEvent);

SEXP rcLSgetDiscreteBlockOutcomes(SEXP      sModel,
                                  SEXP      siEvent,
                                  SEXP      siRealz);

SEXP rcLSgetDiscreteIndep(SEXP      sModel,
                          SEXP      siEvent);

SEXP rcLSgetParamDistIndep(SEXP      sModel,
                           SEXP      siEvent);

SEXP rcLSgetScenario(SEXP      sModel,
                     SEXP      sjScenario);

SEXP rcLSgetChanceConstraint(SEXP      sModel,
                             SEXP      siChance);

SEXP rcLSgetSampleSizes(SEXP      sModel);

SEXP rcLSgetConstraintStages(SEXP      sModel);

SEXP rcLSgetVariableStages(SEXP      sModel);

SEXP rcLSgetStocRowIndices(SEXP      sModel);

SEXP rcLSsetStocParRG(SEXP      sModel,
                      SEXP      siStv,
                      SEXP      siRow,
                      SEXP      sjCol,
                      SEXP      sRG);

SEXP rcLSgetScenarioModel(SEXP      sModel,
                          SEXP      sjScenario);

SEXP rcLSfreeStocMemory(SEXP      sModel);

SEXP rcLSfreeStocHashMemory(SEXP      sModel);

//no LSgetModelStocParameter because can not deal with void *

SEXP rcLSgetModelStocParameterInt(SEXP      sModel,
                                  SEXP      snQuery);

SEXP rcLSgetModelStocParameterDou(SEXP      sModel,
                                  SEXP      snQuery);

SEXP rcLSgetModelStocParameterChar(SEXP      sModel,
                                   SEXP      snQuery);

SEXP rcLSsetModelStocParameterInt(SEXP       sModel,
                                  SEXP       snQuery,
                                  SEXP       spnResult);

SEXP rcLSsetModelStocParameterDou(SEXP       sModel,
                                  SEXP       snQuery,
                                  SEXP       spdResult);

SEXP rcLSsetModelStocParameterChar(SEXP       sModel,
                                   SEXP       snQuery,
                                   SEXP       spacResult);

SEXP rcLSgetEnvStocParameterInt(SEXP      sEnv,
                                SEXP      snQuery);

SEXP rcLSgetEnvStocParameterDou(SEXP      sEnv,
                                SEXP      snQuery);

SEXP rcLSgetEnvStocParameterChar(SEXP      sEnv,
                                 SEXP      snQuery);

SEXP rcLSsetEnvStocParameterInt(SEXP       sEnv,
                                SEXP       snQuery,
                                SEXP       spnResult);

SEXP rcLSsetEnvStocParameterDou(SEXP       sEnv,
                                SEXP       snQuery,
                                SEXP       spdResult);

SEXP rcLSsetEnvStocParameterChar(SEXP       sEnv,
                                 SEXP       snQuery,
                                 SEXP       spacResult);

/********************************************************
* Statistical Calculations Interface (15)               *
*********************************************************/
SEXP rcLSsampCreate(SEXP sEnv,
                    SEXP snDistType);

SEXP rcLSsampDelete(SEXP  sSample);

//no LSsampSetUserDistr because can not deal with void *

SEXP rcLSsampSetDistrParam(SEXP  sSample,
                           SEXP  snIndex,
                           SEXP  sdValue);

SEXP rcLSsampGetDistrParam(SEXP  sSample,
                           SEXP  snIndex);

SEXP rcLSsampEvalDistr(SEXP  sSample,
                       SEXP  snFuncType,
                       SEXP  sdXval);

SEXP rcLSsampEvalUserDistr(SEXP  sSample,
                           SEXP  snFuncType,
                           SEXP  spadXval,
                           SEXP  snDim);

SEXP rcLSsampSetRG(SEXP  sSample,
                   SEXP  sRG);

SEXP rcLSsampGenerate(SEXP  sSample,
                      SEXP  snMethod,
                      SEXP  snSize);

//no LSsampGetPointsPtr

SEXP rcLSsampGetPoints(SEXP  sSample);

SEXP rcLSsampLoadPoints(SEXP  sSample,
                        SEXP  snSampSize,
                        SEXP  spsdXval);

//no LSsampGetCIPointsPtr

SEXP rcLSsampGetCIPoints(SEXP  sSample);

//no LSsampInduceCorrelation

//no LSsampGetCorrelationMatrix

SEXP rcLSsampLoadDiscretePdfTable(SEXP  sSample,
                                  SEXP  snLen,
                                  SEXP  spadProb,
                                  SEXP  spadVals);

SEXP rcLSsampGetDiscretePdfTable(SEXP  sSample);

//no LSsampGetInfo because can not deal with void *

SEXP rcLSsampGetIInfo(SEXP      sSample,
                      SEXP      snQuery);

SEXP rcLSsampGetDInfo(SEXP      sSample,
                      SEXP      snQuery);

/********************************************************
* Random Number Generation Interface (12)               *
*********************************************************/
SEXP rcLScreateRG(SEXP sEnv,
                  SEXP snMethod);

SEXP rcLScreateRGMT(SEXP sEnv,
                    SEXP snMethod);

SEXP rcLSgetDoubleRV(SEXP   sRG);

SEXP rcLSgetInt32RV(SEXP   sRG,
                    SEXP   siLow,
                    SEXP   siHigh);

SEXP rcLSsetRGSeed(SEXP   sRG,
                   SEXP   snSeed);

SEXP rcLSdisposeRG(SEXP   sRG);

SEXP rcLSsetDistrParamRG(SEXP   sRG,
                         SEXP   siParam,
                         SEXP   sdParam);

SEXP rcLSsetDistrRG(SEXP   sRG,
                    SEXP   snDistType);

SEXP rcLSgetDistrRV(SEXP   sRG);

SEXP rcLSgetInitSeed(SEXP   sRG);

SEXP rcLSgetRGNumThreads(SEXP   sRG);

SEXP rcLSfillRGBuffer(SEXP   sRG);

//no LSgetRGBufferPtr

//no LSgetJavaHandle

//no LSsetJavaHandle

//no LSgetHistogram

//no LSsampGetCorrDiff

/********************************************************
* Sprint Interface (1)                                  *
*********************************************************/
SEXP rcLSsolveFileLP(SEXP      sModel,
                     SEXP      sszFileNameMPS,
                     SEXP      sszFileNameSol,
                     SEXP      snNoOfColsEvaluatedPerSet,
                     SEXP      snNoOfColsSelectedPerSet,
                     SEXP      snTimeLimitSec);

/********************************************************
* Date/Time Functions (0)                               *
*********************************************************/

/********************************************************
* Branch and price (1)                                  *
*********************************************************/
SEXP rcLSsolveMipBnp(SEXP      sModel,
                     SEXP      snBlock,
                     SEXP      spszFname);
