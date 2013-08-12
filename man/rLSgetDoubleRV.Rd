\name{rLSgetDoubleRV}
\alias{rLSgetDoubleRV}

\title{Get the next standard uniform random variate in the stream.}

\description{
 R interface function for LINDO API function \code{LSgetDoubleRV}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSgetDoubleRV(rg)
}

\arguments{
 \item{rg}{A LINDO API random generator object, returned by \code{\link{rLScreateRG}}.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdResult}{The result.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
