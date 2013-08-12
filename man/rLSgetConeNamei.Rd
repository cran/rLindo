\name{rLSgetConeNamei}
\alias{rLSgetConeNamei}

\title{Get the name of a cone with a specified index.}

\description{
 R interface function for LINDO API function \code{LSgetConeNamei}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetConeNamei(model,iCone)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iCone}{Index of the cone whose name you wish to retrieve.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pachConeName}{Name of the cone.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetConstraintNamei}}
}