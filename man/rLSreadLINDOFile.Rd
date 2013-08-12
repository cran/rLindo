\name{rLSreadLINDOFile}
\alias{rLSreadLINDOFile}

\title{Read the model in LINDO format from the given file and stores the problem data in the
given model structure.}

\description{
 R interface function for LINDO API function \code{LSreadLINDOFile}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSreadLINDOFile(model,pszFname)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The path and name of the MPS file to which the model should be written.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSreadMPSFile}}
}