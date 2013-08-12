\name{rLSgetMIPReducedCosts}
\alias{rLSgetMIPReducedCosts}

\title{Get the current reduced cost for a MIP model.}

\description{
 R interface function for LINDO API function \code{LSgetMIPReducedCosts}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetMIPReducedCosts(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padReducedCost}{A double array containing the reduced cost to the integer model.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetMIPPrimalSolution}}
}


