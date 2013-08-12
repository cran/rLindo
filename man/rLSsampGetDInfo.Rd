\name{rLSsampGetDInfo}
\alias{rLSsampGetDInfo}

\title{Get double information about the sample.}

\description{
 R interface function for LINDO API function \code{LSsampGetInfo}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsampGetDInfo(sample,nQuery)
}

\arguments{
 \item{sample}{A LINDO API sample object, returned by \code{\link{rLSsampCreate}}.}
 \item{nQuery}{An integer specifying the information requested from the sample. Possible values are:
                  \itemize{
                       \item{LS_IINFO_DIST_TYPE}
                       \item{LS_IINFO_SAMP_SIZE}
                       \item{LS_DINFO_SAMP_MEAN}
                       \item{LS_DINFO_SAMP_STD}
                       \item{LS_DINFO_SAMP_SKEWNESS}
                       \item{LS_DINFO_SAMP_KURTOSIS}
                  }
              }
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdResult}{The result.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
