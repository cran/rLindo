\name{rLSfreeMIPSolutionMemory}
\alias{rLSfreeMIPSolutionMemory}

\title{Free up the arrays associated with the MIP solution of a given model.}

\description{
 R interface function for LINDO API function \code{LSfreeMIPSolutionMemory}. For more information,
 please refer to LINDO API User Manual.
}

\details{
  After freeing the memory, you will lose all access to the information associated to MIP solutions.
}

\usage{
  rLSfreeMIPSolutionMemory(model)
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
