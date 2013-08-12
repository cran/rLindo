\name{rLSfreeStocMemory}
\alias{rLSfreeStocMemory}

\title{Free up stochastic memory.}

\description{
 R interface function for LINDO API function \code{LSfreeStocMemory}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSfreeStocMemory(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
