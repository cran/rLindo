\name{rLSgetModelStocParameterInt}
\alias{rLSgetModelStocParameterInt}

\title{Get a stochastic parameter value of type integer from the given model.}

\description{
 R interface function for LINDO API function \code{LSgetModelStocParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetModelStocParameterInt(model,nQuery)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nQuery}{A valid query macro.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnResult}{The result of type integer.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
