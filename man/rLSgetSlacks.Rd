\name{rLSgetSlacks}
\alias{rLSgetSlacks}

\title{Return the value of the slack variable for each constraint of a given model.}

\description{
 R interface function for LINDO API function \code{LSgetSlacks}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetSlacks(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padSlack}{A double array containing the values of the slack variables.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetDualSolution}}
}

