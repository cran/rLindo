\name{rLSgetStocParData}
\alias{rLSgetStocParData}

\title{Retrieve the data of stochastic parameters.}

\description{
 R interface function for LINDO API function \code{LSgetStocParData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetStocParData(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{paiStages}{An integer array containing the stages of stochastic parameters.}
 \item{padVals}{A double array containing the values of stochastic parameters for the specified scenario.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
