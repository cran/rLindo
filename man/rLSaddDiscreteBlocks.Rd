\name{rLSaddDiscreteBlocks}
\alias{rLSaddDiscreteBlocks}

\title{Add a new discrete stochastic block to the SP model.}

\description{
 R interface function for LINDO API function \code{LSaddDiscreteBlocks}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSaddDiscreteBlocks(model,iStage,nRealzBlock,padProb,
                       pakStart,paiRows,paiCols,paiStvs,padVals,nModifyRule)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iStage}{The stage of the stochastic block.}
 \item{nRealzBlock}{Number of discrete events in the block.}
 \item{padProb}{An double array containing the event probabilities.}
 \item{pakStart}{An integer array containing the starting positions of events in the sparse matrix or instruction list.}
 \item{paiRows}{An integer array containing row indices of stochastic parameters.}
 \item{paiCols}{An integer array containing column indices of stochastic parameters.}
 \item{paiStvs}{An integer array containing stochastic parameters in the instruction list.}
 \item{padVals}{A double array containing stochastic values associated with the stochastic parameters listed in paiStvs or (paiArows,paiAcols).}
 \item{nModifyRule}{A flag indicating whether stochastic parameters update the core model by adding or replacing.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
