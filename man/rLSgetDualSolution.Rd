\name{rLSgetDualSolution}
\alias{rLSgetDualSolution}

\title{Return the dual solution values for a given model.}

\description{
 R interface function for LINDO API function \code{LSgetDualSolution}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetDualSolution(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padDual}{A double array containing the dual solution.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetPrimalSolution}}
}

