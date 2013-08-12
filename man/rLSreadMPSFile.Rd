\name{rLSreadMPSFile}
\alias{rLSreadMPSFile}

\title{Read a model in MPS format from the given file and stores the problem data in the given
problem structure.}

\description{
 R interface function for LINDO API function \code{LSreadMPSFile}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSreadMPSFile(model,pszFname,nFormat)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The path and name of the MPS file.}
 \item{nFormat}{An integer indicating whether the MPS file is formatted or not.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSwriteMPSFile}}
}