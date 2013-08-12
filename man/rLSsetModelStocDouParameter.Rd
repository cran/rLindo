\name{rLSsetModelStocDouParameter}
\alias{rLSsetModelStocDouParameter}

\title{Set a double valued parameter for the given model.}

\description{
 R interface function for LINDO API function \code{LSsetModelStocDouParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSsetModelStocDouParameter(model,iPar,dVal)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iPar}{A valid parameter macro.}
 \item{dVal}{A double variable of the appropriate type.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
