\name{rLSsetEnvStocParameterDou}
\alias{rLSsetEnvStocParameterDou}

\title{Set a stochastic parameter value of type double.}

\description{
 R interface function for LINDO API function \code{LSsetEnvStocParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSsetEnvStocParameterDou(env,nQuery,pdResult)
}

\arguments{
 \item{env}{A LINDO API env object, returned by \code{\link{rLScreateEnv}}.}
 \item{nQuery}{A valid query macro.}
 \item{pdResult}{A double number.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
