\name{rLSgetParamMacroID}
\alias{rLSgetParamMacroID}

\title{Get the integer identifier and the data type of a parameter specified by its name.}

\description{
 R interface function for LINDO API function \code{LSgetParamMacroID}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSgetParamMacroID(env,szParam)
}

\arguments{
 \item{env}{A LINDO API environment object, returned by \code{\link{rLScreateEnv}}.}
 \item{szParam}{A parameter macro name.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnParamType}{The data type of the parameter.}
 \item{pnParam}{The integer identifier of the parameter.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
