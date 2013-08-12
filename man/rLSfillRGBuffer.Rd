\name{rLSfillRGBuffer}
\alias{rLSfillRGBuffer}

\title{Generate next batch of random numbers into random number buffer.}

\description{
 R interface function for LINDO API function \code{LSfillRGBuffer}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSfillRGBuffer(rg)
}

\arguments{
 \item{rg}{A LINDO API random generator object, returned by \code{\link{rLScreateRG}}.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

