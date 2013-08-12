\name{rLSgetScenarioReducedCost}
\alias{rLSgetScenarioReducedCost}

\title{Return the reduced cost for the specified scenario.}

\description{
 R interface function for LINDO API function \code{LSgetScenarioReducedCost}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetScenarioReducedCost(model,jScenario)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{An integer specifying the scenario index.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padX}{A double array containing the scenario's reduced cost.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
