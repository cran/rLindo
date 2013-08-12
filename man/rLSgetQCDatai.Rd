\name{rLSgetQCDatai}
\alias{rLSgetQCDatai}

\title{Retrieve the quadratic data associated with constraint i from a model data structure.}

\description{
 R interface function for LINDO API function \code{LSgetQCDatai}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetQCDatai(model,iCon)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iCon}{The index of the constraint for which the quadratic data will be retrieved.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnQCnnz}{An integer indicating the number of nonzeros in the coefficient matrix of the quadratic term.}
 \item{paiQCcols1}{An integer array containing the index of the first variable defining each quadratic term.}
 \item{paiQCcols2}{An integer array containing the index of the second variable defining each quadratic term.}
 \item{padQCcoef}{A double array containing the nonzero coefficients in the quadratic matrix.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetQCData}}
}