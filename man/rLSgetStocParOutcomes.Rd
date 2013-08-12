\name{rLSgetStocParOutcomes}
\alias{rLSgetStocParOutcomes}

\title{Retrieve the outcomes of stochastic parameters for the specified scenario.}

\description{
 R interface function for LINDO API function \code{LSgetStocParOutcomes}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetStocParOutcomes(model,jScenario)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{Index of the scenario.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padVals}{A double array containing the values of stochastic parameters for the specified scenario.}
 \item{pdProb}{Probability of the scenario.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
