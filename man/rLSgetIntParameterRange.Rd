\name{rLSgetIntParameterRange}
\alias{rLSgetIntParameterRange}

\title{Retrieve the range of a parameter of type integer.}

\description{
 R interface function for LINDO API function \code{LSgetIntParameterRange}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSgetIntParameterRange(model,nParameter)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nParameter}{An integer parameter identifier.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnValMIN}{The minimum value of parameter.}
 \item{pnValMAX}{The maximum value of parameter.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
