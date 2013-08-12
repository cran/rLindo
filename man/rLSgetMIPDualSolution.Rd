\name{rLSgetMIPDualSolution}
\alias{rLSgetMIPDualSolution}

\title{Get the current dual solution for a MIP model.}

\description{
 R interface function for LINDO API function \code{LSgetMIPDualSolution}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetMIPDualSolution(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padDual}{A double array containing the dual solution to the integer model.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetMIPPrimalSolution}}
}


