\name{rLSgetConstraintIndex}
\alias{rLSgetConstraintIndex}

\title{Retrieve the index of a constraint, given its name.}

\description{
 R interface function for LINDO API function \code{LSgetConstraintIndex}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetConstraintIndex(model,pszConName)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszConName}{Name of the constraint whose index you wish to retrieve.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{piCon}{Index of the constraint.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetVariableIndex}}
}