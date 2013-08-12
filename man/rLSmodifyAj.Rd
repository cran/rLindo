\name{rLSmodifyAj}
\alias{rLSmodifyAj}

\title{Modify the coefficients for a given column at specified constraints.}

\description{
 R interface function for LINDO API function \code{LSmodifyAj}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSmodifyAj(model,iVar1,nRows,paiRows,padAj)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iVar1}{Index of the variable to modify the constraint coefficients.}
 \item{nRows}{Number of constraints to modify.}
 \item{paiRows}{An integer array containing the indices of the constraints to modify.}
 \item{padAj}{A double array containing the values of the new coefficients.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

