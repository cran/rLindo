\name{rLSdisposeRG}
\alias{rLSdisposeRG}

\title{Delete the specified random generator object.}

\description{
 R interface function for LINDO API function \code{LSdisposeRG}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSdisposeRG(rg)
}

\arguments{
 \item{rg}{A LINDO API random generator object, returned by \code{\link{rLScreateRG}}.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
