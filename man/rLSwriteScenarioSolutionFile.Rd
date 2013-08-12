\name{rLSwriteScenarioSolutionFile}
\alias{rLSwriteScenarioSolutionFile}

\title{Write the scenario solution to a file.}

\description{
 R interface function for LINDO API function \code{LSwriteScenarioSolutionFile}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSwriteScenarioSolutionFile(model,jScenario,pszFname)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{The scenario to write the solution for.}
 \item{pszFname}{Path and name of the file.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
