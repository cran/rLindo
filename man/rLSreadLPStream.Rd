\name{rLSreadLPStream}
\alias{rLSreadLPStream}

\title{Read from character stream in "CPLEX LP Format".}

\description{
 R interface function for LINDO API function \code{LSreadLPStream}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSreadLPStream(model,pszStream,nStreamLen)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszStream}{A stream of chars constituting the full model.}
 \item{nStreamLen}{Length of the stream.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
