\name{rLSsampLoadPoints}
\alias{rLSsampLoadPoints}

\title{Load a sample of given size to the specified sample.}

\description{
 R interface function for LINDO API function \code{LSsampLoadPoints}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsampLoadPoints(sample,nSampSize,padXval)
}

\arguments{
 \item{sample}{A LINDO API sample object, returned by \code{\link{rLSsampCreate}}.}
 \item{nSampSize}{The sample size.}
 \item{padXval}{A double array containing the sample.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
