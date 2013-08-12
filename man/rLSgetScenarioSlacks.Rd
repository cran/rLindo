\name{rLSgetScenarioSlacks}
\alias{rLSgetScenarioSlacks}

\title{Return the primal slacks for the specified scenario.}

\description{
 R interface function for LINDO API function \code{LSgetScenarioSlacks}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetScenarioSlacks(model,jScenario)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{An integer specifying the scenario index.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padY}{A double array containing the scenario's primal slacks.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
