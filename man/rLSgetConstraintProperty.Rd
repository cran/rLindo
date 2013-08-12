\name{rLSgetConstraintProperty}
\alias{rLSgetConstraintProperty}

\title{Return the property of the specified constraint of the given model.}

\description{
 R interface function for LINDO API function \code{LSgetConstraintProperty}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSgetConstraintProperty(model,ndxCons)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{ndxCons}{The index of the constraint for which the property is requested.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnConptype}{The constraint property.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSsetConstraintProperty}}
}