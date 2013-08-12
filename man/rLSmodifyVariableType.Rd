\name{rLSmodifyVariableType}
\alias{rLSmodifyVariableType}

\title{Modify the types of the variables of the given model.}

\description{
 R interface function for LINDO API function \code{LSmodifyVariableType}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSmodifyVariableType(model,nVars,paiVars,pszVarTypes)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nVars}{Number of variables to modify.}
 \item{paiVars}{An integer array containing the indices of the variables to modify.}
 \item{pszVarTypes}{A character array in which each element is either:'C', 'B', or 'I'indicating each variable's type.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

