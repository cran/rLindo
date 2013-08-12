\name{rLSgetFileError}
\alias{rLSgetFileError}

\title{Provides the line number and text of the line in which an error occurred while reading or writing a file.}

\description{
 R interface function for LINDO API function \code{LSgetFileError}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSgetFileError(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnLinenum}{line number in the I/O file where the error has occurred.}
 \item{pachLinetxt}{the text of the line where the error has occurred.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
