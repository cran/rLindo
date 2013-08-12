\name{rLSwriteDualMPSFile}
\alias{rLSwriteDualMPSFile}

\title{Writes the given problem to a specified file in MPS format.}

\description{
 R interface function for LINDO API function \code{LSwriteDualMPSFile}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSwriteDualMPSFile(model,pszFname,nFormat,nObjSense)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The path and name of the MPS file to which the dual model should be written.}
 \item{nFormat}{An integer indicating whether the MPS file is formatted or not.}
 \item{nObjSense}{An integer specifying if the dual problem will be posed as a 
                  maximization or minimization problem.}
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