\name{rLSsampGetDistrParam}
\alias{rLSsampGetDistrParam}

\title{Get the specified parameter of a given distribution.}

\description{
 R interface function for LINDO API function \code{LSsampGetDistrParam}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsampGetDistrParam(sample,nIndex)
}

\arguments{
 \item{sample}{A LINDO API sample object, returned by \code{\link{rLSsampCreate}}.}
 \item{nIndex}{An integer specifying the index of the parameter.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdValue}{A double precision value specifying the parameter value.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
