\name{rLSwriteWithSetsAndSC}
\alias{rLSwriteWithSetsAndSC}

\title{Writes the given problem to a specified file in MPS format with the sets and SC vars inserted.}

\description{
 R interface function for LINDO API function \code{LSwriteWithSetsAndSC}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSwriteWithSetsAndSC(model,pszFname,nFormat)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The path and name of the MPS file to which the model should be written.}
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