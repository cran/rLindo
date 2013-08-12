\name{rLSgetProbabilityByScenario}
\alias{rLSgetProbabilityByScenario}

\title{Return the probability of a given scenario.}

\description{
 R interface function for LINDO API function \code{LSgetProbabilityByScenario}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetProbabilityByScenario(model,jScenario)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{An integer specifying the scenario index.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdProb}{The probabability of the scenario.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
