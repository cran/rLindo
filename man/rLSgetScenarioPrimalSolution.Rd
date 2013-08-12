\name{rLSgetScenarioPrimalSolution}
\alias{rLSgetScenarioPrimalSolution}

\title{Return the primal solution for the specified scenario.}

\description{
 R interface function for LINDO API function \code{LSgetScenarioPrimalSolution}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetScenarioPrimalSolution(model,jScenario)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{An integer specifying the scenario index.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padX}{A double array containing the scenario's primal solution.}
 \item{pdObj}{Objective value for the specified scenario.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
