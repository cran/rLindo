\name{rLSloadGASolution}
\alias{rLSloadGASolution}

\title{Loads the GA solution at specified index in the final population to the main solution 
       structures for access with solution query routines.}

\description{
 R interface function for LINDO API function \code{LSloadGASolution}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadGASolution(model,nIndex)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nIndex}{Index of the individual in the final population.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
