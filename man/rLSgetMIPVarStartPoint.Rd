\name{rLSgetMIPVarStartPoint}
\alias{rLSgetMIPVarStartPoint}

\title{Retrieve the values of the initial MIP primal solution.}

\description{
 R interface function for LINDO API function \code{LSgetMIPVarStartPoint}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetMIPVarStartPoint(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padPrimal}{A double array containing the starting values for each variable in the given MIP model.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadMIPVarStartPoint}}
}