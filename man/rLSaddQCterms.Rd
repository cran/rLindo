\name{rLSaddQCterms}
\alias{rLSaddQCterms}

\title{Add quadratic elements to the given model.}

\description{
 R interface function for LINDO API function \code{LSaddQCterms}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSaddQCterms(model,nQCnonzeros,paiQCconndx,paiQCvarndx1,paiQCvarndx2,padQCcoef)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nQCnonzeros}{Total number of nonzeros in quadratic coefficient matrices to be added.}
 \item{paiQCconndx}{An integer array containing the index of the constraint associated with each nonzero quadratic term.}
 \item{paiQCvarndx1}{An integer array containing the first variable defining each quadratic term.}
 \item{paiQCvarndx2}{An integer array containing the second variable defining each quadratic term.}
 \item{padQCcoef}{A double array containing the nonzero coefficients in the quadratic matrix.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadQCData}}
}

