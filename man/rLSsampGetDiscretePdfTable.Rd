\name{rLSsampGetDiscretePdfTable}
\alias{rLSsampGetDiscretePdfTable}

\title{Get the PDF table from a discrete distribution sample.}

\description{
 R interface function for LINDO API function \code{LSsampGetDiscretePdfTable}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsampGetDiscretePdfTable(sample)
}

\arguments{
 \item{sample}{A LINDO API sample object, returned by \code{\link{rLSsampCreate}}.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnLen}{The table length.}
 \item{padProb}{A double array containing the probabilities of outcomes.}
 \item{padVals}{A double array containing the values of outcomes.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
