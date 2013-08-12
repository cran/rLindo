\name{rLSgetDistrRV}
\alias{rLSgetDistrRV}

\title{Get the next double random variate of underlying distribution.}

\description{
 R interface function for LINDO API function \code{LSgetDistrRV}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSgetDistrRV(rg)
}

\arguments{
 \item{rg}{A LINDO API random generator object, returned by \code{\link{rLScreateRG}}.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdResult}{The next random value from underlying distribution.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
