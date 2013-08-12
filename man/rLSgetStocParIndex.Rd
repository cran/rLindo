\name{rLSgetStocParIndex}
\alias{rLSgetStocParIndex}

\title{Get the index of stochastic parameter by name.}

\description{
 R interface function for LINDO API function \code{LSgetStocParIndex}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetStocParIndex(model,pszName)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszName}{The name of the stochastic parameter to return the index for.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnIndex}{Index of the stochastic parameter.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
