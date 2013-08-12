\name{rLSsetConstraintProperty}
\alias{rLSsetConstraintProperty}

\title{Set the property of the specified constraint of the given model.}

\description{
 R interface function for LINDO API function \code{LSsetConstraintProperty}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSsetConstraintProperty(model,ndxCons,nConptype)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{ndxCons}{The index of the constraint for which the property is requested.}
 \item{nConptype}{An integer macro to specify the constraint property. Possible values are:
                     \itemize{
                       \item{\code{LS_PROPERTY_UNKNOWN}}
                       \item{\code{LS_PROPERTY_LINEAR}}
                       \item{\code{LS_PROPERTY_CONVEX}}
                       \item{\code{LS_PROPERTY_CONCAVE}}
                       \item{\code{LS_PROPERTY_QUASI_CONVEX}}
                       \item{\code{LS_PROPERTY_QUASI_CONCAVE}}
                       \item{\code{LS_PROPERTY_MAX}}
                     }
                  }
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
