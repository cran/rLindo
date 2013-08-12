\name{rLSloadQCData}
\alias{rLSloadQCData}

\title{Load quadratic program data into a model structure.}

\description{
 R interface function for LINDO API function \code{LSloadQCData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadQCData(model,nQCnnz,paiQCrows,paiQCcols1,paiQCcols2,padQCcoef)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nQCnnz}{The total number of nonzeros in quadratic coefficient matrices.}
 \item{paiQCrows}{An integer array containing the index of the constraint associated with each nonzero quadratic term.}
 \item{paiQCcols1}{An integer array containing the index of the first variable defining each quadratic term.}
 \item{paiQCcols2}{An integer array containing the index of the second variable defining each quadratic term.}
 \item{padQCcoef}{A double array containing the nonzero coefficients in the quadratic matrix.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
  