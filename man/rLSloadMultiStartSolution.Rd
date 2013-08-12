\name{rLSloadMultiStartSolution}
\alias{rLSloadMultiStartSolution}

\title{Load the multistart solution at specified index to the main solution structures for access with solution query routines.}

\description{
 R interface function for LINDO API function \code{LSloadMultiStartSolution}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadMultiStartSolution(model,nIndex)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nIndex}{Index of the multistart solution.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
