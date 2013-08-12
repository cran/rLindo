\name{rLSdeleteSemiContVars}
\alias{rLSdeleteSemiContVars}

\title{Delete a set of semi-continuous variables in the given model.}

\description{
 R interface function for LINDO API function \code{LSdeleteSemiContVars}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSdeleteSemiContVars(model,nSCVars,paiSCVars)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nSCVars}{Number of semi-continuous variables to be deleted.}
 \item{paiSCVars}{An integer array containing the indices of the semi-continuous variables to be deleted.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

