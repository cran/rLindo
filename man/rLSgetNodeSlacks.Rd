\name{rLSgetNodeSlacks}
\alias{rLSgetNodeSlacks}

\title{Return the slack values for the specified node.}

\description{
 R interface function for LINDO API function \code{LSgetNodeSlacks}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetNodeSlacks(model,jScenario,iStage)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{An integer specifying the scenario index.}
 \item{iStage}{An integer specifying the stage index.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padY}{A double array containing the specified node's slack values.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
