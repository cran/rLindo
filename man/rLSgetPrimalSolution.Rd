\name{rLSgetPrimalSolution}
\alias{rLSgetPrimalSolution}

\title{Return the primal solution values for a given model.}

\description{
 R interface function for LINDO API function \code{LSgetPrimalSolution}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetPrimalSolution(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padPrimal}{A double array containing the primal solution.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetDualSolution}}
}