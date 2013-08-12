\name{rLSsampSetRG}
\alias{rLSsampSetRG}

\title{Set a random number generator object to the specified distribution.}

\description{
 R interface function for LINDO API function \code{LSsampSetRG}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsampSetRG(sample,RG)
}

\arguments{
 \item{sample}{A LINDO API sample object, returned by \code{\link{rLSsampCreate}}.}
 \item{RG}{A LINDO API random generator object, returned by \code{\link{rLScreateRG}}.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
