\name{rLSgetEnvIntParameter}
\alias{rLSgetEnvIntParameter}

\title{Retrieves a integer precision parameter for a specified environment.}

\description{
 R interface function for LINDO API function \code{LSgetEnvIntParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSgetEnvIntParameter(env,nParameter)
}

\arguments{
 \item{env}{A LINDO API environment object, returned by \code{\link{rLScreateEnv}}.}
 \item{nParameter}{An integer referring to an integer precision parameter.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnValue}{The parameter's value.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetModelIntParameter}}
}