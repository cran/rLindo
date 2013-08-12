\name{rLSaddDiscreteIndep}
\alias{rLSaddDiscreteIndep}

\title{Add a new discrete independent stochastic parameter to the SP model.}

\description{
 R interface function for LINDO API function \code{LSaddDiscreteIndep}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSaddDiscreteIndep(model,iRow,jCol,iStv,nRealizations,
                      padProbs,padVals,nModifyRule)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iRow}{Row index of the stochastic parameter.}
 \item{jCol}{Column index of the stochastic parameter.}
 \item{iStv}{Index of stochastic parameter in the instruction list.}
 \item{nRealizations}{Number of all possible realizations for the specified stochastic parameter.}
 \item{padProbs}{A double array containing probabilities associated with the realizations of the stochastic parameter.}
 \item{padVals}{A double array containing values associated with the probabilities.}
 \item{nModifyRule}{A flag indicating whether stochastic parameters update the core model by adding or replacing.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
