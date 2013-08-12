\name{rLSgetScenarioObjective}
\alias{rLSgetScenarioObjective}

\title{Return the objective value for the specified scenario.}

\description{
 R interface function for LINDO API function \code{LSgetScenarioObjective}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetScenarioObjective(model,jScenario)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{An integer specifying the scenario index.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdObj}{The obejctive value for the scenario.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
