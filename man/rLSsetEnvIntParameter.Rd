\name{rLSsetEnvIntParameter}
\alias{rLSsetEnvIntParameter}

\title{Set an integer parameter for a specified environment.}

\description{
 R interface function for LINDO API function \code{LSsetEnvIntParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSsetEnvIntParameter(env,nParameter,nValue)
}

\arguments{
 \item{env}{A LINDO API environment object, returned by \code{\link{rLScreateEnv}}.}
 \item{nParameter}{An integer referring to an integer precision parameter.}
 \item{nValue}{An integer precision value.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSsetModelIntParameter}}
}