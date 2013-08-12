\name{rLSmodifySemiContVars}
\alias{rLSmodifySemiContVars}

\title{Modify data of a set of semi-continuous variables in the given model.}

\description{
 R interface function for LINDO API function \code{LSmodifySemiContVars}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSmodifySemiContVars(model,nSCVars,paiSCVars,padL,padU)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nSCVars}{Number of semi-continuous variables to modify.}
 \item{paiSCVars}{An integer array containing the indices of the variables whose data are to be modified.}
 \item{padL}{A double array containing the new lower bound values for the semi-continuous variables.}
 \item{padU}{A double array containing the new upper bound values for the semi-continuous variables.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

