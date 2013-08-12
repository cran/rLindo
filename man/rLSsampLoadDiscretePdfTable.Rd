\name{rLSsampLoadDiscretePdfTable}
\alias{rLSsampLoadDiscretePdfTable}

\title{Load a PDF table for a user defined discrete distribution.}

\description{
 R interface function for LINDO API function \code{LSsampLoadDiscretePdfTable}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsampLoadDiscretePdfTable(sample,nLen,padProb,padVals)
}

\arguments{
 \item{sample}{A LINDO API sample object, returned by \code{\link{rLSsampCreate}}.}
 \item{nLen}{An integer specifying the table length.}
 \item{padProb}{A double array containing the probabilities of outcomes.}
 \item{padVals}{A double array containing the values of outcomes.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
