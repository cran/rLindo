\name{rLSgetScenario}
\alias{rLSgetScenario}

\title{Get the outcomes for the specified specified scenario.}

\description{
 R interface function for LINDO API function \code{LSgetScenario}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetScenario(model,jScenario)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{Index of a scenario realization.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{iParentScen}{Index of parent scenario.}
 \item{iBranchStage}{The branching stage.}
 \item{pdProb}{Event probability of scenario.}
 \item{nRealz}{Number of individual stochastic parameters consitituting the scenario.}
 \item{paiArows}{An integer array containing the row indices of stochastic parameters in the scenario.}
 \item{paiAcols}{An integer array containing the column indices of stochastic parameters in the scenario.}
 \item{paiStvs}{An integer array containing indices of stochastic parameters in the scenario.}
 \item{padVals}{A double array containing values associated with the stochastic parameters listed in paiStvs or (paiArows,paiAcols).}
 \item{iModifyRule}{A flag indicating whether stochastic parameters update the core model by adding or replacing.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
