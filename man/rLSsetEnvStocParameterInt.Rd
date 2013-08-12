\name{rLSsetEnvStocParameterInt}
\alias{rLSsetEnvStocParameterInt}

\title{Set a stochastic parameter value of type integer.}

\description{
 R interface function for LINDO API function \code{LSsetEnvStocParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSsetEnvStocParameterInt(env,nQuery,pnResult)
}

\arguments{
 \item{env}{A LINDO API env object, returned by \code{\link{rLScreateEnv}}.}
 \item{nQuery}{A valid query macro.}
 \item{pnResult}{An integer number.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
