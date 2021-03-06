\name{rLSreadModelParameter}
\alias{rLSreadModelParameter}

\title{Reads model parameters from a parameter file.}

\description{
 R interface function for LINDO API function \code{LSreadModelParameter}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSreadModelParameter(model,pszFname)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The path and name of the file from which parameters will be read.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
