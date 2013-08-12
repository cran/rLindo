\name{rLSsampGenerate}
\alias{rLSsampGenerate}

\title{Generate a sample of a given size with specified method from the underlying distribution.}

\description{
 R interface function for LINDO API function \code{LSsampGenerate}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsampGenerate(sample,nMethod,nSize)
}

\arguments{
 \item{sample}{A LINDO API sample object, returned by \code{\link{rLSsampCreate}}.}
 \item{nMethod}{An integer specifying the sampling method. Possible values are:
                 \itemize{
                   \item{LS_MONTECARLO}
                   \item{LS_LATINSQUARE}
                   \item{LS_ANTITHETIC}
                 }
               }
 \item{nSize}{An integer specifying the sample size.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
