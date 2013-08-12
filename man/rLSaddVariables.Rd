\name{rLSaddVariables}
\alias{rLSaddVariables}

\title{Add variables to a given model.}

\description{
 R interface function for LINDO API function \code{LSaddVariables}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSaddVariables(model,nNumaddvars,pszVarTypes,paszVarNames = NULL,
                  paiAcols,panAcols = NULL,padAcoef,paiArows,padC,
                  padL = NULL,padU = NULL)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nNumaddvars}{Number of variables to append to the model.}
 \item{pszVarTypes}{A character array containing the types of each variable to be added to the model.}
 \item{paszVarNames}{A string array containing the names of each new variable.}
 \item{paiAcols}{An integer array containing the index of the first nonzero element in each new column.}
 \item{panAcols}{An integer array containing the length of each column.}
 \item{padAcoef}{A double array containing the nonzero coefficients of the new columns.}
 \item{paiArows}{An integer array containing the row indices of the nonzeros in the new columns.}
 \item{padC}{A double array containing the objective coefficients for each new variable.}
 \item{padL}{A double array containing the lower bound of each new variable.}
 \item{padU}{A double array containing the upper bound of each new variable.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadLPData}}
\code{\link{rLSaddConstraints}}
}

