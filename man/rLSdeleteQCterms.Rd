\name{rLSdeleteQCterms}
\alias{rLSdeleteQCterms}

\title{Delete the quadratic terms from a set of constraints in the given model.}

\description{
 R interface function for LINDO API function \code{LSdeleteQCterms}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSdeleteQCterms(model,nCons,paiCons)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nCons}{Number of constraints in the model whose quadratic terms will be deleted.}
 \item{paiCons}{An integer array containing the indices of the constraints whose quadratic terms will be deleted.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

