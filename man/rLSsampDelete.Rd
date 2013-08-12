\name{rLSsampDelete}
\alias{rLSsampDelete}

\title{Delete the specified sample object.}

\description{
 R interface function for LINDO API function \code{LSsampDelete}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsampDelete(sample)
}

\arguments{
 \item{sample}{A LINDO API sample object, returned by \code{\link{rLSsampCreate}}.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
