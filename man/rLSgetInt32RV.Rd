\name{rLSgetInt32RV}
\alias{rLSgetInt32RV}

\title{Get the next integer random variate in the stream.}

\description{
 R interface function for LINDO API function \code{LSgetInt32RV}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSgetInt32RV(rg,iLow,iHigh)
}

\arguments{
 \item{rg}{A LINDO API random generator object, returned by \code{\link{rLScreateRG}}.}
 \item{iLow}{The lower bound.}
 \item{iHigh}{The upper bound.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnResult}{The result.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
