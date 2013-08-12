\name{rLSgetStocCCPIInfo}
\alias{rLSgetStocCCPIInfo}

\title{Get integer information about the current state of the stochastic model.}

\description{
 R interface function for LINDO API function \code{LSgetStocCCPInfo}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetStocCCPIInfo(model,nQuery,nScenarioIndex,nCPPIndex)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nQuery}{A valid information macro.}
 \item{nScenarioIndex}{The scenario index.}
 \item{nCPPIndex}{The chance constraint index.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnResult}{An integer value of the information.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
