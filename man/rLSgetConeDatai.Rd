\name{rLSgetConeDatai}
\alias{rLSgetConeDatai}

\title{Retrieve data for cone i.}

\description{
 R interface function for LINDO API function \code{LSgetConeDatai}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetConeDatai(model,iCone)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iCone}{Index of the cone you wish to receive information on.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pchConeType}{Type of the cone.}
 \item{piNnz}{Number of variables characterizing the cone.}
 \item{paiCols}{An integer array containing indices of variables characterizing the cone.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetConstraintDatai}}
}