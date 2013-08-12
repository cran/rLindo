\name{rLSgetReducedCosts}
\alias{rLSgetReducedCosts}

\title{Return the reduced cost of all variables for a given model.}

\description{
 R interface function for LINDO API function \code{LSgetReducedCosts}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetReducedCosts(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padReducedCost}{A double array containing the reduced cost.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetPrimalSolution}}
}

