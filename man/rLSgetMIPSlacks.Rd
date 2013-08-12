\name{rLSgetMIPSlacks}
\alias{rLSgetMIPSlacks}

\title{Get the current slack values for a MIP model.}

\description{
 R interface function for LINDO API function \code{LSgetMIPSlacks}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetMIPSlacks(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padSlack}{A double array containing the slack values to the integer model.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetMIPDualSolution}}
}


