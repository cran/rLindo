\name{rLSwriteLINDOFile}
\alias{rLSwriteLINDOFile}

\title{Writes the given problem to a file in LINDO format.}

\description{
 R interface function for LINDO API function \code{LSwriteLINDOFile}. For more information,
 please refer to LINDO API User Manual.
}

\details{
Model must be linear.
}

\usage{
rLSwriteLINDOFile(model,pszFname)
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
\code{\link{rLSwriteMPSFile}}
}