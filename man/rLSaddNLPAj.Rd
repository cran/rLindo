\name{rLSaddNLPAj}
\alias{rLSaddNLPAj}

\title{Add NLP elements to the specified column for the given model.}

\description{
 R interface function for LINDO API function \code{LSaddNLPAj}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSaddNLPAj(model,iVar1,nRows,paiRows,padAj)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iVar1}{The index of the variable to which NLP elements will be added.}
 \item{nRows}{Number of constraints for which NLP elements will be added.}
 \item{paiRows}{An integer array containing row indices of the nonlinear elements.}
 \item{padAj}{A double array containing the initial nonzero coefficients of the NLP elements}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadNLPData}}
}
