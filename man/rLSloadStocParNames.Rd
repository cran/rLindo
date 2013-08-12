\name{rLSloadStocParNames}
\alias{rLSloadStocParNames}

\title{Load name data for stochastic parameters into the specified model structure.}

\description{
 R interface function for LINDO API function \code{LSloadStocParNames}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSloadStocParNames(model,nSvars,paszSVarNames)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nSvars}{Number of stochastic parameters.}
 \item{paszSVarNames}{A string array containing stochastic parameter names.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
