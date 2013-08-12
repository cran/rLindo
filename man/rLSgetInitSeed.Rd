\name{rLSgetInitSeed}
\alias{rLSgetInitSeed}

\title{Get the seed initiated this random generator.}

\description{
 R interface function for LINDO API function \code{LSgetInitSeed}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSgetInitSeed(rg)
}

\arguments{
 \item{rg}{A LINDO API random generator object, returned by \code{\link{rLScreateRG}}.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnResult}{The seed initiated the random generator.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
