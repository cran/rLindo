\name{rLSgetNodeReducedCost}
\alias{rLSgetNodeReducedCost}

\title{Return the reduced cost for the specified node.}

\description{
 R interface function for LINDO API function \code{LSgetNodeReducedCost}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetNodeReducedCost(model,jScenario,iStage)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{An integer specifying the scenario index.}
 \item{iStage}{An integer specifying the stage index.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padX}{A double array containing the specified node's reduced cost.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
