\name{rLSgetEnvStocParameterInt}
\alias{rLSgetEnvStocParameterInt}

\title{Get a stochastic parameter value of type integer from the given env.}

\description{
 R interface function for LINDO API function \code{LSgetEnvStocParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetEnvStocParameterInt(env,nQuery)
}

\arguments{
 \item{env}{A LINDO API env object, returned by \code{\link{rLScreateEnv}}.}
 \item{nQuery}{A valid query macro.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnResult}{The result of type integer.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
