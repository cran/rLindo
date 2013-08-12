\name{rLSsetDistrRG}
\alias{rLSsetDistrRG}

\title{Set a distribution function for the random generator.}

\description{
 R interface function for LINDO API function \code{LSsetDistrRG}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsetDistrRG(rg,nDistType)
}

\arguments{
 \item{rg}{A LINDO API random generator object, returned by \code{\link{rLScreateRG}}.}
 \item{nDistType}{An integer specifying the distribution type.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSsampCreate}}
}
