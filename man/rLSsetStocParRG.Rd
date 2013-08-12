\name{rLSsetStocParRG}
\alias{rLSsetStocParRG}

\title{Set an RG object to the specified stochastic parameter.}

\description{
 R interface function for LINDO API function \code{LSsetStocParRG}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSsetStocParRG(model,iStv,iRow,jCol,pRG)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iStv}{Index of stochastic parameter in the instruction list.}
 \item{iRow}{Row index of the stochastic parameter.}
 \item{jCol}{Column index of the stochastic parameter.}
 \item{pRG}{A LINDO API RG object, returned by \code{\link{rLScreateRG}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
