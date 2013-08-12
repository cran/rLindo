\name{rLSloadSampleSizes}
\alias{rLSloadSampleSizes}

\title{Load sample sizes per stage for the stochastic model.}

\description{
 R interface function for LINDO API function \code{LSloadSampleSizes}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSloadSampleSizes(model,panSampleSize)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{panSampleSize}{An integer array containing the stage sample sizes.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
