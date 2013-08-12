\name{rLSgetMIPPrimalSolution}
\alias{rLSgetMIPPrimalSolution}

\title{Get the current primal solution for a MIP model.}

\description{
 R interface function for LINDO API function \code{LSgetMIPPrimalSolution}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetMIPPrimalSolution(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padPrimal}{A double array containing the primal solution to the integer model.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}


