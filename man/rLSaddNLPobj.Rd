\name{rLSaddNLPobj}
\alias{rLSaddNLPobj}

\title{Add NLP elements to the objective function for the given model.}

\description{
 R interface function for LINDO API function \code{LSaddNLPobj}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSaddNLPobj(model,nCols,paiCols,padColj)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nCols}{Number of variables for which NLP elements will be added.}
 \item{paiCols}{An integer array containing the variable indices of the nonlinear elements.}
 \item{padColj}{A double array containing the initial nonzero coefficients of the NLP elements.}
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
