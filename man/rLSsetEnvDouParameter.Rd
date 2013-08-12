\name{rLSsetEnvDouParameter}
\alias{rLSsetEnvDouParameter}

\title{Set a double precision parameter for a specified environment.}

\description{
 R interface function for LINDO API function \code{LSsetEnvDouParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSsetEnvDouParameter(env,nParameter,dValue)
}

\arguments{
 \item{env}{A LINDO API environment object, returned by \code{\link{rLScreateEnv}}.}
 \item{nParameter}{An integer referring to a double precision parameter.}
 \item{dValue}{A double precision value.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSsetModelDouParameter}}
}