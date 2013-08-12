\name{rLSgetSampleSizes}
\alias{rLSgetSampleSizes}

\title{Retrieve the number of nodes to be sampled in all stages.}

\description{
 R interface function for LINDO API function \code{LSgetSampleSizes}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetSampleSizes(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{panSampleSize}{An integer array containing the sample size per stage.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
