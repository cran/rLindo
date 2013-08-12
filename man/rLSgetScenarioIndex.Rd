\name{rLSgetScenarioIndex}
\alias{rLSgetScenarioIndex}

\title{Get index of a scenario by its name.}

\description{
 R interface function for LINDO API function \code{LSgetScenarioIndex}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetScenarioIndex(model,pszName)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszName}{The name of the scenario to return the index for.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnIndex}{Index of the scenario.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
