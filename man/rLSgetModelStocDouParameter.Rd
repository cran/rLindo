\name{rLSgetModelStocDouParameter}
\alias{rLSgetModelStocDouParameter}

\title{Get the current value of a double valued parameter for the given model.}

\description{
 R interface function for LINDO API function \code{LSgetModelStocDouParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetModelStocDouParameter(model,iPar)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iPar}{A valid parameter macro.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdValue}{The current value of the parameter.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
