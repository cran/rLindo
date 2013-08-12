\name{rLSloadStocParData}
\alias{rLSloadStocParData}

\title{Load stage structure of the stochastic parameters (SPARs) in the model.}

\description{
 R interface function for LINDO API function \code{LSloadStocParData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSloadStocParData(model,panSparStage,padSparValue)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{panSparStage}{An integer array containing the stages of SPARs.}
 \item{padSparValue}{A double array containing default values of SPARs.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
