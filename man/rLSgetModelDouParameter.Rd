\name{rLSgetModelDouParameter}
\alias{rLSgetModelDouParameter}

\title{Retrieves a double precision parameter for a specified model.}

\description{
 R interface function for LINDO API function \code{LSgetModelDouParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSgetModelDouParameter(model,nParameter)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nParameter}{An integer referring to a double precision parameter.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdValue}{The parameter's value.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
