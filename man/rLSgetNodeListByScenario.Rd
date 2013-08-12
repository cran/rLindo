\name{rLSgetNodeListByScenario}
\alias{rLSgetNodeListByScenario}

\title{Retrieve the indices of the nodes that belong to a given scenario.}

\description{
 R interface function for LINDO API function \code{LSgetNodeListByScenario}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetNodeListByScenario(model,jScenario)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{An integer specifying the scenario index.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{paiNodes}{An integer array containing he node list constituting the scenario.}
 \item{pnNodes}{Actual number of nodes on the scenario.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
