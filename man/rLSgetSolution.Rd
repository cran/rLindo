\name{rLSgetSolution}
\alias{rLSgetSolution}

\title{Get the solution specified by the second argument.}

\description{
 R interface function for LINDO API function \code{LSgetSolution}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetSolution(model,nWhich)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nWhich}{An integer parameter specifying the solution to be retrieved. Possible values are:
                 \itemize{
                     \item{LSSOL_BASIC_PRIMAL}
                     \item{LSSOL_BASIC_DUAL}
                     \item{LSSOL_BASIC_SLACK}
                     \item{LSSOL_BASIC_REDCOST}
                     \item{LSSOL_INTERIOR_PRIMAL}
                     \item{LSSOL_INTERIOR_DUAL}
                     \item{LSSOL_INTERIOR_SLACK}
                     \item{LSSOL_INTERIOR_REDCOST}
                 }
              }
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padResult}{A double array containing the specified solution.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}


