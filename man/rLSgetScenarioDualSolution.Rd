\name{rLSgetScenarioDualSolution}
\alias{rLSgetScenarioDualSolution}

\title{Return the dual solution for the specified scenario.}

\description{
 R interface function for LINDO API function \code{LSgetScenarioDualSolution}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetScenarioDualSolution(model,jScenario)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{An integer specifying the scenario index.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padY}{A double array containing the scenario's dual solution.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
