\name{rLSgetParamMacroName}
\alias{rLSgetParamMacroName}

\title{Get the specified parameter's macro name.}

\description{
 R interface function for LINDO API function \code{LSgetParamMacroName}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSgetParamMacroName(env,nParam)
}

\arguments{
 \item{env}{A LINDO API environment object, returned by \code{\link{rLScreateEnv}}.}
 \item{nParam}{An integer parameter identifier.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{szParam}{The macro's name.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

