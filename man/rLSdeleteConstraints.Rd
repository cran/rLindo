\name{rLSdeleteConstraints}
\alias{rLSdeleteConstraints}

\title{Delete a set of constraints in the given model.}

\description{
 R interface function for LINDO API function \code{LSdeleteConstraints}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSdeleteConstraints(model,nCons,paiCons)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nCons}{Number of constraints to be deleted.}
 \item{paiCons}{An integer array containing the indices of the constraints to be deleted.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

