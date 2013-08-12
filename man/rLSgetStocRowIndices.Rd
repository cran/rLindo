\name{rLSgetStocRowIndices}
\alias{rLSgetStocRowIndices}

\title{Retrieve the indices of stochastic rows.}

\description{
 R interface function for LINDO API function \code{LSgetStocRowIndices}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetStocRowIndices(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{paiSrows}{An integer array containing the indices of stochastic rows in the core model.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
