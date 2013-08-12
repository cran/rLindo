\name{rLSdeleteSETS}
\alias{rLSdeleteSETS}

\title{Delete the sets in the given model.}

\description{
 R interface function for LINDO API function \code{LSdeleteSETS}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSdeleteSETS(model,nSETS,paiSETS)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nSETS}{Number of sets to be deleted.}
 \item{paiSETS}{An integer array containing the indices of the sets to be deleted.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

