\name{rLSreadBasis}
\alias{rLSreadBasis}

\title{Read an initial basis from the given file in the specified format.}

\description{
 R interface function for LINDO API function \code{LSreadBasis}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSreadBasis(model,pszFname,nFormat)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The path and name of the basis file.}
 \item{nFormat}{An integer parameter indicating the format of the file to be read.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
