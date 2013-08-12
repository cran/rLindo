\name{rLSaddScenario}
\alias{rLSaddScenario}

\title{Add a new scenario block to the SP model.}

\description{
 R interface function for LINDO API function \code{LSaddScenario}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSaddScenario(model,jScenario,iParentScen,iStage,dProb,nElems,
                 paiRows,paiCols,paiStvs,padVals,nModifyRule)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{Index of the new scenario to be added.}
 \item{iParentScen}{Index of the parent scenario.}
 \item{iStage}{Index of the stage the new scenario branches from its parent.}
 \item{dProb}{The scenario probability.}
 \item{nElems}{Number of stochastic parameters realized at stage iStage in the new scenario.}
 \item{paiRows}{An integer array containing the row indices of stochastic parameters.}
 \item{paiCols}{An integer array containing the column indices of stochastic parameters.}
 \item{paiStvs}{A double array containing indices of stochastic parameters in instruction list.}
 \item{padVals}{A double array containing values of stochastic parameters.}
 \item{nModifyRule}{A flag indicating whether stochastic parameters update the core model by adding or replacing.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
