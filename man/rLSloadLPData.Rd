\name{rLSloadLPData}
\alias{rLSloadLPData}

\title{Load the given LP data into a model structure.}

\description{
 R interface function for LINDO API function \code{LSloadLPData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadLPData(model,nCons,nVars,nObjSense,dObjConst,padC,padB,pszConTypes,nAnnz,
              paiAcols,panAcols = NULL,padAcoef,paiArows,padL  = NULL,padU = NULL)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nCons}{Number of constraints in the model.}
 \item{nVars}{Number of variables in the model.}
 \item{nObjSense}{An indicator stating whether the objective is to be maximized or minimized.}
 \item{dObjConst}{A constant value to be added to the objective value.}
 \item{padC}{A double array containing the objective coefficients.}
 \item{padB}{A double array containing the constraint right hand side coefficients.}
 \item{pszConTypes}{A character vector containing the type of each constraint. Each constraint is represented 
       by a single byte in the array. Valid values for each constraint are 'L', 'E', 'G', or 'N' for 
       less than or equal to, equal to, greater than or equal to, or neutral, respectively.}
 \item{nAnnz}{The number of nonzeros in the constraint matrix.}
 \item{paiAcols}{An integer array containing the index of the first nonzero in each column.}
 \item{panAcols}{An integer array containing the length of each column.}
 \item{padAcoef}{A double array containing the nonzero coefficients of the constraint matrix.}
 \item{paiArows}{An integer array containing the row indices of the nonzeros in the constraint matrix.}
 \item{padL}{A double array vector containing the lower bound of each variable.}
 \item{padU}{A double array vector containing the upper bound of each variable.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
