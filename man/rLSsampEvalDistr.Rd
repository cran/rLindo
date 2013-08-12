\name{rLSsampEvalDistr}
\alias{rLSsampEvalDistr}

\title{Evaluate the specified function associated with given distribution at specified point.}

\description{
 R interface function for LINDO API function \code{LSsampEvalDistr}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsampEvalDistr(sample,nFuncType,dXval)
}

\arguments{
 \item{sample}{A LINDO API sample object, returned by \code{\link{rLSsampCreate}}.}
 \item{nFuncType}{An integer specifying the function type to evaluate. Possible values are:
                   \itemize{
                       \item{LS_PDF} probability density function.
                       \item{LS_CDF} cummulative density function.
                       \item{LS_CDFINV} inverse of cummulative density function.
                       \item{LS_PDFDIFF} derivative of the probability density function.
                   }
                 }
 \item{dXval}{A double precision value to evaluate the specified function.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdResult}{A double value to return the result.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
