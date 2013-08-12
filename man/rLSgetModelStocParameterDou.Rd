\name{rLSgetModelStocParameterDou}
\alias{rLSgetModelStocParameterDou}

\title{Get a stochastic parameter value of type double from the given model.}

\description{
 R interface function for LINDO API function \code{LSgetModelStocParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetModelStocParameterDou(model,nQuery)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nQuery}{A valid query macro.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdResult}{The result of type double.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
