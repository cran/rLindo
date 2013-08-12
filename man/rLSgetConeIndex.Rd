\name{rLSgetConeIndex}
\alias{rLSgetConeIndex}

\title{Retrieve the name of a cone, given its index.}

\description{
 R interface function for LINDO API function \code{LSgetConeIndex}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetConeIndex(model,pszConeName)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszConeName}{Name of the cone whose index you wish to retrieve.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{piCone}{Index of the cone.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetConstraintIndex}}
}