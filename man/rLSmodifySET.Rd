\name{rLSmodifySET}
\alias{rLSmodifySET}

\title{Modify the set for the specified cone.}

\description{
 R interface function for LINDO API function \code{LSmodifySET}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSmodifySET(model,cSETtype,iSETnum,iSETnnz,paiSETcols)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{cSETtype}{New type of the set.}
 \item{iSETnum}{Index of the set to modify.}
 \item{iSETnnz}{Number of variables in the set.}
 \item{paiSETcols}{An integer array containing the indices of the variables in the set.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

