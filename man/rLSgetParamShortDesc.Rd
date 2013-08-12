\name{rLSgetParamShortDesc}
\alias{rLSgetParamShortDesc}

\title{Get the specified parameter's short description.}

\description{
 R interface function for LINDO API function \code{LSgetParamShortDesc}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSgetParamShortDesc(env,nParam)
}

\arguments{
 \item{env}{A LINDO API environment object, returned by \code{\link{rLScreateEnv}}.}
 \item{nParam}{An integer parameter identifier.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{szDescription}{The parameter's short description.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
