\name{rLSgetEnvDouParameter}
\alias{rLSgetEnvDouParameter}

\title{Retrieves a double precision parameter for a specified environment.}

\description{
 R interface function for LINDO API function \code{LSgetEnvDouParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSgetEnvDouParameter(env,nParameter)
}

\arguments{
 \item{env}{A LINDO API environment object, returned by \code{\link{rLScreateEnv}}.}
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

\seealso{
\code{\link{rLSgetModelDouParameter}}
}