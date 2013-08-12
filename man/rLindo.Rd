\name{rLindo}
\alias{rLindo}

\docType{package}

\title{R interface to LINDO API.}

\description{
 R interface to LINDO API functions. For more information, please refer to LINDO API User Manual.
}

\details{
 In R interface all function names use the convention of 'r' + LINDO API function name. E.g, 
 function rLScreateEnv in R corresponds to LScreateEnv in LINDO API.
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\examples{
#solve an LP

#load the package
library(rLindo)

#create LINDO enviroment object
rEnv <- rLScreateEnv()

#create LINDO model object
rModel <- rLScreateModel(rEnv)

#load LP data
nVars = 4
nCons = 4
nDir = 1
dObjConst = 0.
adC = c(1., 1., 1., 1.)
adB = c( 20., 20., 40., 10.)
acConTypes = "EGEG"
nNZ = 9
anBegCol = c( 0 , 2 , 5 , 7 , 9)
adA = c( 3.0, 4.0, 6.0, 5.0, 7.0, 8.0, 1.0, 2.0, 9.0)
anRowX = c( 0 , 2 , 1 , 2 , 3 , 2 , 3 , 0 , 1 )
pdLower = c(2, 1, -1.0E+30, -1.0E+30)
pdUpper = c(5, 1.0E+30, 10, 1.0E+30)
rLSloadLPData(rModel , nCons, nVars, nDir, dObjConst, adC, adB, acConTypes, 
              nNZ, anBegCol, NULL, adA, anRowX, pdLower, pdUpper)

#solve the model
rLSoptimize(rModel,0)

#get primal solution
rLSgetPrimalSolution(rModel)

#get dual solution
rLSgetDualSolution(rModel)

#retrieve information
rLSgetDInfo(rModel,LS_DINFO_POBJ)
rLSgetIInfo(rModel,LS_IINFO_MODEL_STATUS)

#get basis
rLSgetBasis(rModel)

#delete enviroment and model objects
#free memory
rLSdeleteModel(rModel)
rLSdeleteEnv(rEnv)
}
