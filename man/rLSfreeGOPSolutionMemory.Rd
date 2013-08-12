\name{rLSfreeGOPSolutionMemory}
\alias{rLSfreeGOPSolutionMemory}

\title{Free up the arrays associated with the GOP solution of a given model.}

\description{
 R interface function for LINDO API function \code{LSfreeGOPSolutionMemory}. For more information,
 please refer to LINDO API User Manual.
}

\details{
  After freeing the memory, you will lose all access to the information associated to GOP solutions.
}

\usage{
  rLSfreeGOPSolutionMemory(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
