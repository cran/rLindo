\name{rLSwriteScenarioMPIFile}
\alias{rLSwriteScenarioMPIFile}

\title{Write scenario model in MPI format.}

\description{
 R interface function for LINDO API function \code{LSwriteScenarioMPIFile}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSwriteScenarioMPIFile(model,jScenario,pszFname)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{The scenario to write in MPI format.}
 \item{pszFname}{Path and name of the MPI file.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
