\name{rLSgetErrorMessage}
\alias{rLSgetErrorMessage}

\title{Retrieves the error message associated with the given error code.}

\description{
 R interface function for LINDO API function \code{LSgetErrorMessage}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSgetErrorMessage(env,errorcode)
}

\arguments{
 \item{env}{A LINDO API environment object, returned by \code{\link{rLScreateEnv}}.}
 \item{errorcode}{An integer referring to the error code. }
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pachMessage}{The error message associated with the given error code.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
