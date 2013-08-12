\name{rLSgetDiscreteBlocks}
\alias{rLSgetDiscreteBlocks}

\title{Get the stochastic data for the discrete block event at specified index.}

\description{
 R interface function for LINDO API function \code{LSgetDiscreteBlocks}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetDiscreteBlocks(model,iEvent)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iEvent}{Index of the discrete block event.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{nDistType}{Distribution type of the event.}
 \item{iStage}{Stage index of the block event.}
 \item{nRealzBlock}{Number of block realizations in the event.}
 \item{padProbs}{A double array containing the event probabilities.}
 \item{iModifyRule}{A flag indicating whether stochastic parameters update the core model by adding or replacing.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
