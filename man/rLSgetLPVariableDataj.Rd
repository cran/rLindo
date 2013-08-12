\name{rLSgetLPVariableDataj}
\alias{rLSgetLPVariableDataj}

\title{Retrieve the formulation data for a specified variable.}

\description{
 R interface function for LINDO API function \code{LSgetLPVariableDataj}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetLPVariableDataj(model,iVar)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iVar}{Index of the variable whose data you wish to retrieve.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pchVartype}{Type of the variable.}
 \item{pdC}{Objective coefficient of the variable.}
 \item{pdL}{Lower bound of the variable.}
 \item{pdU}{Upper bound of the variable.}
 \item{pnAnnz}{Number of nonzero constraint coefficients in the variable's column.}
 \item{paiArows}{An integer array containing the row indices of the variable's nonzeros.}
 \item{padAcoef}{A double array that returns the variable's nonzero coefficients.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetLPData}}
}