\name{rLSsetModelStocIntParameter}
\alias{rLSsetModelStocIntParameter}

\title{Set an integer valued parameter for the given model.}

\description{
 R interface function for LINDO API function \code{LSsetModelStocIntParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSsetModelStocIntParameter(model,iPar,iVal)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iPar}{A valid parameter macro.}
 \item{iVal}{An integer variable of the appropriate type.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
