\name{rLSsampGetCIPoints}
\alias{rLSsampGetCIPoints}

\title{Get a copy of the correlation induced sample points.}

\description{
 R interface function for LINDO API function \code{LSsampGetCIPoints}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsampGetCIPoints(sample)
}

\arguments{
 \item{sample}{A LINDO API sample object, returned by \code{\link{rLSsampCreate}}.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnSampSize}{The sample size.}
 \item{padXval}{A double array containing the sample.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
