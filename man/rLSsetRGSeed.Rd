\name{rLSsetRGSeed}
\alias{rLSsetRGSeed}

\title{Set an initialization seed for the random number generator.}

\description{
 R interface function for LINDO API function \code{LSsetRGSeed}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsetRGSeed(rg,nSeed)
}

\arguments{
 \item{rg}{A LINDO API random generator object, returned by \code{\link{rLScreateRG}}.}
 \item{nSeed}{An integer specifying the seed to set.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
