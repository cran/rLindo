\name{rLSmodifyRHS}
\alias{rLSmodifyRHS}

\title{Modify selected constraint right-hand sides of a given model.}

\description{
 R interface function for LINDO API function \code{LSmodifyRHS}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSmodifyRHS(model,nCons,paiCons,padB)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nCons}{Number of constraint right-hand sides to modify.}
 \item{paiCons}{An integer array containing the indices of the constraints whose right-hand sides are to be modified.}
 \item{padB}{A double array containing the new right-hand side values for the modified right-hand sides.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

