\name{rLSgetReducedCostsCone}
\alias{rLSgetReducedCostsCone}

\title{Return the reduced cost of all cone variables for a given model.}

\description{
 R interface function for LINDO API function \code{LSgetReducedCostsCone}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetReducedCostsCone(model)
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

