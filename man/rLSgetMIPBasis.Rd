\name{rLSgetMIPBasis}
\alias{rLSgetMIPBasis}

\title{Get information about the basis that was found at the node that yielded the optimal MIP solution.}

\description{
 R interface function for LINDO API function \code{LSgetMIPBasis}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetMIPBasis(model)
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
\code{\link{rLSgetBasis}}
}

