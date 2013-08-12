\name{rLSgetStocParName}
\alias{rLSgetStocParName}

\title{Get name of stochastic parameter by index.}

\description{
 R interface function for LINDO API function \code{LSgetStocParName}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetStocParName(model,nIndex)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nIndex}{Index of the stochastic parameter.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pachName}{The name of the stochastic parameter.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
