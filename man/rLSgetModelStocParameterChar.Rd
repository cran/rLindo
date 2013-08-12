\name{rLSgetModelStocParameterChar}
\alias{rLSgetModelStocParameterChar}

\title{Get a stochastic parameter value of type characters from the given model.}

\description{
 R interface function for LINDO API function \code{LSgetModelStocParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetModelStocParameterChar(model,nQuery)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nQuery}{A valid query macro.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pachResult}{The result of type characters.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
