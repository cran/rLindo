\name{rLSwriteBasis}
\alias{rLSwriteBasis}

\title{Writes the resident basis to the given file in the specified format.}

\description{
 R interface function for LINDO API function \code{LSwriteBasis}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSwriteBasis(model,pszFname,nFormat)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The path and name of the basis file.}
 \item{nFormat}{An integer parameter indicating the format of the file to be written.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
