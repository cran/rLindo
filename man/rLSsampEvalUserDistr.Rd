\name{rLSsampEvalUserDistr}
\alias{rLSsampEvalUserDistr}

\title{Evaluate the specified multivariate function associated with given distribution at specified point.}

\description{
 R interface function for LINDO API function \code{LSsampEvalUserDistr}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsampEvalUserDistr(sample,nFuncType,padXval,nDim)
}

\arguments{
 \item{sample}{A LINDO API sample object, returned by \code{\link{rLSsampCreate}}.}
 \item{nFuncType}{An integer specifying the function type to evaluate. Possible values are:
                   \itemize{
                       \item{LS_PDF} probability density function.
                       \item{LS_CDF} cummulative density function.
                       \item{LS_CDFINV} inverse of cummulative density function.
                       \item{LS_PDFDIFF} derivative of the probability density function.
                       \item{LS_USER} a user-defined function.
                   }
                  }
 \item{padXval}{A double array containing the values required to evaluate the specified function.}
 \item{nDim}{An integer specifying the number of values required in the computation of the sample point.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdResult}{A double value to return the result.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
