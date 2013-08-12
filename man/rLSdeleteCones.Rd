\name{rLSdeleteCones}
\alias{rLSdeleteCones}

\title{Delete a set of cones in the given model.}

\description{
 R interface function for LINDO API function \code{LSdeleteCones}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSdeleteCones(model,nCones,paiCones)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nCones}{Number of cones to be deleted.}
 \item{paiCones}{An integer array containing the indices of the cones to be deleted.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

