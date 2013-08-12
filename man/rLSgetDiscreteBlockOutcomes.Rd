\name{rLSgetDiscreteBlockOutcomes}
\alias{rLSgetDiscreteBlockOutcomes}

\title{Get the outcomes for the specified block-event at specified block-realization index.}

\description{
 R interface function for LINDO API function \code{LSgetDiscreteBlockOutcomes}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetDiscreteBlockOutcomes(model,iEvent,iRealz)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iEvent}{Index of the discrete block event.}
 \item{iRealz}{Index of a block realization in the specified block event.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{nRealz}{Number of individual stochastic parameters consitituting the block realization iRealz.}
 \item{paiArows}{An integer array containing the row indices of stochastic parameters.}
 \item{paiAcols}{An integer array containing the column indices of stochastic parameters.}
 \item{paiStvs}{An integer array containing indices of stochastic parameters.}
 \item{padVals}{A double array containing the values associated with the stochastic parameters listed in paiStvs or (paiArows,paiAcols).}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
