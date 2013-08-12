\name{rLSreadEnvParameter}
\alias{rLSreadEnvParameter}

\title{Reads environment parameters from a parameter file.}

\description{
 R interface function for LINDO API function \code{LSreadEnvParameter}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSreadEnvParameter(env,pszFname)
}

\arguments{
 \item{env}{A LINDO API environment object, returned by \code{\link{rLScreateEnv}}.}
 \item{pszFname}{The path and name of the file from which parameters will be read.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
