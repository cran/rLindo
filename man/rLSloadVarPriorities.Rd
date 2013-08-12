\name{rLSloadVarPriorities}
\alias{rLSloadVarPriorities}

\title{Provide priorities for each variable for use by mixed-integer and global solvers.}

\description{
 R interface function for LINDO API function \code{LSloadVarPriorities}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadVarPriorities(model,panCprior)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{panCprior}{An integer array containing the priority of each column in the given model. 
                  A valid priority value is any nonnegative integer value. 
                  Variables with higher priority values are given higher branching priority.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
