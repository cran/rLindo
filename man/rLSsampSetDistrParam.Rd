\name{rLSsampSetDistrParam}
\alias{rLSsampSetDistrParam}

\title{Set the specified parameter of the given distribution.}

\description{
 R interface function for LINDO API function \code{LSsampSetDistrParam}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsampSetDistrParam(sample,nIndex,dValue)
}

\arguments{
 \item{sample}{A LINDO API sample object, returned by \code{\link{rLSsampCreate}}.}
 \item{nIndex}{An integer specifying the index of the parameter.}
 \item{dValue}{A double precision value specifying the parameter value.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
