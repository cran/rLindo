\name{rLSgetBasis}
\alias{rLSgetBasis}

\title{Get information about the basis that was found after optimizing the given model.}

\description{
 R interface function for LINDO API function \code{LSgetBasis}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetBasis(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{panCstatus}{An integer array containing information about the status of the variables.}
 \item{panCstatus}{An integer array containing information about the status of the constraints.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadBasis}}
}

