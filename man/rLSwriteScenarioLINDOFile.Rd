\name{rLSwriteScenarioLINDOFile}
\alias{rLSwriteScenarioLINDOFile}

\title{Write scenario model in LINDO format.}

\description{
 R interface function for LINDO API function \code{LSwriteScenarioLINDOFile}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSwriteScenarioLINDOFile(model,jScenario,pszFname)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{The scenario to write in LINDO format.}
 \item{pszFname}{Path and name of the LINDO file.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
