\name{rLSgetConstraintNamei}
\alias{rLSgetConstraintNamei}

\title{Retrieve the name of a constraint, given its index number.}

\description{
 R interface function for LINDO API function \code{LSgetConstraintNamei}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetConstraintNamei(model,iCon)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iCon}{Index of the constraint whose name you wish to retrieve.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pachConName}{Name of the constraint.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetVariableNamej}}
}