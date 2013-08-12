\name{rLSsetModelStocParameterInt}
\alias{rLSsetModelStocParameterInt}

\title{Set a stochastic parameter value of type integer.}

\description{
 R interface function for LINDO API function \code{LSsetModelStocParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSsetModelStocParameterInt(model,nQuery,pnResult)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nQuery}{A valid query macro.}
 \item{pnResult}{An integer number.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
