\name{rLSsetEnvStocParameterChar}
\alias{rLSsetEnvStocParameterChar}

\title{Set a stochastic parameter value of type string.}

\description{
 R interface function for LINDO API function \code{LSsetEnvStocParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSsetEnvStocParameterChar(env,nQuery,pacResult)
}

\arguments{
 \item{env}{A LINDO API env object, returned by \code{\link{rLScreateEnv}}.}
 \item{nQuery}{A valid query macro.}
 \item{pacResult}{A character string.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
