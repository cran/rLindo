\name{rLSsampGetPoints}
\alias{rLSsampGetPoints}

\title{Get a copy of the generated sample points.}

\description{
 R interface function for LINDO API function \code{LSsampGetPoints}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsampGetPoints(sample)
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
